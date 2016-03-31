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
 * Communication class used for HTTP data transfer between client module and
 * server side business logic.
 *
 * @author Daniel Chutrov
 *
 * @email d.chutrov@gmail.com
 *
 * @date 29 Dec 2010
 */
function HttpCommunicator() {

//	/**
//	 * Remote host URL address.
//	 */
//	const HOST = "vitoshatrade.tbsoft.eu";
//
//	/**
//	 * Remote host port.
//	 */
//	const PORT = 80;
//
//	/**
//	 * Remote script ANN list provider.
//	 */
//	const LIST_OF_ANNS_SCRIPT = "/logic/number_of_anns.php";
//
//	/**
//	 * Remote single ANN save script.
//	 */
//	const SAVE_SINGLE_ANN_SCRIPT = "/logic/save_ann.php";
//
//	/**
//	 * Remote ANN neurons amount load script.
//	 */
//	const LOAD_NEURONS_AMOUNT_SCRIPT = "/logic/load_neurons_amount.php";
//
//	/**
//	 * Remote single ANN load script.
//	 */
//	const LOAD_SINGLE_ANN_SCRIPT = "/logic/load_ann.php";
//
//	/**
//	 * Remote single ANN load script.
//	 */
//	const LOAD_BEST_FITNESS_SCRIPT = "/logic/load_best_fitness.php";
//
//	/**
//	 * Remote training set size script.
//	 */
//	const TRAINING_SET_SIZE_SCRIPT ="/logic/training_set_size.php";
//
//	/**
//	 * Remote training set save script.
//	 */
//	const SAVE_TRAINING_SET_SCRIPT = "/logic/save_training_set.php";
//
//	/**
//	 * Remote training set load script.
//	 */
//	const LOAD_TRAINING_SET_SCRIPT = "/logic/load_training_set.php";
//
//	/**
//	 *
//	 */
//	var http = null;
//
//	/*
//	 * Get XTML HTTP request object.
//	 */
//	if (window.XMLHttpRequest) {
//		requests = new XMLHttpRequest(); //Not IE
//	} else if(window.ActiveXObject) {
//		requests = new ActiveXObject("Microsoft.XMLHTTP"); //IE
//	} else {
//		alert("Your browser does not support the XmlHttpRequest object!");
//	}
//
//	/**
//	 * Load list with ANNs.
//	 *
//	 * @param list List of ANN ids on the server side.
//	 *
//	 * @param size Size of ANN ids list.
//	 *
//	 * @param annId Id of ANN to be used as selection parameter.
//	 *
//	 * @param symbol MetaTrader 4 chart currency pair symbol.
//	 *
//	 * @param period MetaTrader 4 chart time period.
//	 *
//	 * @author Daniel Chutrov
//	 *
//	 * @email d.chutrov@gmail.com
//	 *
//	 * @date 26 Dec 2010
//	 */
//	this.loadAnnList = function(list, size, annId, symbol, period) {
//		if(requests.readyState != 4 && requests.readyState != 0) {
//			return;
//		}
//
//		/*
//		 * Prepare request parameters.
//		 */
//		var parameters = "";
//		parameters += "annid=" + annId;
//		parameters += "&";
//		parameters += "&symbol" + symbol;
//		parameters += "&";
//		parameters += "period" + period;
//
//		/*
//		 * Send HTTP request.
//		 */
//		requests.open("POST", HOST+LIST_OF_ANNS_SCRIPT, true);
//		requests.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
//		requests.setRequestHeader("Content-length", params.length);
//		requests.setRequestHeader("Connection", "close");
//
//		/**
//		 *
//		 *
//		 * @author Daniel Chutrov
//		 *
//		 * @email d.chutrov@gmail.com
//		 *
//		 * @date 01 Feb 2010
//		 */
//		requests.onreadystatechange = function() {
//			if (requests.readyState != 4 || requests.status != 200) {
//				return;
//			}
//
//			var buffer = requests.responseText;
//			buffer = buffer.replace("\r\n", " ");
//			buffer = buffer.replace("\r", " ");
//			buffer = buffer.replace("\n", " ");
//			buffer = buffer.split(" ");
//
//			var k = 0;
//			var numberOfIds = buffer[k++];
//
//			/*
//			 * Parse list values and limit it to the size of output array.
//			 */
//			var i = 0;
//			for (i=0; i<numberOfIds&&i<size; i++) {
//				list[i] = buffer[k++];
//			}
//			size = i;
//		}
//
//		requests.send(parameters);
//	}
//
//	/**
//	 * Load ANN neurons amount from DB.
//	 *
//	 * @param annId Id of ANN to be used as selection parameter.
//	 *
//	 * @return Neurons amount value.
//	 *
//	 * @author Daniel Chutrov
//	 *
//	 * @email d.chutrov@gmail.com
//	 *
//	 * @date 26 Dec 2010
//	 */
//	this.loadAnnNeuronsAmount = function(annId) {
//		if(requests.readyState != 4 && requests.readyState != 0) {
//			return;
//		}
//
//		/*
//		 * Prepare request parameters.
//		 */
//		var parameters = "";
//		parameters += "annid=" + annId;
//
//		/*
//		 * Send HTTP request.
//		 */
//		requests.open("POST", HOST+LOAD_NEURONS_AMOUNT_SCRIPT, true);
//		requests.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
//		requests.setRequestHeader("Content-length", params.length);
//		requests.setRequestHeader("Connection", "close");
//
//		/**
//		 *
//		 *
//		 * @author Daniel Chutrov
//		 *
//		 * @email d.chutrov@gmail.com
//		 *
//		 * @date 02 Feb 2010
//		 */
//		var result = 0;
//		requests.onreadystatechange = function() {
//			if (requests.readyState != 4 || requests.status != 200) {
//				return;
//			}
//
//			var buffer = requests.responseText;
//			buffer = buffer.replace("\r\n", " ");
//			buffer = buffer.replace("\r", " ");
//			buffer = buffer.replace("\n", " ");
//			buffer = buffer.split(" ");
//
//			result = buffer[0];
//		}
//
//		requests.send(parameters);
//
//		return(result);
//	}

	/**
	 * Allocate memory and load ANN and DE objects.
	 *
	 * @param ann Not allocated artificial nerural network object pointer with
	 * value NULL.
	 *
	 * @param  de Not allocated differential evolution object pointer with
	 * value NULL.
	 *
	 * @param dbId Database identifier of specific record.
	 *
	 * @param symbol MetaTrader 4 chart currency pair symbol.
	 *
	 * @param period MetaTrader 4 chart time period.
	 *
	 * @param neuronsAmount Number of neurons to be used in artificial network
	 * creation.
	 *
	 * @param populationSize Population size to be used in differential
	 * evolution creation.
	 *
	 * @param bars Prediction bars interval.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 26 Dec 2010
	 */
	this.loadTrainerObjects = function(counters, ann, de, dbId, symbol, period, neuronsAmount, populationSize, bars) {
//		var size = populationSize;
//		var list = new Array(populationSize);
//
//		/*
//		 * Load list with available ANNs.
//		 */
//		var numberOfNeurons = loadAnnNeuronsAmount(dbId);
//		loadAnnList(list, size, dbId, symbol, period);
//		if (size>0 && numberOfNeurons>0) {
//			neuronsAmount = numberOfNeurons;
//		}
//
//		/*
//		 * Memory allocation.
//		 */
//		ann = new ANN(counters, neuronsAmount, bars, period);
//		de = new DE(counters, ann, populationSize, 90.0, 90.0);
//
//		/*
//		 * Load DE with random values. It is useful in new ANN and DE creation.
//		 */
//		de.initRandom();
//
//		/*
//		 * Load DB ANNs.
//		 */
//		var fitness = 0.0;
//		var weights = null;
//		var flags = ann.flags;
//		var activities = ann.activities;
//		if (size>0 && ann.neuronsAmount==neuronsAmount) {
//			for (var i=0; i<size; i++) {
//				weights = de.population[ i ];
//				//TODO Activities, symbol, period, number of neurons and flags can be loaded only once.
//				loadSingleANN(list[i], symbol, period, fitness, neuronsAmount, flags, weights, activities);
//				ann.packInputOutput();
//				de.fitness[i] = fitness;
//			}
//		} else {
//			/*
//			 * In a new ANN set input, output neurons and wights activities.
//			 */
//			for (var j=0,size=ann.neuronsAmount; j<size; j++) {
//				for (var i=0; i<size; i++) {
//					activities[i][j] = ANN.MAX_ACTIVITY;
//				}
//			}
//			ann.setInput(ANN.MIN_INPUT_NEURONS_AMOUNT);
//			ann.setOutput(ANN.MIN_OUTPUT_NEURONS_AMOUNT);
//		}
};

//	/**
//	 * Save single ANN record on the remote side server.
//	 *
//	 * @param symbol Currency pair symbol.
//	 *
//	 * @param period Currency chart period.
//	 *
//	 * @param fitness Weights set fitness value.
//	 *
//	 * @param numberOfNeurons Number of neurons used as topology.
//	 *
//	 * @param flags Nurons flags.
//	 *
//	 * @param weights Weights set.
//	 *
//	 * @param activities Weights activities.
//	 *
//	 * @author Daniel Chutrov
//	 *
//	 * @email d.chutrov@gmail.com
//	 *
//	 * @date 26 Dec 2010
//	 */
//	this.saveSingleANN = function(symbol, period, fitness, numberOfNeurons, flags, weights, activities) {
//		if(requests.readyState != 4 && requests.readyState != 0) {
//			return;
//		}
//
//		/*
//		 * Prepare request parameters.
//		 */
//		var parameters = "";
//		parameters += "symbol=" + symbol;
//		parameters += "&";
//		parameters += "period=" + period;
//		parameters += "&";
//		parameters += "fitness=" + fitness;
//		parameters += "&";
//		parameters += "number_of_neurons=" + numberOfNeurons;
//		for (var i=0; i<numberOfNeurons; i++) {
//			if (i > 0) {
//				parameters += " ";
//			}
//			parameters += flags[i];
//		}
//		for (var j=0; j<numberOfNeurons; j++) {
//			if (j > 0) {
//				parameters += "\n";
//			}
//			for (var i=0; i<numberOfNeurons; i++) {
//				if (i > 0) {
//					parameters += " ";
//				}
//				parameters += weights[i][j];
//			}
//		}
//		for (var j=0; j<numberOfNeurons; j++) {
//			if (j > 0) {
//				parameters += "\n";
//			}
//			for (var i=0; i<numberOfNeurons; i++) {
//				if (i > 0) {
//					parameters += " ";
//				}
//				parameters += activities[i][j];
//			}
//		}
//
//		/*
//		 * Send HTTP request.
//		 */
//		requests.open("POST", HOST+SAVE_SINGLE_ANN_SCRIPT, true);
//		requests.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
//		requests.setRequestHeader("Content-length", params.length);
//		requests.setRequestHeader("Connection", "close");
//
//		/**
//		 *
//		 *
//		 * @author Daniel Chutrov
//		 *
//		 * @email d.chutrov@gmail.com
//		 *
//		 * @date 02 Feb 2010
//		 */
//		requests.onreadystatechange = function() {
//			if (requests.readyState != 4 || requests.status != 200) {
//				return;
//			}
//
//			var buffer = requests.responseText;
//			buffer = buffer.replace("\r\n", " ");
//			buffer = buffer.replace("\r", " ");
//			buffer = buffer.replace("\n", " ");
//			buffer = buffer.split(" ");
//
//			//TODO Handling is not needed for this request.
//		}
//
//		requests.send(parameters);
//	}
//
//	/**
//	 * Load single ANN objec record from remote server side.
//	 *
//	 * @param annId Id of ANN to be used as selection parameter.
//	 *
//	 * @param symbol Currency pair symbol.
//	 *
//	 * @param period Currency chart period.
//	 *
//	 * @param fitness Weights set fitness value.
//	 *
//	 * @param numberOfNeurons Number of neurons used as topology. Neurons amount will be used only for new crated ANN.
//	 *
//	 * @param flags Nurons flags.
//	 *
//	 * @param weights Weights set.
//	 *
//	 * @param activities Weights activities.
//	 *
//	 * @author Daniel Chutrov
//	 *
//	 * @email d.chutrov@gmail.com
//	 *
//	 * @date 26 Dec 2010
//	 */
//	this.loadSingleANN(annId, symbol, period, fitness, numberOfNeurons, flags, weights, activities) {
//		if(requests.readyState != 4 && requests.readyState != 0) {
//			return;
//		}
//
//		/*
//		 * Prepare request parameters.
//		 */
//		var parameters = "";
//		parameters += "annid=" + annId;
//
//		/*
//		 * Send HTTP request.
//		 */
//		requests.open("POST", HOST+LOAD_SINGLE_ANN_SCRIPT, true);
//		requests.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
//		requests.setRequestHeader("Content-length", params.length);
//		requests.setRequestHeader("Connection", "close");
//
//		/**
//		 *
//		 *
//		 * @author Daniel Chutrov
//		 *
//		 * @email d.chutrov@gmail.com
//		 *
//		 * @date 02 Feb 2010
//		 */
//		requests.onreadystatechange = function() {
//			if (requests.readyState != 4 || requests.status != 200) {
//				return;
//			}
//
//			var buffer = requests.responseText;
//			buffer = buffer.replace("\r\n", " ");
//			buffer = buffer.replace("\r", " ");
//			buffer = buffer.replace("\n", " ");
//			buffer = buffer.split(" ");
//
//			var k = 0;
//			if(buffer[k++] == 0){
//				//TODO Report exception.
//				return;
//			}
//			symbol = buffer[k++];
//			period = buffer[k++];
//			fitness = buffer[k++];
//			numberOfNeurons = buffer[k++];
//			for (var i=0; i<numberOfNeurons; i++) {
//				flags[ i ] = buffer[k++];
//			}
//			for (var j=0; j<numberOfNeurons; j++) {
//				for (var i=0; i<numberOfNeurons; i++) {
//					weights[i][j] = buffer[k++];
//				}
//			}
//			for (var j=0; j<numberOfNeurons; j++) {
//				for (var i=0; i<numberOfNeurons; i++) {
//					activities[i][j] = buffer[k++];
//				}
//			}
//		}
//
//		requests.send(parameters);
//	}

	/**
	 * Load training set size from remote side server.
	 *
	 * @param symbol Currency pair symbol.
	 *
	 * @param period Currency chart period.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 26 Dec 2010
	 */
	this.loadTrainingSetSize = function(symbol, period) {
//		if(requests.readyState != 4 && requests.readyState != 0) {
//			return;
//		}
//
//		/*
//		 * Prepare request parameters.
//		 */
//		var parameters = "";
//		parameters += "symbol=" + symbol;
//		parameters += "&";
//		parameters += "period=" + period;
//
//		/*
//		 * Send HTTP request.
//		 */
//		requests.open("POST", HOST+TRAINING_SET_SIZE_SCRIPT, true);
//		requests.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
//		requests.setRequestHeader("Content-length", params.length);
//		requests.setRequestHeader("Connection", "close");
//
//		/**
//		 *
//		 *
//		 * @author Daniel Chutrov
//		 *
//		 * @email d.chutrov@gmail.com
//		 *
//		 * @date 02 Feb 2010
//		 */
		var result = null;
//		requests.onreadystatechange = function() {
//			if (requests.readyState != 4 || requests.status != 200) {
//				return;
//			}
//
//			var buffer = requests.responseText;
//			buffer = buffer.replace("\r\n", " ");
//			buffer = buffer.replace("\r", " ");
//			buffer = buffer.replace("\n", " ");
//			buffer = buffer.split(" ");
//
//			result = buffer[0];
//		}
//
//		requests.send(parameters);
//
		return(result);
};

//	/**
//	 * Save training set record on remote side server.
//	 *
//	 * @param symbol Currency pair symbol.
//	 *
//	 * @param period Currency chart period.
//	 *
//	 * @param rates Rates values.
//	 *
//	 * @param size Number of training set examples.
//	 *
//	 * @author Daniel Chutrov
//	 *
//	 * @email d.chutrov@gmail.com
//	 *
//	 * @date 26 Dec 2010
//	 */
//	this.saveTrainingSet(symbol, period, rates, size) {
//		if(requests.readyState != 4 && requests.readyState != 0) {
//			return;
//		}
//
//		/*
//		 * Prepare request parameters.
//		 */
//		var parameters = "";
//		parameters += "symbol=" + symbol;
//		parameters += "&";
//		parameters += "period=" + period;
//		parameters += "&";
//		parameters += "number_of_examples=" + size;
//		for (var i=0; i<size; i++) {
//			if (i > 0) {
//				parameters += " ";
//			}
//			parameters += rates[i].time;
//		}
//		for (var i=0; i<size; i++) {
//			if (i > 0) {
//				parameters += " ";
//			}
//			parameters += rates[i].open;
//		}
//		for (var i=0; i<size; i++) {
//			if (i > 0) {
//				parameters += " ";
//			}
//			parameters += rates[i].low;
//		}
//		for (var i=0; i<size; i++) {
//			if (i > 0) {
//				parameters += " ";
//			}
//			parameters += rates[i].high;
//		}
//		for (var i=0; i<size; i++) {
//			if (i > 0) {
//				parameters += " ";
//			}
//			parameters += rates[i].close;
//		}
//		for (var i=0; i<size; i++) {
//			if (i > 0) {
//				parameters += " ";
//			}
//			parameters += rates[i].volume;
//		}
//
//		/*
//		 * Send HTTP request.
//		 */
//		requests.open("POST", HOST+SAVE_TRAINING_SET_SCRIPT, true);
//		requests.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
//		requests.setRequestHeader("Content-length", params.length);
//		requests.setRequestHeader("Connection", "close");
//
//		/**
//		 *
//		 *
//		 * @author Daniel Chutrov
//		 *
//		 * @email d.chutrov@gmail.com
//		 *
//		 * @date 02 Feb 2010
//		 */
//		requests.onreadystatechange = function() {
//			if (requests.readyState != 4 || requests.status != 200) {
//				return;
//			}
//
//			var buffer = requests.responseText;
//			buffer = buffer.replace("\r\n", " ");
//			buffer = buffer.replace("\r", " ");
//			buffer = buffer.replace("\n", " ");
//			buffer = buffer.split(" ");
//
//			//TODO Handling is not needed for this request.
//		}
//
//		requests.send(parameters);
//	}

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
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 26 Dec 2010
	 */
	this.loadTrainingSet = function(symbol, period, rates, size) {
//		if(requests.readyState != 4 && requests.readyState != 0) {
//			return;
//		}
//
//		/*
//		 * Prepare request parameters.
//		 */
//		var parameters = "";
//		parameters += "symbol=" + symbol;
//		parameters += "&";
//		parameters += "period=" + period;
//
//		/*
//		 * Send HTTP request.
//		 */
//		requests.open("POST", HOST+LOAD_TRAINING_SET_SCRIPT, true);
//		requests.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
//		requests.setRequestHeader("Content-length", params.length);
//		requests.setRequestHeader("Connection", "close");
//
//		/**
//		 *
//		 *
//		 * @author Daniel Chutrov
//		 *
//		 * @email d.chutrov@gmail.com
//		 *
//		 * @date 02 Feb 2010
//		 */
//		requests.onreadystatechange = function() {
//			if (requests.readyState != 4 || requests.status != 200) {
//				return;
//			}
//
//			var buffer = requests.responseText;
//			buffer = buffer.replace("\r\n", " ");
//			buffer = buffer.replace("\r", " ");
//			buffer = buffer.replace("\n", " ");
//			buffer = buffer.split(" ");
//
//			var k = 0;
//			if(buffer[k++] == 0){
//				//TODO Report exception.
//				return;
//			}
//			if (buffer[k-1] < size) {
//				size = buffer[k-1];
//			}
//			for (var i=0; i<size; i++) {
//				rates[i].time = buffer[k++];
//			}
//			for (var i=0; i<size; i++) {
//				rates[i].open = buffer[k++];
//			}
//			for (var i=0; i<size; i++) {
//				rates[i].low = buffer[k++];
//			}
//			for (var i=0; i<size; i++) {
//				rates[i].high = buffer[k++];
//			}
//			for (var i=0; i<size; i++) {
//				rates[i].close = buffer[k++];
//			}
//			for (var i=0; i<size; i++) {
//				rates[i].volume = buffer[k++];
//			}
//		}
//
//		requests.send(parameters);
};

//	/**
//	 * Load remote server best known fitness for particular ANN kind.
//	 *
//	 * @param symbol Currency pair symbol.
//	 *
//	 * @param period MetaTrader 4 chart period.
//	 *
//	 * @param numberOfNeurons Number of neurons used as topology.
//	 *
//	 * @param flags Nurons flags.
//	 *
//	 * @param activities Weights activities.
//	 *
//	 * @return Best known server side fitness.
//	 *
//	 * @author Daniel Chutrov
//	 *
//	 * @email d.chutrov@gmail.com
//	 *
//	 * @date 26 Dec 2010
//	 */
//	this.loadRemoteBestFitness = function(symbol, period, numberOfNeurons, flags, activities) {
//		if(requests.readyState != 4 && requests.readyState != 0) {
//			return;
//		}
//
//		/*
//		 * Prepare request parameters.
//		 */
//		var parameters = "";
//		parameters += "symbol=" + symbol;
//		parameters += "&";
//		parameters += "period=" + period;
//		parameters += "&";
//		parameters += "number_of_neurons=" + numberOfNeurons;
//		for (var i=0; i<numberOfNeurons; i++) {
//			if (i > 0) {
//				parameters += " ";
//			}
//			parameters += flags[i];
//		}
//		for (var j=0; j<numberOfNeurons; j++) {
//			if (j > 0) {
//				parameters += "\n";
//			}
//			for (var i=0; i<numberOfNeurons; i++) {
//				if (i > 0) {
//					parameters += " ";
//				}
//				parameters += activities[i][j];
//			}
//		}
//
//		/*
//		 * Send HTTP request.
//		 */
//		requests.open("POST", HOST+LOAD_BEST_FITNESS_SCRIPT, true);
//		requests.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
//		requests.setRequestHeader("Content-length", params.length);
//		requests.setRequestHeader("Connection", "close");
//
//		/**
//		 *
//		 *
//		 * @author Daniel Chutrov
//		 *
//		 * @email d.chutrov@gmail.com
//		 *
//		 * @date 02 Feb 2010
//		 */
//		requests.onreadystatechange = function() {
//			if (requests.readyState != 4 || requests.status != 200) {
//				return;
//			}
//
//			var buffer = requests.responseText;
//			buffer = buffer.replace("\r\n", " ");
//			buffer = buffer.replace("\r", " ");
//			buffer = buffer.replace("\n", " ");
//			buffer = buffer.split(" ");
//
//			result = buffer[0];
//		}
//
//		requests.send(parameters);
//
//		return(result);
//	}
}

