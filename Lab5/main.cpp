#include <iostream>
#include <map>
using namespace std;
class Process{
public:

};


class TaskArrival{
    map<int,Process*> arrivalTime;

public:
    Process* getProcess(int time){
        return arrivalTime[time];
    }

    void addProcess(int time, Process *process){
        arrivalTime[time] = process;
    }

};


void defineTasks(TaskArrival * taskArrival){



}

#define SIMULATION_TIME 1000


int main() {
    TaskArrival *taskArrival = new TaskArrival();
    defineTasks(taskArrival);
    int worldTime = 0;
    for (int i = 0; i<SIMULATION_TIME; i++){

    }
    return 0;
}

void defineTasks() {

}
