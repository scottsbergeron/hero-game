cmake_minimum_required(VERSION 3.10)
project(GameProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set MinGW compiler
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_SYSTEM_NAME Windows)

# Set paths
set(SDL2_PATH /usr/x86_64-w64-mingw32)
set(SDL2_TTF_PATH /usr/x86_64-w64-mingw32)
set(GLEW_PATH /usr/x86_64-w64-mingw32)
set(GLM_PATH /usr/x86_64-w64-mingw32)

# Find all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable
add_executable(game WIN32 ${SOURCES})

# Include directories
target_include_directories(game PRIVATE 
    ${SDL2_PATH}/include/SDL2
    ${SDL2_TTF_PATH}/include/SDL2
    ${GLEW_PATH}/include
    ${GLM_PATH}/include
)

# Link libraries in correct order
target_link_libraries(game PRIVATE 
    mingw32
    ${SDL2_PATH}/lib/libSDL2main.a
    ${SDL2_PATH}/lib/libSDL2.dll.a
    ${SDL2_TTF_PATH}/lib/libSDL2_ttf.dll.a
    ${GLEW_PATH}/lib/libglew32.dll.a
    opengl32
)

# Copy all required DLLs to build directory
file(COPY 
    ${SDL2_PATH}/bin/SDL2.dll
    ${SDL2_TTF_PATH}/bin/SDL2_ttf.dll
    ${GLEW_PATH}/bin/glew32.dll
    /usr/lib/gcc/x86_64-w64-mingw32/10-win32/libstdc++-6.dll
    /usr/lib/gcc/x86_64-w64-mingw32/10-win32/libgcc_s_seh-1.dll
    /usr/x86_64-w64-mingw32/lib/libwinpthread-1.dll
    DESTINATION ${CMAKE_BINARY_DIR}
)

# Copy shader files to build directory
file(COPY 
    ${CMAKE_SOURCE_DIR}/assets/shaders
    DESTINATION ${CMAKE_BINARY_DIR}/assets
)
