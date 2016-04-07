#include "Mesh_Box_Line.hpp"
#
#include "../common/texture.hpp"
#include "../common/shader.hpp"



const GLfloat Mesh_Box_Line::g_position_buffer_data[] = {
  -1.0f,-1.0f,-1.0f, // line 01
  +1.0f,-1.0f,-1.0f,
  -1.0f,-1.0f,-1.0f, // line 02
  -1.0f,+1.0f,-1.0f,
  -1.0f,-1.0f,-1.0f, // line 03
  -1.0f,-1.0f,+1.0f,
  
  -1.0f,+1.0f,+1.0f, // line 04
  +1.0f,+1.0f,+1.0f,
  -1.0f,+1.0f,+1.0f, // line 05
  -1.0f,-1.0f,+1.0f,
  -1.0f,+1.0f,+1.0f, // line 06
  -1.0f,+1.0f,-1.0f,
  
  +1.0f,-1.0f,+1.0f, // line 07
  -1.0f,-1.0f,+1.0f,
  +1.0f,-1.0f,+1.0f, // line 08
  +1.0f,+1.0f,+1.0f,
  +1.0f,-1.0f,+1.0f, // line 09
  +1.0f,-1.0f,-1.0f,
  
  +1.0f,+1.0f,-1.0f, // line 10
  -1.0f,+1.0f,-1.0f,
  +1.0f,+1.0f,-1.0f, // line 11
  +1.0f,-1.0f,-1.0f,
  +1.0f,+1.0f,-1.0f, // line 12
  +1.0f,+1.0f,+1.0f,
  
};

const GLfloat Mesh_Box_Line::g_color_buffer_data[] = {
  +0.0f,+1.0f,+1.0f, // line 01
  +0.0f,+1.0f,+1.0f,
  +0.0f,+1.0f,+1.0f,// line 02
  +0.0f,+1.0f,+1.0f,
  +0.0f,+1.0f,+1.0f,// line 03
  +0.0f,+1.0f,+1.0f,
  
  +0.0f,+1.0f,+1.0f,// line 04
  +0.0f,+1.0f,+1.0f,
  +0.0f,+1.0f,+1.0f,// line 05
  +0.0f,+1.0f,+1.0f,
  +0.0f,+1.0f,+1.0f,// line 06
  +0.0f,+1.0f,+1.0f,
  
  +0.0f,+1.0f,+1.0f,// line 07
  +0.0f,+1.0f,+1.0f,
  +0.0f,+1.0f,+1.0f,// line 08
  +0.0f,+1.0f,+1.0f,
  +0.0f,+1.0f,+1.0f,// line 09
  +0.0f,+1.0f,+1.0f,
  
  +0.0f,+1.0f,+1.0f,// line 10
  +0.0f,+1.0f,+1.0f,
  +0.0f,+1.0f,+1.0f,// line 11
  +0.0f,+1.0f,+1.0f,
  +0.0f,+1.0f,+1.0f,// line 12
  +0.0f,+1.0f,+1.0f,
  
};


void
Mesh_Box_Line::init(const char* texturePath)
{
  
  // Generate Buffers
  glGenBuffers(1, &PositionBufferID);  // gl generated vert buffer id
  glBindBuffer(GL_ARRAY_BUFFER, PositionBufferID);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(g_position_buffer_data),
               g_position_buffer_data,
               GL_STATIC_DRAW);
  
  glGenBuffers(1, &ColorBufferID);      // gl generated UV texture coord id
  glBindBuffer(GL_ARRAY_BUFFER, ColorBufferID);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(g_color_buffer_data),
               g_color_buffer_data,
               GL_STATIC_DRAW);
  

  glVertexAttribPointer(0,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        0,
                        (void*) 0   );
  
  //glBindBuffer(GL_ARRAY_BUFFER, this->ColorBufferID);
  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        0,
                        (void*) 0   );

  
  // Load and initialize shaders
  ProgramID = LoadShaders("Simple_VS.glsl", "Simple_FS.glsl");       // gl generated shader program id
  //UniformID = glGetUniformLocation(UniformID, <var-name-in-shader>);
  glGetUniformLocation(ProgramID, "mvp");
}

void
Mesh_Box_Line::render(const glm::mat4 & mvp) const
{
  // BIND SHADER
  glUseProgram(ProgramID);
  // BIND UNIFORM DATA
  glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
 
  
//  glBindBuffer(GL_ARRAY_BUFFER, this->PositionBufferID);
//  glBufferData(GL_ARRAY_BUFFER,
//               sizeof(g_position_buffer_data),
//               &g_position_buffer_data[0],
//               GL_STATIC_DRAW   );
  // BIND COLOR BUFFER
//  glBindBuffer(GL_ARRAY_BUFFER, ColorBufferID);
//  glBufferData(GL_ARRAY_BUFFER,
//               sizeof(g_color_buffer_data),
//               &g_color_buffer_data[0],
//               GL_STATIC_DRAW   );
  
  // now for the drawing
  //Vertices
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  
  //glBindBuffer(GL_ARRAY_BUFFER, this->PositionBufferID);
//  glVertexAttribPointer(0,
//                        3,
//                        GL_FLOAT,
//                        GL_FALSE,
//                        0,
//                        (void*) 0   );
//
//  //glBindBuffer(GL_ARRAY_BUFFER, this->ColorBufferID);
//  glVertexAttribPointer(1,
//                        3,
//                        GL_FLOAT,
//                        GL_FALSE,
//                        0,
//                        (void*) 0   );

  
  glDrawArrays(GL_LINES, 0, 12*2 );
  
  
  // Now, disable bound arrays
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  // disable anything enabled
  
  return;
}

void
Mesh_Box_Line::cleanup()
{
  // Delete buffers
  glDeleteBuffers(1, &PositionBufferID);
  glDeleteBuffers(1, &ColorBufferID);
  
  
  // Delete Shader
  glDeleteProgram(ProgramID);
  
  return;
}