#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <glm/glm.hpp>

struct Mesh
{
  Mesh(){}
  
  Mesh(
    std::vector<glm::vec3> vertexPositions_in,
    std::vector<glm::vec3> vertexNormals_in,
    std::vector<glm::vec3> vertexColors
  );
  //Mesh(Mesh& meshIn);
  
  
  std::vector<glm::vec3> vertexPositions; // one per triangle face
  std::vector<glm::vec3> vertexNormals;   // one per triangle
  std::vector<glm::vec3> vertexColors;   // one per triangle //TODO: MOVE TO MATERIAL AFTER TESTING
  
  static const Mesh BoxMesh;
  static const Mesh BoxLine;
  
  static const Mesh SphereLine;
  static Mesh generateUnitSphereLineMesh();

};


//Mesh generateUnitSphereLineMesh();
#endif
