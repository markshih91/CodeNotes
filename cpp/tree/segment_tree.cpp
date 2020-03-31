#include <iostream>
#include <vector>

using namespace std;

// nums是原数组
// value是分段和构成的线段树
// pos是value中存放nums的区间[left, right]的和的下标
// left和right是nums起止坐标
void build_segment_tree(vector<int> &value, vector<int> &nums, int pos, int left, int right){
    if (left == right){
        value[pos] = nums[left];
        return;
    }
    int mid = (left + right) / 2;
    build_segment_tree(value, nums, pos * 2 + 1, left, mid);
    build_segment_tree(value, nums, pos * 2 + 2, mid + 1, right);
    value[pos] = value[pos * 2 + 1] + value[pos * 2 + 2];
}

// nums是原数组
// value是分段和构成的线段树
// pos是value中存放nums的区间[left, right]的和的下标
// layer是层数，用于辅助打印信息"--"
void print_segment_tree(vector<int> &value, int pos, int left, int right, int layer){
    for (int i = 0; i < layer; i++){
        printf("--");
    }
    printf("[%d, %d], value: %d\n", &left, &right, &value[pos]);
    if (left == right){
        return;
    }
    int mid = (left + right) / 2;
    print_segment_tree(value, pos * 2 + 1, left, mid, layer + 1);
    print_segment_tree(value, pos * 2 + 2, mid + 1, right, layer + 1);
}

// 求[qleft, qright]区间内的和
// value是线段树
// pos是value中存放原数组的区间[left, right]的和的下标
// left和right是原数组起止坐标
// qleft和qright是需要求和的区间
int sum_range_segment_tree(vector<int> &value, int pos, int left, int right, int qleft, int qright){
    // [qleft, qright]与[left, right]没有交集则返回0
    if (qright < left || qleft > right){
        return 0;
    }
    // [left, right]被[qleft, qright]覆盖，则返回区间[left, right]内的和，否则继续二分，分出的区间最终把[qleft, qright]全覆盖得出最终和
    if (qleft <= left && qright >= right){
        return value[pos];
    }
    int mid = (left + right) / 2;
    return sum_range_segment_tree(value, pos * 2 + 1, left, mid, qleft, qright) + 
    sum_range_segment_tree(value, pos * 2 + 2, mid + 1, right, qleft, qright);

}

// 非递归方式：原数组的某个值改变之后，更新线段树value
// value是线段树
// pos是value中存放原数组的区间[left, right]的和的下标
// left和right是原数组起止坐标
// index是原数组更新值的下标
// new_value时原数组更新的值
void update_segment_tree_none_recur(vector<int> &value, int pos, int left, int right, int index, int new_value){
    vector<int> pos_stack;
    while (left < right){
        pos_stack.push_back(pos);
        int mid = (left + right) / 2;
        if (index <= mid){
            right = mid;
            pos = pos * 2 + 1;
        }else
        {
            left = mid + 1;
            pos = pos * 2 + 2;
        }
    }
    int old_value = value[pos];
    value[pos] = new_value;
    for (int i = 0; i < pos_stack.size(); i++){
        value[pos_stack[i]] += new_value - old_value;
    }
}

// 递归方式：原数组的某个值改变之后，更新线段树value
// value是线段树
// pos是value中存放原数组的区间[left, right]的和的下标
// left和right是原数组起止坐标
// index是原数组更新值的下标
// new_value时原数组更新的值
void update_segment_tree_recur(vector<int> &value, int pos, int left, int right, int index, int new_value){
    if (left == index && right == index){
        value[pos] = new_value;
        return;
    }
    int mid = (left + right) / 2;
    if (index <= mid){
        update_segment_tree_recur(value, pos * 2 + 1, left, mid, index, new_value);
    }else{
        update_segment_tree_recur(value, pos * 2 + 2, mid + 1, right, index, new_value);
    }
    value[pos] = value[pos * 2 + 1] + value[pos * 2 + 2];
}