//===============================================
#include "objloader.hpp"
#include <glm/glm.hpp>

#include <vector>
#include <stdio.h>
#include <string>
//#include <cstring>

bool
loadOBJ1(const char * path,
        std::vector <glm::vec3> & out_vertices,
        std::vector <glm::vec2> & out_uvs,
        std::vector <glm::vec3> & out_normals
        )
{
    //temp vertices, note that these do not represent the faces
  std::vector <glm::vec3> temp_vertices;
  std::vector <glm::vec2> temp_uvs;
  std::vector <glm::vec3> temp_normals;
    // we need tempory variables in which we will store the contents of the .obj
  std::vector <unsigned int> vertex_indices;
  std::vector <unsigned int> uv_indices;
  std::vector <unsigned int> normal_indices;

  
  // open the file
  FILE * file = fopen(path, "r");
  if ( file == NULL )
  {
    printf("Can not open the file at the given path. Check spelling &permissions\n");
    return false;
  }
  // Read the file until we get an EOF
  while (true)
  {
    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF) // if end of file exit loop
    {
      break;
    }
    // else: continue parsing the line header
    // reading: vertices
    if (strcmp(lineHeader, "v") == 0)
    {
      glm::vec3 vertex;
      fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
      temp_vertices.push_back(vertex);
    }
    // reading: texture coords
    if (strcmp(lineHeader, "vt") == 0)
    {
      glm::vec2 uv;
      fscanf(file, "%f %f\n", &uv.x, &uv.y);
      temp_uvs.push_back(uv);
    }
    // reading: normals
    if (strcmp(lineHeader, "vn") == 0)
    {
      glm::vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
      temp_normals.push_back(normal);
    }
    // now for the face ordering
    if (strcmp(lineHeader, "f")==0)
    {
      // indices for vertex, uv, and normal ordering
      unsigned int vertexIndex[3];
      unsigned int uvIndex[3];
      unsigned int normalIndex[3];
      //
      int matches = fscanf(file,
                           "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                           &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                           &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                           &vertexIndex[2], &uvIndex[2], &normalIndex[2]
                           );
      if (matches != 9)
      {
        printf("File can't be read by our \"toy\" parser: Try exporting with other options\n");
        return false;
      }
        //push back the indices.
      vertex_indices.push_back(vertexIndex[0]);
      vertex_indices.push_back(vertexIndex[1]);
      vertex_indices.push_back(vertexIndex[2]);
        // push back the uv coords
      uv_indices.push_back(uvIndex[0]);
      uv_indices.push_back(uvIndex[1]);
      uv_indices.push_back(uvIndex[2]);
        // push back the normals
      normal_indices.push_back(normalIndex[0]);
      normal_indices.push_back(normalIndex[1]);
      normal_indices.push_back(normalIndex[2]);
      
    }
  }
  // now to create & add the buffer friendly output based on triplets
  //each loop adds a face
  for (int i = 0; i < vertex_indices.size(); ++i)
  {
    // get vert
    glm::vec3 vert;
    int index_vert = vertex_indices[i] - 1; // -1 for 0 indexing
    vert = temp_vertices[index_vert];
    // push vert onto output vector
    out_vertices.push_back(vert);
  }
  // now for uv
  for (int i = 0; i < uv_indices.size(); ++i)
  {
    // get uv value
    glm::vec2 uv;
    int index_uv = uv_indices[i] - 1; // -1 for 0 indexing
    uv = temp_uvs[index_uv];
    // push onto vector
    out_uvs.push_back(uv);

  }
  //again for normals
  for (int i = 0; i < normal_indices.size(); ++i)
  {
    // get the normal
    glm::vec3 normal;
    int index_normal = normal_indices[i] - 1; // -1 for 0 indexing
    normal = temp_normals[index_normal];
    // push onto vector
    out_normals.push_back(normal);
  }
  
  
  return true;
}

bool loadOBJ(
             const char * path,
             std::vector<glm::vec3> & out_vertices,
             std::vector<glm::vec2> & out_uvs,
             std::vector<glm::vec3> & out_normals
             ){
  printf("Loading OBJ file %s...\n", path);
  
  std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
  std::vector<glm::vec3> temp_vertices;
  std::vector<glm::vec2> temp_uvs;
  std::vector<glm::vec3> temp_normals;
  
  
  FILE * file = fopen(path, "r");
  if( file == NULL ){
    printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
    getchar();
    return false;
  }
  
  while( 1 ){
    
    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
      break; // EOF = End Of File. Quit the loop.
    
    // else : parse lineHeader
    
    if ( strcmp( lineHeader, "v" ) == 0 ){
      glm::vec3 vertex;
      fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
      temp_vertices.push_back(vertex);
    }else if ( strcmp( lineHeader, "vt" ) == 0 ){
      glm::vec2 uv;
      fscanf(file, "%f %f\n", &uv.x, &uv.y );
      uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
      temp_uvs.push_back(uv);
    }else if ( strcmp( lineHeader, "vn" ) == 0 ){
      glm::vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
      temp_normals.push_back(normal);
    }else if ( strcmp( lineHeader, "f" ) == 0 ){
      std::string vertex1, vertex2, vertex3;
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
      if (matches != 9){
        printf("File can't be read by our simple parser :-( Try exporting with other options\n");
        return false;
      }
      vertexIndices.push_back(vertexIndex[0]);
      vertexIndices.push_back(vertexIndex[1]);
      vertexIndices.push_back(vertexIndex[2]);
      uvIndices    .push_back(uvIndex[0]);
      uvIndices    .push_back(uvIndex[1]);
      uvIndices    .push_back(uvIndex[2]);
      normalIndices.push_back(normalIndex[0]);
      normalIndices.push_back(normalIndex[1]);
      normalIndices.push_back(normalIndex[2]);
    }else{
      // Probably a comment, eat up the rest of the line
      char stupidBuffer[1000];
      fgets(stupidBuffer, 1000, file);
    }
    
  }
  
  // For each vertex of each triangle
  for( unsigned int i=0; i<vertexIndices.size(); i++ ){
    
    // Get the indices of its attributes
    unsigned int vertexIndex = vertexIndices[i];
    unsigned int uvIndex = uvIndices[i];
    unsigned int normalIndex = normalIndices[i];
    
    // Get the attributes thanks to the index
    glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
    glm::vec2 uv = temp_uvs[ uvIndex-1 ];
    glm::vec3 normal = temp_normals[ normalIndex-1 ];
    
    // Put the attributes in buffers
    out_vertices.push_back(vertex);
    out_uvs     .push_back(uv);
    out_normals .push_back(normal);
    
  }
  
  return true;
}