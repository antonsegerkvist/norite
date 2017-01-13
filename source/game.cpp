//
//  game.cpp
//  norite
//
//  Created by Anton Segerkvist on 27/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#include "game.hpp"

/* static */ uint32_t      Game::s_frame_counter = 0;
/* static */ GameInstance* Game::s_instance = 0;

Chunk* s_chunk;

/* static */ void Game::Initialize()
{
  s_chunk = new Chunk(0, 0, 0, 16, 16, 16);
  
  for(int i=0; i<16; ++i) {
    for(int j=0; j<16; ++j) {
      for(int k=0; k<16; ++k) {
        s_chunk->setBlockType(i,j,k, BT_DIRT);
      }
    }
  }
  
  
  glClearColor(0, 0, 0, 0);
}

/* static */ void Game::Uninitialize()
{
  delete s_chunk;
}

/* static */ void Game::GameLoop()
{
  ++Game::s_frame_counter;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  s_chunk->render();
}

/* static */ void Game::Pause()
{

}

/* static */ void Game::Unpause()
{

}
