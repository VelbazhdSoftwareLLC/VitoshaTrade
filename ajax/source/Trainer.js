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
 *                            Daniel Chutrov   ( d.chutrov@gmail.com )         *
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

/*
 * Include files.
 */
document.write('<script type="text/javascript" src="' + 'HttpCommunicator.js' + '"></scr' + 'ipt>');
document.write('<script type="text/javascript" src="' + 'TrainingSet.js' + '"></scr' + 'ipt>');
document.write('<script type="text/javascript" src="' + 'ANN.js' + '"></scr' + 'ipt>');
document.write('<script type="text/javascript" src="' + 'DE.js' + '"></scr' + 'ipt>');
document.write('<script type="text/javascript" src="' + 'Counter.js' + '"></scr' + 'ipt>');

/**
 * Constructing trainer by using database data or user defined parameters.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 12 Sep 2009
 */
function Trainer() {
	/**
	 * At start there is no report at all.
	 */
	this.lastBestFitnessReportTime = 0;

	/**
	 * Statistic counters dynamic instance.
	 */
	this.counters = new Counter();

	/*
	 * Estimate work done.
	 */
	var value = new Date();
	this.counters.setValue("Training start time", "" + value);

	/**
	 * Artificial neural network trainer.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 29 Dec 2010
	 */
	this.setup = function(dbId, symbol, period, neuronsAmount, populationSize, bars) {
		//
		// /**
		// * Default random maximum value.
		// */
		// const RAND_MAX = 32767;
		//
		// /**
		// * Do report flag.
		// */
		// const DO_FINAL_REPORT = true;
		//
		// /**
		// * Number of seconds to request training set update.
		// */
		// const TRAINING_SET_UPDATE_INTERVAL = 600;
		//
		// /**
		// * Number of seconds to report local best fitness.
		// */
		// const BEST_FITNESS_REPORT_INTERVAL = 600;
		//
		// /**
		// * MetaTrader 4 chart symbol.
		// */
		// this.symbol = symbol;
		//
		// /**
		// * MetaTrader 4 chart period.
		// */
		// this.period = period;
		//
		// /**
		// * HTTP comunication dynamic instance.
		// */
		// this.http = new HttpCommunicator();
		//
		// /**
		// * Training set dynamic instance.
		// */
		// this.ts = new TrainingSet(null, this.http.loadTrainingSetSize(symbol, period));
		//
		// /**
		// * Statistic counters dynamic instance.
		// */
		// this.counters = new Counter();
		//
		// /**
		// * Artificial neural network dynamic instance.
		// */
		// this.ann = new ANN(this.ts, neuronsAmount, bars, period);
		//
		// /**
		// * Differential evolution dynamic instance.
		// */
		// this.de = new DE(this.ann, populationSize, 90.0, 10.0);
		//
		// /**
		// * Last best local fitness report UNIX time.
		// */
		// this.lastBestFitnessReportTime = 0;
		//
		// /*
		// * At the beggining there is no training set.
		// */
		// this.http.loadTrainingSet(symbol, period, this.ts.rates, this.ts.size);
		//
		// /*
		// * Create object structure.
		// */
		// this.http.loadTrainerObjects(this.ann, this.de, this.dbId, this.symbol, this.period, this.neuronsAmount, this.populationSize, this.bars);
		// this.ann.ts = this.ts;
	}
	/**
	 * Update training set.
	 *
	 * @param rates Array with rates values.
	 *
	 * @param size Size of all parallel arrays.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 23 Dec 2010
	 */
	this.updateTrainingSet = function(rates, size) {
		//		/*
		//		 * Do not update if there is no new data at latest known time.
		//		 */
		//		if (ts!=null && ts.size==size && ts.getTime(ts.size-1)==rates[size-1].time) {
		//			return;
		//		}
		//
		//		/*
		//		 * Create new training set object and swap it with the old one.
		//		 */
		//		var swap = null;
		//		var temp = new TrainingSet(ts, rates, size);
		//
		//		swap = ts;
		//		ts = temp;
		//		temp = swap;
		//
		//		swap = null;
		//		temp = null;
		//
		//		/*
		//		 * Update ANN training set pointer.
		//		 */
		//		ann.setTrainingSetPointer( ts );
		//
		//		/*
		//		 * Select random chromosome to be best, because with new training set it is
		//		 * not sure that previous beest chromosome will be best again.
		//		 */
		//		de.setBestFitnessIndex( Math.floor(Math.random()*(de.getPopulationSize())))
	}
	/**
	 * Do training process.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 23 Dec 2010
	 */
	this.train = function() {
		// /*
		// * If training set is not present training can not be done.
		// */
		// if (this.ts == null || this.ts.size == 0) {
		// return;
		// }
		//
		// /*
		// * Run one epoche of evolution.
		// */
		// if (this.de != null) {
		// this.de.evolve();
		// }
		//
		// /*
		// * Report best chromosome at regular time interval.
		// */
		// if ((new Date()).getTime() - BEST_FITNESS_REPORT_INTERVAL > this.lastBestFitnessReportTime) {
		// this.reportLocalBestFitness();
		// }
	}
	/**
	 * Obtain predicted value.
	 *
	 * @return Predicted value.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 23 Dec 2010
	 */
	this.predict = function() {
		//		/*
		//		 * If training set is not present training can not be done.
		//		 */
		//		if (ts==null || ts.size==0 || ann==null) {
		//			return( 0 );
		//		}
		//
		//		return( this.ann.prediction );
	}
	/**
	 * Report local best fitness.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 23 Dec 2010
	 */
	this.reportLocalBestFitness = function() {
		//		/*
		//		 * Remote best fitness to be used as level for better result server report.
		//		 */
		//		var remoteBestFitness = Math.random()*RAND_MAX;
		//
		//		/*
		//		 * Get pointers needed.
		//		 */
		//		var activities = ann.activities;
		//		var neuronsFlags = ann.neuronsFlags;
		//
		//		/*
		//		 * Check remote best fitness.
		//		 */
		//		remoteBestFitness = http.loadRemoteBestFitness(symbol, period, ann.neuronsAmount, neuronsFlags, activities);
		//
		//		/*
		//		 * Load Compare remote and local best fitness value.
		//		 */
		//		if (de.fitness[de.bestFitnessIndex] < remoteBestFitness) {
		//			var weights = de.weights( de.bestFitnessIndex );
		//			http.saveSingleANN(symbol, period, de.fitness[de.bestFitnessIndex], ann.neuronsAmount, neuronsFlags, weights, activities);
		//			http.saveTrainingSet(symbol, period, ts.rates, ts.size);
		//		}
		//
		//		/*
		//		 * Mark last time checked for server best fitness.
		//		 */
		//		this.lastBestFitnessReportTime = (new Date()).getTime();
	}
}
