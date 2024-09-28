#include <iostream>
#include "theclass.h"
using namespace std; 








int main() 
{  
  
Displaybootup startup;
Processing creation;
startup.startingUp();
cout<< "Operating system is ready to be used\n";
Displaybootup password;
password.loginAuthentication();
creation.managingProcesses();

return 0;
  
};