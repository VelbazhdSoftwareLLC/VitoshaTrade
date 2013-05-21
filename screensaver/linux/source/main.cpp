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
#include <unistd.h>
#include <X11/Xlib.h>

using namespace std;

#include "../include/vroot.h"

#include "../include/Screensaver.h"

/**
 * Application main function.
 *
 * @return Error code to OS.
 *
 * @author Elisaveta Hristova
 *
 * @email elisaveta.s.hristova@gmail.com
 *
 * @date 05 Nov 2010
 */
int main () {
	Display *display;
	Window root;
	GC g;

	/*
	 * Seed random generator.
	 */
	srand( time(NULL) );

	/*
	 * Open the display (connect to the X server).
	 */
	display = XOpenDisplay(getenv ("DISPLAY"));

	/*
	 * Get root window.
	 */
	root = DefaultRootWindow(display);

	/*
	 * Create GC for drawing in the window.
	 */
	g = XCreateGC(display, root, 0, NULL);

	/*
	 * Initializing screensaver object.
	 */
	Screensaver saver(&root, display, &g);

	/*
	 * Draw screensaver art in infinite loop.
	 */
	while ( !0 ) {
		/*
		 * Draw single frame.
		 */
		//saver.update();
		saver.draw();

		/*
		 * flush changes and sleep
		 */
		XFlush(display);
		usleep( 50000 );
	}

	/*
	 * Display close.
	 */
	XCloseDisplay(display);

	return( EXIT_SUCCESS );
}

