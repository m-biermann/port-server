cmake_minimum_required(VERSION 3.16)
project(portServer)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include_directories(include)

add_library(portServer include/mabiphmo/portServer/construction/IAppBuilder.h src/construction/AppBuilder.cpp src/construction/AppBuilder.h include/mabiphmo/portServer/handler/ITcpHandler.h src/TcpAcceptor.h src/TcpAcceptor.cpp src/main.cpp include/mabiphmo/portServer/main.h)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(portServer ${BOOST_LIB_DIR})

find_library(iocServer REQUIRED)
target_link_libraries(portServer ${iocServer_LIB_DIR})

add_subdirectory(test)
