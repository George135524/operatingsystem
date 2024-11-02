#pragma once
#include <iostream>
#include <string>
#include<vector>
#include <queue>
using namespace std;
struct theProcess
{
string theName;
vector<int>Cpuburst;
vector<int>Io;
int currentBurstIndex = 0;


};
class Displaybootup
{
public:

void startingUp()
{
  
  cout<<"Setting up hardware" <<endl;
  cout<< "preparing bootloader"<<endl;
  cout<< "Setting up Bios"<<endl;
  cout<<"preparing the kernel"<<endl<<".\n"<<".\n"<<".\n";

}
void loginAuthentication()
 {
string password;

   do{
     cout<<"Enter the password"<<endl;
     cin>> password;
     if(password !="yes23"){
     cout<< "access denied try again"<<endl; 
     }
     else
     {
       cout<<"Welcome back user"<<endl;
     }
   }while(password != "yes23");

 }
};

class Processing {
public:
const int maxProcesses = 10;
string word;
queue<theProcess> readyQueue;
queue<theProcess> waitingQueue;

void create(queue<theProcess>& readyqueue,int& processCount,string processes[]){
  string processName;
  cout << "Enter the name of the process: ";
  cin >> processName;
  //this is for creating the process
  theProcess N= {processName,{},{}};
  N.theName=processName;
  int totalburst= rand() % 9 +1;
  for (int i = 0; i < totalburst; ++i)
  {
    N.Cpuburst.push_back(rand() % 4 + 1); // the time of a burst 
    N.Io.push_back(rand()% 2+1);// this represents the time of a IO burst
  }
  readyqueue.push(N);
  processes[processCount] = processName;
  processCount++;
  cout << "Process '" << processName << "' successfully created.\n";

  if (processCount >= maxProcesses) {
    cout << "Maximum number of processes reached.\n";
    return;
  }

}

void terminate(string processes[], int& processCount)
{
  string processName;
  cout << "Enter the name of the process to terminate: ";
  cin >> processName;

  int processIndex = -1;
  for (int i = 0; i < processCount; i++){
    if (processes[i] == processName){
      processIndex = i;
      break;
    }
  }
  if (processIndex != -1){
    for (int i = processIndex; i < processCount - 1; i++){
      processes[i] = processes[i + 1];
    }
    processCount--;
    cout << "Process '" << processName << "' successfully terminated.\n";
  }else{
    cout << "Process '" << processName << "' not found.\n";
  }

  if (processCount == 0) {
    cout << "No processes running.\n";
    return;
  }

}

void FCFSexecution(){
  int cycle = 0;
  while(!readyQueue.empty() || !waitingQueue.empty()) {
    theWaitingQueue();

    if(!readyQueue.empty()){
      theProcess &currentProcess = readyQueue.front();
      cout << "Cycle " << cycle << ": Running process '" << currentProcess.theName << "'\n";

      currentProcess.Cpuburst[currentProcess.currentBurstIndex]--;
      
      if(currentProcess.Cpuburst[currentProcess.currentBurstIndex] == 0){
        currentProcess.currentBurstIndex++;

        if(currentProcess.currentBurstIndex < currentProcess.Cpuburst.size()){
          waitingQueue.push(currentProcess);
          readyQueue.pop();
          
        }else {
          cout << "Process '" << currentProcess.theName << "' finished." << endl;
          readyQueue.pop();
        }
      }
    }
    cycle++;
  }
  cout << "All processes finished." << endl;
}

void theWaitingQueue(){
  int waitingQueueSize = waitingQueue.size();
  for (int i=0; i<waitingQueueSize; i++){
    theProcess &currentProcess = waitingQueue.front();
    waitingQueue.pop();

    currentProcess.Io[currentProcess.currentBurstIndex -1]--;

    if(currentProcess.Io[currentProcess.currentBurstIndex -1] == 0){
      readyQueue.push(currentProcess);
    }else {
      waitingQueue.push(currentProcess);
    }
  }
}

void managingProcesses()
  {
  string process[maxProcesses];
  int processCount = 0;
  int choice;

  do{
    cout << "\nProcess Management Menu\n";
    cout << "1. Create a process\n";
    cout << "2. Terminate a process\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    

      switch(choice){
        case 1:
          create(readyQueue, processCount, process);
          break;
        case 2:
          terminate(process, processCount);
          break;
        case 3:
          FCFSexecution();
        break;
        case 4:
          cout << "Exiting the program.\n";
          break;
        default:
          cout << "Invalid choice. Please try again.\n";
      }
   }while (choice != 4);
  }
};
