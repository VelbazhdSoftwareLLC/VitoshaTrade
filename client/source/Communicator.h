/*******************************************************************************
 *                                                                             *
 * VitoshaTrade is Distributed Artificial Neural Network trained by            *
 * Differential Evolution for prediction of Forex. Project development is in   *
 * Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   *
 * the capital of Bulgaria.                                                    *
 *                                                                             *
 * Copyright (C) 2008-2013 by Todor Balabanov  ( todor.balabanov@gmail.com )   *
 *                       Iliyan Zankinski   ( iliyan_mf@abv.bg )               *
 *                       Momchil Anachkov   ( mZer0000@gmail.com )             *
 *                       Daniel Chutrov     ( d.chutrov@gmail.com )            *
 *                       Nikola Simeonov    ( n.simeonow@gmail.com )           *
 *                       Galq Cirkalova     ( galq_cirkalova@abv.bg )          *
 *                       Ivan Grozev        ( ivan.iliev.grozev@gmail.com )    *
 *                       Elisaveta Hristova ( elisaveta.s.hristova@gmail.com ) *
 *                       Simona Karadachka  ( simona.karadachka@gmail.com )    *
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

#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

class DE;
class ANN;

#include "RateInfo.h"
#include "TimePeriod.h"
#include "ModelParameters.h"

/**
 * Communication class used for abstract data transfer.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 18 Jun 2013
 */
class Communicator {

public:

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
	 * @date 10 May 2013
	 */
	virtual void loadAnnList(std::vector<int> &list, int annId, char symbol[], TimePeriod period) = 0;

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
	 * @date 26 Aug 2013
	 */
	virtual void loadTrainerObjects(Counter &counters, ANN &ann, DE &de, char symbol[], TimePeriod period, const ModelParameters &parameters) = 0;

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
	 * @date 10 May 2013
	 */
	virtual void saveSingleANN(char *symbol, TimePeriod period, double fitness, NeuronsList &neurons, WeightsMatrix &weights, ActivitiesMatrix &activities) = 0;

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
	 * @date 01 Aug 2013
	 */
	virtual int loadAnnNeuronsAmount(int annId) = 0;

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
	 * @date 26 Aug 2013
	 */
	virtual void loadSingleANN(int annId, char *symbol, TimePeriod &period, double &fitness, NeuronsList &neurons, WeightsMatrix &weights, ActivitiesMatrix &activities) = 0;

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
	 * @date 23 Sep 2013
	 */
	virtual int loadTrainingSetSize(char *symbol, TimePeriod period) = 0;

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
	 * @date 22 Sep 2013
	 */
	virtual void saveTrainingSet(char symbol[], TimePeriod period, const std::vector<RateInfo> &rates, int size) = 0;

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
	 * @date 22 Sep 2013
	 */
	virtual void loadTrainingSet(char symbol[], TimePeriod period, std::vector<RateInfo> &rates, int size) = 0;

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
	 * @date 10 May 2013
	 */
	virtual double loadRemoteBestFitness(char *symbol, TimePeriod period, NeuronsList &neurons, ActivitiesMatrix &activities) = 0;

};

#endif
