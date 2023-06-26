/* The following C++ program takes inputs for a graph's number of vertices,
   number of edges, and vertex pairs for each edge, and then prints the incidence list representation of the graph. */

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
 
	cout<<"\n\nThe incidence list representation for the given graph: ";
	for(i = 0; i < e; i++)
	{
		cout<<"\n\tE("<<i+1<<") -> { ";
		cout<<"V("<<edge[i][0]<<") , "<<"V("<<edge[i][1]<<")";
		cout<<" }";
	}
}
