#include "text2D.hpp"

#include "../common/texture.hpp"
#include "../common/shader.hpp"

#include <vector>
#include <cstring>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>

// Globals for our buffer and shader ID
GLuint Text2DTextureID;
GLuint Text2DVertexBufferID;
GLuint Text2DUVBufferID;
GLuint Text2DProgramID;
GLuint Text2DUniformID;

void
initText2D(const char* texturePath)
{
  // initialize texture
  Text2DTextureID = loadDDS(texturePath);
  
  //initialize the VBO (vertex buffer objects)
  glGenBuffers(1, &Text2DVertexBufferID);
  glGenBuffers(1, &Text2DUVBufferID);
  
  //initialize shader
  //Text2DProgramID = LoadShaders("Text2D_VS.glsl", "Text2D_FS.glsl");
  Text2DProgramID = LoadShaders("Text2D_VS.glsl", "Text2D_FS.glsl");
  
  //initialize uniform ids
  Text2DUniformID = glGetUniformLocation( Text2DProgramID, "myTextureSampler");
}

void
printText2D(const char* text,
            int x, int y, int size)
{
  unsigned int length = strlen(text);
  
  // first fill these buffers
  std::vector <glm::vec2> vertices;
  std::vector <glm::vec2> uvs;
    // now for the computation
  for (int i = 0; i < length; ++i)
  {
    // first for the vertices
    glm::vec2 vertex_up_left      = glm::vec2(x + i*size     , y+size );
    glm::vec2 vertex_up_right     = glm::vec2(x + (i+1)*size , y+size );
    glm::vec2 vertex_down_right   = glm::vec2(x + (i+1)*size , y      );
    glm::vec2 vertex_down_left    = glm::vec2(x + i*size     , y      );
    
    // now to push them into their buffers
      // tri-1 of rectangular billboard
    vertices.push_back(vertex_up_left);
    vertices.push_back(vertex_down_left);
    vertices.push_back(vertex_up_right);
      //tri 2 of rectangular billboard
    vertices.push_back(vertex_down_right);
    vertices.push_back(vertex_up_right);
    vertices.push_back(vertex_down_left);
    
    
    // now for the uv
    char character = text[i];
    float uv_x = (character%16)/16.f;
    float uv_y = (character/16)/16.f;
    float deltaUV = 1/16.f;
    glm::vec2 uv_up_left      = glm::vec2(uv_x          , uv_y);
    glm::vec2 uv_up_right     = glm::vec2(uv_x + deltaUV, uv_y);
    glm::vec2 uv_down_right   = glm::vec2(uv_x + deltaUV, uv_y + deltaUV);
    glm::vec2 uv_down_left    = glm::vec2(uv_x          , uv_y + deltaUV);
    // now to push them in the same order as we pushed the vertices
      //upper tri
    uvs.push_back(uv_up_left);
    uvs.push_back(uv_down_left);
    uvs.push_back(uv_up_right);
      // lower-tri
    uvs.push_back(uv_down_right);
    uvs.push_back(uv_up_right);
    uvs.push_back(uv_down_left);
  }
  // now that we have our data lets make our open gl calls & bindings
  // bind and send data for vertex positions
  glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
  glBufferData(GL_ARRAY_BUFFER,
              vertices.size() * sizeof(glm::vec2),
              &vertices[0],
              GL_STATIC_DRAW   );
  // bind and send data for uv-coords
  glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
  glBufferData(GL_ARRAY_BUFFER,
               uvs.size() * sizeof(glm::vec2),
               &uvs[0],
               GL_STATIC_DRAW   );
  // bind and write data for shader
  glUseProgram(Text2DProgramID);
  // bind texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Text2DTextureID);
  // Set our "mytextureSampler" sampler to use Texture Unit 0
  glUniform1i(Text2DUniformID, 0);
  
  // now for the drawing
    //vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
  glVertexAttribPointer(0,       // layout #
                        2,       // elements per vertex
                        GL_FLOAT,// element atomic type
                        GL_FALSE,// normalized?
                        0,       // stride
                        (void*) 0// offset
                        );
    //uvs
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
  glVertexAttribPointer(1,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        0,
                        (void*) 0
                        );
  
  //gl settings
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  // Draw call
  glDrawArrays(GL_TRIANGLES, 0, vertices.size());
  
  // Cleanup, leave it how you found it
  glDisable(GL_BLEND);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void
cleanupText2D()
{
  // delet all that text2D data
  glDeleteBuffers(1, &Text2DVertexBufferID);
  glDeleteBuffers(1, &Text2DUVBufferID);
  // delete texture
  glDeleteTextures(1, &Text2DTextureID);
  // delete shader
  glDeleteProgram(Text2DProgramID);
}