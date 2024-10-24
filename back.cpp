// 先dfs然后发现走不下去就剪枝肯定没有错，问题是怎么搞比较快。
// 储存的数据结构用什么好
// 找右边

#include <iostream>
#include <vector>
using namespace std;
int a[10][10] = {0};
// struct node{
//     vector<int> neighber = vector<int>(4,0);
// };
int connection[10][10][4];
int findright(int line_id, int col_id, int col)
{
    while (col_id < col)
    {
        if (a[line_id][col_id] != 0)
            return col_id;
        col_id++;
    }
    return -1;
}
int finddown(int line_id, int col_id, int line)
{
    while (line_id < line)
    {
        if (a[line_id][col_id] != 0)
            return line_id;
        line_id++;
    }
    return -1;
}
int findleft(int line_id, int col_id)
{
    while (col_id >= 0)
    {
        if (a[line_id][col_id] != 0)
            return col_id;
        col_id--;
    }
    return -1;
}
int findup(int line_id, int col_id)
{
    while (line_id >= 0)
    {
        if (a[line_id][col_id] != 0)
            return line_id;
        line_id--;
    }
    return -1;
}
void connect(int line_id, int col_id, int i, int j, int connection[][10][4])
{
    if (line_id == i)
    {
        if (col_id < j)
        {
            connection[line_id][col_id][3] = 1;
            connection[i][j][2] = 1;
        }
        else
        {
            connection[line_id][col_id][2] = 1;
            connection[i][j][3] = 1;
        }
    }
    else
    {
        if (line_id < i)
        {
            connection[line_id][col_id][1] = 1;
            connection[i][j][0] = 1;
        }
        else
        {
            connection[line_id][col_id][0] = 1;
            connection[i][j][1] = 1;
        }
    }
}
void disconnect(int line_id, int col_id, int i, int j, int connection[][10][4])
{
    if (line_id == i)
    {
        if (col_id < j)
        {
            connection[line_id][col_id][3] = 0;
            connection[i][j][2] = 0;
        }
        else
        {
            connection[line_id][col_id][2] = 0;
            connection[i][j][3] = 0;
        }
    }
    else
    {
        if (line_id < i)
        {
            connection[line_id][col_id][1] = 0;
            connection[i][j][0] = 0;
        }
        else
        {
            connection[line_id][col_id][0] = 0;
            connection[i][j][1] = 0;
        }
    }
}
int dfs(int line_id, int col_id, int line, int col, int n)
{
    int i=0, j=0;
    if (line_id < 0 || line_id >= line || col_id < 0 || col_id >= col)
        return 1;
    if (a[line_id][col_id] == 0)
        {col_id++;
        if(col_id==col){
            col_id=0;
            line_id++;
        }
        if(dfs(line_id, col_id, line, col, 0)==-1){
            col_id--;
            if(col_id==-1){
                col_id=col-1;
                line_id--;
            }
            return -1;
        }
       return 1;//
        }
    int rt = 0; // 目前最大的问题是，如果dfs返回的是1，那就固定了不调整了，哪怕不先从右边查找就可能可以成功,甚至右边固定，下方不固定的模式也要搜索一遍。
    if (a[line_id][col_id] != 0 && (n == 0 || n == 5) &&connection[line_id][col_id][3]==0&& (j = findright(line_id, col_id+1, col)) != -1)
    {//cout<<"run"<<line_id<<endl;
        connect(line_id, col_id, line_id, j, connection);
       
        if (n == 5)
            n = 1;
        a[line_id][col_id]--;
        a[line_id][j]--;
        rt = dfs(line_id, j, line, col, 0);
        if (rt == -1)
        {//
            
                rt = dfs(line_id, j, line, col, 5);
                if (rt == -1)
                {
                    rt = dfs(line_id, j, line, col, 1);
                    if (rt == -1)
                    {
                        rt = dfs(line_id, j, line, col, 2);
                        if (rt == -1)
                        {
                            rt = dfs(line_id, j, line, col, 3);
                            if (rt == -1)
                            {
                                a[line_id][col_id]++;
                                a[line_id][j]++;
                                disconnect(line_id, col_id, line_id, j, connection);
                            }
                        }
                    }
                
            }
        }
        else
        {
        }
        // a[line_id][col_id]++;
    }
 n++;
    if (a[line_id][col_id] != 0 && n == 1 &&connection[line_id][col_id][1]==0&& (i = finddown(line_id+1, col_id, line)) != -1)
    {
        connect(line_id, col_id, i, col_id, connection);
        
        a[line_id][col_id]--;
        a[i][col_id]--;
        // rt=dfs(line_id,j,line,col,0);

        rt = dfs(i, col_id, line, col, 0);
        if (rt == -1)
        {
            rt = dfs(i, col_id, line, col, 5);
            if (rt == -1)
            {
                rt = dfs(i, col_id, line, col, 1);
                if (rt == -1)
                {
                    rt = dfs(i, col_id, line, col, 2);
                    if (rt == -1)
                    {
                        rt = dfs(i, col_id, line, col, 3);
                        if (rt == -1)
                        {
                            a[line_id][col_id]++;
                            a[i][col_id]++;
                            disconnect(line_id, col_id, i, col_id, connection);
                        }
                    }
                }
            }
        }
        // a[line_id][col_id]++;
    }n++;
    if (a[line_id][col_id] != 0 && n == 2 &&connection[line_id][col_id][2]==0&& (j = findleft(line_id, col_id-1)) != -1)
    {
        connect(line_id, col_id, line_id, j, connection);
       
        a[line_id][col_id]--;
        a[line_id][j]--;
        //  rt=dfs(i,col_id,line,col,0);
        rt = dfs(line_id, j, line, col, 0);
        if (rt == -1)
        {
            rt = dfs(line_id, j, line, col, 5);
            if (rt == -1)
            {
                rt = dfs(line_id, j, line, col, 1);
                if (rt == -1)
                {
                    rt = dfs(line_id, j, line, col, 2);
                    if (rt == -1)
                    {
                        rt = dfs(line_id, j, line, col, 3);
                        if (rt == -1)
                        {
                            a[line_id][col_id]++;
                            a[line_id][j]++;
                            disconnect(line_id, col_id, line_id, j, connection);
                        }
                    }
                }
            }
        }
        //  a[line_id][col_id]++;
    } n++;
    if (a[line_id][col_id] != 0 && n == 3 && connection[line_id][col_id][0]==0&&(i = findup(line_id-1, col_id)) != -1)
    {
        connect(line_id, col_id, i, col_id, connection);
        a[line_id][col_id]--;
        a[i][col_id]--;
        rt = dfs(i, col_id, line, col, 0);
        //  rt=dfs(i,col_id,line,col,0);
        if (rt == -1)
        {
            rt = dfs(i, col_id, line, col, 5);
            if (rt == -1)
            {
                rt = dfs(i, col_id, line, col, 1);
                if (rt == -1)
                {
                    rt = dfs(i, col_id, line, col, 2);
                    if (rt == -1)
                    {
                        rt = dfs(i, col_id, line, col, 3);
                        if (rt == -1)
                        {
                            a[line_id][col_id]++;
                            a[i][col_id]++;
                            disconnect(line_id, col_id, i, col_id, connection);
                        }
                    }
                }
            }
        }
        //  a[line_id][col_id]++;
    }
    if (a[line_id][col_id] != 0)
        return -1;
    //     if (connection[line_id][col_id][1]==1) {
    //         j=finddown(line_id,col_id,line);
    //         disconnect(line_id,col_id,line_id,j,connection);
    //         a[line_id][j]++;
    //         rt=dfs(findleft(line_id,col_id),col_id,line,col,0);
    //     }
    // }
    else{
        col_id++;
        if(col_id==col){
            col_id=0;
            line_id++;
        }
       if(dfs(line_id, col_id, line, col, 0)==-1){
            col_id--;
            if(col_id==-1){
                col_id=col-1;
                line_id--;
            }
            return -1;
        }
       return 1;

    }

}
int main()
{
    int line, col;
    cin >> line >> col;
    for (int i = 0; i < line; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> a[i][j];
        }
    }
    int line_id = 0, col_id = 0;
    while(line_id < line && col_id < col && a[line_id][col_id] == 0) {
        col_id++;
        if(col_id == col) {
            col_id = 0;
            line_id++;
        }
    }
        if (a[line_id][col_id] != 0)

        {
            int rt = 0;
            rt = dfs(line_id, col_id, line, col, 0);
            if (rt == -1)
            {
                 rt = dfs(line_id, col_id, line, col, 5);
            if (rt == -1)
            {
                rt = dfs(line_id, col_id, line, col, 1);
                if (rt == -1)
                {
                    rt = dfs(line_id, col_id, line, col, 2);
                    if (rt == -1)
                    {
                        rt = dfs(line_id, col_id, line, col, 3);
                        if (rt == -1)
                        {
                            std::cout << "No Solution" << endl;
                            return 0;
                        }
                    }
                }
            }}
        
        
    }
    int flag=0;
    //std::cout << "col_idES" << endl;
    for (int i = 0; i < line; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if(connection[i][j][0]||connection[i][j][1]||connection[i][j][2]||connection[i][j][3]==1)
            {std::cout << i+1<<" "<<j+1<<" "<<connection[i][j][0] << " " << connection[i][j][1] << " " << connection[i][j][2] << " " << connection[i][j][3] << endl;
        flag=1;}
        }
    }
    if(flag==0)
    std::cout<<"NO Solution"<<endl;
    return 0;
}