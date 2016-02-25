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
/*
 * Include files.
 */
document.write('<script type="text/javascript" src="' + 'NeuronType.js' + '"></script>');

/**
 * Single neuron class.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 03 Aug 2011
 */
function Neuron() {
	/**
	 * Bias neuron value.
	 */
	this.BIAS_VALUE = 1.0;

	/**
	 * Neurons reset constant value.
	 */
	this.RESET_VALUE = 0.5;

	/**
	 * Minimal error constant value.
	 */
	this.MIN_ERROR = 0.0;

	/**
	 * Neuron type. More than one neuron can be bias, input and output in multi
	 * layer networks. Also each neuron can be in more than single type.
	 */
	this.type = (new NeuronType()).REGULAR;

	/**
	 * Neuron value.
	 */
	this.value = 0.0;

	/**
	 * Neuron error in back-propagation training.
	 */
	this.error = 0.0;
}
