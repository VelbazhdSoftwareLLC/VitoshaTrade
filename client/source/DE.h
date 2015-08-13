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

#ifndef DE_H
#define DE_H

#include <iostream>

class ANN;
class Counter;

#include "Population.h"
#include "CrossoverType.h"

/**
 * A basic variant of the DE algorithm works by having a population of candidate solutions (called agents). These agents are moved around in the search-space by using simple mathematical formulae to combine the positions of existing agents from the population. If the new position of an agent is an improvement it is accepted and forms part of the population, otherwise the new position is simply discarded. The process is repeated and by doing so it is hoped, but not guaranteed, that a satisfactory solution will eventually be discovered.
 *
 * Formally, let f: \Bbb{R}^n \to \Bbb{R} be the cost function which must be minimized or fitness function which must be maximized. The function takes a candidate solution as argument in the form of a vector of real numbers and produces a real number as output which indicates the fitness of the given candidate solution. The gradient of f is not known. The goal is to find a solution m for which f(m) \leq f(p) for all p in the search-space, which would mean m is the global minimum. Maximization can be performed by considering the function h := -f instead.
 *
 * Let \mathbf{x} \in \Bbb{R}^n designate a candidate solution (agent) in the population. The basic DE algorithm can then be described as follows:
 *
 * Initialize all agents \mathbf{x} with random positions in the search-space.
 * Until a termination criterion is met (e.g. number of iterations performed, or adequate fitness reached), repeat the following:
 * For each agent \mathbf{x} in the population do:
 * Pick three agents \mathbf{a},\mathbf{b}, and \mathbf{c} from the population at random, they must be distinct from each other as well as from agent \mathbf{x}
 * Pick a random index R \in \{1, \ldots, n\} (n being the dimensionality of the problem to be optimized).
 * Compute the agent's potentially new position \mathbf{y} = [y_1, \ldots, y_n] as follows:
 * For each i, pick a uniformly distributed number r_i \equiv U(0,1)
 * If r_i < \text{CR} or i = R then set y_i = a_i + F \times (b_i-c_i) otherwise set y_i = x_i
 * (In essence, the new position is outcome of binary crossover of agent \mathbf{x} with intermediate agent \mathbf{z} = \mathbf{a} + F \times (\mathbf{b}-\mathbf{c}).)
 * If f(\mathbf{y}) < f(\mathbf{x}) then replace the agent in the population with the improved candidate solution, that is, replace \mathbf{x} with \mathbf{y} in the population.
 * Pick the agent from the population that has the highest fitness or lowest cost and return it as the best found candidate solution.
 *
 * Note that F \in [0,2] is called the differential weight and \text{CR} \in [0,1] is called the crossover probability, both these parameters are selectable by the practitioner along with the population size \text{NP} \geq 4 see below. *
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 10 Mar 2009
 */
class DE {

public:

	/**
	 * Do prediction with each chromosome, not only with the best one.
	 */
	//TODO implement it as member variable.
	static const bool PREDICT_WITH_EACH_CHROMOSOME = true;

	/**
	 * Minimum mutation factor.
	 */
	static const double MIN_MUTATION_FACTOR = 0.0;

	/**
	 * Maximum mutation factor.
	 */
	static const double MAX_MUTATION_FACTOR = 2.0;

	/**
	 * Minimum crossover rate as integer number between [0-10000] instead of double number between [0.0-1.0].
	 */
	static const int MIN_CROSSOVER_RATE = 0;

	/**
	 * Maximum crossover rate as integer number between [0-10000] instead of double number between [0.0-1.0].
	 */
	static const int MAX_CROSSOVER_RATE = 10000;

private:

	/**
	 * Population array. Population array is dynamically allocated. Each
	 * member is two dimensional array (matrix of weights). Weights matrix is
	 * also dynamically allocated.
	 */
	Population population;

	/**
	 * Use one of the elements in the population as trial element. When the element is better than some other element just change the index value.
	 */
	int trialIndex;

	/**
	 * In original DE x vector is selected in a loop and each element is visited. Here we will select x random way (statistically it should not have a difference).
	 */
	int xIndex;

	/**
	 * Vector a from the original DE implementation.
	 */
	int aIndex;

	/**
	 * Vector b from the original DE implementation.
	 */
	int bIndex;

	/**
	 * Vector c from the original DE implementation.
	 */
	int cIndex;

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
	 * Indexes should be different in order DE to work.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 27 Dec 2014
	 */
	bool validIndexes();

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
	void recombine();

public:

	/**
	 * Differential evolution class constructor.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
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
	 * @email todor.balabanov@gmail.com
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
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 10 Mar 2009
	 */
	DE(Counter *counters, ANN *ann, int populationSize);

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
	Population& getPopulation();

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
	void setPopulation(Population &population);

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
	CrossoverType getCrossoverType() const;

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
	void setCrossoverType(CrossoverType type);

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
	double getCrossoverPercent() const;

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
	void setCrossoverPercent(double percent);

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
	double getMutationPercent() const;

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
	void setMutationPercent(double percent);

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
	void evolve();

	/**
	 * Differential evolution class destructor.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
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
	 * @email todor.balabanov@gmail.com
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
