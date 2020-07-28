1. Configure WSL as in the link: https://www.jetbrains.com/help/clion/how-to-use-wsl-development-environment-in-clion.html#wsl-general
2. ```
   sudo apt install libboost-all-dev
   sudo apt install aptitude
   aptitude search boost
   ```
3. CMakeLists.txt should be like:
```    
cmake_minimum_required(VERSION 3.10)
project(server)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS system filesystem REQUIRED)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()

find_package(Threads)


include_directories(${Boost_INCLUDE_DIR})
add_executable(server main.cpp authentication/authentication.cpp authentication/authentication.h)
target_link_libraries(server ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
```