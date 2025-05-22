cmake_minimum_required(VERSION 3.20)
project(AirlineReservationSystem)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(AirlineReservationSystem
        main.cpp
        src/Passenger.cpp
        include/Passenger.h
        src/Flight.cpp
        include/Flight.h
        src/Reservation.cpp
        include/Reservation.h
        src/AirlineSystem.cpp
        include/AirlineSystem.h
        test/test.cpp
)

add_executable(runTests test/test.cpp src/AirlineSystem.cpp src/Passenger.cpp src/Flight.cpp src/Reservation.cpp)
