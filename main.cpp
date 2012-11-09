#include <iostream>
#include <list>

using namespace std;


//structure for edge
struct EDGE
{
	unsigned int capacity;
	unsigned int flow;
};

//structure for a vertex
struct NODE
{
	unsigned int id;
	bool isBlocked;
	int fin;
	int fout;
	list<EDGE*> incoming_edges;
	list<EDGE*> outgoing_edges;
};  

int main(int argc, char **argv) 
{
	std::cout << "Hello, world! :))" << std::endl;
	return 0;
}
