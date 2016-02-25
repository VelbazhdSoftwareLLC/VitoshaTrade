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

#ifndef NEURON_TYPE_H
#define NEURON_TYPE_H

/**
 * Neuron type constants.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 25 Feb 2016
 */
enum NeuronType {
	/**
	 * Regular neuron flag.
	 */
	REGULAR = 0x00,

	/**
	 * Bias neuron flag.
	 */
	BIAS = 0x01,

	/**
	 * Input neuron flag.
	 */
	INPUT = 0x02,

	/**
	 * Input and bias neuron flag.
	 */
	INPUT_BIAS = 0x03,

	/**
	 * Output neuron flag.
	 */
	OUTPUT = 0x04,

	/**
	 * Output and bias neuron flag.
	 */
	OUTPUT_BIAS = 0x05,

	/**
	 * Output and input neuron flag.
	 */
	OUTPUT_INPUT = 0x06,

	/**
	 * Output, input and bias neuron flag.
	 */
	OUTPUT_INPUT_BIAS = 0x07
};

#endif
