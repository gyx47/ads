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
int findright(int x, int y, int col)
{
    while (y < col)
    {
        if (a[x][y] != 0)
            return y;
        y++;
    }
    return -1;
}
int finddown(int x, int y, int line)
{
    while (x < line)
    {
        if (a[x][y] != 0)
            return x;
        x++;
    }
    return -1;
}
int findleft(int x, int y)
{
    while (y >= 0)
    {
        if (a[x][y] != 0)
            return y;
        y--;
    }
    return -1;
}
int findup(int x, int y)
{
    while (x >= 0)
    {
        if (a[x][y] != 0)
            return x;
        x--;
    }
    return -1;
}
void connect(int x, int y, int i, int j, int connection[][10][4])
{
    if (x == i)
    {
        if (y < j)
        {
            connection[x][y][1] = 1;
            connection[i][j][0] = 1;
        }
        else
        {
            connection[x][y][0] = 1;
            connection[i][j][1] = 1;
        }
    }
    else
    {
        if (x < i)
        {
            connection[x][y][3] = 1;
            connection[i][j][2] = 1;
        }
        else
        {
            connection[x][y][2] = 1;
            connection[i][j][3] = 1;
        }
    }
}
void disconnect(int x, int y, int i, int j, int connection[][10][4])
{
    if (x == i)
    {
        if (y < j)
        {
            connection[x][y][0] = 0;
            connection[i][j][1] = 0;
        }
        else
        {
            connection[x][y][1] = 0;
            connection[i][j][0] = 0;
        }
    }
    else
    {
        if (x < i)
        {
            connection[x][y][3] = 0;
            connection[i][j][2] = 0;
        }
        else
        {
            connection[x][y][2] = 0;
            connection[i][j][3] = 0;
        }
    }
}
int dfs(int x, int y, int line, int col, int n)
{
    int i, j;
    if (x < 0 || x >= line || y < 0 || y >= col)
        return 1;
    if (a[x][y] == 0)
        return 1;
    int rt = 0; // 目前最大的问题是，如果dfs返回的是1，那就固定了不调整了，哪怕不先从右边查找就可能可以成功,甚至右边固定，下方不固定的模式也要搜索一遍。
    if (a[x][y] != 0 && (n == 0 || n == 5) && (i = findright(x, y+1, col)) != -1)
    {cout<<"run"<<x<<endl;
        connect(x, y, i, y, connection);
        n++;
        if (n == 6)
            n = 2;
        a[x][y]--;
        a[i][y]--;
        rt = dfs(i, y, line, col, 0);
        if (rt == -1)
        {//
            rt = dfs(i, y, line, col, 1);
            if (rt == -1)
            {
                rt = dfs(x, j, line, col, 5);
                if (rt == -1)
                {
                    rt = dfs(x, j, line, col, 1);
                    if (rt == -1)
                    {
                        rt = dfs(x, j, line, col, 2);
                        if (rt == -1)
                        {
                            rt = dfs(x, j, line, col, 3);
                            if (rt == -1)
                            {
                                a[x][y]++;
                                a[x][j]++;
                                disconnect(x, y, x, j, connection);
                            }
                        }
                    }
                }
            }
        }
        else
        {
        }
        // a[x][y]++;
    }

    if (a[x][y] != 0 && n == 1 && (j = finddown(x+1, y, line)) != -1)
    {
        connect(x, y, x, j, connection);
        n++;
        a[x][y]--;
        a[x][j]--;
        // rt=dfs(x,j,line,col,0);

        rt = dfs(x, j, line, col, 0);
        if (rt == -1)
        {
            rt = dfs(x, j, line, col, 5);
            if (rt == -1)
            {
                rt = dfs(x, j, line, col, 1);
                if (rt == -1)
                {
                    rt = dfs(x, j, line, col, 2);
                    if (rt == -1)
                    {
                        rt = dfs(x, j, line, col, 3);
                        if (rt == -1)
                        {
                            a[x][y]++;
                            a[x][j]++;
                            disconnect(x, y, x, j, connection);
                        }
                    }
                }
            }
        }
        // a[x][y]++;
    }
    if (a[x][y] != 0 && n == 2 && (i = findleft(x, y-1)) != -1)
    {
        connect(x, y, i, y, connection);
        n++;
        a[x][y]--;
        a[i][y]--;
        //  rt=dfs(i,y,line,col,0);
        rt = dfs(i, y, line, col, 0);
        if (rt == -1)
        {
            rt = dfs(x, j, line, col, 5);
            if (rt == -1)
            {
                rt = dfs(x, j, line, col, 1);
                if (rt == -1)
                {
                    rt = dfs(x, j, line, col, 2);
                    if (rt == -1)
                    {
                        rt = dfs(x, j, line, col, 3);
                        if (rt == -1)
                        {
                            a[x][y]++;
                            a[x][j]++;
                            disconnect(x, y, x, j, connection);
                        }
                    }
                }
            }
        }
        //  a[x][y]++;
    }
    if (a[x][y] != 0 && n == 3 && (j = findup(x-1, y)) != -1)
    {
        connect(x, y, x, j, connection);
        a[x][y]--;
        a[x][j]--;
        rt = dfs(x, j, line, col, 0);
        //  rt=dfs(i,y,line,col,0);
        if (rt == -1)
        {
            rt = dfs(x, j, line, col, 5);
            if (rt == -1)
            {
                rt = dfs(x, j, line, col, 1);
                if (rt == -1)
                {
                    rt = dfs(x, j, line, col, 2);
                    if (rt == -1)
                    {
                        rt = dfs(x, j, line, col, 3);
                        if (rt == -1)
                        {
                            a[x][y]++;
                            a[x][j]++;
                            disconnect(x, y, x, j, connection);
                        }
                    }
                }
            }
        }
        //  a[x][y]++;
    }
    if (a[x][y] != 0)
        return -1;
    //     if (connection[x][y][1]==1) {
    //         j=finddown(x,y,line);
    //         disconnect(x,y,x,j,connection);
    //         a[x][j]++;
    //         rt=dfs(findleft(x,y),y,line,col,0);
    //     }
    // }

    return 1;
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
    int x = 0, y = 0;
    while (x < line && y < col)
    {
        if (a[x][y] != 0)

        {
            int rt = 0;
            rt = dfs(x, y, line, col, 0);
            if (rt == -1)
            {
                 rt = dfs(x, y, line, col, 5);
            if (rt == -1)
            {
                rt = dfs(x, y, line, col, 1);
                if (rt == -1)
                {
                    rt = dfs(x, y, line, col, 2);
                    if (rt == -1)
                    {
                        rt = dfs(x, y, line, col, 3);
                        if (rt == -1)
                        {
                            cout << "NO" << endl;
                            return 0;
                        }
                    }
                }
            }}
        }
        y++;
        if(y==col){
            y=0;
            x++;
        }
        
    }
    cout << "YES" << endl;
    for (int i = 0; i < line; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if(connection[i][j][0]||connection[i][j][1]||connection[i][j][2]||connection[i][j][3]==1)
            cout << i<<" "<<j<<" "<<connection[i][j][0] << " " << connection[i][j][1] << " " << connection[i][j][2] << " " << connection[i][j][3] << endl;
        }
    }
    return 0;
}