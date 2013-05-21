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

#include "../include/SlideShow.h"
#include "../include/VisualComponent.h"

VisualComponent::VisualComponent() {
	root = NULL;
	display = NULL;
	gc = NULL;
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

VisualComponent::VisualComponent(int x, int y, int width, int height) {
	this->root = NULL;
	this->display = NULL;
	this->gc = NULL;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

VisualComponent::VisualComponent(int x, int y, int width, int height, Window *root, Display *display, GC *gc) {
	this->root = root;
	this->display = display;
	this->gc = gc;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

int VisualComponent::getX() {
	return (x);
}

void VisualComponent::setX(int x) {
	this->x = x;
}

int VisualComponent::getY() {
	return (y);
}

void VisualComponent::setY(int y) {
	this->y = y;
}

int VisualComponent::getWidth() {
	return (width);
}

void VisualComponent::setWidth(int widht) {
	this->width = width;
}

int VisualComponent::getHeight() {
	return (height);
}

void VisualComponent::setHeight(int height) {
	this->height = height;
}

Window* VisualComponent::getRoot() {
	return (root);
}

void VisualComponent::setRoot(Window *root) {
	this->root = root;
}

Display* VisualComponent::getDisplay() {
	return ( display );
}

void VisualComponent::setDisplay(Display *display) {
	this->display = display;
}

GC* VisualComponent::getGc() {
	return ( gc );
}

void VisualComponent::setGc(GC *gc) {
	this->gc = gc;
}

void VisualComponent::draw() {
}

VisualComponent::~VisualComponent() {
}

