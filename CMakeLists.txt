cmake_minimum_required(VERSION 3.3)
project(PlotPhysics)
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)
######################################################
# find packages for the libraries we are using
######################################################
# OpenGL
#####
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if (NOT OPENGL_FOUND)
  message(ERROR "OpenGL not found!")
endif (NOT OPENGL_FOUND)

###################################
# Include Directories
###################################
#set(PE_INCLUDE_DIRS
#    /usr/local/include
#)
#include_directories(${PE_INCLUDE_DIRS})

#find and link glew lib
#find_package(GLEW REQUIRED)
#if(NOT GLEW_FOUND)
#  message(ERROR "GLEW not found!")
#endif(NOT GLEW_FOUND)
#if(GLEW_FOUND)
#  include_directories(${GLEW_INCLUDE_DIRS})
#  link_libraries(${GLEW_LIBRARIES})
#endif(GLEW_FOUND)

#find and ling glfw lib
#find_package(PkgConfig REQUIRED)
#pkg_search_module(GLFW REQUIRED glfw)
#include_directories(${GLFW_INCLUDE_DIRS})


#####################################
# project organization: file groups
#####################################
#GameLoop Group
set(GAMELOOP_GRP
  GameLoop/main.cpp
)
#Mesh Group
set(MESH_GRP
    Mesh/Mesh_Box_Line.cpp
    Mesh/Mesh_Box_Line.hpp
    Mesh/Mesh_Box.cpp
    Mesh/Mesh_Box.hpp
    Mesh/Mesh_Plane_Line.hpp
    Mesh/Mesh_Plane.hpp
    Mesh/Mesh_Sphere_Line.hpp
    Mesh/Mesh_Sphere.hpp
    Mesh/Mesh.hpp
)

# Rendering Group
set(RENDERING_GRP
    Rendering/text2D.cpp
    Rendering/text2D.hpp
    Rendering/RenderManager.cpp
    Rendering/RenderManager.hpp
)
#Shaders Group
set(SHADERS_GRP
    Rendering/shaders/Simple_FS.glsl
    Rendering/shaders/Simple_VS.glsl
    Rendering/shaders/Text2D_FS.glsl
    Rendering/shaders/Text2D_VS.glsl
    Rendering/shaders/Phong_FS.glsl
    Rendering/shaders/Phong_VS.glsl
    Rendering/shaders/LineMesh_FS.glsl
    Rendering/shaders/LineMesh_VS.glsl
)

#Common Group
set(COMMON_GRP
    common/controls.cpp
    common/controls.hpp
    common/objloader.cpp
    common/objloader.hpp
    common/quaternion_utils.cpp
    common/quaternion_utils.hpp
    common/shader.cpp
    common/shader.hpp
    common/tangentspace.cpp
    common/tangentspace.hpp
    common/texture.cpp
    common/texture.hpp
    common/vboindexer.cpp
    common/vboindexer.hpp
)

#core group
set(CORE_GRP
    Core/BaseComponent.hpp
    Core/Component.hpp
    Core/GameObject.cpp
    Core/GameObject.hpp
    Core/Light.hpp
    Core/Material.cpp
    Core/Material.hpp
    Core/Mesh.cpp
    Core/Mesh.hpp
    Core/Model.hpp
    Core/PhysicsManager.cpp
    Core/PhysicsManager.hpp
    Core/RenderComponent.hpp
    Core/Scene.hpp
    Core/System.hpp
    Core/Transform.cpp
    Core/Transform.hpp
)
########################################
# Create executable
########################################
add_executable (PhysicsEngine
                ${GLM_SRC}
                ${GLEW_SRC}
                ${COMMON_GRP}
                ${GAMELOOP_GRP}
                ${MESH_GRP}
                ${RENDERING_GRP}
                ${SHADERS_GRP}
                ${CORE_GRP}
)
########################################
# Xcode and Visual working directories
########################################
set_target_properties(PhysicsEngine
                      PROPERTIES
                      XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR
                      "${CMAKE_CURRENT_SOURCE_DIR}"
)
#create_target_launcher(PhysicsEngine
#                       WORKING_DIRECTORY
#                      "${CMAKE_CURRENT_SOURCE_DIR}"
#)


########################################
# organize code into project folders
########################################
source_group("glm"        FILES ${GLM_SRC})
source_group("glew"       FILES ${GLEW_SRC})
source_group("common"     FILES ${COMMON_GRP})
source_group("GameLoop"   FILES ${GAMELOOP_GRP})
source_group("Mesh"       FILES ${MESH_GRP})
source_group("Shaders"    FILES ${SHADERS_GRP})
source_group("Rendering"  FILES ${RENDERING_GRP})
source_group("Core"       FILES ${CORE_GRP})


#########################################
# For adding and compiling dependencies
#########################################
add_subdirectory(external)

include_directories(
external/glfw-3.1.2/include/GLFW/
external/glm-0.9.7.4/
external/glew-1.13.0/include/
)

set(ALL_LIBS
${OPENGL_LIBRARY}
glfw
GLEW_1130
)

add_definitions(
-DTW_STATIC
-DTW_NO_LIB_PRAGMA
-DTW_NO_DIRECT3D
-DGLEW_STATIC
-D_CRT_SECURE_NO_WARNINGS
)


#########################################
target_link_libraries(PhysicsEngine
                      ${ALL_LIBS}
)

