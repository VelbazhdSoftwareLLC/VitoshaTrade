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
document.write('<script type="text/javascript" src="' + 'cstdlib.js' + '"></script>');

/**
 * Minimum population size. Four is useful at each crossover and mutation to
 * have two parents, one child and one reserved best chromosome.
 */
const MIN_POPULATION_SIZE = 4;

/**
 * Integer number for probability percent result of crossover to be written
 * into the chromosome with the best fittnes. It is part of selection
 * strategy. Sum of all possibilities should be 100.
 */
const CROSSOVER_RESULT_INTO_BEST_PERCENT = 5;

/**
 * Integer number for probability percent result of crossover to be written
 * into the chromosome with the middle fittnes. It is part of selection
 * strategy. Sum of all possibilities should be 100.
 */
const CROSSOVER_RESULT_INTO_MIDDLE_PERCENT = 40;

/**
 * Integer number for probability percent result of crossover to be written
 * into the chromosome with the worst fittnes. It is part of selection
 * strategy. Sum of all possibilities should be 100.
 */
const CROSSOVER_RESULT_INTO_WORST_PERCENT = 55;

/**
 * Flag to involve the best chromosome in evolution process.
 */
const KEEP_THE_BEST_CHROMOSOME = true;

/**
 * Do prediction with each chromosome, not only with the best one.
 */
const PREDICT_WITH_EACH_CHROMOSOME = true;

/**
 * Minimuim random initializaton value for initial chromosome values.
 */
const MIN_INIT_RANDOM = -1.0;

/**
 * Maximum random initializaton value for initial chromosome values.
 */
const MAX_INIT_RANDOM = +1.0;

/**
 * Minimuim mutation factor.
 */
const MIN_MUTATION_FACTOR = 0.0;

/**
 * Maximum mutation factor.
 */
const MAX_MUTATION_FACTOR = 0.1;

/**
 * Flag to switch off crossover at all.
 */
const CROSSOVER_TYPE_NONE = 0x00;

/**
 * Crossover by randomly selected gens flag.
 */
const CROSSOVER_TYPE_RANDOM = 0x01;

/**
 * Crossover by randomly selected gens flag.
 */
const CROSSOVER_TYPE_50_50 = 0x02;

/**
 * Crossover by single intersection flag.
 */
const CROSSOVER_TYPE_SINGLE_CUT = 0x03;

/**
 * Crossover by binary metrix flag.
 */
const CROSSOVER_TYPE_BINARY_MATRIX = 0x04;

/**
 * Differential Evolution.
 *
 * @author Daniel Chutrov
 *
 * @email d.chutrov@gmail.com
 *
 * @date 19 Dec 2010
 */
function DE(ann, populationSize, crossoverPercent, mutationPercent) {
	/**
	 * Crossover type.
	 */
	this.crossoverType = CROSSOVER_TYPE_RANDOM;

	/**
	 * Probability crossover to ocure.
	 */
	this.crossoverPercent = crossoverPercent;

	/**
	 * Probability mutation to ocure.
	 */
	this.mutationPercent = mutationPercent;

	/**
	 * Population size. The amount of chormosomes in first dimension of
	 * population array.
	 */
	this.populationSize = populationSize;

	/**
	 * Number of neurons used into artificial neural network. The amout of
	 * neurons gives second and third dimension of population array (square
	 * matrix).
	 */
	this.neuronsAmount = ann.neuronsAmount;

	/**
	 * Array with fitness values for each chromosome. Smaller output error is
	 * better fitness for the chromosome (weights set).
	 */
	this.fitness = new Array(this.neuronsAmount);

	/**
	 * Population array. Population array is dynamically allocated. Eeach
	 * member is two dimensional array (matrix of weights). Weights matrix is
	 * also dynamically allocated.
	 */
	this.population = new Array(populationSize);
	for (var k = 0; k < this.populationSize; k++) {
		this.population[k] = new Array(this.neuronsAmount);
		for (var i = 0; i < this.neuronsAmount; i++) {
			this.population[k][i] = new Array(this.neuronsAmount);
		}
	}

	/**
	 * Index of the chromozome with the best fitness.
	 */
	this.bestFitnessIndex = 0;

	/**
	 * Link to real artificial neural network object.
	 */
	this.ann = ann;

	/*
	 * Check ANN pointer for point valid object.
	 */
	if (this.ann == null) {
		//TODO Find way to inform the user that there is no ANN reference.
	}

	/*
	 * It is not possible population size to less than minimum amount.
	 */
	if (this.populationSize < MIN_POPULATION_SIZE) {
		this.populationSize = MIN_POPULATION_SIZE;
	}

	/*
	 * Probability is between 0 and 100.
	 */
	if (this.crossoverPercent < 0.0) {
		this.crossoverPercent = 0.0;
	}
	if (this.crossoverPercent > 100.0) {
		this.crossoverPercent = 100.0;
	}
	if (this.mutationPercent < 0.0) {
		this.mutationPercent = 0.0;
	}
	if (this.mutationPercent > 100.0) {
		this.mutationPercent = 100.0;
	}

	/*
	 * Check valid object internal structure.
	 */
	if (this.populationSize <= 0) {
		//TODO Find way to inform the user that there is problem with population size.
	}

	if (this.neuronsAmount <= 0) {
		//TODO Find way to inform the user that there is problem with neurons amount.
	}

	/**
	 * Select chromosomes for crossover. Swap places of each index according
	 * probabilistic strategy.
	 *
	 * @param resultIndex Index on which crossover result is stored.
	 *
	 * @param firstParentIndex Index of the first parent.
	 *
	 * @param secondParentIndex Index of the second parent.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 19 Dec 2010
	 */
	this.select = function(resultIndex, firstParentIndex, secondParentIndex) {
		/*
		 * Do selection of indivuduals according probabilistic strategy.
		 */
		var index;

		/*
		 * Random value should be between 0 and sum of all percents (general 100%).
		 */
		var percent = Math.floor(Math.random() * (CROSSOVER_RESULT_INTO_WORST_PERCENT + CROSSOVER_RESULT_INTO_MIDDLE_PERCENT + CROSSOVER_RESULT_INTO_BEST_PERCENT));

		if (percent < CROSSOVER_RESULT_INTO_WORST_PERCENT) {
			/*
			 * Worst fitness value is the highest.
			 */
			if (this.fitness[resultIndex] < this.fitness[firstParentIndex]) {
				index = resultIndex;
				resultIndex = firstParentIndex;
				firstParentIndex = index;
			}
			if (this.fitness[resultIndex] < this.fitness[secondParentIndex]) {
				index = resultIndex;
				resultIndex = secondParentIndex;
				secondParentIndex = index;
			}
		} else if (percent < (CROSSOVER_RESULT_INTO_WORST_PERCENT + CROSSOVER_RESULT_INTO_MIDDLE_PERCENT)) {
			/*
			 * Middle fitness value is between the others.
			 */
			if (this.fitness[secondParentIndex] < this.fitness[firstParentIndex]) {
				index = secondParentIndex;
				secondParentIndex = firstParentIndex;
				firstParentIndex = index;
			}
			if (this.fitness[resultIndex] < this.fitness[firstParentIndex]) {
				index = resultIndex;
				resultIndex = firstParentIndex;
				firstParentIndex = index;
			}
			if (this.fitness[resultIndex] > this.fitness[secondParentIndex]) {
				index = resultIndex;
				resultIndex = secondParentIndex;
				secondParentIndex = index;
			}
		} else if (percent < (CROSSOVER_RESULT_INTO_WORST_PERCENT + CROSSOVER_RESULT_INTO_MIDDLE_PERCENT + CROSSOVER_RESULT_INTO_BEST_PERCENT)) {
			/*
			 * Best fitness value is the smallest.
			 */
			if (this.fitness[resultIndex] > this.fitness[firstParentIndex]) {
				index = resultIndex;
				resultIndex = firstParentIndex;
				firstParentIndex = index;
			}
			if (this.fitness[resultIndex] > this.fitness[secondParentIndex]) {
				index = resultIndex;
				resultIndex = secondParentIndex;
				secondParentIndex = index;
			}
		}
	}
	/**
	 * Crossover chromosomes.
	 *
	 * @param resultIndex Index on which crossover result is stored.
	 *
	 * @param firstParentIndex Index of the first parent.
	 *
	 * @param secondParentIndex Index of the second parent.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 19 Dec 2010
	 */
	this.crossover = function(resultIndex, firstParentIndex, secondParentIndex) {
		// if (this.crossoverType == CROSSOVER_TYPE_NONE) {
		// return;
		// }
		//
		// if (Math.random()*100 > this.crossoverPercent) {
		// return;
		// }
		//
		// if (resultIndex < 0 || resultIndex >= this.populationSize) {
		// return;
		// }
		//
		// if (firstParentIndex < 0 || firstParentIndex >= this.populationSize) {
		// return;
		// }
		//
		// if (secondParentIndex < 0 || secondParentIndex >= this.populationSize) {
		// return;
		// }
		//
		// if (this.crossoverType == CROSSOVER_TYPE_RANDOM) {
		// //TODO Implement crossover as private helper method.
		// for (var j=0; j<this.neuronsAmount; j++) {
		// for (var i=0; i<this.neuronsAmount; i++) {
		// this.population[resultIndex][i][j] = (Math.random()<0.5) ? this.population[firstParentIndex][i][j] : this.population[secondParentIndex][i][j];
		// }
		// }
		// } else if (this.crossoverType == CROSSOVER_TYPE_50_50) {
		// //TODO Implement crossover as private helper method.
		// for (var i=0; i<this.neuronsAmount; i++) {
		// if (i%2 == 0) {
		// for (var j=0; j<this.neuronsAmount; j++) {
		// this.population[resultIndex][i][j] = this.population[firstParentIndex][i][j];
		// }
		// } else {
		// for (var j=0; j<neuronsAmount; j++) {
		// this.population[resultIndex][i][j] = this.population[secondParentIndex][i][j];
		// }
		// }
		// }
		// } else if (this.crossoverType == DE::CROSSOVER_TYPE_SINGLE_CUT) {
		// //TODO Implement crossover as private helper method.
		// var x = Math.floor(Math.random()*(this.neuronsAmount+1));
		// var y = Math.floor(Math.random()*(this.neuronsAmount+1));
		//
		// for (var j=0; j<this.neuronsAmount; j++) {
		// for (var i=0; i<y; i++) {
		// this.population[resultIndex][i][j] = this.population[firstParentIndex][i][j];
		// }
		// }
		//
		// for (var i=0; i<this.neuronsAmount; i++) {
		// if (i < x) {
		// this.population[resultIndex][y][i] = this.population[firstParentIndex][y][i];
		// } else {
		// this.population[resultIndex][y][i] = this.population[secondParentIndex][y][i];
		// }
		// }
		//
		// for (var j=0; j<this.neuronsAmount; j++) {
		// for (var i=y+1; i<this.neuronsAmount; i++) {
		// this.population[resultIndex][i][j] = this.population[secondParentIndex][i][j];
		// }
		// }
		// } else if (this.crossoverType == CROSSOVER_TYPE_BINARY_MATRIX) {
		// //TODO Implement crossover as private helper method.
		// //TODO Implement binary matrix template for crossover.
		// }
	}
	/**
	 * Mutate chromosome.
	 *
	 * @param index Index of the chromosome which mutate.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 19 Dec 2010
	 */
	this.mutate = function(index) {
		if (Math.random() * 100 > this.mutationPercent) {
			return;
		}

		if (index < 0 || index >= this.populationSize) {
			return;
		}

		/*
		 * First chromosome index used in difference vector calculation.
		 */
		var firstIndex = Math.floor(Math.random() * this.populationSize);

		/*
		 * Second chromosome index used in difference vector calculation.
		 */
		var secondIndex = Math.floor(Math.random() * this.populationSize);

		/*
		 * Difference vector weight factor.
		 */
		var factor = MIN_MUTATION_FACTOR + (MAX_MUTATION_FACTOR - MIN_MUTATION_FACTOR) * Math.random();

		/*
		 * Calculate weighted difference vector.
		 * Add weighted difference vector as mutation of chromosome.
		 */
		for (var j = 0; j < this.neuronsAmount; j++) {
			for (var i = 0; i < this.neuronsAmount; i++) {
				this.population[index][i][j] += (factor * (this.population[firstIndex][i][j] - this.population[secondIndex][i][j]));
			}
		}
	}
	//	/**
	//	 * Search for best fitness and save it in class member variable.
	//	 *
	//	 * @author Daniel Chutrov
	//	 *
	//	 * @email d.chutrov@gmail.com
	//	 *
	//	 * @date 19 Dec 2010
	//	 */
	//	this.searchBestFitnessIndex = function() {
	//		this.bestFitnessIndex = 0;
	//
	//		/*
	//		 * Best fintess is the smallest possible. Fitness is artificial neural
	//		 * network total error.
	//		 */
	//		for (var i=0; i<this.populationSize; i++) {
	//			if (this.fitness[i] < this.fitness[bestFitnessIndex]) {
	//				this.bestFitnessIndex = i;
	//			}
	//		}
	//	}
	//
	//	/**
	//	 * Initialize chromosome with random values.
	//	 *
	//	 * @param index Chromosome index in population array.
	//	 *
	//	 * @author Daniel Chutrov
	//	 *
	//	 * @email d.chutrov@gmail.com
	//	 *
	//	 * @date 19 Dec 2010
	//	 */
	//	this.randomChromosome = function(index) {
	//		/*
	//		* Initialize chromosome with random values.
	//		*/
	//		for (var j=0; j<this.neuronsAmount; j++) {
	//			for (var i=0; i<this.neuronsAmount; i++) {
	//				this.population[index][j][i] = MIN_INIT_RANDOM + (MAX_INIT_RANDOM-MIN_INIT_RANDOM) * Math.random();
	//			}
	//		}
	//	}
	//
	//	/**
	//	 * Initialize population with random chromosomes.
	//	 *
	//	 * @author Daniel Chutrov
	//	 *
	//	 * @email d.chutrov@gmail.com
	//	 *
	//	 * @date 19 Dec 2010
	//	 */
	//	this.initRandom = function() {
	//		/*
	//		 * Set random values as population.
	//		 */
	//		for (var k=0; k<this.populationSize; k++) {
	//			this.randomChromosome( k );
	//			/*
	//			 * Set worse fitness value.
	//			 */
	//			this.fitness[k] = RAND_MAX;
	//		}
	//
	//		this.searchBestFitnessIndex();
	//	}

	/**
	 * Check chromosome for duplication.
	 *
	 * @param index Chromosome index in population array.
	 *
	 * @return True if duplicate is found, false otherwise.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 21 Feb 2011
	 */
	this.hasDupliation = function(index) {
		/*
		 * Check chromosome for duplication.
		 */
		for (var k = 0; k < this.populationSize; k++) {
			if (this.fitness[k] == this.fitness[index] && k != index) {
				return (true );
			}
		}

		return (false );
	}
	/**
	 * Evolve population. Do selection for crossover. Crossover half of the
	 * population. Mutate crossovered half of the population.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 19 Dec 2010
	 */
	this.evolve = function() {
		var resultIndex;
		var firstParentIndex;
		var secondParentIndex;

		/*
		 * Evolve more chromosomes of the population (not all of them).
		 */
		for (var k = 0; k < this.populationSize; k++) {
			/*
			 * Select random indivudials for crossover according selection strategy.
			 * The best chromosome is not part of the evolution to give better chances
			 * to other chromosomes to survive and to evolve.
			 */
			do {
				resultIndex = Math.floor(Math.random() * this.populationSize);
				firstParentIndex = Math.floor(Math.random() * this.populationSize);
				secondParentIndex = Math.floor(Math.random() * this.populationSize);
			} while (KEEP_THE_BEST_CHROMOSOME==true && (resultIndex==this.bestFitnessIndex || firstParentIndex==this.bestFitnessIndex || secondParentIndex==this.bestFitnessIndex));
			this.select(resultIndex, firstParentIndex, secondParentIndex);

			/*
			 * Crossover chromosomes.
			 */
			this.crossover(resultIndex, firstParentIndex, secondParentIndex);

			/*
			 * Mutate crossovered chromosome.
			 */
			this.mutate(resultIndex);

			/*
			 * Load chromosome's weights into ANN.
			 */
			ann.weights = this.population[resultIndex];

			/*
			 * Calculate chromosome fitness by calling ANN total error calculation.
			 */
			this.fitness[resultIndex] = this.ann.totalError();

			/*
			 * Equal chromosomes are useless. Replace with random chromosome.
			 */
			if (this.hasDupliation(resultIndex) == true) {
				/*
				 * Back propagation training for similar chromosomes.
				 */
				this.ann.gradient();
				this.fitness[resultIndex] = this.ann.totalError();
			}

			/*
			 * Update ANN prediction.
			 */
			if (this.fitness[resultIndex] < this.fitness[this.bestFitnessIndex] || PREDICT_WITH_EACH_CHROMOSOME == true) {
				this.ann.predict();
			}

			/*
			 * Update best fitness index.
			 */
			if (this.fitness[resultIndex] < this.fitness[this.bestFitnessIndex]) {
				this.bestFitnessIndex = resultIndex;
			}
		}
	}
}
