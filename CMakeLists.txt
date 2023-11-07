cmake_minimum_required(VERSION 3.18)

project(Facial-Attendence-Sim)

set(SRCS
    src/main.cpp
    "src/DBConnection.cpp"
    src/Device.cpp
)

include_directories(include/)

find_package(Boost REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
find_package(OpenSSL REQUIRED)

add_executable(fasim ${SRCS})
target_link_libraries( fasim OpenSSL::SSL ) #Boost::boost ${Boost_LIBRARIES} )
