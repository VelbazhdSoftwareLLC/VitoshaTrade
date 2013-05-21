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

/*/-----------------------------------------------------------------
#include <cstdlib>

using namespace std;

#include <X11/Xlib.h>
//#include <X11/xpm.h>

#include "../include/vroot.h"

//-----------------------------------------------------------------*/

#include "../include/SlideShow.h"

SlideShow::SlideShow() : VisualComponent(0,0,0,0) {
	imageChangeInterval = 0;
	morphingTime = 0;
}

SlideShow::SlideShow(int x, int y, int width, int height) : VisualComponent(x,y,width,height) {
	this->imageChangeInterval = 0;
	this->morphingTime = 0;
}

SlideShow::SlideShow(int x, int y, int width, int height, unsigned long imageChangeInterval, unsigned long morphingTime) : VisualComponent(x,y,width,height) {
	this->imageChangeInterval = imageChangeInterval;
	this->morphingTime = morphingTime;
}

unsigned long SlideShow::getImageChangeInterval() {
	return (imageChangeInterval);
}

void SlideShow::setImageChangeInterval(unsigned long imageChangeInterval) {
	this->imageChangeInterval = imageChangeInterval;
}

unsigned long SlideShow::getMorphingTime() {
	return (morphingTime);
}

void SlideShow::setMorphingTime(unsigned long morphingTime) {
	this->morphingTime = morphingTime;
}

void SlideShow::draw() {
	unsigned width;
	unsigned height;
	int xHot;
	int yHot;

	Pixmap image = XCreatePixmap(display, (*root), 1077, 653,  DefaultDepth(display,0));
	XReadBitmapFile(display, (*root), "vitosha.bmp", &width, &height, &image, &xHot, &yHot);
	XPutImage(display, (*root), (*gc), image, src_x, src_y, dest_x, dest_y, width, height)
	XFreePixmap(display, image);


//TODO XReadBitmapFile
//TODO http://tronche.com/gui/x/xlib/utilities/XReadBitmapFile.html

	/*/------------------------------------------------------------------------
	XImage *img;
	XWindowAttributes wa;
	XGetWindowAttributes(display, (*root), &wa);

	if (XpmReadFileToImage (display, "monalisa.xpm", &img, NULL, NULL)) {
	}

	XPutImage(display, (*root), (*gc), img, 0, 0,
	                rand()%(wa.width-img->width),
	                rand()%(wa.height-img->height),
	                img->width, img->height );

	//------------------------------------------------------------------------*/
}

SlideShow::~SlideShow() {
}

