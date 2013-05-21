/*******************************************************************************
 *                                                                             *
 * VitoshaTrade is Distributed Artificial Neural Network trained by            *
 * Differential Evolution for prediction of Forex. Project development is in   *
 * Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   *
 * the capital of Bulgaria.                                                    *
 *                                                                             *
 * Copyright (C) 2008-2011 by Todor Balabanov  ( tdb@tbsoft.eu )               *
 *                            Iliyan Zankinski ( iliyan_mf@abv.bg )            *
 *                            Galq Cirkalova   ( galq_cirkalova@abv.bg )       *
 *                            Ivan Grozev      ( ivan.iliev.grozev@gmail.com ) *
 *                            Nikola Simeonov  ( n.simeonow@gmail.com )        *
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
#define WIN32_LEAN_AND_MEAN

#include "../include/wrapper.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "../../../mql4/include/pdh.h"
#include "../../../client/include/trainer/Trainer.h"
#include "../../../client/include/trainer/RateInfo.h"

/**
 * Thread identifyer.
 */
static DWORD threadId;

/**
 * Thread handle.
 */
static HANDLE threadHandle;

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
 * Information needed to initialize trainer object.
 */
static struct {
	int dbId;
	char symbol[100];
	int period;
	int neuronsAmount;
	int populationSize;
	int bars;
} init;

/**
 * Measure CPU overload by using Microsoft performance data helper.
 *
 * @return CPU overload in percent.
 *
 * @author Nikola Simeonov
 *
 * @email n.simeonow@gmail.com
 *
 * @date 12 Jan 2011
 */
double cpuOverload() {
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
}

/**
 * Platform independent sleep.
 *
 * @author Nikola Simeonov
 *
 * @email n.simeonow@gmail.com
 *
 * @date 12 Jan 2011
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
 * @author Nikola Simeonov
 *
 * @email n.simeonow@gmail.com
 *
 * @date 19 Jan 2011
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
		trainer = new Trainer(init.dbId, init.symbol, init.period, init.neuronsAmount, init.populationSize, init.bars);
		isRunning = true;
	} catch (const char* message) {
		isRunning = false;
		MessageBox(NULL, message, "Trainer construction error.", 0);
		fprintf(stderr, "%s\n", message);
	} catch (...) {
		isRunning = false;
		MessageBox(NULL, "Unknown error.", "Trainer construction error.", 0);
	}
	LeaveCriticalSection( &criticalSection );

	/*
	 * Thread infinite loop.
	 */
	while (isRunning == true) {
		EnterCriticalSection( &criticalSection );

		/*
		 * Training.
		 */
		try {
			trainer->train();
		} catch (const char* message) {
			isRunning = false;
			MessageBox(NULL, message, "Calculating thread run method error.", 0);
			fprintf(stderr, "%s\n", message);
		} catch (...) {
			isRunning = false;
			MessageBox(NULL, "Unknown error.", "Calculating thread run method error.", 0);
		}

		/*
		 * Prediction.
		 */
		try {
			predictedValue = trainer->predict();
		} catch (const char* message) {
			isRunning = false;
			MessageBox(NULL, message, "Calculate prediction error.", 0);
			fprintf(stderr, "%s\n", message);
		} catch (...) {
			isRunning = false;
			MessageBox(NULL, "Unknown error.", "Calculate prediction error.", 0);
		}

		LeaveCriticalSection( &criticalSection );
		sleep();
	}

	/*
	 * Free memory of trainer object.
	 */
	EnterCriticalSection( &criticalSection );
	try {
		delete(trainer);
	} catch (const char* message) {
		isRunning = false;
		MessageBox(NULL, message, "Trainer destruction error.", 0);
		fprintf(stderr, "%s\n", message);
	} catch (...) {
		isRunning = false;
		MessageBox(NULL, "Unknown error.", "Trainer destruction error.", 0);
	}
	trainer = NULL;
	LeaveCriticalSection( &criticalSection );
}

void __stdcall about() {
	MessageBox(NULL, "Forex forecasting.", "About VitoshaTrade", 0);
}

void __stdcall startPredictor(const int dbId, const char *symbol, const int period, const int neuronsAmount, const int populationSize, const int bars) {
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
	init.period = period;
	init.neuronsAmount = neuronsAmount;
	init.populationSize = populationSize;
	init.bars = bars;

	/*
	 * Activate calculation thread.
	 */
	threadHandle = CreateThread(NULL, 0, run, NULL, 0, &threadId);

	/*
	 * Run-time check thread handle for NULL pointer and report error if any.
	 */
	if (threadHandle == NULL) {
		isRunning = false;
		MessageBox(NULL, "Calculating thread creation error.", "Thread creation error.", 0);
	}
	LeaveCriticalSection( &criticalSection );

	char netType[ 100 ] = "";
	sprintf(netType, "%s%d", symbol, period);
	//MessageBox(NULL, netType, "Network type:", 0);
}

void __stdcall stopPredictor() {
	/*
	 * Deactivate calculation thread.
	 */
	isRunning = false;
	WaitForSingleObject(threadHandle, INFINITE);
	CloseHandle( threadHandle );

	/*
	 * Delete critical section object.
	 */
	DeleteCriticalSection(&criticalSection);

	//MessageBox(NULL, "Indicator stop!", "Closing...", 0);
}

void __stdcall loadChartData(const RateInfo *rates, int size) {
	/*
	 * Return if there is no conditions to update.
	 */
	if (size<=0 || isRunning==false || trainer==NULL || rates==NULL) {
		return;
	}

	static bool firstTime = true;
	if (firstTime == true) {
		EnterCriticalSection( &criticalSection );
		try {
			trainer->updateTrainingSet(rates, size);
		} catch (const char* message) {
			isRunning = false;
			MessageBox(NULL, message, "First time update training set error.", 0);
			fprintf(stderr, "%s\n", message);
		} catch (...) {
			isRunning = false;
			MessageBox(NULL, "Unknown error.", "First time update training set error.", 0);
		}

		firstTime = false;
		LeaveCriticalSection( &criticalSection );
	} else if (TryEnterCriticalSection(&criticalSection) == true) {
		try {
			trainer->updateTrainingSet(rates, size);
		} catch (const char* message) {
			isRunning = false;
			MessageBox(NULL, message, "Update training set error.", 0);
			fprintf(stderr, "%s\n", message);
		} catch (...) {
			isRunning = false;
			MessageBox(NULL, "Unknown error.", "Update training set error.", 0);
		}

		LeaveCriticalSection( &criticalSection );
	}
}

double __stdcall prediction() {
	return( predictedValue );
}
