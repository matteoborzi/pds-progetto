#include "JobQueue.h"

#define MAX_SIZE 100

Action getAction(Action oldAct, Action newAct);

void JobQueue::add(std::string path, Action act) {
    std::unique_lock l{m};
    if(!to_send.count(path)){
        full.wait(l, [this]{return queue.size() + sent.size() < MAX_SIZE; });
        queue.push(path);
        to_send[path]=act;
        empty.notify_one();
    }else{
        to_send[path] = getAction(to_send[path], act);
    }
}

Job JobQueue::getLastAndSetSent() {
    std::unique_lock l{m};
    Action a;
    std::string path;
    do{
        empty.wait(l, [this]{return !queue.empty(); });
        path= queue.front();
        queue.pop();
        a= to_send[path];
        to_send.erase(path);
        full.notify_one();
    }while(a==CANCELLED);

    sent[path]=a;
    return Job{path, a};
}

void JobQueue::setConcluded(std::string &path) {
    std::unique_lock l{m};
    if(!sent.count(path))
        throw std::logic_error("No action was pending for "+path);
    sent.erase(path);
    full.notify_one();
}

void JobQueue::retry(std::string &path) {
    std::unique_lock l{m};
    if(!sent.count(path))
        throw std::logic_error("No action was pending for "+path);

    if(!to_send.count(path)) {
        to_send[path] = sent[path];
        queue.emplace(path);
    }else{
        to_send[path] = getAction(sent[path], to_send[path]);
    }

    sent.erase(path);
    full.notify_one();
}

Action getAction(Action oldAct, Action newAct) {
    //TODO implement
    return UPDATE;
}


