#include<bits/stdc++.h>
using namespace std;

class HuffmanTree{
public:
        int val;
        char letter;
        HuffmanTree *left;
        HuffmanTree *right;

        HuffmanTree(int val, char c)
        {
            this->val = val;
            this->letter = c;
            left = NULL;
            right = NULL;
        }
};

vector<pair<int, char>> FrequencyDect(string s)
{
    map<char, int> mp;
    for(int i=0;i<s.size();i++)
    {
        mp[s[i]]++;
    }

    vector<pair<int, char>> v;
    for(int i=0;i<s.size();i++)
    {
       if(mp[s[i]]!=0)
       {
            v.push_back({mp[s[i]],s[i]});
            mp[s[i]]= 0;
       }
    }
   
    cout<<"FrequencyMap -> "<<endl;
    for(int i=0;i<v.size();i++)
        {
            cout<<v[i].first<<" -> "<<v[i].second<<endl;
        }
    cout<<endl;
    return v;
}

class compare
{
public:
    bool operator()(HuffmanTree *a, HuffmanTree *b)
    {
        return a->val > b->val;
    }
};

void print(priority_queue<HuffmanTree*, vector<HuffmanTree*>,compare> q)
{
    while(q.size())
    {
        cout<<q.top()->letter<<" "<<q.top()->val<<endl;
        q.pop();
    }
    return;
}
HuffmanTree *makeTree(vector<pair<int, char>> &Freq) {
    priority_queue<HuffmanTree*, vector<HuffmanTree*>, compare> q;
    for (int i = 0; i < Freq.size(); ++i) {
        q.push(new HuffmanTree(Freq[i].first, Freq[i].second));
    }

    while (q.size() > 1) {
        HuffmanTree *l = q.top();
        q.pop();
        HuffmanTree *r = q.top();
        q.pop();

        HuffmanTree *sumNode = new HuffmanTree(l->val + r->val, '~');
        sumNode->left = l;
        sumNode->right = r;
        q.push(sumNode);
    }

    return q.top();
}

void getCode(HuffmanTree *root, string s, map<char, string> &codevector) {
    if (!root) {
        return;
    }

    if (root->letter != '~') {
        codevector[root->letter] = s;
        return;
    }

    getCode(root->left, s + "0", codevector);
    getCode(root->right, s + "1", codevector);
}


string encode(HuffmanTree *tree, string s) {
    map<char, string> codevector;
    getCode(tree, "", codevector);

    string res = "";
    for (auto i : s) {
        res += codevector[i];
    }
    return res;
}

string decode(HuffmanTree *tree, string encoded) {
    string decoded = "";
    int i = 0;
    while (i < encoded.size()) {
        HuffmanTree *current = tree;
        while (current->letter == '~') {
            if (encoded[i] == '0') {
                current = current->left;
            } else if (encoded[i] == '1') {
                current = current->right;
            }
            i++;
        }
        decoded += current->letter;
    }
    return decoded;
}

int main() {
    string s;
    getline(cin, s);

    vector<pair<int, char>> Freq = FrequencyDect(s);

    HuffmanTree *tree = makeTree(Freq);

    string encoded = encode(tree, s);

    cout<<"Given String :-> "<<s<<endl;
    cout << "Huffman Code for the given string is :-> " << encoded << endl;

    string decoded = decode(tree, encoded);

    cout << "Decoded string :-> " << decoded << endl;

    return 0;
}





