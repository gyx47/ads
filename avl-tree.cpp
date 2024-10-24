#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

 struct Node{
        int data;
        Node *left;
        Node *right;
        int hight;
        int bf;
    };
Node* newNode(int data){
    Node *node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->hight = 1;
    node->bf=0;
    return node;
}
Node* insert(Node* root, int data){
    if(root == NULL){
        return newNode(data);
    }
    if(data < root->data){
        root->left = insert(root->left, data);
    }
    else{
        root->right = insert(root->right, data);
    }
    return root;
}
int getHeight(Node* root) {
    return (root == nullptr) ? 0 : root->hight;//把两个函数hight和balance逻辑混到一起了，导致了段错误
}
Node* rightRotate(Node* root){
    Node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    root->hight = max(getHeight(root->left), getHeight(root->right)) + 1;//本来写的是root->left->hight,导致了段错误
    newRoot->hight = max(getHeight(newRoot->right), getHeight(newRoot->left)) + 1;
    return newRoot;
}
Node* leftRotate(Node* root){
    Node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    root->hight = max(getHeight(root->left), getHeight(root->right)) + 1;
    newRoot->hight = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
    return newRoot;
}

int hight(Node* &root){//传指针参居然没法改变原树，除非在最后返回根节点！三观倒塌了。
// 在C++中，传递指针参数时，实际上是按值传递的，即传递的是指针的拷贝。当你在函数中修改指针的值时，修改的只是这个拷贝，并不会影响到原来的指针。这就是为什么即使你在函数中改变了指针的值（如指向了一个新的节点），也不会影响到原树的根节点。

// 要改变原树的根节点，有两种方法：

// 使用指针的引用（Node*&）：通过传递指针的引用，函数能够直接修改原来的指针。这样一来，任何对指针的修改都会直接反映在调用者的环境中。

// 返回新根节点并在外部更新：另一种方法是让函数返回修改后的根节点，然后在外部使用返回值来更新原树的根节点。这种方法虽然稍显冗长，但在某些场景下更加清晰和直观。
    if(root == NULL){
        return 0;
    }
    root->hight=max(hight(root->left),hight(root->right))+1;
    if(root->left==NULL && root->right==NULL){
        root->bf=0;
    }
    else if(root->left==NULL){
        root->bf=-(root->right->hight);
    }
    else if(root->right==NULL){
        root->bf=root->left->hight;
    }
    else
    {root->bf=root->left->hight-root->right->hight;}

    if(root->bf > 1 ){
        if(root->left->bf < 0){
            root->left = leftRotate(root->left);
        }
       
            root = rightRotate(root);
            // cout<<root->data<<endl;
       

    }
    else if(root->bf < -1){
        if(root->right->bf > 0){
            root->right = rightRotate(root->right);
        }
        root = leftRotate(root);
      //   cout<<root->data<<endl;
    }
    return root->hight;//hight函数设计的巨差，属于临时起意图方便
}
int main(){
    int number;
     Node* root =nullptr;//不能在if里初始化，不然root是if里的局部变量，外部不可见。
    int data,n;
    cin >> number;
    for(int i = 0; i < number; i++){
        cin >> data;
       
        root = insert(root, data);     
      //   cout<<root->data<<endl;
        n=hight(root);
       //  cout<<root->data<<endl;
    }
   
    cout<<root->data;
    
}