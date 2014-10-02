#pragma once

#ifdef _WIN32
#include "windows.h"
#endif

#include "GL/glut.h"

#ifdef _WIN32
#include "glext.h"
#endif


#include <stdio.h>

#ifdef _WIN32
// As microsoft did not maintain openGL after version 1.1, Windows platform need to go throught this crap ; macosX and Linux are fine.
// This block simply retries openGL function needed for this example.
// I recommend to use GLEW instead of going this way. This is done this way only to ease beginner's compilation and portability


PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;

// FrameBuffer (FBO) gen, bin and texturebind
PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT ;
PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT ;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT ;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT ;


// Shader functions
PFNGLCREATEPROGRAMOBJECTARBPROC  glCreateProgramObjectARB ;
PFNGLUSEPROGRAMOBJECTARBPROC     glUseProgramObjectARB   ;
PFNGLCREATESHADEROBJECTARBPROC   glCreateShaderObjectARB ;
PFNGLSHADERSOURCEARBPROC         glShaderSourceARB        ;
PFNGLCOMPILESHADERARBPROC        glCompileShaderARB       ;
PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
PFNGLATTACHOBJECTARBPROC         glAttachObjectARB        ;
PFNGLLINKPROGRAMARBPROC          glLinkProgramARB         ;
PFNGLGETUNIFORMLOCATIONARBPROC   glGetUniformLocationARB  ;
PFNGLUNIFORM1IARBPROC            glUniform1iARB           ;
PFNGLACTIVETEXTUREARBPROC		  glActiveTextureARB;
PFNGLGETINFOLOGARBPROC           glGetInfoLogARB          ;

void getOpenGLFunctionPointers(void)
{
	// FBO
	glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glGenFramebuffersEXT		= (PFNGLGENFRAMEBUFFERSEXTPROC)		wglGetProcAddress("glGenFramebuffersEXT");
	glBindFramebufferEXT		= (PFNGLBINDFRAMEBUFFEREXTPROC)		wglGetProcAddress("glBindFramebufferEXT");
	glFramebufferTexture2DEXT	= (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)wglGetProcAddress("glFramebufferTexture2DEXT");
	glCheckFramebufferStatusEXT	= (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)wglGetProcAddress("glCheckFramebufferStatusEXT");
	
	//Shaders
	glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)wglGetProcAddress("glCreateProgramObjectARB");
	glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)wglGetProcAddress("glUseProgramObjectARB");
	glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)wglGetProcAddress("glCreateShaderObjectARB");
	glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)wglGetProcAddress("glShaderSourceARB"); 
	glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)wglGetProcAddress("glCompileShaderARB"); 
	glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)wglGetProcAddress("glGetObjectParameterivARB"); 
	glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)wglGetProcAddress("glAttachObjectARB"); 
	glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)wglGetProcAddress("glGetInfoLogARB");
	glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)wglGetProcAddress("glLinkProgramARB");
	glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC)wglGetProcAddress("glGetUniformLocationARB");
	glUniform1iARB = (PFNGLUNIFORM1IARBPROC)wglGetProcAddress("glUniform1iARB");
	
}
#endif

GLhandleARB loadShader(char* filename, unsigned int type);
