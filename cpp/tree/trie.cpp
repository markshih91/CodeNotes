#include <iostream>
#include<vector>
#include <string>

using namespace std;

const int MAX_ALPHA_NUM = 26;

struct TrieNode{
    TrieNode *child[MAX_ALPHA_NUM];
    bool is_end;
    TrieNode():is_end(false){
        for(int i = 0; i < MAX_ALPHA_NUM; i++){
            child[i] = 0;
        }
    }
};

class Trie{
    public:
    Trie(){}
    ~Trie(){
        for (int i = 0; i < _node_vec.size(); i++){
            delete _node_vec[i];
        }
    }

    // 插入一个单词
    void insert(string word){
        TrieNode *ptr = &_root;

        int i = 0;
        while(i < word.length()){
            int pos = word[i] - 'a';
            if (!ptr->child[pos]){
                ptr->child[pos] = new_node();
            }
            ptr = ptr->child[pos];
            i++;
        }
        ptr->is_end = true;
    }

    //查找是否包含单词
    bool search(string word){
        TrieNode *ptr = &_root;
        int i = 0;
        while(i < word.length()){
            int pos = word[i] - 'a';
            if (!ptr->child[pos]){
                return false;
            }
            ptr = ptr->child[pos];
            i++;
        }
        return ptr->is_end;
    }

    //查找是否包含以prefix为前缀的单词
    bool startsWith(string prefix){
        TrieNode *ptr = &_root;
        int i = 0;
        while(i < prefix.length()){
            int pos = prefix[i] - 'a';
            if (!ptr->child[pos]){
                return false;
            }
            ptr = ptr->child[pos];
            i++;
        }
        return true;
    }


    TrieNode* root(){
        return &_root;
    }

    private:

    TrieNode* new_node(){
        TrieNode *node = new TrieNode();
        _node_vec.push_back(node);
        return node;
    }

    vector<TrieNode *> _node_vec;
    TrieNode _root;
};

// 前序遍历trie节点，并保存单词到words
void preolder_trie(TrieNode *node, vector<string> &words, string prefix){
    for(int i = 0; i < MAX_ALPHA_NUM; i++){
        if (node->child[i]){
            prefix.push_back('a' + i);
            if(node->child[i]->is_end){
                words.push_back(prefix);
            }
            preolder_trie(node->child[i], words, prefix);
            prefix.pop_back();
        }
    }
}

//查找是否包含单词，单词中可能包含'.'，代表任意字符
bool reg_search(TrieNode *node, string word){
    if(word.length() == 0 && node->is_end){
        return true;
    }
    if(word[0] == '.'){
        for (int i = 0; i < MAX_ALPHA_NUM; i++){
            if(node->child[i] && reg_search(node->child[i], word.substr(1))){
                return true;
            }
        }
    }else{
        int pos = word[0] - 'a';
        if (node->child[pos] && reg_search(node->child[pos], word.substr(1))){
            return true;
        }
    }
    return false;
}

int main(){

    // 测试：trie类insert和search
    Trie dict = Trie();
    dict.insert("hello world");
    dict.insert("hello");
    dict.insert("wordl");
    cout << "hello in dict: " << dict.search("hello") << endl;
    cout << "starts with wor: " << dict.startsWith("wor") << endl;

    // 测试：先序遍历trie
    vector<string> words;
    preolder_trie(dict.root(), words, "");
    for (int i = 0; i < words.size(); i++){
        cout<< "words " << i << ": " << words[i] << endl;
    }

    // 测试：包含'.'的单词查找
    cout << "he.lo in dict: " << reg_search(dict.root(), "he.lo") << endl;

}