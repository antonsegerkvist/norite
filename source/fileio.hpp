//
//  fileio.hpp
//  norite
//
//  Created by Anton Segerkvist on 26/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#ifndef fileio_hpp
#define fileio_hpp

#include <cstdio>
#include <string>
#include "norite.hpp"

class FileIO
{
public:
  
  /**
   * Read the content of a file and store it in a buffer.
   * @param buffer The buffer to store the file content in.
   * @param filename The filename to read the data from.
   */
  static bool ReadFromFile(std::string& buffer, const std::string& filename);
  
};

#endif /* fileio_hpp */
