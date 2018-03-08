project(theNextWin32Socket)
cmake_minimum_required(VERSION 3.5)
add_compile_options(-std=c++11)
include_directories(
	include
)
include_directories(
	fuchsia-mirror-third_party-json/include	
)
## WSA计数
add_library(
	socketBase_lib
	src/lib/socketBase.cpp
)
## 线程封装
add_library(
	theNextThread_lib
	src/lib/thenextThread.cpp
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

## 本机信息获取封装
add_library(
	socketinformation_lib
	src/lib/socketInformation.cpp
)
target_link_libraries(
	socketinformation_lib
	socketBase_lib
	wsock32
	netapi32
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
## 用户登录类
add_library(
	loginer_lib
	src/lib/loginer.cpp
)
target_link_libraries(
	loginer_lib
socketBase_lib
theNextThread_lib
theNextUDPbroadcast_lib
socketinformation_lib
theNextTCPptop_lib
)
## 综合
add_library(
	all_lib
)
target_link_libraries(
	all_lib
socketBase_lib
theNextUDPbroadcast_lib
socketinformation_lib
theNextTCPptop_lib
)
## 测试实例，测试UDP是否能够正常发送
add_executable(
	UDP_test_server
	src/test/UDP_test_server.cpp
)
target_link_libraries(
	UDP_test_server	
	all_lib
	theNextUDPbroadcast_lib 
	theNextThread_lib
)

## 测试实例，测试UDP是否能够正常接收
add_executable(
	UDP_test_client
	src/test/UDP_test_client.cpp
)
target_link_libraries(
	UDP_test_client	
	all_lib
	theNextUDPbroadcast_lib 
	theNextThread_lib
)
## 测试实例,测试TCP是否能够正常收发
add_executable(
	TCP_test_client
	src/test/TCP_test_client.cpp
)
target_link_libraries(
	TCP_test_client
	theNextTCPptop_lib
	theNextThread_lib
)
add_executable(
	TCP_test_server
	src/test/TCP_test_server.cpp
)
target_link_libraries(
	TCP_test_server
	theNextTCPptop_lib
	theNextThread_lib
)
## 测试主机信息获取函数
add_executable(
	socketInformation_test
	src/test/socket_information_test.cpp
)
target_link_libraries(
	socketInformation_test
	socketinformation_lib
)

## 测试线程库正确性
add_executable(
	thenextThread
	src/test/thread_test.cpp
)
target_link_libraries(
	thenextThread
	theNextThread_lib
)
## 测试用户类
add_executable(
	userlog
	src/test/test_loginer.cpp
)
target_link_libraries(
	userlog
	loginer_lib
)