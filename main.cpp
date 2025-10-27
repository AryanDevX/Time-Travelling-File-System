#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "FileSystem.hpp"
using namespace std;

int main(){
    FileSystem fileSystem;
    string command_line;
    string command;
    string filename;
    string contentOrMessage;
    int versionId;
    int num;
    cout << "Time-Travelling File System CLI" << endl;
    cout << "Enter a command (type 'EXIT' to quit)" << endl;
    while(getline(cin, command_line)){
        if(command_line == "EXIT"){
            break;
        }
        stringstream ss(command_line);
        if (!(ss >> command)) {
            cout << "Error: Unknown command." << endl;
            continue;
        }
        if(command == "CREATE"){
            if(ss >> filename){
                string extra;
                if(ss >> extra){
                    cout << "Error: CREATE command take only one argument (filename)." << endl;
                }
                else{
                    fileSystem.createFile(filename);
                }
            }        
            else{
                cout << "No filename provided." << endl;
            }
        }
        else if(command == "READ"){
            if(ss >> filename){
                string extra;
                if(ss >> extra){
                    cout << "Error: READ command take only one argument (filename)." << endl;
                }
                else{
                    fileSystem.readContent(filename);
                }
            }        
            else{
                cout << "No filename provided." << endl;
            }
        }
        else if(command == "INSERT"){
            if(ss >> filename){
                getline(ss, contentOrMessage);
                if(contentOrMessage!=""){
                    contentOrMessage.erase(0,1);
                }
                fileSystem.insertContent(filename, contentOrMessage);
            }        
            else{
                cout << "No filename provided." << endl;
            }
        }
        else if(command == "UPDATE"){
            if(ss >> filename){
                getline(ss, contentOrMessage);
                if(contentOrMessage!=""){
                    contentOrMessage.erase(0,1);
                }
                fileSystem.updateContent(filename, contentOrMessage);
            }        
            else{
                cout << "No filename provided." << endl;
            }
        }
        else if(command == "SNAPSHOT"){
            if(ss >> filename){
                contentOrMessage="";
                getline(ss, contentOrMessage);
                fileSystem.convertSnapshot(filename, contentOrMessage);
            }        
            else{
                cout << "No filename provided." << endl;
            }
        }
        else if(command == "ROLLBACK"){
            if(ss >> filename){
                if(ss >> versionId){
                    fileSystem.versionRollback(filename, versionId);
                }
                else{
                    fileSystem.versionRollback(filename, -1);
                }
            }        
            else{
                cout << "No filename provided." << endl;
            }
        }
        else if(command == "HISTORY"){
            if(ss >> filename){
                fileSystem.readHistory(filename);
            }        
            else{
                cout << "No filename provided." << endl;
            }
        }
        else if (command == "RECENT_FILES") {
            if(ss >> num){
                if(num<0){
                    cout << "Error: Invalid number of entries." << endl;
                }
                else{
                    fileSystem.showRecentFiles(num);
                }
            }        
            else{
                cout << "Error: Number of entries not specified." << endl;
            }
        }
        else if (command == "BIGGEST_TREES") {
            if(ss >> num){
                if(num<0){
                    cout << "Error: Invalid number of entries." << endl;
                }
                else{
                    fileSystem.showBiggestTrees(num);
                }
            }        
            else{
                cout << "Error: Number of entries not specified." << endl;
            }
        } 
        else {
            cout << "Error: Unknown command." << endl;
        }
    }
    return 0;
}