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

using namespace std;

#include "DE.h"
#include "ANN.h"
#include "NeuronsList.h"
#include "ActivitiesMatrix.h"
#include "TrainingExample.h"

#include "HttpCommunicator.h"

#define MSG_WAITALL 0x0

const char HttpCommunicator::HOST[] = "localhost";

const char HttpCommunicator::LIST_OF_ANNS_SCRIPT[] = "/logic/number_of_anns.php";

const char HttpCommunicator::SAVE_SINGLE_ANN_SCRIPT[] = "/logic/save_ann.php";

const char HttpCommunicator::LOAD_NEURONS_AMOUNT_SCRIPT[] = "/logic/load_neurons_amount.php";

const char HttpCommunicator::LOAD_SINGLE_ANN_SCRIPT[] = "/logic/load_ann.php";

const char HttpCommunicator::LOAD_BEST_FITNESS_SCRIPT[] = "/logic/load_best_fitness.php";

const char HttpCommunicator::TRAINING_SET_SIZE_SCRIPT[] = "/logic/training_set_size.php";

const char HttpCommunicator::SAVE_TRAINING_SET_SCRIPT[] = "/logic/save_training_set.php";

const char HttpCommunicator::LOAD_TRAINING_SET_SCRIPT[] = "/logic/load_training_set.php";

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

void HttpCommunicator::loadAnnList(vector<int> &list, int annId, char symbol[], TimePeriod period) {
	// SOCKADDR_IN address;
	// SOCKET client;
	// WSADATA data;

	// if (WSAStartup(MAKEWORD(1,1), &data) != 0) {
		// throw( "HttpCommunicator00043" );
		// return;
	// }

	// struct hostent *host = gethostbyname( HOST );
	// if (host == NULL) {
		// WSACleanup();
		// throw( "HttpCommunicator00044" );
		// return;
	// }

	// client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// if (client == INVALID_SOCKET) {
		// WSACleanup();
		// throw( "HttpCommunicator00045" );
		// return;
	// }

	// memset(&address, 0, sizeof(address));
	// address.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	// address.sin_family = AF_INET;
	// address.sin_port = htons( PORT );

	// if (connect(client, (LPSOCKADDR)&address, sizeof(address)) != 0) {
		// closesocket( client );
		// WSACleanup();
		// throw( "HttpCommunicator00046" );
		// return;
	// }

	// char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ];
	// char *position = parameters;

	// sprintf(position, "annid=%d&", annId);
	// position += strlen(position);

	// sprintf(position, "symbol=%s&", symbol);
	// position += strlen(position);

	// sprintf(position, "period=%d", period);
	// position += strlen(position);

	// sprintf(buffer, "POST %s HTTP/1.0\nHost: %s\r\nContent-Length: %d\r\nConnection: Keep-Alive\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s\r\n", LIST_OF_ANNS_SCRIPT, HOST, strlen(parameters), parameters);
	// if (send(client, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
		// closesocket( client );
		// WSACleanup();
		// throw( "HttpCommunicator00047" );
		// return;
	// }

	// position = buffer;
	// int result = 0;
	// int numberOfBytes = 0;
	// do {
		// result = recv(client, position, BUFFER_SIZE-numberOfBytes-1, MSG_WAITALL);
		// if (result == SOCKET_ERROR) {
			// closesocket( client );
			// WSACleanup();
			// throw( "HttpCommunicator00048" );
			// return;
		// } else {
			// numberOfBytes += result;
			// position = buffer + numberOfBytes;
		// }
	// } while(result > 0);
	// buffer[ numberOfBytes ] = '\0';

	// /*
	 // * Separate HTTP header from HTTP body.
	 // */
	// position = strstr(buffer, "\r\n\r\n");

	// /*
	 // * Parse list size.
	 // */
	// position = strtok(position, " \r\n");
	// int numberOfIds = 0;
	// if(position-buffer < numberOfBytes) {
		// sscanf(position, "%d", &numberOfIds);
	// }

	// /*
	 // * Parse list values and limit it to the size of output array.
	 // */
	// int i = 0;
	// int value = 0;
	// for (i=0; i<numberOfIds&&i<list.size(); i++) {
		// list[i] = 0;
		// position = strtok(NULL, " \r\n");
		// if(position-buffer < numberOfBytes) {
			// sscanf(position, "%d", &value);
		// }
		// list[i] = value;
	// }

	// /*
	 // * Resize list if there are less available ANNs.
	 // */
	// if(i < list.size()) {
		// list.resize( i );
	// }

	// closesocket( client );
	// WSACleanup();
}

int HttpCommunicator::loadAnnNeuronsAmount(int annId) {
	char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ];
	sprintf(parameters, "annid=%d", annId);

	CURLcode result;
	CURL *curl;

	struct MemoryStruct chunk;
	chunk.memory = (char*)malloc(1);
	chunk.size = 0;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();

	if(curl == NULL) {
		// TODO Exception handling should be done.
	}

	sprintf(buffer, "http://%s/%s", HOST, LOAD_NEURONS_AMOUNT_SCRIPT);
	curl_easy_setopt(curl, CURLOPT_URL, buffer);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(parameters));

	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)(&chunk));
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

 	result = curl_easy_perform(curl);

	if(result != CURLE_OK) {
		// TODO Exception handling should be done.
	}

	/*
	 * Parse result.
	 */
	int amout = 0;
	char *position = chunk.memory;
	// TODO May be command should be like this: sscanf(position, "\n\n%d", &result);
	sscanf(position, "%d", &amout);

	curl_easy_cleanup(curl);

	if(chunk.memory) {
		free(chunk.memory);
	}

	curl_global_cleanup();

	return (amout);
}

void HttpCommunicator::loadTrainerObjects(Counter &counters, ANN &ann, DE &de, int dbId, char symbol[], TimePeriod period, int neuronsAmount, int populationSize, int bars) {
	// vector<int> list(populationSize);

	// /*
	 // * Load list with available ANNs.
	 // */
	// int numberOfNeurons = loadAnnNeuronsAmount(dbId);
	// loadAnnList(list, dbId, symbol, period);
	// if (list.size()>0 && numberOfNeurons>0) {
		// neuronsAmount = numberOfNeurons;

		// ANN annInstance(&counters, neuronsAmount, bars, period);
		// ann = annInstance;
	// } else if (list.size() == 0) {
		// /*
		 // * It is good new network to have at least neurons for input and output.
		 // */
		// if(neuronsAmount < (TrainingExample::NUMBER_OF_INPUT_SPLIT_DIGITS+TrainingExample::NUMBER_OF_OUTPUT_SPLIT_DIGITS)) {
			// neuronsAmount = TrainingExample::NUMBER_OF_INPUT_SPLIT_DIGITS + TrainingExample::NUMBER_OF_OUTPUT_SPLIT_DIGITS;
		// }

		// /*
		 // * Create new network if no record presented in database.
		 // * Input and output neurons should be specified on network creation.
		 // */
		// ANN annInstance(&counters, neuronsAmount, bars, period);
		// ann = annInstance;
		// ann.setupInput( TrainingExample::NUMBER_OF_INPUT_SPLIT_DIGITS );
		// ann.setupOutput( TrainingExample::NUMBER_OF_OUTPUT_SPLIT_DIGITS );
	// }

	// /* Memory allocation. */ {
		// DE deInstance(&counters, &ann, populationSize, 90.0, 90.0);
		// de = deInstance;
	// }

	// /*
	 // * Load DE with random values. It is useful in new ANN and DE creation.
     // * Internal size of chromosomes should be given before initialization.
     // */
	// Population &population = de.getPopulation();
    // for(int i=0; i<population.dimension(); i++) {
        // WeightsMatrix weights( ann.getNeurons().dimension() );
        // Chromosome chromosome(weights, (double)RAND_MAX);
        // population[i] = chromosome;
    // }
    // TODO Find better way to initialize random population with proper size of weight matrices.
	// population.initRandom();
    // TODO This setter call may be is not needed.
	// de.setPopulation( population );

	// /*
	 // * Load DB ANNs.
	 // */
	// double fitness = (double)RAND_MAX;
	// NeuronsList &neurons = ann.getNeurons();
	// ActivitiesMatrix &activities = ann.getActivities();
	// if (list.size()>0 && neurons.dimension()>0 && neurons.dimension()==neuronsAmount) {
		// Population &population = de.getPopulation();
		// for (int i=0; i<list.size(); i++) {
			// WeightsMatrix &weights = population[i].getWeights();
			// TODO Activities, symbol, period, number of neurons and flags can be loaded only once.
			// loadSingleANN(list[i], symbol, period, fitness, neurons, weights, activities);
			// population[i].setFitness( fitness );
			// population[i].setWeights( weights );
		// }
		// de.setPopulation( population );
	// }
}

void HttpCommunicator::saveSingleANN(char *symbol, TimePeriod period, double fitness, NeuronsList &neurons, WeightsMatrix &weights, ActivitiesMatrix &activities) {
	// SOCKADDR_IN address;
	// SOCKET client;
	// WSADATA data;

	// if (WSAStartup(MAKEWORD(1,1), &data) != 0) {
		// throw( "HttpCommunicator00055" );
		// return;
	// }

	// struct hostent *host = gethostbyname( HOST );
	// if (host == NULL) {
		// WSACleanup();
		// throw( "HttpCommunicator00056" );
		// return;
	// }

	// client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// if (client == INVALID_SOCKET) {
		// WSACleanup();
		// throw( "HttpCommunicator00057" );
		// return;
	// }

	// memset(&address, 0, sizeof(address));
	// address.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	// address.sin_family = AF_INET;
	// address.sin_port = htons( PORT );

	// if (connect(client, (LPSOCKADDR)&address, sizeof(address)) != 0) {
		// closesocket( client );
		// WSACleanup();
		// throw( "HttpCommunicator00058" );
		// return;
	// }

	// char number[ 100 ];
	// char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ] = "";
	// char *position = parameters;

	// sprintf(position, "symbol=%s&", symbol);
	// position += strlen(position);

	// sprintf(position, "period=%d&", period);
	// position += strlen(position);

	// sprintf(position, "fitness=%lf&", fitness);
	// position += strlen(position);

	// sprintf(position, "number_of_neurons=%d&", neurons.dimension());
	// position += strlen(position);

	// strcpy(buffer, "");
	// for (int i=0; i<neurons.dimension(); i++) {
		// if (i > 0) {
			// strcat(buffer, " ");
		// }
		// sprintf(number, "%d", neurons[i].getType());
		// strcat(buffer, number);
	// }
	// sprintf(position, "flags=%s&", buffer);
	// position += strlen(position);

	// strcpy(buffer, "");
	// for (int j=0; j<neurons.dimension(); j++) {
		// if (j > 0) {
			// strcat(buffer, "\n");
		// }
		// for (int i=0; i<neurons.dimension(); i++) {
			// if (i > 0) {
				// strcat(buffer, " ");
			// }
			// sprintf(number, "%lf", weights(i,j));
			// strcat(buffer, number);
		// }
	// }
	// sprintf(position, "weights=%s&", buffer);
	// position += strlen(position);

	// strcpy(buffer, "");
	// for (int j=0; j<neurons.dimension(); j++) {
		// if (j > 0) {
			// strcat(buffer, "\n");
		// }
		// for (int i=0; i<neurons.dimension(); i++) {
			// if (i > 0) {
				// strcat(buffer, " ");
			// }
			// sprintf(number, "%lf", activities(i,j));
			// strcat(buffer, number);
		// }
	// }
	// sprintf(position, "activities=%s", buffer);
	// position += strlen(position);

	// sprintf(buffer, "POST %s HTTP/1.0\nHost: %s\r\nContent-Length: %d\r\nConnection: Keep-Alive\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s\r\n", SAVE_SINGLE_ANN_SCRIPT, HOST, strlen(parameters), parameters);
	// if (send(client, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
		// closesocket( client );
		// WSACleanup();
		// throw( "HttpCommunicator00059" );
		// return;
	// }

	// closesocket( client );
	// WSACleanup();
}

void HttpCommunicator::loadSingleANN(int annId, char *symbol, TimePeriod &period, double &fitness, NeuronsList &neurons, WeightsMatrix &weights, ActivitiesMatrix &activities) {
	// SOCKADDR_IN address;
	// SOCKET client;
	// WSADATA data;

	// if (WSAStartup(MAKEWORD(1,1), &data) != 0) {
		// throw( "HttpCommunicator00060" );
		// return;
	// }

	// struct hostent *host = gethostbyname( HOST );
	// if (host == NULL) {
		// WSACleanup();
		// throw( "HttpCommunicator00061" );
		// return;
	// }

	// client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// if (client == INVALID_SOCKET) {
		// WSACleanup();
		// throw( "HttpCommunicator00062" );
		// return;
	// }

	// memset(&address, 0, sizeof(address));
	// address.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	// address.sin_family = AF_INET;
	// address.sin_port = htons( PORT );

	// if (connect(client, (LPSOCKADDR)&address, sizeof(address)) != 0) {
		// closesocket( client );
		// WSACleanup();
		// throw( "HttpCommunicator00063" );
		// return;
	// }

	// char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ] = "";
	// sprintf(parameters, "annid=%d", annId);
	// sprintf(buffer, "POST %s HTTP/1.0\nHost: %s\r\nContent-Length: %d\r\nConnection: Keep-Alive\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s\r\n", LOAD_SINGLE_ANN_SCRIPT, HOST, strlen(parameters), parameters);
	// if (send(client, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
		// closesocket( client );
		// WSACleanup();
		// throw( "HttpCommunicator00064" );
		// return;
	// }

	// char *position = buffer;
	// int result = 0;
	// int numberOfBytes = 0;
	// do {
		// result = recv(client, position, BUFFER_SIZE-numberOfBytes-1, MSG_WAITALL);
		// if (result == SOCKET_ERROR) {
			// closesocket( client );
			// WSACleanup();
			// throw( "HttpCommunicator00065" );
			// return;
		// } else {
			// numberOfBytes += result;
			// position = buffer + numberOfBytes;
		// }
	// } while(result > 0);
	// buffer[ numberOfBytes ] = '\0';

	// /*
	 // * Separate HTTP header from HTTP body.
	 // */
	// position = strstr(buffer, "\r\n\r\n");

	// int available = 0;
	// position = strtok (position, " \r\n");
	// if(position-buffer < numberOfBytes) {
		// sscanf(position, "%d", &available);
	// }
	// if (available != 0) {
		// position = strtok (NULL, " \r\n");
		// strcpy(symbol, "");
		// if(position-buffer < numberOfBytes) {
			// sscanf(position, "%s", symbol);
		// }

		// position = strtok (NULL, " \r\n");
		// period = NO;
		// if(position-buffer < numberOfBytes) {
			// sscanf(position, "%d", &period);
		// }

		// position = strtok (NULL, " \r\n");
		// fitness = (double)RAND_MAX;
		// if(position-buffer < numberOfBytes) {
			// sscanf(position, "%lf", &fitness);
		// }

		// int numberOfNeurons = 0;
		// position = strtok (NULL, " \r\n");
		// if(position-buffer < numberOfBytes) {
			// sscanf(position, "%d", &numberOfNeurons);
		// }

		// int intValue = 0;
		// for (int i=0; i<numberOfNeurons; i++) {
			// position = strtok (NULL, " \r\n");
			// intValue = 0;
			// if(position-buffer < numberOfBytes) {
				// sscanf(position, "%d", &intValue);
			// }
			// switch (intValue) {
			// case REGULAR:
				// neurons[i].setType( REGULAR );
				// break;
			// case BIAS:
				// neurons[i].setType( BIAS );
				// break;
			// case INPUT:
				// neurons[i].setType( INPUT );
				// break;
			// case INPUT_BIAS:
				// neurons[i].setType( INPUT_BIAS );
				// break;
			// case OUTPUT:
				// neurons[i].setType( OUTPUT );
				// break;
			// case OUTPUT_BIAS:
				// neurons[i].setType( OUTPUT_BIAS );
				// break;
			// case OUTPUT_INPUT:
				// neurons[i].setType( OUTPUT_INPUT );
				// break;
			// case OUTPUT_INPUT_BIAS:
				// neurons[i].setType( OUTPUT_INPUT_BIAS );
				// break;
			// default:
				// neurons[i].setType( REGULAR );
				// break;
			// }
		// }

		// double doubleValue = 0.0;
		// for (int j=0; j<numberOfNeurons; j++) {
			// for (int i=0; i<numberOfNeurons; i++) {
				// position = strtok (NULL, " \r\n");
				// doubleValue = 0.0;
				// if(position-buffer < numberOfBytes) {
					// sscanf(position, "%lf", &doubleValue);
				// }
				// weights(i,j) = doubleValue;
			// }
		// }

		// for (int j=0; j<numberOfNeurons; j++) {
			// for (int i=0; i<numberOfNeurons; i++) {
				// position = strtok (NULL, " \r\n");
				// doubleValue = 0.0;
				// if(position-buffer < numberOfBytes) {
					// sscanf(position, "%lf", &doubleValue);
				// }
				// activities(i,j) = doubleValue;
			// }
		// }
	// }

	// closesocket( client );
	// WSACleanup();

	// if (available == 0) {
		// throw( "HttpCommunicator00066" );
	// }
}

int HttpCommunicator::loadTrainingSetSize(char *symbol, TimePeriod period) {
	// SOCKADDR_IN address;
	// SOCKET client;
	// WSADATA data;

	// if (WSAStartup(MAKEWORD(1,1), &data) != 0) {
		// throw( "HttpCommunicator00138" );
		// return( 0 );
	// }

	// struct hostent *host = gethostbyname( HOST );
	// if (host == NULL) {
		// WSACleanup();
		// throw( "HttpCommunicator00139" );
		// return( 0 );
	// }

	// client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// if (client == INVALID_SOCKET) {
		// WSACleanup();
		// throw( "HttpCommunicator00140" );
		// return( 0 );
	// }

	// memset(&address, 0, sizeof(address));
	// address.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	// address.sin_family = AF_INET;
	// address.sin_port = htons( PORT );

	// if (connect(client, (LPSOCKADDR)&address, sizeof(address)) != 0) {
		// closesocket( client );
		// WSACleanup();
		// throw( "HttpCommunicator00141" );
		// return( 0 );
	// }

	// char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ] = "";
	// sprintf(parameters, "symbol=%s&period=%d", symbol, period);
	// sprintf(buffer, "POST %s HTTP/1.0\nHost: %s\r\nContent-Length: %d\r\nConnection: Keep-Alive\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s\r\n", TRAINING_SET_SIZE_SCRIPT, HOST, strlen(parameters), parameters);
	// if (send(client, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
		// closesocket( client );
		// WSACleanup();
		// throw( "HttpCommunicator00142" );
		// return( 0 );
	// }

	// char *position = buffer;
	// int result = 0;
	// int numberOfBytes = 0;
	// do {
		// result = recv(client, position, BUFFER_SIZE-numberOfBytes-1, MSG_WAITALL);
		// if (result == SOCKET_ERROR) {
			// closesocket( client );
			// WSACleanup();
			// throw( "HttpCommunicator00143" );
			// return( 0 );
		// } else {
			// numberOfBytes += result;
			// position = buffer + numberOfBytes;
		// }
	// } while(result > 0);
	// buffer[ numberOfBytes ] = '\0';

	// /*
	 // * Separate HTTP header from HTTP body.
	 // */
	// position = strstr(buffer, "\r\n\r\n");

	// int size = 0;
	// position = strtok (position, " \r\n");
	// if(position-buffer < numberOfBytes) {
		// sscanf(position, "%d", &size);
	// }

	// closesocket( client );
	// WSACleanup();

	// return( size );
}

void HttpCommunicator::saveTrainingSet(char symbol[], TimePeriod period, const vector<RateInfo> &rates, int size) {
	// SOCKADDR_IN address;
	// SOCKET client;
	// WSADATA data;

	// if (WSAStartup(MAKEWORD(1,1), &data) != 0) {
		// throw( "HttpCommunicator00126" );
		// return;
	// }

	// struct hostent *host = gethostbyname( HOST );
	// if (host == NULL) {
		// WSACleanup();
		// throw( "HttpCommunicator00127" );
		// return;
	// }

	// client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// if (client == INVALID_SOCKET) {
		// WSACleanup();
		// throw( "HttpCommunicator00128" );
		// return;
	// }

	// memset(&address, 0, sizeof(address));
	// address.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	// address.sin_family = AF_INET;
	// address.sin_port = htons( PORT );

	// if (connect(client, (LPSOCKADDR)&address, sizeof(address)) != 0) {
		// closesocket( client );
		// WSACleanup();
		// throw( "HttpCommunicator00129" );
		// return;
	// }

	// char number[ 100 ];
	// char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ] = "";
	// char *position = parameters;

	// sprintf(position, "symbol=%s&", symbol);
	// position += strlen(position);

	// sprintf(position, "period=%d&", period);
	// position += strlen(position);

	// sprintf(position, "number_of_examples=%d&", size);
	// position += strlen(position);

	// strcpy(buffer, "");
	// for (int i=0; i<size; i++) {
		// if (i > 0) {
			// strcat(buffer, " ");
		// }
		// sprintf(number, "%d", rates[i].time);
		// strcat(buffer, number);
	// }
	// sprintf(position, "time=%s&", buffer);
	// position += strlen(position);

	// strcpy(buffer, "");
	// for (int i=0; i<size; i++) {
		// if (i > 0) {
			// strcat(buffer, " ");
		// }
		// sprintf(number, "%lf", rates[i].open);
		// strcat(buffer, number);
	// }
	// sprintf(position, "open=%s&", buffer);
	// position += strlen(position);

	// strcpy(buffer, "");
	// for (int i=0; i<size; i++) {
		// if (i > 0) {
			// strcat(buffer, " ");
		// }
		// sprintf(number, "%lf", rates[i].low);
		// strcat(buffer, number);
	// }
	// sprintf(position, "low=%s&", buffer);
	// position += strlen(position);

	// strcpy(buffer, "");
	// for (int i=0; i<size; i++) {
		// if (i > 0) {
			// strcat(buffer, " ");
		// }
		// sprintf(number, "%lf", rates[i].high);
		// strcat(buffer, number);
	// }
	// sprintf(position, "high=%s&", buffer);
	// position += strlen(position);

	// strcpy(buffer, "");
	// for (int i=0; i<size; i++) {
		// if (i > 0) {
			// strcat(buffer, " ");
		// }
		// sprintf(number, "%lf", rates[i].close);
		// strcat(buffer, number);
	// }
	// sprintf(position, "close=%s&", buffer);
	// position += strlen(position);

	// strcpy(buffer, "");
	// for (int i=0; i<size; i++) {
		// if (i > 0) {
			// strcat(buffer, " ");
		// }
		// sprintf(number, "%lf", rates[i].volume);
		// strcat(buffer, number);
	// }
	// sprintf(position, "volume=%s", buffer);
	// position += strlen(position);

	// sprintf(buffer, "POST %s HTTP/1.0\nHost: %s\r\nContent-Length: %d\r\nConnection: Keep-Alive\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s\r\n", SAVE_TRAINING_SET_SCRIPT, HOST, strlen(parameters), parameters);
	// if (send(client, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
		// closesocket( client );
		// WSACleanup();
		// throw( "HttpCommunicator00130" );
		// return;
	// }

	// closesocket( client );
	// WSACleanup();
}

void HttpCommunicator::loadTrainingSet(char symbol[], TimePeriod period, vector<RateInfo> &rates, int size) {
	// SOCKADDR_IN address;
	// SOCKET client;
	// WSADATA data;

	// if (WSAStartup(MAKEWORD(1,1), &data) != 0) {
		// throw( "HttpCommunicator00131" );
		// return;
	// }

	// struct hostent *host = gethostbyname( HOST );
	// if (host == NULL) {
		// WSACleanup();
		// throw( "HttpCommunicator00132" );
		// return;
	// }

	// client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// if (client == INVALID_SOCKET) {
		// WSACleanup();
		// throw( "HttpCommunicator00133" );
		// return;
	// }

	// memset(&address, 0, sizeof(address));
	// address.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	// address.sin_family = AF_INET;
	// address.sin_port = htons( PORT );

	// if (connect(client, (LPSOCKADDR)&address, sizeof(address)) != 0) {
		// closesocket( client );
		// WSACleanup();
		// throw( "HttpCommunicator00134" );
		// return;
	// }

	// char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ] = "";
	// sprintf(parameters, "symbol=%s&period=%d", symbol, period);
	// sprintf(buffer, "POST %s HTTP/1.0\nHost: %s\r\nContent-Length: %d\r\nConnection: Keep-Alive\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s\r\n", LOAD_TRAINING_SET_SCRIPT, HOST, strlen(parameters), parameters);
	// if (send(client, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
		// closesocket( client );
		// WSACleanup();
		// throw( "HttpCommunicator00135" );
		// return;
	// }

	// char *position = buffer;
	// int result = 0;
	// int numberOfBytes = 0;
	// do {
		// result = recv(client, position, BUFFER_SIZE-numberOfBytes-1, MSG_WAITALL);
		// if (result == SOCKET_ERROR) {
			// closesocket( client );
			// WSACleanup();
			// throw( "HttpCommunicator00136" );
			// return;
		// } else {
			// numberOfBytes += result;
			// position = buffer + numberOfBytes;
		// }
	// } while(result > 0);
	// buffer[ numberOfBytes ] = '\0';

	// /*
	 // * Separate HTTP header from HTTP body.
	 // */
	// position = strstr(buffer, "\r\n\r\n");

	// int available = 0;
	// position = strtok (position, " \r\n");
	// if(position-buffer < numberOfBytes) {
		// sscanf(position, "%d", &available);
	// }
	// if (available != 0) {
		// if (available < size) {
			// size = available;
		// }

		// int intValue = 0;
		// for (int i=0; i<size; i++) {
			// position = strtok (NULL, " \r\n");
			// intValue = 0;
			// if(position-buffer < numberOfBytes) {
				// sscanf(position, "%d", &intValue);
			// }
			// rates[i].time = intValue;
		// }

		// double doubleValue = 0.0;
		// for (int i=0; i<size; i++) {
			// position = strtok (NULL, " \r\n");
			// doubleValue = 0.0;
			// if(position-buffer < numberOfBytes) {
				// sscanf(position, "%lf", &doubleValue);
			// }
			// rates[i].open = doubleValue;
		// }

		// for (int i=0; i<size; i++) {
			// position = strtok (NULL, " \r\n");
			// doubleValue = 0.0;
			// if(position-buffer < numberOfBytes) {
				// sscanf(position, "%lf", &doubleValue);
			// }
			// rates[i].low = doubleValue;
		// }

		// for (int i=0; i<size; i++) {
			// position = strtok (NULL, " \r\n");
			// doubleValue = 0.0;
			// if(position-buffer < numberOfBytes) {
				// sscanf(position, "%lf", &doubleValue);
			// }
			// rates[i].high = doubleValue;
		// }

		// for (int i=0; i<size; i++) {
			// position = strtok (NULL, " \r\n");
			// doubleValue = 0.0;
			// if(position-buffer < numberOfBytes) {
				// sscanf(position, "%lf", &doubleValue);
			// }
			// rates[i].close = doubleValue;
		// }

		// for (int i=0; i<size; i++) {
			// position = strtok (NULL, " \r\n");
			// doubleValue = 0.0;
			// if(position-buffer < numberOfBytes) {
				// sscanf(position, "%lf", &doubleValue);
			// }
			// rates[i].volume = doubleValue;
		// }
	// }

	// closesocket( client );
	// WSACleanup();
}

double HttpCommunicator::loadRemoteBestFitness(char *symbol, TimePeriod period, NeuronsList &neurons, ActivitiesMatrix &activities) {
	// SOCKADDR_IN address;
	// SOCKET client;
	// WSADATA data;

	// if (WSAStartup(MAKEWORD(1,1), &data) != 0) {
		// throw( "HttpCommunicator00067" );
		// return( (double)RAND_MAX );
	// }

	// struct hostent *host = gethostbyname( HOST );
	// if (host == NULL) {
		// WSACleanup();
		// throw( "HttpCommunicator00068" );
		// return( (double)RAND_MAX );
	// }

	// client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// if (client == INVALID_SOCKET) {
		// WSACleanup();
		// throw( "HttpCommunicator00069" );
		// return( (double)RAND_MAX );
	// }

	// memset(&address, 0, sizeof(address));
	// address.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	// address.sin_family = AF_INET;
	// address.sin_port = htons( PORT );

	// if (connect(client, (LPSOCKADDR)&address, sizeof(address)) != 0) {
		// closesocket( client );
		// WSACleanup();
		// throw( "HttpCommunicator00070" );
		// return( (double)RAND_MAX );
	// }

	// char number[ 100 ];
	// char parameters[ HTTP_PARAMETERS_BUFFER_SIZE ] = "";
	// char *position = parameters;

	// sprintf(position, "symbol=%s&", symbol);
	// position += strlen(position);

	// sprintf(position, "period=%d&", period);
	// position += strlen(position);

	// sprintf(position, "number_of_neurons=%d&", neurons.dimension());
	// position += strlen(position);

	// strcpy(buffer, "");
	// for (int i=0; i<neurons.dimension(); i++) {
		// if (i > 0) {
			// strcat(buffer, " ");
		// }
		// sprintf(number, "%d", neurons[i].getType());
		// strcat(buffer, number);
	// }
	// sprintf(position, "flags=%s&", buffer);
	// position += strlen(position);

	// strcpy(buffer, "");
	// for (int j=0; j<neurons.dimension(); j++) {
		// if (j > 0) {
			// strcat(buffer, "\n");
		// }
		// for (int i=0; i<neurons.dimension(); i++) {
			// if (i > 0) {
				// strcat(buffer, " ");
			// }
			// sprintf(number, "%lf", activities(i,j));
			// strcat(buffer, number);
		// }
	// }
	// sprintf(position, "activities=%s", buffer);
	// position += strlen(position);

	// strcpy(buffer, "");
	// sprintf(buffer, "POST %s HTTP/1.0\nHost: %s\r\nContent-Length: %d\r\nConnection: Keep-Alive\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s\r\n", LOAD_BEST_FITNESS_SCRIPT, HOST, strlen(parameters), parameters);
	// if (send(client, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
		// closesocket( client );
		// WSACleanup();
		// throw( "HttpCommunicator00071" );
		// return( (double)RAND_MAX );
	// }

	// position = buffer;
	// int result = 0;
	// int numberOfBytes = 0;
	// do {
		// result = recv(client, position, BUFFER_SIZE-numberOfBytes-1, MSG_WAITALL);
		// if (result == SOCKET_ERROR) {
			// closesocket( client );
			// WSACleanup();
			// throw( "HttpCommunicator00072" );
			// return( (double)RAND_MAX );
		// } else {
			// numberOfBytes += result;
			// position = buffer + numberOfBytes;
		// }
	// } while(result > 0);
	// buffer[ numberOfBytes ] = '\0';

	// /*
	 // * Separate HTTP header from HTTP body.
	 // */
	// position = strstr(buffer, "\r\n\r\n");

	// double bestFitness = (double)RAND_MAX;
	// position = strtok (position, " \r\n");
	// if(position-buffer < numberOfBytes) {
		// sscanf(position, "%lf", &bestFitness);
	// }

	// closesocket( client );
	// WSACleanup();

	// return( bestFitness );
}
