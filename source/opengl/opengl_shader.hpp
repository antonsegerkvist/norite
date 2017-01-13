//
//  opengl_shader.hpp
//  norite
//
//  Created by Anton Segerkvist on 26/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#ifndef opengl_shader_hpp
#define opengl_shader_hpp

#include <cassert>
#include <string>
#include "opengl_include.hpp"

class OpenGLShader
{
public:
  
  /**
   * Constructor.
   */
  OpenGLShader();
  
  /**
   * Destructor.
   */
  ~OpenGLShader();
  
  /**
   * Get the shader identifier.
   */
  inline GLuint getShader() const
  { return m_shader; }
  
  /**
   * Create a shader of the specified type.
   * @return True on success.
   */
  bool create(GLenum type);
  
  /**
   * Delete the shader.
   */
  void destroy();
  
  /**
   * Compile shader from source code.
   * @param code The source code of the shader.
   */
  void compileFromCode(const std::string& code) const;
  
  /**
   * Check if the compilation went ok.
   * @return True if the compilation went ok.
   */
  bool getCompileStatus() const
  {
    GLint isCompiled = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &isCompiled);
    return isCompiled == GL_TRUE;
  }
  
  /**
   * Get info log from compilation.
   * @return The info log.
   */
  std::string getInfoLog() const;
  
private:
  
  GLuint m_shader;
  
};

#endif /* opengl_shader_hpp */
