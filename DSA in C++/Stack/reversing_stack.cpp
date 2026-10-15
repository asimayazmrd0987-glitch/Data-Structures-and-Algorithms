#include<iostream>
#include<stack>
#include<string>
using namespace std;


int main() {
    stack<char> st;

    string str = "Data Structure & Algorithm";

    for(int i=0; i<str.length(); i++) {
        char ch = str[i];
        st.push(ch);
    }

    string ans = "";

    while(!st.empty()) {
        char ch = st.top();
        ans.push_back(ch);
        st.pop();   
    }
    cout << "Reversed string: " << ans << endl;
}
// Reversed string: mhtiroglA & erutcurtS ataD
// Time complexity: O(n)