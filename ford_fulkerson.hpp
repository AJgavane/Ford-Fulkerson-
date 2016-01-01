#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stack>

#include <queue>
#include <cstdio>
#include <climits>
#include <fstream>
#include <list>
#include <cstdlib>
#include <time.h>

void getAdjacencyMatrix(int **adjacency_matrix, int num_of_veritces);

int getMaxFLowFordFulkerson(int **adjacency_matrix, int num_of_veritces, int source_index, int sink_index);

void getMinCut(int **residual_graph, int num_of_veritces, int source_index, int sink_index);

void diplayAdjacencyMatrix(int **adjacency_matrix, int num_of_veritces);

int getSinkIndex(int **adjacency_matrix, int num_of_veritces);

int getSourceIndex(int **adjacency_matrix, int num_of_veritces);

/*int breadthFirstSearch(int source_index, int sink_index, int **residual_graph, int *path, int num_of_veritces);*/
int depthFirstSearch(int source_index, int sink_index, int **residual_graph, std::vector<int> &path, int num_of_veritces);

void augment(int *flow, std::vector<int> &path, int source_index, int sink_index, int **residual_graph);

int min(int num1, int num2);

void UpdateResidualGraph(int **residual_graph, int **adjacency_matrix, int delta, int num_of_veritces);

void fordFulkerson(std::vector<std::pair<int, int> > pixel, int **adjacency_matrix, int num_of_veritces);

void getCapacity(int **adjacency_matrix, int num_of_vertices);

void installRandomCapacity(int **adjacency_matrix, int num_of_vertices);