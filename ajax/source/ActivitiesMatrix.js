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
 * Minimum possible weight activity.
 */
const MIN_ACTIVITY = 0.0;

/**
 * Maximum possible weight activity.
 */
const MAX_ACTIVITY = 1.0;

/**
 * ANN typology graph adjacency matrix class.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 03 Aug 2011
 */
function ActivitiesMatrix(size) {
	/**
	 * Matrix values.
	 */
	this.values = new Array(size);

	for ( i = 0; i < size; i++) {
		this.values[i] = new Array(size);
	}

	for ( i = 0; i < size; i++) {
		for ( j = 0; j < size; j++) {
			this.values[i][j] = MAX_ACTIVITY;
		}
	}

	/**
	 * Set all activities to the maximum valid value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 17 Jul 2015
	 */
	this.setAllToMax = function() {
		for ( i = 0; i < this.values.length; i++) {
			for ( j = 0; j < this.values[i].length; j++) {
				this.values[i][j] = MAX_ACTIVITY;
			}
		}
	};

	/**
	 * Activities normalizatoin.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.comm
	 *
	 * @date 03 Aug 2011
	 */
	this.normalize = function() {
		for ( i = 0; i < this.values.length; i++) {
			for ( j = 0; j < this.values[i].length; j++) {
				if (this.values[i][j] < MIN_ACTIVITY) {
					this.values[i][j] = MIN_ACTIVITY;
				}
				if (this.values[i][j] > MAX_ACTIVITY) {
					this.values[i][j] = MAX_ACTIVITY;
				}
			}
		}
	};
}
