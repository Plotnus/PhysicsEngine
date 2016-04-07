#include "RenderManager.hpp"

// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <glfw3.h>
// Include glm
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>



#include "../Core/Transform.hpp"

#include "../Core/GameObject.hpp"
#include "../Core/Model.hpp"
#include "../Core/Mesh.hpp"
#include "../Core/Material.hpp"

#include "../common/shader.hpp"


struct MeshGLuints
{
  static GLuint VAO_ID;
  
  enum Buffer_IDs {PositionBuffer, ColorBuffer, NormalBuffer, NumBuffers};
  enum Attrib_IDs {vPosition = 0, vColor = 1, vNormal = 2};
  enum Uniform_UDs{uMVP, uM, NumUniforms};
  
  static GLuint Buffers[NumBuffers];
  static GLuint ProgramID;
  static GLuint Uniforms[NumUniforms];
  
};

struct LineGLuints
{
  static GLuint VAO_ID;
  
  enum Buffer_IDs {PositionBuffer, NumBuffers};
  enum Attrib_IDs {b_vPosition = 0};
  enum Uniform_UDs{u_MVP, u_Color, NumUniforms};
  
  static GLuint Buffers[NumBuffers];
  //static GLuint ProgramID;
  static GLuint Uniforms[NumUniforms];
  // string names for uniform locations
  
};
enum VAO_IDs {BoxMesh, BoxLine, PlaneMesh, PlaneLine, NumVAOs};//Planes, Boxes, Spheres, NumVAOs};

namespace Program{
  enum Program   {Mesh, LineMesh, NumberOf};
};
namespace Object{
  enum Object_IDs   {Plane, Box, Sphere, NumberOf};
};

enum Buffer_IDs   {PositionBuffer, ColorBuffer, NormalBuffer, NumBuffers};

namespace MeshAttributeID{
enum Attrib_IDs   {vPosition = 0 , vColor = 1, vNormal = 2};//vNormals = 1};
};


GLuint mvpID; // todo consider making array for shader variables
GLuint line_mvpID;
glm::mat4 MVP;
GLuint mID;
glm::mat4 M;
GLuint u_ColorID;

GLuint VAOs[NumVAOs];
GLuint Buffers[NumVAOs][NumBuffers];
GLuint ProgramIDs[Program::NumberOf];

const GLuint NumVertices = 36;
extern GLFWwindow* window;


void
RenderManager::init()
{
  glClearColor(0.0f, 0.0f, 0.3f, 0.0f); // set default fragment color
  glEnable(GL_DEPTH_TEST);  // enable depth test
  glDepthFunc(GL_LESS);     // accept fragment if it is closer to the camera than the former frag
  //glEnable(GL_CULL_FACE);
  

  glGenVertexArrays(NumVAOs, VAOs);
  
// SETUP BOXMESH RENDERER
  glBindVertexArray(VAOs[BoxMesh]);
//  glBindVertexArray(VAOs[Planes]);
//  glBindVertexArray(VAOs[Boxes]);
//  glBindVertexArray(VAOs[Spheres]);
  ProgramIDs[Program::Mesh] = LoadShaders(Material::Phong_Monochrome.vertexshader.c_str(),
                                  Material::Phong_Monochrome.fragmentshader.c_str()
                                  );
  glUseProgram(ProgramIDs[Program::Mesh]);
  // Generate and bind buffer objects
  glGenBuffers(NumBuffers, Buffers[BoxMesh]);
  // now for each buffer
    //position buffer
  glBindBuffer(GL_ARRAY_BUFFER, Buffers[BoxMesh][PositionBuffer]);
  glBufferData( GL_ARRAY_BUFFER
               ,Mesh::BoxMesh.vertexPositions.size() * sizeof(glm::vec3)+100//vertices)     // size of the buffer data in bytes
               ,&(Mesh::BoxMesh.vertexPositions[0])//vertices       // pointer to the buffer data
               ,GL_STATIC_DRAW
               );
  //color buffer
  glBindBuffer(GL_ARRAY_BUFFER, Buffers[BoxMesh][ColorBuffer]);
  glBufferData( GL_ARRAY_BUFFER
               ,Mesh::BoxMesh.vertexColors.size() * sizeof(glm::vec3)     // size of the buffer data in bytes
               ,&(Mesh::BoxMesh.vertexColors[0])       // pointer to the buffer data
               ,GL_STATIC_DRAW
               );
  //normal buffer
  glBindBuffer(GL_ARRAY_BUFFER, Buffers[BoxMesh][NormalBuffer]);
  glBufferData( GL_ARRAY_BUFFER
               ,Mesh::BoxMesh.vertexNormals.size() * sizeof(glm::vec3)     // size of the buffer data in bytes
               ,&(Mesh::BoxMesh.vertexNormals[0])       // pointer to the buffer data
               ,GL_STATIC_DRAW
               );
  // transform ID //TODO: switch to GL_ARRAY_BUFFER, I've heard its faster/better practice
  mvpID = glGetUniformLocation(ProgramIDs[Program::Mesh], "MVP");
  mID   = glGetUniformLocation(ProgramIDs[Program::Mesh], "M");
    // transform ID //TODO: switch to GL_ARRAY_BUFFER, I've heard its faster/better practice
  //mvpID = glGetUniformLocation(ProgramIDs[Program::Mesh], "MVP");
  //mID   = glGetUniformLocation(ProgramIDs[Program::Mesh], "M");
// SET UP BOX LINE RENDERER
  glBindVertexArray(VAOs[BoxLine]);
//  //  glBindVertexArray(VAOs[Planes]);
//  //  glBindVertexArray(VAOs[Boxes]);
//  //  glBindVertexArray(VAOs[Spheres]);
  ProgramIDs[Program::LineMesh] = LoadShaders( "Rendering/shaders/LineMesh_VS.glsl"//Material::Phong_Monochrome.vertexshader.c_str(),
                                          ,"Rendering/shaders/LineMesh_FS.glsl"//Material::Phong_Monochrome.fragmentshader.c_str()
                                          );
  
  glUseProgram(ProgramIDs[Program::LineMesh]);
//  // Generate and bind buffer objects
    glGenBuffers(NumBuffers, Buffers[BoxLine]);
//  // now for each buffer
//  //position buffer
  glBindBuffer(GL_ARRAY_BUFFER, Buffers[BoxLine][PositionBuffer]);
  glBufferData( GL_ARRAY_BUFFER
               ,Mesh::SphereLine.vertexPositions.size() * sizeof(glm::vec3)//Mesh::BoxLine.vertexPositions.size() * sizeof(glm::vec3)     // size of the buffer data in bytes
               ,&(Mesh::SphereLine.vertexPositions[0])//&(Mesh::BoxLine.vertexPositions[0])      // pointer to the buffer data
               ,GL_STATIC_DRAW
               );
  // and binding the MVP
  line_mvpID = glGetUniformLocation(ProgramIDs[Program::LineMesh], "u_MVP");
  u_ColorID = glGetUniformLocation(ProgramIDs[Program::LineMesh], "u_Color");
  

 }

void
RenderManager::registerModel(Model* pModel)
{
  
}

void
RenderManager::addRenderable(GameObject* gameObject)
{
  m_renderableObjects.push_back(gameObject);
  
  // see if game objects model has been registered and had VAO generated for it
  bool go_ModelHasRegistered = false;
  for (int i=0; i < m_registeredModels.size(); ++i)
  {
    if (m_registeredModels[i] == gameObject->m_pModel) // if they point to the same flyweight they are same geo
    {
      go_ModelHasRegistered = true;
      continue;
    }
  }
  // if so do not register the model
  // if not, register the model
  if (!go_ModelHasRegistered)
  {
    registerModel(gameObject->m_pModel);
  }
  
}

void
RenderManager::render( const glm::mat4& view_transform
                      ,const glm::mat4& projection_transform
                      )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// draw Mesh
  if (false)
  {
    glUseProgram(ProgramIDs[Program::Mesh]);
    
    // Note since all of these models have the same position and color data we can
    //    just do this once. However, if this is done rendering will be batched
    //    according to a given model. Render all instances of a model, then the next.
    glEnableVertexAttribArray(MeshAttributeID::vPosition);
    glEnableVertexAttribArray(MeshAttributeID::vColor);
    glEnableVertexAttribArray(MeshAttributeID::vNormal);
   
    for (int i = 0; i < m_renderableObjects.size(); ++i)
    {
    // Model matrix : an identity matrix (model will be at the origin)
      glm::mat4 Model    = m_renderableObjects[i]->m_transform.getAsMat4();//glm::mat4(1.0f);
      MVP        = projection_transform * view_transform * Model; // Remember, matrix multiplication is the other way around
      glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]); // I don't even need to init MatrixID...???
      M          = Model;
      glUniformMatrix4fv(mID, 1, GL_FALSE, &M[0][0]);
    
      glBindBuffer(GL_ARRAY_BUFFER,Buffers[BoxMesh][PositionBuffer]);
      glVertexAttribPointer( MeshAttributeID::vPosition
                            ,3
                            ,GL_FLOAT
                            ,GL_FALSE
                            ,0
                            ,(void*) 0
                            );
      
      
      glBindBuffer(GL_ARRAY_BUFFER,Buffers[BoxMesh][ColorBuffer]);
      glVertexAttribPointer( MeshAttributeID::vColor
                            ,3
                            ,GL_FLOAT
                            ,GL_FALSE
                            ,0
                            ,(void*) 0
                            );
      
      glBindBuffer(GL_ARRAY_BUFFER, Buffers[BoxMesh][NormalBuffer]);
      glVertexAttribPointer( MeshAttributeID::vNormal
                            ,3
                            ,GL_FLOAT
                            ,GL_FALSE
                            ,0
                            ,(void*)0
                            );
      
      glDrawArrays(GL_TRIANGLES, 0, NumVertices);
      
     
    }
    glDisableVertexAttribArray(MeshAttributeID::vPosition);
    glDisableVertexAttribArray(MeshAttributeID::vColor);
    glDisableVertexAttribArray(MeshAttributeID::vNormal);
  }
  if (true)
  {
    glUseProgram(ProgramIDs[Program::LineMesh]);
    
    // Note since all of these models have the same position and color data we can
    //    just do this once. However, if this is done rendering will be batched
    //    according to a given model. Render all instances of a model, then the next.
    glEnableVertexAttribArray(MeshAttributeID::vPosition);
    
    for (int i = 0; i < m_renderableObjects.size(); ++i)
    {
      glm::mat4 Model = m_renderableObjects[i]->m_transform.getAsMat4();
      MVP             = projection_transform * view_transform * Model * glm::scale(glm::vec3(1.3f,1.3f,1.3f));
      glUniformMatrix4fv(line_mvpID, 1, GL_FALSE, &MVP[0][0]);
      glm::vec3 color = glm::vec3(0,1,1);
      glUniform3fv(u_ColorID, 1, &color[0]);
      
      glBindBuffer(GL_ARRAY_BUFFER,Buffers[BoxLine][PositionBuffer]);
      glVertexAttribPointer( MeshAttributeID::vPosition
                            ,3
                            ,GL_FLOAT
                            ,GL_FALSE
                            ,0
                            ,(void*) 0
                            );
      
      
//      glBindBuffer(GL_ARRAY_BUFFER,Buffers[BoxMesh][ColorBuffer]);
//      glVertexAttribPointer( MeshAttributeID::vColor
//                            ,3
//                            ,GL_FLOAT
//                            ,GL_FALSE
//                            ,0
//                            ,(void*) 0
//                            );
//      
//      glBindBuffer(GL_ARRAY_BUFFER, Buffers[BoxMesh][NormalBuffer]);
//      glVertexAttribPointer( MeshAttributeID::vNormal
//                            ,3
//                            ,GL_FLOAT
//                            ,GL_FALSE
//                            ,0
//                            ,(void*)0
//                            );
      
      glDrawArrays(GL_LINES, 0, NumVertices);
    }
    glDisableVertexAttribArray(MeshAttributeID::vPosition);
  }
  // Swap buffers

  glfwSwapBuffers(window);
  glfwPollEvents();
  //glFlush(); Is this needed? if so, where should it go?
  
}