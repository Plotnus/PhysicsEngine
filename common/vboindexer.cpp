#include "vboindexer.hpp"

// header includes are
// <vector>
// <glm/glm.hpp>


#include <map>
#include <string.h> // for memcmp

// helper methods

/**
 * compares two floats returns true if their difference is below a coded, in
 * function threshhold
 */
bool
is_near(float a, float b)
{
  float threshhold = 0.01;
  return fabs(a - b) < threshhold;
}

/**
 * returns true if a similar vertex index was found that matches in_face
 * searches through the existing vertex buffers for a match
 * similar is defined as all pairwise elements are "near" one another
 */
bool
getSimilarVertexIndex(
                      const glm::vec3 & in_vertex,
                      const glm::vec2 & in_uv,
                      const glm::vec3 & in_normal,
                      
                      const std::vector <glm::vec3> & out_vertices,
                      const std::vector <glm::vec2> & out_uvs,
                      const std::vector <glm::vec3> & out_normals,
                      
                      unsigned short & matching_index
)
{
  // compare each element of each vertex property, if all are considered
  // near than we have a match, get the index and return, else return false
  for (unsigned short i = 0; i < out_vertices.size(); ++i)
  {
    if (
        // to test if faces match, check the
          //nearness of position
           is_near(in_vertex.x, out_vertices[i].x)
        && is_near(in_vertex.y, out_vertices[i].y)
        && is_near(in_vertex.z, out_vertices[i].z)
          //nearness of uv
        && is_near(in_uv.x, out_uvs[i].x)
        && is_near(in_uv.y, out_uvs[i].y)
          // and nearness of the normals
        && is_near(in_normal.x, out_normals[i].x)
        && is_near(in_normal.y, out_normals[i].y)
        && is_near(in_normal.z, out_normals[i].z)
          // note that for a face with more attributes we would have to test
          // that all of the attributes match
        )
    {
      matching_index = i;
      return true;
    }
  }
  // if we have gotten this far we have gone through all of the currently indexed
  // output faces and have not found a match.
  return false;
}

// NOW FOR THE MAIN COURSE: NON-HELPERS
void
indexVBO_slow1(
              std::vector <glm::vec3> & in_vertices,
              std::vector <glm::vec2> & in_uvs,
              std::vector <glm::vec3> & in_normals,
              
              std::vector <glm::vec3> & out_vertices,
              std::vector <glm::vec2> & out_uvs,
              std::vector <glm::vec3> & out_normals,
              
              std::vector <unsigned short> & out_indices
              
              

)
{
  // for each input vertex, see if there is a match
  for (unsigned int i = 0; i < in_vertices.size(); i++)
  {
    //if there is a match simply add the index to out_indices
    unsigned short vertIndex;
    bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i],
                                       out_vertices, out_uvs, out_normals,
                                       vertIndex);
    // if there is a match just add the vert data index to out_indices
    if (found)
    {
      out_indices.push_back(vertIndex);
    }
    // if there is no match add the values to out_vertices, out_uvs, and out_norm
    //    then add the cooresponding index to out_indices
    else
    {
      // add the position, uv, and normal data to out vert, out uv, & out_norm
      // push the new index which is the size of vert -1
      out_vertices.push_back(in_vertices[i]);
      out_uvs.push_back(in_uvs[i]);
      out_normals.push_back(in_normals[i]);
      out_indices.push_back((unsigned short)out_vertices.size() - 1);
    }
  }
}


void indexVBO_slow(
                   std::vector<glm::vec3> & in_vertices,
                   std::vector<glm::vec2> & in_uvs,
                   std::vector<glm::vec3> & in_normals,
                   
                   
                   std::vector<glm::vec3> & out_vertices,
                   std::vector<glm::vec2> & out_uvs,
                   std::vector<glm::vec3> & out_normals,
                   std::vector<unsigned short> & out_indices
                   ){
  // For each input vertex
  for ( unsigned int i=0; i<in_vertices.size(); i++ ){
    
    // Try to find a similar vertex in out_XXXX
    unsigned short index;
    bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i],     out_vertices, out_uvs, out_normals, index);
    
    if ( found ){ // A similar vertex is already in the VBO, use it instead !
      out_indices.push_back( index );
    }else{ // If not, it needs to be added in the output data.
      out_vertices.push_back( in_vertices[i]);
      out_uvs     .push_back( in_uvs[i]);
      out_normals .push_back( in_normals[i]);
      out_indices .push_back( (unsigned short)out_vertices.size() - 1 );
    }
  }
}
// TODO: if you want you can speed up this function and provide the other
// implementation. For directien look at vboindexer.cpp in the turorial 9 folder