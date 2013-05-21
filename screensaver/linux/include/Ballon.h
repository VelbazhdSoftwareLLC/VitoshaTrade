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

#ifndef BALLON_H
#define BALLON_H

#include <string>

using namespace std;

#include "VisualComponent.h"

/**
 * GUI Ballon with system information.
 *
 * @author Elisaveta Hristova
 *
 * @email elisaveta.s.hristova@gmail.com
 *
 * @date 25 Nov 2010
 */
class Ballon : public VisualComponent {

public:

	/*
	 * Specify the width, which are the major and minor axes of the arc.
	 */
	static const int ELIPSE_WIDTH = 160;

	/*
	 *Specify the height, which are the major and minor axes of the arc.
	 */
	static const int ELIPSE_HEIGHT = 120;

	/*
	 * Specifies the start of the arc relative to the three-o'clock position from the center, in units of degrees * 64.
	 */
	static const int ELIPSE_ANGLE_1 = 100;

	/*
	 * Specifies the path and extent of the arc relative to the start of the arc, in units of degrees * 64.
	 */
	static const int ELIPSE_ANGLE_2 = 23040;

private:

	/*
	 * Text to show.
	 */
	string text;

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
	Ballon();

	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @param x Ballon component x cordinate.
	 *
	 * @param y Ballon component y cordinate.
	 *
	 * @param width The width of the ballon component.
	 *
	 * @param height The height of the ballon component.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 25 Nov 2010
	 */
	Ballon(int x, int y, int width, int height);

	/**
	 * Text to show getter.
	 *
	 * @return Text in Ballon component.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 30 Nov 2010
	 */
	string getText();

	/**
	 * Text to show setter.
	 *
	 * @param text Ballon component text to show.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 30 Nov 2010
	 */
	void setText(string text);

	/**
	 * Draws a ballon component.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 30 Nov 2010
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
	~Ballon();
};

#endif

