cmake_minimum_required(VERSION 3.10.0)

project(google_curl_tool)

find_package(CURL REQUIRED)

add_executable(tool main.cpp)

target_link_libraries(tool PUBLIC
                CURL::libcurl)