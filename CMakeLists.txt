cmake_minimum_required(VERSION 2.8.4)
project(telegram_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pthread")

# libs
## threads
find_package(Threads REQUIRED)

## openssl
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

## curl
find_package(CURL)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

## boost
set(Boost_USE_MULTITHREADED ON)
if (ENABLE_TESTS)
    find_package(Boost 1.59.0 COMPONENTS system unit_test_framework REQUIRED)
else()
    find_package(Boost 1.59.0 COMPONENTS system REQUIRED)
endif()
include_directories(${Boost_INCLUDE_DIR})

set(LIB_LIST
        #${CMAKE_THREAD_LIBS_INIT}
        ${OPENSSL_LIBRARIES}
        ${Boost_LIBRARIES}
        ${CURL_LIBRARIES}
        )



message("libraries: ${LIB_LIST}")

include_directories(include)

add_executable(telegram-bridge
        include/Robot.h
        include/User.h
        src/Robot.cpp
        src/telegram-bridge.cpp
        src/User.cpp)

add_executable(client
        include/Robot.h
        include/User.h
        src/client.cpp
        src/Robot.cpp
        src/User.cpp)

target_link_libraries(
        client
        ${LIB_LIST}
        TgBot)