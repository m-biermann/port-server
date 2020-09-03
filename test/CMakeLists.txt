# 'Boost_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable (portServerTests test1.cpp)
target_link_libraries (portServerTests PRIVATE ${Boost_LIBRARIES} ${PROJECT_NAME}::portServer)
target_include_directories(portServerTests PRIVATE ${Boost_INCLUDE_DIRS})

add_test(NAME portServerTests COMMAND portServerTests)