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

#include <cmath>
#include <climits>
#include <cstdlib>
#include <iomanip>

using namespace std;

#include "DE.h"
#include "ANN.h"
#include "Counter.h"

extern void sleep();

/*
 * Control running of the thread.
 */
extern bool isRunning;

void DE::select(int &resultIndex, int &firstParentIndex, int &secondParentIndex) {
	/*
	 * Do selection of indivuduals according probabilistic strategy.
	 */
	int index;

	/*
	 * Random value should be between 0 and sum of all percents (general 100%).
	 */
	int percent = rand() % (CROSSOVER_RESULT_INTO_WORST_PERCENT+CROSSOVER_RESULT_INTO_MIDDLE_PERCENT+CROSSOVER_RESULT_INTO_BEST_PERCENT);

	if (percent < CROSSOVER_RESULT_INTO_WORST_PERCENT) {
		/*
		 * Worst fitness value is the highest.
		 */
		if (population[resultIndex].getFitness() < population[firstParentIndex].getFitness()) {
			index = resultIndex;
			resultIndex = firstParentIndex;
			firstParentIndex = index;
		}
		if (population[resultIndex].getFitness() < population[secondParentIndex].getFitness()) {
			index = resultIndex;
			resultIndex = secondParentIndex;
			secondParentIndex = index;
		}
	} else if (percent < (CROSSOVER_RESULT_INTO_WORST_PERCENT+CROSSOVER_RESULT_INTO_MIDDLE_PERCENT)) {
		/*
		 * Middle fitness value is between the others.
		 */
		if (population[secondParentIndex].getFitness() < population[firstParentIndex].getFitness()) {
			index = secondParentIndex;
			secondParentIndex = firstParentIndex;
			firstParentIndex = index;
		}
		if (population[resultIndex].getFitness() < population[firstParentIndex].getFitness()) {
			index = resultIndex;
			resultIndex = firstParentIndex;
			firstParentIndex = index;
		}
		if (population[resultIndex].getFitness() > population[secondParentIndex].getFitness()) {
			index = resultIndex;
			resultIndex = secondParentIndex;
			secondParentIndex = index;
		}
	} else if (percent < (CROSSOVER_RESULT_INTO_WORST_PERCENT+CROSSOVER_RESULT_INTO_MIDDLE_PERCENT+CROSSOVER_RESULT_INTO_BEST_PERCENT)) {
		/*
		 * Best fitness value is the smallest.
		 */
		if (population[resultIndex].getFitness() > population[firstParentIndex].getFitness()) {
			index = resultIndex;
			resultIndex = firstParentIndex;
			firstParentIndex = index;
		}
		if (population[resultIndex].getFitness() > population[secondParentIndex].getFitness()) {
			index = resultIndex;
			resultIndex = secondParentIndex;
			secondParentIndex = index;
		}
	}
}

void DE::crossover(int resultIndex, int firstParentIndex, int secondParentIndex) {
	if (crossoverType == NONE) {
		return;
	}

	if ((double)(rand()%10000)/(double)100.0 > crossoverPercent) {
		return;
	}

	if (resultIndex < 0 || resultIndex >= population.dimension()) {
		throw( "DE00025" );
		return;
	}

	if (firstParentIndex < 0 || firstParentIndex >= population.dimension()) {
		throw( "DE00026" );
		return;
	}

	if (secondParentIndex < 0 || secondParentIndex >= population.dimension()) {
		throw( "DE00027" );
		return;
	}

	/*
	 * Get copies of the chromosomes.
	 */
	WeightsMatrix &result = population[resultIndex].getWeights();
	WeightsMatrix &first = population[firstParentIndex].getWeights();
	WeightsMatrix &second = population[secondParentIndex].getWeights();

	//TODO Implement real crossover in Chromosome class.
	if (crossoverType == RANDOM) {
		//TODO Implement crossover as polymorphic class.
		for (int j=0; j<result.dimension(); j++) {
			for (int i=0; i<result.dimension(); i++) {
				result(i,j) = (rand()%2==0) ? first(i,j) : second(i,j);
			}
		}
	} else if (crossoverType == FIFTY_FIFTY) {
		//TODO Implement crossover as polymorphic class.
		for (int j=0, k=0; j<result.dimension(); j++) {
			for (int i=0; i<result.dimension(); i++, k++) {
				if (k%2 == 0) {
					result(i,j) = first(i,j);
				} else {
					result(i,j) = second(i,j);
				}
			}
		}
	} else if (crossoverType == SINGLE_CUT) {
		//TODO Implement crossover as polymorphic class.
		int x = rand() % (result.dimension()+1);
		int y = rand() % (result.dimension()+1);

		for (int j=0; j<result.dimension(); j++) {
			for (int i=0; i<x; i++) {
				result(i,j) = first(i,j);
			}
		}

		for (int j=0; j<result.dimension(); j++) {
			if (j < y) {
				result(x,j) = first(x,j);
			} else {
				result(x,j) = second(x,j);
			}
		}

		for (int j=0; j<result.dimension(); j++) {
			for (int i=x+1; i<result.dimension(); i++) {
				result(i,j) = second(i,j);
			}
		}
	} else if (crossoverType == BINARY_MATRIX) {
		//TODO Implement crossover as polymorphic class.
		//TODO Implement binary matrix template for crossover.
	}

	/*
	 * Update result chromosome.
	 */
	population[resultIndex].setWeights( result );
}

void DE::mutate(int index) {
	if ((double)(rand()%10000)/(double)100.0 > mutationPercent) {
		return;
	}

	if (index < 0 || index >= population.dimension()) {
		throw( "DE00028" );
		return;
	}

	/*
	 * First chromosome index used in difference vector calculation.
	 */
	int firstIndex = rand() % population.dimension();

	/*
	 * Second chromosome index used in difference vector calculation.
	 */
	int secondIndex = rand() % population.dimension();

	/*
	 * Difference vector weight factor.
	 */
	double factor = MIN_MUTATION_FACTOR + (MAX_MUTATION_FACTOR - MIN_MUTATION_FACTOR) * ((double)rand() / (double)RAND_MAX);

	WeightsMatrix &result = population[index].getWeights();
	WeightsMatrix &first = population[firstIndex].getWeights();
	WeightsMatrix &second = population[secondIndex].getWeights();

	//TODO Implement real mutation in Chromosome class and send as parameter difference vector.
	/*
	 * Calculate weighted difference vector.
	 * Add weighted difference vector as mutation of chromosome.
	 */
	for (int j=0; j<result.dimension(); j++) {
		for (int i=0; i<result.dimension(); i++) {
			result(i,j) += (factor * (first(i,j) - second(i,j)));
		}
	}

	/*
	 * Update result chromosome.
	 */
	population[index].setWeights( result );
}

DE::DE() {
	/*
	 * Initialize class members.
	 */
	this->counters = NULL;
	this->ann = NULL;
	this->crossoverPercent = 0;
	this->mutationPercent = 0;

	/*
	 * Memory allocation.
	 */
	Population population( 0 );
	this->population = population;

	//TODO Implement getters and setters.
	crossoverType = RANDOM;
}

DE::DE(const DE &de) {
	this->counters = de.counters;
	this->ann = de.ann;
	this->crossoverPercent = de.crossoverPercent;
	this->mutationPercent = de.mutationPercent;
	this->population = de.population;
	this->crossoverType = de.crossoverType;
}

DE::DE(Counter *counters, ANN *ann, int populationSize, double crossoverPercent, double mutationPercent) {
	/*
	 * Check counters pointer for point valid object.
	 */
	if (counters == NULL) {
		throw( "DE00148" );
		return;
	}

	/*
	 * Check ANN pointer for point valid object.
	 */
	if (ann == NULL) {
		throw( "DE00095" );
		return;
	}

	this->counters = counters;

	/*
	 * Probability is between 0 and 100.
	 */
	if (crossoverPercent < 0.0) {
		crossoverPercent = 0.0;
	}
	if (crossoverPercent > 100.0) {
		crossoverPercent = 100.0;
	}
	if (mutationPercent < 0.0) {
		mutationPercent = 0.0;
	}
	if (mutationPercent > 100.0) {
		mutationPercent = 100.0;
	}

	/*
	 * Initialize class members.
	 */
	this->ann = ann;
	this->crossoverPercent = crossoverPercent;
	this->mutationPercent = mutationPercent;

	/*
	 * Memory allocation.
	 */
	Population population( populationSize );
	this->population = population;

	/*
	 * Check valid object internal structure.
	 */
	if (population.dimension() <= 0) {
		throw( "DE00035" );
		return;
	}

	//TODO Implement getters and setters.
	crossoverType = RANDOM;

	/*
	 * Estimate work done.
	 */
	if (counters != NULL) {
		counters->setValue("Population size", population.dimension());
	}
}

Population& DE::getPopulation() {
	return( population );
}

void DE::setPopulation(Population &population) {
	this->population = population;
}

CrossoverType DE::getCrossoverType() const {
	return( crossoverType );
}

void DE::setCrossoverType(CrossoverType type) {
	crossoverType = type;
}

double DE::getCrossoverPercent() const {
	return( crossoverPercent );
}

void DE::setCrossoverPercent(double percent) {
	crossoverPercent = percent;
}

double DE::getMutationPercent() const {
	return( mutationPercent );
}

void DE::setMutationPercent(double percent) {
	mutationPercent = percent;
}

void DE::evolve() {
	int resultIndex;
	int firstParentIndex;
	int secondParentIndex;

	/*
	 * Estimate work done.
	 */
	if (counters != NULL) {
		counters->increment( "Evolution loops" );
	}

	/*
	 * Evolve more chromosomes of the population (not all of them).
	 */
	for (int k=0; k<population.dimension()&&isRunning==true; k++) {
		/*
		 * Select random indivudials for crossover according selection strategy.
		 * The best chromosome is not part of the evolution to give better chances
		 * to other chromosomes to survive and to evolve.
		 */
		do {
			resultIndex = rand() % population.dimension();
			firstParentIndex = rand() % population.dimension();
			secondParentIndex = rand() % population.dimension();
		} while (KEEP_THE_BEST_CHROMOSOME==true && (resultIndex==population.getBestFitnessIndex() || firstParentIndex==population.getBestFitnessIndex() || secondParentIndex==population.getBestFitnessIndex()));

		/*
		 * Select which chromosome to kill.
		 */
		select(resultIndex, firstParentIndex, secondParentIndex);

		/*
		 * Crossover chromosomes.
		 */
		crossover(resultIndex, firstParentIndex, secondParentIndex);

		/*
		 * Mutate crossovered chromosome.
		 */
		mutate( resultIndex );

		/*
		 * Load chromosome's weights into ANN.
		 */
		ann->setWeights(population[resultIndex].getWeights());

		/*
		 * Calculate chromosome fitness by calling ANN total error calculation.
		 */
		population[ resultIndex ].setFitness( ann->totalError() );

		/*
		 * There is a chance total error calculation to be interrupted.
		 */
		if (isRunning == false) {
			population[resultIndex].setFitness( RAND_MAX );
		}

		/*
		 * Equal chromosomes are useless. Replace with random chromosome.
		 */
		if (population.hasDuplication( population[resultIndex] ) == true) {
			/*
			 * Back propagation training for similar chromosomes.
			 */
			population[ resultIndex ].random();
			//TODO Use backpropagation in better way.
			ann->gradient();
			population[ resultIndex ].setFitness( ann->totalError() );
		}

		/*
		 * Update ANN prediction.
		 */
		if (population[resultIndex].getFitness()<population.getBestFitness() || PREDICT_WITH_EACH_CHROMOSOME==true) {
			ann->predict();
		}

		/*
		 * Update best fitness index.
		 */
		population.searchBestFitnessIndex();

		/*
		 * Sleep for better performance.
		 */
		sleep();
	}
}

DE::~DE() {
	ann = NULL;
	counters = NULL;
}

DE& DE::operator=(const DE &de) {
	this->counters = de.counters;
	this->ann = de.ann;
	this->crossoverPercent = de.crossoverPercent;
	this->mutationPercent = de.mutationPercent;
	this->population = de.population;
	this->crossoverType = de.crossoverType;

	return( *this );
}

ostream& operator<<(ostream &out, DE &de) {
	out << fixed;

	out << de.crossoverPercent;
	out << endl;

	out << de.mutationPercent;
	out << endl;

	out << de.population;

	return( out );
}
