/*******************************************************************************
 *                                                                             *
 * VitoshaTrade is Distributed Artificial Neural Network trained by            *
 * Differential Evolution for prediction of Forex. Project development is in   *
 * Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   *
 * the capital of Bulgaria.                                                    *
 *                                                                             *
 * Copyright (C) 2008-2009 by Todor Balabanov  ( tdb@tbsoft.eu )               *
 *                       Iliyan Zankinski   ( iliyan_mf@abv.bg )               *
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

#include <cstring>
#include <cstdlib>

using namespace std;
#include "../include/Ballon.h"

using namespace std;

Ballon::Ballon() : VisualComponent(0,0,0,0) {
}

Ballon::Ballon(int x, int y, int width, int height) : VisualComponent(x,y,width,height) {
}

string Ballon::getText() {
	return (text);
}

void Ballon::setText(string text) {
	this->text = text;
}

void Ballon::draw() {
	const char *str = text.c_str();

	/*
	 * Load a font.
	 */
	Font font = XLoadFont(display, "-*-helvetica-bold-r-*-*-25-*-*-*-*-*-*-*");
	XSetFont(display, (*gc), font);

	/*
	 * Get font metrics.
	 */
	XGCValues gcValues;
	XGetGCValues(display, (*gc), GCFont, &gcValues);
	XFontStruct *fontStructure = XQueryFont(display, gcValues.font);

	/*
	 * Get text width and height.
	 */
	int textWidth = XTextWidth(fontStructure, str, strlen(str) );

//--------------------------------------------------------------------------------------------------------------------------------------------
	{
		static int steps = 32;
		static int sr=0, sg=0, sb=0;
		static int cr=0, cg=0, cb=0;
		static int er=0, eg=0, eb=0;
		static int dr=0, dg=0, db=0;
		static int counter = 0;

		if (counter == 0) {
			sr = er;
			sg = eg;
			sb = eb;

			cr = sr;
			cg = sg;
			cb = sb;

			er = rand()%256;
			eg = rand()%256;
			eb = rand()%256;

			dr = (er-sr) / steps;
			dg = (eg-sg) / steps;
			db = (eb-sb) / steps;
		}

		XSetForeground(display, (*gc), (cr<<16) | (cg<<8) | cb);

		/*
		 * Draw a rectangle.
		 */
		static XWindowAttributes wa;
		XGetWindowAttributes(display, (*root), &wa);
		//XFillArc(display, (*root), (*gc), x-(ELIPSE_WIDTH/2), y-(ELIPSE_HEIGHT/2), ELIPSE_WIDTH, ELIPSE_HEIGHT, ELIPSE_ANGLE_1, ELIPSE_ANGLE_2);
		XDrawRectangle(display, (*root), (*gc), x-(ELIPSE_WIDTH/2), y-(ELIPSE_HEIGHT/2), ELIPSE_WIDTH, ELIPSE_HEIGHT);

		XSetForeground(display, (*gc), ((255-cr)<<16) | ((255-cg)<<8) | (255-cb));

		cr += dr;
		cg += dg;
		cb += db;

		counter = (counter + 1) % steps;
	}
//--------------------------------------------------------------------------------------------------------------------------------------------*/

	XDrawString(display, (*root), (*gc), x-(ELIPSE_WIDTH/9), y+(ELIPSE_HEIGHT/9), str, strlen(str));
}

Ballon::~Ballon() {
}

