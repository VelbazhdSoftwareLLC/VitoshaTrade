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

#ifndef TRAINING_EXAMPLE_H
#define TRAINING_EXAMPLE_H

#include "ANNIO.h"

#pragma pack(push,1)

/**
 * Single training example structure.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 12 Sep 2009
 */
struct TrainingExample {

	/**
	 * Constructor without parameters.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 12 Aug 2011
	 */
	TrainingExample();

	/**
	 * Size of arrays with input split digits.
	 */
	static const int NUMBER_OF_INPUT_SPLIT_DIGITS = 10;

	/**
	 * Size of arrays with output split digits.
	 */
	static const int NUMBER_OF_OUTPUT_SPLIT_DIGITS = 5;

	/**
	 * Rate time values.
	 */
	//TODO Wrong spelling. It should be inputted.
	ANNIO inputted;

	/**
	 * Expected values.
	 */
	ANNIO expected;

	/**
	 * Predicted values.
	 */
	ANNIO predicted;
};

#pragma pack(pop)

#endif
