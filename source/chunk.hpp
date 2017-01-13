//
//  chunk.hpp
//  norite
//
//  Created by Anton Segerkvist on 24/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#ifndef chunk_hpp
#define chunk_hpp

#include <cassert>
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "block.hpp"
#include "camera.hpp"
#include "opengl.hpp"
#include "table_shader.hpp"

class Chunk
{
public:
  
  /**
   * Constructor.
   */
  Chunk(GLfloat x_translation,
        GLfloat y_translation,
        GLfloat z_translation,
        uint16_t size_x,
        uint16_t size_y,
        uint16_t size_z);
  
  /**
   * Destructor.
   */
  ~Chunk();
  
  /**
   * Get the translation unit of the chunk in the x direction.
   */
  inline GLfloat getXTranslation() const
  { return m_x_translation; }
  
  /**
   * Get the translation unit of the chunk in the y direction.
   */
  inline GLfloat getYTranslation() const
  { return m_y_translation; }
  
  /**
   * Get the translation unit of the chunk in the z direction.
   */
  inline GLfloat getZTranslation() const
  { return m_z_translation; }
  
  /**
   * Get the number of blocks in the x direction.
   */
  inline uint16_t getSizeX() const
  { return m_size_x; }
  
  /**
   * Get the number of blocks in the y direction.
   */
  inline uint16_t getSizeY() const
  { return m_size_y; }
  
  /**
   * Get the number of blocks in the z direction.
   */
  inline uint16_t getSizeZ() const
  { return m_size_z; }
  
  /**
   * Get the block type at coordinate.
   */
  inline BlockType getBlockType(int x, int y, int z) const
  {
    assert(x >= 0 && x < m_size_x);
    assert(y >= 0 && y < m_size_y);
    assert(z >= 0 && z < m_size_z);
    return m_blocks[x][y][z].getBlockType();
  }
  
  /**
   * Set the block type att coordinate.
   */
  inline void setBlockType(int x, int y, int z, BlockType block_type)
  {
    assert(x >= 0 && x < m_size_x);
    assert(y >= 0 && y < m_size_y);
    assert(z >= 0 && z < m_size_z);
    m_blocks[x][y][z].setBlockType(block_type);
    m_update = true;
  }
  
  /**
   * Update the chunk.
   */
  void update();
  
  /**
   * Render the chunk.
   */
  void render();
  
  /**
   * Setup attributes.
   */
  static bool SetupAttributes();
  
private:
  
  // Translation of the chunk.
  GLfloat m_x_translation;
  GLfloat m_y_translation;
  GLfloat m_z_translation;
  
  // Size data.
  uint16_t m_size_x;
  uint16_t m_size_y;
  uint16_t m_size_z;
  
  // Update flag.
  bool m_update;
  
  // Block information.
  Block*** m_blocks;
  
  // Block drawing information.
  std::vector<glm::vec3>  m_position_data;
  std::vector<glm::vec3>  m_normal_data;
  std::vector<glm::uvec2> m_texture_data;
  
  // Vertex array object.
  GLuint m_vao;
  
  // Vertex buffer objects.
  GLuint m_position_vbo;
  GLuint m_normal_vbo;
  GLuint m_texture_vbo;
  
  // Uniform locations.
  static GLint s_uniform_modelview;
  static GLint s_uniform_projection;
  
  // Attribute locations.
  static GLint s_attrib_vert_position;
  static GLint s_attrib_vert_texture;
  
};

#endif /* chunk_hpp */
