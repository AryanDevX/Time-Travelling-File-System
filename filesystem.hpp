#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include "hashmap.hpp"
#include "heap.hpp"
#include "file.hpp"
#include "filemetric.hpp"
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class FileSystem{
private:
    HashMap<string, File*> allFiles;
    Heap<FileMetric> recent_files;
    Heap<FileMetric> biggest_trees;

public:
    FileSystem();
    ~FileSystem();
    void createFile(const string& filename);
    void readContent(const string& filename);
    void insertContent(const string& filename, const string& content);
    void updateContent(const string& filename, const string& content);
    void convertSnapshot(const string& filename, const string& message);
    void versionRollback(const string& filename, const int& id);
    void readHistory(const string& filename);
    void showRecentFiles(int num);
    void showBiggestTrees(int num);
};

#endif