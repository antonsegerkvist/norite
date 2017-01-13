//
//  video_driver.cpp
//  norite
//
//  Created by Anton Segerkvist on 24/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#include "video_driver.hpp"

// Define initialization flags.
static bool video_driver_is_video_initialized = false;
static bool video_driver_is_window_created = false;
static bool video_driver_is_context_created = false;
static bool video_driver_is_opengl_bound = false;

// SDL structures.
static SDL_Window* video_driver_window = NULL;
static SDL_GLContext video_driver_context = NULL;

/**
 * Initialize the SDL subsystems.
 * @return True on success.
 */
static bool VideoDriver_InitializeSDLVideo()
{
  // Initialize SDL video subsystem.
  if(SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
  {
    return false;
  }
  
  // Set flag and return.
  video_driver_is_video_initialized = true;
  return true;
}

/**
 * Create the game window
 * @return True on success.
 */
static bool VideoDriver_CreateWindow()
{
  // Define default parameters.
  int x = SDL_WINDOWPOS_CENTERED;
  int y = SDL_WINDOWPOS_CENTERED;
  int w = 640;
  int h = 480;
  int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
  
  // Set window OpenGL attributes.
  if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG) < 0) return false;
  if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) < 0) return false;
  if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, _opengl_version_major) < 0) return false;
  if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, _opengl_version_minor) < 0) return false;
  
  // Try to get the desktop dimensions.
  SDL_DisplayMode mode;
  if(SDL_GetCurrentDisplayMode(0, &mode) == 0)
  {
    w = mode.w * 0.8;
    h = mode.h * 0.8;
  }
  else
  {
    // Not a fatal error.
    SDL_Log("Could not get desktop dimensions! Warning: %s\n", SDL_GetError());
    SDL_ClearError();
  }
  
  // Create window.
  video_driver_window = SDL_CreateWindow("Norite", x, y, w, h, flags);
  if(video_driver_window == NULL)
  {
    return false;
  }
  
  // Inform the system of the window size.
  Window::HandleWindowResize(w, h);
  
  // Set flag and return.
  video_driver_is_window_created = true;
  return true;
}

/**
 * Create the opengl context.
 * @return True on success.
 */
static bool VideoDriver_CreateContext()
{
  video_driver_context = SDL_GL_CreateContext(video_driver_window);
  if(video_driver_context == NULL)
  {
    return false;
  }
  
  // Set flag and return.
  video_driver_is_context_created = true;
  return true;
}

/**
 * Bind OpenGL functions.
 * @return true on success.
 */
static bool VideoDriver_BindOpenGLFunctions()
{
  // Initialize gl3w.
  if(gl3wInit())
  {
    return false;
  }
  
  // Set flag and return.
  video_driver_is_opengl_bound = true;
  return true;
}


/* static */ bool VideoDriver::Initialize()
{
  // Initialize video subsystem.
  if(!VideoDriver_InitializeSDLVideo())
  {
    SDL_Log("Error: %s", SDL_GetError());
    Uninitialize();
    return false;
  }
  
  // Create the window.
  if(!VideoDriver_CreateWindow())
  {
    SDL_Log("Error: %s", SDL_GetError());
    Uninitialize();
    return false;
  }
  
  // Create the context.
  if(!VideoDriver_CreateContext())
  {
    SDL_Log("Error: %s", SDL_GetError());
    Uninitialize();
    return false;
  }
  
  // Bind OpenGL functions.
  if(!VideoDriver_BindOpenGLFunctions())
  {
    SDL_Log("Error: Could not bind OpenGL functions!");
    Uninitialize();
    return false;
  }
  
  return true;
}


/* static */ void VideoDriver::Uninitialize()
{
  if(video_driver_is_context_created)   SDL_GL_DeleteContext(video_driver_context);
  if(video_driver_is_window_created)    SDL_DestroyWindow(video_driver_window);
  if(video_driver_is_video_initialized) SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  
  video_driver_is_video_initialized = false;
  video_driver_is_window_created = false;
  video_driver_is_context_created = false;
  
  video_driver_window = NULL;
  video_driver_context = NULL;
}

/* static */ void VideoDriver::MainLoop()
{
  // Initialize the game data.
  Game::Initialize();
  
  while(!Norite::GetExitGameFlag())
  {
    // Game loop.
    Game::GameLoop();
    
    // Draw stuff.
    SDL_GL_SwapWindow(video_driver_window);
    
    // Poll all events of the event queue.
    while(PollEvent()) { }
  }
  
  // Uninitialize game resources.
  Game::Uninitialize();
}

/* static */ int VideoDriver::ToggleFullscreen()
{
  
  return 0;
}

/* static */ int VideoDriver::PollEvent()
{
  // Define variables.
  int ret;
  SDL_Event event;
  
  // Poll a single event, check return flag and dispatch event.
  ret = SDL_PollEvent(&event);
  if(ret == 0) return 0;
  
  // Handle the events.
  switch(event.type)
  {
    // Handle quit events.
    case SDL_QUIT:
      Norite::HandleExitGameRequest();
      return 0;
      break;
      
    // Handle window events.
    case SDL_WINDOWEVENT:
      switch(event.window.event)
      {
        // Handle window maximization.
        case SDL_WINDOWEVENT_MAXIMIZED:
          Window::HandleWindowMinimized(false);
          break;
          
        // Handle window minimization.
        case SDL_WINDOWEVENT_MINIMIZED:
          Window::HandleWindowMinimized(true);
          break;
          
        // Handle window restored.
        case SDL_WINDOWEVENT_RESTORED:
          Window::HandleWindowMinimized(false);
          break;
        
        // Handle keyboard gain focus event.
        case SDL_WINDOWEVENT_FOCUS_GAINED:
          Window::HandleKeyboardFocus(true);
          break;
          
        // Handle keyboard lost focus event.
        case SDL_WINDOWEVENT_FOCUS_LOST:
          Window::HandleKeyboardFocus(false);
          break;
          
        // Handle mouse enter event.
        case SDL_WINDOWEVENT_ENTER:
          Window::HandleMouseFocus(true);
          break;
          
        // Handle mouse leave event.
        case SDL_WINDOWEVENT_LEAVE:
          Window::HandleMouseFocus(false);
          break;

        // Handle window resize.
        case SDL_WINDOWEVENT_RESIZED:
        case SDL_WINDOWEVENT_SIZE_CHANGED:
          int w = event.window.data1;
          int h = event.window.data2;
          Window::HandleWindowResize(w, h);
          break;
      }
      break;
      
      // Default is to do nothing.
    default:
      break;
  }
  
  // Return the return code.
  return ret;
}
