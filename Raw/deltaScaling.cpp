#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <climits>
#include <fstream>
#include <list>
#include "function.h"
using namespace std;
#define db cout<<"here\n"

int **adjacency_matrix;
int num_of_veritces;
ifstream fin;

int main(int argc, char const *argv[])
{
	/* Variable declarations*/
	int sink_index = 0, source_index = 0;
	int flow;


	string filename;
	if(argc != 2){
		cout << "Enter the file name : ";
		cin >> filename;
	} else {
		filename = argv[1];
	}

	fin.open(filename.c_str(), ios::in);
	
	fin >> num_of_veritces;
	cout << "Number of Vertices : "<< num_of_veritces << endl;
	//  create adjacency matric
	adjacency_matrix = new int*[num_of_veritces];
	for (int i = 0; i < num_of_veritces; ++i)
	{
		adjacency_matrix[i] = new int[num_of_veritces];
	}

	// initializing adjacency matrix
	for (int i = 0; i < num_of_veritces; ++i)
	{
		for (int j = 0; j < num_of_veritces; ++j)
		{
			adjacency_matrix[i][j] = 0;
		}
	}

	getAdjacencyMatrix(adjacency_matrix, num_of_veritces);

	/* getting source and sink from the graph */
	sink_index = getSinkIndex(adjacency_matrix, num_of_veritces);
		cout << "sink index : " << sink_index << endl;
	if(sink_index == -1){
		cout<< "ERROR: Graph contains no Sink: \n";
		return 0;
	}
	source_index = getSourceIndex(adjacency_matrix, num_of_veritces);
		cout << "source index : " << source_index << endl;
	if(source_index == -1){
		cout << "ERROR: Graph contains no Source \n";
		return 0;
	}
	/*  done getting source and sink from the graph*/
	cout << "Given ";
	diplayAdjacencyMatrix(adjacency_matrix, num_of_veritces);

	flow = getMaxFLowFordFulkerson(adjacency_matrix, num_of_veritces, source_index, sink_index);
		cout << "Max Flow is : " << flow <<endl;
/*	getMinCut(adjacency_matrix, num_of_veritces, source_index, sink_index);*/

	return 0;
}


void getAdjacencyMatrix(int **adjacency_matrix, int num_of_veritces){
	for (int i = 0; i < num_of_veritces; ++i)
	{
		for (int j = 0; j < num_of_veritces; ++j)
		{
			fin >> adjacency_matrix[i][j];
		}
	}
}

void diplayAdjacencyMatrix(int **adjacency_matrix, int num_of_veritces){
	cout << "Adjacency Matrix : \n";
	cout << "**************************************************************\n";
	for (int i = 0; i < num_of_veritces; ++i)
	{
		for (int j = 0; j < num_of_veritces; ++j)
		{
			cout << adjacency_matrix[i][j] << "\t" ;
		}
		cout << endl;
	}
	cout << "**************************************************************\n";
}

int getSinkIndex(int **adjacency_matrix, int num_of_veritces){
	vector<int> candidate_sink;
	for(int i = 0 ; i < num_of_veritces; i++)
		candidate_sink.push_back(i);
		
	while(1)
	{
		if(candidate_sink.size() == 1)
			break;
		if(adjacency_matrix[candidate_sink[0]][candidate_sink[1]] != 0 ){
		/*	cout << adjacency_matrix[candidate_sink[0]][candidate_sink[1]] << " ";
			cout << "erase node : " << candidate_sink[0] << endl;*/
			candidate_sink.erase( candidate_sink.begin() + 0 );
		} else if(adjacency_matrix[candidate_sink[0]][candidate_sink[1]] == 0 ){
		/*	cout << adjacency_matrix[candidate_sink[0]][candidate_sink[1]] << " ";
			cout << "erase node : " << candidate_sink[1] << endl;*/
			candidate_sink.erase( candidate_sink.begin() + 1);
		}
		
	}
	int flag = 1;
	for (int i = 0; i < num_of_veritces; ++i)
	{
		if(adjacency_matrix[candidate_sink[0]][i] != 0)
			flag = 0;
	}
	if (flag)
	{
		return candidate_sink[0];
	}
	cout << " no sink exits in the graph \n";
	return -1;
}

int getSourceIndex(int **adjacency_matrix, int num_of_veritces){
	int flag = 1;	
	for(int i = 0 ; i < num_of_veritces; i++){
		flag = 1;
		for(int j = 0 ; j < num_of_veritces ; j++){
			if(adjacency_matrix[j][i] != 0){
				flag = 0;
				continue;
			}
		}
		if(flag)
			return i;
	}
	return -1;
}

int getMaxFLowFordFulkerson(int **adjacency_matrix, int num_of_veritces, int source_index, int sink_index){
	int flow = 0, path_flow;
	int **residual_graph;
	int delta = 1;
	 int **graph;
	vector<int> path;				// used to store path

	//path = new int[num_of_veritces];
	residual_graph = new int*[num_of_veritces];
	 graph = new int*[num_of_veritces];
	for (int i = 0; i < num_of_veritces; ++i)
	{
		residual_graph[i] = new int[num_of_veritces];
		 graph[i] = new int[num_of_veritces];
		//path[i] = 0;
		path.push_back(0);
	}
	// cout << " size of path : "<< path.size() << endl;

	// initially f(e) = 0 	for all edges in G;
	for (int i = 0; i < num_of_veritces; ++i)
	{
		for (int j = 0; j < num_of_veritces; ++j)
		{
			graph[i][j] = adjacency_matrix[i][j];
		}
	}

	// intialize residual graph capacity

	for (int i = 0; i < num_of_veritces; ++i)
	{
		for (int j = 0; j < num_of_veritces; ++j)
		{
			residual_graph[i][j] = adjacency_matrix[i][j];
			while( 2* delta < residual_graph[i][j]){
				delta *= 2;
			}
		}
	}
	
	while(delta >= 1){
		cout << "delta value: " << delta << endl;
		UpdateResidualGraph(residual_graph, graph, delta, num_of_veritces);
		
		//diplayAdjacencyMatrix(residual_graph, num_of_veritces);


		while( depthFirstSearch(source_index, sink_index, residual_graph, path ,num_of_veritces) == 1){

			//diplayAdjacencyMatrix(residual_graph, num_of_veritces);


			// get max flow of the path
			augment(&path_flow, path, source_index, sink_index, residual_graph);
				cout <<  "Path_flow : " << path_flow << endl;

			flow += path_flow;

			// Update residual graph
			for (int vertex	= sink_index ; vertex != source_index; vertex = path[vertex]){
				residual_graph[path[vertex]][vertex] -= path_flow;
				residual_graph[vertex][path[vertex]] += path_flow;
				graph[path[vertex]][vertex] -= path_flow;
				graph[vertex][path[vertex]] += path_flow;
					
			}
			diplayAdjacencyMatrix(residual_graph, num_of_veritces);
			
			// break;
		}

		delta /= 2;
	}

	// mincut A -> B	
		getMinCut(residual_graph, num_of_veritces, source_index, sink_index);
	return flow;
}

void augment(int *path_flow, vector<int> &path, int source_index, int sink_index, int **residual_graph){
	*path_flow = INT_MAX;
	for (int vertex	= sink_index ; vertex != source_index; vertex = path[vertex])
	{
		*path_flow = min(*path_flow, residual_graph[path[vertex]][vertex]);
	}
}

int min(int num1, int num2){
	if(num1 < num2)
		return num1;
	else 
		return num2;
}

int depthFirstSearch(int source_index, int sink_index, int **residual_graph, vector<int> &path, int num_of_veritces){

// create an array for visited nodes and initialize them to 0
	path.clear();
	int *visited = new int[num_of_veritces];
	for(int i = 0 ; i < num_of_veritces; i++){
		visited[i] = 0;
		path.push_back(0);
	}
	

	// create stack
	stack<int> S;
	int vertex = source_index;

	S.push(vertex);

	while(!S.empty()){
		vertex = S.top();
		S.pop();
		if(visited[vertex] == 0){
			visited[vertex] = 1;
			for( int i = 0 ; i < num_of_veritces ; i++){
				if(visited[i] == 0  && residual_graph[vertex][i] > 0){
					path[i] = vertex;
					S.push(i);
				}
			}
		}
		if(vertex == sink_index)
			break;
	}

	/*cout<<"Path DFS : ";
		for (int vertex	= 0 ; vertex < path.size() ; vertex++)
			cout << path[vertex] << " ";*/


		// cout << "visited[sink_index] : " << visited[sink_index] << endl;
	return visited[sink_index];

}

void getMinCut(int **residual_graph, int num_of_veritces, int source_index, int sink_index){

	int vertex;
	int *visited = new int(num_of_veritces);
	for(int i = 0 ; i < num_of_veritces ; i++){
		visited[i] = 0;
	}
	// create queue
	queue<int> Q;
	Q.push(source_index);
	visited[source_index] = 1;

	while(!Q.empty()){
		vertex = Q.front();
		Q.pop();
		for(int i = 0 ;  i < num_of_veritces; i++){
			if(visited[i] == 0 && residual_graph[vertex][i] > 0){
				Q.push(i);
				visited[i] = 1;
			}
		}
	}
	cout<< "Min Cut: { ";
	for(int i = 0 ; i < num_of_veritces ; i++){
		//cout << visited[i] << " " ;
		if(visited[i] == 1)
			cout<< i << " ";
	}

	cout << "} -> { ";
	for(int i = 0 ; i < num_of_veritces ; i++){
		//cout << visited[i] << " " ;
		if(visited[i] == 0)
			cout<< i << " ";
	}

	cout << "}"<<endl;

	return;
}


void UpdateResidualGraph(int **residual_graph, int **adjacency_matrix, int delta, int num_of_veritces){
	for (int i = 0; i < num_of_veritces; ++i)
	{
		for (int j = 0; j < num_of_veritces; ++j)
		{
			if(adjacency_matrix[i][j] < delta)
				residual_graph[i][j] = 0;
			else 
				residual_graph[i][j] = adjacency_matrix[i][j];
		}
	}
	//diplayAdjacencyMatrix(residual_graph, num_of_veritces);
}