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

#ifndef SLIDE_SHOW_H
#define SLIDE_SHOW_H

#include "VisualComponent.h"

/**
 * Slide show component class.
 *
 * @author Elisaveta Hristova
 *
 * @email elisaveta.s.hristova@gmail.com
 *
 * @date 28 Nov 2010
 */
class SlideShow : public VisualComponent {

private:
	//TODO Images as vector. Research what kind of structure to use.

	/*
	 * Number of seconds for image visualization in seconds.
	 */
	unsigned long imageChangeInterval;

	/*
	 * Time needed for image morphing in milliseconds.
	 */
	unsigned long morphingTime;

public:

	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 28 Nov 2010
	 */
	SlideShow();

	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @param x Visual component x cordinate.
	 *
	 * @param y Visual component y cordinate.
	 *
	 * @param width The width of the slide show component.
	 *
	 * @param height The height of the slide show component.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 01 Dec 2010
	 */
	SlideShow(int x, int y, int width, int height);

	/**
	 * Class constructor. Memory allocation and internal variables initializaton.
	 *
	 * @param x Visual component x cordinate.
	 *
	 * @param y Visual component y cordinate.
	 *
	 * @param width The width of the slide show component.
	 *
	 * @param height The height of the slide show component.
	 *
	 * @param imageChangeInterval Time to be displayed image.
	 *
	 * @param morphingTime Time to move smoothly from one image to another.
	   	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 01 Dec 2010
	 */
	SlideShow(int x, int y, int width, int height, unsigned long imageChangeInterval, unsigned long morphingTime);

	/**
	 * Value of interval for change of images getter.
	 *
	 * @return Value of time to be displayed image.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 01 Dec 2010
	 */
	unsigned long getImageChangeInterval();

	/**
	 * Value of interval for change of images setter.
	 *
	 * @param imageChangeInterval Value of time to be displayed image.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 01 Dec 2010
	 */
	void setImageChangeInterval(unsigned long imageChangeInterval);

	/**
	 * Time for morfing getter.
	 *
	 * @return Time to move smoothly from one image to another.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 01 Dec 2010
	 */
	unsigned long getMorphingTime();

	/**
	 * Time for morfing setter.
	 *
	 * @param morphingTime Time to move smoothly from one image to another.
	 *
	 * @author Elisaveta Hristova
	 *
	 * @email elisaveta.s.hristova@gmail.com
	 *
	 * @date 01 Dec 2010
	 */
	void setMorphingTime(unsigned long morphingTime);

	/**
	 * Care for displaying a slideshow.
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
	 * @date 28 Nov 2010
	 */
	~SlideShow();
};

#endif

