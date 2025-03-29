cmake_minimum_required(VERSION 3.29)
project(note)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.15.2
)
FetchContent_MakeAvailable(googletest)

add_library(note_lib
        Note.cpp Note.h
        Collection.cpp Collection.h
        ConcreteObserver.cpp ConcreteObserver.h
        Subject.h
        Observer.h
)

add_executable(note main.cpp)
target_link_libraries(note PRIVATE note_lib)

add_executable(note_tests test/CollectionTest.cpp
        test/NoteTest.cpp
        test/ObserverTest.cpp
)
target_link_libraries(note_tests PRIVATE note_lib gtest gtest_main)

target_include_directories(note_tests PRIVATE ${googletest_SOURCE_DIR}/googletest/include)

enable_testing()
include(GoogleTest)
gtest_discover_tests(note_tests)
