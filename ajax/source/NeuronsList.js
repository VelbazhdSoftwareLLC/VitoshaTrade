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
document.write('<script type="text/javascript" src="' + 'Neuron.js' + '"></script>');

/**
 * List of neurons class.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 03 Aug 2011
 */
function NeuronsList(size) {
	/**
	 * Minumum input amount of ANN neurons.
	 */
	this.MIN_INPUT_NEURONS_AMOUNT = 1;

	/**
	 * Minumum regular amount of ANN neurons.
	 */
	this.MIN_REGULAR_NEURONS_AMOUNT = 1;

	/**
	 * Minumum output amount of ANN neurons.
	 */
	this.MIN_OUTPUT_NEURONS_AMOUNT = 1;

	/**
	 * Minumum amount of ANN neurons.
	 */
	this.MIN_NEURONS_AMOUNT = this.MIN_INPUT_NEURONS_AMOUNT + this.MIN_REGULAR_NEURONS_AMOUNT + this.MIN_OUTPUT_NEURONS_AMOUNT;

	/*
	 * It is not possible neurons amount to be negative number.
	 */
	if (size < this.MIN_NEURONS_AMOUNT) {
		size = this.MIN_NEURONS_AMOUNT;
	}

	/**
	 * Neurons list.
	 */
	this.list = new Array(size);
	for (var i = 0; i < list.length; i++) {
		list[i] = new Neuron();
	}

	/**
	 * Input neurons amount getter.
	 *
	 * @return Input neurons amount.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 27 Jul 2009
	 */
	this.getInputNeuronsAmount = function() {
		var inputNeuronsAmount = 0;

		for (var i = 0; i < list.length; i++) {
			if (list[i].isInput() == true) {
				inputNeuronsAmount++;
			}
		}

		return inputNeuronsAmount;
	};

	/**
	 * Output neurons amount getter.
	 *
	 * @return Output neurons amount.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 27 Jul 2009
	 */
	this.getOutputNeuronsAmount = function() {
		var outputNeuronsAmount = 0;

		for (var i = 0; i < list.length; i++) {
			if (list[i].isOutput() == true) {
				outputNeuronsAmount++;
			}
		}

		return outputNeuronsAmount;
	};

	/**
	 * Size of neurons list getter.
	 *
	 * @return Size of neurons list.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	this.dimension = function() {
		return list.length;
	};

	/**
	 * Clear all type flags.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 21 Aug 2009
	 */
	this.clearTypes = function() {
		for (var i = 0; i < list.length; i++) {
			list[i].setRegular(true);
		}
	};

	/**
	 * Reset all neurons values.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 21 Aug 2009
	 */
	this.reset = function() {
		for (var i = 0; i < list.length; i++) {
			list[i].reset();
		}
	};

	clearTypes();
}
