/*******************************************************************************
 *                                                                             *
 * VitoshaTrade is Distributed Artificial Neural Network trained by            *
 * Differential Evolution for prediction of Forex. Project development is in   *
 * Sofia, Bulgaria. Vitosha is a mountain massif, on the outskirts of Sofia,   *
 * the capital of Bulgaria.                                                    *
 *                                                                             *
 * Copyright (C) 2008-2011 by Todor Balabanov  ( tdb@tbsoft.eu )               *
 *                            Iliyan Zankinski ( iliyan_mf@abv.bg )            *
 *                            Galq Cirkalova   ( galq_cirkalova@abv.bg )       *
 *                            Ivan Grozev      ( ivan.iliev.grozev@gmail.com ) *
 *                            Nikola Simeonov  ( n.simeonow@gmail.com )        *
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

#include <windows.h>
#include <scrnsave.h>
#include <commctrl.h>

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

#include "../include/wrapper.h"

/**
 * Global variable that is used as a timer tells how often the operating system
 * will give control of our application, so that it can redraw the screen.
 */
#define TIMER 1

/**
 *
 */
struct TFlyingObject {
	GLfloat x;
	GLfloat y;
	float dx;
	float dy;
	float red;
	float green;
	float blue;
	GLfloat rotation;
	float dry;
	char text[100];
};

typedef struct TFlyingObject FlyingObject;

FlyingObject title = {0.0, 0.0, 0.0, 0.0, 0.5f, 3.0f, 0.5f, 0.0, 1.3, "VitoshaTrade"};
FlyingObject symbol = {0.0, 0.0, 0.0, 0.0, 3.0f, 0.5f, 0.5f, 0.0, 1.2, "EURUSD"};
FlyingObject period = {0.0, 0.0, 0.0, 0.0, 3.0f, 3.0f, 0.5f, 0.0, 1.1, "M1"};
FlyingObject forecast = {0.0, 0.0, 0.0, 0.0, 0.5f, 0.5f, 3.0f, 0.0, 1.0, "0.0"};
FlyingObject direction = {0.0, 0.0, 0.0, 0.0, 3.0f, 0.9f, 0.1f, 0.0, 1.0, "/\\ or \\/"};

void InitGL(HWND hWnd, HDC &hDC, HGLRC &hRC);
void CloseGL(HWND hWnd, HDC hDC, HGLRC hRC);
void SetupAnimation(int width, int height);
void OnTimer(HDC hDC);

/**
 * Handle to device context.
 */
static HDC hDC;

/**
 * Handle to OpenGL rendering context.
 */
static HGLRC hRC;

/**
 * Instance of structure RECT which defines the coords of the upper-left and
 * lower-right corners of a rectangle.
 */
static RECT rect;

/**
 * Width size of screen variables.
 */
int width;

/**
 * Height size of screen variables.
 */
int height;

/**
 * Holds the instance of the application.
 */
HINSTANCE hInstance;

/**
 * Screen saver main procedure.
 *
 * @param hwnd Windows handle (pointer to the application window).
 *
 * @param message Message sent by the operating system understand it can we
 * create a window.
 *
 * @param wparam
 *
 * @param lparam
 *
 * @return Handled by default, all messages received from the function
 * ScreenSaverProc which were not processed.
 *
 * @author Nikola Simeonov
 *
 * @email n.simeonow@gmail.com
 *
 * @date 03 Nov 2010
 */
LONG WINAPI ScreenSaverProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) {
	switch (message) {

		/*
		 * Set timer and any other initializations.
		 */
	case WM_CREATE:
		srand( time(NULL) );
		GetClientRect(hWnd, &rect);
		width = rect.right;
		height = rect.bottom;
		InitGL(hWnd, hDC,hRC);
		SetupAnimation(width, height);
		SetTimer(hWnd, TIMER, 10, NULL);

		//TODO Use screensaver dialog parameters to start predictor.
		//startPredictor(const int dbId, const char *symbol, const int period, const int neuronsAmount, const int populationSize, const int bars);
		sprintf(direction.text, "");

		return( 0 );

		/*
		 * Destroy timer and perform cleanup.
		 */
	case WM_DESTROY:
		/*
		 * Stop predictor thread.
		 */
		//stopPredictor();

		KillTimer(hWnd, TIMER);
		CloseGL(hWnd, hDC, hRC);
		return( 0 );

		/*
		 * Perform drawing operations.
		 */
	case WM_TIMER:
		/*
		 * Obtaion ANN corrency prediction.
		 */
		//sprintf(forecast.text, "%lf", prediction());
		if (rand()%100 == 0) {
			sprintf(forecast.text, "%.2lf", (double)(rand()%10001)/100.0);
			if (rand()%2 == 0) {
				sprintf(direction.text, "/\\");
			} else {
				sprintf(direction.text, "\\/");
			}
		}

		OnTimer(hDC);
		return( 0 );
	}

	return( DefScreenSaverProc(hWnd, message, wParam, lParam) );
}

/**
 * This function displays a dialog box that enables the user to configure the
 * screen saver (an application must provide a corresponding dialog box template).
 * Windows displays the configuration dialog box when the user selects the Setup button
 * in the Control Panel's Screen Saver dialog box.
 *
 * @param hWnd Windows handle (pointer to the application window).
 *
 * @param message Message sent by the operating system understand it can we
 * create a window.
 *
 * @param wParam
 *
 * @param lParam
 *
 * @return
 *
 * @author Nikola Simeonov
 *
 * @email n.simeonow@gmail.com
 *
 * @date 03 Nov 2010
 */
BOOL WINAPI ScreenSaverConfigureDialog(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam) {
	return FALSE;
}

/**
 * This function must be called by all screen saver applications. However, applications
 * that do not require special windows or custom controls in the configuration dialog box
 * can simply return TRUE. Applications requiring special windows or custom controls
 * should use this function to register the corresponding window classes.
 *
 * @param hmodule
 *
 * @return
 *
 * @author Nikola Simeonov
 *
 * @email n.simeonow@gmail.com
 *
 * @date 03 Nov 2010
 */
BOOL WINAPI RegisterDialogClasses(HANDLE hmodule) {
	//TODO Find information about this function and its purpouse.
	return TRUE;
}

/**
 * Base display list for the font set.
 */
GLuint base;

/**
 * Base display list for the font set.
 */
bool keys[256];

/**
 * Storage for information about our outline font characters.
 */
GLYPHMETRICSFLOAT gmf[256];

/**
 * Initialize font. Build our bitmap font.
 *
 * @param GLvoid
 *
 * @author Nikola Simeonov
 *
 * @email n.simeonow@gmail.com
 *
 * @date 20 Nov 2010
 */
GLvoid BuildFont( GLvoid ) {
	/*
	 * Windows font ID.
	 */
	HFONT font;

	/*
	 * Storage for 256 characters.
	 */
	base = glGenLists( 256 );

	font = CreateFont(	15,
						0,
						0,
						0,
						FW_BOLD,
						FALSE,
						FALSE,
						FALSE,
						ANSI_CHARSET,
						OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
						FF_DONTCARE|DEFAULT_PITCH,
						"Arial");

	SelectObject(hDC, font);

	wglUseFontOutlines(	hDC,
						0,
						255,
						base,
						0.0f,
						0.2f,
						WGL_FONT_POLYGONS,
						gmf);
}

/**
 * Delete font.
 *
 * @param GLvoid
 *
 * @author Nikola Simeonov
 *
 * @email n.simeonow@gmail.com
 *
 * @date 20 Nov 2010
 */
GLvoid KillFont(GLvoid) {
	glDeleteLists(base, 256);
}

/**
 * Custom GL print routine.
 *
 * @param fmt
 *
 * @author Nikola Simeonov
 *
 * @email n.simeonow@gmail.com
 *
 * @date 03 Nov 2010
 */
GLvoid glPrint(const char *fmt, ...) {
	/*
	 * Used to find the length of the text.
	 */
	float length = 0;

	/*
	 * Hold our string.
	 */
	char text[256];

	/*
	 * Pointer to list of arguments.
	 */
	va_list	ap;

	/*
	 * If there's no text do nothing.
	 */
	if (fmt == NULL) {
		return;
	}

	va_start(ap, fmt);
	vsprintf(text, fmt, ap);
	va_end(ap);

	/*
	 * Loop to find text length.
	 */
	for (unsigned int loop=0; loop<(strlen(text)); loop++) {
		/*
		 * Increase length by each characters width.
		 */
		length += gmf[text[loop]].gmfCellIncX;
	}

	/*
	 * Center our text on the screen.
	 */
	glTranslatef(-length/2, 0.0f, 0.0f);

	/*
	 * Pushes the display list bits.
	 */
	glPushAttrib(GL_LIST_BIT);

	/*
	 * Sets the base character to 0.
	 */
	glListBase(base);

	/*
	 * Draws the display list text.
	 */
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);

	/*
	 * Pops the display list bits.
	 */
	glPopAttrib();
}

/**
 * Initialize OpenGl.
 *
 * @param width
 *
 * @param height
 *
 * @author Nikola Simeonov
 *
 * @email n.simeonow@gmail.com
 *
 * @date 14 Dec 2010
 */
void SetupAnimation(int width, int height) {
	/*
	 * Next we set up for a perspective view.
	 */
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	/*
	 * Select the projection matrix.
	 */
	glMatrixMode(GL_PROJECTION);

	/*
	 * Reset (init) the projection matrix.
	 */
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

	/*
	 * Select the modelview matrix.
	 */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*
	 * Enable smooth shading.
	 */
	glShadeModel(GL_SMOOTH);

	/*
	 * Set black background.
	 */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);

	/*
	 * Depth buffer setup.
	 */
	glClearDepth(1.0f);

	/*
	 * Enables depth testing.
	 */
	glEnable(GL_DEPTH_TEST);

	/*
	 * The type of depth testing to do.
	 */
	glDepthFunc(GL_LEQUAL);

	/*
	 * Perspective calculations.
	 */
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	/*
	 * Enable default light (quick and dirty).
	 */
	glEnable(GL_LIGHT0);

	/*
	 * Enable lighting.
	 */
	glEnable(GL_LIGHTING);

	/*
	 * Enable coloring of material.
	 */
	glEnable(GL_COLOR_MATERIAL);

	/*
	 * Build the font.
	 */
	BuildFont();
}

/**
 * Update flying object state.
 *
 * @param object
 *
 * @author Nikola Simeonov
 *
 * @email n.simeonow@gmail.com
 *
 * @date 29 Dec 2010
 */
void updateFlyingObject(FlyingObject &object) {

	/*
	 * Increase the rotation variable.
	 */
	object.rotation += object.dry;

	if (object.dx==0 || object.dy==0) {
		object.dx = (float)rand() / RAND_MAX * 0.1;
		object.dy = (float)rand() / RAND_MAX * 0.1;
	}
	if (object.x>=10.0 || object.x<=-10.0) {
		object.dx = -object.dx;
		object.dx = (rand()%2==0) ? object.dx*1.1 : object.dx*0.9;
		object.dy = (rand()%2==0) ? object.dy*1.1 : object.dy*0.9;
	}
	if (object.y>=10.0 || object.y<-10.0) {
		object.dy = -object.dy;
		object.dx = (rand()%2==0) ? object.dx*1.1 : object.dx*0.9;
		object.dy = (rand()%2==0) ? object.dy*1.1 : object.dy*0.9;
	}

	object.x += object.dx;
	object.y += object.dy;

	/*
	 * Reset the current modelview matrix.
	 */
	glLoadIdentity();

	/*
	 * Move title object into the screen.
	 */
	glTranslatef(object.x, object.y, -25.0f);
	glRotatef(object.rotation, 0.0f, 1.0f, 0.0f);
	glColor3f(object.red, object.green, object.blue);
	glPrint( object.text );
}

/**
 * OpenGL drawing and animation.
 *
 * @param hDC
 *
 * @author Nikola Simeonov
 *
 * @email n.simeonow@gmail.com
 *
 * @date 02 Jan 2010
 */
void OnTimer(HDC hDC) {

	/*
	 * Clear screen and depth buffer.
	 */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	updateFlyingObject( title );
	updateFlyingObject( symbol );
	updateFlyingObject( period );
	updateFlyingObject( forecast );
	updateFlyingObject( direction );

	glEnd();
	SwapBuffers(hDC);
}

/**
 * Initialize GL.
 *
 * @param hWnd
 *
 * @param hDC
 *
 * @param hRC
 *
 * @author Nikola Simeonov
 *
 * @email n.simeonow@gmail.com
 *
 * @date 03 Nov 2010
 */
void InitGL(HWND hWnd, HDC &hDC, HGLRC &hRC) {
	/*
	 * Ensures data is stored between calls.
	 */
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	/*
	 * Retrieves a handle to a display device context.
	 */
	hDC = GetDC(hWnd);

	/*
	 * Try and match a pixel format supported by DC.
	 */
	int i = ChoosePixelFormat(hDC, &pfd);

	SetPixelFormat(hDC, i, &pfd);

	/*
	 * Create a new OpenGL rendering context.
	 */
	hRC = wglCreateContext(hDC);

	/*
	 * Makes OpenGL hRC the calling.
	 */
	wglMakeCurrent(hDC, hRC);
}

/**
 * Shut down OpenGL.
 *
 * @param hWnd
 *
 * @param hDC
 *
 * @param hRC
 *
 * @author Nikola Simeonov
 *
 * @email n.simeonow@gmail.com
 *
 * @date 03 Nov 2010
 */
void CloseGL(HWND hWnd, HDC hDC, HGLRC hRC) {
	/*
	 * Makes current RC no longer current.
	 */
	wglMakeCurrent(NULL, NULL);

	/*
	 * Deletes OpenGL rendering context.
	 */
	wglDeleteContext(hRC);

	/*
	 * Releases a DC, freeing it for other apps.
	 */
	ReleaseDC(hWnd, hDC);
}
