cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(portServer src/construction/AppBuilder.cpp src/construction/AppBuilder.h src/TcpAcceptor.h src/TcpAcceptor.cpp src/main.cpp)

target_include_directories(portServer PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> PUBLIC ${Boost_INCLUDE_DIR})

target_link_libraries(portServer PUBLIC ${PROJECT_NAME}::iocServer)

add_library(${PROJECT_NAME}::portServer ALIAS portServer)

add_subdirectory(test)

include(GNUInstallDirs)
install(TARGETS portServer
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/mabiphmo TYPE INCLUDE)