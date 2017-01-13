//
//  game.hpp
//  norite
//
//  Created by Anton Segerkvist on 27/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "chunk.hpp"
#include "game_instance.hpp"
#include "opengl.hpp"
#include "table/table_shader.hpp"
#include "window.hpp"

class Game
{
public:
  
  /**
   * Initialize the game resources.
   */
  static void Initialize();
  
  /**
   * Uninitialize the game resources.
   */
  static void Uninitialize();
  
  /**
   * The game loop.
   */
  static void GameLoop();
  
  /**
   * Pause the game.
   */
  static void Pause();
  
  /**
   * Unpause the game.
   */
  static void Unpause();
  
private:
  
  static uint32_t s_frame_counter;
  static GameInstance* s_instance;
  
};

#endif /* game_hpp */
