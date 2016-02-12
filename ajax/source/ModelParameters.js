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
 * Training and predicting model parameters.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 25 Oct 2011
 */
function ModelParameters() {
	/**
	 * Database identifier of ANN.
	 */
	this.dbId = 0;

	/**
	 * Currency pair symbol.
	 */
	this.symbol = "";

	/**
	 * Time series period.
	 */
	this.period = 0;

	/**
	 * Number of neurons in ANN.
	 */
	this.neuronsAmount = 0;

	/**
	 * Number of neurons used for input.
	 */
	this.inputSize = 0;

	/**
	 * Number of neurons used for output.
	 */
	this.outputSize = 0;

	/**
	 * Number of chromosomes in DE population.
	 */
	this.populationSize = 0;

	/**
	 * Number of past bars where history information will be used for the training.
	 */
	this.learn = 0;

	/**
	 * Number of future bars where prediction will be needed.
	 */
	this.forecast = 0;
}
