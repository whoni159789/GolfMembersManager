cmake_minimum_required(VERSION 3.0.0)

project(GolfMembersManager)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
    ./src/golfMembershipManager.cpp
    ./src/app/Listener/Listener.cpp
    ./src/app/Controller/Controller.cpp
    ./src/app/Service/MembersManageService.cpp
    ./src/app/Entity/MembersEntity.cpp
    ./src/hw/Button/Button.cpp
    ./src/hw/Button/ManageButton.cpp
    ./src/hw/rfid/mfrc522.cpp
    ./src/hw/rfid/CardReader.cpp
    ./src/hw/spi/SPI.cpp
    ./src/hw/Monitor/Monitor.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ./src
    ./src/app/Model
    ./src/app/Listener
    ./src/app/Controller
    ./src/app/Service
    ./src/app/Entity
    ./src/hw/Button
    ./src/hw/rfid
    ./src/hw/spi
    ./src/hw/Monitor
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    -lwiringPi
)

target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall
)

