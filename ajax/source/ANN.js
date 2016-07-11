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
document.write('<script type="text/javascript" src="' + 'cstdlib.js' + '"></script>');
document.write('<script type="text/javascript" src="' + 'NeuronsList.js' + '"></script>');
document.write('<script type="text/javascript" src="' + 'ActivitiesMatrix.js' + '"></script>');
document.write('<script type="text/javascript" src="' + 'WeightsMatrix.js' + '"></script>');

/**
 * Learning rate of backpropagation.
 */
const LEARNING_RATE = 0.35;

/**
 * Full-connected Artificial Neural Network.
 *
 * @author Daniel Chutrov
 *
 * @email d.chutrov@gmail.com
 *
 * @date 16 Dec 2010
 */
function ANN(counters, ts, neuronsAmount, learn, bars, period) {

	/**
	 * Number of ANN neurons.
	 */
	this.neuronsAmount = neuronsAmount;

	/**
	 * Just a pinter to real array.
	 */
	this.neurons = new NeuronsList(this.neuronsAmount);
	this.neuronsAmount = neurons.dimension();

	/*
	 * Make all neurons regular.
	 */
	neurons.clearTypes();

	/*
	 * Initialize neurons for first update.
	 */
	neurons.reset();

	/**
	 * Activities 2D maxtrix.
	 */
	this.activities = new ActivitiesMatrix(this.neuronsAmount);

	/**
	 * Weights reference from DE.
	 */
	this.weights = null;

	/**
	 * Counters reference is used for statistics collecton.
	 */
	this.counters = counters;

	/**
	 * Link to real training set object.
	 */
	this.ts = ts;

	/**
	 * Past bars interval.
	 */
	this.learn = learn;

	/**
	 * Prediction bars interval.
	 */
	this.bars = bars;

	/**
	 * Chart period value.
	 */
	this.period = period;

	/**
	 * Prediction of the best chromosome.
	 */
	this.prediction = 0.0;

	/*
	 * Estimate work done.
	 */
	if (counters != null) {
		counters.setValue("Number of neurons", this.neuronsAmount);
	}

	/**
	 * Neurons list getter.
	 *
	 * @return Neurons list reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 19 Aug 2009
	 */
	this.getNeurons = function() {
		return (neurons );
	};

	/**
	 * Neurons list setter.
	 *
	 * @param neurons Neurons list.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 31 Jul 2009
	 */
	this.setNeurons = function(neurons) {
		this.neurons = neurons;
	};

	/**
	 * Weights matrix getter.
	 *
	 * @return Weights matrix reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 19 Aug 2009
	 */
	this.getWeights = function() {
		return (weights );
	};


	/**
	 * Weights matrix setter.
	 *
	 * @param weights Weights matrix.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 26 Feb 2009
	 */
	this.setWeights = function(weights) {
		this.weights = weights;
	};

	/**
	 * Activities matrix getter.
	 *
	 * @return Activities matrix reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 19 Aug 2009
	 */
	this.getActivities = function() {
		return (activities );
	};

	/**
	 * Activities matrix setter.
	 *
	 * @param activities Activities matrix.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 26 Feb 2009
	 */
	this.setActivities = function(activities) {
		this.activities = activities;
	};

	/**
	 * Activity value getter.
	 *
	 * @param int x Column index.
	 *
	 * @param int y Row index.
	 *
	 * @return Activity value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 14 Mar 2009
	 */
	this.getActivity = function(x, y) {
		if (x < 0 || y < 0 || x >= activities.dimension() || y >= activities.dimension()) {
			throw ("ANN00015" );
			return (0.0 );
		}

		return ( activities(x, y) );
	};

	/**
	 * Activity value setter.
	 *
	 * @param int x Column index.
	 *
	 * @param int y Row index.
	 *
	 * @param value Activity value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 14 Mar 2009
	 */
	this.setActivity = function(x, y, value) {
		if (x < 0 || y < 0 || x >= activities.dimension() || y >= activities.dimension()) {
			throw ("ANN00016" );
			return;
		}

		activities(x, y) = value;
		activities.normalize();
	};


	/**
	 * Set all weights activities to minimum.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 16 Jul 2015
	 */
	this.setAllInactive = function() {
		//TODO Move this method in activities class.
		for (var j = 0; j < activities.dimension(); j++) {
			for (var i = 0; i < activities.dimension(); i++) {
				activities(i, j) = MIN_ACTIVITY;
			}
		}
	};

	/**
	 * Set all weights activities to maximum.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 14 Mar 2009
	 */
	this.setAllActive = function() {
		//TODO Move this method in activities class.
		for (var j = 0; j < activities.dimension(); j++) {
			for (var i = 0; i < activities.dimension(); i++) {
				activities(i, j) = MAX_ACTIVITY;
			}
		}
	};

	/**
	 * Training set pointer setter.
	 *
	 * @param ts Training set pointer.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 31 Jul 2009
	 */
	this.setTrainingSetPointer = function(ts) {
		this.ts = ts;
	};

	/**
	 * Prediction value getter.
	 *
	 * @return Prediction value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 29 Apr 2009
	 */
	this.getPrediction = function() {
		return (prediction );
	};

	/**
	 * Setup first neurons in internal array to be input.
	 *
	 * @param size Number of neurons to be used.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 27 Oct 2011
	 */
	this.setupInput = function(size) {
		for (var i = 0; i < size && i < neurons.dimension(); i++) {
			neurons[i].setInput(true);
		}
	};

	/**
	 * Setup last neurons in internal array to be output.
	 *
	 * @param size Number of neurons to be used.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 27 Oct 2011
	 */
	this.setupOutput = function(size) {
		for (var i = neurons.dimension() - size; i < neurons.dimension(); i++) {
			neurons[i].setOutput(true);
		}
	};

	/**
	 * Setup three layers topology.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 16 Jul 2015
	 */
	this.setupThreeLayers = function() {
		/*
		 * Clear all connections.
		 */
		setAllInactive();

		/*
		 * Set bias between input and hidden layers.
		 */
		var b1 = 0;
		for ( b1 = 0; b1 < neurons.dimension(); b1++) {
			if (neurons[b1].isRegular() == true) {
				neurons[b1].setBias(true);
				break;
			}
		}

		/*
		 * Set bias between hidden and output layers.
		 */
		var b2 = 0;
		for ( b2 = neurons.dimension() - 1; b2 > 0; b2--) {
			if (neurons[b2].isRegular() == true) {
				neurons[b2].setBias(true);
				break;
			}
		}

		/*
		 * Connect bias neuron.
		 */
		for (var j = 0; j < neurons.dimension(); j++) {
			if (neurons[j].isRegular() == false) {
				continue;
			}
			activities(j, b1) = activities.MAX_ACTIVITY;
		}

		/*
		 * Connect bias neuron.
		 */
		for (var j = 0; j < neurons.dimension(); j++) {
			if (neurons[j].isOutput() == false) {
				continue;
			}
			activities(j, b2) = activities.MAX_ACTIVITY;
		}

		/*
		 * Set connections between input and hidden layers.
		 */
		for (var i = 0; i < neurons.dimension(); i++) {
			if (neurons[i].isInput() == false) {
				continue;
			}

			for (var j = 0; j < neurons.dimension(); j++) {
				if (neurons[j].isRegular() == false) {
					continue;
				}
				activities(j, i) = activities.MAX_ACTIVITY;
			}
		}

		/*
		 * Set connections between hidden and output layers.
		 */
		for (var i = 0; i < neurons.dimension(); i++) {
			if (neurons[i].isRegular() == false) {
				continue;
			}

			for (var j = 0; j < neurons.dimension(); j++) {
				if (neurons[j].isOutput() == false) {
					continue;
				}
				activities(j, i) = activities.MAX_ACTIVITY;
			}
		}
	};

	/**
	 * Load input vector inside the network.
	 *
	 * @param input Input vector.
	 *
	 * @param size Vector size.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	this.loadInput = function(input, size) {
		if (input.dimension() != neurons.getInputNeuronsAmount()) {
			//TODO Find better exception handling.
			return;
		}

		for (var i = 0,
		    k = 0; i < neurons.dimension(); i++) {
			if (neurons[i].isInput() == false) {
				continue;
			}

			neurons[i].setValue(input[k]);
			k++;
		}
	};

	/**
	 * Forward pass of network state change. All neurons get new values.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	this.update = function() {
		/*
		 * Return if weights are not loaded.
		 */
		if (weights.dimension() == 0) {
			//TODO Find better exception handling.
			return;
		}

		next = new NeuronsList(neurons.dimension());
		for (var i = 0; i < neurons.dimension(); i++) {
			if (neurons[i].isInput() == true || neurons[i].isBias() == true) {
				continue;
			}

			/*
			 * Activation function of neuron i.
			 */
			var value = 0.0;
			for (var j = 0; j < neurons.dimension(); j++) {
				value += neurons[j].getValue() * weights.get(i, j) * activities.get(i, j);
			}

			/*
			 * Normalize activation level of neuron i with sigmoid function.
			 */
			value = 1.0 / (1.0 + exp(-value));

			next[i].setValue(value);
		}

		/*
		 * Swap buffer to be ready for next network forward update.
		 */
		neurons = next;
	};

	/**
	 * Store (retrun) output of the network into output array.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	this.storeOutput = function(output, size) {
		if (output.dimension() != neurons.getOutputNeuronsAmount()) {
			//TODO Find better exception handling.
			return;
		}

		for (var i = 0,
		    k = 0; i < neurons.dimension(); i++) {
			if (neurons[i].isOutput() == false) {
				continue;
			}

			output[k] = neurons[i].getValue();
			k++;
		}
	};

	/**
	 * Calculate network output error.
	 *
	 * @param expected Array with expected output values.
	 *
	 * @param predicted Array with predicted output values.
	 *
	 * @param size Size of expected values array.
	 *
	 * @return Euclidian distance between expected array and output array.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	this.error = function(expected, predicted, size) {
		if (expected.dimension() != predicted.dimension()) {
			//TODO Find better exception handling.
			return 0.0;
		}

		if (predicted.dimension() < 0 || predicted.dimension() > neurons.dimension()) {
			//TODO Find better exception handling.
			return 0.0;
		}

		storeOutput(predicted);

		/*
		 * Difference sum.
		 * http://www.speech.sri.com/people/anand/771/html/node37.html
		 */
		var result = 0.0;
		var subtraction = 0.0;
		for (var i = 0; i < predicted.dimension(); i++) {
			subtraction = expected[i] - predicted[i];
			result += subtraction * subtraction;
		}
		result /= 2.0;

		return result;
	};

	/**
	 * Calculate average net error for all training examples.
	 *
	 * @return Average net error for all trainign examples.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	this.totalError = function() {
		var result = 0.0;

		/*
		 * Estimate work done.
		 */
		if (counters != null) {
			counters.increment("Total error calculations");
		}

		/*
		 * Total artificial neural network error can not be calculated without
		 * training set.
		 */
		if (ts == null) {
			return ( Math.floor(Math.random() * (RAND_MAX + 1)) );
		}

		/*
		 * Reset network for new training.
		 */
		neurons.reset();

		/*
		 * Loop over training set examples.
		 */
		for (var i = 0,
		    size = ts.getSize(); i < size; i++) {
			/*
			 * For each time load ANN input.
			 */
			loadInput(ts.getSplittedInputted(i));

			/*
			 * Update ANN internal state.
			 */
			update();

			/*
			 * Calculate error.
			 */
			result += error(ts.getSplittedExpected(i), ts.getSplittedPredicted(i));

			/*
			 * Sleep for better performance.
			 */
			sleep();
		}

		/*
		 * Average error for comparisons with different amount of training examples.
		 */
		result /= ts.getSize();

		return (result );
	};

	/**
	 * Feed forward ANN.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	this.feedforward = function() {
		/*
		 * Return if weights are not loaded.
		 */
		if (weights.dimension() == 0) {
			//TODO Find better exception handling.
			return;
		}

		next = new NeuronsList(neurons);

		/*
		 * Feed hidden layer with values.
		 */
		for (var i = 0; i < neurons.dimension(); i++) {
			/*
			 * Select neurons into the hidden layer.
			 */
			if (neurons[i].isInput() == true || neurons[i].isOutput() == true || neurons[i].isBias() == true) {
				continue;
			}

			/*
			 * Activation function of neuron i.
			 */
			var value = 0.0;
			for (var j = 0; j < neurons.dimension(); j++) {
				/*
				 * Select neurons into the input layer.
				 */
				if (neurons[j].isInput() == false) {
					continue;
				}

				value += neurons[j].getValue() * weights.get(i, j) * activities.get(i, j);
			}

			/*
			 * Normalize activation level of neuron i with sidmoid function.
			 */
			value = 1.0 / (1.0 + exp(-value));

			next[i].setValue(value);
		}

		/*
		 * Feed output layer with values.
		 */
		for (var i = 0; i < neurons.dimension(); i++) {
			/*
			 * Select neurons into the output layer.
			 */
			if (neurons[i].isOutput() == false) {
				continue;
			}

			/*
			 * Activation function of neuron i.
			 */
			var value = 0.0;
			for (var j = 0; j < neurons.dimension(); j++) {
				/*
				 * Select neurons into the hidden layer.
				 */
				if (neurons[j].isInput() == true || neurons[j].isOutput() == true) {
					continue;
				}

				value += neurons[j].getValue() * weights.get(i, j) * activities.get(i, j);
			}

			/*
			 * Normalize activation level of neuron i with sidmoid function.
			 */
			value = 1.0 / (1.0 + exp(-value));

			next[i].setValue(value);
		}

		/*
		 * Swap buffer to be ready for next network forward update.
		 */
		neurons = next;
	};

	/**
	 * Back propagate ANN.
	 *
	 * @param expected Array with expected output values.
	 *
	 * @param size Size of expected values array.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	this.backpropagation = function(expected, size) {
		var weights = this.weights;

		/*
		 * Calculate error into output layer.
		 */
		for (var i = 0,
		    k = 0; i < neurons.dimension() && k < expected.dimension(); i++) {
			/*
			 * Select neurons into the output layer.
			 */
			if (neurons[i].isOutput() == false) {
				continue;
			}

			var error = (neurons[i].getValue() - expected[k]) * neurons[i].getValue() * (1.0 - neurons[i].getValue());
			neurons[i].setError(error);

			/*
			 * Increment expected values counter.
			 */
			k++;
		}

		/*
		 * Calculate error into hidden layer.
		 */
		for (var i = 0; i < neurons.dimension(); i++) {
			/*
			 * Select neurons into the hidden layer.
			 */
			if (neurons[i].isInput() == true || neurons[i].isOutput() == true) {
				continue;
			}

			var error = 0.0;
			for (var j = 0; j < neurons.dimension(); j++) {
				/*
				 * Select neurons into the output layer.
				 */
				if (neurons[j].isOutput() == false) {
					continue;
				}

				error += neurons[j].getError() * weights(i, j);
			}

			error *= neurons[i].getValue() * (1.0 - neurons[i].getValue());
			neurons[i].setError(error);
		}

		/*
		 * Correct weights between output and hidden layer.
		 */
		for (var i = 0; i < neurons.dimension(); i++) {
			/*
			 * Select neurons into the output layer.
			 */
			if (neurons[i].isOutput() == false) {
				continue;
			}

			var value = 0;
			for (var j = 0; j < neurons.dimension(); j++) {
				/*
				 * Select neurons into the hidden layer.
				 */
				if (neurons[j].isInput() == true || neurons[j].isOutput() == true) {
					continue;
				}

				value += LEARNING_RATE * neurons[i].getError() * neurons[j].getValue();
			}
			weights.set(i, j, value);
		}

		/*
		 * Correct weights between hidden and output layer.
		 */
		for (var i = 0; i < neurons.dimension(); i++) {
			/*
			 * Select neurons into the hidden layer.
			 */
			if (neurons[i].isInput() == true || neurons[i].isOutput() == true || neurons[i].isBias() == true) {
				continue;
			}

			var value = 0;
			for (var j = 0; j < neurons.dimension(); j++) {
				/*
				 * Select neurons into the input layer.
				 */
				if (neurons[j].isInput() == false) {
					continue;
				}

				value += LEARNING_RATE * neurons[i].getError() * neurons[j].getValue();
			}
			weights.set(i, j, value);
		}
	};

	/**
	 * Gradient training of ANN.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	this.gradient = function() {
		var index = 0;

		/*
		 * Gradient optimization can not be applied without training set.
		 */
		if (ts == NULL) {
			//TODO Find better exception handling.
			return;
		}

		for (var i = 0,
		    size = ts.getSize(); i < size; i++) {
			/*
			 * Select random training example.
			 * All recurrent connections are switched off and there is no need to
			 * have time order of examples feeding.
			 */
			index = rand() % size;

			/*
			 * For each time load ANN input.
			 */
			loadInput(ts.getSplittedInputted(index));

			/*
			 * Feed forward ANN.
			 */
			feedforward();

			/*
			 * Back propacate ANN error.
			 */
			backpropagation(ts.getSplittedExpected(index));
		}
	};

	/**
	 * Predict future value.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	this.predict = function() {

		/*
		 * Total artificial neural network error can not be calculated without
		 * training set.
		 */
		if (this.ts == null) {
			return;
		}

		loadInput(ts.getSplittedInputted(0));

		update();

		outputValues = new ANNOutput(neurons.getOutputNeuronsAmount());
		storeOutput(outputValues);

		//TODO Should have array of predicted future values.
		prediction = outputValues[0];
	};
}
