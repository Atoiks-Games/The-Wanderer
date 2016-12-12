add_subdirectory(players)

file(GLOB SOURCES "*.cxx")
add_library(wanderer $<TARGET_OBJECTS:players> ${SOURCES})
