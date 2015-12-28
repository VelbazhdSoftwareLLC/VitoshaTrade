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

#include "Chromosome.h"

const double Chromosome::LESS_OPTIMAL_FITNESS_VALUE = RAND_MAX;

const double Chromosome::MIN_INIT_RANDOM = -1.0;

const double Chromosome::MAX_INIT_RANDOM = +1.0;

Chromosome::Chromosome() {
	fitness = LESS_OPTIMAL_FITNESS_VALUE;
}

Chromosome::Chromosome(WeightsMatrix &weights, double value) {
	this->weights = weights;
	this->fitness = value;
}

Chromosome::Chromosome(const Chromosome &chromosome) {
	weights = chromosome.weights;
	fitness = chromosome.fitness;
}

WeightsMatrix& Chromosome::getWeights() {
	return( weights );
}

void Chromosome::setWeights(WeightsMatrix &weights) {
	this->weights = weights;
}

double Chromosome::getFitness() const {
	return( fitness );
}

void Chromosome::setFitness(double value) {
	this->fitness = value;
}

void Chromosome::random() {
	/*
	 * Initialize chromosome with random values.
	 */
	for (int j=0; j<weights.dimension(); j++) {
		for (int i=0; i<weights.dimension(); i++) {
			weights(i,j) = MIN_INIT_RANDOM + (MAX_INIT_RANDOM-MIN_INIT_RANDOM) * ((double)rand() / (double)RAND_MAX);
		}
	}

	fitness = rand();
}

Chromosome::~Chromosome() {
}

Chromosome& Chromosome::operator=(const Chromosome &chromosome) {
	weights = chromosome.weights;
	fitness = chromosome.fitness;

	return( *this );
}

std::ostream& operator<<(std::ostream &out, Chromosome &chromosome) {
	out << chromosome.weights;
	out << std::endl;

	out << chromosome.fitness;
	out << std::endl;

	return( out );
}
