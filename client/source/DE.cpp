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

const bool DE::PREDICT_WITH_EACH_CHROMOSOME = true;

const double DE::MIN_MUTATION_FACTOR = 0.000;

const double DE::MAX_MUTATION_FACTOR = 0.002;

const int DE::MIN_CROSSOVER_RATE = 0;

const int DE::MAX_CROSSOVER_RATE = 10000;

bool DE::validIndexes() {
	if(trialIndex == baseIndex || trialIndex == targetIndex || trialIndex == firstIndex || trialIndex == secondIndex) {
		return false;
	}

	if(baseIndex == targetIndex || baseIndex == firstIndex || baseIndex == secondIndex) {
		return false;
	}

	if(targetIndex == firstIndex || targetIndex == secondIndex) {
		return false;
	}

	if(firstIndex == secondIndex) {
		return false;
	}

	return true;
}


void DE::recombine() {
	int CR = MIN_CROSSOVER_RATE + rand() % (MAX_CROSSOVER_RATE - MIN_CROSSOVER_RATE + 1);
	double F = MIN_MUTATION_FACTOR + (MAX_MUTATION_FACTOR - MIN_MUTATION_FACTOR) * ((double)rand() / (double)RAND_MAX);

	/*
	 * Trail vector.
	 */
	WeightsMatrix &trial = population[trialIndex].getWeights();

	/*
	 * Base vector.
	 */
	WeightsMatrix &base = population[baseIndex].getWeights();

	/*
	 * Target vector.
	 */
	WeightsMatrix &target = population[targetIndex].getWeights();

	/*
	 * First vector for the difference.
	 */
	WeightsMatrix &first = population[firstIndex].getWeights();

	/*
	 * Second vector for the difference.
	 */
	WeightsMatrix &second = population[secondIndex].getWeights();

	/*
	 * Size of the ANN should not be zero.
	 */
    if(trial.dimension() <= 0) {
		throw( "DE00219" );
		return;
    }

	//TODO Implement recombination as polymorphic class.

	/*
	 * It is a guarantee that at least one element will be crossed.
	 */
	int R = rand() % (trial.dimension() * trial.dimension());

    /*
     * Binomial crossover.
     */
	for (int j=0, k=0; j<trial.dimension(); j++) {
		for (int i=0; i<trial.dimension(); i++, k++) {
			int ri = MIN_CROSSOVER_RATE + rand() % (MAX_CROSSOVER_RATE - MIN_CROSSOVER_RATE + 1);

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
}


DE::DE() {
	/*
	 * Initialize class members.
	 */
	this->counters = NULL;
	this->ann = NULL;

	/*
	 * Memory allocation.
	 */
	Population population( 0 );
	this->population = population;
}

DE::DE(const DE &de) {
	this->counters = de.counters;
	this->ann = de.ann;
	this->population = de.population;
}

DE::DE(Counter *counters, ANN *ann, int populationSize) {
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
	 * Initialize class members.
	 */
	this->ann = ann;

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

void DE::evolve() {
	/*
	 * Estimate work done.
	 */
	if (counters != NULL) {
		counters->increment( "Evolution loops" );
	}

	/*
	 * Select trial vector index (it is used as buffer).
	 */
	//TODO Use the chromosome with the worst fitness.
	trialIndex = rand() % population.dimension();

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
		ann->setWeights(population[trialIndex].getWeights());

		/*
		 * Calculate chromosome fitness by calling ANN total error calculation.
		 */
		population[ trialIndex ].setFitness( ann->totalError() );

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
			ann->predict();
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
	this->population = de.population;

	return( *this );
}

ostream& operator<<(ostream &out, DE &de) {
	out << fixed;

	out << de.population;

	return( out );
}
