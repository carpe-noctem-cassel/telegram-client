cmake_minimum_required(VERSION 2.8.4)
project(telegram-client)

add_compile_options(-std=c++11)
#set(CMAKE_POSITION_INDEPENDENT_CODE ON)

## FIND THIRD PARTY LIBRARIES

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(CapnProto REQUIRED)
find_package(Boost REQUIRED COMPONENTS system )
find_package(PythonLibs REQUIRED)
#find_package(systemd REQUIRED)

## ZMQ
find_package(PkgConfig)
pkg_check_modules(PC_ZeroMQ QUIET zmq)
find_path(ZeroMQ_INCLUDE_DIR
  NAMES zmq.hpp
  PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
)
find_library(ZeroMQ_LIBRARY
  NAMES zmq
  PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
)


## ROS OPTIONAL
find_package(catkin QUIET)
if(catkin_FOUND)
  find_package(catkin REQUIRED COMPONENTS capnzero)

  catkin_package(
    INCLUDE_DIRS include
    LIBRARIES telegram-bridge telegram-msgs
    CATKIN_DEPENDS capnzero
  #  DEPENDS system_lib
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
  ${PYTHON_INCLUDE_DIR}
)

## TELEGRAM-BRIDGE
add_executable(telegram-bridge
  src/TelegramBridge.cpp
)
target_link_libraries(telegram-bridge
  telegram-msgs
  robot
  message
  ${CMAKE_THREAD_LIBS_INIT}
  ${OPENSSL_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CURL_LIBRARIES}
  ${CAPNP_LIBRARIES}
  ${catkin_LIBRARIES}
)
target_compile_definitions(telegram-bridge PUBLIC ZMQ_BUILD_DRAFT_API=1)


if (NOT catkin_FOUND)
  target_include_directories(telegram-bridge PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif()

## MESSAGE ECHO
add_executable(msgecho
        src/msg-echo.cpp
        )

target_link_libraries(msgecho
        telegram-msgs${PYTHON_LIBRARIES}
        message
        ${catkin_LIBRARIES}
        ${CAPNP_LIBRARIES}
        ${ZeroMQ_LIBRARIES}
        ${Boost_LIBRARIES}
        pthread
        )
target_compile_definitions(msgecho PUBLIC ZMQ_BUILD_DRAFT_API=1)

add_library(robot src/Robot.cpp include/Robot.h)
target_link_libraries(robot
        TgBot
        user
        message
        )
target_compile_definitions(robot PUBLIC ZMQ_BUILD_DRAFT_API=1)
set_property(TARGET robot PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(message src/Message.cpp include/Message.h)

add_library(user src/User.cpp include/User.h)

# NLP-PROCESSING TEST
add_executable(nlp src/nlp.cpp)
#target_compile_definitions(nlp PUBLIC spacy)
target_link_libraries(nlp spacy)

## TELEGRAM-CAPNZERO-MESSAGE
set(capnp_message_folder "${CMAKE_CURRENT_SOURCE_DIR}/msg")
file(GLOB_RECURSE capnp_messages ${capnp_message_folder} *.capnp)
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include/telegram_msgs")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/telegram_msgs")
endif()
set(CAPNPC_SRC_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/msg)
set(CAPNPC_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/telegram_msgs")
capnp_generate_cpp(CAPNP_SRCS CAPNP_HDRS ${capnp_messages})
add_library(telegram-msgs ${CAPNP_SRCS})
if (NOT catkin_FOUND)
  target_include_directories(telegram-msgs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif (NOT catkin_FOUND)
