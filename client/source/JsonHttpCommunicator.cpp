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

#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <climits>

#include "curl/curl.h"
#include "libjson/libjson.h"

#include "DE.h"
#include "ANN.h"
#include "NeuronsList.h"
#include "ActivitiesMatrix.h"
#include "TrainingExample.h"

#include "JsonHttpCommunicator.h"

#define MSG_WAITALL 0x0

const char JsonHttpCommunicator::HOST[] = "localhost";

const char JsonHttpCommunicator::LIST_OF_ANNS_SCRIPT[] = "/logic/json_number_of_anns.php";

const char JsonHttpCommunicator::SAVE_SINGLE_ANN_SCRIPT[] = "/logic/save_ann.php";

const char JsonHttpCommunicator::LOAD_NEURONS_AMOUNT_SCRIPT[] = "/logic/json_load_neurons_amount.php";

const char JsonHttpCommunicator::LOAD_SINGLE_ANN_SCRIPT[] = "/logic/json_load_ann.php";

const char JsonHttpCommunicator::LOAD_BEST_FITNESS_SCRIPT[] = "/logic/json_load_best_fitness.php";

const char JsonHttpCommunicator::TRAINING_SET_SIZE_SCRIPT[] = "/logic/json_training_set_size.php";

const char JsonHttpCommunicator::SAVE_TRAINING_SET_SCRIPT[] = "/logic/save_training_set.php";

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
		throw( "JsonHttpCommunicator00214" );
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
		throw( "JsonHttpCommunicator00215" );
	}

	curl_easy_cleanup(curl);

	memcpy(response, chunk.memory, sizeof(char)*(chunk.size+1));

	if(chunk.memory) {
		free(chunk.memory);
	}

	curl_global_cleanup();

	return(response);
}

void JsonHttpCommunicator::parseJsonLoadRemoteBestFitness(const JSONNode &node, double &fitness, const bool initialCall) {
	for(JSONNode::const_iterator i = node.begin(); i!=node.end(); ++i) {
		std::string node_name = i -> name();

		/*
		 * Store values into proper object filds.
		 */
		if (node_name == "fitness") {
			fitness = i->as_float();
		}

		/*
		 * Recursively call ourselves to dig deeper into the tree.
		 */
		if (i -> type() == JSON_ARRAY || i -> type() == JSON_NODE) {
			parseJsonLoadRemoteBestFitness(*i, fitness, false);
		}
	}
}

void JsonHttpCommunicator::parseJsonLoadAnnNeuronsAmount(const JSONNode &node, int &amount, const bool initialCall) {
	for(JSONNode::const_iterator i = node.begin(); i!=node.end(); ++i) {
		std::string node_name = i -> name();

		/*
		 * Store values into proper object filds.
		 */
		if (node_name == "neuronsAmount") {
			amount = i->as_int();
		}

		/*
		 * Recursively call ourselves to dig deeper into the tree.
		 */
		if (i -> type() == JSON_ARRAY || i -> type() == JSON_NODE) {
			parseJsonLoadAnnNeuronsAmount(*i, amount, false);
		}
	}
}

void JsonHttpCommunicator::parseJsonLoadTrainingSetSize(const JSONNode &node, int &size, const bool initialCall) {
	for(JSONNode::const_iterator i = node.begin(); i!=node.end(); ++i) {
		std::string node_name = i -> name();

		/*
		 * Store values into proper object filds.
		 */
		if (node_name == "numberOfExamples") {
			size = i->as_int();
		}

		/*
		 * Recursively call ourselves to dig deeper into the tree.
		 */
		if (i -> type() == JSON_ARRAY || i -> type() == JSON_NODE) {
			parseJsonLoadTrainingSetSize(*i, size, false);
		}
	}
}

void JsonHttpCommunicator::parseJsonLoadAnnList(const JSONNode &node, std::vector<int> &list, const bool initialCall) {
	static int size = 0;
	static int identifiersCounter = 0;
	static std::string array = "";
	if(initialCall == true) {
		size = 0;
		identifiersCounter = 0;
		array = "";
	}

	for(JSONNode::const_iterator i = node.begin(); i!=node.end(); ++i) {
		std::string node_name = i -> name();

		/*
		 * Store values into proper object filds.
		 */
		if (node_name == "size") {
			size = i->as_int();
		} else if (node_name == "identifiers") {
			array = "identifiers";
		} else if (array == "identifiers") {
			list.push_back( i->as_int() );
			identifiersCounter++;
		}

		/*
		 * Recursively call ourselves to dig deeper into the tree.
		 */
		if (i -> type() == JSON_ARRAY || i -> type() == JSON_NODE) {
			parseJsonLoadAnnList(*i, list, false);
		}
	}
}

void JsonHttpCommunicator::parseJsonLoadTrainingSet(const JSONNode &node, std::vector<RateInfo> &rates, const bool initialCall) {
	static std::string array = "";
	static int timeCounter = 0;
	static int openCounter = 0;
	static int lowCounter = 0;
	static int highCounter = 0;
	static int closeCounter = 0;
	static int volumeCounter = 0;

	for(JSONNode::const_iterator i = node.begin(); i!=node.end(); ++i) {
		std::string node_name = i -> name();

		/*
		 * Store values into proper object filds.
		 */
		if (node_name == "numberOfExamples") {
			//TODO May be it is better to clear the vector.
			//TODO Find better way to deal with the parallel arrays.
			for(int j=i->as_int(); j>0; j--) {
				//TODO Possible problems with local variables.
				rates.push_back( RateInfo() );
			}
		} else if (node_name == "time") {
			array = "time";
		} else if (node_name == "open") {
			array = "open";
		} else if (node_name == "low") {
			array = "low";
		} else if (node_name == "high") {
			array = "high";
		} else if (node_name == "close") {
			array = "close";
		} else if (node_name == "volume") {
			array = "volume";
		} else if (array == "time") {
			rates[timeCounter].time = i->as_int();
			timeCounter++;
		} else if (array == "open") {
			rates[openCounter].open = i->as_float();
			openCounter++;
		} else if (array == "low") {
			rates[lowCounter].low = i->as_float();
			lowCounter++;
		} else if (array == "high") {
			rates[highCounter].high = i->as_float();
			highCounter++;
		} else if (array == "close") {
			rates[closeCounter].close = i->as_float();
			closeCounter++;
		} else if (array == "volume") {
			rates[volumeCounter].volume = i->as_int();
			volumeCounter++;
		}

		/*
		 * Recursively call ourselves to dig deeper into the tree.
		 */
		if (i -> type() == JSON_ARRAY || i -> type() == JSON_NODE) {
			parseJsonLoadTrainingSet(*i, rates, false);
		}
	}
}

void JsonHttpCommunicator::parseJsonLoadSingleANN(const JSONNode &node, bool &available, char *symbol, TimePeriod &period, double &fitness, NeuronsList &neurons, WeightsMatrix &weights, ActivitiesMatrix &activities, const bool initialCall) {
	static int size = 0;
	static int numberOfNeurons = 0;
	static int flagsCounter = 0;
	static int weightsCounter = 0;
	static int activitiesCounter = 0;
	static std::string array = "";
	if(initialCall == true) {
		size = 0;
		numberOfNeurons = 0;
		flagsCounter = 0;
		weightsCounter = 0;
		activitiesCounter = 0;
		array = "";
	}

	if(available == false) {
		return;
	}

	for(JSONNode::const_iterator i = node.begin(); i!=node.end(); ++i) {
		std::string node_name = i -> name();

		/*
		 * Store values into proper object filds.
		 */
		if (node_name == "size") {
			size = i->as_int();
			if(size == 0) {
				available = false;
			}
		} else if (node_name == "symbol") {
			strcpy(symbol, (i->as_string()).c_str());
		} else if (node_name == "period") {
			switch (i->as_int()) {
			case 1:
				period = M1;
				break;
			case 5:
				period = M5;
				break;
			case 15:
				period = M15;
				break;
			case 30:
				period = M30;
				break;
			case 60:
				period = H1;
				break;
			case 240:
				period = H4;
				break;
			case 1440:
				period = D1;
				break;
			case 10080:
				period = W1;
				break;
			case 43200:
				period = MN1;
				break;
			default:
				period = NO;
				break;
			}
		} else if (node_name == "fitness") {
			fitness = i->as_float();
		} else if (node_name == "numberOfNeurons") {
			numberOfNeurons = i->as_int();
		} else if (node_name == "flags") {
			array = "flags";
			//TODO May be it will need to fill the data container with empty objects.
		} else if (node_name == "weights") {
			array = "weights";
			//TODO May be it will need to fill the data container with empty objects.
		} else if (node_name == "activities") {
			array = "activities";
			//TODO May be it will need to fill the data container with empty objects.
		} else if (array == "flags") {
			switch (i->as_int()) {
			case REGULAR:
				neurons[flagsCounter].setType( REGULAR );
				break;
			case BIAS:
				neurons[flagsCounter].setType( BIAS );
				break;
			case INPUT:
				neurons[flagsCounter].setType( INPUT );
				break;
			case INPUT_BIAS:
				neurons[flagsCounter].setType( INPUT_BIAS );
				break;
			case OUTPUT:
				neurons[flagsCounter].setType( OUTPUT );
				break;
			case OUTPUT_BIAS:
				neurons[flagsCounter].setType( OUTPUT_BIAS );
				break;
			case OUTPUT_INPUT:
				neurons[flagsCounter].setType( OUTPUT_INPUT );
				break;
			case OUTPUT_INPUT_BIAS:
				neurons[flagsCounter].setType( OUTPUT_INPUT_BIAS );
				break;
			default:
				neurons[flagsCounter].setType( REGULAR );
				break;
			}
			flagsCounter++;
			//TODO After reading all numbers array value should be empty string.
		} else if (array == "weights") {
			static int a = 0;
			static int b = 0;

			//TODO There is a problem with extra reading of one more zero.
			weights(a,b) = i->as_float();

			a++;
			if(a >= numberOfNeurons) {
				b++;
				a = 0;
			}

			weightsCounter++;
			//TODO After reading all numbers array value should be empty string.
		} else if (array == "activities") {
			static int a = 0;
			static int b = 0;

			//TODO There is a problem with extra reading of one more zero.
			activities(a,b) =  i->as_float();

			a++;
			if(a >= numberOfNeurons) {
				b++;
				a = 0;
			}

			activitiesCounter++;
			//TODO After reading all numbers array value should be empty string.
		}

		/*
		 * Recursively call ourselves to dig deeper into the tree.
		 */
		if (i -> type() == JSON_ARRAY || i -> type() == JSON_NODE) {
			parseJsonLoadSingleANN(*i, available, symbol, period, fitness, neurons, weights, activities, false);
		}
	}
}

void JsonHttpCommunicator::loadAnnList(std::vector<int> &list, int annId, char symbol[], TimePeriod period) {
	char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ];
	char *position = parameters;

	sprintf(position, "annid=%d&", annId);
	position += strlen(position);

	sprintf(position, "symbol=%s&", symbol);
	position += strlen(position);

	sprintf(position, "period=%d", period);
	position += strlen(position);

	HttpRequestResponse(buffer, parameters, HOST, LIST_OF_ANNS_SCRIPT);

	list.clear();
	JSONNode node = libjson::parse(buffer);
	parseJsonLoadAnnList(node, list, true);
}

int JsonHttpCommunicator::loadAnnNeuronsAmount(int annId) {
	char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ];
	sprintf(parameters, "annid=%d", annId);

	HttpRequestResponse(buffer, parameters, HOST, LOAD_NEURONS_AMOUNT_SCRIPT);

	/*
	 * Parse result.
	 */
	int amount = 0;

	JSONNode node = libjson::parse(buffer);
	parseJsonLoadAnnNeuronsAmount(node, amount, true);

	return (amount);
}

void JsonHttpCommunicator::loadTrainerObjects(Counter &counters, ANN &ann, DE &de, char symbol[], TimePeriod period, const ModelParameters &parameters) {
	std::vector<int> list(parameters.populationSize);
	int neuronsAmount = parameters.neuronsAmount;

	/*
	 * Load list with available ANNs.
	 */
	int numberOfNeurons = loadAnnNeuronsAmount(parameters.dbId);
	loadAnnList(list, parameters.dbId, symbol, period);
	if (list.size()>0 && numberOfNeurons>0) {
		neuronsAmount = numberOfNeurons;

		ANN annInstance(&counters, neuronsAmount, parameters.learn, parameters.forecast, period);
		ann = annInstance;
	} else if (list.size() == 0) {
		neuronsAmount = parameters.neuronsAmount;

		/*
		 * It is good new network to have at least neurons for input and output.
		 */
		if(neuronsAmount < (parameters.inputSize+parameters.outputSize)) {
			neuronsAmount = parameters.inputSize+parameters.outputSize;
		}

		/*
		 * Create new network if no record presented in database.
		 * Input and output neurons should be specified on network creation.
		 */
		ANN annInstance(&counters, neuronsAmount, parameters.learn, parameters.forecast, period);
		ann = annInstance;
		ann.setupInput( parameters.inputSize );
		ann.setupOutput( parameters.outputSize );
		ann.setupThreeLayers();
	}

	/* Memory allocation. */ {
		DE deInstance(&counters, &ann, parameters.populationSize);
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

	bool available = false;
	strcpy(symbol, "");
	period = NO;
	fitness = (double)RAND_MAX;

	JSONNode node = libjson::parse(buffer);
	parseJsonLoadSingleANN(node, available, symbol, period, fitness, neurons, weights, activities, true);

	if (available == false) {
		throw( "JsonHttpCommunicator00216" );
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

	JSONNode node = libjson::parse(buffer);
	parseJsonLoadTrainingSetSize(node, size, true);

	return( size );
}

void JsonHttpCommunicator::saveTrainingSet(char symbol[], TimePeriod period, const std::vector<RateInfo> &rates, int size) {
	char number[ 100 ];
	char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ] = "";
	char *position = parameters;

	size = rates.size();

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
		sprintf(number, "%ld", rates[i].time);
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

void JsonHttpCommunicator::loadTrainingSet(char symbol[], TimePeriod period, std::vector<RateInfo> &rates, int size) {
	char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ] = "";
	sprintf(parameters, "symbol=%s&period=%d", symbol, period);

	HttpRequestResponse(buffer, parameters, HOST, LOAD_TRAINING_SET_SCRIPT);

	rates.clear();
	JSONNode node = libjson::parse(buffer);
	parseJsonLoadTrainingSet(node, rates, true);
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

	JSONNode node = libjson::parse(buffer);
	parseJsonLoadRemoteBestFitness(node, bestFitness, true);

	return( bestFitness );
}
