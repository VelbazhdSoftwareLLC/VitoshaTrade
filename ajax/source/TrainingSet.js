/*******************************************************************************
 *                                                                             *
 * VitoshaTrade is Distributed Artificial Neural Network trained by            *
 * Differential Evolution for prediction of Forex. Project development is in   *
 * Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   *
 * the capital of Bulgaria.                                                    *
 *                                                                             *
 * Copyright (C) 2008-2011 by Todor Balabanov  ( tdb@tbsoft.eu )               *
 *                            Iliyan Zankinski ( iliyan_mf@abv.bg )            *
 *                            Galq Cirkalova   ( galq_cirkalova@abv.bg )       *
 *                            Ivan Grozev      ( ivan.iliev.grozev@gmail.com ) *
 *                            Daniel Chutrov   ( d.chutrov@gmail.com )         *
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

/**
 * Artificial neural network training set.
 *
 * @author Daniel Chutrov
 *
 * @email d.chutrov@gmail.com
 *
 * @date 19 Dec 2010
 */
function TrainingSet(rates, size, past, future) {

	/**
	 * Floating point factor to convert from floating point to integer.
	 */
	const FLOATING_POINT_FACTOR = 10000.0;

	/*
	 * It is not possible arrays size to be negative number.
	 */
	if (size < 0) {
		size = 0;
	}

	/**
	 * Array with training examples.
	 */
	this.rates = new Array(size);

	/**
	 * Array with training examples.
	 */
	this.examples = new Array(size);

	/**
	 * Array with rates.
	 */
	for ( i = 0; i < size; i++) {
		this.rates[i] = rates[size - i - 1];
		this.examples[i] = new TrainingExample();
	}

	//TODO splitData(past, future);

	/**
	 * Split number digits in separate double values. Devide each double value by 10.
	 *
	 * @param values Output values array.
	 *
	 * @param size Available array cells for number splitting.
	 *
	 * @param number Number to be split.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 23 Dec 2010
	 */
	this.splitDigits = function(values, size, number) {
		for (var i = size - 1; i >= 0; i--) {
			values[i] = ((number % 10) / 10.0);
			number /= 10;
		}
	}
	/**
	 * Merge number digits in sigle number value. Multiply each double value by 10.
	 *
	 * @param values Input values array.
	 *
	 * @param size Array cells of number to merge.
	 *
	 * @return Merged number.
	 *
	 * @author Daniel Chutrov
	 *
	 * @email d.chutrov@gmail.com
	 *
	 * @date 23 Dec 2010
	 */
	this.mergeDigits = function(values, size) {
		var result = 0.0;
		var multiplier = 1.0;

		/*
		 * Plus 0.5 is for rounding.
		 */
		for (var i = size - 1; i >= 0; i--) {
			result += Math.floor((values[i] * 10.0 + 0.5) * multiplier);
			multiplier *= 10;
		}

		return (result );
	}
	//	/**
	//	 * Check for specific time record.
	//	 *
	//	 * @return True if time record is found, false otherwise.
	//	 *
	//	 * @author Daniel Chutrov
	//	 *
	//	 * @email d.chutrov@gmail.com
	//	 *
	//	 * @date 23 Dec 2010
	//	 */
	//	this.isTimeFound = function(time) {
	//		/*
	//		 * Left side is the begining. Right side is the end.
	//		 */
	//		var left = 0;
	//		var right = size-1;
	//		var middle;
	//
	//		/*
	//		 * Binary search.
	//		 */
	//		do {
	//			middle = (left + right) / 2;
	//			if (this.rates[middle].time == time) {
	//				return( true );
	//			} else if (left >= right) {
	//				return( false );
	//			} else if (time < this.rates[middle].time) {
	//				right = middle - 1;
	//			} else if (time > this.rates[middle].time) {
	//				left = middle + 1;
	//			}
	//		} while ( true );
	//
	//		return( false );
	//	}
	//
	//	/**
	//	 * Load splitted digits.
	//	 *
	//	 * @author Daniel Chutrov
	//	 *
	//	 * @email d.chutrov@gmail.com
	//	 *
	//	 * @date 20 Dec 2010
	//	 */
	//	this.splitData = function() {
	//		for (var i=0; i<size; i++) {
	//			splitDigits(examples[i].time, examples.NUMBER_OF_INPUT_SPLIT_DIGITS, rates[i].time);
	//
	//			//TODO Some mechanisum of changing predicted value should be implemented.
	//			splitDigits(examples[i].expected, examples.NUMBER_OF_OUTPUT_SPLIT_DIGITS, (FLOATING_POINT_FACTOR*(rates[i].open+rates[i].close)/2.0));
	//		}
	//	}
}
