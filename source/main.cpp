//
//  main.cpp
//  norite
//
//  Created by Anton Segerkvist on 24/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#include <cstdlib>
#include "driver/driver_factory.hpp"
#include "table/table_shader.hpp"
#include "block.hpp"

int main(int argc, char** argv)
{
  // Initialize the drivers.
  if(!DriverFactory::InitializeDrivers()) return EXIT_FAILURE;
  
  // Load default shaders.
  if(!TableShader_SafeLoadDefaultPrograms()) return EXIT_FAILURE;
  
  // Enter main loop.
  VideoDriver::MainLoop();
  
  // Free resources.
  TableShader_FreeDefaultPrograms();
  DriverFactory::UninitializeDrivers();
  return EXIT_SUCCESS;
}
