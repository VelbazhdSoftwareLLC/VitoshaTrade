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

#ifndef TRAINING_SET_H
#define TRAINING_SET_H

#include <vector>
#include <iostream>

#include "RateInfo.h"
#include "TrainingExample.h"

/**
 * Artificial neural network training set.
 *
 * @author Todor Balabanov
 *
 * @email tdb@tbsoft.eu
 *
 * @date 31 Mar 2009
 */
class TrainingSet {
public:

	/**
	 * Floating point factor to convert from floating point to integer.
	 */
	static const double FLOATING_POINT_FACTOR = 10000.0;

public:

	/**
	 * Split number digits in separate double values. Devide each double value by 10.
	 *
	 * @param values Output values array.
	 *
	 * @param number Number to be split.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 27 May 2009
	 */
	static void splitDigits(ANNIO &values, unsigned long number);

	/**
	 * Merge number digits in sigle number value. Multiply each double value by 10.
	 *
	 * @param values Input values array.
	 *
	 * @return Merged number.
	 *
	 * @author Yasen Ivanov
	 *
	 * @email jassen@mbox.contact.bg
	 *
	 * @date 07 Jun 2009
	 */
	static double mergeDigits(ANNIO &values);

private:

	/**
	 * Array with rates.
	 */
	std::vector<RateInfo> rates;

	/**
	 * Array with training examples.
	 */
	std::vector<TrainingExample> examples;

private:

	/**
	 * Check for specific time record.
	 *
	 * @return True if time record is found, false otherwise.
	 *
	 * @author Ivan Grozev
	 *
	 * @email Ivan.Iliev.Grozev@gmail.com
	 *
	 * @date 22 May 2009
	 */
	bool isTimeFound(unsigned int time) const;

	/**
	 * Load splitted digits.
	 *
	 * @param past How many bars in the past.
	 *
	 * @param future How many bars in the future.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmail.com
	 *
	 * @date 12 Aug 2015
	 */
	void splitData(int past, int future);

public:

	/**
	 * Constructor for initial creation.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 20 Oct 2011
	 */
	TrainingSet();

	/**
	 * Constructor for initial creation.
	 *
	 * @param rates Array with rates values.
	 *
	 * @param size Size of all parallel arrays.
	 *
	 * @param past How many bars in the past.
	 *
	 * @param future How many bars in the future.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 06 Apr 2009
	 */
	TrainingSet(const std::vector<RateInfo> &rates, int size, int past, int future);

	/**
	 * Parallel arrays size getter.
	 *
	 * @return Arrays size.
	 *
	 * @author Galq Cirkalova
	 *
	 * @email galq_cirkalova@abv.bg
	 *
	 * @date 06 Apr 2009
	 */
	int getSize() const;

	/**
	 * Rates pointer getter.
	 *
	 * @return Rates pointer.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 23 Sep 2009
	 */
	std::vector<RateInfo>& getRates();

	/**
	 * Open price at index getter.
	 *
	 * @return Open price at index.
	 *
	 * @author Galq Cirkalova
	 *
	 * @email galq_cirkalova@abv.bg
	 *
	 * @date 06 Apr 2009
	 */
	double getOpen(int index);

	/**
	 * Close price at index getter.
	 *
	 * @return Close price at index.
	 *
	 * @author Galq Cirkalova
	 *
	 * @email galq_cirkalova@abv.bg
	 *
	 * @date 06 Apr 2009
	 */
	double getClose(int index);

	/**
	 * Highest price at index getter.
	 *
	 * @return Highest price at index.
	 *
	 * @author Galq Cirkalova
	 *
	 * @email galq_cirkalova@abv.bg
	 *
	 * @date 08 Apr 2009
	 */
	double getHigh(int index);

	/**
	 * Lowest price at index getter.
	 *
	 * @return Lowest price at index.
	 *
	 * @author Galq Cirkalova
	 *
	 * @email galq_cirkalova@abv.bg
	 *
	 * @date 08 Apr 2009
	 */
	double getLow(int index);

	/**
	 * UNIX time at index getter.
	 *
	 * @return UNIX time at index.
	 *
	 * @author Galq Cirkalova
	 *
	 * @email galq_cirkalova@abv.bg
	 *
	 * @date 08 Apr 2009
	 */
	unsigned int getTime(int index);

	/**
	 * Amount bars in the past from the index.
	 *
	 * @param index Starting point.
	 *
	 * @param amount How many bars in the past.
	 *
	 * @return Values of bars.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmial.com
	 *
	 * @date 12 Aug 2015
	 */
	ANNIO getBarsInPast(int index, int amount);

	/**
	 * Amount bars in the future from the index.
	 *
	 * @param index Starting point.
	 *
	 * @param amount How many bars in the future.
	 *
	 * @return Values of bars.
	 *
	 * @author Todor Balabanov
	 *
	 * @email todor.balabanov@gmial.com
	 *
	 * @date 12 Aug 2015
	 */
	ANNIO getBarsInFuture(int index, int amount);

	/**
	 * UNIX time at index pointer getter.
	 *
	 * @return UNIX time at index pointer.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 09 Sep 2009
	 */
	ANNIO& getSplittedInputed(int index);

	/**
	 * Expected value at index pointer getter.
	 *
	 * @return Expected value at index pointer.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 09 Sep 2009
	 */
	ANNIO& getSplittedExpected(int index);

	/**
	 * Predicted value at index pointer getter.
	 *
	 * @return Predicted value at index pointer.
	 *
	 * @author Todor Balabanov
	 *
	 * @email tdb@tbsoft.eu
	 *
	 * @date 09 Sep 2009
	 */
	ANNIO& getSplittedPredicted(int index);

	/**
	 * Array index at moment in time getter.
	 *
	 * @param atMoment UNIX timestamp value.
	 *
	 * @return Array index at specific time moment.
	 *
	 * @author Galq Cirkalova
	 *
	 * @email galq_cirkalova@abv.bg
	 *
	 * @date 09 Apr 2009
	 */
	int getIndexAtTime(unsigned int atMoment) const;

	/**
	 * Open price at moment in time getter.
	 *
	 * @return Open price at moment in time.
	 *
	 * @author Galq Cirkalova
	 *
	 * @email galq_cirkalova@abv.bg
	 *
	 * @date 09 Apr 2009
	 */
	double getOpen(unsigned int atMoment);

	/**
	 * Close price at moment in time getter.
	 *
	 * @return Close price at moment in time.
	 *
	 * @author Galq Cirkalova
	 *
	 * @email galq_cirkalova@abv.bg
	 *
	 * @date 09 Apr 2009
	 */
	double getClose(unsigned int atMoment);

	/**
	 * Highest price at moment in time getter.
	 *
	 * @return Highest price at moment in time.
	 *
	 * @author Galq Cirkalova
	 *
	 * @email galq_cirkalova@abv.bg
	 *
	 * @date 21 Apr 2009
	 */
	double getHigh(unsigned int atMoment);

	/**
	 * Lowest price at moment in time getter.
	 *
	 * @return Lowest price at moment in time.
	 *
	 * @author Galq Cirkalova
	 *
	 * @email galq_cirkalova@abv.bg
	 *
	 * @date 21 Apr 2009
	 */
	double getLow(unsigned int atMoment);

	/**
	 * Destructor. Free memory.
	 *
	 * @author Iliyan Zankinski
	 *
	 * @email iliyan_mf@abv.bg
	 *
	 * @date 27 Apr 2009
	 */
	virtual ~TrainingSet();

	friend std::ostream& operator<<(std::ostream &out, TrainingSet &ts);
};

/**
 * Output operator redefinition.
 *
 * @param out Output stream.
 *
 * @param ts Training set instance.
 *
 * @return Output stream.
 *
 * @author Iliyan Zankinski
 *
 * @email iliyan_mf@abv.bg
 *
 * @date 23 Aug 2009
 */
std::ostream& operator<<(std::ostream &out, TrainingSet &ts);

#endif
