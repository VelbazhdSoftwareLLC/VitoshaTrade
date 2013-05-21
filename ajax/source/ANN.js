<!--
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
 * Full-connected Artificial Neural Network.
 *
 * @author Daniel Chutrov
 *
 * @email d.chutrov@gmail.com
 *
 * @date 16 Dec 2010
 */
function ANN(ts, neuronsAmount, bars, period) {

	/**
	 * Default random maximum value.
	 */
	const RAND_MAX = 32767;

	/**
	 * Minumum input amount of ANN neurons.
	 */
	const MIN_INPUT_NEURONS_AMOUNT = 10;

	/**
	 * Minumum regular amount of ANN neurons.
	 */
	const MIN_REGULAR_NEURONS_AMOUNT = 5;

	/**
	 * Minumum output amount of ANN neurons.
	 */
	const MIN_OUTPUT_NEURONS_AMOUNT = 5;

	/**
	 * Minumum amount of ANN neurons.
	 */
	const MIN_NEURONS_AMOUNT = MIN_INPUT_NEURONS_AMOUNT+MIN_REGULAR_NEURONS_AMOUNT+MIN_OUTPUT_NEURONS_AMOUNT;

	/**
	 * Learning rate of backpropagation.
	 */
	const LEARNING_RATE = 0.35;

	/**
	 * Minimum possible weight activity.
	 */
	const MIN_ACTIVITY = 0.0;

	/**
	 * Maximum possible weight activity.
	 */
	const MAX_ACTIVITY = 1.0;

	/**
	 * Bias neuron value.
	 */
	const BIAS_VALUE = 1.0;

	/**
	 * Neurons reset constant value.
	 */
	const NEURONS_RESET_VALUE = 0.5;

	/**
	 * Regular neuron flag.
	 */
	const REGULAR_NEURON = 0x00;

	/**
	 * Bias neuron flag.
	 */
	const BIAS_NEURON = 0x01;

	/**
	 * Input neuron flag.
	 */
	const INPUT_NEURON = 0x02;

	/**
	 * Output neuron flag.
	 */
	const OUTPUT_NEURON = 0x04;

	/**
	 * Number of ANN neurons.
	 */
	this.neuronsAmount = neuronsAmount;

	if (this.neuronsAmount < MIN_NEURONS_AMOUNT) {
		this.neuronsAmount = MIN_NEURONS_AMOUNT;
	}

	/**
	 * Number of ANN input neurons.
	 */
	this.inputNeuronsAmount = 0;

	/**
	 * Number of ANN output neurons.
	 */
	this.outputNeuronsAmount = 0;

	/**
	 * Neurons flags. More than one neuron can be bias, input and output in multi
	 * layer networks.
	 */
	this.neuronsFlags = new Array(this.neuronsAmount);

	/**
	 * Real nurons buffer array 1.
	 */
	this.neuronsBuffer1 = new Array(this.neuronsAmount);

	/**
	 * Real nurons buffer array 2.
	 */
	this.neuronsBuffer2 = new Array(this.neuronsAmount);

	/**
	 * Just a pinter to real array.
	 */
	this.neurons = this.neuronsBuffer1;

	/**
	 * Neurons error array for backpropagation.
	 */
	this.neuronsError = new Array(this.neuronsAmount);

	/**
	 * Real buffer for prediction time split digits.
	 */
	this.timeValue = new Array(this.neuronsAmount);

	/**
	 * Real buffer for merge output digits.
	 */
	this.outputValues = new Array(this.neuronsAmount);

	/**
	 * Activities 2D maxtrix.
	 */
	this.activities = new Array(this.neuronsAmount);
	for (var i=0; i<this.neuronsAmount; i++) {
		this.activities[i] = new Array(this.neuronsAmount);
	}

	/**
	 * Weights reference from DE.
	 */
	this.weights = null;

	/**
	 * Link to real training set object.
	 */
	this.ts = ts;

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
	 * It is not possible neurons amount to be negative number.
	 */
	if (this.neuronsAmount < MIN_NEURONS_AMOUNT) {
		this.neuronsAmount = MIN_NEURONS_AMOUNT;
	}

	/**
	 * Is bias neuron getter.
	 *
	 * @param index Index in neurons array.
	 *
	 * @return True if neuron is bias, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 21 Aug 2009
	 */
	this.isBias = function(index) {
		if ((this.neuronsFlags[index]&BIAS_NEURON) == BIAS_NEURON) {
			return( true );
		} else {
			return( false );
		}
	}

	/**
	 * Remove all flag from all neurons.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 22 Feb 2011
	 */
	this.clearFlags = function() {
		for (var i=0; i<this.neuronsAmount; i++) {
			this.neuronsFlags[i] = REGULAR_NEURON;
		}
	}

	/**
	 * Reset all neurons to constant value.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 18 Dec 2010
	 */
	this.resetNeurons = function() {
		for (var i=0; i<this.neuronsAmount; i++) {
			this.neurons[i] = NEURONS_RESET_VALUE;

			if (this.isBias(this.neuronsFlags[i]) == true) {
				this.neurons[i] = BIAS_VALUE;
			}
		}
	}

	/*
	 * Remove all bias neurons.
	 */
	this.clearFlags();

	/*
	 * Initialize neurons for first update.
	 */
	this.resetNeurons();

	/**
	 * Is input neuron getter.
	 *
	 * @param index Index in neurons array.
	 *
	 * @return True if neuron is input, false otherwise.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 27 Dec 2010
	 */
	this.isInput = function(index) {
		if (index < 0 || index >= this.neuronsAmount) {
			return( false );
		}

		if ((this.neuronsFlags[index]&INPUT_NEURON) == INPUT_NEURON) {
			return( true );
		} else {
			return( false );
		}
	}

	/**
	 * Is output neuron getter.
	 *
	 * @param index Index in neurons array.
	 *
	 * @return True if neuron is output, false otherwise.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 27 Dec 2010
	 */
	this.isOutput = function(index) {
		if (index < 0 || index >= this.neuronsAmount) {
			return( false );
		}

		if ((this.neuronsFlags[index]&OUTPUT_NEURON) == OUTPUT_NEURON) {
			return( true );
		} else {
			return( false );
		}
	}

//	/**
//	 * Pack neurons flags in both ends of the array.
//	 *
//	 * @author Daniel Chutrov
//	 *
//	 * @email d.chutrov@gmail.com
//	 *
//	 * @date 16 Dec 2010
//	 */
//	this.packInputOutput = function() {
//		this.inputNeuronsAmount = 0;
//		this.outputNeuronsAmount = 0;
//		for (var i=0; i<neuronsAmount; i++) {
//			if (isInput(i) == true) {
//				this.inputNeuronsAmount++;
//			}
//			if (isOutput(i) == true) {
//				this.outputNeuronsAmount++;
//			}
//		}
//
//		var done = false;
//		var swap = "0";
//
//		do {
//			done = true;
//
//			for (var i=0; i<neuronsAmount-1; i++) {
//				if (isInput(i)==false && isInput(i+1)==true) {
//					swap = neuronsFlags[ i];
//					neuronsFlags[ i] = neuronsFlags[ i+1 ];
//					neuronsFlags[ i+1 ] = swap;
//
//					done = false;
//				}
//			}
//			for (var i=1; i<neuronsAmount; i++) {
//				if (isOutput(i)==false && isOutput(i-1)==true) {
//					swap = neuronsFlags[ i];
//					neuronsFlags[ i ] = neuronsFlags[ i-1 ];
//					neuronsFlags[ i-1 ] = swap;
//
//					done = false;
//				}
//			}
//		} while (done == false);
//	}

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
		if (size < 0 || size > this.neuronsAmount) {
			return;
		}

		for (var i=0; i<size; i++) {
			this.neurons[i] = input[i];
		}
	}

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
		for (var i=0; i<this.neuronsAmount; i++) {
			if (this.isInput(i)==true || this.isBias(i)==true) {
				continue;
			}

			this.neuronsBuffer2[i] = 0.0;

			/*
			 * Activation function of neuron i.
			 */
			for (var j=0; j<this.neuronsAmount; j++) {
				this.neuronsBuffer2[i] += this.neuronsBuffer1[j] * this.weights[i][j] * this.activities[i][j];
			}

			/*
			 * Normalize activation level of neuron i with sidmoid function.
			 */
			this.neuronsBuffer2[i] = 1.0 / (1.0 + Math.exp(-this.neuronsBuffer2[i]));
		}

		/*
		 * Swap buffer to be ready for next network forward update.
		 */
		this.neurons = this.neuronsBuffer2;
		this.neuronsBuffer2 = this.neuronsBuffer1;
		this.neuronsBuffer1 = this.neurons;
	}

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
		if (size < 0 || size > this.neuronsAmount) {
			return;
		}

		for (var i=0; i<size; i++) {
			this.neurons[this.neuronsAmount-size+i] = output[ i ];
		}
	}

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
		if (size < 0 || size > this.neuronsAmount) {
			return( 0.0 );
		}

		this.storeOutput(predicted, size);

		/*
		 * Difference sum.
		 * http://www.speech.sri.com/people/anand/771/html/node37.html
		 */
		var result = 0.0;
		var subtraction = 0.0;
		for (var i=0; i<size; i++) {
			subtraction = expected[i] - predicted[i];
			result += subtraction * subtraction;
		}
		result /= 2.0;

		return( result );
	}

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
		 * Total artificial neural network error can not be calculated without
		 * training set.
		 */
		if (this.ts == null) {
			return( Math.floor(Math.random()*(RAND_MAX+1)) );
		}

		/*
		 * Reset network for new training.
		 */
		this.resetNeurons();

		/*
		 * Loop over training set examples.
		 */
		for (var i=0,size=this.ts.size; i<size; i++) {
//			/*
//			 * For each time load ANN input.
//			 */
//			this.loadInput(this.ts.examples[i].time, this.inputNeuronsAmount);

			/*
			 * Update ANN internal state.
			 */
			this.update();

//			/*
//			 * Calculate error.
//			 */
//			result += this.error(this.ts.examples[i].expected, this.ts.examples[i].predicted, this.outputNeuronsAmount);
		}

		/*
		 * Average error for comparisons with different amount of training examples.
		 */
		result /= this.ts.size;

		return( result );
	}

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
		 * Feed hidden layer with values.
		 */
		for (var i=0; i<this.neuronsAmount; i++) {
			/*
			 * Select neurons into the hidden layer.
			 */
			if (this.isInput(i)==true || this.isOutput(i)==true || this.isBias(i)==true) {
				continue;
			}

			this.neuronsBuffer2[i] = 0.0;

			/*
			 * Activation function of neuron i.
			 */
			for (var j=0; j<this.neuronsAmount; j++) {
				/*
				 * Select neurons into the input layer.
				 */
				if (this.isInput(j) == false) {
					continue;
				}

				this.neuronsBuffer2[i] += this.neuronsBuffer1[j] * this.weights[i][j] * this.activities[i][j];
			}

			/*
			 * Normalize activation level of neuron i with sidmoid function.
			 */
			this.neuronsBuffer2[i] = 1.0 / (1.0 + Math.exp(-this.neuronsBuffer2[i]));
		}

		/*
		 * Feed output layer with values.
		 */
		for (var i=0; i<this.neuronsAmount; i++) {
			/*
			 * Select neurons into the output layer.
			 */
			if (this.isOutput(i) == false) {
				continue;
			}

			this.neuronsBuffer2[i] = 0.0;

			/*
			 * Activation function of neuron i.
			 */
			for (var j=0; j<this.neuronsAmount; j++) {
				/*
				 * Select neurons into the hidden layer.
				 */
				if (this.isInput(i)==true || this.isOutput(i)==true || this.isBias(i)==true) {
					continue;
				}

				this.neuronsBuffer2[i] += this.neuronsBuffer1[j] * this.weights[i][j] * this.activities[i][j];
			}

			/*
			 * Normalize activation level of neuron i with sidmoid function.
			 */
			this.neuronsBuffer2[i] = 1.0 / (1.0 + Math.exp(-this.neuronsBuffer2[i]));
		}

		/*
		 * Swap buffer to be ready for next network forward update.
		 */
		this.neurons = this.neuronsBuffer2;
		this.neuronsBuffer2 = this.neuronsBuffer1;
		this.neuronsBuffer1 = this.neurons;
	}

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
		for (var i=0,k=0; i<this.neuronsAmount&&k<size; i++) {
			/*
			 * Select neurons into the output layer.
			 */
			if (this.isOutput(i) == false) {
				continue;
			}

			this.neuronsError[ i ] = (this.neurons[i] - this.expected[k]) * this.neurons[i] * (1.0 - this.neurons[i]);

			/*
			 * Increment expected values counter.
			 */
			k++;
		}

		/*
		 * Calculate error into hidden layer.
		 */
		for (var i=0; i<this.neuronsAmount; i++) {
			/*
			 * Select neurons into the hidden layer.
			 */
			if (this.isInput(i)==true || this.isOutput(i)==true) {
				continue;
			}

			this.neuronsError[ i ] = 0.0;


			for (var j=0; j<this.neuronsAmount; j++) {
				/*
				 * Select neurons into the output layer.
				 */
				if (this.isOutput(j) == false) {
					continue;
				}

				this.neuronsError[ i ] += this.neuronsError[j] * this.weights[i][j];
			}

			this.neuronsError[ i ] *= this.neurons[i] * (1.0 - this.neurons[i]);
		}

		/*
		 * Correct weights between output and hidden layer.
		 */
		for (var i=0; i<this.neuronsAmount; i++) {
			/*
			 * Select neurons into the output layer.
			 */
			if (this.isOutput(i) == false) {
				continue;
			}

			for (var j=0; j<this.neuronsAmount; j++) {
				/*
				 * Select neurons into the hidden layer.
				 */
				if (this.isInput(j)==true || this.isOutput(j)==true) {
					continue;
				}

				this.weights[i][j] += LEARNING_RATE * this.neuronsError[i] * this.neurons[j];
			}
		}

		/*
		 * Correct weights between hidden and output layer.
		 */
		for (var i=0; i<this.neuronsAmount; i++) {
			/*
			 * Select neurons into the hidden layer.
			 */
			if (this.isInput(i)==true || this.isOutput(i)==true || this.isBias(i)==true) {
				continue;
			}

			for (var j=0; j<this.neuronsAmount; j++) {
				/*
				 * Select neurons into the input layer.
				 */
				if (this.isInput(j) == false) {
					continue;
				}

				this.weights[i][j] += LEARNING_RATE * this.neuronsError[i] * this.neurons[j];
			}
		}
	}

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

		for (var i=0,size=this.ts.examples.length; i<size; i++) {
			/*
			 * Select random training example.
			 */
			index = Math.floor( Math.random()*size );

//			/*
//			 * For each time load ANN input.
//			 */
//			this.loadInput(this.ts.examples[index].time, this.inputNeuronsAmount);

			/*
			 * Feed forward ANN.
			 */
			this.feedforward();

//			/*
//			 * Back propacate ANN error.
//			 */
//			this.backpropagation(this.ts.examples[index].expected, this.outputNeuronsAmount);
		}
	}

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

		/*
		 * Minutes shoud be converted to seconds.
		 */
		var period = this.period * 60;
		var moment = 0;

//		/*
//		 * Loop over future time values.
//		 */
//		moment = this.ts.rates[this.ts.size-1].time + period;
		for (var i=0; i<this.bars; i++) {
			/*
			 * For each time load ANN input.
			 */
			this.ts.splitDigits(this.timeValues, this.inputNeuronsAmount, moment);
			this.loadInput(this.timeValues, this.inputNeuronsAmount);

			this.update();

			moment += period;
		}

		this.storeOutput(this.outputValues, this.outputNeuronsAmount);

		this.prediction = this.ts.mergeDigits(this.outputValues, this.outputNeuronsAmount) / this.ts.FLOATING_POINT_FACTOR;
	}
}
//-->
