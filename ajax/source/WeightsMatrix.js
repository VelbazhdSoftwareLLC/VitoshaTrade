/*******************************************************************************
 *                                                                             *
 * VitoshaTrade is Distributed Artificial Neural Network trained by            *
 * Differential Evolution for prediction of Forex. Project development is in   *
 * Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   *
 * the capital of Bulgaria.                                                    *
 *                                                                             *
 * Copyright (C) 2008-2011 by Todor Balabanov  ( tdb@tbsoft.eu )               *
 *                            Iliyan Zankinski ( iliyan_mf@abv.bg )            *
 *                            Galq Cirkalova   ( galq_cirkalova@abv.bg )       *
 *                            Ivan Grozev      ( ivan.iliev.grozev@gmail.com ) *
 *                            Daniel Chutrov   ( d.chutrov@gmail.com )         *
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

/**
 * ANN typology graph adjacency matrix class.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 03 Aug 2011
 */
function WeightsMatrix(size) {
	/**
	 * Matrix values.
	 */
	this.values = new Array(size);

	for ( i = 0; i < size; i++) {
		this.values[i] = new Array(size);
	}

	for ( i = 0; i < size; i++) {
		for ( j = 0; j < size; j++) {
			values[i][j] = 0.0;
		}
	}

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
	this.dimension = function() {
		return values.length;
	};
	
	this.get = function(col, row) {
		if (col<0 || col>=values.size() || row<0 || row>=values.size()) {
			//TODO Do exception handling.
			return( 0.0 );
		};
	
		return values[col][row];
	};

	this.set = function(col, row, value) {
		if (col<0 || col>=values.size() || row<0 || row>=values.size()) {
			//TODO Do exception handling.
			return value;
		}
	
		values[col][row] = value;
	
		return( values[col][row] );
	};
}
