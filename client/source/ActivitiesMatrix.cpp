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

using namespace std;

#include "ActivitiesMatrix.h"

void ActivitiesMatrix::setAllToMax() {
	for (vector< vector<double> >::iterator i=values.begin(); i!=values.end(); i++) {
		for (vector<double>::iterator ij=(*i).begin(); ij!=(*i).end(); ij++) {
			*ij = MAX_ACTIVITY;
		}
	}
}

ActivitiesMatrix::ActivitiesMatrix() : GraphMatrix() {
   setAllToMax();
}

ActivitiesMatrix::ActivitiesMatrix(int size) : GraphMatrix(size) {
   setAllToMax();
}

ActivitiesMatrix::ActivitiesMatrix(const ActivitiesMatrix &activities) : GraphMatrix(activities) {
   setAllToMax();
}

void ActivitiesMatrix::normalize() {
	for (vector< vector<double> >::iterator i=values.begin(); i!=values.end(); i++) {
		for (vector<double>::iterator ij=(*i).begin(); ij!=(*i).end(); ij++) {
			if (*ij < MIN_ACTIVITY) {
				*ij = MIN_ACTIVITY;
			}
			if (*ij > MAX_ACTIVITY) {
				*ij = MAX_ACTIVITY;
			}
		}
	}
}

ActivitiesMatrix& ActivitiesMatrix::operator=(const ActivitiesMatrix &activities) {
	//TODO Check how parent functions are called?
	GraphMatrix::operator=(activities);
	normalize();

	return( *this );
}
