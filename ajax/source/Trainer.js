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
document.write('<script type="text/javascript" src="' + 'JsonHttpCommunicator.js' + '"></script>');
document.write('<script type="text/javascript" src="' + 'TrainingSet.js' + '"></script>');
document.write('<script type="text/javascript" src="' + 'ANN.js' + '"></script>');
document.write('<script type="text/javascript" src="' + 'DE.js' + '"></script>');
document.write('<script type="text/javascript" src="' + 'Counter.js' + '"></script>');
document.write('<script type="text/javascript" src="' + 'ModelParameters.js' + '"></script>');
document.write('<script type="text/javascript" src="' + 'cstdlib.js' + '"></script>');
document.write('<script type="text/javascript" src="' + 'ctime.js' + '"></script>');

/**
 * Do report flag.
 */
const DO_FINAL_REPORT = true;

/**
 * Report file name.
 */
const REPORT_FILE_NAME = "VitoshaTradeTrainingReport.txt";

/**
 * Number of seconds to request training set update.
 */
const TRAINING_SET_UPDATE_INTERVAL = 600;

/**
 * Number of seconds to report local best fitness.
 */
const BEST_FITNESS_REPORT_INTERVAL = 600;

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

	/**
	 * HTTP comunication dynamic instance.
	 */
	this.http = new JsonHttpCommunicator();

	/*
	 * Estimate work done.
	 */
	this.counters.setValue("Training start time", "" + time(null));

	/**
	 * Artificial neural network trainer.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 29 Dec 2010
	 */
	this.setup = function(parameters) {
		/**
		 * MetaTrader 4 chart symbol.
		 */
		this.symbol = parameters.symbol;

		/**
		 * MetaTrader 4 chart period.
		 */
		this.period = parameters.period;

		/**
		 * Training set dynamic instance.
		 */
		this.ts = new TrainingSet();

		/**
		 * Artificial neural network dynamic instance.
		 */
		this.ann = new ANN(counters, ts, parameters.neuronsAmount, parameters.learn, parameters.forecast, period);

		/**
		 * Differential evolution dynamic instance.
		 */
		this.de = new DE();

		/*
		* At the beginning there is no training set.
		*/
		var result = http.loadTrainingSet(symbol, period, ts.getRates(), ts.getSize());
		this.ts = new TrainingSet(result[0], result[1], parameters.learn, parameters.forecast);
		ts.splitData(parameters.learn, parameters.forecast); 

		/*
		 * Create object structure.
		 */
		result = http.loadTrainerObjects(this.ann, this.de, parameters);
		this.ann = result[0];
		this.de = result[1];
		ann.setTrainingSetPointer(this.ts);
	};

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
		/*
		 * Do not update if there is no new data at latest known time.
		 */
		if (ts.getSize() == size && ts.getTime(ts.getSize() - 1) == rates[size - 1].time) {
			return;
		}

		/*
		 * Create new training set object and swap it with the old one.
		 * Constructor with merge capabilities also can be used.
		 */
		ts = new TrainingSet(rates, size, ann.getNeurons().getInputNeuronsAmount(), ann.getNeurons().getOutputNeuronsAmount());

		/*
		 * Update ANN training set pointer.
		 */
		ann.setTrainingSetPointer(ts);

		/*
		 * Estimate work done.
		 */
		counters.setValue("Training set size", ts.getSize());
	};

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
		/*
		 * If training set is not present training can not be done.
		 */
		if (ts.getSize() == 0) {
			return;
		}

		/*
		 * Run one epoche of evolution.
		 */
		de.evolve();

		/*
		 * Report best chromosome at regular time interval.
		 */
		if (time(null) - BEST_FITNESS_REPORT_INTERVAL > lastBestFitnessReportTime) {
			reportLocalBestFitness();
		}
	};

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
		/*
		 * If training set is not present training can not be done.
		 */
		if (ts.getSize() == 0) {
			return (0 );
		}

		return ( ann.getPrediction() );
	};

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
		/*
		 * Remote best fitness to be used as level for better result server report.
		 */
		var remoteBestFitness = RAND_MAX;

		/*
		 * Get pointers needed.
		 */
		var activities = ann.getActivities();
		var neurons = ann.getNeurons();

		/*
		 * Do not handle zero size ANNs.
		 */
		if (activities.dimension() == 0 || neurons.dimension() == 0) {
			return;
		}

		/*
		 * Check remote best fitness.
		 */
		remoteBestFitness = http.loadRemoteBestFitness(symbol, period, neurons, activities);

		/*
		 * Load Compare remote and local best fitness value.
		 */
		var population = de.getPopulation();
		if (population.getBestFitness() < remoteBestFitness) {
			var weights = population[population.getBestFitnessIndex()].getWeights();

			/*
			 * Do not handle zero size ANNs.
			 */
			if (weights.dimension() > 0) {
				http.saveSingleANN(symbol, period, population.getBestFitness(), neurons, weights, activities);
				http.saveTrainingSet(symbol, period, ts.getRates(), ts.getSize());
			}
		}

		/*
		 * Mark last time checked for server best fitness.
		 */
		lastBestFitnessReportTime = time(NULL);
	};

	this.finalize = function() {
		/*
		 * Report local best fitness value.
		 */
		reportLocalBestFitness();

		/*
		 * Estimate work done.
		 */
		counters.setValue("Training end time seconds", clock() / CLOCKS_PER_SEC);

		/*
		 * Report training results.
		 */
		if (DO_FINAL_REPORT == true) {
			console.log("================================================================================");
			console.log(counters);
			console.log("================================================================================");
			console.log(ann);
			console.log("================================================================================");
			console.log(de);
			console.log("================================================================================");
			console.log(ts);
			console.log("================================================================================");
		}
	};
}
