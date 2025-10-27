#ifndef FILEMETRIC_HPP
#define FILEMETRIC_HPP
using namespace std;
#include <string>
class File;

struct FileMetric{
    string filename;
    File* file;
    int value;
    FileMetric(): filename(""), file(nullptr), value(0){};
    FileMetric(const string& name, File* f, int v): filename(name), file(f), value(v){};
    bool operator>(const FileMetric& other) const{
        if (value != other.value) {
            return value > other.value;
        }
        return filename < other.filename;
    }
};

#endif