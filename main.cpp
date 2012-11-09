#include <iostream>
#include <list>
#include <fstream>

using namespace std;

#define MAXIMUM_NODES 100


int no_of_vertices;
int capacity_matrix[MAXIMUM_NODES][MAXIMUM_NODES];
int flow_matrix[MAXIMUM_NODES][MAXIMUM_NODES];
int vertices[MAXIMUM_NODES][3];
	
void initialise();
int incoming_flow(int);
int outgoing_flow(int);
void print();
void start_wave();
void increase_flow();
void decrease_flow();

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
			cout<<flow_matrix[i][j]<<"  ";
			
		}
		cout<<endl;
	}
}


void start_wave()
{
	for(int j=0;j<no_of_vertices;j++)
	{
		flow_matrix[0][j] = capacity_matrix[0][j];
	}
}

void increase_flow()
{
	bool balanced;
	int add_flow;
	int fin,fout;
	for(int i=1;i<no_of_vertices-1;i++)
	{
		balanced = true;
		fin = incoming_flow(i);
		fout = outgoing_flow(i);
		if(vertices[i][0] == 1 && fin  != fout )
		{
			balanced =false;
			//attempt to balance the node
			for(int j=0;j<no_of_vertices;j++)
			{
				//if the vertex j is unblocked 
				if( vertices[j][0] == 1 )
				{
					add_flow = min(capacity_matrix[i][j]-flow_matrix[i][j],fin - fout);
					flow_matrix[i][j] = flow_matrix[i][j] + add_flow;
					fout = fout + add_flow;
				}
				if(fin == fout)
				{
					balanced = true;
					break;
				}
			}
		}
		
		//if unable to balance the vertex
		if(balanced == false)
		{
			vertices[i][0] = 0;
		}
	}
	
	//If there is blocked, unbalanced vertex other than s, call decrease flow_matrix
	for(int i=1;i<no_of_vertices;i++)
	{
		if(vertices[i][0] == 0 && incoming_flow(i) != outgoing_flow(i) )
			decrease_flow();
	}
}

int incoming_flow(int vertex_id)
{
	int fin = 0;
	for(int i=0;i<no_of_vertices;i++)
	{
		fin = fin + flow_matrix[i][vertex_id];
	}
	return fin;
}

int outgoing_flow(int vertex_id)
{
	int fout = 0;
	for(int i=0;i<no_of_vertices;i++)
	{
		fout = fout + flow_matrix[vertex_id][i];
	}
	return fout;
}
	

void decrease_flow()
{
	int subtract_flow;
	int fin,fout;
	for(int j=no_of_vertices-2;j>0;j--)
	{
		fin = incoming_flow(j);
		fout = outgoing_flow(j);	
		if(vertices[j][0] == 0 && fin != fout )
		{
			for(int i=0;i<no_of_vertices;i++)
			{
				subtract_flow = min(flow_matrix[i][j],fin - fout);
				flow_matrix[i][j] = flow_matrix[i][j] - subtract_flow;
				fin = fin - subtract_flow;
			}	
		}
	}	
	
	//if htere an unblocked, unbalanced vertex other than t call increase flow_matrix
	for(int i=0;i<no_of_vertices-1;i++)
	{
		if(vertices[i][0] == 1 && incoming_flow(i) != outgoing_flow(i) )
			increase_flow();
	}
}


int main(int argc, char **argv) 
{
	int blocking_flow =0;
	int no_of_lines;
	ifstream fin;
	fin.open("../tc");
	fin>>no_of_lines;
	fin>>no_of_vertices;
	int v,w,capacity;
	initialise();
	for(int i=1;i<no_of_lines;i++)
	{
		fin>>v>>w>>capacity;
		capacity_matrix[v][w] = capacity;
	}
	
	start_wave();
	increase_flow();
	print();
	
	for(int j=0;j<no_of_vertices;j++)
	{
		blocking_flow = blocking_flow + flow_matrix[0][j];
	}
	cout<<"\nBlocking Flow is "<<blocking_flow;
	fin.close();
	
}
