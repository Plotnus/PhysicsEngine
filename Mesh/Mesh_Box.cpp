#include "Mesh_Box.hpp"

#include "../common/texture.hpp"
#include "../common/shader.hpp"



const GLfloat Mesh_Box::g_color_buffer_data[] = {
  0.583f,  0.771f,  0.014f,
  0.609f,  0.115f,  0.436f,
  0.327f,  0.483f,  0.844f,
  0.822f,  0.569f,  0.201f,
  0.435f,  0.602f,  0.223f,
  0.310f,  0.747f,  0.185f,
  0.597f,  0.770f,  0.761f,
  0.559f,  0.436f,  0.730f,
  0.359f,  0.583f,  0.152f,
  0.483f,  0.596f,  0.789f,
  0.559f,  0.861f,  0.639f,
  0.195f,  0.548f,  0.859f,
  0.014f,  0.184f,  0.576f,
  0.771f,  0.328f,  0.970f,
  0.406f,  0.615f,  0.116f,
  0.676f,  0.977f,  0.133f,
  0.971f,  0.572f,  0.833f,
  0.140f,  0.616f,  0.489f,
  0.997f,  0.513f,  0.064f,
  0.945f,  0.719f,  0.592f,
  0.543f,  0.021f,  0.978f,
  0.279f,  0.317f,  0.505f,
  0.167f,  0.620f,  0.077f,
  0.347f,  0.857f,  0.137f,
  0.055f,  0.953f,  0.042f,
  0.714f,  0.505f,  0.345f,
  0.783f,  0.290f,  0.734f,
  0.722f,  0.645f,  0.174f,
  0.302f,  0.455f,  0.848f,
  0.225f,  0.587f,  0.040f,
  0.517f,  0.713f,  0.338f,
  0.053f,  0.959f,  0.120f,
  0.393f,  0.621f,  0.362f,
  0.673f,  0.211f,  0.457f,
  0.820f,  0.883f,  0.371f,
  0.982f,  0.099f,  0.879f
};
const GLfloat Mesh_Box::g_position_buffer_data[] = {
  -1.0f,-1.0f,-1.0f, // triangle 1 : begin
  -1.0f,-1.0f, 1.0f,
  -1.0f, 1.0f, 1.0f, // triangle 1 : end
  1.0f, 1.0f,-1.0f, // triangle 2 : begin
  -1.0f,-1.0f,-1.0f,
  -1.0f, 1.0f,-1.0f, // triangle 2 : end
  1.0f,-1.0f, 1.0f,
  -1.0f,-1.0f,-1.0f,
  1.0f,-1.0f,-1.0f,
  1.0f, 1.0f,-1.0f,
  1.0f,-1.0f,-1.0f,
  -1.0f,-1.0f,-1.0f,
  -1.0f,-1.0f,-1.0f,
  -1.0f, 1.0f, 1.0f,
  -1.0f, 1.0f,-1.0f,
  1.0f,-1.0f, 1.0f,
  -1.0f,-1.0f, 1.0f,
  -1.0f,-1.0f,-1.0f,
  -1.0f, 1.0f, 1.0f,
  -1.0f,-1.0f, 1.0f,
  1.0f,-1.0f, 1.0f,
  1.0f, 1.0f, 1.0f,
  1.0f,-1.0f,-1.0f,
  1.0f, 1.0f,-1.0f,
  1.0f,-1.0f,-1.0f,
  1.0f, 1.0f, 1.0f,
  1.0f,-1.0f, 1.0f,
  1.0f, 1.0f, 1.0f,
  1.0f, 1.0f,-1.0f,
  -1.0f, 1.0f,-1.0f,
  1.0f, 1.0f, 1.0f,
  -1.0f, 1.0f,-1.0f,
  -1.0f, 1.0f, 1.0f,
  1.0f, 1.0f, 1.0f,
  -1.0f, 1.0f, 1.0f,
  1.0f,-1.0f, 1.0f
};


void Mesh_Box::init(const char* texturePath)
{
  
  // get a name/declare a name
  glGenVertexArrays(1, &VertexArrayID);
  // Allocate for the array/ connect it
  glBindVertexArray(VertexArrayID);
  
  // Generate Buffers
  glGenBuffers(1, &PositionBufferID);  // gl generated vert buffer id
  glGenBuffers(1, &UVBufferID);      // gl generated UV texture coord id
  // Initialize & generate textures
  //TextureID = loadDDS(texturePath);
  
  // Load and initialize shaders
  ProgramID = LoadShaders("Rendering/shaders/Simple_VS.glsl",
                          "Rendering/shaders/Simple_FS.glsl");
  //UniformID = glGetUniformLocation(UniformID, <var-name-in-shader>);
  glGetUniformLocation(ProgramID, "mvp");
}

void
Mesh_Box::render(const glm::mat4 & mvp) const
{
  // BIND SHADER
  glUseProgram(ProgramID);
  // BIND UNIFORM DATA
  glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
  // BIND POSITION BUFFER
  //glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, this->PositionBufferID);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Mesh_Box::g_position_buffer_data),
               &Mesh_Box::g_position_buffer_data[0],
               GL_STATIC_DRAW   );
  // BIND COLOR BUFFER
  //glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, UVBufferID);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(g_color_buffer_data),
               &g_color_buffer_data[0],
               GL_STATIC_DRAW   );
  
  // now for the drawing
  //Vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, this->PositionBufferID);
  glVertexAttribPointer(0,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        0,
                        (void*) 0   );
  // color
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, this->UVBufferID);
  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        0,
                        (void*) 0   );
  // gl settings
  // gl blend function
  // draw call
  glDrawArrays(GL_TRIANGLES, 0, 12*3 );
  
  // Now, disable bound arrays
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  // disable anything enabled
  
  return;
}

void
Mesh_Box::cleanup()
{
  // Delete buffers
  glDeleteBuffers(1, &PositionBufferID);
  glDeleteBuffers(1, &UVBufferID);
  
  // Delete Texture
  glDeleteTextures(1, &TextureID);
  
  // Delete Shader
  glDeleteProgram(ProgramID);
  
  return;
}