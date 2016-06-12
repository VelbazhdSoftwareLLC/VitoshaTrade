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
document.write('<script type="text/javascript" src="' + 'Population.js' + '"></script>');
document.write('<script type="text/javascript" src="' + 'CrossoverType.js' + '"></script>');
document.write('<script type="text/javascript" src="' + 'WeightsMatrix.js' + '"></script>');

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
 * Minimum crossover rate as integer number between [0-10000] instead of double number between [0.0-1.0].
 */
const MIN_CROSSOVER_RATE = 0;

/**
 * Maximum crossover rate as integer number between [0-10000] instead of double number between [0.0-1.0].
 */
const MAX_CROSSOVER_RATE = 10000;

/**
 * Differential Evolution.
 *
 * @author Daniel Chutrov
 *
 * @email d.chutrov@gmail.com
 *
 * @date 19 Dec 2010
 */
function DE(counters, ann, populationSize) {
	/**
	 * Use one of the elements in the population as trial element. When the element is better than some other element just change the index value.
	 */
	this.trialIndex = 0;

	/**
	 * In original DE x vector is selected in a loop and each element is visited. Here we will select x random way (statistically it should not have a difference).
	 */
	this.baseIndex = 0;

	/**
	 * Vector a from the original DE implementation.
	 */
	this.targetIndex = 0;

	/**
	 * Vector b from the original DE implementation.
	 */
	this.firstIndex = 0;

	/**
	 * Vector c from the original DE implementation.
	 */
	this.secondIndex = 0;

	/*
	 * Check counters pointer for point valid object.
	 */
	if (counters == null) {
		//TODO Find better way for exception handling.
		return;
	}
	this.counters = counters;

	/*
	 * Check ANN pointer for point valid object.
	 */
	if (ann == null) {
		//TODO Find better way for exception handling.
		return;
	}
	this.ann = ann;

	/**
	 * Population array. Population array is dynamically allocated. Eeach
	 * member is two dimensional array (matrix of weights). Weights matrix is
	 * also dynamically allocated.
	 */
	this.population = new Population(populationSize);

	/**
	 * Indexes should be different in order DE to work.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 27 Dec 2014
	 */
	this.validIndexes = function() {
		if (trialIndex == baseIndex || trialIndex == targetIndex || trialIndex == firstIndex || trialIndex == secondIndex) {
			return false;
		}

		if (baseIndex == targetIndex || baseIndex == firstIndex || baseIndex == secondIndex) {
			return false;
		}

		if (targetIndex == firstIndex || targetIndex == secondIndex) {
			return false;
		}

		if (firstIndex == secondIndex) {
			return false;
		}

		return true;
	};

	/**
	 * Recombine chromosomes.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 31 Mar 2009
	 */
	//TODO Do it in Chromosome class.
	this.recombine = function() {
		var CR = MIN_CROSSOVER_RATE + rand() % (MAX_CROSSOVER_RATE - MIN_CROSSOVER_RATE + 1);
		var F = MIN_MUTATION_FACTOR + (MAX_MUTATION_FACTOR - MIN_MUTATION_FACTOR) * (1.0*rand() / RAND_MAX);
	
		/*
		 * Trail vector.
		 */
		trial = population.list[trialIndex].getWeights();
	
		/*
		 * Base vector.
		 */
		base = population.list[baseIndex].getWeights();
	
		/*
		 * Target vector.
		 */
		target = population.list[targetIndex].getWeights();
	
		/*
		 * First vector for the difference.
		 */
		first = population.list[firstIndex].getWeights();
	
		/*
		 * Second vector for the difference.
		 */
		second = population.list[secondIndex].getWeights();
	
		/*
		 * Size of the ANN should not be zero.
		 */
	    if(trial.dimension() <= 0) {
			//TODO Find better way for exception handling.
			return;
	    }
	
		//TODO Implement recombination as polymorphic class.
	
		/*
		 * It is a guarantee that at least one element will be crossed.
		 */
		var R = rand() % (trial.dimension() * trial.dimension());
	
	    /*
	     * Binomial crossover.
	     */
		for (var j=0, k=0; j<trial.dimension(); j++) {
			for (var i=0; i<trial.dimension(); i++, k++) {
				var ri = MIN_CROSSOVER_RATE + rand() % (MAX_CROSSOVER_RATE - MIN_CROSSOVER_RATE + 1);
	
				if (ri < CR || k == R) {
					trial(i,j) = base(i,j) + F * (first(i,j)-second(i,j));
				} else {
					trial(i,j) = target(i,j);
				}
			}
		}
	
		/*
		 * Update result chromosome. When reference is used result is already on place.
		 */
		//TODO population[trialIndex].setWeights( trial );
	};

	/**
	 * Population getter.
	 *
	 * @return Weights Population reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 19 Aug 2009
	 */
	this.getPopulation = function() {
		return population;
	};

	/**
	 * Population setter.
	 *
	 * @param population Population to set.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 20 May 2009
	 */
	this.setPopulation = function(value) {
		population = value;
	};

	/**
	 * Crossover type getter.
	 *
	 * @return Crossover type.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 11 Aug 2011
	 */
	this.getCrossoverType = function() {
	};

	/**
	 * Crossover type setter.
	 *
	 * @param type Crossover type.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 11 Aug 2011
	 */
	this.setCrossoverType = function(type) {
	};

	/**
	 * Crossover percent getter.
	 *
	 * @return Crossover probability in percent.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 11 Aug 2011
	 */
	this.getCrossoverPercent = function() {
	};

	/**
	 * Crossover percent setter.
	 *
	 * @param percent Crossover probability in percent.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 11 Aug 2011
	 */
	this.setCrossoverPercent = function(percent) {
	};

	/**
	 * Mutation percent getter.
	 *
	 * @return Mutation probability in percent.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 11 Aug 2011
	 */
	this.getMutationPercent = function() {
	};

	/**
	 * Mutation percent setter.
	 *
	 * @param percent Mutation probability in percent.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 11 Aug 2011
	 */
	this.setMutationPercent = function(percent) {
	};

	/**
	 * Evolve population. Do selection for crossover. Crossover half of the
	 * population. Mutate crossovered half of the population.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 15 May 2009
	 */
	this.evolve = function() {
		/*
		 * Estimate work done.
		 */
		if (counters != null) {
			counters.increment( "Evolution loops" );
		}
	
		/*
		 * Select trial vector index (it is used as buffer).
		 */
		//TODO Use the chromosome with the worst fitness.
		trialIndex = rand() % population.dimension();
	
		/*
		 * Evolve more chromosomes of the population (not all of them).
		 */
		for (var k=0; k<population.dimension()&&isRunning==true; k++) {
			/*
			 * Select random indivudials for crossover according selection strategy.
			 * The best chromosome is not part of the evolution to give better chances
			 * to other chromosomes to survive and to evolve.
			 */
			do {
				/*
				 * Base vector should never be equal to the trial vector. That is why k can not be used as x vector selection.
				 */
				baseIndex = rand() % population.dimension();
	
				targetIndex = rand() % population.dimension();
				firstIndex = rand() % population.dimension();
				secondIndex = rand() % population.dimension();
			} while (validIndexes() == false);
	
			/*
			 * Produce trial vector.
			 */
			recombine();
	
			/*
			 * Load chromosome's weights into ANN.
			 */
			ann.setWeights(population[trialIndex].getWeights());
	
			/*
			 * Calculate chromosome fitness by calling ANN total error calculation.
			 */
			population[ trialIndex ].setFitness( ann.totalError() );
	
			/*
			 * There is a chance total error calculation to be interrupted.
			 */
			if (isRunning == false) {
				population[trialIndex].setFitness( RAND_MAX );
			}
	
			/*
			 * Update ANN prediction.
			 */
			if (population[trialIndex].getFitness()<=population.getBestFitness() || PREDICT_WITH_EACH_CHROMOSOME==true) {
				ann.predict();
			}
	
			/*
			 * If trial vector is better than base vector than switch indexes.
			 */
			if(population[ trialIndex ].getFitness() < population[ baseIndex ].getFitness()) {
				trialIndex = baseIndex;
			}
	
			/*
			 * Update best fitness index.
			 */
			population.searchBestFitnessIndex();
		}
	};

	/*
	 * Estimate work done.
	 */
	if (counters != null) {
		counters.setValue("Population size", population.dimension());
	}
}
