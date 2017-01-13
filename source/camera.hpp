//
//  camera.hpp
//  norite
//
//  Created by Anton Segerkvist on 27/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
  
  /**
   * Update window dimensions.
   */
  static inline void UpdateWindowSize(int w, int h)
  {
    s_w = w;
    s_h = h;
    s_update_projection = true;
  }
  
  /**
   * Update camera field of view.
   */
  static inline void UpdateFOVY(float angle)
  {
    s_fovy = angle;
    s_update_projection = true;
  }
  
  /**
   * Update near camera clipping plane.
   */
  static inline void UpdateNearClippingPlane(float near)
  {
    s_z_near = near;
    s_update_projection = true;
  }
  
  /**
   * Update far clipping plane.
   */
  static inline void UpdateFarClippingPlane(float far)
  {
    s_z_far = far;
    s_update_projection = true;
  }
  
  /**
   * Update the cameras center point.
   */
  static inline void UpdateCenterPoint(const glm::vec3& center_point)
  {
    s_center_point = center_point;
    s_update_modelview = true;
  }
  
  /**
   * Update the XZ angle.
   */
  static inline void UpdateXZAngle(float angle)
  {
    s_xz_angle = angle;
    s_update_modelview = true;
  }
  
  /**
   * Update the Y angle.
   */
  static inline void UpdateYAngle(float angle)
  {
    s_y_angle = angle;
    s_update_modelview = true;
  }
  
  /**
   * Update the view radius.
   */
  static inline void UpdateRadius(float radius)
  {
    s_radius = radius;
    s_update_modelview = true;
  }
  
  /**
   * Calculate the new modelview matrix.
   */
  static const glm::mat4& CalculateCurrentModelview();
  
  /**
   * Calculate the new projection matrix.
   */
  static const glm::mat4& CalculateCurrentProjection();
  
private:
  
  static int s_w; // The width of the screen.
  static int s_h; // The height of the screen.
  static float s_fovy; // Field of view in the y direction.
  static float s_z_near; // Near clipping plane.
  static float s_z_far; // Far clipping plane.
  
  static glm::vec3 s_center_point; // Where the camera is looking.
  static float s_xz_angle; // The angle in the xz plane.
  static float s_y_angle; // The angle on the y axis.
  static float s_radius; // The distance from the center point.
  
  static bool s_update_modelview; // If we should update the modelview.
  static bool s_update_projection; // If we should update the projection.
  static glm::mat4 s_current_modelview; // The current modelview matrix.
  static glm::mat4 s_current_projection; // The current projection matrix.
  
};

#endif /* camera_hpp */
