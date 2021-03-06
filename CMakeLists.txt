cmake_minimum_required(VERSION 2.8.4)
project(telegram-client)

add_compile_options(-std=c++11)
#set(CMAKE_POSITION_INDEPENDENT_CODE ON)

## FIND THIRD PARTY LIBRARIES
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(CapnProto REQUIRED)
find_package(Boost REQUIRED COMPONENTS system )

## ROS OPTIONAL
find_package(catkin QUIET)
if(catkin_FOUND)
  find_package(catkin REQUIRED COMPONENTS capnzero system_config id_capnzero)

  catkin_package(
    INCLUDE_DIRS include
    LIBRARIES telegram-bridge telegram-msgs
    CATKIN_DEPENDS capnzero
  #  DEPENDS system_lib
  )
  catkin_package(
    INCLUDE_DIRS include
    LIBRARIES telegram_msg_wrapper
    CATKIN_DEPENDS capnzero system_config
  )
else (catkin_FOUND)
  set(catkin_LIBRARIES "capnzero")
endif(catkin_FOUND)

include_directories(include
  ${OPENSSL_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
  ${ZeroMQ_INCLUDE_DIRS}
  ${CAPNP_INCLUDE_DIRS}
)

## TELEGRAM-BRIDGE
add_executable(telegram-bridge
  src/TelegramBridge.cpp
)
target_link_libraries(telegram-bridge
  telegram-msgs
  robot
  telegram_msg_wrapper
  ${CMAKE_THREAD_LIBS_INIT}
  ${OPENSSL_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CURL_LIBRARIES}
  ${CAPNP_LIBRARIES}
  ${catkin_LIBRARIES}
)


if (NOT catkin_FOUND)
  target_include_directories(telegram-bridge PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif()

## MESSAGE ECHO
add_executable(msgecho
  src/msg-echo.cpp
)

target_link_libraries(msgecho
  telegram-msgs
  telegram_msg_wrapper
  ${catkin_LIBRARIES}
  ${CAPNP_LIBRARIES}
  ${ZeroMQ_LIBRARIES}
  ${Boost_LIBRARIES}
  pthread
)

add_library(robot src/Robot.cpp include/Robot.h)
target_link_libraries(robot
  TgBot
  user
  telegram_msg_wrapper
)
# target_compile_definitions(robot PUBLIC ZMQ_BUILD_DRAFT_API=1)
# set_property(TARGET robot PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(telegram_msg_wrapper src/Message.cpp include/Message.h)

add_library(user src/User.cpp include/User.h)


## TESTMESSAGE
add_executable(testmsg
  src/testmsg.cpp
)

target_link_libraries(testmsg
  telegram-msgs
  telegram_msg_wrapper
  ${Boost_LIBRARIES}
  ${catkin_LIBRARIES}
  ${CAPNP_LIBRARIES}
  ${ZeroMQ_LIBRARIES}
  pthread
)


## TELEGRAM-CAPNZERO-MESSAGE
set(CAPNPC_IMPORT_DIRS "${id_capnzero_SOURCE_PREFIX}/include")# include external capnp message schema files

set(capnp_message_folder "${CMAKE_CURRENT_SOURCE_DIR}/include/telegram_msgs")
file(GLOB_RECURSE capnp_messages ${capnp_message_folder} *.capnp)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include/telegram_msgs")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/telegram_msgs")
endif()

set(CAPNPC_SRC_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/include/telegram_msgs")
set(CAPNPC_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/telegram_msgs")
capnp_generate_cpp(CAPNP_SRCS CAPNP_HDRS ${capnp_messages})

add_library(telegram-msgs ${CAPNP_SRCS})
if (NOT catkin_FOUND)
  target_include_directories(telegram-msgs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif (NOT catkin_FOUND)
