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

#property copyright "Copyright © 2008-2014, Todor Balabanov"
#property link "http://vitoshatrade.veldsoft.eu/"
#property version "1.001"
#property strict
#property indicator_chart_window
#property indicator_buffers 0

#include <VitoshaTrade.mqh>

/**
 * Right arrow symbol.
 */
#define SYMBOL_ARROWRIGHT 240

/**
 * MQL4 maximum random value available.
 */
#define RAND_MAX 32767.0

/**
 * Color to be used for text messages.
 */
extern color TEXT_COLOR = Red;

/**
 * Color to be used for up price.
 */
extern color UP_COLOR = Cyan;

/**
 * Color to be used for down price.
 */
extern color DOWN_COLOR = Orange;

/**
 * ANN neurons amout input parameter.
 */
extern int NEURONS_AMOUNT = 35;

/**
 * DE population size indicator input parameter.
 */
extern int POPULATION_SIZE = 45;

/**
 * Number of bars to be used for trainign.
 */
extern int TRAINING_BARS = 250;

/**
 * Inspect interval in bars (number of past bars window).
 */
extern int INSPECT_BARS = 25;

/**
 * Predict interval in bars (number of future bars window).
 */
extern int PREDICT_BARS = 5;

/**
 * Predictor database id.
 *
 * Value 0 is used for no existing database record.
 */
extern int PREDICTOR_ID = 0;

/**
 * Send historical data to software module.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft-bg.com
 *
 * @date 07 Apr 2009
 */
void sendDataToPredictor() {
	double rates[][6];
	int size = ArrayCopyRates( rates );

	/*
	 * Do nothing if there is no enough data.
	 */
	if(size < TRAINING_BARS) {
		return;
	}

	/*
	 * Normalize values between zero and one.
	 * Time should not be normalized. It should be on index 0.
	 */
	for(int r=1; r<6; r++) {
		double min = rates[0][r];
		double max = rates[0][r];
		for(int i=0; i<size; i++) {
			if(rates[i][r] < min) {
				min = rates[i][r];
			}
			if(rates[i][r] > max) {
				max = rates[i][r];
			}
		}

		for(int i=0; i<size; i++) {
			rates[i][r] = (rates[i][r]-min) / (max - min);
		}
	}

	_Z13loadChartDataPK8RateInfoi(rates, TRAINING_BARS);
}

/**
 * Indicator initialization function.
 *
 * @return Execution error code.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft-bg.com
 *
 * @date 01 Aug 2014
 */
int OnInit() {
	/*
	 * Show about box as welcome screen.
	 */
	_Z5aboutv();

	/*
	 * Validate input data.
	 */
	if (NEURONS_AMOUNT < 0) {
		NEURONS_AMOUNT = 0;
	}

	if (POPULATION_SIZE < 0) {
		POPULATION_SIZE = 0;
	}

	if (TRAINING_BARS < 0) {
		TRAINING_BARS = 0;
	}

	if (TRAINING_BARS > Bars) {
		TRAINING_BARS = Bars;
	}

	if (INSPECT_BARS < 0) {
		INSPECT_BARS = 0;
	}

	if (PREDICT_BARS < 0) {
		PREDICT_BARS = 0;
	}

	/*
	 * Seed PRNG.
	 */
	MathSrand( GetTickCount() );

	/*
	 * Initialize predictor.
	 */
	char value[255];
	StringToCharArray(Symbol(), value);
	_Z14startPredictoriPKciiiii(PREDICTOR_ID, value, Period(), NEURONS_AMOUNT, POPULATION_SIZE, INSPECT_BARS, PREDICT_BARS);

	return( 0 );
}

/**
 * Indicator deinitialization function.
 *
 * @return Execution error code.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft-bg.com
 *
 * @date 01 Aug 2014
 */
void OnDeinit(const int reason) {
	if (ObjectFind("arrow") == 0) {
		ObjectDelete( "arrow" );
	}
	if (ObjectFind("text") == 0) {
		ObjectDelete( "text" );
	}
	if (ObjectFind("line") == 0) {
		ObjectDelete( "line" );
	}

	/*
	 * Stop and destroy predictor.
	 */
	_Z13stopPredictorv();
}

/**
 * Indicator iteration function.
 *
 * @return Execution error code.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft-bg.com
 *
 * @date 01 Aug 2014
 */
int OnCalculate(const int rates_total,
				const int prev_calculated,
				const datetime& time[],
				const double& open[],
				const double& high[],
				const double& low[],
				const double& close[],
				const long& tick_volume[],
				const long& volume[],
				const int& spread[]) {

	/*
	 * Send historical data to predicting module.
	 */
	sendDataToPredictor();

	/*
	 * Clear visual objects from previous call.
	 */
	if (ObjectFind("arrow") == 0) {
		ObjectDelete( "arrow" );
	}
	if (ObjectFind("text") == 0) {
		ObjectDelete( "text" );
	}
	if (ObjectFind("line") == 0) {
		ObjectDelete( "line" );
	}

	/*
	 * Create text object.
	 */
	ObjectCreate("text", OBJ_LABEL, 0, 0, 0);
	ObjectSet("text", OBJPROP_CORNER, 2);
	ObjectSet("text", OBJPROP_XDISTANCE, 5);
	ObjectSet("text", OBJPROP_YDISTANCE, 5);
	ObjectSet("text", OBJPROP_BACK, true);

	/*
	 * Ask for prediction.
	 */
	static double lastValue = 0.0;
	double value = 0.0;
	value = _Z10predictionv();

	/*
	 * Denormalize prediction.
	 */
	double min = low[0];
	double max = high[0];
	for(int i=0; i<rates_total; i++) {
		if(low[i] < min) {
			min = low[ i ];
		}
		if(high[i] < max) {
			max = high[ i ];
		}
	}
	value = min + value*(max-min);

	/*
	 * Display prediction.
	 */
	if (value==0.0 && lastValue==0.0) {
		ObjectSetText("text", "Calculating ...", 8, "Arial", TEXT_COLOR);
	} else {
		ObjectCreate("arrow", OBJ_ARROW, 0, Time[0], WindowPriceMax());
		ObjectSet("arrow", OBJPROP_STYLE, STYLE_SOLID);

		ObjectCreate("line", OBJ_HLINE, 0, Time[0], lastValue, 0, 0);
		ObjectSet("line", OBJPROP_STYLE, STYLE_SOLID);

		if (lastValue > (Ask+Bid)/2.0) {
			ObjectSet("arrow", OBJPROP_ARROWCODE, SYMBOL_ARROWUP);
			ObjectSet("arrow", OBJPROP_COLOR, UP_COLOR);
			ObjectSet("line", OBJPROP_COLOR, UP_COLOR);
			ObjectSetText("text", ""+DoubleToString(lastValue)+" ~ "+DoubleToString(PREDICT_BARS)+" bar(s).", 8, "Arial", UP_COLOR);
		} else if (lastValue < (Ask+Bid)/2.0) {
			ObjectSet("arrow", OBJPROP_ARROWCODE, SYMBOL_ARROWDOWN);
			ObjectSet("arrow", OBJPROP_COLOR, DOWN_COLOR);
			ObjectSet("line", OBJPROP_COLOR, DOWN_COLOR);
			ObjectSetText("text", ""+DoubleToString(lastValue)+" ~ "+DoubleToString(PREDICT_BARS)+" bar(s).", 8, "Arial", DOWN_COLOR);
		} else if (lastValue == (Ask+Bid)/2.0) {
			ObjectSet("arrow", OBJPROP_ARROWCODE, SYMBOL_ARROWRIGHT);
			ObjectSet("arrow", OBJPROP_COLOR, TEXT_COLOR);
			ObjectSet("line", OBJPROP_COLOR, TEXT_COLOR);
			ObjectSetText("text", "No change.", 8, "Arial", TEXT_COLOR);
		}
	}

	/*
	 * Redraw chart.
	 */
	WindowRedraw();

	/*
	 * Keep value predicted on the previous call.
	 */
	if (value != 0.0) {
		lastValue = value;
	}

	return( 0 );
}
