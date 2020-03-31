#include<iostream>
#include<vector>
#include<queue>

using namespace std;

bool adjacent(string &word1, string &word2){
    int dist = 0;

    for (int i = 0; i < word1.length(); i++){
        if (word1[i] != word2[i]){
            dist++;
        }
        if (dist > 1){
            break;
        }
    }
    return dist == 1;
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    wordList.push_back(beginWord);
    vector<int> visit(wordList.size(), 0);

    // 构造以单词下标为节点，以单词间的不同字符个数为边的图
    vector<vector<int>> graph(wordList.size());
    for (int i = 0; i < wordList.size(); i++){
        graph[i] = vector<int>();
    }
    for (int i = 0; i < wordList.size(); i++){
        for (int j = i + 1; j < wordList.size(); j++){
            if (adjacent(wordList[i], wordList[j])){
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    // 广度优先遍历图
    queue<pair<int, int>> Q;
    visit[wordList.size() - 1] = 1;
    Q.push(make_pair(wordList.size() - 1, 1));
    while(!Q.empty()){
        int idx = Q.front().first;
        int dist = Q.front().second;
        Q.pop();

        if (wordList[idx] == endWord){
            return dist;
        }

        for (int i = 0; i < graph[idx].size(); i++){
            if (visit[graph[idx][i]] == 0){
                visit[graph[idx][i]] = 1;
                Q.push(make_pair(graph[idx][i], dist + 1));
            }
        }
    }
    return 0;
}

int main(){
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    string beginWord = "hit";
    string endWord = "cog";
    cout << ladderLength(beginWord, endWord, wordList) << endl;
}