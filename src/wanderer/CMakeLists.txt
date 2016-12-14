add_subdirectory(players)
add_subdirectory(enemies)

file(GLOB SOURCES "*.cxx")
add_library(wanderer
    $<TARGET_OBJECTS:players>
    $<TARGET_OBJECTS:enemies>
    ${SOURCES})
