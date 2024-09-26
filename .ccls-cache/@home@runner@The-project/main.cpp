#include <iostream>
using namespace std; 
void startingUp()
{
cout<<"Setting up hardware" <<endl;
  cout<< "preparing bootloader"<<endl;
  cout<< "Setting up Bios"<<endl;
  cout<<"preparing the kernel"<<endl<<".\n"<<".\n"<<".\n";

}
void loginAuthentication()
{
cout<< "Enter the password"<<endl;
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

int main() 
{  
  
startingUp();
  cout<< "Operating system is ready to be used";
loginAuthentication();

  
};