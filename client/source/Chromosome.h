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

#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <cstdlib>
#include <iostream>

#include "WeightsMatrix.h"

/**
 * DE chromosome class.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 05 Aug 2011
 */
class Chromosome {

public:

	/**
	 * Less optimal fitness value constant.
	 */
	static const double LESS_OPTIMAL_FITNESS_VALUE = RAND_MAX;

	/**
	 * Minimuim random initializaton value for initial chromosome values.
	 */
	static const double MIN_INIT_RANDOM = -1.0;

	/**
	 * Maximum random initializaton value for initial chromosome values.
	 */
	static const double MAX_INIT_RANDOM = +1.0;

private:

	/**
	 * Each chromosome is matrix of weights.
	 */
	WeightsMatrix weights;

	/**
	 * Chromosome fitness value. Smaller output error is better fitness for the
	 * chromosome (weights set).
	 */
	double fitness;

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
	Chromosome();

	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @param weights Set of weights.
	 *
	 * @param fintess Total ANN error as fitness value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 05 Aug 2011
	 */
	Chromosome(WeightsMatrix &weights, double fintess);

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
	Chromosome(const Chromosome &chromosome);

	/**
	 * Weights matrix getter.
	 *
	 * @return Weights matrix reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 05 Aug 2011
	 */
	WeightsMatrix& getWeights();

	/**
	 * Weights matrix setter.
	 *
	 * @param weights Weights matrix.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 05 Aug 2011
	 */
	void setWeights(WeightsMatrix &weights);

	/**
	 * Chromosome fintess value getter.
	 *
	 * @return Fitness value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 05 Aug 2011
	 */
	double getFitness() const;

	/**
	 * Chromosome fintess value setter.
	 *
	 * @param fitness Fitness value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 05 Aug 2011
	 */
	void setFitness(double fitness);

	/**
	 * Initialize chromosome with random values.
	 *
	 * @param index Chromosome index in population array.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 25 Aug 2009
	 */
	void random();

	/**
	 * Class destructor.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 22 Oct 2011
	 */
	virtual ~Chromosome();

	/**
	 * Assignment operator overloading.
	 *
	 * @param chromosome Right side operand.
	 *
	 * @return Neurons list instance reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 05 Aug 2011
	 */
	virtual Chromosome& operator=(const Chromosome &chromosome);

	friend std::ostream& operator<<(std::ostream &out, Chromosome &chromosome);
};

/**
 * Output operator redefinition.
 *
 * @param out Output stream reference.
 *
 * @param chromosome Chromosome instance reference.
 *
 * @return Output stream reference.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 05 Aug 2011
 */
std::ostream& operator<<(std::ostream &out, Chromosome &chromosome);

#endif
