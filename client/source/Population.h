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

#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <iostream>

#include "Chromosome.h"

/**
 * List of weights used as population class.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 05 Aug 2011
 */
class Population {

public:

	/**
	 * Minimum population size. Four is useful at each crossover and mutation to
	 * have two parents, one child and one reserved best chromosome.
	 */
	static const int MIN_POPULATION_SIZE = 4;

private:

	/**
	 * Weights list.
	 */
	std::vector<Chromosome> list;

	/**
	 * Index of the chromozome with the best fitness.
	 */
	int bestFitnessIndex;

public:

	/**
	 * Constructor without parameters.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 05 Aug 2011
	 */
	Population();

	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @param size Size of the population.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 05 Aug 2011
	 */
	Population(int size);

	/**
	 * Copy constructor.
	 *
	 * @param list Instance to be copied.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 05 Aug 2011
	 */
	Population(const Population &population);

	/**
	 * Size of neurons list getter.
	 *
	 * @return Size of neurons list.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 05 Aug 2011
	 */
	int dimension() const;

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
	double getBestFitness() const;

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
	int getBestFitnessIndex() const;

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
	bool hasDuplication(Chromosome &chromosome);

	/**
	 * Initialize population with random chromosomes.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 27 Mar 2009
	 */
	void initRandom();

	/**
	 * Search for best fitness and save it in class member variable.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 18 Aug 2009
	 */
	void searchBestFitnessIndex();

	/**
	 * Class destructor. Memory release and variables deinitialization.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 05 Aug 2011
	 */
	virtual ~Population();

	/**
	 * List elements access operator overloading.
	 *
	 * @param index Index of element.
	 *
	 * @return Constant element value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 05 Aug 2011
	 */
	Chromosome operator[](int index) const;

	/**
	 * List elements access operator overloading.
	 *
	 * @param index Index of element.
	 *
	 * @return Constant element value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 05 Aug 2011
	 */
	Chromosome& operator[](int index);

	/**
	 * Assignment operator overloading.
	 *
	 * @param population Right side operand.
	 *
	 * @return Neurons list instance reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 05 Aug 2011
	 */
	Population& operator=(const Population &population);

	friend std::ostream& operator<<(std::ostream &out, Population &population);
};

/**
 * Output operator redefinition.
 *
 * @param out Output stream reference.
 *
 * @param population Population instance reference.
 *
 * @return Output stream reference.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 05 Aug 2011
 */
std::ostream& operator<<(std::ostream &out, Population &population);

#endif
