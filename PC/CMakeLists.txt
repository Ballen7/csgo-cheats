cmake_minimum_required(VERSION 3.19)

set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

project(pc-software)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR_PLATFORM x86)

set(SOURCES
        Arduino/arduino.cpp
        Arrays/arrays.cpp
        Features/aim_bot.h
        Features/bunny_hop.h
        Features/trigger_bot.h
        Global/global.cpp
        Memory/memory.cpp
        SDK/Entity/LocalPlayer/abstract_local_player.h
        SDK/Entity/LocalPlayer/local_player.cpp
        SDK/Entity/entity.cpp
        SDK/EntityList/entity_list.cpp
        Timer/timer.cpp
        Utils/utils.cpp
        Vector/vector.h
        dump.h
        )

add_compile_options(-Wno-error -fpermissive)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE setupapi)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_options(${PROJECT_NAME} PRIVATE -static -static-libgcc -static-libstdc++)
