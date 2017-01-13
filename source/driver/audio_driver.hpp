//
//  audio_driver.hpp
//  norite
//
//  Created by Anton Segerkvist on 24/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#ifndef audio_driver_hpp
#define audio_driver_hpp

class AudioDriver
{
public:
  
  /**
   * Initialize the driver.
   * @return True on success.
   */
  static bool Initialize();
  
  /**
   * Uninitialize the driver.
   */
  static void Uninitialize();
  
private:
  
};

#endif /* audio_driver_hpp */
