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



public:
    int getPriority() const {
        return priority;
    }

    int getArrivalTime(){
        return  this->arrivalTime;
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



    int execute(int currentTime, int time){
        this->burstTime = this->burstTime - time;
        return -(time);
    }

    bool done(){
        return this->burstTime<=0;
    }

    string getName(){
        return this->name;
    }

    void execute(int currentTime){
        this->startTime = (this->startTime == -1) ? currentTime : this->startTime;
        this->burstTime = 0;
    }


};


class TaskArrival {
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

void defineTasks(TaskArrival *taskArrival) {

    auto* p1 = new Process(13,3,"P1",2);
    auto* p2 = new Process(1,1,"P2",0);
    auto* p3 = new Process(2,3,"P3",1);
    auto* p4 = new Process(16,4,"P4",3);
    auto* p5 = new Process(7,2,"P5",5);

    taskArrival->addProcess(2,p1);
    taskArrival->addProcess(0,p2);
    taskArrival->addProcess(1,p3);
    taskArrival->addProcess(3,p4);
    taskArrival->addProcess(7,p5);
}

#define SIMULATION_TIME 1000

queue <Process*> readyQueue;
int worldTime = 0;


int main() {
    auto  *taskArrival = new TaskArrival();
    defineTasks(taskArrival);

    for ( worldTime = 0; worldTime < SIMULATION_TIME; worldTime++) {
        auto processes =taskArrival->getProcess(worldTime);

        while(!processes.empty()){
            auto *process = processes.front();
         //   if(*process==nullptr) continue;
            readyQueue.push(process);
            processes.pop();

        }
        executeProcess();



    }
    return 0;
}

void executeProcess() {
    if(readyQueue.empty())
        return;
    auto process = readyQueue.front();
    readyQueue.pop();
    if(process != nullptr)
    {cout<<" --> ";
    process->execute(worldTime);
    if(process->done()) cout<<process->getName();}
}

