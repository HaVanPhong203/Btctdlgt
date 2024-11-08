#include <bits/stdc++.h>
#define endl "\n"
#define int long long
#define ChoHoKhongGam main
using namespace std;
const int mod = 1e9+7;

#ifndef __Trie__
#define __Trie__
class Trie{
public:
    class Node {
    public:
        int exist; 
        int cnt; 
        Node* Child[26];
        Node() {
            cnt = exist = 0;
            for (int i = 0; i < 26; i++) Child[i] = NULL;
        }
    };
    int current;
    Node* root;
    Trie() : current(0) {
        root = new Node();
    }
    void add_string(string s) {
        Node* p = root;
        for (auto x : s) {
            int temp = x - 'a';
            if (p->Child[temp] == NULL) p->Child[temp] = new Node();
            p = p->Child[temp];
            p->cnt++;
        }
        p->exist++;
    }
    bool find_string(string s) {
        Node* p = root;
        for (auto x : s) {
            int temp = x - 'a';
            if (p->Child[temp] == NULL) return 0;
            p = p->Child[temp];
        }
        return p->exist != 0;
    }
    int count_prefix(string s) {
        Node* p = root;
        for (auto x : s) {
            int temp = x - 'a';
            if (p->Child[temp] == NULL) return 0;
            p = p->Child[temp];
        }
        return p->cnt;
    }
    bool delete_string_recursive(string& s, int id, Node* p) {
        if (id < s.size()) {
            int temp = s[id] - 'a';
            bool is_child_deleted = delete_string_recursive(s, id + 1, p->Child[temp]);
            if (is_child_deleted) p->Child[temp] = NULL;
        } else p->exist--;
        if (p != root) {
            p->cnt--;
            if (p->cnt == 0) {
                delete p;
                return 1;
            }
        }
        return 0;
    }
    void delete_string(string s) {
        if (!find_string(s)) return;
        delete_string_recursive(s, 0, root);
    }
};
#endif

ChoHoKhongGam() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    Trie T;
    for (int i = 0; i < n; i++) {
        string cmd, dir; cin >> cmd >> dir;
        if (cmd == "add") T.add_string(dir);
        else cout << T.count_prefix(dir) << endl;
    }  
}
