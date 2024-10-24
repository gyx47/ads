#include<iostream>
#include<vector>
using namespace std;
int N=3;
struct Node{
    bool isleaf;
    vector<int> data;
    Node* next;
    vector<Node*> children;
};
Node *createnode(int n){
    Node* temp = new Node;
    temp->isleaf=true;
    temp->data.push_back(n);
    return temp;
}

void print(Node* head){
     cout<<"[";
        for(int i=0;i<head->data.size()-1;i++){
            cout<<head->data[i]<<",";
        }
        cout<<head->data[head->data.size()-1]<<"]";
  
}
Node* split(Node* head){
    Node* newnode=new Node;
     newnode->isleaf = head->isleaf;
    if(head->isleaf){
        for (int i = head->data.size()-1; i >N / 2; i--) {//要用size_t
        newnode->data.insert(newnode->data.begin(), head->data[i]);
        head->data.erase(head->data.begin() + i);
    }
        head->next=newnode;
    }else{
       for (int i = N-1 ; i >= N / 2; i--) {
        newnode->data.insert(newnode->data.begin(), head->data[i]);
       // cout<<head->data[i]<<endl;
        newnode->children.insert(newnode->children.begin(),head->children[i]);
        head->data.erase(head->data.begin() + i);
        head->children.erase(head->children.begin() + i);
    }
        head->next=newnode;
    }newnode->next = nullptr;
    return head;
}
Node* insert(Node* pronode, int key){
  
       bool found=false;
     if(pronode->children.size()!=0&&pronode->children[0]->isleaf){
      //  Node* pronode=head;
       //int i=0;
         Node* temp=nullptr;//好像是前面的定义不完善的问题所以段错误为什么
    for(int i=0;i<pronode->data.size();i++){//***段错误真难找啊
    if(key<pronode->data[i]){//加一个重复检测,超出范围的data是-141481……
       temp=pronode->children[i];
         found=true;
       break;//****
    }
    }
    if (!found) {
    temp = pronode->children.back(); // 如果key是最大的，选择最后一个子节点
}
found=false;
   for(int i=0;i<temp->data.size();i++){
    if(key<temp->data[i]){
        temp->data.insert(temp->data.begin()+i,key);
        found=true;
        break;
       
    }
   }
   if(found==false){
    temp->data.push_back(key);
   }
 
    if(temp->data.size()>N){
        temp=split(temp);
        
        for(int i=0;i<pronode->data.size();i++){
     if(temp->next->data[0]<pronode->data[i]){
         
             pronode->data.insert(pronode->data.begin()+i,temp->next->data[0]);//***
             pronode->children.insert(pronode->children.begin()+i+1,temp->next);
    break;
         }
          else if(i==pronode->data.size()-1)
        {pronode->data.push_back(temp->next->data[0]);
        pronode->children.push_back(temp->next);}
        }
    }
    return pronode;
    
}else if(pronode->children.size()==0){
    for(int i=0;i< pronode->data.size();i++){
    if(key<pronode->data[i]){
        pronode->data.insert(pronode->data.begin()+i,key);

        
        return pronode;
    }
   }
    pronode->data.push_back(key);
    return pronode;
}

else{
 
    Node* son=NULL;
for(int i=0;i<pronode->data.size();i++){
    if(key<pronode->data[i]){
        son= insert(pronode->children[i],key);
        found=true;
 
    }
}
if(!found){
    son=insert(pronode->children[pronode->children.size()-1],key);
}

if(son->data.size()>=N){
            son=split(son);
  //  cout<<son->next->data[0]<<endl;
    //  for(int i=0;i<pronode->data.size();i++){
    //  if(son->next->data[0]<pronode->data[i]){
         
    //          pronode->data.insert(pronode->data.begin()+i,son->next->data[0]);//***
    //          pronode->children.insert(pronode->children.begin()+i+1,son->next);
    // break;
    //      }
    //       if(i==pronode->data.size()-1)

          
    //     {pronode->data.push_back(son->next->data[0]);
    //     pronode->children.push_back(son->next);}
    //     }}
    pronode->data.push_back(son->next->data[0]);
            pronode->children.push_back(son->next);
        }
        return pronode;

}
   
    }
int main(){
int n;
cin>>n;
int key;
cin>>key;
Node* node=createnode(key);
Node* head=node;
for(int i=1;i<n;i++){
    cin>>key;
    head=insert(head,key);
    if(head->data.size()>N||(head->data.size()==N&&head->isleaf==false)){//***
        head=split(head);
        Node* prohead=createnode(head->next->data[0]);
       prohead->isleaf=false;
        prohead->children.push_back(head);
  
            prohead->children.push_back(head->next);
            head=prohead;
    }
   
}
print(head);
vector<Node*> v;
 Node* enter=createnode(111);
v.push_back(enter);
for(int i=0;i<head->children.size();i++){
    v.push_back(head->children[i]);
}

while(v.size()!=0){
    Node* temp=v[0];
    v.erase(v.begin());
   if(temp->data[0]!=111) {print(temp);
    for(int i=0;i<temp->children.size();i++){
        v.push_back(temp->children[i]);
        
    }v.push_back(enter);}
    else cout<<endl;
}
}