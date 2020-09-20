//
// Created by Matteo on 18/09/20.
//

#include "job_utils.h"

JobRequest::PBAction toPBAction(Action toConvert) {
    switch (toConvert) {
        case ADD_FILE:
            return JobRequest::PBAction::JobRequest_PBAction_ADD_FILE;
        case ADD_DIRECTORY:
            return JobRequest::PBAction::JobRequest_PBAction_ADD_DIRECTORY;
        case UPDATE:
            return JobRequest::PBAction::JobRequest_PBAction_UPDATE;
        case DELETE:
            return JobRequest::PBAction::JobRequest_PBAction_DELETE;
        case CANCELLED:
            return JobRequest::PBAction::JobRequest_PBAction_CANCELLED;
    }
}

Action toType(JobRequest::PBAction toConvert) {
    switch (toConvert) {
        case JobRequest::PBAction::JobRequest_PBAction_ADD_FILE:
            return ADD_FILE;
        case JobRequest::PBAction::JobRequest_PBAction_ADD_DIRECTORY:
            return ADD_DIRECTORY;
        case JobRequest::PBAction::JobRequest_PBAction_UPDATE:
            return UPDATE;
        case JobRequest::PBAction::JobRequest_PBAction_DELETE:
            return DELETE;
        case JobRequest::PBAction::JobRequest_PBAction_CANCELLED:
            return CANCELLED;
    }
}