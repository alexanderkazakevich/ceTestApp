
set(srcCurves
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Ellipse.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Circle.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/Curve.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Curves.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Helix.cpp
)

add_library(Curves SHARED ${srcCurves})

target_include_directories(Curves
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Curves
    Utils
)
