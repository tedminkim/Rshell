CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(test
	tests/test.cpp
)

ADD_EXECUTABLE(rshell
	src/rshell.cpp
	src/execute.cpp
	src/connector.cpp
	src/commands.cpp
	src/main.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
#TARGET_LINK_LIBRARIES(rshell gtest)
