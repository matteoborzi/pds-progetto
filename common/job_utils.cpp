//
// Created by Matteo on 18/09/20.
//

#include "job_utils.h"

/**
 * convert a Action (defined in Action.h) to PBAction
 * @param Action to convert
 * @return the corresponding PBAction
 */
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
    return BackupPB::JobRequest::PBAction::JobRequest_PBAction_CANCELLED;
}

/**
 * convert a PBAction to Action (defined in Action.h)
 * @param PBAction to convert
 * @return the corresponding Action
 */
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
    return CANCELLED;
}