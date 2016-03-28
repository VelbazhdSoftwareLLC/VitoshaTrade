/*******************************************************************************
 *                                                                             *
 * VitoshaTrade is Distributed Artificial Neural Network trained by            *
 * Differential Evolution for prediction of Forex. Project development is in   *
 * Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   *
 * the capital of Bulgaria.                                                    *
 *                                                                             *
 * Copyright (C) 2008-2011 by Todor Balabanov  ( todor.balabanov@gmail.com )   *
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

#include <cmath>
#include <climits>
#include <cstdlib>
#include <iomanip>

using namespace std;

#include "ANN.h"
#include "ANNInput.h"
#include "ANNOutput.h"
#include "Counter.h"
#include "WeightsMatrix.h"
#include "TrainingSet.h"
#include "ActivitiesMatrix.h"

extern void sleep();

/*
 * Control running of the thread.
 */
extern bool isRunning;

const double ANN::LEARNING_RATE = 0.35;

void ANN::create(int neuronsAmount) {
	NeuronsList neurons(neuronsAmount);
	this->neurons = neurons;
	neuronsAmount = this->neurons.dimension();

	ActivitiesMatrix activities(neuronsAmount);
	this->activities = activities;

	/*
	 * Make all neurons regular.
	 */
	neurons.clearTypes();

	/*
	 * Initialize neurons for first update.
	 */
	neurons.reset();

	/*
	 * In the beginning there is no prediction.
	 */
	prediction = 0;

	/*
	 * Estimate work done.
	 */
	if (counters != NULL) {
		counters->setValue("Number of neurons", neuronsAmount);
	}
}

ANN::ANN() {
	this->counters = NULL;
	this->ts = NULL;
	this->learn = 0;
	this->bars = 0;
	this->period = NO;

	/*
	 * Allocate memory.
	 */
	create(0);
}

ANN::ANN(const ANN &ann) {
	this->counters = ann.counters;
	this->ts = ann.ts;
	this->learn = ann.learn;
	this->bars = ann.bars;
	this->period = ann.period;
	this->neurons = ann.neurons;
	this->activities = ann.activities;
	this->weights = ann.weights;
	this->prediction = ann.prediction;
}

ANN::ANN(Counter *counters, int neuronsAmount, int learn, int bars, TimePeriod period) {
	/*
	 * Check counters pointer for point valid object.
	 */
	if (counters == NULL) {
		throw( "ANN00144" );
		return;
	}

	/*
	 * In prediction mode there is no training set link.
	 */
	this->counters = counters;
	this->ts = NULL;
	this->learn = learn;
	this->bars = bars;
	this->period = period;

	/*
	 * Allocate memory.
	 */
	create(neuronsAmount);
}

ANN::ANN(Counter *counters, TrainingSet *ts, int neuronsAmount, int learn, int bars, TimePeriod period) {
	/*
	 * Check counters pointer for point valid object.
	 */
	if (counters == NULL) {
		throw( "ANN00146" );
		return;
	}

	/*
	 * Check training set pointer for point valid object.
	 */
	if (ts == NULL) {
		throw( "ANN00147" );
		return;
	}

	this->counters = counters;
	this->ts = ts;
	this->learn = learn;
	this->bars = bars;
	this->period = period;

	/*
	 * Allocate memory.
	 */
	create(neuronsAmount);
}

NeuronsList& ANN::getNeurons() {
	return( neurons );
}

void ANN::setNeurons(NeuronsList &neurons) {
	this->neurons = neurons;
}

WeightsMatrix& ANN::getWeights() {
	return( weights );
}

void ANN::setWeights(WeightsMatrix &weights) {
	this->weights = weights;
}

ActivitiesMatrix& ANN::getActivities() {
	return( activities );
}

void ANN::setActivities(ActivitiesMatrix &activities) {
	this->activities = activities;
}

double ANN::getActivity(int x, int y) {
	if (x < 0 || y<0 || x >= activities.dimension() || y >= activities.dimension()) {
		throw( "ANN00015" );
		return( 0.0 );
	}

	return( activities(x,y) );
}

void ANN::setActivity(int x, int y, double value) {
	if (x < 0 || y<0 || x >= activities.dimension() || y >= activities.dimension()) {
		throw( "ANN00016" );
		return;
	}

	activities(x,y) = value;
	activities.normalize();
}

void ANN::setAllInactive() {
	//TODO Move this method in activities class.
	for (int j=0; j<activities.dimension(); j++) {
		for (int i=0; i<activities.dimension(); i++) {
			activities(i,j) = ActivitiesMatrix::MIN_ACTIVITY;
		}
	}
}

void ANN::setAllActive() {
	//TODO Move this method in activities class.
	for (int j=0; j<activities.dimension(); j++) {
		for (int i=0; i<activities.dimension(); i++) {
			activities(i,j) = ActivitiesMatrix::MAX_ACTIVITY;
		}
	}
}

void ANN::setTrainingSetPointer(TrainingSet *ts) {
	this->ts = ts;
}

double ANN::getPrediction() const {
	return( prediction );
}

void ANN::setupInput(int size) {
	for(int i=0; i<size&&i<neurons.dimension(); i++) {
		neurons[i].setInput( true );
	}
}

void ANN::setupOutput(int size) {
	for(int i=neurons.dimension()-size; i<neurons.dimension(); i++) {
		neurons[i].setOutput( true );
	}
}

void ANN::setupThreeLayers() {
	/*
	 * Clear all connections.
	 */
	setAllInactive();

	/*
	 * Set bias between input and hidden layers.
	 */
	int b1 = 0;
	for(b1=0; b1<neurons.dimension(); b1++) {
		if(neurons[b1].isRegular() == true) {
			neurons[b1].setBias( true );
			break;
		}
	}

	/*
	 * Set bias between hidden and output layers.
	 */
	int b2 = 0;
	for(b2=neurons.dimension()-1; b2>0; b2--) {
		if(neurons[b2].isRegular() == true) {
			neurons[b2].setBias( true );
			break;
		}
	}

	/*
	 * Connect bias neuron.
	 */
	for (int j=0; j<neurons.dimension(); j++) {
		if (neurons[j].isRegular() == false) {
			continue;
		}
		activities(j,b1) = activities.MAX_ACTIVITY;
	}

	/*
	 * Connect bias neuron.
	 */
	for (int j=0; j<neurons.dimension(); j++) {
		if (neurons[j].isOutput() == false) {
			continue;
		}
		activities(j,b2) = activities.MAX_ACTIVITY;
	}

	/*
	 * Set connections between input and hidden layers.
	 */
	for (int i=0; i<neurons.dimension(); i++) {
		if (neurons[i].isInput() == false) {
			continue;
		}

		for (int j=0; j<neurons.dimension(); j++) {
			if (neurons[j].isRegular() == false) {
				continue;
			}
			activities(j,i) = activities.MAX_ACTIVITY;
		}
	}

	/*
	 * Set connections between hidden and output layers.
	 */
	for (int i=0; i<neurons.dimension(); i++) {
		if (neurons[i].isRegular() == false) {
			continue;
		}

		for (int j=0; j<neurons.dimension(); j++) {
			if (neurons[j].isOutput() == false) {
				continue;
			}
			activities(j,i) = activities.MAX_ACTIVITY;
		}
	}
}

void ANN::loadInput(ANNIO &input) {
	if (input.dimension() != neurons.getInputNeuronsAmount()) {
		throw( "ANN00022" );
		return;
	}

	for (int i=0, k=0; i<neurons.dimension(); i++) {
		if (neurons[i].isInput() == false) {
			continue;
		}

		neurons[i].setValue( input[k] );
		k++;
	}
}

void ANN::update() {
	/*
	 * Return if weights are not loaded.
	 */
	if (weights.dimension() == 0) {
		return;
	}

	NeuronsList next(neurons);
	for (int i=0; i<neurons.dimension(); i++) {
		if (neurons[i].isInput()==true || neurons[i].isBias()==true) {
			continue;
		}

		/*
		 * Activation function of neuron i.
		 */
		double value = 0.0;
		for (int j=0; j<neurons.dimension(); j++) {
			value += neurons[j].getValue() * weights(i,j) * activities(i,j);
		}

		/*
		 * Normalize activation level of neuron i with sigmoid function.
		 */
		value = 1.0 / (1.0 + exp(-value));

		next[i].setValue( value );
	}

	/*
	 * Swap buffer to be ready for next network forward update.
	 */
	neurons = next;
}

void ANN::storeOutput(ANNIO &output) {
	if (output.dimension() != neurons.getOutputNeuronsAmount()) {
		throw( "ANN00023" );
		return;
	}

	for (int i=0, k=0; i<neurons.dimension(); i++) {
		if (neurons[i].isOutput() == false) {
			continue;
		}

		output[k] = neurons[i].getValue();
		k++;
	}
}

double ANN::error(ANNIO &expected, ANNIO &predicted) {
	if (expected.dimension() != predicted.dimension()) {
		throw( "ANN00170" );
		return( 0.0 );
	}

	if (predicted.dimension() < 0 || predicted.dimension() > neurons.dimension()) {
		throw( "ANN00024" );
		return( 0.0 );
	}

	storeOutput(predicted);

	/*
	 * Difference sum.
	 * http://www.speech.sri.com/people/anand/771/html/node37.html
	 */
	double result = 0.0;
	static double subtraction = 0.0;
	for (int i=0; i<predicted.dimension(); i++) {
		subtraction = expected[i] - predicted[i];
		result += subtraction * subtraction;
	}
	result /= (double)2.0;

	return( result );
}

double ANN::totalError() {
	double result = 0.0;

	/*
	 * Estimate work done.
	 */
	if (counters != NULL) {
		counters->increment( "Total error calculations" );
	}

	/*
	 * Total artificial neural network error can not be calculated without
	 * training set.
	 */
	if (ts == NULL) {
		return( (double)RAND_MAX );
	}

	/*
	 * Reset network for new training.
	 */
	neurons.reset();

	/*
	 * Loop over training set examples.
	 */
	for (int i=0,size=ts->getSize(); i<size&&isRunning==true; i++) {putted
		/*
		 * For each time load ANN input.
		 */
		loadInput(ts->getSplittedInputted(i));

		/*
		 * Update ANN internal state.
		 */
		update();

		/*
		 * Calculate error.
		 */
		result += error(ts->getSplittedExpected(i), ts->getSplittedPredicted(i));

		/*
		 * Sleep for better performance.
		 */
		sleep();
	}

	/*
	 * Average error for comparisons with different amount of training examples.
	 */
	result /= ts->getSize();

	return( result );
}

void ANN::feedforward() {
	/*
	 * Return if weights are not loaded.
	 */
	if (weights.dimension() == 0) {
		return;
	}

	NeuronsList next(neurons);

	/*
	 * Feed hidden layer with values.
	 */
	for (int i=0; i<neurons.dimension(); i++) {
		/*
		 * Select neurons into the hidden layer.
		 */
		if (neurons[i].isInput()==true || neurons[i].isOutput()==true || neurons[i].isBias()==true) {
			continue;
		}

		/*
		 * Activation function of neuron i.
		 */
		double value = 0.0;
		for (int j=0; j<neurons.dimension(); j++) {
			/*
			 * Select neurons into the input layer.
			 */
			if (neurons[j].isInput() == false) {
				continue;
			}

			value += neurons[j].getValue() * weights(i,j) * activities(i,j);
		}

		/*
		 * Normalize activation level of neuron i with sidmoid function.
		 */
		value = 1.0 / (1.0 + exp(-value));

		next[i].setValue( value );
	}

	/*
	 * Feed output layer with values.
	 */
	for (int i=0; i<neurons.dimension(); i++) {
		/*
		 * Select neurons into the output layer.
		 */
		if (neurons[i].isOutput() == false) {
			continue;
		}

		/*
		 * Activation function of neuron i.
		 */
		double value = 0.0;
		for (int j=0; j<neurons.dimension(); j++) {
			/*
			 * Select neurons into the hidden layer.
			 */
			if (neurons[j].isInput()==true || neurons[j].isOutput()==true) {
				continue;
			}

			value += neurons[j].getValue() * weights(i,j) * activities(i,j);
		}

		/*
		 * Normalize activation level of neuron i with sidmoid function.
		 */
		value = 1.0 / (1.0 + exp(-value));

		next[i].setValue( value );
	}

	/*
	 * Swap buffer to be ready for next network forward update.
	 */
	neurons = next;
}

void ANN::backpropagation(ANNIO &expected) {
	WeightsMatrix weights = this->weights;

	/*
	 * Calculate error into output layer.
	 */
	for (int i=0,k=0; i<neurons.dimension()&&k<expected.dimension(); i++) {
		/*
		 * Select neurons into the output layer.
		 */
		if (neurons[i].isOutput() == false) {
			continue;
		}

		double error = (neurons[i].getValue() - expected[k]) * neurons[i].getValue() * (1.0 - neurons[i].getValue());
		neurons[i].setError( error );

		/*
		 * Increment expected values counter.
		 */
		k++;
	}

	/*
	 * Calculate error into hidden layer.
	 */
	for (int i=0; i<neurons.dimension(); i++) {
		/*
		 * Select neurons into the hidden layer.
		 */
		if (neurons[i].isInput()==true || neurons[i].isOutput()==true) {
			continue;
		}

		double error = 0.0;


		for (int j=0; j<neurons.dimension(); j++) {
			/*
			 * Select neurons into the output layer.
			 */
			if (neurons[j].isOutput() == false) {
				continue;
			}

			error += neurons[j].getError() * weights(i,j);
		}

		error *= neurons[i].getValue() * (1.0 - neurons[i].getValue());
		neurons[i].setError( error );
	}

	/*
	 * Correct weights between output and hidden layer.
	 */
	for (int i=0; i<neurons.dimension(); i++) {
		/*
		 * Select neurons into the output layer.
		 */
		if (neurons[i].isOutput() == false) {
			continue;
		}

		for (int j=0; j<neurons.dimension(); j++) {
			/*
			 * Select neurons into the hidden layer.
			 */
			if (neurons[j].isInput()==true || neurons[j].isOutput()==true) {
				continue;
			}

			weights(i,j) += LEARNING_RATE * neurons[i].getError() * neurons[j].getValue();
		}
	}

	/*
	 * Correct weights between hidden and output layer.
	 */
	for (int i=0; i<neurons.dimension(); i++) {
		/*
		 * Select neurons into the hidden layer.
		 */
		if (neurons[i].isInput()==true || neurons[i].isOutput()==true || neurons[i].isBias()==true) {
			continue;
		}

		for (int j=0; j<neurons.dimension(); j++) {
			/*
			 * Select neurons into the input layer.
			 */
			if (neurons[j].isInput() == false) {
				continue;
			}

			weights(i,j) += LEARNING_RATE * neurons[i].getError() * neurons[j].getValue();
		}
	}
}

void ANN::gradient() {
	int index = 0;

	/*
	 * Gradient optimization can not be applied without training set.
	 */
	if (ts == NULL) {
		return;
	}

	for (int i=0,size=ts->getSize(); i<size&&isRunning==true; i++) {
		/*
		 * Select random training example.
		 * All recurrent connections are switched off and there is no need to
		 * have time order of examples feeding.
		 */
		index = rand() % size;

		/*
		 * For each time load ANN input.
		 */
		loadInput(ts->getSplittedInputted(index));

		/*
		 * Feed forward ANN.
		 */
		feedforward();

		/*
		 * Back propacate ANN error.
		 */
		backpropagation(ts->getSplittedExpected(index));

		/*
		 * Sleep for better performance.
		 */
		sleep();
	}
}

void ANN::predict() {
	/*
	 * Total artificial neural network error can not be calculated without
	 * training set.
	 */
	if (ts == NULL) {
		return;
	}

    loadInput(ts->getSplittedInputted(0));

	update();

	ANNOutput outputValues( neurons.getOutputNeuronsAmount() );
	storeOutput(outputValues);

	//TODO Should have array of predicted future values.
	prediction = outputValues[0];
}

ANN::~ANN() {
	ts = NULL;
	counters = NULL;
}

ANN& ANN::operator=(const ANN &ann) {
	this->counters = ann.counters;
	this->ts = ann.ts;
	this->learn = ann.learn;
	this->bars = ann.bars;
	this->period = ann.period;
	this->neurons = ann.neurons;
	this->activities = ann.activities;
	this->weights = ann.weights;
	this->prediction = ann.prediction;

	return( *this );
}

ostream& operator<<(ostream &out, ANN &ann) {
	out << fixed;

	out << ann.neurons;
	out << endl;

	out << ann.activities;
	out << endl;

	out << ann.weights;

	return( out );
}
