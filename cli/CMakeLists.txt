
set(srcCliCurve
    ${CMAKE_CURRENT_SOURCE_DIR}/cliCurve.cpp
)

add_executable(cliCurve ${srcCliCurve})

target_include_directories(cliCurve
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(cliCurve Utils)
target_link_libraries(cliCurve Curves)
