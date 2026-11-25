// 02 - Tree Traversals
// DFS: Inorder (L,Root,R), Preorder (Root,L,R), Postorder (L,R,Root)
// BFS: Level order (level by level)
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

// ---------- Recursive ----------
void inorder(Node* r)   { if (!r) return; inorder(r->left);  cout << r->data << " "; inorder(r->right); }
void preorder(Node* r)  { if (!r) return; cout << r->data << " "; preorder(r->left); preorder(r->right); }
void postorder(Node* r) { if (!r) return; postorder(r->left); postorder(r->right); cout << r->data << " "; }

// ---------- Iterative (using stack) ----------
vector<int> inorderIter(Node* root) {
    vector<int> res;
    stack<Node*> st;
    Node* cur = root;
    while (cur || !st.empty()) {
        while (cur) { st.push(cur); cur = cur->left; }  // go far left
        cur = st.top(); st.pop();
        res.push_back(cur->data);                        // visit
        cur = cur->right;                                // then right
    }
    return res;
}

vector<int> preorderIter(Node* root) {
    vector<int> res;
    if (!root) return res;
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* cur = st.top(); st.pop();
        res.push_back(cur->data);
        if (cur->right) st.push(cur->right);   // push right first
        if (cur->left)  st.push(cur->left);    // so left is processed first
    }
    return res;
}

vector<int> postorderIter(Node* root) {        // trick: reverse of (Root, R, L)
    vector<int> res;
    if (!root) return res;
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* cur = st.top(); st.pop();
        res.push_back(cur->data);
        if (cur->left)  st.push(cur->left);
        if (cur->right) st.push(cur->right);
    }
    reverse(res.begin(), res.end());
    return res;
}

// ---------- BFS (Level order) ----------
vector<vector<int>> levelOrder(Node* root) {
    vector<vector<int>> res;
    if (!root) return res;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();                 // nodes in this level
        vector<int> level;
        for (int i = 0; i < size; i++) {
            Node* cur = q.front(); q.pop();
            level.push_back(cur->data);
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        res.push_back(level);
    }
    return res;
}

void print(const vector<int>& v) { for (int x : v) cout << x << " "; cout << "\n"; }

int main() {
    /*
             1
            / \
           2   3
          / \   \
         4   5   6
    */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);

    cout << "Inorder   (rec) : "; inorder(root);   cout << "\n";
    cout << "Preorder  (rec) : "; preorder(root);  cout << "\n";
    cout << "Postorder (rec) : "; postorder(root); cout << "\n\n";

    cout << "Inorder   (iter): "; print(inorderIter(root));
    cout << "Preorder  (iter): "; print(preorderIter(root));
    cout << "Postorder (iter): "; print(postorderIter(root));

    cout << "\nLevel order:\n";
    for (auto& level : levelOrder(root)) print(level);
    return 0;
}
