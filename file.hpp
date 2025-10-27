
#ifndef FILE_HPP
#define FILE_HPP
#include "treenode.hpp"
#include "hashmap.hpp"
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class File {
private:
    TreeNode* root;
    TreeNode* active_version;
    HashMap<int, TreeNode*> version_map;
    int total_versions;
    time_t lastModified;

public:
    File();
    ~File();
    void read();
    void modifyContent(const string& newContent, bool isAppend = false);
    void insert(string s);
    void update(string s);
    void snapshot(string c);
    void rollback(int id = -1);
    void history();
    int getTotalVersions();
    time_t getLastModified();
};

#endif