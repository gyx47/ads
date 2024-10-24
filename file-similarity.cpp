#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>
#include<iomanip>
using namespace std;
int main(){
   vector<string> files;
   vector<string> words;
   vector<vector<int>> has;
   int n;
   cin>>n;
   int j=0;
    for(int i=0;i<n;i++,j++){
         string file;
         cin>>file;
         files.push_back(file);

         string word;
         while(cin>>word){
              if(word=="#") break;
              if(word.size() >= 2 && word.rfind("ed") == word.size() - 2) word.erase(word.size() - 2); // ***去掉末尾的 "ed"
              else if(word.size() >= 3 && word.rfind("ing") == word.size() - 3) word.erase(word.size() - 3); // ***去掉末尾的 "ing"
              else if(word.size() >= 2 && word.rfind("es") == word.size() - 2) word.erase(word.size() - 2); // ***去掉末尾的 "es"
              else if(word.size() >= 3 && word.rfind("ies") == word.size() - 3) word.erase(word.size() - 3); // ***去掉末尾的 "ly"
              int i=distance(words.begin(), find(words.begin(),words.end(),word));
              if(find(words.begin(),words.end(),word)!=words.end()) {
              has[j][i]++;
              }
              words.push_back(word);

             
         }
    }
    cin>>n;
    while(n!=0){
        n--;
        int q=1;

        string file;
      cin>>file;
      int j1 =distance(files.begin(),find(files.begin(),files.end(),file));
      cin>>file;
      int j2 =distance(files.begin(),find(files.begin(),files.end(),file));
      int sum=0;
      double sum1=0;
      double sum2=0;
      for(int i=0;i<words.size();++i){
          sum+=has[j1][i]*has[j2][i];
            sum1+=has[j1][i]*has[j1][i];
            sum2+=has[j2][i]*has[j2][i];
          }
          sum1=sqrt(sum1);
            sum2=sqrt(sum2);
            double result=acos(sum/(sum1*sum2));
            cout<<"Case "<<q<<": "<<fixed<<setprecision(3)<<result<<endl;
            q++;
      }

    }

