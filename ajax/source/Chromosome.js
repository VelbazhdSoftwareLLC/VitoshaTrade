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
/*
 * Include files.
 */
document.write('<script type="text/javascript" src="' + 'WeightsMatrix.js' + '"></script>');

/**
 * Less optimal fitness value constant.
 */
const LESS_OPTIMAL_FITNESS_VALUE = 32767;

/**
 * Minimuim random initializaton value for initial chromosome values.
 */
const MIN_INIT_RANDOM = -1.0;

/**
 * Maximum random initializaton value for initial chromosome values.
 */
const MAX_INIT_RANDOM = +1.0;

/**
 * DE chromosome class.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 05 Aug 2011
 */
function Chromosome() {
	/**
	 * Each chromosome is matrix of weights.
	 */
	this.weights = WeightsMatrix(0);

	/**
	 * Chromosome fitness value. Smaller output error is better fitness for the
	 * chromosome (weights set).
	 */
	this.fitness = LESS_OPTIMAL_FITNESS_VALUE;

	/**
	 * Weights matrix getter.
	 *
	 * @return Weights matrix reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 05 Aug 2011
	 */
	this.getWeights = function() {
		return weights;
	};

	/**
	 * Weights matrix setter.
	 *
	 * @param weights Weights matrix.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 05 Aug 2011
	 */
	this.setWeights = function(weights) {
		this.weights = weights;
	};

	/**
	 * Chromosome fintess value getter.
	 *
	 * @return Fitness value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 05 Aug 2011
	 */
	this.getFitness = function() {
		return (fitness );
	};

	/**
	 * Chromosome fintess value setter.
	 *
	 * @param fitness Fitness value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 05 Aug 2011
	 */
	this.setFitness = function(value) {
		this.fitness = value;
	};

	/**
	 * Initialize chromosome with random values.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 25 Aug 2009
	 */
	this.random = function() {
		/*
		 * Initialize chromosome with random values.
		 */
		for (var j=0; j<weights.dimension(); j++) {
			for (var i=0; i<weights.dimension(); i++) {
				weights[i][j] = MIN_INIT_RANDOM + (MAX_INIT_RANDOM-MIN_INIT_RANDOM) * Math.random();
			}
		}
	
		fitness = LESS_OPTIMAL_FITNESS_VALUE * Math.random();
	};
}
