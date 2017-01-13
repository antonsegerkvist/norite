//
//  fileio.cpp
//  norite
//
//  Created by Anton Segerkvist on 26/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#include "fileio.hpp"

/* static */ bool FileIO::ReadFromFile(std::string& buffer, const std::string& filename)
{
  // Define file pointer.
  FILE* file = NULL;
  
  // Try to open the file.
  file = fopen(filename.c_str(), "r");
  if(file == NULL) return false;
  
  // Seek the end of the file.
  if(fseek(file, 0, SEEK_END) != 0)
  {
    fclose(file);
    return false;
  }
  
  // Get the size of the file.
  long int buf_size = ftell(file);
  if(buf_size == -1)
  {
    fclose(file);
    return false;
  }
  
  // Seek the begining of the file.
  if(fseek(file, 0, SEEK_SET) != 0)
  {
    fclose(file);
    return false;
  }
  
  // Resize the string object.
  buffer.resize(buf_size-1);
  
  // Read the buffer.
  // @note includes EOF char.
  size_t new_size = fread(&buffer[0], sizeof(char), buf_size-1, file);
  
  // Check for inconsistency.
  if(new_size != buf_size-1)
  {
    fclose(file);
    printf("hello");
    return false;
  }
  
  // Close the file and return.
  fclose(file);
  return true;
}
