#version 330 core

//uniform mat4 modelview_matrix;
//uniform mat4 projection_matrix;

in vec3 vert_position;
//in uvec2 vert_texture;

out vec4 frag_position;
//out uvec2 frag_texture;

void main()
{
  frag_position = vec4(vert_position, 1.0);
  //frag_texture  = vert_texture;
  gl_Position   = frag_position;
}
