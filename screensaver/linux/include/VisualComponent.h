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

#ifndef VISUAL_COMPONENT_H
#define VISUAL_COMPONENT_H

#include <X11/Xlib.h>
#include "vroot.h"

/**
 * Visual component class.
 *
 * @author Elisaveta Hristova
 *
 * @email elisaveta.s.hristova@gmail.com
 *
 * @date 16 Dec 2010
 */
class VisualComponent {

protected:

	/*
	 * Determined the root window.
	 */
	Window *root;

	/*
	 * Display for connect to the X server..
	 */
	Display *display;

	/*
	 * Pointer to graphic context structure that contains all parameters used by the drawing functions..
	 */
	GC *gc;

	/*
	 * Top left x coordinate.
	 */
	int x;

	/*
	 * Top left y coordinate.
	 */
	int y;

	/*
	 * Slide show width.
	 */
	int width;

	/*
	 * GUI ballon componet height.
	 */
	int height;

public:
	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 16 Dec 2010
	 */
	VisualComponent();

	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @param x Visual component x cordinate.
	 *
	 * @param y Visual component y cordinate.
	 *
	 * @param width The width of the visual component.
	 *
	 * @param height The height of the visual component.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 16 Dec 2010
	 */
	VisualComponent(int x, int y, int width, int height);

	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @param x Visual component x cordinate.
	 *
	 * @param y Visual component y cordinate.
	 *
	 * @param width The width of the visual component.
	 *
	 * @param height The height of the visual component.
	 *
	  * @param root Determined the root window.
	 *
	 * @param display For connect to the X server.
	 *
	 * @param gc Pointer to structure that contains all parameters used by the drawing functions.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 16 Dec 2010
	 */
	VisualComponent(int x, int y, int width, int height, Window *root, Display *display, GC *gc);

	/**
	 * Visual component top left x coordinate getter.
	 *
	 * @return Visual component x cordinate.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 16 Dec 2010
	 */
	int getX();

	/**
	 * Visual component top left x coordinate setter.
	 *
	 * @param x Visual component x cordinate.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 16 Dec 2010
	 */
	void setX(int x);

	/**
	 * Visual component top left y coordinate getter.
	 *
	 * @return Visual component y cordinate.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 16 Dec 2010
	 */
	int getY();

	/**
	 * Visual component top left y coordinate setter.
	 *
	 * @param y Visual component y cordinate.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 16 Dec 2010
	 */
	void setY(int y);

	/**
	 * Visual component width getter.
	 *
	 * @return Width of the visual component.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 16 Dec 2010
	 */
	int getWidth();

	/**
	 * Visual component width setter.
	 *
	 * @param width The width of the visual component.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 16 Dec 2010
	 */
	void setWidth(int width);

	/**
	 * Visual component height getter.
	 *
	 * @return Height of the visual component.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 *  @date 16 Dec 2010
	 */
	int getHeight();

	/**
	 * Visual component height setter.
	 *
	 * @param height The height of the visual component.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 16 Dec 2010
	 */
	void setHeight(int height);

	/**
	 * Visual component Window getter.
	 *
	 * @return Pointer that determined the root window.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 26 Dec 2010
	 */
	Window* getRoot();

	/**
	 * Visual component Window setter.
	 *
	  * @param root Determined the root window.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 26 Dec 2010
	 */
	void setRoot(Window *root);

	/**
	 * Visual component Display getter.
	 *
	 * @return Return a pointer to contact X server.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 26 Dec 2010
	 */
	Display* getDisplay();

	/**
	 * Visual component Display setter.
	 *
	 * @param display For connect to the X server.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 26 Dec 2010
	 */
	void setDisplay(Display *display);

	/**
	 * Visual component GC getter.
	 *
	 * @return Pointer to structure that contains all parameters used by the drawing functions.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 26 Dec 2010
	 */
	GC* getGc();

	/**
	 * Visual component GC setter.
	 *
	 * @param gc Pointer to structure that contains all parameters used by the drawing functions.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 26 Dec 2010
	 */
	void setGc(GC *gc);

	/**
	 * Draw visual component.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 16 Dec 2010
	 */
	virtual void draw();

	/**
	 * Class destructor. Memory release and variables deinitialization.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 16 Dec 2010
	 */
	~VisualComponent();
};

#endif

