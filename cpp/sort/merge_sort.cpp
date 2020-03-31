#include <iostream>
#include <vector>

using namespace std;

void merge_sort(vector<int> &nums, int start, int end){
    if (start >= end){
        return;
    }
    int mid = (start + end) / 2;
    merge_sort(nums, start, mid);
    merge_sort(nums, mid + 1, end);
    vector<int> tmp(nums);
    int i = start, j = mid + 1, k = start;
    while(i <= mid && j <= end){
        if (tmp[i] <= tmp[j]){
            nums[k++] = tmp[i++];
        }else{
            nums[k++] = tmp[j++];
        }
    }
    while(i <= mid){
        nums[k++] = tmp[i++];
    }
    while(j <= end){
        nums[k++] = tmp[j++];
    }
}

int main(){

    vector<int> nums = {5, 4, 3, 2, 1};
    merge_sort(nums, 0, nums.size() - 1);

    for (int i = 0; i < nums.size(); i++){
        cout << nums[i] << endl;
    }

    return 0;
}