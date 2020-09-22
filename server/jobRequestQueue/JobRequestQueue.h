//
// Created by rober on 15/09/2020.
//

#ifndef SERVER_JOBREQUESTQUEUE_H
#define SERVER_JOBREQUESTQUEUE_H

#include <mutex>
#include <condition_variable>
#include <list>
#include "../../common/messages/JobRequest.pb.h"

class JobRequestQueue {

public:

    void enqueueJobRequest(BackupPB::JobRequest&);

    BackupPB::JobRequest dequeueJobRequest();

};


#endif //SERVER_JOBREQUESTQUEUE_H
