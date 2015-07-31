/*******************************************************************************
 *                                                                             *
 * VitoshaTrade is Distributed Artificial Neural Network trained by            *
 * Differential Evolution for prediction of Forex. Project development is in   *
 * Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   *
 * the capital of Bulgaria.                                                    *
 *                                                                             *
 * Copyright (C) 2008-2011 by Todor Balabanov  ( tdb@tbsoft.eu )               *
 *                       Iliyan Zankinski   ( iliyan_mf@abv.bg )               *
 *                       Momchil Anachkov   ( mZer0000@gmail.com )             *
 *                       Daniel Chutrov     ( d.chutrov@gmail.com )            *
 *                       Nikola Simeonov    ( n.simeonow@gmail.com )           *
 *                       Galq Cirkalova     ( galq_cirkalova@abv.bg )          *
 *                       Ivan Grozev        ( ivan.iliev.grozev@gmail.com )    *
 *                       Elisaveta Hristova ( elisaveta.s.hristova@gmail.com ) *
 *                                                                             *
 * This program is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.        *
 *                                                                             *
 ******************************************************************************/

/**
 * Exclude rarely-used parts from Windows headers.
 */
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <vector>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "../../client/source/Trainer.h"
#include "../../client/source/RateInfo.h"
#include "../../client/source/ModelParameters.h"

#include "pdh.h"

#include "VitoshaTrade.h"

/**
 * Thread identifier.
 */
static DWORD threadId;

/**
 * Thread handle.
 */
static HANDLE threadHandle = NULL;

/**
 * Critical section for threads synchronization.
 */
static CRITICAL_SECTION criticalSection;

/**
 * Control running of the thread.
 */
bool isRunning = false;

/**
 * Trainer instance.
 */
static Trainer *trainer = NULL;

/**
 * Trainer instance.
 */
static double predictedValue = 0.0;

/**
 * Calculating model initial parameters.
 */
static ModelParameters init;

/**
 * Measure CPU overload by using Microsoft performance data helper.
 *
 * @return CPU overload in percent.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 24 Aug 2009
 */
double cpuOverload() {
	//TODO Platform specific problems should be solved.
	return(50.0);

	static HCOUNTER counterHandle;
	static PDH_FMT_COUNTERVALUE formatValue;

	/*
	 * Microsoft PDH query.
	 */
	static HQUERY queryHandle;

	/*
	 * Open Microsoft PDH query.
	 */
	PdhOpenQuery(NULL, 0, &queryHandle);

	PdhCollectQueryData( queryHandle );
	PdhAddCounter(queryHandle, "\\Processor(_Total)\\% Processor Time", 0, &counterHandle);
	PdhGetFormattedCounterValue(counterHandle, PDH_FMT_DOUBLE, NULL, &formatValue);

	/*
	 * Close Microsoft PDH query.
	 */
	PdhCloseQuery( queryHandle );

	if (formatValue.doubleValue < 0.0) {
		return( 50.0 );
	} else if (formatValue.doubleValue > 100.0) {
		return( 50.0 );
	} else {
		return( formatValue.doubleValue );
	}

	return(0.0);
}

/**
 * Platform independent sleep.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 21 Aug 2009
 */
void sleep() {
	/*
	 * Number of clock ticks elapsed since the program was launched in
	 * milliseconds. Constant should not be zero, because it is used as divisor.
	 */
	static const unsigned long CLOCKS_PER_MSEC = CLOCKS_PER_SEC/1000==0?1:CLOCKS_PER_SEC/1000;

	/*
	 * Minimum time after which thread will go in sleep mode in milliseconds.
	 */
	static const unsigned long DO_NOT_SLEEP_FOR_LESS_THAN = 100;

	/*
	 * Minimum time for thread to sleep in milliseconds.
	 */
	static const unsigned long MIN_TIME_FOR_SLEEP = 0;

	/*
	 * Maximum time for thread to sleep in milliseconds.
	 */
	static const unsigned long MAX_TIME_FOR_SLEEP = 1000;

	/*
	 * Last moment in time when thread slept.
	 */
	static unsigned long lastSleepTime = 0;

	/*
	 * Execute sleep only if fixed amount of time was spend.
	 */
	if ((clock()-lastSleepTime)/CLOCKS_PER_MSEC < DO_NOT_SLEEP_FOR_LESS_THAN) {
		return;
	} else {
		unsigned long time = (unsigned long)(cpuOverload()/100.0*(MAX_TIME_FOR_SLEEP-MIN_TIME_FOR_SLEEP) + MIN_TIME_FOR_SLEEP);
		Sleep( time );

		lastSleepTime = clock() / CLOCKS_PER_MSEC;
	}
}

/**
 * Thread run/loop function.
 *
 * @param arg Thread function parameter.
 *
 * @return
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 04 May 2009
 */
DWORD WINAPI run(void *arg) {
	/*
	 * Initialize pseudo-random number generator.
	 */
	srand( time(NULL) );

	/*
	 * Put the thread in idle mode.
	 */
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_IDLE);

	/*
	 * Allocate memory for trainer object.
	 */
	EnterCriticalSection( &criticalSection );
	try {
		trainer = new Trainer();
		if (trainer == NULL) {
			isRunning = false;
			MessageBox(NULL, "              VitoshaTrade00175", "Calculation process stopped.", 0);
		} else {
			//TODO Fix commucation problems.
			trainer->setup( init );
			isRunning = true;
		}
	} catch (const char* message) {
		isRunning = false;
		MessageBox(NULL, "              VitoshaTrade00176", message, 0);
		fprintf(stderr, "%s\n", message);
	} catch (...) {
		isRunning = false;
		MessageBox(NULL, "              VitoshaTrade00177", "Calculation process stopped.", 0);
	}
	LeaveCriticalSection( &criticalSection );

	/*
	 * Thread infinite loop.
	 */
	while (isRunning == true) {
		EnterCriticalSection( &criticalSection );

		/*
		 * Prediction.
		 */
		try {
			if (trainer != NULL) {
				predictedValue = trainer->predict();
			} else {
				isRunning = false;
				MessageBox(NULL, "              VitoshaTrade00181", "Calculation process stopped.", 0);
			}
		} catch (const char* message) {
			isRunning = false;
			MessageBox(NULL, "              VitoshaTrade00182", message, 0);
			fprintf(stderr, "%s\n", message);
		} catch (...) {
			isRunning = false;
			MessageBox(NULL, "              VitoshaTrade00183", "Calculation process stopped.", 0);
		}

		/*
		 * Training.
		 */
		try {
			if (trainer != NULL) {
				trainer->train();
			} else {
				isRunning = false;
				MessageBox(NULL, "              VitoshaTrade00178", "Calculation process stopped.", 0);
			}
		} catch (const char* message) {
			isRunning = false;
			MessageBox(NULL, "              VitoshaTrade00179", message, 0);
			fprintf(stderr, "%s\n", message);
		} catch (...) {
			isRunning = false;
			MessageBox(NULL, "              VitoshaTrade00180", "Calculation process stopped.", 0);
		}

		LeaveCriticalSection( &criticalSection );
		sleep();
	}

	/*
	 * Free memory of trainer object before thread stop.
	 */
	EnterCriticalSection( &criticalSection );
	try {
		isRunning = false;
		delete(trainer);
	} catch (const char* message) {
		MessageBox(NULL, "              VitoshaTrade00184", message, 0);
		fprintf(stderr, "%s\n", message);
	} catch (...) {
		MessageBox(NULL, "              VitoshaTrade00185", "Calculation process stopped.", 0);
	}
	trainer = NULL;
	LeaveCriticalSection( &criticalSection );
}

MT4_EXPFUNC void about() {
	//MessageBox(NULL, "Forex forecasting.", "About VitoshaTrade", 0);
}

MT4_EXPFUNC void startPredictor(const int dbId, const char *symbol, const int period, const int neuronsAmount, const int populationSize, const int learn, const int bars) {
	/*
	 * Initialize critical section object.
	 */
	if ( !InitializeCriticalSectionAndSpinCount(&criticalSection,0x80000400) ) {
		//TODO Report error.
		return;
	}

	/*
	 * Fill init trainer structure.
	 */
	EnterCriticalSection( &criticalSection );
	init.dbId = dbId;
	strcpy(init.symbol, symbol);
	switch( period ) {
	case M1:
		init.period = M1;
		break;
	case M5:
		init.period = M5;
		break;
	case M15:
		init.period = M15;
		break;
	case M30:
		init.period = M30;
		break;
	case H1:
		init.period = H1;
		break;
	case H4:
		init.period = H4;
		break;
	case D1:
		init.period = D1;
		break;
	case W1:
		init.period = W1;
		break;
	case MN1:
		init.period = MN1;
		break;
	default:
		init.period = NO;
		break;
	}
	init.neuronsAmount = neuronsAmount;
	init.populationSize = populationSize;
	init.learn = learn;
	init.bars = bars;
	init.inputSize = learn;
	init.outputSize = bars;

	/*
	 * Activate calculation thread.
	 */
	if(threadHandle == NULL) {
		threadHandle = CreateThread(NULL, 0, run, NULL, CREATE_SUSPENDED, &threadId);
	}

	/*
	 * Run-time check thread handle for NULL pointer and report error if any.
	 */
	if (threadHandle == NULL) {
		isRunning = false;
		MessageBox(NULL, "              VitoshaTrade00186", "Calculation process stopped.", 0);
	}
	LeaveCriticalSection( &criticalSection );
	if(threadHandle!=NULL && ResumeThread(threadHandle)==(DWORD)-1) {
		char error[100] = "";
		sprintf(error, "%ld", (long)GetLastError());
		MessageBox(NULL, "              VitoshaTrade00201", error, 0);
	}

	char netType[ 100 ] = "";
	sprintf(netType, "%s%d", symbol, period);
	//MessageBox(NULL, netType, "Network type:", 0);
}

MT4_EXPFUNC void stopPredictor() {
	/*
	 * Deactivate calculation thread.
	 */
	EnterCriticalSection( &criticalSection );
	isRunning = false;
	LeaveCriticalSection( &criticalSection );
	//TODO Investigate effects caused by the second parameter.
	WaitForSingleObject(threadHandle, 0);
	CloseHandle( threadHandle );

	/*
	 * Delete critical section object.
	 */
	DeleteCriticalSection(&criticalSection);

	//MessageBox(NULL, "Indicator stop!", "Closing...", 0);
}

MT4_EXPFUNC void loadChartData(double rates[][6], int size) {
	/*
	 * Return if there is no conditions to update.
	 */
	if (size<=0 || isRunning==false || trainer==NULL || rates==NULL) {
		return;
	}

	/*
	 * 0 - time
	 * 1 - open
	 * 2 - low
	 * 3 - high
	 * 4 - close
	 * 5 - volume
	 */
	std::vector<RateInfo> values( size );
	for(int i=0; i<size; i++) {
		values[i].time = rates[i][0];
		values[i].open = rates[i][1];
		values[i].low = rates[i][2];
		values[i].high = rates[i][3];
		values[i].close = rates[i][4];
		values[i].volume = rates[i][5];
	}

	static bool firstTime = true;
	if (firstTime == true) {
		EnterCriticalSection( &criticalSection );
		try {
			if (trainer != NULL) {
				trainer->updateTrainingSet(values, size);
			} else {
				isRunning = false;
				MessageBox(NULL, "              VitoshaTrade00187", "Calculation process stopped.", 0);
			}
		} catch (const char* message) {
			isRunning = false;
			MessageBox(NULL, "              VitoshaTrade00188", message, 0);
			fprintf(stderr, "%s\n", message);
		} catch (...) {
			isRunning = false;
			MessageBox(NULL, "              VitoshaTrade00189", "Calculation process stopped.", 0);
		}

		firstTime = false;
		LeaveCriticalSection( &criticalSection );
	} else if (TryEnterCriticalSection(&criticalSection) == true) {
		try {
			if (trainer != NULL) {
				trainer->updateTrainingSet(values, size);
			} else {
				isRunning = false;
				MessageBox(NULL, "              VitoshaTrade00190", "Calculation process stopped.", 0);
			}
		} catch (const char* message) {
			isRunning = false;
			MessageBox(NULL, "              VitoshaTrade00191", message, 0);
			fprintf(stderr, "%s\n", message);
		} catch (...) {
			isRunning = false;
			MessageBox(NULL, "              VitoshaTrade00192", "Calculation process stopped.", 0);
		}

		LeaveCriticalSection( &criticalSection );
	}
}

MT4_EXPFUNC double prediction() {
	return( predictedValue );
}

/**
 * Standard DLL main function.
 *
 * @param hInst
 *
 * @param reason
 *
 * @param reserved
 *
 * @return Predicted value.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 11 Aug 2009
 */
BOOL APIENTRY DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved) {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_PROCESS_DETACH:
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;
	}

	return( TRUE );
}
