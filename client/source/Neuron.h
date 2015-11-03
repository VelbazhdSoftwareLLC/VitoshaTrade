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

#ifndef NEURON_H
#define NEURON_H

#include <iostream>

#include "NeuronType.h"

/**
 * Single neuron class.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 03 Aug 2011
 */
class Neuron {

public:

	/**
	 * Bias neuron value.
	 */
	static const double BIAS_VALUE;

	/**
	 * Neurons reset constant value.
	 */
	static const double RESET_VALUE;

	/**
	 * Minimal error constant value.
	 */
	static const double MIN_ERROR;

private:

	/**
	 * Neuron type. More than one neuron can be bias, input and output in multi
	 * layer networks. Also each neuron can be in more than single type.
	 */
	NeuronType type;

	/**
	 * Neuron value.
	 */
	double value;

	/**
	 * Neuron error in back-propagation training.
	 */
	double error;

public:

	/**
	 * Constructor without parameters.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	Neuron();

	/**
	 * Constructor without parameters.
	 *
	 * @param neuron Instance to be copied.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	Neuron(const Neuron &neuron);

	/**
	 * Is regular neuron getter.
	 *
	 * @return True if neuron is bias, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	bool isRegular() const;

	/**
	 * Regular neuron setter.
	 *
	 * @param value True if neuron will be bias, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	void setRegular(bool value);

	/**
	 * Is bias neuron getter.
	 *
	 * @return True if neuron is bias, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 21 Aug 2009
	 */
	bool isBias() const;

	/**
	 * Bias neuron setter.
	 *
	 * @param value True if neuron will be bias, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 08 Mar 2009
	 */
	void setBias(bool value);

	/**
	 * Is input neuron getter.
	 *
	 * @return True if neuron is input, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 30 Apr 2009
	 */
	bool isInput() const;

	/**
	 * Input neurons setter.
	 *
	 * @param value True if neuron will be input, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 29 Apr 2009
	 */
	void setInput(bool value);

	/**
	 * Is output neuron getter.
	 *
	 * @return True if neuron is output, false otherwise.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 30 Apr 2009
	 */
	bool isOutput() const;

	/**
	 * Output neurons setter.
	 *
	 * @param size Amount of output neurons at the end of neurons array.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 29 Apr 2009
	 */
	void setOutput(bool value);

	/**
	 * Neuron type getter.
	 *
	 * @return Neuron type.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 04 Aug 2011
	 */
	NeuronType getType() const;

	/**
	 * Neuron type setter.
	 *
	 * @param type Neuron type.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 04 Aug 2011
	 */
	void setType(NeuronType type);

	/**
	 * Neuron value getter.
	 *
	 * @return Neuron value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	double getValue() const;

	/**
	 * Neuron value setter.
	 *
	 * @param value Neuron value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	void setValue(double value);

	/**
	 * Neuron error getter.
	 *
	 * @return Neuron value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	double getError() const;

	/**
	 * Neuron error setter.
	 *
	 * @param value Neuron value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	void setError(double error);

	/**
	 * Reset neuron to constant value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 19 Aug 2009
	 */
	void reset();

	/**
	 * Class destructor.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 22 Oct 2011
	 */
	virtual ~Neuron();

	/**
	 * Assignment operator overloading.
	 *
	 * @param neuron Right side neuron operand.
	 *
	 * @return Neuron instance reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	virtual Neuron& operator=(const Neuron &neuron);

	/**
	 * Assignment operator overloading.
	 *
	 * @param neuron Right side neuron value operand.
	 *
	 * @return Neuron istance reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	Neuron& operator+=(const double value);

	/**
	 * Assignment operator overloading.
	 *
	 * @param neuron Right side neuron error operand.
	 *
	 * @return Neuron instance reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	Neuron& operator-=(const double error);

	friend std::ostream& operator<<(std::ostream &out, Neuron &neuron);
};

/**
 * Output operator redefinition.
 *
 * @param out Output stream reference.
 *
 * @param neuron Neuron instance reference.
 *
 * @return Output stream reference.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 03 Aug 2011
 */
std::ostream& operator<<(std::ostream &out, Neuron &neuron);

#endif
