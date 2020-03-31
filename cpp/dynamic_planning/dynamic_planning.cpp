#include <iostream>
#include <vector>

using namespace std;

// 爬n层楼梯，每次上1或2个台阶，共多少种方式？
int climbStairs(int n){
    if (n <= 1){
        return 1;
    }
    vector<int> res(n);
    res[0] = 1;
    res[1] = 2;
    for (int i = 2; i < n; i++){
        res[i] = res[i - 1] + res[i - 2];
    }
    return res[n - 1];
}

// leetcode198:打家劫舍
int rob(vector<int> &nums){
    if (nums.empty()){
        return 0;
    }
    if (nums.size() == 1){
        return nums[0];
    }
    vector<int> res(nums.size());
    res[0] = nums[0];
    res[1] = nums[0] >= nums[1] ? nums[0] : nums[1];
    for (int i = 2; i < nums.size(); i++){
        res[i] = res[i - 1] >= res[i - 2] + nums[i] ? res[i - 1] : res[i - 2] + nums[i];
    }
    return res[nums.size() - 1];
}

// leetcode53：给定一个整数数组nums，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和
int maxSubArray(vector<int>& nums) {
    if (nums.empty()){
        return 0;
    }
    struct Res{
        int max; // 最大连续子序列
        int maxContainedLast; // 包含最后一个元素的最大连续子序列
        Res(){} 
        Res(int max, int maxContainedLast):max(max), maxContainedLast(maxContainedLast){}
    };
    vector<Res> res(nums.size());
    res[0] = Res(nums[0], nums[0]);
    for (int i = 1; i < nums.size(); i++){
        int maxContainedLast = res[i - 1].maxContainedLast > 0 ? res[i - 1].maxContainedLast + nums[i] : nums[i];
        int max = res[i - 1].max > maxContainedLast ? res[i - 1].max : maxContainedLast;
        res[i] = Res(max, maxContainedLast);
    }
    return res[nums.size() - 1].max;
}

// leetcode53：方法二
int maxSubArray2(vector<int>& nums) {
    if (nums.empty()){
        return 0;
    }
    // 以当前节点为最后元素的最大连续子序列
    vector<int> res(nums.size());
    res[0] = nums[0];
    int max = res[0];
    for (int i = 1; i < nums.size(); i++){
        res[i] = res[i - 1] + nums[i] > nums[i] ? res[i - 1] + nums[i] : nums[i];
        if (res[i] > max){
            max = res[i];
        }
    }
    return max;
}

// leetcode322：给定不同面额的硬币coins(从小到大排列)和一个总金额amount。
// 计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回-1
// F(n, m)表示前n种硬币凑成金额m需要的最少个数
// F(n, m) = min{F(n-1, m), F(n-1, m-coins[n-1]+1), ..., F(n-1, m-k*coins[n-1]+k)}
// F(n, 0) = 0
int coinChange(vector<int>& coins, int amount) {
    int n = coins.size();
    if(n == 0){
        return -1;
    }

    // pre表示截止到前一种硬币的各个金额所需最少硬币个数，cur表示截止到当前种类硬币的各个金额所需最少硬币个数
    vector<int> pre(amount + 1), cur(amount + 1);

    int MAX = 2147483647;
    pre[0] = 0;
    // 初始化只有第一种硬币的情况下组成各个金额需要的最少硬币个数，如果无法组成则赋值MAX
    for (int i = 1; i <= amount; i++){
        int count = i / coins[0];
        int red = i % coins[0];
        if (red == 0 && count > 0){
            pre[i] = count;
        }else{
            pre[i] = MAX;
        }
    }
    // 逐步添加硬币种类
    for (int i = 1; i < n; i++){
        cur[0] = 0;
        for (int j = 1; j <= amount; j++){
            int min = pre[j];
            int k = 1;
            while (j - k * coins[i] >= 0){
                if (pre[j - k * coins[i]] < MAX && pre[j - k * coins[i]] + k < min){
                    min = pre[j - k * coins[i]] + k;
                }
                k++;
            }
            cur[j] = min;
        }
        pre = cur;
    }
    return pre[amount] < MAX ? pre[amount] : -1;
}

// leetcode120：给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上
int minimumTotal(vector<vector<int>>& triangle) {
    if (triangle.empty()){
        return 0;
    }
    vector<int> pre(triangle.size()), cur(triangle.size());
    pre[0] = triangle[0][0];
    int min = pre[0];
    for (int i = 1; i < triangle.size(); i++){
        cur[0] = pre[0] + triangle[i][0];
        min = cur[0];
        for (int j = 1; j < i; j++){
            cur[j] = pre[j - 1] < pre[j] ? pre[j - 1] : pre[j];
            cur[j] += triangle[i][j];
            if (cur[j] < min){
                min = cur[j];
            }
        }
        cur[i] = pre[i - 1] + triangle[i][i];
        if (cur[i] < min){
            min = cur[i];
        }
        pre = cur;
    }
    return min;
}

// leetcode300：给定一个无序的整数数组，找到其中最长上升子序列的长度
int lengthOfLIS(vector<int>& nums) {
    if (nums.empty()){
        return 0;
    }
    // 包含最后元素的最长上升子序列长度
    vector<int> res(nums.size());
    res[0] = 1;
    // max存储结果
    int max = res[0];
    for (int i = 1; i < res.size(); i++){
        int j = i - 1;
        res[i] = 1;
        // 依次与前面的最长上升子序列的最后一个元素比较
        // 找出满足如下条件的子序列，1、子序列的最后一个元素比当前元素小；2、子序列是所有得出的最长上升子序列中最长的
        // 以当前元素结尾的最长子序列长度为找出的子序列长度加1
        while (j >= 0){
            if (nums[i] > nums[j] && res[j] + 1 > res[i]){
                res[i] = res[j] + 1;
            }
            j--;
        }
        if (max < res[i]){
            max = res[i];
        }
    }
    return max;
}

// leetcode64：给定一个包含非负整数的mxn网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小
int minPathSum(vector<vector<int>>& grid) {
    if (grid.size() == 0 || grid[0].size() == 0){
        return 0;
    }
    int m = grid.size();
    int n = grid[0].size();
    vector<int> pre(n), cur(n);
    pre[0] = grid[0][0];
    for (int i = 1; i < n; i++){
        pre[i] = pre[i - 1] + grid[0][i];
    }
    for (int i = 1; i < m; i++){
        cur[0] = pre[0] + grid[i][0];
        for (int j = 1; j < n; j++){
            cur[j] = cur[j - 1] < pre[j] ? cur[j - 1] : pre[j];
            cur[j] += grid[i][j];
        }
        pre = cur;
    }
    return pre[n - 1];
}

// leetcode174：已知一个二维数组(整数，可能有正有负)，左上角为骑士的位置，右下角代表公主的位置
// 正数增加生命，负数减少生命，问骑士进入数组前至少是多少生命值，才能保证行走过程中生命至少为1(只能向下或者向右走)
// 思路：从右下角到左上角对生命值进行动态规划
int calculateMinimumHP(vector<vector<int>>& dungeon) {
    if (dungeon.size() == 0 || dungeon[0].size() == 0){
        return 0;
    }
    int m = dungeon.size();
    int n = dungeon[0].size();
    // pre为cur的下一行，从下往上倒着一行一行赋值
    vector<int> pre(n), cur(n);
    pre[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--){
        pre[i] = pre[i + 1] - dungeon[m - 1][i + 1] > 1 ? pre[i + 1] - dungeon[m - 1][i + 1] : 1;
    }
    for (int i = m - 2; i >= 0; i--){
        cur[n - 1] = pre[n - 1] - dungeon[i + 1][n - 1] > 1 ? pre[n - 1] - dungeon[i + 1][n - 1] : 1;
        for (int j = n - 2; j >= 0; j--){
            cur[j] = cur[j + 1] - dungeon[i][j + 1] > 1 ? cur[j + 1] - dungeon[i][j + 1] : 1;
            int tmp = pre[j] - dungeon[i + 1][j] > 1 ? pre[j] - dungeon[i + 1][j] : 1;
            cur[j] = tmp < cur[j] ? tmp : cur[j];
        }
        pre = cur;
    }
    return pre[0] - dungeon[0][0] > 1 ? pre[0] - dungeon[0][0] : 1;
}

int main(){
    vector<int> coins = {1, 2, 5};
    cout << "coinChange: " << coinChange(coins, 11) << endl;
}

