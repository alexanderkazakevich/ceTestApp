

set(srcUtils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ArgParse.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utils.cpp
)

add_library(Utils SHARED ${srcUtils})

target_include_directories(Utils
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
