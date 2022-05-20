cmake_minimum_required(VERSION 3.16)

project(ceTestApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${USE_SANITIZER}" STREQUAL "ON")
    #
    # It is not possible to combine more than one of the 3 options below at the time
    #
    set(ADDR_SANITIZER OFF)     # memory error detector
    set(THREAD_SANITIZER OFF)   # data race detector
    set(MEM_SANITIZER OFF)      # detector of uninitialized reads

    set(UB_SANITIZER ON)        # undefined behavior checker

    if ("${ADDR_SANITIZER}" STREQUAL "ON")
        set(SANITIZER_OPTIONS "-fsanitize=address")
    elseif ("${THREAD_SANITIZER}" STREQUAL "ON")
        set(SANITIZER_OPTIONS "-fsanitize=thread")
    elseif ("${MEM_SANITIZER}" STREQUAL "ON")
        set(SANITIZER_OPTIONS "-fsanitize=memory")
    endif()
    if ("${UB_SANITIZER}" STREQUAL "ON")
        set(SANITIZER_OPTIONS "${SANITIZER_OPTIONS} -fsanitize=undefined")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mllvm -asan-use-private-alias=1 ${SANITIZER_OPTIONS} -fsanitize-recover=all -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SANITIZER_OPTIONS}")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${SANITIZER_OPTIONS}")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Set default debug flags")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb3 -g3 -DDEBUG")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb3 -g3 -DDEBUG")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-limit-debug-info")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    endif()
endif()
