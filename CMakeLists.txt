cmake_minimum_required(VERSION 2.4)

project(addr_book)
FIND_PACKAGE( Boost 1.65 COMPONENTS program_options REQUIRED )
include_directories(${PROJECT_SOURCE_DIR})
add_executable(app main.cpp address_book.cpp contact.cpp)
TARGET_LINK_LIBRARIES( app LINK_PUBLIC ${Boost_LIBRARIES} )
