//
//  opengl_program.hpp
//  norite
//
//  Created by Anton Segerkvist on 26/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#ifndef opengl_program_hpp
#define opengl_program_hpp

#include <cassert>
#include <string>
#include "opengl_include.hpp"
#include "opengl_shader.hpp"

class OpenGLProgram
{
public:
  
  /**
   * Constructor.
   */
  OpenGLProgram();
  
  /**
   * Destructor.
   */
  ~OpenGLProgram();
  
  /**
   * Get program identifier.
   */
  inline GLuint getProgram() const
  { return m_program; }
  
  /**
   * Create shader program object.
   * @return True on success.
   */
  bool create();
  
  /**
   * Delete shader program object.
   */
  void destroy();
  
  /**
   * Attach a shader to the program.
   * @param shader The shader to attach.
   */
  void attachShader(class OpenGLShader shader) const;
  
  /**
   * Detach a shader from the program.
   * @param shader The shader to detach.
   */
  void detachShader(class OpenGLShader shader) const;
  
  /**
   * Link the program.
   */
  void link() const;
  
  /**
   * Check if the program is linked.
   * @return True on success.
   */
  bool getLinkStatus() const
  {
    GLint isLinked = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &isLinked);
    return isLinked == GL_TRUE;
  }
  
  /**
   * Get info log from linking.
   * @return The info log.
   */
  std::string getInfoLog() const;
  
  /**
   * Get the uniform location.
   */
  GLint getUniformLocation(const GLchar* name);
  
  /**
   * Get the attribute location.
   */
  GLint getAttribLocation(const GLchar* name);
  
  /**
   * Tell the OpenGL pipeline to use this program.
   */
  void use() const;
  
  /**
   * Tell the OpenGL pipeline to use no program.
   */
  static void unuse();
  
private:
  
  GLuint m_program;
  
};

#endif /* opengl_program_hpp */
