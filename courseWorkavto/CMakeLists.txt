cmake_minimum_required(VERSION 3.28)
project(courseWorkavto)

set(CMAKE_CXX_STANDARD 17)

add_executable(courseWorkavto main.cpp
        Admin.cpp
        Admin.h
        Customer.cpp
        Customer.h
        SupplierRequest.cpp
        SupplierRequest.h
        AdminManagement.cpp
        AdminManagement.h
        CarManagement.cpp
        CarManagement.h
        CustomerManagement.cpp
        CustomerManagement.h
        SupplierRequestManagement.cpp
        SupplierRequestManagement.h
        MainMenu.cpp
        MainMenu.h
        NewCar.cpp
        NewCar.h
        OldDomesticCar.cpp
        OldDomesticCar.h
        ForeignCar.cpp
        ForeignCar.h)
