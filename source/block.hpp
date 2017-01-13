//
//  block.hpp
//  norite
//
//  Created by Anton Segerkvist on 24/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#ifndef block_hpp
#define block_hpp

#include <vector>
#include <glm/glm.hpp>

enum BlockType
{
  BT_NULL,  // Air or the equivalent of nothing.
  BT_DIRT,  // Dirt block.
  BT_GRASS, // Grass block.
  BT_STONE, // Stone block.
};

/** Contains information of a single block. **/
class Block
{
public:
  
  /**
   * Constructor.
   */
  Block(BlockType block_type=BT_NULL);
  
  /**
   * Destructor.
   */
  virtual ~Block();
  
  /**
   * Is the block transparent?
   */
  inline bool isTransparent() const
  { return m_block_type == BT_NULL; }
  
  /**
   * Get the block type.
   */
  inline BlockType getBlockType() const
  { return m_block_type; }
  
  /**
   * Set the block type.
   */
  inline void setBlockType(BlockType block_type)
  { m_block_type = block_type; }
  
private:
  
  BlockType m_block_type;
  
};

#endif /* block_hpp */
