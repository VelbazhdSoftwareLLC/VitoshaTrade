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

#ifndef NEURON_LIST_H
#define NEURON_LIST_H

#include <vector>
#include <iostream>

#include "Neuron.h"

/**
 * List of neurons class.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 03 Aug 2011
 */
class NeuronsList {

public:

	/**
	 * Minumum input amount of ANN neurons.
	 */
	static const int MIN_INPUT_NEURONS_AMOUNT = 10;

	/**
	 * Minumum regular amount of ANN neurons.
	 */
	static const int MIN_REGULAR_NEURONS_AMOUNT = 5;

	/**
	 * Minumum output amount of ANN neurons.
	 */
	static const int MIN_OUTPUT_NEURONS_AMOUNT = 5;

	/**
	 * Minumum amount of ANN neurons.
	 */
	static const int MIN_NEURONS_AMOUNT = MIN_INPUT_NEURONS_AMOUNT+MIN_REGULAR_NEURONS_AMOUNT+MIN_OUTPUT_NEURONS_AMOUNT;

private:

	/**
	 * Neurons list.
	 */
	std::vector<Neuron> list;

public:

	/**
	 * Constructor without parameters.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 03 Aug 2011
	 */
	NeuronsList();

	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @param size Size of the neurons list.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 03 Aug 2011
	 */
	NeuronsList(int size);

	/**
	 * Copy constructor.
	 *
	 * @param list Instance to be copied.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 03 Aug 2011
	 */
	NeuronsList(const NeuronsList &neurons);

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
	int getInputNeuronsAmount() const;

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
	int getOutputNeuronsAmount() const;

	/**
	 * Size of neurons list getter.
	 *
	 * @return Size of neurons list.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 03 Aug 2011
	 */
	int dimension() const;

	/**
	 * Clear all type flags.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 21 Aug 2009
	 */
	void clearTypes();

	/**
	 * Reset all neurons values.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 21 Aug 2009
	 */
	void reset();

	/**
	 * Class destructor. Memory release and variables deinitialization.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 03 Aug 2011
	 */
	virtual ~NeuronsList();

	/**
	 * List elements access operator overloading.
	 *
	 * @param index Index of element.
	 *
	 * @return Constant element value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 03 Aug 2011
	 */
	Neuron operator[](int index) const;

	/**
	 * List elements access operator overloading.
	 *
	 * @param index Index of element.
	 *
	 * @return Constant element value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 03 Aug 2011
	 */
	Neuron& operator[](int index);

	/**
	 * Assignment operator overloading.
	 *
	 * @param neurons Right side operand.
	 *
	 * @return Neurons list instance reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 03 Aug 2011
	 */
	virtual NeuronsList& operator=(const NeuronsList &neurons);

	friend std::ostream& operator<<(std::ostream &out, NeuronsList &neurons);

};

/**
 * Output operator redefinition.
 *
 * @param out Output stream reference.
 *
 * @param neuron Neuron list instance reference.
 *
 * @return Output stream reference.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 03 Aug 2011
 */
std::ostream& operator<<(std::ostream &out, NeuronsList &neurons);

#endif
