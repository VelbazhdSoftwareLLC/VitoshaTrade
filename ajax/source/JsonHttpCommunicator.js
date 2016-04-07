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
	var requests = null;

	/*
	 * Get XTML HTTP request object.
	 */
	if (window.XMLHttpRequest) {
		requests = new XMLHttpRequest();
		/*
		 * Not IE.
		 */
	} else if (window.ActiveXObject) {
		requests = new ActiveXObject("Microsoft.XMLHTTP");
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

		if(requests.readyState != 4 && requests.readyState != 0) {
			return;
		}

		/*
		 * Prepare request parameters.
		 */
		var parameters = "";
		parameters += "annid=" + annId;
		parameters += "&";
		parameters += "&symbol" + symbol;
		parameters += "&";
		parameters += "period" + period;

		/*
		 * Send synchronous HTTP request.
		 */
		requests.open("POST", HOST+LIST_OF_ANNS_SCRIPT, false);
		requests.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
		requests.setRequestHeader("Content-length", parameters.length);
		requests.setRequestHeader("Connection", "close");

		requests.send(parameters);
		
		list = JSON.parse(requests.responseText);
		
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
	};
}
