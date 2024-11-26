#pragma once
#include <iostream>
#include <string>
#include<vector>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

struct Ptable{
int virtual_memory;
int physical_memory;

};
struct theProcess {
  string theName;
  vector<int>Cpuburst;
  vector<int>Io;
  int currentBurstIndex = 0;
  vector<Ptable>pageT;

};

class Displaybootup {
public:

void startingUp(){
  
  cout<<"Setting up hardware" <<endl;
  cout<< "preparing bootloader"<<endl;
  cout<< "Setting up Bios"<<endl;
  cout<<"preparing the kernel......."<< endl <<endl;

}
void loginAuthentication()
 {
string password;

   do{
     cout<<"Enter the password"<<endl;
     cin>> password;
     if(password !="yes23"){
        cout<< "access denied try again"<<endl; 
     }else{
        cout<<"Welcome back user"<<endl;
     }
    }while(password != "yes23");
  }
};



class Processing {
public:
const int maxProcesses = 10;
//string word;
queue<theProcess> readyQueue;
queue<theProcess> waitingQueue;

void create(queue<theProcess>& readyqueue,int& processCount,string processes[]){
  if (processCount >= maxProcesses) {
    cout << "Maximum number of processes reached." << endl;
    return;
  }
  
  string processName;
  cout << "Enter the name of the process: ";
  cin >> processName;
  //this is for creating the process
  theProcess N = {processName,{},{}};
  int totalburst= (processCount + 1) % 8 + 1;// will determine the total number of bursts
  for (int i = 0; i < totalburst; ++i)
  {
    N.Cpuburst.push_back((processCount + i + 2) % 4 + 1); // the values that are randomly generated will be put in the cpu burst vector
    N.Io.push_back((processCount + i + 3) % 2 + 1);// the same as the cpu burst
  }
    int pages = 5;
    for(int i=0;i<pages;i++){
        Ptable entry = {i,(processCount+i) % 8};
        N.pageT.push_back(entry);
        
    }
    
  readyqueue.push(N);
  processes[processCount] = processName;
  processCount++;
  cout << "Process '" << processName << "' successfully created.\n";
}

int translateAddress(int virtualAddress,const vector<Ptable>&pageT,int pageS){
    int pageN = virtualAddress/pageS;
    int offset = virtualAddress % pageS;

    for (const auto& entry : pageT){
        if (entry.virtual_memory == pageN){
            int physicalFrame = entry.physical_memory;
            int physicalAddress = (physicalFrame * pageS) + offset;
            cout << "Translated virtual address " << virtualAddress << " , Page: " << pageN << ", Offset: " << offset << ", Physical address: " << physicalAddress << endl;
            return physicalAddress;
        }
    }
    cout << "Page fault: Virtual Page " << pageN << " not found int the page table. \n";
    return -1;
}

// this to terminate process
void terminate(queue<theProcess>& readyQueue, queue<theProcess>& waitingQueue, string processes[], int& processCount){
  string processName;
  cout << "Enter the name of the process to terminate: ";
  cin >> processName;

  removeProcessFromQueue(readyQueue, processName);
  removeProcessFromQueue(waitingQueue, processName);
  
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
    cout << "Process '" << processName << "' not found.\n";
  }else{
    cout << "Process '" << processName << "' successfully terminated.\n";
  }
}
// this to do the FCFs execution
void FCFSexecution(){
  int cycle = 0;
   int pageS=4096;
  while(!readyQueue.empty() || !waitingQueue.empty()) {
      theWaitingQueue(); 

      if(!readyQueue.empty()) {
          theProcess currentProcess = readyQueue.front();
          readyQueue.pop();
          cout << "Cycle '" << cycle << "' Process '" << currentProcess.theName << "' is running." << endl << endl;

          if (currentProcess.currentBurstIndex < currentProcess.Cpuburst.size()) {
             
              int virtual_address = rand()% 9000;
              int physicalAddress = translateAddress(virtual_address,currentProcess.pageT,pageS);
              if(physicalAddress!=-1){
              cout<< "The Vitural address should be ' "<< virtual_address<< " ' then it translates to: "<< physicalAddress << endl << endl;
              }
              currentProcess.Cpuburst[currentProcess.currentBurstIndex]--;  
              if (currentProcess.Cpuburst[currentProcess.currentBurstIndex] == 0) {
                  currentProcess.currentBurstIndex++;
                  if(currentProcess.currentBurstIndex < currentProcess.Io.size()) {
                      waitingQueue.push(currentProcess);  
                  } else {
                      cout << "\nProcess '" << currentProcess.theName << "' finished." << endl;  
                  }
              } else {
                  readyQueue.push(currentProcess);  
              }
          }
      }
      cycle++;
  }
  cout << "\nAll processes finished."  << endl;
}
//this is for the SJF execution 
void SJFexecution() {
  int cycle = 0;
    int pageS= 4096;
  while(!readyQueue.empty() || !waitingQueue.empty()) {
      theWaitingQueue(); 

      vector<theProcess> theVector;
      while(!readyQueue.empty()) {
          theVector.push_back(readyQueue.front());
          readyQueue.pop();
      }
      sort(theVector.begin(), theVector.end(), [](const theProcess& a, const theProcess& b) {
          return a.Cpuburst[a.currentBurstIndex] < b.Cpuburst[b.currentBurstIndex]; 
      });

      for (auto& p : theVector) {
          readyQueue.push(p);
      }

      if (!readyQueue.empty()) {
          theProcess currentProcess = readyQueue.front();
          readyQueue.pop();

          cout << "Cycle '" << cycle << "' Process '" << currentProcess.theName << "' is running." << endl << endl;
          currentProcess.Cpuburst[currentProcess.currentBurstIndex]--;

          if (currentProcess.Cpuburst[currentProcess.currentBurstIndex] == 0) {
              currentProcess.currentBurstIndex++;
              if(currentProcess.currentBurstIndex < currentProcess.Io.size()) {
                    int virtual_address = rand()% 9000;
                    int physicalAddress = translateAddress(virtual_address,currentProcess.pageT,pageS);
                    if(physicalAddress!=-1){
                    cout<< "The Vitural address should be ' "<< virtual_address<< " ' then it translates to: "<< physicalAddress << endl << endl;
                    }
                  waitingQueue.push(currentProcess);  
              } else {
                  cout << "\nProcess '" << currentProcess.theName << "' finished." << endl;
              }
          } else {
              readyQueue.push(currentProcess); 
          }
      }
      cycle++;
  }
  cout << "\nAll processes finished." << endl;
}

//waiting queue 
void theWaitingQueue(){ 
  int waitingQueueSize = waitingQueue.size();

    for (int i = 0; i < waitingQueueSize; i++) {
        theProcess currentProcess = waitingQueue.front();
        waitingQueue.pop();

        if (currentProcess.currentBurstIndex < currentProcess.Io.size()) {
            currentProcess.Io[currentProcess.currentBurstIndex]--;
            if (currentProcess.Io[currentProcess.currentBurstIndex] == 0) {
                readyQueue.push(currentProcess);
            } else {
                waitingQueue.push(currentProcess);
            }
        }
    }
}

void managingProcesses(int& processCount){
  string processes[maxProcesses];
  int choice;

    do{
      cout << "\nProcess Management Menu\n";
      cout << "1. Create a process\n";
      cout << "2. Terminate a process\n";
      cout << "3. FCFS schedule\n";
      cout << "4. SJF schedule\n";
      cout << "5. Exit\n";
      cout << "Enter your choice: ";
      cin >> choice;

      // this code below helps so words or letters are not accepted
      if (cin.fail()) {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
          cout << "Invalid input! Please enter a number between 1 and 5.\n";
          continue;
      }
    
      switch (choice){
        case 1:
          create(readyQueue, processCount, processes);
          break;
        case 2:
          terminate(readyQueue, waitingQueue, processes, processCount);
          break;
        case 3:
          cout<< "\nFCFS schedule is running: \n" << endl;
          FCFSexecution();
          break;
        case 4:
          cout<< "\nSJF schedule is running: \n" << endl;
          SJFexecution();
          break;
        case 5:
          cout << "\nExiting the program.\n";
          break;
        default:
          cout << "Invalid choice. Please try again.\n";
          break;
      }
    }while (choice != 5);
  }

private:
// This is to actually remove the process from the queue
// its private since the user doesnt have to call or see it
  void removeProcessFromQueue(queue<theProcess>& q, const string& processName) {
    int size = q.size();
    for (int i = 0; i < size; i++) {
        theProcess current = q.front();
        q.pop();
        if (current.theName != processName) {
            q.push(current);
          }
      }
  }
};
