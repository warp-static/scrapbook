project(Disaster)

add_executable(Disaster src/main.cpp)

target_link_libraries(Disaster ${OPENGL_LIBRARIES} SDL2 ${GLEW_LIBRARIES} ${ASSIMP_LIBRARIES})