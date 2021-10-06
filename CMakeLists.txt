cmake_minimum_required(VERSION 3.0.0)

project(EthernetSocket VERSION 0.1 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "runtime/")

set(OS_DIRECTORY "")

if(APPLE)
	message(STATUS "Apple system")
	set(OS_DIRECTORY "unix")
	message(STATUS "OS_DIRECTORY is " ${OS_DIRECTORY})
elseif(WIN32)
	message(STATUS "Windows system")
	set(OS_DIRECTORY "win")
	message(STATUS "OS_DIRECTORY is " ${OS_DIRECTORY})
endif

add_executable(EthernetSock main.cpp
	stdafx.h			socket.h
	connect_base.h			connect_base.cpp
	${OS_DIRECTORY}/socket_impl.h	${OS_DIRECTORY}/socket_impl.cpp
	resize_buffer.h			resize_buffer.cpp)
