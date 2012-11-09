#include <iostream>
#include <list>

using namespace std;

#define MAXIMUM_NODES 100
int no_of_vertices;
int capacity_matrix[MAXIMUM_NODES][MAXIMUM_NODES];
int flow_matrix[MAXIMUM_NODES][MAXIMUM_NODES];
int vertices[MAXIMUM_NODES][3];
	

void initialise()
{
	for(int i=0;i<no_of_vertices;i++)
	{
		for(int j=0;j<no_of_vertices;j++)
		{	
			capacity_matrix[i][j] = 0;
			flow_matrix[i][j] = 0;
			
		}
	}
	
	vertices[0][0] = 0;
	vertices[0][1] = 0;
	vertices[0][1] = 0;	
	for(int i=1;i<no_of_vertices;i++)
	{
		vertices[i][0] = 1;
		vertices[i][1] = 0;
		vertices[i][2] = 0;
	}	
}

void print()
{	
	for(int i=0;i<no_of_vertices;i++)
	{
		for(int j=0;j<no_of_vertices;j++)
		{	
			cout<<capacity_matrix[i][j]<<"  ";
			
		}
		cout<<endl;
	}
	
}

int main(int argc, char **argv) 
{
	int no_of_lines;
	cin>>no_of_lines;
	cin>>no_of_vertices;
	int v,w,capacity;
	initialise();
	for(int i=1;i<no_of_lines;i++)
	{
		cin>>v>>w>>capacity;
		capacity_matrix[v][w] = capacity;
	}
	
	print();
	
}
