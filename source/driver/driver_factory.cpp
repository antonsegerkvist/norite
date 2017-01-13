//
//  driver_factory.cpp
//  norite
//
//  Created by Anton Segerkvist on 24/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#include "driver_factory.hpp"

/* static */ bool DriverFactory::InitializeDrivers()
{
  if(!AudioDriver::Initialize()) return false;
  if(!VideoDriver::Initialize()) return false;
  return true;
}

/* static */ void DriverFactory::UninitializeDrivers()
{
  VideoDriver::Uninitialize();
}
