cmake_minimum_required(VERSION 2.8.4)
project(telegram-client)

add_compile_options(-std=c++11)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system )
find_package(CURL)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

find_package(CapnProto)
find_package(catkin QUIET)
if(catkin_FOUND)

    # this line does not work right now...
    # find_package(catkin REQUIRED COMPONENTS capnzero)

    catkin_package(
      INCLUDE_DIRS include
      LIBRARIES telegram-client
      CATKIN_DEPENDS capnzero
    #  DEPENDS system_lib
    )
else (catkin_FOUND)
    set(catkin_LIBRARIES "event_handling discovery_msgs capnzero")
endif(catkin_FOUND)

include_directories(include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS})

## requried source for all targets
set(DEFAULT_SRC_LIST
  src/Robot.cpp
  src/User.cpp
)

## required libraries for all targets
set(DEFAULT_LIB_LIST
  TgBot
  ${CMAKE_THREAD_LIBS_INIT}
  ${OPENSSL_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CURL_LIBRARIES}
)

add_library(
    message_wrap
    src/Message.cpp
    include/Message.h
    ${CapnProto}
)
target_link_libraries(
    message_wrap
    ${CAPNP_LIBRARIES}
)

add_executable(telegram-bridge
  src/TelegramBridge.cpp
  ${DEFAULT_SRC_LIST}
)

target_link_libraries(
  telegram-bridge
    message_wrap
    tgbridge_basic_messages
    ${DEFAULT_LIB_LIST}
)

if (NOT catkin_FOUND)
    target_include_directories(telegram-bridge PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif()

# add_executable(client
#         src/client.cpp
#         ${DEFAULT_SRC_LIST})
#
# target_link_libraries(
#         client
#         ${DEFAULT_LIB_LIST}
#         )

################  TELEGRAM MESSAGES
## Autogenerate the c++ capnproto files
set(capnp_message_folder "${CMAKE_CURRENT_SOURCE_DIR}/msg")
file(GLOB_RECURSE capnp_messages ${capnp_message_folder} *.capnp)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include/tgbridge_basic_messages")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/tgbridge_basic_messages")
endif()

set(CAPNPC_SRC_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/msg)
set(CAPNPC_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/tgbridge_basic_messages")
capnp_generate_cpp(CAPNP_SRCS CAPNP_HDRS ${capnp_messages})
add_library(tgbridge_basic_messages ${CAPNP_SRCS})

message("CAPNP_SRCS: ${CAPNP_SRCS}")
message("CAPNP_HDRS: ${CAPNP_HDRS}")

if (NOT catkin_FOUND)
    target_include_directories(tgbridge_basic_messages PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif (NOT catkin_FOUND)
