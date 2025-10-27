#include <iostream>
#include "file.hpp"
using namespace std;

File::File() {
    root = new TreeNode(0, "", nullptr, "Initial Snapshot");
    root->snapshot_timestamp = time(nullptr);
    active_version = root;
    version_map.insert(0, root);
    total_versions = 1;
    lastModified = time(nullptr);
}

File::~File() {
    vector<TreeNode*> nodesToDelete;
    if (root) {
        nodesToDelete.push_back(root);
    }
    size_t head = 0;
    while (head < nodesToDelete.size()) {
        TreeNode* curr = nodesToDelete[head++];
        for (TreeNode* child : curr->children) {
            nodesToDelete.push_back(child);
        }
        delete curr;
    }
}

void File::read() {
    cout << active_version->content << endl;
}

void File::modifyContent(const string& newContent, bool isAppend) {
    if (active_version->snapshot_timestamp==-1) {
        if (isAppend) {
            active_version->content += newContent;
        } else {
            active_version->content = newContent;
        }
        lastModified = time(nullptr);
    } else {
        string content = isAppend ? active_version->content + newContent : newContent;
        TreeNode* newNode = new TreeNode(total_versions, content, active_version, "");
        active_version->children.push_back(newNode);
        active_version = newNode;
        version_map.insert(total_versions, newNode);
        total_versions++;
        lastModified = time(nullptr);
    }
}

void File::insert(string s) {
    if(!active_version->content.empty()){
        s=" " + s;
    }
    modifyContent(s, true);
}

void File::update(string s) {
    modifyContent(s, false);
}

void File::snapshot(string c) {
    active_version->message = c;
    if(active_version->snapshot_timestamp!=-1){
        cout << "Already a snapshot, so only the message has been updated." << endl;
    }
    else{
        cout << "Converted to Snapshot." << endl;
        active_version->snapshot_timestamp = time(nullptr);
    }
}

void File::rollback(int id) {
    if (id == -1) {
        if (active_version->parent) {
            active_version = active_version->parent;
            cout << "Successfully rollbacked to parent." << endl;
        }
        else{
            cout << "No parent to rollback to." << endl;
        }
    } else {
        TreeNode* versionId = nullptr;
        if (version_map.get(id, versionId)) {
            active_version = versionId;
            cout << "Succesfully rollbacked to Version Id: " << id << endl;
        } else {
            cout << "Error: Version ID " << id << " not found." << endl;
        }
    }
}

void File::history() {
    vector<TreeNode*> snapshots;
    TreeNode* current = active_version;

    while (current != nullptr) {
        if (current->snapshot_timestamp != -1) {
            snapshots.push_back(current);
        }
        current = current->parent;
    }
    for (int i = snapshots.size() - 1; i >= 0; --i) {
        TreeNode* id = snapshots[i];
        cout << "ID: " << id->version_id
             << ", Timestamp Created: " << ctime(&id->created_timestamp)
             << ", Timestamp Snapshoted: " << ctime(&id->snapshot_timestamp)
             << ", Message: " << id->message << endl;
    }
    cout << "Printed all the history" << endl;
}

int File::getTotalVersions() {
    return total_versions;
}

time_t File::getLastModified() {
    return lastModified;
}