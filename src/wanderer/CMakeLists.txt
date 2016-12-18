add_subdirectory(items)
add_subdirectory(players)
add_subdirectory(enemies)

file(GLOB SOURCES "*.cxx")
add_library(wanderer
    $<TARGET_OBJECTS:items>
    $<TARGET_OBJECTS:players>
    $<TARGET_OBJECTS:enemies>
    ${SOURCES})
