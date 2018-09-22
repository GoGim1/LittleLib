include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

find_package(Threads)

add_executable(Little_String_Test little_string_test.cc)
target_link_libraries(Little_String_Test gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})