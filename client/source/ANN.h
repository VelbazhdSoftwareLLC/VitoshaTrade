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

#ifndef ANN_H
#define ANN_H

#include <iostream>

class Counter;
class TrainingSet;

#include "NeuronsList.h"
#include "WeightsMatrix.h"
#include "TimePeriod.h"
#include "ActivitiesMatrix.h"
#include "ANNIO.h"

/**
 * Full-connected Artificial Neural Network.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 19 Feb 2009
 */
class ANN {

public:

	/**
	 * Learning rate of backpropagation.
	 */
	static const double LEARNING_RATE = 0.35;

private:

	/**
	 * Just a pinter to real array.
	 */
	NeuronsList neurons;

	/**
	 * Topology maxtrix.
	 */
	ActivitiesMatrix activities;

	/**
	 * Weights 2D matrix.
	 */
	WeightsMatrix weights;

	/**
	 * Link to counters object.
	 */
	Counter *counters;

	/**
	 * Link to real training set object.
	 */
	TrainingSet *ts;

	/**
	 * Prediction bars interval.
	 */
	int bars;

	/**
	 * Chart period value.
	 */
	TimePeriod period;

	/**
	 * Prediction of the best chromosome.
	 */
	double prediction;

private:

	/**
	 * Help function used by constructors to creat internal object structure.
	 *
	 * @param neuronsAmount Nubmer of neurons to be used.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 23 Apr 2009
	 */
	void create(int neuronsAmount);

public:

	/**
	 * Class constructor. Memory allocation and internal variables initialization.
	 * Constructor is used to create artificial neural network for using.
	 *
	 * @param counters Link to real counters object.
	 *
	 * @param neuronsAmount How many neurons network has including bias neuron.
	 *
	 * @param bars Prediction bars interval.
	 *
	 * @param period Prediction period.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 20 Oct 2011
	 */
	ANN();

	/**
	 * Class constructor. Memory allocation and internal variables initialization.
	 * Constructor is used to create artificial neural network for using.
	 *
	 * @param ann Instance to be copied.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 22 Oct 2011
	 */
	ANN(const ANN &ann);

	/**
	 * Class constructor. Memory allocation and internal variables initialization.
	 * Constructor is used to create artificial neural network for using.
	 *
	 * @param counters Link to real counters object.
	 *
	 * @param neuronsAmount How many neurons network has including bias neuron.
	 *
	 * @param bars Prediction bars interval.
	 *
	 * @param period Prediction period.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 26 Feb 2009
	 */
	ANN(Counter *counters, int neuronsAmount, int bars, TimePeriod period);

	/**
	 * Class constructor. Memory allocation and internal variables initialization.
	 * Constructor is used to create artificial neural network for training.
	 *
	 * @param counters Link to real counters object.
	 *
	 * @param ts Link to real training set.
	 *
	 * @param neuronsAmount How many neurons network has including bias neuron.
	 *
	 * @param bars Prediction bars interval.
	 *
	 * @param period Prediction period.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 22 Apr 2009
	 */
	ANN(Counter *counters, TrainingSet *ts, int neuronsAmount, int bars, TimePeriod period);

	/**
	 * Neurons list getter.
	 *
	 * @return Neurons list reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 19 Aug 2009
	 */
	NeuronsList& getNeurons();

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
	void setNeurons(NeuronsList &neurons);

	/**
	 * Weights matrix getter.
	 *
	 * @return Weights matrix reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 19 Aug 2009
	 */
	WeightsMatrix& getWeights();

	/**
	 * Weights matrix setter.
	 *
	 * @param weights Weights matrix.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 26 Feb 2009
	 */
	void setWeights(WeightsMatrix &weights);

	/**
	 * Activities matrix getter.
	 *
	 * @return Activities matrix reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 19 Aug 2009
	 */
	ActivitiesMatrix& getActivities();

	/**
	 * Activities matrix setter.
	 *
	 * @param activities Activities matrix.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 26 Feb 2009
	 */
	void setActivities(ActivitiesMatrix &activities);

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
	 * @email tdb@tbsoft.eu
	 *
	 * @date 14 Mar 2009
	 */
	double getActivity(int x, int y);

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
	 * @email tdb@tbsoft.eu
	 *
	 * @date 14 Mar 2009
	 */
	void setActivity(int x, int y, double value);

	/**
	 * Set all weights activities to maximum.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 14 Mar 2009
	 */
	void setAllActive();

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
	void setTrainingSetPointer(TrainingSet *ts);

	/**
	 * Prediction value getter.
	 *
	 * @return Prediction value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 29 Apr 2009
	 */
	double getPrediction() const;

	/**
	 * Setup first neurons in internal array to be input.
	 *
	 * @param size Number of neurons to be used.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 27 Oct 2011
	 */
	void setupInput(int size);

	/**
	 * Setup last neurons in internal array to be output.
	 *
	 * @param size Number of neurons to be used.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 27 Oct 2011
	 */
	void setupOutput(int size);

	/**
	 * Load input vector inside the network.
	 *
	 * @param input Input vector.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 26 Feb 2009
	 */
	void loadInput(ANNIO &input);

	/**
	 * Forward pass of network state change. All neurons get new values.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 26 Feb 2009
	 */
	void update();

	/**
	 * Store output of the network into output array.
	 *
	 * @param output Output vector.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 26 Feb 2009
	 */
	void storeOutput(ANNIO &output);

	/**
	 * Calculate network output error.
	 *
	 * @param expected Array with expected output values.
	 *
	 * @param predicted Array with predicted output values.
	 *
	 * @return Euclidian distance between expected array and output array.
	 *
	 * @author Rumyana Petkova
	 *
	 * @email r_u_m_i_e_p@abv.bg
	 *
	 * @date 15 Mar 2009
	 */
	double error(ANNIO &expected, ANNIO &predicted);

	/**
	 * Calculate average net error for all training examples.
	 *
	 * @return Average net error for all trainign examples.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 01 Jun 2009
	 */
	double totalError();

	/**
	 * Feed forward ANN.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 07 Sep 2009
	 */
	void feedforward();

	/**
	 * Back propagate ANN.
	 *
	 * @param expected Array with expected output values.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 07 Sep 2009
	 */
	void backpropagation(ANNIO &expected);

	/**
	 * Gradient training of ANN.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 07 Sep 2009
	 */
	void gradient();

	/**
	 * Predict future value.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 28 Jul 2009
	 */
	void predict();

	/**
	 * Class destructor. Memory release and variables deinitialization.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 26 Feb 2009
	 */
	virtual ~ANN();

	/**
	 * Assignment operator overloading.
	 *
	 * @param ann Right side ANN operand.
	 *
	 * @return ANN instance reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 22 Oct 2011
	 */
	virtual ANN& operator=(const ANN &ann);

	friend std::ostream& operator<<(std::ostream &out, ANN &ann);
};

/**
 * Output operator redefinition.
 *
 * @param out Output stream.
 *
 * @param ann ANN instance.
 *
 * @return Output stream.
 *
 * @author Iliyan Zankinski
 *
 * @email iliyan_mf@abv.bg
 *
 * @date 23 Aug 2009
 */
std::ostream& operator<<(std::ostream &out, ANN &ann);

#endif
