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

#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <vector>
#include <iostream>

/**
 * Graph adjacency matrix base class used as base for ANN weights and topology
 * matrices.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 03 Aug 2011
 */
class GraphMatrix {

protected:

	/**
	 * Matrix values.
	 */
	std::vector< std::vector<double> > values;

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
	GraphMatrix();

	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @param size Size of the matrix.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	GraphMatrix(int size);

	/**
	 * Copy constructor.
	 *
	 * @param graph Instance to be copied.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	GraphMatrix(const GraphMatrix &graph);

	/**
	 * Size of the square matrix getter.
	 *
	 * @return Size of the square matrix.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	int dimension() const;

	/**
	 * Class destructor. Memory release and variables deinitialization.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	virtual ~GraphMatrix();

	/**
	 * Matrix elements access operator overloading.
	 *
	 * @param col Column.
	 *
	 * @param row Row.
	 *
	 * @return Constant element value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	double operator()(int col, int row) const;

	/**
	 * Matrix elements access operator overloading.
	 *
	 * @param col Column.
	 *
	 * @param row Row.
	 *
	 * @return Constant element value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	double& operator()(int col, int row);

	/**
	 * Assignment operator overloading.
	 *
	 * @param graph Right side operand.
	 *
	 * @return Graph instance reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 03 Aug 2011
	 */
	virtual GraphMatrix& operator=(const GraphMatrix &graph);

	//TODO Overload poerator[].

	friend std::ostream& operator<<(std::ostream &out, GraphMatrix &graph);
};

/**
 * Output operator redefinition.
 *
 * @param out Output stream reference.
 *
 * @param graph Graph instance reference.
 *
 * @return Output stream reference.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 03 Aug 2011
 */
std::ostream& operator<<(std::ostream &out, GraphMatrix &graph);

#endif
