//
//  driver_factory.hpp
//  norite
//
//  Created by Anton Segerkvist on 24/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#ifndef driver_factory_hpp
#define driver_factory_hpp

#include "audio_driver.hpp"
#include "video_driver.hpp"

class DriverFactory
{
public:
  
  /**
   * Initialize the drivers.
   */
  static bool InitializeDrivers();
  
  /**
   * Uninitialize the drivers.
   */
  static void UninitializeDrivers();
  
private:
  
};

#endif /* driver_factory_hpp */
