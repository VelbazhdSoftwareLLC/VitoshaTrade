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

#include <iomanip>

using namespace std;

#include "GraphMatrix.h"

GraphMatrix::GraphMatrix() {
	for (vector< vector<double> >::iterator i=values.begin(); i!=values.end(); i++) {
		(*i).clear();
	}
	values.clear();
}

GraphMatrix::GraphMatrix(int size) {
	for (vector< vector<double> >::iterator i=values.begin(); i!=values.end(); i++) {
		(*i).clear();
	}
	values.clear();

	for(int i=0; i<size; i++) {
		values.push_back( vector<double>() );
	}

	for(int i=0; i<size; i++) {
		for(int j=0; j<size; j++) {
			values[i].push_back( 0.0 );
		}
	}
}

GraphMatrix::GraphMatrix(const GraphMatrix &graph) {
	values = graph.values;
}

int GraphMatrix::dimension() const {
	return( values.size() );
}

GraphMatrix::~GraphMatrix() {
	for (vector< vector<double> >::iterator i=values.begin(); i!=values.end(); i++) {
		(*i).clear();
	}
	values.clear();
}

double GraphMatrix::operator()(int col, int row) const {
	if (col<0 || col>=values.size() || row<0 || row>=values.size()) {
		throw( "GraphMatrix00171" );
		return( 0.0 );
	}

	return( values[col][row] );
}

double& GraphMatrix::operator()(int col, int row) {
	if (col<0 || col>=values.size() || row<0 || row>=values.size()) {
		throw( "GraphMatrix00211" );

		/*
		 * Fake object to bypass compiler.
		 */
		static double dummy = 0;
		return( dummy );
	}

	//TODO Change the internal value!!!
	return( values[col][row] );
}

GraphMatrix& GraphMatrix::operator=(const GraphMatrix &graph) {
	values = graph.values;

	return( *this );
}

ostream& operator<<(ostream &out, GraphMatrix &graph) {
	for (vector< vector<double> >::iterator i=graph.values.begin(); i!=graph.values.end(); i++) {
		for (vector<double>::iterator ij=(*i).begin(); ij!=(*i).end(); ij++) {
			out << setw(8) << *ij;
			if (ij+1 != (*i).end()) {
				out << " ";
			}
		}

		if (i+1 != graph.values.end()) {
			out << endl;
		}
	}

	return( out );
}
