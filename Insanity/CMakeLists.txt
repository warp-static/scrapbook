project(Insanity)

add_executable(Insanity src/main.cpp)

target_link_libraries(Insanity ${OPENGL_LIBRARIES} SDL2 ${GLEW_LIBRARIES} ${ASSIMP_LIBRARIES})