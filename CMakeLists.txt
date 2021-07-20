cmake_minimum_required(VERSION 3.0.0)

project(EthernetSocket VERSION 0.1 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "runtime/")

add_executable(EthernetSock main.cpp	stdafx.h
	connect.h		connect.cpp
	connect_mac.h		connect_mac.cpp
	resize_buffer.h		resize_buffer.cpp)
