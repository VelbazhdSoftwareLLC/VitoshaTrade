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

using namespace std;

#include <ctime>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

#include "NeuronsList.h"
#include "ModelParameters.h"

#include "Trainer.h"

const char Trainer::REPORT_FILE_NAME[] = "VitoshaTradeTrainingReport.txt";

Trainer::Trainer() {
	/*
	 * At start there is no report at all.
	 */
	lastBestFitnessReportTime = 0L;

	/*
	 * Estimate work done.
	 */
	counters.setValue("Training start time seconds", clock()/CLOCKS_PER_SEC);
}

void Trainer::setup(const ModelParameters &parameters) {
	strcpy(this->symbol, parameters.symbol);
	this->period = parameters.period;

	/*
	 * At the beginning there is no training set.
	 */
	http.loadTrainingSet(symbol, period, ts.getRates(), ts.getSize());

	/*
	 * Create object structure.
	 */
	http.loadTrainerObjects(counters, ann, de, parameters.dbId, symbol, period, parameters.neuronsAmount, parameters.populationSize, parameters.bars);
	ann.setTrainingSetPointer( &ts );
}

void Trainer::updateTrainingSet(const vector<RateInfo> &rates, int size) {
	/*
	 * Do not update if there is no new data at latest known time.
	 */
	if (ts.getSize()==size && ts.getTime(ts.getSize()-1)==rates[size-1].time) {
		return;
	}

	/*
	 * Create new training set object and swap it with the old one.
	 */
	TrainingSet swap(ts, rates, size);
	ts = swap;

	/*
	 * Update ANN training set pointer.
	 */
	ann.setTrainingSetPointer( &ts );

	/*
	 * Estimate work done.
	 */
	counters.setValue("Training set size", ts.getSize());
}

void Trainer::train() {
	/*
	 * If training set is not present training can not be done.
	 */
	if (ts.getSize()==0) {
		return;
	}

	/*
	 * Run one epoche of evolution.
	 */
	de.evolve();

	/*
	 * Report best chromosome at regular time interval.
	 */
	if (time(NULL)-BEST_FITNESS_REPORT_INTERVAL > lastBestFitnessReportTime) {
		reportLocalBestFitness();
	}
}

double Trainer::predict() {
	/*
	 * If training set is not present training can not be done.
	 */
	if (ts.getSize() == 0) {
		return( 0 );
	}

	return( ann.getPrediction() );
}

void Trainer::reportLocalBestFitness() {
	/*
	 * Remote best fitness to be used as level for better result server report.
	 */
	double remoteBestFitness = (double)RAND_MAX;

	/*
	 * Get pointers needed.
	 */
	ActivitiesMatrix &activities = ann.getActivities();
	NeuronsList &neurons = ann.getNeurons();

	/*
	 * Do not handle zero size ANNs.
	 */
	if(activities.dimension()==0 || neurons.dimension()==0) {
		return;
	}

	/*
	 * Check remote best fitness.
	 */
	remoteBestFitness = http.loadRemoteBestFitness(symbol, period, neurons, activities);

	/*
	 * Load Compare remote and local best fitness value.
	 */
	Population &population = de.getPopulation();
	if (population.getBestFitness() < remoteBestFitness) {
		WeightsMatrix &weights = population[population.getBestFitnessIndex()].getWeights();

		/*
		 * Do not handle zero size ANNs.
		 */
		if(weights.dimension() > 0) {
			http.saveSingleANN(symbol, period, population.getBestFitness(), neurons, weights, activities);
			http.saveTrainingSet(symbol, period, ts.getRates(), ts.getSize());
		}
	}

	/*
	 * Mark last time checked for server best fitness.
	 */
	lastBestFitnessReportTime = time(NULL);
}

Trainer::~Trainer() {
	/*
	 * Report local best fitness value.
	 */
	reportLocalBestFitness();

	/*
	 * Estimate work done.
	 */
	counters.setValue("Training end time seconds", clock()/CLOCKS_PER_SEC);

	/*
	 * Report training results.
	 */
	if (DO_FINAL_REPORT == true) {
		ofstream out( REPORT_FILE_NAME );
		out << "================================================================================" << endl;
		out << counters << endl;
		out << "================================================================================" << endl;
		out << ann << endl;
		out << "================================================================================" << endl;
		out << de << endl;
		out << "================================================================================" << endl;
		out << ts << endl;
		out << "================================================================================" << endl;
		out.close();
	}
}
