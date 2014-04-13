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

#ifndef TRAINER_H
#define TRAINER_H

#include <vector>

struct ModelParameters;

#include "DE.h"
#include "ANN.h"
#include "Counter.h"
#include "RateInfo.h"
#include "TimePeriod.h"
#include "TrainingSet.h"
#include "JsonHttpCommunicator.h"

/**
 * Artificial neural network trainer.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 16 Apr 2009
 */
class Trainer {
public:

	/**
	 * Do report flag.
	 */
	static const bool DO_FINAL_REPORT = true;

	/**
	 * Report file name.
	 */
	static const char REPORT_FILE_NAME[];

	/**
	 * Number of seconds to request training set update.
	 */
	static const unsigned long TRAINING_SET_UPDATE_INTERVAL = 600;

	/**
	 * Number of seconds to report local best fitness.
	 */
	static const unsigned long BEST_FITNESS_REPORT_INTERVAL = 600;

private:

	/**
	 * MetaTrader 4 chart symbol.
	 */
	char symbol[ 10 ];

	/**
	 * MetaTrader 4 chart period.
	 */
	TimePeriod period;

	/**
	 * Statistic counters dynamic instance.
	 */
	Counter counters;

	/**
	 * Artificial neural network dynamic instance.
	 */
	ANN ann;

	/**
	 * Differential evolution dynamic instance.
	 */
	DE de;

	/**
	 * Training set dynamic instance.
	 */
	TrainingSet ts;

	/**
	 * HTTP communication dynamic instance.
	 */
	JsonHttpCommunicator http;

	/**
	 * Last best local fitness report UNIX time.
	 */
	unsigned long lastBestFitnessReportTime;

public:

	/**
	 * Constructing trainer by using database data or user defined parameters.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 12 Sep 2009
	 */
	Trainer();

	/**
	 * Setup trainer by using database data or user defined parameters.
	 *
	 * @param parameters Calculation model parameters.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 18 Jun 2013
	 */
	void setup(const ModelParameters &parameters);

	/**
	 * Update training set.
	 *
	 * @param rates Array with rates values.
	 *
	 * @param size Size of all parallel arrays.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 26 Jul 2009
	 */
	void updateTrainingSet(const std::vector<RateInfo> &rates, int size);

	/**
	 * Do training process.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 28 Jul 2009
	 */
	void train();

	/**
	 * Obtain predicted value.
	 *
	 * @return Predicted value.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 28 Jul 2009
	 */
	double predict();

	/**
	 * Report local best fitness.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 12 Sep 2009
	 */
	void reportLocalBestFitness();

	/**
	 * Trainer destructor.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 12 Sep 2009
	 */
	virtual ~Trainer();
};

#endif
