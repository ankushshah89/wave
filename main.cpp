#include <iostream>
#include <list>
#include <fstream>

using namespace std;

#define MAXIMUM_NODES 100


int no_of_vertices, no_of_edges;
int capacity_matrix[MAXIMUM_NODES][MAXIMUM_NODES];
int flow_matrix[MAXIMUM_NODES][MAXIMUM_NODES];
int vertices[MAXIMUM_NODES][3];
bool visited_vertices[MAXIMUM_NODES];
int topoSorted[MAXIMUM_NODES],topoCount = 0;	

void initialise();
int incoming_flow(int);
int outgoing_flow(int);
void print_adj_list();
void print_adj_matrix();
void start_wave();
void increase_flow();
void decrease_flow();
void dfs(int );

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
	
	vertices[0][0] = 0; //blocked initially
	vertices[0][1] = 0;
	vertices[0][2] = 0; 	
	for(int i=1;i<no_of_vertices;i++)
	{
		vertices[i][0] = 1; //unblocked initially
		vertices[i][1] = 0;
		vertices[i][2] = 0;
	}	
	
	for(int i=0;i<no_of_vertices;i++)
		visited_vertices[i] = false;
	
}

void print_adj_matrix()
{	
	cout<<"\nFlow matrix is:\n";
	for(int i=0;i<no_of_vertices;i++)
	{
		for(int j=0;j<no_of_vertices;j++)
		{	
			cout<<flow_matrix[i][j]<<"  ";
		}
		cout<<endl;
	}
}

void dfs(int u)
{
    visited_vertices[u]=true;
    for(int  i=0;i<no_of_vertices;i++)
    {
        if((!visited_vertices[i]) && capacity_matrix[u][i] > 0)
	{
            dfs(i);
	}
    }
    topoSorted[topoCount++]=u;
}

void print_adj_list()
{	
	cout<<"\nFlow diagram is:\n";
	for(int i=0;i<no_of_vertices;i++)
	{
		for(int j=0;j<no_of_vertices;j++)
		{	
			if(flow_matrix[i][j]!=0)
				cout<<i<<" "<<j<<" "<<flow_matrix[i][j]<<endl;
		}
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
	int i;
	for(int r=0;r<no_of_vertices;r++)
	{
		i = topoSorted[no_of_vertices-r-1];
		
		//scan topologically all vertices except s and t.
		if (i == 0 || i == (no_of_vertices-1))
			continue;
		balanced = true;
		fin = incoming_flow(i);
		fout = outgoing_flow(i);
		if(vertices[i][0] == 1 && fin  != fout )
		{
			balanced =false;
			//attempt to balance the node
			for(int j=0;j<no_of_vertices  > 0;j++)
			{
				//check if j is a neighbor
				if(capacity_matrix[i][j] > 0)
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
	int j;
	for(int r=no_of_vertices-1;r>=0;r--)
	{
		j = topoSorted[no_of_vertices - r - 1];
		//scan topologically all vertices except s and t.
		if (j == 0 || j == (no_of_vertices-1))
			continue;	
		fin = incoming_flow(j);
		fout = outgoing_flow(j);	
		if(vertices[j][0] == 0 && fin != fout )
		{
			for(int i=0;i<no_of_vertices;i++)
			{
				//check if i and j are neighbor
				if(capacity_matrix[i][j] > 0)
				{
					subtract_flow = min(flow_matrix[i][j],fin - fout);
					flow_matrix[i][j] = flow_matrix[i][j] - subtract_flow;
					fin = fin - subtract_flow;
				}
			}	
		}
	}	
	
	//if there an unblocked, unbalanced vertex other than t call increase flow_matrix
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
	//ifstream fin;
	//fin.open("../testcases/tc0");
	cin>>no_of_vertices>>no_of_edges;
	int v,w,capacity;
	initialise();
	for(int i=0;i<no_of_edges;i++)
	{
		cin>>v>>w>>capacity;
		capacity_matrix[v][w] = capacity;
	}

	
	//do the topological sorting
	for(int i=0;i<no_of_vertices;i++)
		if(!visited_vertices[i])
			dfs(i);

	//print the topo order
	cout<<"Topoligical Order:\n";
	for(int i=0;i<no_of_vertices;i++)
		cout<<topoSorted[no_of_vertices -i - 1]<<" ";
	
	start_wave();
	increase_flow();
	print_adj_list();
	
	for(int j=0;j<no_of_vertices;j++)
	{
		blocking_flow = blocking_flow + flow_matrix[0][j];
	}
	cout<<"\nBlocking Flow is "<<blocking_flow<<endl;
	//fin.close();
	
}
