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

#include <stdio.h>
#include <cstdlib>
#include <cstring>

#include "Init.h"

const char Init::INI_FILE_NAME[] = "VitoshaTrade.ini";

const char Init::TEMP_FILE_NAME[] = "VitoshaTrade.tmp";

double Init::load(const char key[], double value) {
	FILE *in;
	double result = value;
	char buffer[ BUFFER_SIZE ];

	/*
	 * Create file if does not exist.
	 */
	in = fopen(INI_FILE_NAME, "at");
	fclose( in );

	/*
	 * Find key and read value.
	 */
	in = fopen(INI_FILE_NAME, "rt");
	while ( !feof(in) ) {
		fscanf(in, "%s", buffer);
		if (strstr(buffer,key) != NULL) {
			char *position = strstr(buffer, ":") + 1;
			sscanf(position, "%lf", &result);
		}
	}
	fclose( in );

	return( result );
}

void Init::save(const char key[], double value) {
	FILE *in;
	FILE *out;
	char buffer[ BUFFER_SIZE ] = "";

	/*
	 * Create file if does not exist.
	 */
	in = fopen(INI_FILE_NAME, "at");
	fprintf(in, "");
	fclose( in );

	/*
	 * Find key and write value.
	 */
	bool found = false;
	in = fopen(INI_FILE_NAME, "rt");
	out = fopen(TEMP_FILE_NAME, "wt");
	while ( !feof(in) ) {
		fscanf(in, "%s\r\n", buffer);
		if (strstr(buffer,key) != NULL) {
			fprintf(out, "%s:%lf\r\n", key, value);
			found = true;
		} else {
			fprintf(out, "%s\r\n", buffer);
		}
	}
	if (found == false) {
		fprintf(out, "%s:%lf\r\n", key, value);
	}
	fclose( out );
	fclose( in );

	/*
	 * Swap INI file.
	 */
	remove( INI_FILE_NAME );
	rename(TEMP_FILE_NAME, INI_FILE_NAME);
}
