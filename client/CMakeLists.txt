cmake_minimum_required(VERSION 3.10)
project(client)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost REQUIRED)


find_package(Threads)
link_libraries(stdc++fs -lprotobuf
       -lboost_locale
        -lcryptopp)


add_executable(client main.cpp
        job/Job.cpp job/Job.h job/JobQueue.cpp job/JobQueue.h
        Configuration/Configuration.cpp Configuration/Configuration.h
        Configuration/file_util.cpp Configuration/file_util.h
        DirectoryStructure/Directory.cpp DirectoryStructure/Directory.h DirectoryStructure/DirectoryEntry.h
        DirectoryStructure/File.h DirectoryStructure/File.cpp DirectoryStructure/utils.cpp DirectoryStructure/utils.h
        FileWatcher/watcher.cpp FileWatcher/watcher.h

        communicationProtocol/initialization.cpp communicationProtocol/initialization.h
        communicationProtocol/dataManagement.cpp communicationProtocol/dataManagement.h
        communicationProtocol/restore.cpp communicationProtocol/restore.h

        #UTILITIES
        ../common/time_utils.cpp ../common/time_utils.h
        ../common/Checksum.cpp ../common/Checksum.h
        ../common/messages/socket_utils.h
        ../common/job_utils.h ../common/job_utils.cpp
        ../common/messages/file_utils.cpp ../common/messages/file_utils.h
        ../common/fieldValidation.cpp ../common/fieldValidation.h

        #PROTO BUF MESSAGES
        ../common/messages/AuthenticationRequest.pb.cc ../common/messages/AuthenticationRequest.pb.h
        ../common/messages/AuthenticationResponse.pb.cc ../common/messages/AuthenticationResponse.pb.h
        ../common/messages/DirectoryEntryMessage.pb.cc ../common/messages/DirectoryEntryMessage.pb.h
        ../common/messages/JobRequest.pb.cc ../common/messages/JobRequest.pb.h
        ../common/messages/JobResponse.pb.h ../common/messages/JobResponse.pb.cc
        ../common/messages/AvailableWorkspaces.pb.cc ../common/messages/AvailableWorkspaces.pb.h
        ../common/messages/Workspace.pb.cc ../common/messages/Workspace.pb.h
        ../common/messages/MachinePath.pb.cc ../common/messages/MachinePath.pb.h
        ../common/messages/MetaInfo.pb.cc   ../common/messages/MetaInfo.pb.h
        ../common/messages/RestoreResponse.pb.cc ../common/messages/RestoreResponse.pb.h
        )
target_link_libraries(client ${CMAKE_THREAD_LIBS_INIT}  ${Boost_SYSTEM_LIBRARY})

