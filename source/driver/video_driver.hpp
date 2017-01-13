//
//  video_driver.hpp
//  norite
//
//  Created by Anton Segerkvist on 24/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#ifndef video_driver_hpp
#define video_driver_hpp

#include <string>
#include <SDL2/SDL.h>
#include "../game.hpp"
#include "../opengl.hpp"
#include "../norite.hpp"
#include "../window.hpp"

class VideoDriver
{
public:
  
  /**
   * Initialize the video subsystem.
   * @return True on success.
   */
  static bool Initialize();
  
  /**
   * Uninitialize the video subsystem.
   */
  static void Uninitialize();
  
  /**
   * Enter the main loop of the video subsystem.
   */
  static void MainLoop();
  
private:
  
  static int ToggleFullscreen();
  
  static int PollEvent();
  
};

#endif /* video_driver_hpp */
