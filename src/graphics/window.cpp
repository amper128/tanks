#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <SDL/SDL.h>
#include <unistd.h>	 // Header file for sleeping.
#include <cstdio>

#include "../global.h"

#include "../main.h"
#include "graphics.h"
#include "../system/input.h"

//храним наше окно
int window;

void init_shadows(int w, int h)
{
	if (shadow_texid != 0)
		glDeleteTextures(1, &shadow_texid);
	if (shadow_buffer != 0)
		glDeleteFramebuffersEXT(1, &shadow_buffer);
	if (rboId != 0)
		glDeleteRenderbuffersEXT(1, &rboId);

	glGenTextures(1, &shadow_texid);
	glBindTexture(GL_TEXTURE_2D, shadow_texid);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap generation included in OpenGL v1.4
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 2048, 2048, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffersEXT(1,&shadow_buffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, shadow_buffer);

	glGenRenderbuffersEXT(1,&rboId);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rboId);

	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, 2048, 2048);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, shadow_texid, 0);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rboId);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)			// We call this right after our OpenGL window is created.
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);		// This Will Clear The Background Color To Black
	glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
	glDisable(GL_DEPTH_TEST);			// Enables Depth Testing
	glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();				// Reset The Projection Matrix

	viewport_w = (GLfloat)Width/(GLfloat)Height*1024;
	viewport_h = 1024;
	glOrtho(-viewport_w/2, viewport_w/2, -viewport_h/2, viewport_h/2, -128, 256);
	win_to_map_x = (GLfloat)Width/(((GLfloat)Width/(GLfloat)Height*512));
	win_to_map_y = -(GLfloat)Height/512;
	//gluPerspective(90.0f,(GLfloat)Width/(GLfloat)Height,0.1f,300.0f);	// Calculate The Aspect Ratio Of The Window

	window_width = Width;
	window_height = Height;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

//	printf("init glew...\n");
	glewInit();

	printf("init light buffer...\n");
	init_shadows(Width, Height);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
	printf("resize\n");
	if (Height<480)				// Prevent A Divide By Zero If The Window Is Too Small
		Height=480;
	if (Width<640)
		Width=640;

//	InitGL(Width, Height);
	glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	viewport_w = (GLfloat)Width/(GLfloat)Height*1024;
	viewport_h = 1024;
	glOrtho(-viewport_w/2, viewport_w/2, -viewport_h/2, viewport_h/2, -128, 256);
	win_to_map_x = (GLfloat)Width/(((GLfloat)Width/(GLfloat)Height*512));
	win_to_map_y = -(GLfloat)Height/512;

	window_width = Width;
	window_height = Height;

	//gluPerspective(75.0f,(GLfloat)Width/(GLfloat)Height,0.1f,300.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	init_shadows(Width, Height);
}

int initwnd(int argc, char **argv)
{
	/* Initialize GLUT state - glut will take any command line arguments that pertain to it or
	X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */
//	printf("init glew...\n");
//	glewInit();
//	printf("init glut...\n");
//	glutInit(&argc, argv);

	/* Select type of Display mode:
	Double buffer
	RGBA color
	Alpha components supported
	Depth buffer */
//	printf("setting up glut...\n");
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_MULTISAMPLE);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_MULTISAMPLE);

//	glutInitWindowSize(1280, 720);

//	glutInitWindowPosition(0, 0);

//	printf("creating window...\n");
//	window = glutCreateWindow("Tanks");
//	printf("ok...\n");
	/* Register the function to do all our OpenGL drawing. */
	//glutDisplayFunc(&DrawGLScene);
	//glutDisplayFunc(NULL);

	/* Go fullscreen.  This is as soon as possible. */
//	if (settings.gm_fullscreen == true) glutFullScreen();

	/* Even if there are no events, redraw our gl scene. */
//	glutIdleFunc(&gameloop);

	/* Register the function called when our window is resized. */
//	glutReshapeFunc(&ReSizeGLScene);
//	glutReshapeFunc(&ReSizeGLScene);
//	glutReshapeFunc(&ReSizeGLScene);

	printf("starting keyboard worker...\n");

	/* Register the function called when the keyboard is pressed. */
	//glutKeyboardFunc(&keyPressed);
//	glutKeyboardFunc(&press_key);
//	glutKeyboardUpFunc(&up_key);

//	glutSpecialFunc(&press_sp_key);
//	glutSpecialUpFunc(&up_sp_key);
	//glutMotionFunc(&MouseMoveFunc);
//	glutPassiveMotionFunc(&MouseMoveFunc);

	/* Initialize our window. */
	printf("init GL graphic...\n");
	InitGL(800, 600);

	/* Start Event Processing Engine */

	return 0;
}

void exit_game()
{
//	glDeleteTextures(1, &shadow_texid);
//	glDeleteFramebuffersEXT(1, &shadow_buffer);
//	glDeleteRenderbuffersEXT(1, &rboId);
//	glutDestroyWindow(window);
	exit(0);
}
