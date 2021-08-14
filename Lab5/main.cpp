#include <iostream>
#include <map>
#include <queue>

using namespace std;

class Process {
private:
    int burstTime;
    int priority;
    string name;



public:
    int getPriority() const {
        return priority;
    }

    Process(int burstTime, int priority, string name) {
        this->burstTime = burstTime;
        this->priority = priority;
        this->name = name;
    }

    int getBurstTime() const {
        return this->burstTime;
    }



    int execute(int time){
        this->burstTime = this->burstTime - time;
        return -(time);
    }

    bool done(){
        return this->burstTime<=0;
    }

    string getName(){
        return this->name;
    }

    void execute(){
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


void defineTasks(TaskArrival *taskArrival) {

    auto* p1 = new Process(13,3,"P1");
    auto* p2 = new Process(1,1,"P2");
    auto* p3 = new Process(2,3,"P3");
    auto* p4 = new Process(16,4,"P4");
    auto* p5 = new Process(7,2,"P5");

    taskArrival->addProcess(2,p1);
    taskArrival->addProcess(0,p2);
    taskArrival->addProcess(1,p3);
    taskArrival->addProcess(3,p4);
    taskArrival->addProcess(7,p5);
}

#define SIMULATION_TIME 1000


int main() {
    auto  *taskArrival = new TaskArrival();
    defineTasks(taskArrival);

    for (int worldTime = 0; worldTime < SIMULATION_TIME; worldTime++) {
        auto processes =taskArrival->getProcess(worldTime);

        while(!processes.empty()){
            auto *process = processes.front();
            processes.pop();

            if(process== nullptr)
                continue;
            cout<<" --> ";
            process->execute();
            if(process->done()) cout<<process->getName();
        }



    }
    return 0;
}

