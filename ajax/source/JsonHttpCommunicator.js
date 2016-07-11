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

/**
 * Remote host URL address.
 */
const HOST = "localhost";

/**
 * Remote host port.
 */
const PORT = 80;

/**
 * Remote script ANN list provider.
 */
const LIST_OF_ANNS_SCRIPT = "/logic/json_number_of_anns.php";

/**
 * Remote single ANN save script.
 */
const SAVE_SINGLE_ANN_SCRIPT = "/logic/save_ann.php";

/**
 * Remote ANN neurons amount load script.
 */
const LOAD_NEURONS_AMOUNT_SCRIPT = "/logic/json_load_neurons_amount.php";

/**
 * Remote single ANN load script.
 */
const LOAD_SINGLE_ANN_SCRIPT = "/logic/json_load_ann.php";

/**
 * Remote single ANN load script.
 */
const LOAD_BEST_FITNESS_SCRIPT = "/logic/json_load_best_fitness.php";

/**
 * Remote training set size script.
 */
const TRAINING_SET_SIZE_SCRIPT = "/logic/json_training_set_size.php";

/**
 * Remote training set save script.
 */
const SAVE_TRAINING_SET_SCRIPT = "/logic/save_training_set.php";

/**
 * Remote training set load script.
 */
const LOAD_TRAINING_SET_SCRIPT = "/logic/json_load_training_set.php";

/**
 * Communication class used for HTTP data transfer between client module and
 * server side business logic.
 *
 * @author Daniel Chutrov
 *
 * @email d.chutrov@gmail.com
 *
 * @date 29 Dec 2010
 */
function JsonHttpCommunicator() {

	/**
	 * Communication object as private member.
	 */
	var request = null;

	/*
	 * Get XTML HTTP request object.
	 */
	if (window.XMLHttpRequest) {
		request = new XMLHttpRequest();
		/*
		 * Not IE.
		 */
	} else if (window.ActiveXObject) {
		request = new ActiveXObject("Microsoft.XMLHTTP");
		/*
		 * IE
		 */
	} else {
		alert("Your browser does not support the XmlHttpRequest object!");
	}

	/**
	 * Load list with ANNs.
	 *
	 * @param list List of ANN ids on the server side.
	 *
	 * @param annId Id of ANN to be used as selection parameter.
	 *
	 * @param symbol MetaTrader 4 chart currency pair symbol.
	 *
	 * @param period MetaTrader 4 chart time period.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 16 Sep 2013
	 */
	this.loadAnnList = function(list, annId, symbol, period) {
		list.splice(0, list.length);

		if (request.readyState != 4 && request.readyState != 0) {
			return;
		}

		/*
		 * Prepare request parameters.
		 */
		var parameters = "";
		parameters += "annid=" + annId;
		parameters += "&";
		parameters += "&symbol=" + symbol;
		parameters += "&";
		parameters += "period=" + period;

		/*
		 * Send synchronous HTTP request.
		 */
		request.open("POST", "http://" + HOST + LIST_OF_ANNS_SCRIPT, false);
		request.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

		request.send(parameters);
		var response = JSON.parse(request.responseText);

		for (var i = 0; i < response.identifiers.length; i++) {
			list[i] = response.identifiers[i];
		}

		return list;
	};

	/**
	 * Allocate memory and load ANN and DE objects.
	 *
	 * @param ann Not allocated artificial nerural network object pointer with
	 * value NULL.
	 *
	 * @param  de Not allocated differential evolution object pointer with
	 * value NULL.
	 *
	 * @param symbol MetaTrader 4 chart currency pair symbol.
	 *
	 * @param period MetaTrader 4 chart time period.
	 *
	 * @param parameters All other netwrok parameters.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 16 Sep 2013
	 */
	this.loadTrainerObjects = function(counters, ann, de, symbol, period, parameters) {
		var numberOfNeurons = loadAnnNeuronsAmount(parameters.dbId);

		var list = [];
		list = loadAnnList(list, parameters.dbId, symbol, period);

		if (list.length > 0 && numberOfNeurons > 0) {
			neuronsAmount = numberOfNeurons;

			ann = new ANN(counters, neuronsAmount, parameters.learn, parameters.forecast, period);
		} else if (list.length == 0) {
			neuronsAmount = parameters.neuronsAmount;

			/*
			 * It is good new network to have at least neurons for input and output.
			 */
			if (neuronsAmount < (parameters.inputSize + parameters.outputSize)) {
				neuronsAmount = parameters.inputSize + parameters.outputSize;
			}

			/*
			 * Create new network if no record presented in database.
			 * Input and output neurons should be specified on network creation.
			 */
			ann = new ANN(counters, neuronsAmount, parameters.learn, parameters.forecast, period);
			ann.setupInput(parameters.inputSize);
			ann.setupOutput(parameters.outputSize);
			ann.setupThreeLayers();
		}

		de = new DE(counters, ann, parameters.populationSize);

		/*
		 * Load DE with random values. It is useful in new ANN and DE creation.
		 * Internal size of chromosomes should be given before initialization.
		 */
		var population = de.getPopulation();
		for (var i = 0; i < population.dimension(); i++) {
			weights = new WeightsMatrix(ann.getNeurons().dimension());
			chromosome = new Chromosome(weights, RAND_MAX);
			population[i] = chromosome;
		}
		//TODO Find better way to initialize random population with proper size of weight matrices.
		population.initRandom();
		//TODO This setter call may be is not needed.
		de.setPopulation(population);

		/*
		 * Load DB ANNs.
		 */
		var fitness = RAND_MAX;
		var neurons = ann.getNeurons();
		var activities = ann.getActivities();
		if (list.size() > 0 && neurons.dimension() > 0 && neurons.dimension() == neuronsAmount) {
			var population = de.getPopulation();
			for (var i = 0; i < list.size(); i++) {
				weights = population[i].getWeights();
				//TODO Activities, symbol, period, number of neurons and flags can be loaded only once.
				var result = loadSingleANN(list[i], symbol, period, fitness, neurons, weights, activities);
				ann.symbol = result[0];
				ann.period = result[1];
				ann.setNeurons(result[3]);
				ann.setActivities(result[5]);

				population[i].setFitness(result[2]);
				population[i].setWeights(result[4]);
			}
			de.setPopulation(population);
		}

		return [ann, de, symbol, period];
	};

	/**
	 * Save single ANN record on the remote side server.
	 *
	 * @param symbol Currency pair symbol.
	 *
	 * @param period Currency chart period.
	 *
	 * @param fitness Weights set fitness value.
	 *
	 * @param numberOfNeurons Number of neurons used as topology.
	 *
	 * @param flags Nurons flags.
	 *
	 * @param weights Weights set.
	 *
	 * @param activities Weights activities.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 16 Sep 2013
	 */
	this.saveSingleANN = function(symbol, period, fitness, neurons, weights, activities) {
		if (request.readyState != 4 && request.readyState != 0) {
			return;
		}

		/*
		 * Prepare request parameters.
		 */
		var parameters = "";
		parameters += "&symbol=" + symbol;
		parameters += "&";
		parameters += "period=" + period;
		parameters += "&";
		parameters += "fitness=" + fitness;
		parameters += "&";
		parameters += "number_of_neurons=" + neurons.dimension();

		parameters += "&";
		parameters += "flags=";
		for (var i = 0; i < neurons.dimension(); i++) {
			if (i > 0) {
				parameters += " ";
			}
			parameters += neurons[i].getType();
		}

		parameters += "&";
		parameters += "weights=";
		for (var j = 0; j < neurons.dimension(); j++) {
			if (j > 0) {
				parameters += "\n";
			}
			for (var i = 0; i < neurons.dimension(); i++) {
				if (i > 0) {
					parameters += " ";
				}
				parameters += weights.get(i, j);
			}
		}

		parameters += "&";
		parameters += "activities=";
		for (var j = 0; j < neurons.dimension(); j++) {
			if (j > 0) {
				parameters += "\n";
			}
			for (var i = 0; i < neurons.dimension(); i++) {
				if (i > 0) {
					parameters += " ";
				}
				parameters += activities.get(i, j);
			}
		}

		/*
		 * Send synchronous HTTP request.
		 */
		request.open("POST", "http://" + HOST + SAVE_SINGLE_ANN_SCRIPT, false);
		request.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

		request.send(parameters);
	};

	/**
	 * Load ANN neurons amount from DB.
	 *
	 * @param annId Id of ANN to be used as selection parameter.
	 *
	 * @return Neurons amount value.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 16 Sep 2013
	 */
	this.loadAnnNeuronsAmount = function(annId) {
		if (request.readyState != 4 && request.readyState != 0) {
			return;
		}

		/*
		 * Prepare request parameters.
		 */
		var parameters = "";
		parameters += "annid=" + annId;

		/*
		 * Send synchronous HTTP request.
		 */
		request.open("POST", "http://" + HOST + LOAD_NEURONS_AMOUNT_SCRIPT, false);
		request.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

		request.send(parameters);
		var response = JSON.parse(request.responseText);

		return response.neuronsAmount;
	};

	/**
	 * Load single ANN objec record from remote server side.
	 *
	 * @param annId Id of ANN to be used as selection parameter.
	 *
	 * @param symbol Currency pair symbol.
	 *
	 * @param period Currency chart period.
	 *
	 * @param fitness Weights set fitness value.
	 *
	 * @param numberOfNeurons Number of neurons used as topology. Neurons amount will be used only for new crated ANN.
	 *
	 * @param flags Nurons flags.
	 *
	 * @param weights Weights set.
	 *
	 * @param activities Weights activities.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 16 Sep 2013
	 */
	this.loadSingleANN = function(annId, symbol, period, fitness, neurons, weights, activities) {
		if (request.readyState != 4 && request.readyState != 0) {
			return;
		}

		/*
		 * Prepare request parameters.
		 */
		var parameters = "";
		parameters += "annid=" + annId;

		/*
		 * Send synchronous HTTP request.
		 */
		request.open("POST", "http://" + HOST + LOAD_SINGLE_ANN_SCRIPT, false);
		request.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

		request.send(parameters);
		var response = JSON.parse(request.responseText);

		if (response.size == 1) {
			symbol = response.symbol;
			period = response.period;
			fitness = response.fitness;
			var size = response.flags.length;

			neurons = new NeuronsList(size);
			for (var i = 0; i < size; i++) {
				neurons.list[i].type = response.flags[i];
			}

			weights = new WeightsMatrix(size);
			for (var i = 0; i < size; i++) {
				for (var j = 0; j < size; j++) {
					weights.set(i, j, response.weights[i][j]);
				}
			}

			activities = new ActivitiesMatrix(size);
			for (var i = 0; i < size; i++) {
				for (var j = 0; j < size; j++) {
					activities.set(i, j, response.activities[i][j]);
				}
			}
		}

		return [symbol, period, fitness, neurons, weights, activities];
	};

	/**
	 * Load training set size from remote side server.
	 *
	 * @param symbol Currency pair symbol.
	 *
	 * @param period Currency chart period.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 16 Sep 2013
	 */
	this.loadTrainingSetSize = function(symbol, period) {
		if (request.readyState != 4 && request.readyState != 0) {
			return;
		}

		/*
		 * Prepare request parameters.
		 */
		var parameters = "";
		parameters += "&symbol=" + symbol;
		parameters += "&";
		parameters += "period=" + period;

		/*
		 * Send synchronous HTTP request.
		 */
		request.open("POST", "http://" + HOST + TRAINING_SET_SIZE_SCRIPT, false);
		request.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

		request.send(parameters);
		var response = JSON.parse(request.responseText);

		return response.numberOfExamples;
	};

	/**
	 * Save training set record on remote side server.
	 *
	 * @param symbol Currency pair symbol.
	 *
	 * @param period Currency chart period.
	 *
	 * @param rates Rates values.
	 *
	 * @param size Number of training set examples.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 16 Sep 2013
	 */
	this.saveTrainingSet = function(symbol, period, rates, size) {
		if (request.readyState != 4 && request.readyState != 0) {
			return;
		}

		/*
		 * Prepare request parameters.
		 */
		var parameters = "";
		parameters += "&symbol=" + symbol;
		parameters += "&";
		parameters += "period=" + period;
		parameters += "&";
		parameters += "number_of_examples=" + size;

		parameters += "&";
		parameters += "time=";
		for (var i = 0; i < size; i++) {
			if (i > 0) {
				parameters += " ";
			}
			parameters += rates[i].time;
		}

		parameters += "&";
		parameters += "open=";
		for (var i = 0; i < size; i++) {
			if (i > 0) {
				parameters += " ";
			}
			parameters += rates[i].open;
		}

		parameters += "&";
		parameters += "low=";
		for (var i = 0; i < size; i++) {
			if (i > 0) {
				parameters += " ";
			}
			parameters += rates[i].low;
		}

		parameters += "&";
		parameters += "high=";
		for (var i = 0; i < size; i++) {
			if (i > 0) {
				parameters += " ";
			}
			parameters += rates[i].high;
		}

		parameters += "&";
		parameters += "close=";
		for (var i = 0; i < size; i++) {
			if (i > 0) {
				parameters += " ";
			}
			parameters += rates[i].close;
		}

		parameters += "&";
		parameters += "volume=";
		for (var i = 0; i < size; i++) {
			if (i > 0) {
				parameters += " ";
			}
			parameters += rates[i].volume;
		}

		/*
		 * Send synchronous HTTP request.
		 */
		request.open("POST", "http://" + HOST + SAVE_TRAINING_SET_SCRIPT, false);
		request.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

		request.send(parameters);
	};

	/**
	 * Load training set record from remote side server.
	 *
	 * @param symbol Currency pair symbol.
	 *
	 * @param period Currency chart period.
	 *
	 * @param rates Rates values.
	 *
	 * @param size Number of training set examples.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 16 Sep 2013
	 */
	this.loadTrainingSet = function(symbol, period, rates, size) {
	};

	/**
	 * Load remote server best known fitness for particular ANN kind.
	 *
	 * @param symbol Currency pair symbol.
	 *
	 * @param period MetaTrader 4 chart period.
	 *
	 * @param numberOfNeurons Number of neurons used as topology.
	 *
	 * @param flags Nurons flags.
	 *
	 * @param activities Weights activities.
	 *
	 * @return Best known server side fitness.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 16 Sep 2013
	 */
	this.loadRemoteBestFitness = function(symbol, period, neurons, activities) {
		if (request.readyState != 4 && request.readyState != 0) {
			return;
		}

		/*
		 * Prepare request parameters.
		 */
		var parameters = "";
		parameters += "&symbol=" + symbol;
		parameters += "&";
		parameters += "period=" + period;
		parameters += "&";
		parameters += "number_of_neurons=" + neurons.dimension();

		parameters += "&";
		parameters += "flags=";
		for (var i = 0; i < neurons.dimension(); i++) {
			if (i > 0) {
				parameters += " ";
			}
			parameters += neurons[i].getType();
		}

		parameters += "&";
		parameters += "activities=";
		for (var j = 0; j < neurons.dimension(); j++) {
			if (j > 0) {
				parameters += "\n";
			}
			for (var i = 0; i < neurons.dimension(); i++) {
				if (i > 0) {
					parameters += " ";
				}
				parameters += activities.get(i, j);
			}
		}

		/*
		 * Send synchronous HTTP request.
		 */
		request.open("POST", "http://" + HOST + LOAD_BEST_FITNESS_SCRIPT, false);
		request.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

		request.send(parameters);
		var response = JSON.parse(request.responseText);

		return response.fitness;
	};
}
