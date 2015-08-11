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

#include <windows.h>

#include <vector>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../client/source/Trainer.h"
#include "../../client/source/RateInfo.h"
#include "../../client/source/ModelParameters.h"

#include "pdh.h"

using namespace std;

/**
 * DLL functions prototype style.
 */
#define MT4_EXPFUNC __declspec(dllexport)

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
 * Update training set helper function.
 *
 * @param values Rates vector.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 11 Aug 2015
 */
void updateTrainingSet(std::vector<RateInfo> &values) {
	static bool firstTime = true;
	if (firstTime == true) {
		try {
			if (trainer != NULL) {
				trainer->updateTrainingSet(values, values.size());
			} else {
				isRunning = false;
				fprintf(stderr, "%s %s\n", "              VitoshaTrade00187", "Calculation process stopped.");
			}
		} catch (const char* message) {
			isRunning = false;
			fprintf(stderr, "%s %s\n", "              VitoshaTrade00188", message);
		} catch (...) {
			isRunning = false;
			fprintf(stderr, "%s %s\n", "              VitoshaTrade00189", "Calculation process stopped.");
		}

		firstTime = false;
	} else {
		try {
			if (trainer != NULL) {
				trainer->updateTrainingSet(values, values.size());
			} else {
				isRunning = false;
				fprintf(stderr, "%s %s\n", "              VitoshaTrade00190", "Calculation process stopped.");
			}
		} catch (const char* message) {
			isRunning = false;
			fprintf(stderr, "%s %s\n", "              VitoshaTrade00191", message);
		} catch (...) {
			isRunning = false;
			fprintf(stderr, "%s %s\n", "              VitoshaTrade00192", "Calculation process stopped.");
		}
	}
}

/**
 * Read from file the rates.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 11 Aug 2015
 */
void checkRates() {
	FILE *file = fopen("rates.txt", "rt");
	if(file == NULL) {
		isRunning = false;
		return;
	}

	static double value;
	static int size;
	fscanf(file, "%d", &size);

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
		fscanf(file, "%lf", &value);
		values[i].time = value;
		fscanf(file, "%lf", &value);
		values[i].open = value;
		fscanf(file, "%lf", &value);
		values[i].low = value;
		fscanf(file, "%lf", &value);
		values[i].high = value;
		fscanf(file, "%lf", &value);
		values[i].close = value;
		fscanf(file, "%lf", &value);
		values[i].volume = value;
	}
	fclose(file);

	updateTrainingSet(values);
}

/**
 * Write to file the prediction.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 10 Aug 2015
 */
void checkPrediction() {
	FILE *file = fopen("prediction.txt", "wt");
	if(file == NULL) {
		return;
	}

	fprintf(file, "%lf", predictedValue);
	fclose(file);
}

/**
 * Read from file initial parameters.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 10 Aug 2015
 */
void checkInit() {
	FILE *file = fopen("start.txt", "rt");
	if(file == NULL) {
		isRunning = false;
		return;
	}

	static int period;
	fscanf(file, "%d", &init.dbId);
	fscanf(file, "%s", init.symbol);
	fscanf(file, "%d", &period);
	fscanf(file, "%d", &init.neuronsAmount);
	fscanf(file, "%d", &init.populationSize);
	fscanf(file, "%d", &init.learn);
	fscanf(file, "%d", &init.forecast);
	fclose(file);

	init.inputSize = init.learn;
	init.outputSize = init.forecast;

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
}

/**
 * Read from file is running state.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 10 Aug 2015
 */
void checkIsRunning() {
	FILE *file = fopen("running.txt", "rt");
	if(file == NULL) {
		isRunning = false;
		return;
	}

	static char line[256];
	fscanf(file, "%s", line);
	if(strcmp(line,"true") == 0) {
		isRunning = true;
	} else if(strcmp(line,"false") == 0) {
		isRunning = false;
	} else {
		isRunning = false;
	}

	fclose(file);
}

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
	 * Prediction.
	 */
	try {
		if (trainer != NULL) {
			predictedValue = trainer->predict();
		} else {
			isRunning = false;
			fprintf(stderr, "%s %s\n", "              VitoshaTrade00181", "Calculation process stopped.");
		}
	} catch (const char* message) {
		isRunning = false;
		fprintf(stderr, "%s %s\n", "              VitoshaTrade00182", message);
	} catch (...) {
		isRunning = false;
		fprintf(stderr, "%s %s\n", "              VitoshaTrade00183", "Calculation process stopped.");
	}

	/*
	 * Training.
	 */
	try {
		if (trainer != NULL) {
			trainer->train();
		} else {
			isRunning = false;
			fprintf(stderr, "%s %s\n", "              VitoshaTrade00178", "Calculation process stopped.");
		}
	} catch (const char* message) {
		isRunning = false;
		fprintf(stderr, "%s %s\n", "              VitoshaTrade00179", message);
	} catch (...) {
		isRunning = false;
		fprintf(stderr, "%s %s\n", "              VitoshaTrade00180", "Calculation process stopped.");
	}

	sleep();
}

/**
 * Show about message dialog.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 07 Apr 2009
 */
MT4_EXPFUNC void about() {
	//MessageBox(NULL, "Forex forecasting.", "About VitoshaTrade", 0);
}

/**
 * Start predictor instance and calculation loop of it.
 *
 * @param dbId Database identifier of specific record.
 *
 * @param symbol Forex symbol for trading.
 *
 * @param period Chart period value.
 *
 * @param neuronsAmount Neurons amout to be used if predictor will not be loaded from database.
 *
 * @param populationSize Population size to be used if predictor will not be loaded from database.
 *
 * @param learn Learning bars interval.
 *
 * @param forecast Prediction bars interval.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 07 Apr 2009
 */
MT4_EXPFUNC void startPredictor(const int dbId, const char *symbol, const int period, const int neuronsAmount, const int populationSize, const int learn, const int forecast) {
	/*
	 * Fill init trainer structure.
	 */
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
	init.forecast = forecast;
	init.inputSize = learn;
	init.outputSize = forecast;

	char netType[ 100 ] = "";
	sprintf(netType, "%s%d", symbol, period);
	//MessageBox(NULL, netType, "Network type:", 0);
}

/**
 * Stop predictor and its loop.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 07 Apr 2009
 */
MT4_EXPFUNC void stopPredictor() {
	/*
	 * Deactivate calculation thread.
	 */
	isRunning = false;

	//MessageBox(NULL, "Indicator stop!", "Closing...", 0);
}

/**
 * Load chart historical data.
 *
 * @param rates Chart time series.
 *
 * @param size Size of the time series.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 11 Aug 2009
 */
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

	updateTrainingSet(values);
}

/**
 * Load historical data into predictig module.
 *
 * @return Prediction price value.
 *
 * @author Iliyan Zankinski
 *
 * @email iliyan_mf@abv.bg
 *
 * @date 26 Jul 2009
 */
MT4_EXPFUNC double prediction() {
	return( predictedValue );
}

int WINAPI WinMain(HINSTANCE hInstance,         HINSTANCE hPrevInstance,                   LPSTR lpCmdLine,						int nCmdShow) {
	/*
	 * Initialize pseudo-random number generator.
	 */
	srand( time(NULL) );

	/*
	 * Initial check of the state.
	 */
	checkIsRunning();
	checkInit();

	//TODO Make training set available.

	/*
	 * Allocate memory for trainer object.
	 */
	try {
		trainer = new Trainer();
		if (trainer == NULL) {
			isRunning = false;
			fprintf(stderr, "%s %s\n", "              VitoshaTrade00175", "Calculation process stopped.");
		} else {
			//TODO Fix commucation problems.
			trainer->setup( init );
			isRunning = true;
		}
	} catch (const char* message) {
		isRunning = false;
		fprintf(stderr, "%s %s\n", "              VitoshaTrade00176", message);
	} catch (...) {
		isRunning = false;
		fprintf(stderr, "%s %s\n", "              VitoshaTrade00177", "Calculation process stopped.");
	}

	/*
	 * Application loop.
	 */
	while (isRunning == true) {
		checkIsRunning();
		checkRates();
		run(NULL);
		checkPrediction();
	}

	/*
	 * Free memory of trainer object before thread stop.
	 */
	try {
		isRunning = false;
		delete(trainer);
	} catch (const char* message) {
		fprintf(stderr, "%s %s\n", "              VitoshaTrade00184", message);
	} catch (...) {
		fprintf(stderr, "%s %s\n", "              VitoshaTrade00185", "Calculation process stopped.");
	}
	trainer = NULL;

	return (int) 0;
}
