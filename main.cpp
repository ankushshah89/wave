#include <iostream>
#include <list>

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


void start_wave()
{
	for(int i=0;i<no_of_vertices;i++)
	{
		flow_matrix[0][i] = capacity_matrix[0][i];
	}
}

void increase_flow()
{
	bool balanced;
	int add_flow;
	for(int i=1;i<no_of_vertices-1;i++)
	{
		balanced = true;
		if(vertices[i][0] == 1 && incoming_flow(i) != outgoing_flow(i) )
		{
			balanced =false;
			//attempt to balance the node
			for(int j=0;j<no_of_vertices && vertices[j][0] == 1;j++)
			{
				add_flow = min(capacity_matrix[i][j]-flow_matrix[i][j],incoming_flow(i) - outgoing_flow(i));
				flow_matrix[i][j] = flow_matrix[i][j] + add_flow;
				
				if(incoming_flow(i) != outgoing_flow(i))
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
	for(int j=no_of_vertices-2;j>0;j--)
	{
		if(vertices[j][0] == 0 && incoming_flow(j) != outgoing_flow(j) )
		{
			for(int i=0;i<no_of_vertices;i++)
			{
				subtract_flow = min(flow_matrix[i][j],incoming_flow(j) - outgoing_flow(j));
				flow_matrix[i][j] = flow_matrix[i][j] - subtract_flow;
			}	
		}
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
	
	start_wave();
	increase_flow();
	decrease_flow();
	print();
}
