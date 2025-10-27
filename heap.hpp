#ifndef HEAP_HPP
#define HEAP_HPP

#include "hashmap.hpp"
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

template <typename V>
class Heap{
private:
    vector<V> heap;
    HashMap<string, int> idxMap;

    void heapifyDown(int i){
        int largest = i;
        int left = 2*i+1;
        int right = 2*i+2;
        int n = heap.size();

        if(left < n && heap[left] > heap[largest]){
            largest = left;
        }
        if(right < n && heap[right] > heap[largest]){
            largest = right;
        }

        if(largest != i){
            swap(heap[i], heap[largest]);
            idxMap.insert(heap[i].filename, i);
            idxMap.insert(heap[largest].filename, largest);
            heapifyDown(largest);
        }
    }

    void heapifyUp(int i){
        while(i > 0){
            int parent = (i-1)/2;
            if(heap[i] > heap[parent]){
                swap(heap[i], heap[parent]);
                idxMap.insert(heap[i].filename, i);
                idxMap.insert(heap[parent].filename, parent);
                i = parent;
            }
            else{
                break;
            }
        }
    }

public:
    void insert(V val){
        heap.push_back(val);
        int idx = heap.size() - 1;
        idxMap.insert(val.filename, idx);
        heapifyUp(idx);
    }

    V top(){
        if(heap.empty()){
            throw runtime_error("Heap is empty");
        }
        return heap[0];
    }

    void pop(){
        if(heap.empty()) return;

        string filename = heap[0].filename;
        swap(heap[0], heap[heap.size()-1]);
        idxMap.remove(filename);
        heap.pop_back();

        if(!heap.empty()){
            idxMap.insert(heap[0].filename, 0);
            heapifyDown(0);
        }
    }

    bool empty(){
        return heap.empty();
    }

    int size(){
        return heap.size();
    }

    void update(const string& filename, int newValue) {
        int idx = -1;
        if (idxMap.get(filename, idx)) {
            int oldValue = heap[idx].value;
            heap[idx].value = newValue;

            if (newValue > oldValue) {
                heapifyUp(idx);
            } else if (newValue < oldValue) {
                heapifyDown(idx);
            }
        }
    }
};

#endif