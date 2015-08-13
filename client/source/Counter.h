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

#ifndef COUNTER_H
#define COUNTER_H

#include <map>
#include <iostream>

/**
 * Counter for application statistics.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 28 Sep 2009
 */
class Counter {

private:

	/**
	 * Container with counters values.
	 */
	std::map<const char*, long> counters;

public:

	/**
	 * Clear counters.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 28 Sep 2009
	 */
	void clear();

	/**
	 * Get counter value.
	 *
	 * @param key Counter key.
	 *
	 * @return Counter value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 28 Sep 2009
	 */
	long getValue(const char* key);

	/**
	 * Set counter value.
	 *
	 * @param key Counter key.
	 *
	 * @param value Counter value.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 28 Sep 2009
	 */
	void setValue(const char* key, long value);

	/**
	 * Increment counter value.
	 *
	 * @param key Counter key.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 28 Sep 2009
	 */
	void increment(const char* key);

	/**
	 * Decrement counter value.
	 *
	 * @param key Counter key.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 28 Sep 2009
	 */
	void decrement(const char* key);

	/**
	 * Access specific value.
	 *
	 * @param key Counter key.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 13 Oct 2011
	 */
	long operator[](const char* key);

	friend std::ostream& operator<<(std::ostream &out, Counter &counter);
};

/**
 * Output operator redefinition.
 *
 * @param out Output stream.
 *
 * @param counter Counters instance.
 *
 * @return Output stream.
 *
 * @author Todor Balabanov
 *
 * @email todor.balabanov@gmail.com
 *
 * @date 28 Sep 2009
 */
std::ostream& operator<<(std::ostream &out, Counter &counter);

#endif
