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

#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <climits>

#include "curl/curl.h"
#include "libjson/libjson.h"

using namespace std;

#include "DE.h"
#include "ANN.h"
#include "NeuronsList.h"
#include "ActivitiesMatrix.h"
#include "TrainingExample.h"

#include "JsonHttpCommunicator.h"

//TODO Remove this object. It was used only to compile JSON library.
JSONNode node = libjson::parse("");

#define MSG_WAITALL 0x0

const char JsonHttpCommunicator::HOST[] = "localhost";

const char JsonHttpCommunicator::LIST_OF_ANNS_SCRIPT[] = "/logic/json_number_of_anns.php";

const char JsonHttpCommunicator::SAVE_SINGLE_ANN_SCRIPT[] = "/logic/json_save_ann.php";

const char JsonHttpCommunicator::LOAD_NEURONS_AMOUNT_SCRIPT[] = "/logic/json_load_neurons_amount.php";

const char JsonHttpCommunicator::LOAD_SINGLE_ANN_SCRIPT[] = "/logic/json_load_ann.php";

const char JsonHttpCommunicator::LOAD_BEST_FITNESS_SCRIPT[] = "/logic/json_load_best_fitness.php";

const char JsonHttpCommunicator::TRAINING_SET_SIZE_SCRIPT[] = "/logic/json_training_set_size.php";

const char JsonHttpCommunicator::SAVE_TRAINING_SET_SCRIPT[] = "/logic/json_save_training_set.php";

const char JsonHttpCommunicator::LOAD_TRAINING_SET_SCRIPT[] = "/logic/json_load_training_set.php";

struct MemoryStruct {
	char *memory;
	size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if(mem->memory == NULL) {
		return 0;
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

const char* JsonHttpCommunicator::HttpRequestResponse(char *response, const char* fields, const char* host, const char* script) {
	CURL *curl;
	CURLcode result;

	struct MemoryStruct chunk;
	chunk.memory = (char*)malloc(1);
	chunk.size = 0;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();

	if(curl == NULL) {
		throw( "JsonHttpCommunicator00___" );
	}

	sprintf(buffer, "http://%s%s", host, script);
	curl_easy_setopt(curl, CURLOPT_URL, buffer);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(fields));

	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)(&chunk));
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

 	result = curl_easy_perform(curl);

	if(result != CURLE_OK) {
		throw( "JsonHttpCommunicator00___" );
	}

	curl_easy_cleanup(curl);

	memcpy(response, chunk.memory, sizeof(char)*(chunk.size+1));

	if(chunk.memory) {
		free(chunk.memory);
	}

	curl_global_cleanup();

	return(response);
}

void JsonHttpCommunicator::loadAnnList(vector<int> &list, int annId, char symbol[], TimePeriod period) {
	char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ];
	char *position = parameters;

	sprintf(position, "annid=%d&", annId);
	position += strlen(position);

	sprintf(position, "symbol=%s&", symbol);
	position += strlen(position);

	sprintf(position, "period=%d", period);
	position += strlen(position);

	HttpRequestResponse(buffer, parameters, HOST, LIST_OF_ANNS_SCRIPT);

	//TODO Use JSON parser to extract response information.
}

int JsonHttpCommunicator::loadAnnNeuronsAmount(int annId) {
	char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ];
	sprintf(parameters, "annid=%d", annId);

	HttpRequestResponse(buffer, parameters, HOST, LOAD_NEURONS_AMOUNT_SCRIPT);

	/*
	 * Parse result.
	 */
	int amout = 0;

	//TODO Use JSON parser to extract response information.

	return (amout);
}

void JsonHttpCommunicator::loadTrainerObjects(Counter &counters, ANN &ann, DE &de, char symbol[], TimePeriod period, const ModelParameters &parameters) {
	vector<int> list(parameters.populationSize);
	int neuronsAmount = parameters.neuronsAmount;

	/*
	 * Load list with available ANNs.
	 */
	int numberOfNeurons = loadAnnNeuronsAmount(parameters.dbId);
	loadAnnList(list, parameters.dbId, symbol, period);
	if (list.size()>0 && numberOfNeurons>0) {
		neuronsAmount = numberOfNeurons;

		ANN annInstance(&counters, neuronsAmount, parameters.learn, parameters.bars, period);
		ann = annInstance;
	} else if (list.size() == 0) {
		/*
		 * It is good new network to have at least neurons for input and output.
		 */
		if(neuronsAmount < (TrainingExample::NUMBER_OF_INPUT_SPLIT_DIGITS+TrainingExample::NUMBER_OF_OUTPUT_SPLIT_DIGITS)) {
			neuronsAmount = TrainingExample::NUMBER_OF_INPUT_SPLIT_DIGITS + TrainingExample::NUMBER_OF_OUTPUT_SPLIT_DIGITS;
		}

		/*
		 * Create new network if no record presented in database.
		 * Input and output neurons should be specified on network creation.
		 */
		ANN annInstance(&counters, neuronsAmount, parameters.learn, parameters.bars, period);
		ann = annInstance;
		ann.setupInput( TrainingExample::NUMBER_OF_INPUT_SPLIT_DIGITS );
		ann.setupOutput( TrainingExample::NUMBER_OF_OUTPUT_SPLIT_DIGITS );
	}

	/* Memory allocation. */ {
		DE deInstance(&counters, &ann, parameters.populationSize, 90.0, 90.0);
		de = deInstance;
	}

	/*
	 * Load DE with random values. It is useful in new ANN and DE creation.
     * Internal size of chromosomes should be given before initialization.
     */
	Population &population = de.getPopulation();
    for(int i=0; i<population.dimension(); i++) {
        WeightsMatrix weights( ann.getNeurons().dimension() );
        Chromosome chromosome(weights, (double)RAND_MAX);
        population[i] = chromosome;
    }
    //TODO Find better way to initialize random population with proper size of weight matrices.
	population.initRandom();
    //TODO This setter call may be is not needed.
	de.setPopulation( population );

	/*
	 * Load DB ANNs.
	 */
	double fitness = (double)RAND_MAX;
	NeuronsList &neurons = ann.getNeurons();
	ActivitiesMatrix &activities = ann.getActivities();
	if (list.size()>0 && neurons.dimension()>0 && neurons.dimension()==neuronsAmount) {
		Population &population = de.getPopulation();
		for (int i=0; i<list.size(); i++) {
			WeightsMatrix &weights = population[i].getWeights();
			//TODO Activities, symbol, period, number of neurons and flags can be loaded only once.
			loadSingleANN(list[i], symbol, period, fitness, neurons, weights, activities);
			population[i].setFitness( fitness );
			population[i].setWeights( weights );
		}
		de.setPopulation( population );
	}
}

void JsonHttpCommunicator::saveSingleANN(char *symbol, TimePeriod period, double fitness, NeuronsList &neurons, WeightsMatrix &weights, ActivitiesMatrix &activities) {
	char number[ 100 ];
	char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ] = "";
	char *position = parameters;

	sprintf(position, "symbol=%s&", symbol);
	position += strlen(position);

	sprintf(position, "period=%d&", period);
	position += strlen(position);

	sprintf(position, "fitness=%lf&", fitness);
	position += strlen(position);

	sprintf(position, "number_of_neurons=%d&", neurons.dimension());
	position += strlen(position);

	strcpy(buffer, "");
	for (int i=0; i<neurons.dimension(); i++) {
		if (i > 0) {
			strcat(buffer, " ");
		}
		sprintf(number, "%d", neurons[i].getType());
		strcat(buffer, number);
	}
	sprintf(position, "flags=%s&", buffer);
	position += strlen(position);

	strcpy(buffer, "");
	for (int j=0; j<neurons.dimension(); j++) {
		if (j > 0) {
			strcat(buffer, "\n");
		}
		for (int i=0; i<neurons.dimension(); i++) {
			if (i > 0) {
				strcat(buffer, " ");
			}
			sprintf(number, "%lf", weights(i,j));
			strcat(buffer, number);
		}
	}
	sprintf(position, "weights=%s&", buffer);
	position += strlen(position);

	strcpy(buffer, "");
	for (int j=0; j<neurons.dimension(); j++) {
		if (j > 0) {
			strcat(buffer, "\n");
		}
		for (int i=0; i<neurons.dimension(); i++) {
			if (i > 0) {
				strcat(buffer, " ");
			}
			sprintf(number, "%lf", activities(i,j));
			strcat(buffer, number);
		}
	}
	sprintf(position, "activities=%s", buffer);
	position += strlen(position);

	HttpRequestResponse(buffer, parameters, HOST, SAVE_SINGLE_ANN_SCRIPT);
}

void JsonHttpCommunicator::loadSingleANN(int annId, char *symbol, TimePeriod &period, double &fitness, NeuronsList &neurons, WeightsMatrix &weights, ActivitiesMatrix &activities) {
	char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ] = "";
	sprintf(parameters, "annid=%d", annId);

	HttpRequestResponse(buffer, parameters, HOST, LOAD_SINGLE_ANN_SCRIPT);

	int available = 0;
	//TODO Use JSON parser to extract response information.

	if (available == 0) {
		throw( "JsonHttpCommunicator00___" );
	}
}

int JsonHttpCommunicator::loadTrainingSetSize(char *symbol, TimePeriod period) {
	char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ] = "";
	sprintf(parameters, "symbol=%s&period=%d", symbol, period);

	HttpRequestResponse(buffer, parameters, HOST, TRAINING_SET_SIZE_SCRIPT);

	/*
	 * Parse result.
	 */
	int size = 0;
	//TODO Use JSON parser to extract response information.

	return( size );
}

void JsonHttpCommunicator::saveTrainingSet(char symbol[], TimePeriod period, const vector<RateInfo> &rates, int size) {
	char number[ 100 ];
	char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ] = "";
	char *position = parameters;

	sprintf(position, "symbol=%s&", symbol);
	position += strlen(position);

	sprintf(position, "period=%d&", period);
	position += strlen(position);

	sprintf(position, "number_of_examples=%d&", size);
	position += strlen(position);

	strcpy(buffer, "");
	for (int i=0; i<size; i++) {
		if (i > 0) {
			strcat(buffer, " ");
		}
		sprintf(number, "%d", rates[i].time);
		strcat(buffer, number);
	}
	sprintf(position, "time=%s&", buffer);
	position += strlen(position);

	strcpy(buffer, "");
	for (int i=0; i<size; i++) {
		if (i > 0) {
			strcat(buffer, " ");
		}
		sprintf(number, "%lf", rates[i].open);
		strcat(buffer, number);
	}
	sprintf(position, "open=%s&", buffer);
	position += strlen(position);

	strcpy(buffer, "");
	for (int i=0; i<size; i++) {
		if (i > 0) {
			strcat(buffer, " ");
		}
		sprintf(number, "%lf", rates[i].low);
		strcat(buffer, number);
	}
	sprintf(position, "low=%s&", buffer);
	position += strlen(position);

	strcpy(buffer, "");
	for (int i=0; i<size; i++) {
		if (i > 0) {
			strcat(buffer, " ");
		}
		sprintf(number, "%lf", rates[i].high);
		strcat(buffer, number);
	}
	sprintf(position, "high=%s&", buffer);
	position += strlen(position);

	strcpy(buffer, "");
	for (int i=0; i<size; i++) {
		if (i > 0) {
			strcat(buffer, " ");
		}
		sprintf(number, "%lf", rates[i].close);
		strcat(buffer, number);
	}
	sprintf(position, "close=%s&", buffer);
	position += strlen(position);

	strcpy(buffer, "");
	for (int i=0; i<size; i++) {
		if (i > 0) {
			strcat(buffer, " ");
		}
		sprintf(number, "%lf", rates[i].volume);
		strcat(buffer, number);
	}
	sprintf(position, "volume=%s", buffer);
	position += strlen(position);

	HttpRequestResponse(buffer, parameters, HOST, SAVE_TRAINING_SET_SCRIPT);
}

void JsonHttpCommunicator::loadTrainingSet(char symbol[], TimePeriod period, vector<RateInfo> &rates, int size) {
	char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ] = "";
	sprintf(parameters, "symbol=%s&period=%d", symbol, period);

	HttpRequestResponse(buffer, parameters, HOST, LOAD_TRAINING_SET_SCRIPT);

	//TODO Use JSON parser to extract response information.
}

double JsonHttpCommunicator::loadRemoteBestFitness(char *symbol, TimePeriod period, NeuronsList &neurons, ActivitiesMatrix &activities) {
	char number[ 100 ];
	char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ] = "";
	char *position = parameters;

	sprintf(position, "symbol=%s&", symbol);
	position += strlen(position);

	sprintf(position, "period=%d&", period);
	position += strlen(position);

	sprintf(position, "number_of_neurons=%d&", neurons.dimension());
	position += strlen(position);

	strcpy(buffer, "");
	for (int i=0; i<neurons.dimension(); i++) {
		if (i > 0) {
			strcat(buffer, " ");
		}
		sprintf(number, "%d", neurons[i].getType());
		strcat(buffer, number);
	}
	sprintf(position, "flags=%s&", buffer);
	position += strlen(position);

	strcpy(buffer, "");
	for (int j=0; j<neurons.dimension(); j++) {
		if (j > 0) {
			strcat(buffer, "\n");
		}
		for (int i=0; i<neurons.dimension(); i++) {
			if (i > 0) {
				strcat(buffer, " ");
			}
			sprintf(number, "%lf", activities(i,j));
			strcat(buffer, number);
		}
	}
	sprintf(position, "activities=%s", buffer);
	position += strlen(position);
	strcpy(buffer, "");

	HttpRequestResponse(buffer, parameters, HOST, LOAD_BEST_FITNESS_SCRIPT);

	double bestFitness = (double)RAND_MAX;
	//TODO Use JSON parser to extract response information.

	return( bestFitness );
}
