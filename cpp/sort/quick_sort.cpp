#include <iostream>
#include <vector>

using namespace std;

void quick_sort(vector<int> &nums, int start, int end){
    if (start >= end){
        return;
    }

    int i = start, j = end;
    int tmp = nums[start];
    bool back = true;
    while(i < j){
        if (back){
            if (nums[j] < tmp){
                nums[i] = nums[j];
                back = false;
            }else{
                j--;
            }
        }else{
            if (nums[i] > tmp){
                nums[j] = nums[i];
                back = true;
            }else{
                i++;
            }
        }
    }

    nums[i] = tmp;

    quick_sort(nums, start, i - 1);
    quick_sort(nums, i + 1, end);
}

int main(){

    vector<int> nums = {5, 4, 3, 2, 1};
    quick_sort(nums, 0, nums.size() - 1);

    for (int i = 0; i < nums.size(); i++){
        cout << nums[i] << endl;
    }

    return 0;
}