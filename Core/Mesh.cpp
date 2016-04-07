#include "Mesh.hpp"

#include <glm/gtc/constants.hpp>

////////////////////////////////////////////////
// Static Const Definitions: for Mesh.hpp     //
////////////////////////////////////////////////
const Mesh Mesh::BoxMesh = Mesh(
// first set of data is for the vertex Positions
                                {
                                  {-1.0f,-1.0f,-1.0f},  // normal = (-1,+0,+0)
                                  {-1.0f,-1.0f, 1.0f},
                                  {-1.0f, 1.0f, 1.0f},
                                  { 1.0f, 1.0f,-1.0f},   // normal = (+0,+0,-1)
                                  {-1.0f,-1.0f,-1.0f},
                                  {-1.0f, 1.0f,-1.0f},
                                  { 1.0f,-1.0f, 1.0f},   // normal = (+0,-1,+0)
                                  {-1.0f,-1.0f,-1.0f},
                                  { 1.0f,-1.0f,-1.0f},
                                  { 1.0f, 1.0f,-1.0f},   // normal = (+0,+0,-1)
                                  { 1.0f,-1.0f,-1.0f},
                                  {-1.0f,-1.0f,-1.0f},
                                  {-1.0f,-1.0f,-1.0f},  // normal = (-1,+0,+0)
                                  {-1.0f, 1.0f, 1.0f},
                                  {-1.0f, 1.0f,-1.0f},
                                  { 1.0f,-1.0f, 1.0f},   // normal = (+0,-1,+0)
                                  {-1.0f,-1.0f, 1.0f},
                                  {-1.0f,-1.0f,-1.0f},
                                  {-1.0f, 1.0f, 1.0f},  // normal = (+0,+0,+1)
                                  {-1.0f,-1.0f, 1.0f},
                                  { 1.0f,-1.0f, 1.0f},
                                  { 1.0f, 1.0f, 1.0f},   // normal = (+1,+0,+0)
                                  { 1.0f,-1.0f,-1.0f},
                                  { 1.0f, 1.0f,-1.0f},
                                  { 1.0f,-1.0f,-1.0f},   // normal = (+1,+0,+0)
                                  { 1.0f, 1.0f, 1.0f},
                                  { 1.0f,-1.0f, 1.0f},
                                  { 1.0f, 1.0f, 1.0f},   // normal = (+0,+1,+0)
                                  { 1.0f, 1.0f,-1.0f},
                                  {-1.0f, 1.0f,-1.0f},
                                  { 1.0f, 1.0f, 1.0f},   // normal = (+0,+1,+0)
                                  {-1.0f, 1.0f,-1.0f},
                                  {-1.0f, 1.0f, 1.0f},
                                  { 1.0f, 1.0f, 1.0f},   // normal = (+0,+0,+1)
                                  {-1.0f, 1.0f, 1.0f},
                                  { 1.0f,-1.0f, 1.0f}
                                }
// this next set is for the normals
                                ,{
                                  {-1,+0,+0},   // normal = (-1,+0,+0)
                                  {-1,+0,+0},
                                  {-1,+0,+0},
                                  {+0,+0,-1},   // normal = (+0,+0,-1)
                                  {+0,+0,-1},
                                  {+0,+0,-1},
                                  {+0,-1,+0},   // normal = (+0,-1,+0)
                                  {+0,-1,+0},
                                  {+0,-1,+0},
                                  {+0,-1,+0},   // normal = (+0,+0,-1)
                                  {+0,-1,+0},
                                  {+0,-1,+0},
                                  {-1,+0,+0},  // normal = (-1,+0,+0)
                                  {-1,+0,+0},
                                  {-1,+0,+0},
                                  {+0,-1,+0},   // normal = (+0,-1,+0)
                                  {+0,-1,+0},
                                  {+0,-1,+0},
                                  {+0,+0,+1},  // normal = (+0,+0,+1)
                                  {+0,+0,+1},
                                  {+0,+0,+1},
                                  {+1,+0,+0},   // normal = (+1,+0,+0)
                                  {+1,+0,+0},
                                  {+1,+0,+0},
                                  {+1,+0,+0},   // normal = (+1,+0,+0)
                                  {+1,+0,+0},
                                  {+1,+0,+0},
                                  {+0,+1,+0},   // normal = (+0,+1,+0)
                                  {+0,+1,+0},
                                  {+0,+1,+0},
                                  {+0,+1,+0},   // normal = (+0,+1,+0)
                                  {+0,+1,+0},
                                  {+0,+1,+0},
                                  {+0,+0,+1},   // normal = (+0,+0,+1)
                                  {+0,+0,+1},
                                  {+0,+0,+1}
                                }
// this one is for the colors
                                ,{
                                  {0.583f,  0.771f,  0.014f},
                                  {0.609f,  0.115f,  0.436f},
                                  {0.327f,  0.483f,  0.844f},
                                  {0.822f,  0.569f,  0.201f},
                                  {0.435f,  0.602f,  0.223f},
                                  {0.310f,  0.747f,  0.185f},
                                  {0.597f,  0.770f,  0.761f},
                                  {0.559f,  0.436f,  0.730f},
                                  {0.359f,  0.583f,  0.152f},
                                  {0.483f,  0.596f,  0.789f},
                                  {0.559f,  0.861f,  0.639f},
                                  {0.195f,  0.548f,  0.859f},
                                  {0.014f,  0.184f,  0.576f},
                                  {0.771f,  0.328f,  0.970f},
                                  {0.406f,  0.615f,  0.116f},
                                  {0.676f,  0.977f,  0.133f},
                                  {0.971f,  0.572f,  0.833f},
                                  {0.140f,  0.616f,  0.489f},
                                  {0.997f,  0.513f,  0.064f},
                                  {0.945f,  0.719f,  0.592f},
                                  {0.543f,  0.021f,  0.978f},
                                  {0.279f,  0.317f,  0.505f},
                                  {0.167f,  0.620f,  0.077f},
                                  {0.347f,  0.857f,  0.137f},
                                  {0.055f,  0.953f,  0.042f},
                                  {0.714f,  0.505f,  0.345f},
                                  {0.783f,  0.290f,  0.734f},
                                  {0.722f,  0.645f,  0.174f},
                                  {0.302f,  0.455f,  0.848f},
                                  {0.225f,  0.587f,  0.040f},
                                  {0.517f,  0.713f,  0.338f},
                                  {0.053f,  0.959f,  0.120f},
                                  {0.393f,  0.621f,  0.362f},
                                  {0.673f,  0.211f,  0.457f},
                                  {0.820f,  0.883f,  0.371f},
                                  {0.982f,  0.099f,  0.879f}
                                }

);


const Mesh Mesh::BoxLine = Mesh(
                                {
                                  {-1.0f,-1.0f,-1.0f}, // line 01
                                  {+1.0f,-1.0f,-1.0f},
                                  {-1.0f,-1.0f,-1.0f}, // line 02
                                  {-1.0f,+1.0f,-1.0f},
                                  {-1.0f,-1.0f,-1.0f}, // line 03
                                  {-1.0f,-1.0f,+1.0f},
                                
                                  {-1.0f,+1.0f,+1.0f}, // line 04
                                  {+1.0f,+1.0f,+1.0f},
                                  {-1.0f,+1.0f,+1.0f}, // line 05
                                  {-1.0f,-1.0f,+1.0f},
                                  {-1.0f,+1.0f,+1.0f}, // line 06
                                  {-1.0f,+1.0f,-1.0f},
                                
                                  {+1.0f,-1.0f,+1.0f}, // line 07
                                  {-1.0f,-1.0f,+1.0f},
                                  {+1.0f,-1.0f,+1.0f}, // line 08
                                  {+1.0f,+1.0f,+1.0f},
                                  {+1.0f,-1.0f,+1.0f}, // line 09
                                  {+1.0f,-1.0f,-1.0f},
                                
                                  {+1.0f,+1.0f,-1.0f}, // line 10
                                  {-1.0f,+1.0f,-1.0f},
                                  {+1.0f,+1.0f,-1.0f}, // line 11
                                  {+1.0f,-1.0f,-1.0f},
                                  {+1.0f,+1.0f,-1.0f}, // line 12
                                  {+1.0f,+1.0f,+1.0f},
                                }
                                ,
                                {
                                  {0,0,0}
                                }
                                ,
                                {
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0},
                                  {1,1,0}

                                }
                                
);
const Mesh Mesh::SphereLine = Mesh(Mesh::generateUnitSphereLineMesh());






////////////////////////////////////////////////
// Constructor Definitions: for Mesh.hpp     //
///////////////////////////////////////////////
Mesh::Mesh(
     std::vector<glm::vec3> vertexPositions_in,
     std::vector<glm::vec3> vertexNormals_in,
     std::vector<glm::vec3> vertexColors_in
           )
:vertexPositions(vertexPositions_in)
,vertexNormals(vertexNormals_in)
,vertexColors(vertexColors_in)
{
  
}

///////////////////////////////////////////////
// Static Functions: for Mesh.hpp            //
///////////////////////////////////////////////
Mesh Mesh::generateUnitSphereLineMesh()
{
  const int numVerts = 10; // seems that 18 is the max before gaps are introduced
  const double dTheta = glm::two_pi<float>() / double(numVerts);
  double theta = 0;
  Mesh sphereLineMesh;
  // set the color
  sphereLineMesh.vertexColors.push_back(glm::vec3(0.f,1.f,1.f));
  // we don't need to worry about the normals, just adding a color
  sphereLineMesh.vertexNormals.push_back(glm::vec3(0.f,0.f,0.f));
  // now generate the values for each plane, x, y, and z
  for (int i = 0; i < numVerts; ++i)
  {
    float x_1 = cos(theta);  // variable read as x naut
    float x_2 = cos(theta + dTheta); // variable read as x final
    float y_1 = sin(theta);
    float y_2 = sin(theta + dTheta);
    
    theta += dTheta;//glm::two_pi<float>()* (float(i+1) / numVerts);//dTheta;
    
    // now add the line
    sphereLineMesh.vertexPositions.push_back(glm::vec3(0.f, x_1, y_1));
    sphereLineMesh.vertexPositions.push_back(glm::vec3(0.f, x_2, y_2));
    
    sphereLineMesh.vertexPositions.push_back(glm::vec3(x_1, 0.f, y_1));
    sphereLineMesh.vertexPositions.push_back(glm::vec3(x_2, 0.f, y_2));
//
    sphereLineMesh.vertexPositions.push_back(glm::vec3(x_1, y_1, 0.f));
    sphereLineMesh.vertexPositions.push_back(glm::vec3(x_2, y_2, 0.f));
  }
  return sphereLineMesh;
}