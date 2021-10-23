cmake_minimum_required(VERSION 3.0)

project(EthernetSocket VERSION 0.1 LANGUAGES CXX)

set(RUNTIME_DIRECTORY "runtime")
set(OS_DIRECTORY "unix")

#logger can be disabled
set(LOGGER_ENABLED ON)

#set package for OS
if(APPLE)
    message(STATUS "Apple system")
    set(OS_DIRECTORY "unix")
elseif(WIN32)
    message(STATUS "Windows system")
    set(OS_DIRECTORY "win")
endif()

#set build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_DIRECTORY})
message(STATUS "'CMAKE_RUNTIME_OUTPUT_DIRECTORY' is [${RUNTIME_DIRECTORY}]")

message(STATUS "'OS_DIRECTORY' is  [${OS_DIRECTORY}]")

#connect logger module
set(LOGGER_MODULE_FILES "")
if(LOGGER_ENABLED)
	set(LOGGER_MODULE_FILES "logger/logger.h" "logger/logger.cpp")
	add_definitions(-DLOGGER_ENABLED)
	message(STATUS "Module Logger enabled")
endif()

add_executable(EthernetSock main.cpp	stdafx.h
	socket.h				socket.cpp
	connect_base.h			connect_base.cpp
	${OS_DIRECTORY}/socket_impl.h	${OS_DIRECTORY}/socket_impl.cpp
	resize_buffer.h			resize_buffer.cpp
	${LOGGER_MODULE_FILES})

message(STATUS "BUILD COMPLETED SUCCESSFULLY")
