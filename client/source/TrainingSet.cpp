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

#include <cstdlib>
#include <iomanip>

using namespace std;

#include "TrainingSet.h"

void TrainingSet::splitDigits(ANNIO &values, unsigned long number) {
	for (int i=values.dimension()-1; i>=0; i--) {
		values[i] = ((double)(number % 10) / 10.0);
		number /= 10;
	}
}

double TrainingSet::mergeDigits(ANNIO &values) {
	double result = 0.0;
	double multiplier = 1.0;

	/*
	 * Plus 0.5 is for rounding.
	 */
	for (int i=values.dimension()-1; i>=0; i--) {
		result += (long)(values[i]*10.0+0.5) * multiplier;
		multiplier *= 10;
	}

	return( result );
}

bool TrainingSet::isTimeFound(unsigned int time) const {
	/*
	 * Left side is the begining. Right side is the end.
	 */
	int left = 0;
	int right = rates.size()-1;
	int middle;

	/*
	 * Binary search.
	 */
	do {
		middle = (left + right) / 2;
		if (this->rates[middle].time == time) {
			return( true );
		} else if (left >= right) {
			return( false );
		} else if (time < this->rates[middle].time) {
			right = middle - 1;
		} else if (time > this->rates[middle].time) {
			left = middle + 1;
		}
	} while ( true );

	return( false );
}

void TrainingSet::splitData() {
	for (int i=0; i<rates.size(); i++) {
		splitDigits(examples[i].time, rates[i].time);

		//TODO Some mechanisum of changing predicted value should be implemented.
		splitDigits(examples[i].expected, (unsigned long)(FLOATING_POINT_FACTOR*(rates[i].open+rates[i].close)/2.0));
	}
}

TrainingSet::TrainingSet() {
	rates.clear();
	examples.clear();
}

TrainingSet::TrainingSet(const vector<RateInfo> &rates, int size) {
	/*
	 * It is not possible arrays size to be negative number.
	 */
	if (size < 0) {
		size = 0;
	}
	this->rates.clear();
	this->examples.clear();

	/*
	 * Array revers because of MetaTrader 4 data presentation.
	 */
	for (int i=0; i<size; i++) {
		this->rates.push_back( rates[size-i-1] );
		this->examples.push_back( TrainingExample() );
	}

	splitData();
}

TrainingSet::TrainingSet(const TrainingSet &set, const vector<RateInfo> &rates, int size) {
	/*
	 * It is not possible arrays size to be negative number.
	 */
	if (size < 0) {
		size = 0;
	}

	int resized = this->rates.size()+size;
	this->rates.clear();

	for (int i=0; i<resized; i++) {
		this->rates.push_back( rates[size-i-1] );
	}

	/*
	 * Merge time series.
	 * Array revers because of MetaTrader 4 data presentation.
	 */
	int k = 0;
	int j = 0;
	int i = size-1;
	for (k=0; k<resized; k++) {
		if (i<0 && j>=set.rates.size()) {
			break;
		} else if (i<0) {
			this->rates[k] = set.rates[j];

			j++;
		} else if (j>=set.rates.size()) {
			this->rates[k] = rates[i];

			i--;
		} else if (rates[i].time == set.rates[j].time) {
			this->rates[k] = rates[i];

			i--;
			j++;
		} else if (rates[i].time < set.rates[j].time) {
			this->rates[k] = rates[i];

			i--;
		} else if (rates[i].time > set.rates[j].time) {
			this->rates[k] = set.rates[j];

			j++;
		}
	}
	this->rates.resize(k);

	this->examples.clear();
	for (int i=0; i<k; i++) {
		this->examples.push_back( TrainingExample() );
	}

	splitData();
}

int TrainingSet::getSize() const {
	return( rates.size() );
}

vector<RateInfo>& TrainingSet::getRates() {
	return( rates );
}

double TrainingSet::getOpen(int index) {
	if (index >= 0 && index < rates.size()) {
		return( rates[index].open );
	} else {
		throw( "TrainingSet00086" );
		return( 0 );
	}
}

double TrainingSet::getClose(int index) {
	if (index >= 0 && index < rates.size()) {
		return( rates[index].close );
	} else {
		throw( "TrainingSet00087" );
		return( 0 );
	}
}

double TrainingSet::getHigh(int index) {
	if (index >= 0 && index < rates.size()) {
		return( rates[index].high );
	} else {
		throw( "TrainingSet00088" );
		return( 0 );
	}
}

double TrainingSet::getLow(int index) {
	if (index >= 0 && index < rates.size()) {
		return( rates[index].low );
	} else {
		throw( "TrainingSet00089" );
		return( 0 );
	}
}

unsigned int TrainingSet::getTime(int index) {
	if (index >= 0 && index < rates.size()) {
		return( rates[index].time );
	} else {
		throw( "TrainingSet00090" );
		return( 0 );
	}
}

ANNIO& TrainingSet::getSplittedTime(int index) {
	if (index >= 0 && index < rates.size()) {
		return( examples[index].time );
	} else {
		throw( "TrainingSet00125" );
	}
}

ANNIO& TrainingSet::getSplittedExpected(int index) {
	if (index >= 0 && index < rates.size()) {
		return( examples[index].expected );
	} else {
		throw( "TrainingSet00123" );
	}
}

ANNIO& TrainingSet::getSplittedPredicted(int index) {
	if (index >= 0 && index < rates.size()) {
		return( examples[index].predicted );
	} else {
		throw( "TrainingSet00124" );
	}
}

int TrainingSet::getIndexAtTime(unsigned int atMoment) const {
	/*
	 * Left side is the begining. Right side is the end.
	 */
	int left = 0;
	int right = rates.size()-1;
	int middle;

	/*
	 * Binary search.
	 */
	do {
		middle = (left + right) / 2;

		if (this->rates[middle].time == atMoment) {
			return( middle );
		} else if (left >= right) {
			return( -1 );
		} else if (atMoment < this->rates[middle].time) {
			right = middle - 1;
		} else if (atMoment > this->rates[middle].time) {
			left = middle + 1;
		}
	} while ( true );

	return( -1 );
}

double TrainingSet::getOpen(unsigned int atMoment) {
	int index = getIndexAtTime( atMoment );

	if (index >= 0) {
		return( rates[index].open );
	} else {
		throw( "TrainingSet00091" );
		return( 0 );
	}
}

double TrainingSet::getClose(unsigned int atMoment) {
	int index = getIndexAtTime( atMoment );

	if (index >= 0) {
		return( rates[index].close );
	} else {
		throw( "TrainingSet00092" );
		return( 0 );
	}
}

double TrainingSet::getHigh(unsigned int atMoment) {
	int index = getIndexAtTime( atMoment );

	if (index >= 0) {
		return( rates[index].high );
	} else {
		throw( "TrainingSet00093" );
		return( 0 );
	}
}

double TrainingSet::getLow(unsigned int atMoment) {
	int index = getIndexAtTime( atMoment );

	if ( index >= 0 ) {
		return( rates[index].low );
	} else {
		throw( "TrainingSet00094" );
		return( 0 );
	}
}

TrainingSet::~TrainingSet() {
	rates.clear();
	examples.clear();
}

ostream& operator<<(ostream &out, TrainingSet &ts) {
	out << fixed;

	out << ts.rates.size();
	out << endl;

	for (vector<RateInfo>::iterator r=ts.rates.begin(); r!=ts.rates.end(); r++) {
		out << (*r).open;
		if ((r+1)!=ts.rates.end()) {
			out << " ";
		}
	}
	out << endl;

	for (vector<RateInfo>::iterator r=ts.rates.begin(); r!=ts.rates.end(); r++) {
		out << (*r).close;
		if ((r+1)!=ts.rates.end()) {
			out << " ";
		}
	}
	out << endl;

	for (vector<RateInfo>::iterator r=ts.rates.begin(); r!=ts.rates.end(); r++) {
		out << (*r).high;
		if ((r+1)!=ts.rates.end()) {
			out << " ";
		}
	}
	out << endl;

	for (vector<RateInfo>::iterator r=ts.rates.begin(); r!=ts.rates.end(); r++) {
		out << (*r).low;
		if ((r+1)!=ts.rates.end()) {
			out << " ";
		}
	}
	out << endl;

	for (vector<RateInfo>::iterator r=ts.rates.begin(); r!=ts.rates.end(); r++) {
		out << (*r).time;
		if ((r+1)!=ts.rates.end()) {
			out << " ";
		}
	}
	out << endl;

	vector<RateInfo>::iterator r=ts.rates.begin();
	vector<TrainingExample>::iterator e=ts.examples.begin();
	for (; r!=ts.rates.end()&&e!=ts.examples.end(); r++, e++) {
		out << (*r).time;
		out << "\t";
		out << TrainingSet::mergeDigits((*e).expected);
		out << "\t";
		out << TrainingSet::mergeDigits((*e).predicted);
		if ((r+1)!=ts.rates.end() && (e+1)!=ts.examples.end()) {
			out << endl;
		}
	}
	out << endl;

	return( out );
}
