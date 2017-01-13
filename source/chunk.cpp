//
//  chunk.cpp
//  norite
//
//  Created by Anton Segerkvist on 24/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#include "chunk.hpp"
#include <iostream>

/* static */ GLint Chunk::s_uniform_modelview    = 0;
/* static */ GLint Chunk::s_uniform_projection   = 0;
/* static */ GLint Chunk::s_attrib_vert_position = 0;
/* static */ GLint Chunk::s_attrib_vert_texture  = 0;

Chunk::Chunk(GLfloat x_translation,
             GLfloat y_translation,
             GLfloat z_translation,
             uint16_t size_x,
             uint16_t size_y,
             uint16_t size_z)
: m_x_translation(x_translation)
, m_y_translation(y_translation)
, m_z_translation(z_translation)
, m_size_x(size_x)
, m_size_y(size_y)
, m_size_z(size_z)
, m_update(false)
, m_blocks(0)
, m_position_data()
, m_normal_data()
, m_texture_data()
, m_vao(0)
, m_position_vbo(0)
, m_normal_vbo(0)
, m_texture_vbo(0)
{
  // Generate a vertex array object.
  glGenVertexArrays(1, &m_vao);
  
  // Generate a vertex buffer objects.
  glGenBuffers(1, &m_position_vbo);
  glGenBuffers(1, &m_normal_vbo);
  glGenBuffers(1, &m_texture_vbo);
  
  // Alocate an empty chunk.
  m_blocks = new Block** [m_size_x];
  for(int i=0; i<m_size_x; ++i) {
    m_blocks[i] = new Block* [m_size_y];
  }
  for(int i=0; i<m_size_x; ++i) {
    for(int j=0; j<m_size_y; ++j) {
      m_blocks[i][j] = new Block [m_size_z];
    }
  }
}

Chunk::~Chunk()
{
  glDeleteBuffers(1, &m_position_vbo);
  glDeleteBuffers(1, &m_normal_vbo);
  glDeleteBuffers(1, &m_texture_vbo);
  glDeleteVertexArrays(1, &m_vao);
}

void Chunk::update()
{
  // Don't update unless the chunk has changed.
  if(!m_update) return;
  
  // Empty the data buffers.
  m_position_data.clear();
  m_normal_data.clear();
  m_texture_data.clear();
  
  // Append the vertex data.
  for(int x=0; x<m_size_x; ++x) {
    for(int y=0; y<m_size_y; ++y) {
      for(int z=0; z<m_size_z; ++z) {
        // If the
        if(m_blocks[x][y][z].getBlockType() == BT_NULL) continue;
        
        // Down y surface coordinates.
        if(y == 0 || m_blocks[x][y-1][z].isTransparent()) {
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+0+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+0+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+0+m_y_translation,
                                               z+1+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+0+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+0+m_y_translation,
                                               z+1+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+0+m_y_translation,
                                               z+1+m_z_translation));
        }
        
        // Up y surface.
        if(y == m_size_y-1 || m_blocks[x][y+1][z].isTransparent()) {
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+1+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+1+m_y_translation,
                                               z+1+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+1+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+1+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+1+m_y_translation,
                                               z+1+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+1+m_y_translation,
                                               z+1+m_z_translation));
        }
        
        // Left x surface.
        if(x == 0 || m_blocks[x-1][y][z].isTransparent()) {
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+0+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+1+m_y_translation,
                                               z+1+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+1+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+0+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+0+m_y_translation,
                                               z+1+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+1+m_y_translation,
                                               z+1+m_z_translation));
        }
        
        // Right x surface.
        if(x == m_size_x-1 || m_blocks[x+1][y][z].isTransparent()) {
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+0+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+1+m_y_translation,
                                               z+1+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+1+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+0+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+1+m_y_translation,
                                               z+1+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+0+m_y_translation,
                                               z+1+m_z_translation));
        }
        
        // Left z surface.
        if(z == 0 || m_blocks[x][y][z-1].isTransparent()) {
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+0+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+1+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+0+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+0+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+1+m_y_translation,
                                               z+0+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+1+m_y_translation,
                                               z+0+m_z_translation));
        }
        
        // Right z surface.
        if(z == 0 || m_blocks[x][y][z+1].isTransparent()) {
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+0+m_y_translation,
                                               z+1+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+0+m_y_translation,
                                               z+1+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+1+m_y_translation,
                                               z+1+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+0+m_y_translation,
                                               z+1+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+1+m_x_translation,
                                               y+1+m_y_translation,
                                               z+1+m_z_translation));
          m_position_data.push_back(glm::uvec3(x+0+m_x_translation,
                                               y+1+m_y_translation,
                                               z+1+m_z_translation));
        }
      }
    }
  }
  
  // Bind the vertex array object.
  
  // Update vertex positions buffer.
  glBindBuffer(GL_ARRAY_BUFFER, m_position_vbo);
  glBufferData(GL_ARRAY_BUFFER, m_position_data.size() * sizeof(GLfloat) * 3,
                                m_position_data.data(),
                                GL_DYNAMIC_DRAW);
  
  /*
  // Update vertex texture buffer.
  glBindBuffer(GL_ARRAY_BUFFER, m_texture_vbo);
  glBufferData(GL_ARRAY_BUFFER, m_texture_data.size() * sizeof(GLfloat) * 2,
                                m_texture_data.data(),
                                GL_DYNAMIC_DRAW);
  */
  
  m_update = false;
}

void Chunk::render()
{
  if(m_update) update();
  
  // Get the program.
  OpenGLProgram program = _table_shader_programs[TABLE_SHADER_DEFAULT_TILE_MAP_PROG];
  
  // Enable culling and depth test.
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  
  // Use the program.
  program.use();
  
  // Bind vertex array objet.
  glBindVertexArray(m_vao);
  
  // Set uniform values.
  glUniformMatrix4fv(s_uniform_modelview,
                     1,
                     GL_FALSE,
                     glm::value_ptr(Camera::CalculateCurrentModelview()));
  glUniformMatrix4fv(s_uniform_projection,
                     1,
                     GL_FALSE,
                     glm::value_ptr(Camera::CalculateCurrentProjection()));
  
  // Bind buffer attribute objects.
  glBindBuffer(GL_ARRAY_BUFFER, m_position_vbo);
  glVertexAttribPointer(s_attrib_vert_position, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_position_data.size());
  //glBindBuffer(GL_ARRAY_BUFFER, m_texture_vbo);
  //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  
}

/* static */ bool Chunk::SetupAttributes()
{
  OpenGLProgram program = _table_shader_programs[TABLE_SHADER_DEFAULT_TILE_MAP_PROG];
  
  s_uniform_modelview    = program.getUniformLocation("modelview_matrix");
  s_uniform_projection   = program.getUniformLocation("projection_matrix");
  s_attrib_vert_position = program.getAttribLocation("vert_position");
  
  std::cout << s_uniform_modelview    << std::endl;
  std::cout << s_uniform_projection   << std::endl;
  std::cout << s_attrib_vert_position << std::endl;
  
  return s_uniform_modelview    != -1
      && s_uniform_projection   != -1
      && s_attrib_vert_position != -1;
}
