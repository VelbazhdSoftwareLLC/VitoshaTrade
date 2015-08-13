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

using namespace std;

#include "Population.h"

Population::Population() {
	list.clear();

	searchBestFitnessIndex();
}

Population::Population(int size) {
	/*
	 * DE is not working with less than minimum amount of chromosomes.
	 */
	if (size < MIN_POPULATION_SIZE) {
		size = MIN_POPULATION_SIZE;
	}

	list.clear();
	for(int i=0; i<size; i++) {
		list.push_back( Chromosome() );
	}

	searchBestFitnessIndex();
}

Population::Population(const Population &population) {
	list = population.list;

	searchBestFitnessIndex();
}

int Population::dimension() const {
	return( list.size() );
}

double Population::getBestFitness() const {
	return( list[bestFitnessIndex].getFitness() );
}

int Population::getBestFitnessIndex() const {
	return( bestFitnessIndex );
}

bool Population::hasDuplication(Chromosome &chromosome) {
	/*
	 * Check chromosome for duplication.
	 */
	for (vector<Chromosome>::iterator k=list.begin(); k!=list.end(); k++) {
		if ((*k).getFitness()==chromosome.getFitness() && (&(*k) != &chromosome)) {
			return( true );
		}
	}

	return( false );
}

void Population::initRandom() {
	for (vector<Chromosome>::iterator i=list.begin(); i!=list.end(); i++) {
		(*i).random();
	}

	searchBestFitnessIndex();
}

void Population::searchBestFitnessIndex() {
	bestFitnessIndex = 0;

	/*
	 * Best fintess is the smallest possible. Fitness is artificial neural
	 * network total error.
	 */
	for (int i=0; i<list.size(); i++) {
		if (list[i].getFitness() < list[bestFitnessIndex].getFitness()) {
			bestFitnessIndex = i;
		}
	}
}

Population::~Population() {
	list.clear();
}

Chromosome Population::operator[](int index) const {
	if (index<0 || index>=list.size()) {
		throw( "Population00204" );
	}

	return( list[index] );
}

Chromosome& Population::operator[](int index) {
	if (index<0 || index>=list.size()) {
		throw( "Population00210" );

		/*
		 * Fake object to bypass compiler.
		 */
		static Chromosome dummy;
		return( dummy );
	}

	return( list[index] );
}

Population& Population::operator=(const Population &population) {
	list = population.list;

	searchBestFitnessIndex();

	return( *this );
}

ostream& operator<<(ostream &out, Population &population) {
	out << population.list.size();
	out << endl;

	for (vector<Chromosome>::iterator i=population.list.begin(); i!=population.list.end(); i++) {
		out << (*i);
		if (i+1 != population.list.end()) {
			out << endl;
		}
	}
	out << endl;

	out << population.bestFitnessIndex;

	return( out );
}
