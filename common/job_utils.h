//
// Created by Matteo on 18/09/20.
//

#ifndef SERVER_JOB_UTILS_H
#define SERVER_JOB_UTILS_H

#include "messages/JobRequest.pb.h"
#include "Action.h"

BackupPB::JobRequest::PBAction toPBAction(Action toConvert);
Action toType(BackupPB::JobRequest::PBAction toConvert);

#endif //SERVER_JOB_UTILS_H
