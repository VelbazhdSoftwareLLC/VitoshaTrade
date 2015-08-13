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

using namespace std;

#include "ANNIO.h"

ANNIO::ANNIO() {
	values.clear();
}

ANNIO::ANNIO(int size) {
	values.clear();
	for(int i=0; i<size; i++) {
		values.push_back( 0.0 );
	}
}

ANNIO::ANNIO(const ANNIO &io) {
	values = io.values;
}

int ANNIO::dimension() const {
	return( values.size() );
}

ANNIO::~ANNIO() {
	values.clear();
}

double ANNIO::operator[](int index) const {
	if (index<0 || index>=values.size()) {
		throw( "ANNIO00202" );
		return( 0.0 );
	}

	return( values[index] );
}

double& ANNIO::operator[](int index) {
	if (index<0 || index>=values.size()) {
		throw( "ANNIO00203" );
	}

	return( values[index] );
}

ANNIO& ANNIO::operator=(const ANNIO &io) {
	values = io.values;

	return( *this );
}

ostream& operator<<(ostream &out, ANNIO &io) {
	out << io.values.size();
	out << endl;

	for (vector<double>::const_iterator i=io.values.begin(); i!=io.values.end(); i++) {
		out << *i;
		if ((i+1) != io.values.end()) {
			out << " ";
		}
	}

	return( out );
}
