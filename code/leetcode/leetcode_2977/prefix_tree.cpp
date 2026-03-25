#include<iostream>

using namespace std;
struct TrieNode{
    TrieNode* children[26];
    int strID = -1;
    bool isEnd = false;
    TrieNode() {
        for (int i = 0; i < 26; i++) children[i] = nullptr;
    }
};

TrieNode* NewNode(){
    struct TrieNode* node = new TrieNode();
    return node;
}

int main(void){
    struct TrieNode *node = NewNode();
    string input = "hello world";
    TrieNode *ptr = node;
    int count = 0;
    for(int i = 0; i < input.size(); i++){
        char c = input[i];
        if(c == ' '){
            ptr->strID = count++;
            ptr->isEnd = true;
            ptr = node;
        }
        ptr->children[input[i] - 'a'] = NewNode(); 
        ptr = ptr->children[input[i] - 'a'];
    }
    string check = "hell";
    ptr = node;
    for(int i = 0; i < check.size(); i++){
        char c = check[i];
        if(ptr->children[c - 'a'] == nullptr){
            cout << "not exist" << endl;
            return 0;
        }
        ptr = ptr->children[input[i] - 'a'];
    }
    if(ptr->isEnd == true){
        cout << "the id is " << ptr->strID << endl;
    }else{
        cout << "the id is empty" << endl;
    }
    

}