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

#ifndef MODEL_PARAMETERS_H
#define MODEL_PARAMETERS_H

#include "TimePeriod.h"

/**
 * Training and predicting model parameters.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 25 Oct 2011
 */
struct ModelParameters {

	/**
	 * Database identifier of ANN.
	 */
	int dbId;

	/**
	 * Currency pair symbol.
	 */
	char symbol[100];

	/**
	 * Time series period.
	 */
	TimePeriod period;

	/**
	 * Number of neurons in ANN.
	 */
	int neuronsAmount;

	/**
	 * Number of neurons used for input.
	 */
	int inputSize;

	/**
	 * Number of neurons used for output.
	 */
	int outputSize;

	/**
	 * Number of chromosomes in DE population.
	 */
	int populationSize;

	/**
	 * Number of past bars where history information will be used for the training.
	 */
	int learn;

	/**
	 * Number of future bars where prediction will be needed.
	 */
	int forecast;
};

#endif
