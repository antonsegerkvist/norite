//
//  table_shader.cpp
//  norite
//
//  Created by Anton Segerkvist on 26/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#include "table_shader.hpp"

OpenGLProgram _table_shader_programs[TABLE_SHADER_PROG_END];

bool TableShader_LoadDefaultPrograms()
{
  /**
   * This is unfortunatelly quit the tedious process if we want error
   * checking at each of the stages involved in creating a shader.
   */
  for(int i=TABLE_SHADER_PROG_BEGIN; i<TABLE_SHADER_PROG_END; ++i)
  {
    // Buffers for holding the source.
    std::string vert_buffer;
    std::string frag_buffer;
    
    // Load the buffers.
    if(!FileIO::ReadFromFile(vert_buffer, _table_shader_vert_shader_file[i]))
    {
      printf("Error reading data from: %s\n", _table_shader_vert_shader_file[i]);
      return false;
    }
    if(!FileIO::ReadFromFile(frag_buffer, _table_shader_frag_shader_file[i]))
    {
      printf("Error reading data from: %s\n", _table_shader_frag_shader_file[i]);
      return false;
    }
    
    // Define the shaders.
    OpenGLShader vert_shader;
    OpenGLShader frag_shader;
    
    // Create the shader objects.
    if(!vert_shader.create(GL_VERTEX_SHADER))
    {
      printf("Could not create shader from: %s\n", _table_shader_vert_shader_file[i]);
      return false;
    }
    if(!frag_shader.create(GL_FRAGMENT_SHADER))
    {
      printf("Could not create shader from: %s\n", _table_shader_frag_shader_file[i]);
      vert_shader.destroy();
      return false;
    }
    
    // Compile the shaders.
    vert_shader.compileFromCode(vert_buffer);
    frag_shader.compileFromCode(frag_buffer);
    
    // Check the compilation status.
    if(!vert_shader.getCompileStatus())
    {
      printf("Failed to compile shader from: %s\n", _table_shader_vert_shader_file[i]);
      printf("Error message: \n%s\n", vert_shader.getInfoLog().c_str());
      vert_shader.destroy();
      frag_shader.destroy();
      return false;
    }
    if(!frag_shader.getCompileStatus())
    {
      printf("Failed to compile shader from: %s\n", _table_shader_frag_shader_file[i]);
      printf("Error message: \n%s\n", frag_shader.getInfoLog().c_str());
      vert_shader.destroy();
      frag_shader.destroy();
      return false;
    }
    
    // Create program and attach shaders.
    if(!_table_shader_programs[i].create())
    {
      printf("Failed to create a shader program\n");
      vert_shader.destroy();
      frag_shader.destroy();
      return false;
    }
    
    // Attach the shaders.
    _table_shader_programs[i].attachShader(vert_shader);
    _table_shader_programs[i].attachShader(frag_shader);
    
    // Link the program.
    _table_shader_programs[i].link();
    
    // Check the link status.
    if(!_table_shader_programs[i].getLinkStatus())
    {
      // Delete shaders.
      _table_shader_programs[i].detachShader(vert_shader);
      _table_shader_programs[i].detachShader(frag_shader);
      vert_shader.destroy();
      frag_shader.destroy();
      
      //Print error message.
      printf("Failed to link: \n ->%s\n ->%s\n",
             _table_shader_vert_shader_file[i],
             _table_shader_frag_shader_file[i]);
      printf("Info log information: \n%s\n", _table_shader_programs[i].getInfoLog().c_str());
      
      // Destroy program.
      _table_shader_programs[i].destroy();
      
      // Return.
      return false;
    }
    
    // Detach and destroy the shaders.
    _table_shader_programs[i].detachShader(vert_shader);
    _table_shader_programs[i].detachShader(frag_shader);
    vert_shader.destroy();
    frag_shader.destroy();
  }
  return true;
}

void TableShader_FreeDefaultPrograms()
{
  for(int i=TABLE_SHADER_PROG_BEGIN; i<TABLE_SHADER_PROG_END; ++i)
  {
    if(_table_shader_programs[i].getProgram() != 0)
    {
      _table_shader_programs[i].destroy();
    }
    else
    {
      break; // Shaders are initialized in order.
    }
  }
}

bool TableShader_SafeLoadDefaultPrograms()
{
  if(!TableShader_LoadDefaultPrograms())
  {
    TableShader_FreeDefaultPrograms();
    return false;
  }
  return true;
}
