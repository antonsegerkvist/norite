//
//  opengl_shader.cpp
//  norite
//
//  Created by Anton Segerkvist on 26/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#include "opengl_shader.hpp"

OpenGLShader::OpenGLShader()
: m_shader(0)
{ }

OpenGLShader::~OpenGLShader()
{ }

bool OpenGLShader::create(GLenum type)
{
  m_shader = glCreateShader(type);
  return m_shader != 0;
}

void OpenGLShader::destroy()
{
  glDeleteShader(m_shader);
  m_shader = 0;
}

void OpenGLShader::compileFromCode(const std::string& code) const
{
  // Should only be called if there is a shader object.
  assert(m_shader != 0);
  
  // Send the vertex shader source code to GL.
  const GLchar* source = (const GLchar*)code.c_str();
  glShaderSource(m_shader, 1, &source, NULL);
  
  // Compile the shader.
  glCompileShader(m_shader);
}

std::string OpenGLShader::getInfoLog() const
{
  // Get info message length.
  GLint max_length = 0;
  glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &max_length);
  
  // Retrive the message.
  std::string ret;
  ret.resize(max_length);
  glGetShaderInfoLog(m_shader, max_length, &max_length, &ret[0]);
  
  // Return the message.
  return ret;
}
