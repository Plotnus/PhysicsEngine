#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window; //TODO: make this and the below part of a window struct
int window_width = 1024;
int window_height = 768;

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

// inter-engine includes
#include "../Rendering/text2D.hpp"
#include "../common/shader.hpp"
#include "../common/controls.hpp"
//#include "../Mesh/Mesh_Box.hpp"

#include "../Core/Mesh.hpp"
#include "../Core/Material.hpp"
#include "../Core/Model.hpp"

#include "../Rendering/RenderManager.hpp"
#include "../Core/PhysicsManager.hpp"

int initglfw();
int initglew();
void renderAndCalcPerformanceStats();//double&);

int
main()
{
  initglfw(); // inits glfw: window and input
  initglew(); // initializes glew
  
  

  //init our text renderer
  //initText2D("Assets/Holstein.DDS");
  
  // setup scene, create and place objects
  // create a model which is a mesh, and material
  //CREATE A MODEL
  Mesh unitPlaneMesh;
  glm::vec3 p1 = glm::vec3( 1.f, 0.f,  1.f);
  glm::vec3 p2 = glm::vec3( 1.f, 0.f, -1.f);
  glm::vec3 p3 = glm::vec3(-1.f, 0.f, -1.f);
  glm::vec3 p4 = glm::vec3(-1.f, 0.f,  1.f);
  unitPlaneMesh.vertexPositions.push_back(p1); // face 1 positions
  unitPlaneMesh.vertexPositions.push_back(p2);
  unitPlaneMesh.vertexPositions.push_back(p3);
  unitPlaneMesh.vertexPositions.push_back(p3); // face 2 positions
  unitPlaneMesh.vertexPositions.push_back(p4);
  unitPlaneMesh.vertexPositions.push_back(p1);
  glm::vec3 n1 = glm::vec3(0.f, 1.f, 0.f);
  unitPlaneMesh.vertexPositions.push_back(n1); // face 1 normals
  unitPlaneMesh.vertexPositions.push_back(n1);
  unitPlaneMesh.vertexPositions.push_back(n1);
  unitPlaneMesh.vertexPositions.push_back(n1); // face 2 normals
  unitPlaneMesh.vertexPositions.push_back(n1);
  unitPlaneMesh.vertexPositions.push_back(n1);
  


  Model unitPlaneModel;
  unitPlaneModel.mesh     = unitPlaneMesh;
  unitPlaneModel.material = Material::Phong_Monochrome;
  
  std::cout << unitPlaneModel.material.vertexshader << std::endl;
  // CREATE A TRANSFORM
  Transform modelTransform;
  modelTransform.m_position     = glm::vec3(5.f, 0.f, 2.f);
  modelTransform.m_scale        = glm::vec3(2.f, 1.f, 1.5f);
  modelTransform.m_orientation  = glm::vec4(0.f, 1.f, 1.f, 1.f);
  
  // CREATE A GAME OBJECT
  GameObject planeInstance;
  planeInstance.m_pModel     = &unitPlaneModel;
  planeInstance.m_transform = modelTransform;
  // CREATE A RENDERING MANAGER
  RenderManager renderingManager;
  renderingManager.init();
  renderingManager.addRenderable(&planeInstance);
  
  // now testing for another box on the opposite area
  modelTransform.m_position     = glm::vec3(-5.f, 0.f,-2.f);
  modelTransform.m_orientation  = glm::vec4( 0.f, 0.f, 1.f, 0.f);
  //
  Transform transform1;
  transform1.m_position     = glm::vec3(0.f, 4.f, 2.f);
  transform1.m_scale        = glm::vec3(1.f, 1.f, 1.f);
  transform1.m_orientation  = glm::vec4(0.f, 0.f, 1.f, 0.f);

  Transform transform2;
  transform2.m_position     = glm::vec3(-5.f, 0.f, 2.f);
  transform2.m_scale        = glm::vec3(2.f, 1.f, 1.f);
  transform2.m_orientation  = glm::vec4(0.f, 0.f, 1.f, 0.f);

  Transform transform3;
  transform3.m_position     = glm::vec3(-5.f, 0.f, -2.f);
  transform3.m_scale        = glm::vec3(1.f, 2.f, 1.f);
  transform3.m_orientation  = glm::vec4(0.f, 0.f, 1.f, 0.f);
  
  
  Transform transform4;
  transform4.m_position     = glm::vec3(5.f, 0.f, -2.f);
  transform4.m_scale        = glm::vec3(1.f, 1.f, 2.f);
  transform4.m_orientation  = glm::vec4(0.f, 0.f, 1.f, 0.f);
  
  renderingManager.boxTransforms.push_back(&transform1);
  renderingManager.boxTransforms.push_back(&transform2);
  renderingManager.boxTransforms.push_back(&transform3);
  renderingManager.boxTransforms.push_back(&transform4);
  
  GameObject gameObject1;
  gameObject1.m_pModel = &unitPlaneModel;
  gameObject1.m_transform = transform1;
  
  GameObject gameObject2;
  gameObject2.m_pModel = &unitPlaneModel;
  gameObject2.m_transform = transform2;
  
  GameObject gameObject3;
  gameObject3.m_pModel = &unitPlaneModel;
  gameObject3.m_transform = transform3;
  
  GameObject gameObject4;
  gameObject4.m_pModel = &unitPlaneModel;
  gameObject4.m_transform = transform4;
  
  renderingManager.addRenderable(&gameObject1);
  renderingManager.addRenderable(&gameObject2);
  renderingManager.addRenderable(&gameObject3);
  renderingManager.addRenderable(&gameObject4);
  
  // TEST IF WE CAN RENDER THROUGH THE RENDERING MANAGER
  Mesh boxMesh = Mesh::BoxMesh;
  
  
  //PHYSICS MANAGER
  PhysicsManager physicsManager;
  
  do{
    //update input
    computeMatricesFromInputs();
    
    if (!gameIsPaused())
    {
      // updating mvp for some animation
      gameObject1.m_transform.m_position += glm::vec3(0.f,     0.002f, 0.f);
      gameObject2.m_transform.m_position += glm::vec3( 0.f,   -0.002f, 0.f);
      gameObject3.m_transform.m_position += glm::vec3(-0.002f, 0.0f  , 0.f);
      gameObject4.m_transform.m_position += glm::vec3( 0.002f, 0.0f  , 0.f);
      planeInstance.m_transform.m_orientation += glm::vec4(0.1f, 0.f, 0.f, 0.f);
      
      //update physics
      physicsManager.update();
    }
    // update renderer
    renderingManager.render(getViewMatrix(), getProjectionMatrix());
    
  // text fps output
   // renderAndCalcPerformanceStats();//currentTime);
    
  } // Check if the ESC key was pressed or the window was closed
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0 );
  
  // Close OpenGL window and terminate GLFW
  glfwTerminate();
  
  return 0;
}

int initglfw()
{
  // this code typed out from tutorial
  // Initialize GLFW
  if( !glfwInit() )
  {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    getchar();
    return -1;
  }
  
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  // Open a window and create its OpenGL context
  window = glfwCreateWindow( window_width, window_height, "PLOT-PHYSICS", NULL, NULL);
  if( window == NULL ){
    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
    getchar();
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  // initialize input
  // Ensure we can capture the escape keybeing pressed
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // keyboard input
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  // Set the cursor at the center of the screen
  glfwPollEvents(); // I'm not sure why this is here
  glfwSetCursorPos(window, window_width/2, window_height/2);   return 0;
}
int
initglew()
{
  // this code typed out from tutorial
  // Initialize GLEW
  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return -1;
  }
  else{
    printf("Glew Initializing ... success\n");
    return 0;
  }
}

void
renderAndCalcPerformanceStats()//double& currentTime)
{
  static double  currentTime = glfwGetTime();// runs first time function is called
  // Performance calculations
  char fps[256];
  char timePerFrame[256];
  
  double lastTime = currentTime;
  currentTime = glfwGetTime();
  double timeElapsed = currentTime - lastTime;
  
  // printf and reset timer
  sprintf(fps, "FPS = %.2f", 1/double(timeElapsed));
  sprintf(timePerFrame, "TPF = %.2f ms/frame", (timeElapsed));
  
  // rendering performance output
  // draw the text stuff
  unsigned int x_start = 10;
  unsigned int y_start = 25;
  unsigned int size = 20;
  printText2D(fps, x_start, y_start, size);
  printText2D(timePerFrame, x_start, y_start - 1.1*size, size);
}