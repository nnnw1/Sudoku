CMAKE_MINIMUM_REQUIRED(VERSION 3.12) #required cmake version

PROJECT(sudoku) #project name

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") #add c++11 support

SET(CMAKE_BUILD_TYPE "Debug") #Debug mode OPtions: Release Debug MinSizeRel RelWithDebInfo

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb") #debug mode gdb options
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall") #release mode gdb options

# set(CMAKE_VERSION_MAKEFILE ON) #open debug when there are errors

# enable_testing() #open test

add_definitions(-DDEBUG) #equal to #define DEBUG

# add_subdirectory(test) #add test path

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin") #.exe output path

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include") #include files path

#can identify OS
MESSAGE("Identifying the OS...")
if(WIN32)
    MESSAGE("This is Windows.")
    exec_program("cmd" ${PROJECT_SOURCE_DIR} ARGS "/c chcp" OUTPUT_VARIABLE CHCP_OUT)
    string(REGEX MATCH "[0-9]+" CODE_PAGE ${CHCP_OUT})
    message("Active code page: ${CODE_PAGE}")
    if(CODE_PAGE EQUAL 936 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        MESSAGE("THis is Windows Chinese. Change the charset to GBK.")
        add_compile_options("-fexec-charset=GBK")
    endif()
elseif(APPLE)
    MESSAGE("This is MacOS.")
elseif(UNIX)
    MESSAGE("This is Linux.")
endif()
#can identify OS


AUX_SOURCE_DIRECTORY(src DIR_SRCS) #add src path, will scan all the files

add_executable(sudoku  #output exe named sudoku
    ${DIR_SRCS}    
)  