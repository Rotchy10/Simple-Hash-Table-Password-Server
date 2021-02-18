#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <cstdlib>
#include "passserver.h"
#include <cctype>
#include <termios.h>
#include <unistd.h>

using namespace std;
void Menu();
void disableEcho();
void enableEcho();

struct termios termParam;
int lt;

int main (){

  size_t tableCapacity;
  string userInput;

  cout << "Enter preffered hash table capacity: ";
  cin >> tableCapacity;
  cin.ignore();

  PassServer myServer(tableCapacity);

  do{
    Menu();
    getline(cin,userInput);
    for(int i =0; i < userInput.size(); i++)
        userInput[i] = tolower(userInput[i]);

    if(userInput == "l"){   // Load file option ======================================
      string fileName;
      
      cout << "Enter password file name to load from: ";
      getline(cin,fileName);
      
      if(!myServer.load(fileName.c_str()))
        cout << "*****Error: Cannot open file \"" << fileName << "\"" << endl;
    }
    else if (userInput == "a"){ // Add User option ===================================
      std::pair<string,string> newUserInfo;
      
      cout << "Enter username: ";
      getline(cin,newUserInfo.first);
      
      cout << "Enter password: ";
      disableEcho();   // Disabling echo on terminal for password entry
      getline(cin,newUserInfo.second);
      enableEcho();     // Enablind echo on terminal

      if(myServer.addUser(newUserInfo)){
        cout << "\nUser \"" << newUserInfo.first << "\" added." << endl;
      }else{
        cout << "*****Error: User already exists. Could not add user." << endl;
      }
    }
    else if(userInput == "r"){  // Remove user option ================================
      string userName;
      
      cout << "Enter username: ";
      getline(cin,userName);

      if(myServer.removeUser(userName))
        cout << "\nUser \"" << userName << "\" deleted." << endl;
      else
        cout << "*****Error: User not found. Could not delete user" << endl;
    }
    else if(userInput == "c"){ // Change Password option =============================
      std::pair<string,string> userInfo;
      string newPassword;
      
      cout << "Enter username: ";
      getline(cin,userInfo.first);
      cout << "Enter password: ";

      disableEcho();        // Disabling echo on terminal for password entry
      getline(cin,userInfo.second);
      enableEcho();                 // Enabling Echo
      
      cout << "\nEnter new password: ";
                
      disableEcho();                // Disabling Echo
      getline(cin,newPassword);
      enableEcho();                 // Enabling Echo

      if(myServer.changePassword(userInfo,newPassword))
        cout << "\nPassword changed for user \""<< userInfo.first << "\"" << endl;
      else
        cout << "*****Error: Could not change user password" << endl;
    }
    else if(userInput == "f"){ // Find User option ==================================
      string userName;
      cout << "Enter username: ";
      getline(cin,userName);

      if(myServer.find(userName))
        cout << "\nUser \"" << userName << "\" found." << endl;
      else
        cout << "\nUser \"" << userName << "\" not found." << endl;
    }
    else if(userInput == "d"){ // Dumb Hashtable option ==============================
      myServer.dump();
    }
    else if(userInput == "s"){ // Size option ==============================
      cout << "Size of hashtable: " << myServer.size() << endl;
    }
    else if(userInput == "w"){  // writeToFile option ==============================
      string fileName;
      cout << "Enter password file name to write to: ";
      getline(cin,fileName);
      if(!myServer.write_to_file(fileName.c_str()))
        cout << "*****Error: Cannot open file \"" << fileName << "\"" << endl;
    }
  }while(userInput != "x");
}

void Menu(){
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
void disableEcho(){         // This function hides the echo of the terminal
  tcgetattr(lt,&termParam); // when a user keys in their entry
  termParam.c_lflag &= ~ECHO;
  tcsetattr(lt,TCSANOW,&termParam);
}
void enableEcho(){            // This function undoes what the disableEcho()
  tcgetattr(lt,&termParam);   // function does
  termParam.c_lflag |= ECHO;
  tcsetattr(lt,TCSANOW,&termParam);
}