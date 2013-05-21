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

#include <cstdlib>

#include "../include/Screensaver.h"

using namespace std;

Screensaver::Screensaver(Window *root, Display *display, GC *gc) {
	this->root = root;
	this->display = display;
	this->gc = gc;

	/*
	 * Connect references to drawing structures.
	 */
	show.setRoot( root );
	show.setDisplay( display );
	show.setGc( gc );
	topLeft.setRoot( root );
	topLeft.setDisplay( display );
	topLeft.setGc( gc );
	topRight.setRoot( root );
	topRight.setDisplay( display );
	topRight.setGc( gc );
	bottomRight.setRoot( root );
	bottomRight.setDisplay( display );
	bottomRight.setGc( gc );
	bottomLeft.setRoot( root );
	bottomLeft.setDisplay( display );
	bottomLeft.setGc( gc );

	/*
	 * Visual components positioning.
	 */
	XWindowAttributes wa;
	XGetWindowAttributes(display, (*root), &wa);
	topLeft.setX( 100+0 );
	topLeft.setY( 100+0 );
	topRight.setX( wa.width-100 );
	topRight.setY( 100+0 );
	bottomLeft.setX( 100+0 );
	bottomLeft.setY( wa.height-100  );
	bottomRight.setX( wa.width-100  );
	bottomRight.setY( wa.height-100 );

	topLeft.setText( "TL" );
	topRight.setText( "TR" );
	bottomLeft.setText( "BL" );
	bottomRight.setText( "BR" );
}

Screensaver::Screensaver() {
}

void Screensaver::draw() {
	/*static int steps = 32;
	static int sr=0, sg=0, sb=0;
	static int cr=0, cg=0, cb=0;
	static int er=0, eg=0, eb=0;
	static int dr=0, dg=0, db=0;
	static int counter = 0;

	if(counter == 0) {
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

	static XWindowAttributes wa;
	XGetWindowAttributes(display, (*root), &wa);
	XFillRectangle(display, (*root), (*gc), 0, 0, wa.width-1, wa.height-1);

	cr += dr;
	cg += dg;
	cb += db;

	counter = (counter + 1) % steps;*/

	//TODO Real redraw.
	show.draw();
	topLeft.draw();
	topRight.draw();
	bottomRight.draw();
	bottomLeft.draw();
}

Screensaver::~Screensaver() {
}

