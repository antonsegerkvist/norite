//
//  window.hpp
//  norite
//
//  Created by Anton Segerkvist on 27/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#ifndef window_hpp
#define window_hpp

#include <cstdio>
#include "camera.hpp"

class VideoDriver;

class Window
{
public:
  
  /**
   * Get the width of the window for this frame.
   */
  static inline int GetWidth()
  { return s_w; }
  
  /**
   * Get the height of the window for this frame.
   */
  static inline int getHeight()
  { return s_h; }
  
  /**
   * Handle minimize/maximize events.
   */
  static void HandleWindowMinimized(bool minimized);
  
  /**
   * Handle keyboard focus events.
   */
  static void HandleKeyboardFocus(bool focus);
  
  /**
   * Handle mouse focus events.
   */
  static void HandleMouseFocus(bool focus);
  
  /**
   * Handle a window resize events.
   */
  static void HandleWindowResize(int w, int h);
  
private:
  
  static bool s_is_fullscreen; // The fullscreen status.
  static bool s_is_minimized; // The minimized status.
  
  static bool s_has_keyboard_focus; // The keyboard focus status.
  static bool s_has_mouse_focus; // The mouse focus state.
  
  static int s_w; // The width of the window.
  static int s_h; // The height of the window.
  
private:
  
  friend class VideoDriver;
  
};

#endif /* window_hpp */
