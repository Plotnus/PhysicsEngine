#ifndef CONTROLS_HPP
#define CONTROLS_HPP

/**
 * reads the keyboard and mouse and computes the Projection and View matrices
 *    one could say that this is where the "magic" happens
 */
void computeMatricesFromInputs();
/**
 * Returns the pre-computed ProjectionMatrix
 */
glm::mat4 getProjectionMatrix();
/**
 * Returns the computed View matrix
 */
glm::mat4 getViewMatrix();

bool gameIsPaused();
#endif