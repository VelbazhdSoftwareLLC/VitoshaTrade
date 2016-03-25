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
document.write('<script type="text/javascript" src="' + 'Chromosome.js' + '"></script>');

/**
 * Minimum population size. Four is useful at each crossover and mutation to
 * have two parents, one child and one reserved best chromosome.
 */
var MIN_POPULATION_SIZE = 4;

/**
 * List of weights used as population class.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 05 Aug 2011
 */
function Population(size) {
	/*
	 * DE is not working with less than minimum amount of chromosomes.
	 */
	if (size < MIN_POPULATION_SIZE) {
		size = MIN_POPULATION_SIZE;
	}

	/**
	 * Weights list.
	 */
	this.list = [];
	for (var k = 0; k < list.length; k++) {
		list[k] = new Chromosome();
	}

	/**
	 * Index of the chromozome with the best fitness.
	 */
	this.bestFitnessIndex = 0;

	/**
	 * Size of neurons list getter.
	 *
	 * @return Size of neurons list.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 05 Aug 2011
	 */
	this.dimension = function() {
		return list.length;
	};

	/**
	 * Best local fitness value getter.
	 *
	 * @return Best local fitness value.
	 *
	 * @author Ivan Grozev
	 *
	 * @email Ivan.Iliev.Grozev@gmail.com
	 *
	 * @date 07 Jun 2009
	 */
	this.getBestFitness = function() {
		return list[bestFitnessIndex].getFitness();
	};

	/**
	 * Find index of the chromosome with the best fitness value.
	 *
	 * @return Index of the chromosome with the best fitness.
	 *
	 * @author Galq Cirkalova
	 *
	 * @email galq_cirkalova@abv.bg
	 *
	 * @date 24 Apr 2009
	 */
	this.getBestFitnessIndex = function() {
		return bestFitnessIndex;
	};

	/**
	 * Check chromosome for duplication.
	 *
	 * @param chromosome Chromosome in population array.
	 *
	 * @return True if duplicate is found, false otherwise.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 25 Aug 2009
	 */
	this.hasDuplication = function(chromosome) {
		/*
		 * Check chromosome for duplication.
		 */
		for (var k = 0; k < list.length; k++) {
			if (list[k].getFitness() == chromosome.getFitness() && list[k] != chromosome) {
				return true;
			}
		}

		return false;
	};

	/**
	 * Initialize population with random chromosomes.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 27 Mar 2009
	 */
	this.initRandom = function() {
		for (var k = 0; k < list.length; k++) {
			list[k].random();
		}

		searchBestFitnessIndex();
	};

	/**
	 * Search for best fitness and save it in class member variable.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 18 Aug 2009
	 */
	this.searchBestFitnessIndex = function() {
		bestFitnessIndex = 0;

		/*
		 * Best fintess is the smallest possible. Fitness is artificial neural
		 * network total error.
		 */
		for (var i = 0; i < list.length; i++) {
			if (list[i].getFitness() < list[bestFitnessIndex].getFitness()) {
				bestFitnessIndex = i;
			}
		}
	};

	/*
	 * Best fitness index should be available.
	 */
	searchBestFitnessIndex();
}
