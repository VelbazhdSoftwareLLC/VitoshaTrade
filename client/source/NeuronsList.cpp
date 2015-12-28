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

#include "NeuronsList.h"

NeuronsList::NeuronsList() {
	list.clear();
}

NeuronsList::NeuronsList(int size) {
	/*
	 * It is not possible neurons amount to be negative number.
	 */
	if (size < MIN_NEURONS_AMOUNT) {
		size = MIN_NEURONS_AMOUNT;
	}

	list.clear();
	for(int i=0; i<size; i++) {
		list.push_back( Neuron() );
	}

	clearTypes();
}

NeuronsList::NeuronsList(const NeuronsList &neurons) {
	list = neurons.list;
}

int NeuronsList::getInputNeuronsAmount() const {
	int inputNeuronsAmount = 0;

	for (std::vector<Neuron>::const_iterator i=list.begin(); i!=list.end(); i++) {
		if((*i).isInput() == true) {
			inputNeuronsAmount++;
		}
	}

	return( inputNeuronsAmount );
}

int NeuronsList::getOutputNeuronsAmount() const {
	int outputNeuronsAmount = 0;

	for (std::vector<Neuron>::const_iterator i=list.begin(); i!=list.end(); i++) {
		if((*i).isOutput() == true) {
			outputNeuronsAmount++;
		}
	}

	return( outputNeuronsAmount );
}

int NeuronsList::dimension() const {
	return( list.size() );
}

void NeuronsList::clearTypes() {
	for (std::vector<Neuron>::iterator i=list.begin(); i!=list.end(); i++) {
		(*i).setRegular( true );
	}
}

void NeuronsList::reset() {
	for (std::vector<Neuron>::iterator i=list.begin(); i!=list.end(); i++) {
		(*i).reset();
	}
}

NeuronsList::~NeuronsList() {
	list.clear();
}

Neuron NeuronsList::operator[](int index) const {
	if (index<0 || index>=list.size()) {
		throw( "NeuronsList00206" );
	}

	return( list[index] );
}

Neuron& NeuronsList::operator[](int index) {
	if (index<0 || index>=list.size()) {
		throw( "NeuronsList00207" );
	}

	return( list[index] );
}

NeuronsList& NeuronsList::operator=(const NeuronsList &neurons) {
	list = neurons.list;

	return( *this );
}

std::ostream& operator<<(std::ostream &out, NeuronsList &neurons) {
	out << neurons.list.size();
	out << std::endl;

	out << neurons.getInputNeuronsAmount();
	out << std::endl;

	out << neurons.getOutputNeuronsAmount();
	out << std::endl;

	for (std::vector<Neuron>::iterator i=neurons.list.begin(); i!=neurons.list.end(); i++) {
		out << (*i);
		if (i+1 != neurons.list.end()) {
			out << " ";
		}
	}

	return( out );
}
