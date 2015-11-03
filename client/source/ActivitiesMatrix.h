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

#ifndef ACTIVITIES_MATRIX_H
#define ACTIVITIES_MATRIX_H

#include "GraphMatrix.h"

/**
 * ANN typology graph adjacency matrix class.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 03 Aug 2011
 */
class ActivitiesMatrix : public GraphMatrix {

public:

	/**
	 * Minimum possible weight activity.
	 */
	static const double MIN_ACTIVITY;

	/**
	 * Maximum possible weight activity.
	 */
	static const double MAX_ACTIVITY;

private:

	/**
	 * Set all activities to the maximum valid value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 17 Jul 2015
	 */
	void setAllToMax();

public:

	/**
	 * Constructor without parameters.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.comm
	 *
	 * @date 03 Aug 2011
	 */
	ActivitiesMatrix();

	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @param size Size of the matrix.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.comm
	 *
	 * @date 03 Aug 2011
	 */
	ActivitiesMatrix(int size);

	/**
	 * Copy constructor.
	 *
	 * @param graph Instance to be copied.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.comm
	 *
	 * @date 03 Aug 2011
	 */
	ActivitiesMatrix(const ActivitiesMatrix &activities);

	/**
	 * Activities normalizatoin.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.comm
	 *
	 * @date 03 Aug 2011
	 */
	void normalize();

	/**
	 * Assignment operator overloading.
	 *
	 * @param col Column.
	 *
	 * @param Row Row.
	 *
	 * @return Constant element value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.comm
	 *
	 * @date 03 Aug 2011
	 */
	virtual ActivitiesMatrix& operator=(const ActivitiesMatrix &activities);
};

#endif
