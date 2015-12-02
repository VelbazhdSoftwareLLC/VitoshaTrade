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

#include "Counter.h"

void Counter::clear() {
	counters.clear();
}

long Counter::getValue(const char* key) {
	if (counters.count(key) == 0) {
		return( 0 );
	} else {
		return( counters[key] );
	}
}

void Counter::setValue(const char* key, long value) {
	counters[key] = value;
}

void Counter::increment(const char* key) {
	if (counters.count(key) == 0) {
		counters[key] = +1;
	} else {
		counters[key]++;
	}
}

void Counter::decrement(const char* key) {
	if (counters.count(key) == 0) {
		counters[key] = -1;
	} else {
		counters[key]--;
	}
}

long Counter::operator[](const char* key) {
	return( getValue(key) );
}

ostream& operator<<(ostream &out, Counter &counter) {
	for (map<const char*, long>::iterator i=counter.counters.begin(); i!=counter.counters.end();) {
		out << (*i).first << "\t :\t " << (*i).second;

        ++i;
		if (i != counter.counters.end()) {
			out << endl;
		}
	}

	return( out );
}

//TODO Implement ++ and -- operators.
