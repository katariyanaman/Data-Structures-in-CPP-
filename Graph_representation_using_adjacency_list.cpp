/* The following C++ program takes inputs for a graph's number of vertices and edges,
   and vertex pairs for each edge. It then prints the adjacency list representation of the graph. */

#include<iostream>
 
using namespace std;
 
int main()
{
	int i, v, e, j, count;
 
	cout<<"Enter the number of vertexes of the graph: ";
	cin>>v;
	cout<<"\nEnter the number of edges of the graph: ";
	cin>>e;
	int edge[e][2];
 
	for(i = 0; i < e; i++)
	{
		cout<<"\nEnter the vertex pair for edge "<<i+1;
		cout<<"\nV(1): ";
		cin>>edge[i][0];
		cout<<"V(2): ";
		cin>>edge[i][1];
	}
 
	cout<<"\n\nThe adjacency list representation for the given graph: ";
	for(i = 0; i < v; i++)
	{
		count = 0;
		cout<<"\n\t"<<i+1<<"-> { ";
		for(j = 0; j < e; j++)
		{
			if(edge[j][0] == i+1)
			{
				cout<<edge[j][1]<<"  ";
				count++;
			}
			else if(edge[j][1] == i+1)
			{
				cout<<edge[j][0]<<"  ";
				count++;
			}
			else if(j == e-1 && count == 0)
				cout<<"Isolated Vertex!";
		}
		cout<<" }";
	}
}
