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

#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <X11/Xlib.h>
#include "vroot.h"

#include "Ballon.h"
#include "SlideShow.h"
#include "VisualComponent.h"

/**
 * Base screensaver class.
 *
 * @author Elisaveta Hristova
 *
 * @email elisaveta.s.hristova@gmail.com
 *
 * @date 25 Nov 2010
 */
class Screensaver : public VisualComponent {

private:

	/*
	 * Slide show componet.
	 */
	SlideShow show;

	/*
	 * Top left GUI ballon.
	 */
	Ballon topLeft;

	/*
	 * Top right GUI ballon.
	 */
	Ballon topRight;

	/*
	 * Bottom right GUI ballon.
	 */
	Ballon bottomRight;

	/*
	 * Bottom left GUI ballon.
	 */
	Ballon bottomLeft;

public:

	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 25 Nov 2010
	 */
	Screensaver();

	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @param root Determined the root window
	 *
	 * @param display For connect to the X server.
	 *
	 * @param gc Pointer to structure that contains all parameters used by the drawing functions.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 01 Dec 2010
	 */
	Screensaver(Window *root, Display *display, GC *gc);

	/**
	 * Invokes draw methods of the constituent elements of a screen saver.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 01 Dec 2010
	 */
	virtual void draw();

	/**
	 * Class destructor. Memory release and variables deinitialization.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 25 Nov 2010
	 */
	~Screensaver();
};

#endif

