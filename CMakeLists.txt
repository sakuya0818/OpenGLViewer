cmake_minimum_required(VERSION 3.5)
project(OpenGLViewer VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(deps/glfw)
add_subdirectory(deps/glm)

set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_COLLADA_IMPORTER TRUE)
set(ASSIMP_BUILD_OBJ_IMPORTER TRUE)
set(ASSIMP_BUILD_FBX_IMPORTER TRUE)
add_subdirectory(deps/assimp)

file(GLOB ASSETS "./assets")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

set(GLAD_SOURCES
    deps/glad/src/glad.c
)
set(IMGUI_SOURCES
    deps/imgui/imgui.cpp
    deps/imgui/imgui_demo.cpp
    deps/imgui/imgui_draw.cpp
    deps/imgui/imgui_tables.cpp
    deps/imgui/imgui_widgets.cpp
    deps/imgui/imgui_impl_glfw.cpp
    deps/imgui/imgui_impl_opengl3.cpp
)

set(APPLICATION_SOURCES
    src/application/Application.cpp
    src/application/camera/Camera.cpp
    src/application/camera/OrthographicCamera.cpp
    src/application/camera/PerspectiveCamera.cpp
    src/application/camera/CameraControl.cpp
    src/application/camera/TrackBallController.cpp
    src/application/camera/GameCameraControl.cpp
)

set(GLFRAMEWORK_SOURCES
    src/glframework/shader.cpp
    src/glframework/texture.cpp
    src/glframework/Geometry.cpp
    src/glframework/Object.cpp
    src/glframework/Scene.cpp
    src/glframework/Mesh.cpp
    src/glframework/material/material.cpp
    src/glframework/material/phongMaterial.cpp
    src/glframework/light/light.cpp
    src/glframework/light/directionLight.cpp
    src/glframework/light/ambientLight.cpp
    src/glframework/light/pointLight.cpp
    src/glframework/light/spotLight.cpp
    src/glframework/renderer/renderer.cpp
    src/glframework/tools/tools.cpp
)

set(SOURCES
    src/main.cpp
    ${GLAD_SOURCES}
    ${IMGUI_SOURCES}
    ${APPLICATION_SOURCES}
    ${GLFRAMEWORK_SOURCES}
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME}
    PRIVATE deps
    PRIVATE deps/glad/include
    PRIVATE deps/glfw/include
    PRIVATE deps/glm
    PRIVATE deps/stb
)
target_link_directories(${PROJECT_NAME} PRIVATE deps)
target_link_libraries(${PROJECT_NAME}
    glfw
    assimp
)