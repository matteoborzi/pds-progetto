//
// Created by Matteo on 18/09/20.
//

#include "job_utils.h"

BackupPB::JobRequest::PBAction toPBAction(Action toConvert) {
    switch (toConvert) {
        case ADD_FILE:
            return BackupPB::JobRequest::PBAction::JobRequest_PBAction_ADD_FILE;
        case ADD_DIRECTORY:
            return BackupPB::JobRequest::PBAction::JobRequest_PBAction_ADD_DIRECTORY;
        case UPDATE:
            return BackupPB::JobRequest::PBAction::JobRequest_PBAction_UPDATE;
        case DELETE:
            return BackupPB::JobRequest::PBAction::JobRequest_PBAction_DELETE;
        case CANCELLED:
            return BackupPB::JobRequest::PBAction::JobRequest_PBAction_CANCELLED;
    }
}

Action toType(BackupPB::JobRequest::PBAction toConvert) {
    switch (toConvert) {
        case BackupPB::JobRequest::PBAction::JobRequest_PBAction_ADD_FILE:
            return ADD_FILE;
        case BackupPB::JobRequest::PBAction::JobRequest_PBAction_ADD_DIRECTORY:
            return ADD_DIRECTORY;
        case BackupPB::JobRequest::PBAction::JobRequest_PBAction_UPDATE:
            return UPDATE;
        case BackupPB::JobRequest::PBAction::JobRequest_PBAction_DELETE:
            return DELETE;
        case BackupPB::JobRequest::PBAction::JobRequest_PBAction_CANCELLED:
            return CANCELLED;
    }
}