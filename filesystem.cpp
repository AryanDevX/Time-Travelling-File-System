#include <iostream>
#include <string>
#include "filemetric.hpp"
#include "file.hpp"
#include "filesystem.hpp"
#include <ctime>
#include <set>
using namespace std;

FileSystem::FileSystem(){};
FileSystem::~FileSystem(){};

void FileSystem::createFile(const string& filename){
    File* filePtr = nullptr;
    if(allFiles.get(filename, filePtr)){
        cout << "Error: File " << filename << " already exists." << endl;
    }
    else{
        File* newFile = new File();
        allFiles.insert(filename, newFile);
        FileMetric modified(filename, newFile, newFile->getLastModified());
        FileMetric biggest(filename, newFile, newFile->getTotalVersions());
        recent_files.insert(modified);
        biggest_trees.insert(biggest);
        cout << "File: " << filename << " is created successfully." << endl;
    }
}
void FileSystem::readContent(const string& filename){
    File* filePtr = nullptr;
    if(allFiles.get(filename, filePtr)){
        filePtr->read();
    }
    else{
        cout << "Error: File " << filename << " not found." << endl;
    }
}
void FileSystem::insertContent(const string& filename, const string& content){
    File* filePtr = nullptr;
    if(allFiles.get(filename, filePtr)){
        filePtr->insert(content);
        recent_files.update(filename, filePtr->getLastModified());
        biggest_trees.update(filename, filePtr->getTotalVersions());
        cout << "Content has been inserted in " << filename << endl;
    }
    else{
        cout << "Error: File " << filename << " not found." << endl;
    }
}
void FileSystem::updateContent(const string& filename, const string& content){
    File* filePtr = nullptr;
    if(allFiles.get(filename, filePtr)){
        filePtr->update(content);
        recent_files.update(filename, filePtr->getLastModified());
        biggest_trees.update(filename, filePtr->getTotalVersions());
        cout << "Content has been updated in " << filename << endl;
    }
    else{
        cout << "Error: File " << filename << " not found." << endl;
    }
}
void FileSystem::convertSnapshot(const string& filename, const string& message){
    File* filePtr = nullptr;
    if(allFiles.get(filename, filePtr)){
        filePtr->snapshot(message);
    }
    else{
        cout << "Error: File " << filename << " not found." << endl;
    }
}
void FileSystem::versionRollback(const string& filename, const int& id){
    File* filePtr = nullptr;
    if(allFiles.get(filename, filePtr)){
        filePtr->rollback(id);
    }
    else{
        cout << "Error: File " << filename << " not found." << endl;
    }
}
void FileSystem::readHistory(const string& filename){
    File* filePtr = nullptr;
    if(allFiles.get(filename, filePtr)){
        filePtr->history();
    }
    else{
        cout << "Error: File " << filename << " not found." << endl;
    }
}

void FileSystem::showRecentFiles(int num){
    Heap<FileMetric> temp = recent_files;
    cout << "Recent Files by last modified time:" << endl;

    while(num-- && !temp.empty()){
        FileMetric topMetric = temp.top();
        time_t lastModifiedtime = topMetric.file->getLastModified();
        cout << "File: " << topMetric.filename << ", Last Modified: " << ctime(&lastModifiedtime);
        temp.pop();
    }
}
void FileSystem::showBiggestTrees(int num){
    Heap<FileMetric> temp = biggest_trees;
    cout << "Biggest Trees by total versions:" << endl;
    
    while(num--&& !temp.empty()){
        FileMetric topMetric = temp.top();
        cout << "File: " << topMetric.filename << ", total versions: " << topMetric.file->getTotalVersions() << endl;
        temp.pop();
    }
}