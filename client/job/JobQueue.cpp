#include <optional>
#include <iostream>
#include "JobQueue.h"

#define MAX_SIZE 100

Action getAction(Action oldAct, Action newAct);

/**
 * Method to add a new Job in the queue
 * @param Job to add
 * @throws logic_error if the action to be performed is in conflict with other Job on the same path
 */
void JobQueue::add(Job &j) {
    std::unique_lock l{m};
    for (Job &j1:queue) {
        if (j1 == j) {
            //updating action when a Job on the same element is already present
            j1.setAct(getAction(j1.getAct(), j.getAct()));
            if (j1.getAct() == CANCELLED)
                //removing job if cancelled
                queue.remove(j1);
            return;
        }
    }
    //waiting for some new space
    full.wait(l, [this] { return queue.size() + sent.size() <= MAX_SIZE; });
    //adding the element
    queue.emplace_back(j);
    //notifying threads waiting for a new job
    empty.notify_one();

}

/**
 * Method to get the first free Job in queue. It will also put the Job in the sen queue
 * @return first Job in queue
 */
Job JobQueue::getLastAndSetSent() {
    std::unique_lock l{m};

    std::optional<Job> res;
    while (!res.has_value()) {
        //waiting for a new value (or an element to be removed from sent list
        empty.wait(l, [this] { return !queue.empty(); });
        for (Job &j : queue) {
            //searching if the item has been already sent and not confirmed
            bool foundSent = false;
            for (Job &s : sent) {
                if (s.getPath() == j.getPath()) {
                    foundSent = true;
                    break;
                }
            }
            // a Job on the same file has been found, scanning next element in queue
            if (foundSent)
                continue;

            //saving the result and moving into sent list
            res.emplace(j);
            sent.emplace_back(j);
            queue.remove(j);
            break;

        }
        if(!res.has_value())
            empty.wait(l);
    }
    return res.value();
}

/**
 * Remove the element from the list of job sent
 * @param path
 * @throws logic_error no action has been sent for that path
 */
void JobQueue::setConcluded(const std::string &path) {
    std::unique_lock l{m};
    for (Job &j: sent) {
        if (j.getPath() == path) {
            sent.remove(j);
            // a new place is available
            full.notify_one();

            // an item from sent has been removed:
            // this means that an element from the queue may be sent in getLastAndSetSent
            empty.notify_one();
            return;
        }
    }
    throw std::logic_error("No pending job for path " + path);

}

/**
 * Remove the element from the sent queue and re-insert it after a failure
 * @param path
 * @throws logic_error if the action to be performed is in conflict with other Job on the same path
 * @throws logic_error no action has been sent for that path
 */
void JobQueue::retry(const std::string &path) {
    std::unique_lock l{m};

    std::optional<Job> j;
    for (Job &s: sent) {
        //searching the element in sent queue
        if (s.getPath() == path) {
            j.emplace(s);
            sent.remove(s);
            break;
        }
    }
    if (!j.has_value())
        throw std::logic_error("No action was pending for " + path);
    for (Job &j1:queue) {
        //searching in queue, if found a new action has to be computed
        if (j1 == j.value()) {
            j1.setAct(getAction(j.value().getAct(), j1.getAct()));

            if(j1.getAct()==CANCELLED)
                //removing job if cancelled
                queue.remove(j1);

            // an item from sent has been removed:
            // this means that an element from the queue can be sent in getLastAndSetSent
            empty.notify_one();

            //removed at least one job
            full.notify_one();
            return;
        }
    }

    //not in the queue, the item must be added
    queue.emplace_back(j.value());

    // an item from sent has been removed:
    // this means that an element from the queue can be sent in getLastAndSetSent
    empty.notify_one();

    return;

}

/**
 * Computes the resulting action of 2 consecutive actions
 * @param oldAct
 * @param newAct
 * @return the write change to do
 */
Action getAction(Action oldAct, Action newAct) {
    if (oldAct == CANCELLED)
        return newAct;
    if (newAct == CANCELLED)
        return CANCELLED;
    if (oldAct == newAct && (oldAct==UPDATE || oldAct==DELETE))
        return oldAct;
    if (newAct == DELETE) {
        if (oldAct == UPDATE)
            return DELETE;
        else return CANCELLED;
    }
    if (((newAct == ADD_DIRECTORY || newAct == ADD_FILE) &&
         (oldAct == ADD_DIRECTORY || oldAct == ADD_FILE) )//combination not valid:
                                                            // a file or directory cannot be added twice
        || (oldAct == DELETE && newAct == UPDATE) //after a deletion a file cannot be updated anymore
        || (oldAct == UPDATE)) //an update cannot preceed an ADD_*
        //should not go there
        throw std::logic_error("Impossible combination of action to be updated");

    if (oldAct == ADD_DIRECTORY || oldAct == ADD_FILE)
        return oldAct;

    //only possible combination is DELETE -> ADD (it is an update)
    return UPDATE;
}


