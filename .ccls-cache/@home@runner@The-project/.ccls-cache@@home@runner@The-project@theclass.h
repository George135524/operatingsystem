#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<queue>
using namespace std;
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
string word;
const int maxProcesses = 10;
void create(string processes[], int& processCount){
  string processName;
  cout << "Enter the name of the process: ";
  cin >> processName;

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
          create(process, processCount);
          break;
        case 2:
          terminate(process, processCount);
          break;
        case 3:
          cout << "Exiting the program.\n";
          break;
        default:
          cout << "Invalid choice. Please try again.\n";
      }
   }while (choice != 3);
  }
};
