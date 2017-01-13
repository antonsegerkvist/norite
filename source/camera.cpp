//
//  camera.cpp
//  norite
//
//  Created by Anton Segerkvist on 27/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#include "camera.hpp"

/* static */ int Camera::s_w = 0;
/* static */ int Camera::s_h = 0;

/* static */ float Camera::s_fovy   = 90;
/* static */ float Camera::s_z_near = 1;
/* static */ float Camera::s_z_far  = 100;

/* static */ glm::vec3 Camera::s_center_point = glm::vec3(0, 0, 0);
/* static */ float Camera::s_xz_angle = 45.0 / 180.0 * M_PI;
/* static */ float Camera::s_y_angle  = 45.0 / 180.0 * M_PI;
/* static */ float Camera::s_radius   = 10;

/* static */ bool Camera::s_update_modelview = true;
/* static */ bool Camera::s_update_projection = true;

/* static */ glm::mat4 Camera::s_current_modelview;
/* static */ glm::mat4 Camera::s_current_projection;

/* static */ const glm::mat4& Camera::CalculateCurrentModelview()
{
  if(s_update_modelview)
  {
    s_update_modelview = false;
    
    glm::vec3 camera_point = s_center_point
                           + glm::vec3(+s_radius * sin(s_y_angle) * cos(s_xz_angle),
                                       +s_radius * cos(s_y_angle),
                                       -s_radius * sin(s_y_angle) * sin(s_xz_angle));
    glm::vec3 camera_up    = s_center_point
                           + glm::vec3(+s_radius * cos(s_y_angle) * cos(s_xz_angle),
                                       -s_radius * sin(s_y_angle),
                                       -s_radius * cos(s_y_angle) * sin(s_xz_angle));
    s_current_modelview = glm::lookAt(camera_point,
                                      s_center_point,
                                      camera_up);
    s_update_modelview = false;
  }
  return s_current_modelview;
}

/* static */ const glm::mat4& Camera::CalculateCurrentProjection()
{
  // Update the projection matrix if needed.
  if(s_update_projection)
  {
    s_current_projection = glm::perspectiveFov(s_fovy,
                                               (float)s_w,
                                               (float)s_h,
                                               s_z_near,
                                               s_z_far);
    s_update_projection = false;
  }
  return s_current_projection;
}
