

set(srcRandomCurves
    ${CMAKE_CURRENT_SOURCE_DIR}/randomCurves.cpp
)

add_executable(randomCurves ${srcRandomCurves})

target_include_directories(randomCurves
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(randomCurves Utils)
target_link_libraries(randomCurves Curves)
