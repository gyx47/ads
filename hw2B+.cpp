#include<iostream>
#include<vector>
using namespace std;

int N=3;

struct Node {
    bool isleaf;
    vector<int> data;
    Node* next;
    vector<Node*> children;
};

Node *createnode(int n) {
    Node* temp = new Node;
    temp->isleaf = true;
    temp->data.push_back(n);
    return temp;
}

bool find(Node* node, int key) {
    for (int i = 0; i < node->data.size(); ++i) {
        if (node->data[i] == key) {
            return true;
        }
        if (!node->isleaf && key < node->data[i]) {
            return find(node->children[i], key);
        }
    }
    if (!node->isleaf && key > node->data.back()) {
        return find(node->children.back(), key);
    }
    return false;
}

void print(Node* head) {
    cout << "[";
    for (int i = 0; i < head->data.size() - 1; ++i) {
        cout << head->data[i] << ",";
    }
    cout << head->data[head->data.size() - 1] << "]";
}

Node* split(Node* head) {
    Node* newnode = new Node;
    newnode->isleaf = head->isleaf;
    if (head->isleaf) {
        for (int i = head->data.size() - 1; i > N / 2; --i) {
            newnode->data.insert(newnode->data.begin(), head->data[i]);
            head->data.erase(head->data.begin() + i);
        }
        head->next = newnode;
    } else {
        for (int i = N - 1; i >= N / 2; --i) {
            newnode->data.insert(newnode->data.begin(), head->data[i]);
            newnode->children.insert(newnode->children.begin(), head->children[i+1]);//**
            head->data.erase(head->data.begin() + i);
            head->children.erase(head->children.begin() + i+1);//量很大的时候导致段错误？
        }
        head->next = newnode;
    }
    newnode->next = nullptr;
    return head;
}

Node* insert(Node* pronode, int key) {
    if (find(pronode, key)) {
        cout << "Key " << key << " is duplicated" << endl;
        return pronode;
    }

    if (pronode->children.size() != 0 && pronode->children[0]->isleaf) {
        Node* temp = nullptr;
        for (int i = 0; i < pronode->data.size(); ++i) {
            if (key < pronode->data[i]) {
                temp = pronode->children[i];
                break;
            }
        }
        if (!temp) {
            temp = pronode->children.back();
        }
        for (int i = 0; i < temp->data.size(); ++i) {
            if (key < temp->data[i]) {
                temp->data.insert(temp->data.begin() + i, key);
                break;
            }
        }
        if (temp->data.empty() || temp->data.back() < key) {
            temp->data.push_back(key);
        }
        if (temp->data.size() > N) {
            temp = split(temp);
            bool found = false;
            for (int i = 0; i < pronode->data.size(); ++i) {
                if (pronode->data[i] >temp->data[0]) {
                    pronode->data.insert(pronode->data.begin() + i, temp->next->data[0]);
                    pronode->children.insert(pronode->children.begin() + i+1, temp->next);
                    found = true;
                    break;
                }
            }
            if (!found) {
                pronode->data.push_back(temp->next->data[0]);
                pronode->children.push_back(temp->next);
            }
        }
        return pronode;
    } else if (pronode->children.size() == 0) {
        for (int i = 0; i < pronode->data.size(); ++i) {
            if (key < pronode->data[i]) {
                pronode->data.insert(pronode->data.begin() + i, key);
                return pronode;
            }
        }
        pronode->data.push_back(key);
        return pronode;
    } else {
        Node* son = nullptr;
        for (int i = 0; i < pronode->data.size(); ++i) {
            if (key < pronode->data[i]) {
                son = insert(pronode->children[i], key);
                break;
            }
        }
        if (!son) {
            son = insert(pronode->children[pronode->children.size() - 1], key);
        }
        if (son->data.size() >= N) {
            son = split(son);
            pronode->data.push_back(son->next->data[0]);
          
            //son->next->data.erase(son->next->data.begin()+1);
            pronode->children.push_back(son->next);
        }
        return pronode;
    }
}

int main() {
    int n, key;
    cin >> n >> key;
    Node* node = createnode(key);
    Node* head = node;
    for (int i = 1; i < n; ++i) {
        cin >> key;
        head = insert(head, key);
        if (head->data.size() > N || (head->data.size() == N && !head->isleaf)) {
            head = split(head);
            Node* prohead = createnode(head->next->data[0]);
            prohead->isleaf = false;
            prohead->children.push_back(head);
            if(head->isleaf==false) head->next->data.erase(head->next->data.begin());
            prohead->children.push_back(head->next);
            head = prohead;
        }
    }
    print(head);
    vector<Node*> v;
    Node* enter = createnode(111);
    v.push_back(enter);
    for (int i = 0; i < head->children.size(); ++i) {
        v.push_back(head->children[i]);
    }
    while (!v.empty()) {
        Node* temp = v[0];
        v.erase(v.begin());
        if (temp->data[0] != 111) {
            print(temp);
            for (int i = 0; i < temp->children.size(); ++i) {
            //    cout<<temp->children[i]->data[0]<<endl;
                v.push_back(temp->children[i]);
            }
          
           
        } else {
            cout << endl;
            if( v[0]->children.size()!=0)
             v.push_back(enter);
        }
    }
}