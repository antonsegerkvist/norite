//
//  opengl_program.cpp
//  norite
//
//  Created by Anton Segerkvist on 26/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#include "opengl_program.hpp"

OpenGLProgram::OpenGLProgram()
: m_program(0)
{ }

OpenGLProgram::~OpenGLProgram()
{ }

bool OpenGLProgram::create()
{
  m_program = glCreateProgram();
  return m_program != 0;
}

void OpenGLProgram::destroy()
{
  glDeleteProgram(m_program);
  m_program = 0;
}

void OpenGLProgram::attachShader(class OpenGLShader shader) const
{
  assert(m_program != 0);
  assert(shader.getShader() != 0);
  glAttachShader(m_program, shader.getShader());
}

void OpenGLProgram::detachShader(class OpenGLShader shader) const
{
  assert(m_program != 0);
  assert(shader.getShader() != 0);
  glDetachShader(m_program, shader.getShader());
}

void OpenGLProgram::link() const
{
  assert(m_program != 0);
  glLinkProgram(m_program);
}

std::string OpenGLProgram::getInfoLog() const
{
  // Get info message length.
  GLint max_length = 0;
  glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &max_length);
  
  // Retrive the message.
  std::string ret;
  ret.resize(max_length);
  glGetProgramInfoLog(m_program, max_length, &max_length, &ret[0]);
  
  // Return the message.
  return ret;
}

GLint OpenGLProgram::getUniformLocation(const GLchar *name)
{
  return glGetUniformLocation(m_program, name);
}

GLint OpenGLProgram::getAttribLocation(const GLchar* name)
{
  return glGetAttribLocation(m_program, name);
}

void OpenGLProgram::use() const
{
  assert(m_program != 0);
  glUseProgram(m_program);
}

/* static */ void OpenGLProgram::unuse()
{
  glUseProgram(0);
}
