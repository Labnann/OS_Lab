//PS NP

#include <iostream>
#include <map>
#include <queue>


using namespace std;

class Process {
private:
    int burstTime;
    int priority;
    string name;
    int startTime = -1;
    int arrivalTime;
    int lastTime = 0;
    int waitingTime = 0;


private:


    void work(int currentTime) {
        int timePassed = currentTime - lastTime + 1;
        this->burstTime--;
        this->lastTime += timePassed;
    }


public:
    int getPriority() const {
        return priority;
    }

    int getArrivalTime() {
        return this->arrivalTime;
    }

    Process(int burstTime, int priority, string name, int arrivalTime) {
        this->burstTime = burstTime;
        this->priority = priority;
        this->name = name;
        this->arrivalTime = arrivalTime;
    }

    int getBurstTime() const {
        return this->burstTime;
    }


    int getFinishTime() {
        return lastTime;
    }


    int getStartTime() const {
        return this->startTime;
    }

    int getResponseTime() {
        return startTime - arrivalTime;
    }

    int getWaitingTime() {
        return startTime - arrivalTime;
    }


    bool done() {
        return this->burstTime <= 0;
    }

    string getName() {
        return this->name;
    }


    void execute(int currentTime) {
        this->startTime = (this->startTime == -1) ? currentTime : this->startTime;
        work(currentTime);
    }


};


class JobQueue {
    map<int, queue<Process *>> processQueue;

public:
    auto getProcess(int time) {
        return processQueue[time];
    }

    void addProcess(int time, Process *process) {
        processQueue[time].push(process);
    }

};


void executeProcess();

void propagateToReadyQueue(queue<Process *> &processes);

void printStatus();

void defineTasks(JobQueue *taskArrival) {

    auto *p1 = new Process(13, 3, "P1", 2);
    taskArrival->addProcess(2, p1);

    auto *p2 = new Process(1, 1, "P2", 0);
    taskArrival->addProcess(0, p2);

    auto *p3 = new Process(2, 3, "P3", 1);
    taskArrival->addProcess(1, p3);

    auto *p4 = new Process(16, 4, "P4", 3);
    taskArrival->addProcess(3, p4);

    auto *p5 = new Process(7, 2, "P5", 5);
    taskArrival->addProcess(7, p5);

}

struct HighPriority {
    bool operator()(const Process *lhs, const Process *rhs) const {
        return lhs->getPriority() > rhs->getPriority();
    }
};


#define SIMULATION_TIME 1000

priority_queue<Process *, vector<Process *>, HighPriority> readyQueue;
queue<Process *> finishedQueue;
auto *pJobQueue = new JobQueue();


int worldTime = 0;


int main() {

    defineTasks(pJobQueue);

    for (worldTime = 0; worldTime < SIMULATION_TIME; worldTime++) {
        auto processes = pJobQueue->getProcess(worldTime);
        propagateToReadyQueue(processes);
        executeProcess();
    }

    printStatus();

    return 0;
}

void printStatus() {
    while (!finishedQueue.empty()) {
        auto finished = finishedQueue.front();
        finishedQueue.pop();

        cout << "\n";
        cout << "Process " << finished->getName() << ":\n";
        cout << "Start Time " << finished->getStartTime() << ":\n";
        cout << "Finish Time " << finished->getFinishTime() << ":\n";
        cout << "Response Time " << finished->getResponseTime() << ":\n";
        cout << "Waiting Time " << finished->getWaitingTime() << ":\n";

    }
}

void propagateToReadyQueue(queue<Process *> &processes) {
    while (!processes.empty()) {
        auto *process = processes.front();
        readyQueue.push(process);
        processes.pop();

    }
}

Process *currentProcess = nullptr;

void executeProcess() {
    if (readyQueue.empty() && currentProcess== nullptr)
        return;
    if (currentProcess == nullptr) {
        currentProcess = readyQueue.top();
        readyQueue.pop();
    }

    auto process = currentProcess;
    process->execute(worldTime);
    if (process->done()) {
        cout << "-->" << process->getName();
        finishedQueue.push(process);
        currentProcess = nullptr;
    }
}

