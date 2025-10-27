#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <string>
#include <vector>
#include <ctime>
using namespace std;

struct TreeNode {
    int version_id;
    string content;
    string message;
    TreeNode* parent;
    time_t created_timestamp; 
    time_t snapshot_timestamp=-1;
    vector<TreeNode*> children;

    TreeNode(int i, string s, TreeNode* t=nullptr, string m=""): version_id(i), content(s), message(m), parent(t) {
        created_timestamp = time(nullptr);
    }
}; 
#endif