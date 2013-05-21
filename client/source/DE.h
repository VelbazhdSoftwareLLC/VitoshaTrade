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

#ifndef DE_H
#define DE_H

#include <iostream>

class ANN;
class Counter;

#include "Population.h"
#include "CrossoverType.h"

/**
 * Differential Evolution.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 10 Mar 2009
 */
class DE {

public:

	/**
	 * Integer number for probability percent result of crossover to be written
	 * into the chromosome with the best fittnes. It is part of selection
	 * strategy. Sum of all possibilities should be 100.
	 */
	//TODO implement it as member variable.
	static const int CROSSOVER_RESULT_INTO_BEST_PERCENT = 5;

	/**
	 * Integer number for probability percent result of crossover to be written
	 * into the chromosome with the middle fittnes. It is part of selection
	 * strategy. Sum of all possibilities should be 100.
	 */
	//TODO implement it as member variable.
	static const int CROSSOVER_RESULT_INTO_MIDDLE_PERCENT = 40;

	/**
	 * Integer number for probability percent result of crossover to be written
	 * into the chromosome with the worst fittnes. It is part of selection
	 * strategy. Sum of all possibilities should be 100.
	 */
	//TODO implement it as member variable.
	static const int CROSSOVER_RESULT_INTO_WORST_PERCENT = 55;

	/**
	 * Flag to involve the best chromosome in evolution process.
	 */
	//TODO implement it as member variable.
	static const bool KEEP_THE_BEST_CHROMOSOME = true;

	/**
	 * Do prediction with each chromosome, not only with the best one.
	 */
	//TODO implement it as member variable.
	static const bool PREDICT_WITH_EACH_CHROMOSOME = true;

	/**
	 * Minimuim mutation factor.
	 */
	static const double MIN_MUTATION_FACTOR = 0.0;

	/**
	 * Maximum mutation factor.
	 */
	static const double MAX_MUTATION_FACTOR = 0.1;

private:

	/**
	 * Crossover type.
	 */
	//TODO Implement getter and setter.
	CrossoverType crossoverType;

	/**
	 * Probability crossover to ocure.
	 */
	//TODO Implement getter and setter.
	double crossoverPercent;

	/**
	 * Probability mutation to ocure.
	 */
	//TODO Implement getter and setter.
	double mutationPercent;

	/**
	 * Population array. Population array is dynamically allocated. Eeach
	 * member is two dimensional array (matrix of weights). Weights matrix is
	 * also dynamically allocated.
	 */
	Population population;

	/**
	 * Link to counters object.
	 */
	Counter *counters;

	/**
	 * Link to real artificial neural network object.
	 */
	ANN *ann;

private:

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
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 15 May 2009
	 */
	void select(int &resultIndex, int &firstParentIndex, int &secondParentIndex);

	/**
	 * Crossover chromosomes.
	 *
	 * @param resultIndex Index on which crossover result is stored.
	 *
	 * @param firstParentIndex Index of the first parent.
	 *
	 * @param secondParentIndex Index of the second parent.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 31 Mar 2009
	 */
	//TODO Do in in Chromosome class.
	void crossover(int resultIndex, int firstParentIndex, int secondParentIndex);

	/**
	 * Mutate chromosome.
	 *
	 * @param index Index of the chromosome which mutate.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 31 Mar 2009
	 */
	//TODO Do in in Chromosome class.
	void mutate(int index);

public:

	/**
	 * Differential evolution class constructor.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 20 Oct 2011
	 */
	DE();

	/**
	 * Differential evolution class constructor.
	 *
	 * @param de Instance to be copied.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 22 Oct 2011
	 */
	DE(const DE &de);

	/**
	 * Differential evolution class constructor.
	 *
	 * @param counters Link to real counters object.
	 *
	 * @param ann Link to artificial neural network.
	 *
	 * @param populationSize Population size to be used.
	 *
	 * @param crossoverPercent Crossover to ocure probability.
	 *
	 * @param mutationPercent Mutation to ocure probability.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 10 Mar 2009
	 */
	DE(Counter *counters, ANN *ann, int populationSize, double crossoverPercent, double mutationPercent);

	/**
	 * Population getter.
	 *
	 * @return Weights Population reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 19 Aug 2009
	 */
	Population& getPopulation();

	/**
	 * Population setter.
	 *
	 * @param population Population to set.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 20 May 2009
	 */
	void setPopulation(Population &population);

	/**
	 * Crossover type getter.
	 *
	 * @return Crossover type.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 11 Aug 2011
	 */
	CrossoverType getCrossoverType() const;

	/**
	 * Crossover type setter.
	 *
	 * @param type Crossover type.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 11 Aug 2011
	 */
	void setCrossoverType(CrossoverType type);

	/**
	 * Crossover percent getter.
	 *
	 * @return Crossover probability in percent.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 11 Aug 2011
	 */
	double getCrossoverPercent() const;

	/**
	 * Crossover percent setter.
	 *
	 * @param percent Crossover probability in percent.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 11 Aug 2011
	 */
	void setCrossoverPercent(double percent);

	/**
	 * Mutation percent getter.
	 *
	 * @return Mutation probability in percent.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 11 Aug 2011
	 */
	double getMutationPercent() const;

	/**
	 * Mutation percent setter.
	 *
	 * @param percent Mutation probability in percent.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 11 Aug 2011
	 */
	void setMutationPercent(double percent);

	/**
	 * Evolve population. Do selection for crossover. Crossover half of the
	 * population. Mutate crossovered half of the population.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 15 May 2009
	 */
	void evolve();

	/**
	 * Differential volution class destructor.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 10 Mar 2009
	 */
	virtual ~DE();

	/**
	 * Assignment operator overloading.
	 *
	 * @param de Right side DE operand.
	 *
	 * @return DE instance reference.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 22 Oct 2011
	 */
	virtual DE& operator=(const DE &de);

	friend std::ostream& operator<<(std::ostream &out, DE &de);
};

/**
 * Output operator redefinition.
 *
 * @param out Output stream.
 *
 * @param de DE instance.
 *
 * @return Output stream.
 *
 * @author Iliyan Zankinski
 *
 * @email iliyan_mf@abv.bg
 *
 * @date 23 Aug 2009
 */
std::ostream& operator<<(std::ostream &out, DE &de);

#endif
