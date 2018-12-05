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

find_package(catkin QUIET)
if(catkin_FOUND)

    catkin_package(
      INCLUDE_DIRS include
      LIBRARIES telegram-client
      CATKIN_DEPENDS capnzero
    #  DEPENDS system_lib
    )
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

add_executable(telegram-bridge
  src/TelegramBridge.cpp
  ${DEFAULT_SRC_LIST}
)

target_link_libraries(
  telegram-bridge
  ${DEFAULT_LIB_LIST}
)

# add_executable(client
#         src/client.cpp
#         ${DEFAULT_SRC_LIST})
#
# target_link_libraries(
#         client
#         ${DEFAULT_LIB_LIST}
#         )
