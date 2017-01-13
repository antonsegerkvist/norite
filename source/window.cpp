//
//  window.cpp
//  norite
//
//  Created by Anton Segerkvist on 27/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#include "window.hpp"

/* static */ bool Window::s_is_minimized = false;
/* static */ bool Window::s_is_fullscreen = false;

/* static */ bool Window::s_has_mouse_focus = false;
/* static */ bool Window::s_has_keyboard_focus = false;

/* static */ int Window::s_w = 0;
/* static */ int Window::s_h = 0;

/* static */ void Window::HandleWindowMinimized(bool minimized)
{
  s_is_minimized = minimized;
}

/* static */ void Window::HandleKeyboardFocus(bool focus)
{
  s_has_keyboard_focus = focus;
}

/* static */ void Window::HandleMouseFocus(bool focus)
{
  s_has_mouse_focus = focus;
}

/* static */ void Window::HandleWindowResize(int w, int h)
{
  s_w = w;
  s_h = h;
  Camera::UpdateWindowSize(w, h);
}
