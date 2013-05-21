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
 * Single training example structure.
 *
 * @author Daniel Chutrov
 *
 * @email d.chutrov@gmail.com
 *
 * @date 25 Dec 2010
 */
function TrainingExample() {

	/**
	 * Size of arrays with input split digits.
	 */
	const NUMBER_OF_INPUT_SPLIT_DIGITS = 10;

	/**
	 * Size of arrays with output split digits.
	 */
	const NUMBER_OF_OUTPUT_SPLIT_DIGITS = 5;

	/**
	 * Rate time values.
	 */
	this.time = new Array(NUMBER_OF_INPUT_SPLIT_DIGITS);

	/**
	 * Expected values.
	 */
	this.expected = new Array(NUMBER_OF_OUTPUT_SPLIT_DIGITS);

	/**
	 * Predicted values.
	 */
	this.predicted = new Array(NUMBER_OF_OUTPUT_SPLIT_DIGITS);
}

//-->

