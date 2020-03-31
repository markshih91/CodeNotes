#include <iostream>
#include <vector>

using namespace std;

class DisjointSet{
public:
    DisjointSet(int n){
        for (int i = 0; i < n; i++){
            _id.push_back(i);
            _size.push_back(1);
        }
        _count = n;
    }

    int find(int p){

        while(p != _id[p]){
            _id[p] = _id[_id[p]];
            p = _id[p];
        }
        return p;
    }

    void union_(int p, int q){
        int i = find(p);
        int j = find(q);
        if (i == j){
            return;
        }
        if (_size[i] < _size[j]){
            _id[i] = j;
            _size[j] += _size[i];
        }else{
            _id[j] = i;
            _size[i] += _size[j];
        }
        _count--;
    }

    int count(){
        return _count;
    }

private:
    vector<int> _id;
    vector<int> _size;
    int _count;

};