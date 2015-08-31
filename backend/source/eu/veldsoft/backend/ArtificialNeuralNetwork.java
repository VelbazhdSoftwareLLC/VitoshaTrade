package eu.veldsoft.backend;

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
 *                            Momchil Anachkov ( mZer0000@gmail.com )          *
 *                            Ralitza Koleva   ( rallly@abv.bg )               *
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
 * Data structure containing ANN for visual representation.
 * 
 * @author Momchil Anachkov
 * 
 * @email mZer0000@gmail.com
 * 
 * @date 24 Dec 2010
 */
public class ArtificialNeuralNetwork {

	/**
	 * Regular neuron flag.
	 */
	static final int REGULAR_NEURON = 0x00;

	/**
	 * Bias neuron flag.
	 */
	static final int BIAS_NEURON = 0x01;

	/**
	 * Input neuron flag.
	 */
	static final int INPUT_NEURON = 0x02;

	/**
	 * Output neuron flag.
	 */
	static final int OUTPUT_NEURON = 0x04;

	/**
	 * Representing the ID of the ANN.
	 */
	int id;

	/**
	 * Containing the currency pair.
	 */
	String symbol;

	/**
	 * Representing the time period for the bars.
	 */
	int period;

	/**
	 * Representing the number of neurons for the selected ANN.
	 */
	int numberOfNeurons;

	/**
	 * Containing the flags for the selected neuron.
	 */
	int flags[];

	/**
	 * Representing weights fitness value.
	 */
	double fitness;

	/**
	 * Containing the weight variables for the links.
	 */
	double weights[][];

	/**
	 * Containing the activity variables for the links.
	 */
	double activities[][];

	/**
	 * Neurons out signals.
	 */
	double signals[];

	/**
	 * Neurons out errors.
	 */
	double errors[];

	/**
	 * Containing the coordinates of the neurons for the selected ANN.
	 */
	int coordinates[][];

	/**
	 * Size of input layer.
	 * 
	 * @return The size of the input layer.
	 * 
	 * @author Todor Balabanov
	 * 
	 * @email todor.balabanov@gmail.com
	 * 
	 * @date 31 Aug 2015
	 */
	int numberOfInputNeurons() {
		int size = 0;

		for (int k = 0; k < flags.length; k++) {
			if (flags[k] != INPUT_NEURON) {
				continue;
			}

			size++;
		}

		return size;
	}

	/**
	 * Size of hidden layer.
	 * 
	 * @return The size of the hidden layer.
	 * 
	 * @author Todor Balabanov
	 * 
	 * @email todor.balabanov@gmail.com
	 * 
	 * @date 31 Aug 2015
	 */
	int numberOfHiddenNeurons() {
		int size = 0;

		for (int k = 0; k < flags.length; k++) {
			if (flags[k] != REGULAR_NEURON) {
				continue;
			}

			size++;
		}

		return size;
	}

	/**
	 * Size of output layer.
	 * 
	 * @return The size of the output layer.
	 * 
	 * @author Todor Balabanov
	 * 
	 * @email todor.balabanov@gmail.com
	 * 
	 * @date 31 Aug 2015
	 */
	int numberOfOutputNeurons() {
		int size = 0;

		for (int k = 0; k < flags.length; k++) {
			if (flags[k] != OUTPUT_NEURON) {
				continue;
			}

			size++;
		}

		return size;
	}
}
