project(theNextWin32Socket)
cmake_minimum_required(VERSION 3.5)
include_directories(
	include
)
## WSA计数
add_library(
	socketBase_lib
	src/lib/socketBase.cpp
)
## UDP广播封装
add_library(
	theNextUDPbroadcast_lib
	src/lib/broadcastUDP.cpp
)
target_link_libraries(
	theNextUDPbroadcast_lib
	socketBase_lib
	wsock32
)

## TCP封装
add_library(
	theNextTCPptop_lib
	src/lib/ptopTCP.cpp
)
target_link_libraries(
	theNextTCPptop_lib
	socketBase_lib
	wsock32
)
## 测试实例，测试UDP是否能够正常发送
add_executable(
	UDP_test_server
	src/test/UDP_test_server.cpp
)
target_link_libraries(
	UDP_test_server	
	theNextUDPbroadcast_lib 
)

## 测试实例，测试UDP是否能够正常接收
add_executable(
	UDP_test_client
	src/test/UDP_test_client.cpp
)
target_link_libraries(
	UDP_test_client	
	theNextUDPbroadcast_lib 
)
## 测试实例,测试TCP是否能够正常收发
add_executable(
	TCP_test_client
	src/test/TCP_test_client.cpp
)
target_link_libraries(
	TCP_test_client
	theNextTCPptop_lib
)
add_executable(
	TCP_test_server
	src/test/TCP_test_server.cpp
)
target_link_libraries(
	TCP_test_server
	theNextTCPptop_lib
)