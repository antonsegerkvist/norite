//
//  table_shader.hpp
//  norite
//
//  Created by Anton Segerkvist on 26/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#ifndef table_shader_hpp
#define table_shader_hpp

#include <string>
#include "../fileio.hpp"
#include "../opengl.hpp"

/**
 * Here all the default shader programs are specified. They need to be compiled
 * and linked during start time. If any one fails, the game just exits.
 */

#define TABLE_SHADER_PROG_BEGIN            0 // For iterations.
#define TABLE_SHADER_DEFAULT_TILE_MAP_PROG 0 // Default program for drawing tile map.
#define TABLE_SHADER_PROG_END              1 // For iterations and sizes.

// Filepaths to vertex shader source.
static const char* const _table_shader_vert_shader_file[] = {
  "data/shader/default_voxel_map.vert"
};

// Filepaths to fragment shader source.
static const char* const _table_shader_frag_shader_file[] = {
  "data/shader/default_voxel_map.frag"
};

// Actual shader and program objects.
extern OpenGLProgram _table_shader_programs[TABLE_SHADER_PROG_END];

// Method for loading default shader programs.
bool TableShader_LoadDefaultPrograms();
void TableShader_FreeDefaultPrograms();
bool TableShader_SafeLoadDefaultPrograms();

#endif /* table_shader_hpp */
