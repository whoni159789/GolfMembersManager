cmake_minimum_required(VERSION 3.0.0)

project(GolfMembersManager)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
    ./src/golfMembershipManager.cpp
    ./src/app/Listener/Listener.cpp
    ./src/app/Controller/Controller.cpp
    ./src/app/Service/MembersManageService.cpp
    ./src/app/Entity/MembersEntity.cpp
    ./src/app/View/View.cpp
    ./src/hw/Button/Button.cpp
    ./src/hw/Button/ManageButton.cpp
    ./src/hw/rfid/mfrc522.cpp
    ./src/hw/rfid/CardReader.cpp
    ./src/hw/spi/SPI.cpp
    ./src/hw/Monitor/Monitor.cpp
    ./src/hw/I2C/I2C.cpp
    ./src/hw/LCD/LCD.cpp
    ./src/hw/tcpServer/ComDev.cpp
    ./src/hw/tcpServer/tcpServer.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ./src
    ./src/app/Model
    ./src/app/Listener
    ./src/app/Controller
    ./src/app/Service
    ./src/app/Entity
    ./src/app/View
    ./src/hw/Button
    ./src/hw/rfid
    ./src/hw/spi
    ./src/hw/Monitor
    ./src/hw/I2C
    ./src/hw/LCD
    ./src/hw/tcpServer
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    -lwiringPi
)

target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall
)

