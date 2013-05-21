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

#include <iomanip>

using namespace std;

#include "Neuron.h"

Neuron::Neuron() {
	setRegular( true );
	reset();
}

Neuron::Neuron(const Neuron &neuron) {
	type = neuron.type;
	value = neuron.value;
	error = neuron.error;
}

bool Neuron::isRegular() const {
	if (type == REGULAR) {
		return( true );
	} else {
		return( false );
	}
}

void Neuron::setRegular(bool value) {
	if (value == true) {
		type = REGULAR;
	}
}

bool Neuron::isBias() const {
	if ((type&BIAS) == BIAS) {
		return( true );
	} else {
		return( false );
	}
}

void Neuron::setBias(bool value) {
	if (value == true) {
		switch (type) {
		case REGULAR:
			type = BIAS;
			break;
		case BIAS:
			break;
		case INPUT:
			type = INPUT_BIAS;
			break;
		case INPUT_BIAS:
			break;
		case OUTPUT:
			type = OUTPUT_BIAS;
			break;
		case OUTPUT_BIAS:
			break;
		case OUTPUT_INPUT:
			type = OUTPUT_INPUT_BIAS;
			break;
		case OUTPUT_INPUT_BIAS:
			break;
		}

		value = BIAS_VALUE;
	} else if (value == false) {
		switch (type) {
		case REGULAR:
			break;
		case BIAS:
			type = REGULAR;
			break;
		case INPUT:
			break;
		case INPUT_BIAS:
			type = INPUT;
			break;
		case OUTPUT:
			break;
		case OUTPUT_BIAS:
			type = OUTPUT;
			break;
		case OUTPUT_INPUT:
			break;
		case OUTPUT_INPUT_BIAS:
			type = OUTPUT_INPUT;
			break;
		}
	}
}

bool Neuron::isInput() const {
	if ((type&INPUT) == INPUT) {
		return( true );
	} else {
		return( false );
	}
}

void Neuron::setInput(bool value) {
	if (value == true) {
		switch (type) {
		case REGULAR:
			type = INPUT;
			break;
		case BIAS:
			type = INPUT_BIAS;
			break;
		case INPUT:
			break;
		case INPUT_BIAS:
			break;
		case OUTPUT:
			type = OUTPUT_INPUT;
			break;
		case OUTPUT_BIAS:
			type = OUTPUT_INPUT_BIAS;
			break;
		case OUTPUT_INPUT:
			break;
		case OUTPUT_INPUT_BIAS:
			break;
		}
	} else if (value == false) {
		switch (type) {
		case REGULAR:
			break;
		case BIAS:
			break;
		case INPUT:
			break;
		case INPUT_BIAS:
			type = BIAS;
			break;
		case OUTPUT:
			break;
		case OUTPUT_BIAS:
			break;
		case OUTPUT_INPUT:
			type = OUTPUT;
			break;
		case OUTPUT_INPUT_BIAS:
			type = OUTPUT_BIAS;
			break;
		}
	}
}

bool Neuron::isOutput() const {
	if ((type&OUTPUT) == OUTPUT) {
		return( true );
	} else {
		return( false );
	}
}

void Neuron::setOutput(bool value) {
	if (value == true) {
		switch (type) {
		case REGULAR:
			type = OUTPUT;
			break;
		case BIAS:
			type = OUTPUT_BIAS;
			break;
		case INPUT:
			type = OUTPUT_INPUT;
			break;
		case INPUT_BIAS:
			type = OUTPUT_INPUT_BIAS;
			break;
		case OUTPUT:
			break;
		case OUTPUT_BIAS:
			break;
		case OUTPUT_INPUT:
			break;
		case OUTPUT_INPUT_BIAS:
			break;
		}
	} else if (value == false) {
		switch (type) {
		case REGULAR:
			type = OUTPUT;
			break;
		case BIAS:
			type = OUTPUT_BIAS;
			break;
		case INPUT:
			type = OUTPUT_INPUT;
			break;
		case INPUT_BIAS:
			type = OUTPUT_INPUT_BIAS;
			break;
		case OUTPUT:
			break;
		case OUTPUT_BIAS:
			break;
		case OUTPUT_INPUT:
			break;
		case OUTPUT_INPUT_BIAS:
			break;
		}
	}
}

NeuronType Neuron::getType() const {
	return( type );
}

void Neuron::setType(NeuronType type) {
	this->type = type;
}

double Neuron::getValue() const {
	return( value );
}

void Neuron::setValue(double value) {
	this->value = value;
}

double Neuron::getError() const {
	return( error );
}

void Neuron::setError(double error) {
	this->error = error;
}

void Neuron::reset() {
	if (isBias() == true) {
		value = BIAS_VALUE;
	} else {
		value = RESET_VALUE;
	}

	error = MIN_ERROR;
}

Neuron::~Neuron() {
}

Neuron& Neuron::operator=(const Neuron &neuron) {
	type = neuron.type;
	value = neuron.value;
	error = neuron.error;

	return( *this );
}

Neuron& Neuron::operator+=(const double value) {
	setValue( value );

	return( *this );
}

Neuron& Neuron::operator-=(const double error) {
	setError( error );

	return( *this );
}

ostream& operator<<(ostream &out, Neuron &neuron) {
	out << "[" << (unsigned)neuron.type << ", " << setw(8) << neuron.value << ", " << setw(8) << neuron.error << "]";

	return( out );
}
