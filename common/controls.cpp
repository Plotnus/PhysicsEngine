// Include GLFW
#include <glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.
extern int window_width; //TODO: fix the architecture
extern int window_height; //TODO: fix the architecture

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//using namespace glm;


#include "controls.hpp"

// globals
#define DVORAK 0
#define QWERTY 1
#define KEYBOARD_LAYOUT QWERTY //note keyboard doesn't adjust for layout. is how glfw is coded


glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
bool isPaused = false;

bool
gameIsPaused()
{
  return isPaused;
}

glm::mat4
getViewMatrix()
{
  return ViewMatrix;
}
glm::mat4
getProjectionMatrix()
{
  return ProjectionMatrix;
}

//Initial camera/player position and orientations
glm::vec3 position = glm::vec3( 0, 5, 10 );
float horizontalAngle = 3.14f;
float verticalAngle = -3.14/8.f;
float initialFoV = 45.0f;
float speed = 3.0f;         // 3 units / second
float cursorSpeed = 0.005f;

void
computeMatricesFromInputs()
{
  // glfwGetTime is called only once, the first time this function is called
  static double lastTime = glfwGetTime();
  
  
  
    // for any discrete simulation we need the time step
  double currentTime = glfwGetTime();
  float deltaTime = float(currentTime - lastTime);
  lastTime = currentTime; //now that we have del_t, update lastTime for next loop
  
  
  // Recomput the position, rotation, orientation and FoV based on inputs
    // Get cursor position
  double cursor_x;
  double cursor_y;
  glfwGetCursorPos(window, &cursor_x, &cursor_y);
  // Reset the cursor position for the next frame
  glfwSetCursorPos(window, window_width/2, window_height/2);
    // compute new orientation
  horizontalAngle += cursorSpeed /* deltaTime*/ * float(window_width/2 - cursor_x);
  verticalAngle   += cursorSpeed /* deltaTime*/ * float(window_height/2 - cursor_y);

    // Orientation
  glm::vec3 forward(
                    cos(verticalAngle) * sin(horizontalAngle),
                    sin(verticalAngle),
                    cos(verticalAngle) * cos(horizontalAngle)
                    );
  
  glm::vec3 right = glm::vec3(
                              sin(horizontalAngle - 3.14f/2.f),
                              0,
                              cos(horizontalAngle - 3.14f/2.f)
                              );
  // Up vector : perpendicular to both direction and right
  glm::vec3 up = glm::cross( right, forward );
  
  // Position
    // Move forward
  switch(KEYBOARD_LAYOUT)
  {
    case DVORAK: // NOTE: GLFW IS CODED TO HARDWARE INPUT CODES, DOES NOT ADJUST TO REBINDS!!
    {
      if ( glfwGetKey( window, GLFW_KEY_COMMA ) == GLFW_PRESS) // move forward
      {
        position += forward * deltaTime * speed;
      }
      if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS ) // strafe right
      {
        position += right * deltaTime * speed;
      }
      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // strafe left
      {
        position += -right * deltaTime * speed;
      }
      if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
      {
        position += -forward * deltaTime * speed;
      }
      if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
      {
        position += -forward * deltaTime * speed;
      }
      if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      {
        position += up * deltaTime * speed;
      }
      if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
      {
        position += -up * deltaTime * speed;
      }
      if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
      {
        isPaused = (isPaused ? false: true);
      }
    }
    case QWERTY:
    {
      if ( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS) // move forward
      {
        position += forward * deltaTime * speed;
      }
      if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ) // strafe right
      {
        position += right * deltaTime * speed;
      }
      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // strafe left
      {
        position += -right * deltaTime * speed;
      }
      if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      {
        position += -forward * deltaTime * speed;
      }
      if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      {
        position += up * deltaTime * speed;
      }
      if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
      {
        position += -up * deltaTime * speed;
      }
      if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
      {
        isPaused = (isPaused ? false: true);
      }
      
    }
    default:
    {
      //printf("ERROR: NO INPUT LAYOUT SET");
    }
  }
  // ZOOM: not needed but is part of the tutorial
  float FoV = initialFoV; // Not implemented //- 5 * glfwGet
  
  
  // Compute the matrices
    // Projection
  ProjectionMatrix = glm::perspective(
                                      FoV,    // field of view
                                      window_width / (float) window_width, //aspect ratio
                                      0.1f,   // near plane
                                      100.f   // far plane
                                      );
    // View
  ViewMatrix = glm::lookAt(
                           position,              // camera positon
                           position + forward,    // look at point
                           up                     // up vector
                           );
  
  
  
  
  // Then recalculate the View and Projection matrices
  
  //TODO: code...
}