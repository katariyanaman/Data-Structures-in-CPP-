#include<iostream>
#include<iomanip>
 
using namespace std;
 
void PrintMat(int **mat, int n)
{
	int i, j;
 
	cout<<"\n\n"<<setw(4)<<"";
	for(i = 0; i < n; i++)
		cout<<setw(3)<<"("<<i+1<<")";
	cout<<"\n\n";
 
	for(i = 0; i < n; i++)
	{
		cout<<setw(3)<<"("<<i+1<<")";
		for(j = 0; j < n; j++)
		{
			cout<<setw(4)<<mat[i][j];
		}
		cout<<"\n\n";
	}
}
 
int main()
{
	int i, v, e, j, v1, v2;
 
	cout<<"Enter the number of vertexes of the graph: ";
	cin>>v;
 
	int **graph;
	graph = new int*[v];
 
	for(i = 0; i < v; i++)
	{
		graph[i] = new int[v];
		for(j = 0; j < v; j++)graph[i][j] = 0;
	}
 
	cout<<"\nEnter the number of edges of the graph: ";
	cin>>e;
 
	for(i = 0; i < e; i++)
	{
		cout<<"\nEnter the vertex pair for edge "<<i+1;
		cout<<"\nV(1): ";
		cin>>v1;
		cout<<"V(2): ";
		cin>>v2;
 
		graph[v1-1][v2-1] = 1;
		graph[v2-1][v1-1] = 1;
	}
 
	PrintMat(graph, v);
}
