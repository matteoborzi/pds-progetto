cmake_minimum_required(VERSION 3.10)
project(server)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

find_package(Boost REQUIRED)

# adding third party library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/thirdparty/SQLiteCpp)

# adding headers for third party library
include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SQLiteCpp/include
)

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

find_package(Threads)
link_libraries(stdc++fs -lcryptopp -lboost_locale)

add_executable(server main.cpp
        authentication/authentication.cpp authentication/authentication.h
        Workspace/workspace_utils.cpp Workspace/workspace_utils.h
        Workspace/load.cpp Workspace/load.h
        waiter/Waiter.cpp waiter/Waiter.h
        pathPool/PathPool.cpp pathPool/PathPool.h
        jobRequestQueue/JobRequestQueue.cpp jobRequestQueue/JobRequestQueue.h
        jobRequestQueue/jobManager.cpp jobRequestQueue/jobManager.h
        ChecksumStorage/ChecksumStorage.cpp ChecksumStorage/ChecksumStorage.h

        #UTILS
        log/log_utils.cpp log/log_utils.h
        ../common/messages/socket_utils.h
        ../common/messages/file_utils.cpp ../common/messages/file_utils.h
        ../common/Checksum.cpp ../common/Checksum.h
        ../common/fieldValidation.cpp ../common/fieldValidation.h

        #messages
        ../common/messages/JobRequest.pb.h ../common/messages/JobRequest.pb.cc
        ../common/messages/JobResponse.pb.h ../common/messages/JobResponse.pb.cc
        ../common/messages/AuthenticationResponse.pb.cc ../common/messages/AuthenticationResponse.pb.h
        ../common/messages/AuthenticationRequest.pb.cc ../common/messages/AuthenticationRequest.pb.h
        ../common/messages/AvailableWorkspaces.pb.cc ../common/messages/AvailableWorkspaces.pb.h
        ../common/messages/Workspace.pb.cc ../common/messages/Workspace.pb.h
        ../common/messages/MachinePath.pb.cc ../common/messages/MachinePath.pb.h
        ../common/messages/MetaInfo.pb.cc   ../common/messages/MetaInfo.pb.h
        ../common/messages/DirectoryEntryMessage.pb.cc ../common/messages/DirectoryEntryMessage.pb.h
        ../common/messages/RestoreResponse.pb.cc ../common/messages/RestoreResponse.pb.h
       )

target_link_libraries(server
        ${CMAKE_THREAD_LIBS_INIT}
        ${OPENSSL_LIBRARIES}
        ${Boost_SYSTEM_LIBRARY}
        SQLiteCpp
        sqlite3
        pthread
        dl
        ${Boost_FILESYSTEM_LIBRARY}
        ${PROTOBUF_LIBRARY} )
