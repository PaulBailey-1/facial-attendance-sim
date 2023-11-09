cmake_minimum_required(VERSION 3.18)

project(Facial-Attendence-Sim)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(SRCS
    src/main.cpp
    "src/DBConnection.cpp"
    src/Device.cpp
 "src/Simulation.cpp" "src/Display.cpp")

include_directories(include/)

find_package(Boost REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

find_package(OpenSSL REQUIRED)

set(CINDER_DIR "C:/tools/Cinder")
include_directories(${CINDER_DIR}/include)
link_directories(${CINDER_DIR}/lib/msw/x64)
link_directories(${CINDER_DIR}/lib/msw/x64/Debug/v143)

add_executable(fasim ${SRCS})
target_link_libraries( fasim OpenSSL::SSL cinder) #Boost::boost ${Boost_LIBRARIES} )
target_compile_features(fasim PRIVATE cxx_std_17)
