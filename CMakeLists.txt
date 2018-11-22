cmake_minimum_required(VERSION 2.8.4)
project(telegram_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
include_directories(include)

## requried source for all targets
set(DEFAULT_SRC_LIST
        src/Robot.cpp
        src/User.cpp)

# libs
## threads
find_package(Threads REQUIRED)
## openssl
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
## boost
find_package(Boost COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

## curl
find_package(CURL)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

## required libraries for all targets
set(DEFAULT_LIB_LIST
        TgBot
        ${CMAKE_THREAD_LIBS_INIT}
        ${OPENSSL_LIBRARIES}
        ${Boost_LIBRARIES}
        ${CURL_LIBRARIES}
        )


add_executable(telegram-bridge
        src/telegram-bridge.cpp
        ${DEFAULT_SRC_LIST})

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
