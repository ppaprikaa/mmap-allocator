set(PLAYGROUND_TARGET ${LIB_TARGET}_PLAY)

add_executable(${PLAYGROUND_TARGET} main.cpp)
target_link_libraries(${PLAYGROUND_TARGET} ${LIB_TARGET})
