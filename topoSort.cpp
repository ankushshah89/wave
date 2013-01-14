#include<iostream>
#include<stdio.h>
#include <cstdlib>
#include <cstring>
using namespace std;
int count=0;
 static int *a=new int[4];
 
void dfs(int u,bool v[],bool matrix[][4])
{
 
    v[u]=true;
    for(int  i=0;i<4;i++)
        if(!v[i]&& matrix[u][i])
            dfs(i,v,matrix);
 
    a[count++]=u;
    }
 
int main()
{
    bool v[4];
    bool  matrix[4][4];
    memset(v, 0 ,sizeof(v));
    memset(matrix, 0, sizeof(matrix));
    matrix[0][3]=true;
    matrix[0][1] = true;
    matrix[1][2]=true;
    matrix[3][1]=true;
    matrix[3][2]=true;
    for(int i=0;i<4;i++)
        if(!v[i])
            dfs(i,v,matrix);
    for(int i=0;i<4;i++)
    cout<<a[3-i]<<"  ";
 
 
    return 0;
}
