/* This is a code for COMP 201 assignment 3.
 * In this code, Floyd-Warshall algorithm is implemented
 * to find the shortest paths between any two cities
 * in a given graph of cities.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int INF = 1e7;  

/* Array of vertices. 
 * Each element of the str array contains a city name and 
 * its index in str becomes the city's numeric id.
 */
typedef struct vertices 
{
	// This attribute shows the size of dynamically allocated memory
	int size;
	// This attribute shows the number of cities in the array
	int city_count;
	// This attribute is the array of city names
	char (* str)[30];
} 
vertices;

/* Array of edges. 
 * Each element of the edge array contains the ids of two cities 
 * connected directy by a road and the length of the road.
 */
typedef struct edges 
{
	// This attribute shows the size of dynamically allocated memory
	int size;
	// This attribute shows the number of roads in the array
	int edge_count;
	// This attribute is the array of road information
	int (* edge)[3];
} 
edges;

vertices cities;

edges roads;

/* A two-dimensional array that shows 
 * the length of the shortest path connecting 
 * any two cities.
 */
int **city_graph;

/* A two-dimensional array that shows the direction 
 * to the shortest path between any two cities.
 */
int **shortest_paths;

/* A function that implements Floyd-Warshall algorithm. 
 * This algorithm finds the shortest path between 
 * any two vertices in a given graph.
 */
void floydWarshall()  
{  
	for (int k = 0; k < cities.city_count; k++) 
	{  
		for (int i = 0; i < cities.city_count; i++) 
		{  
			for (int j = 0; j < cities.city_count; j++) 
			{  

				// We cannot cross a road that doesn't exist  
				if ((city_graph[i][k] == INF) || (city_graph[k][j] == INF))  
				{
					continue;
				}  

				if (city_graph[i][j] > (city_graph[i][k] + city_graph[k][j])) 
				{  
					city_graph[i][j] = city_graph[i][k] + city_graph[k][j];  
					shortest_paths[i][j] = shortest_paths[i][k];  
				}  
			}  
		}  
	}  
} 

/* A function that initializes the values in 
 * city_graph and shortest_paths arrays.
 */
void initialise()  
{  
	for (int i = 0; i < cities.city_count; i++) 
	{  
		for (int j = 0; j < cities.city_count; j++) 
		{    

			// No edge between node i and j  
			if (city_graph[i][j] == INF)  
			{
				shortest_paths[i][j] = -1;
			}  
			else
			{
				shortest_paths[i][j] = j;
			}  
		}  
	}  
}

/* A function that inserts the name of a new city 
 * to the cities array.
 */
int insert_to_cities(char str[30]) 
{
	// Write your code here
	// Check if the city name already exists in the array 
	// If it does, return the array index of the city
for(int i=0; i<cities.city_count; i++){
  if(strcmp(str, cities.str[i])==0){
    return i;
  }
}
        cities.str=realloc(cities.str, cities.size + sizeof(char)*30);
        strcpy(&cities.str[cities.city_count][0], str);
        cities.size += 30;
        cities.city_count ++;
        return cities.city_count-1;
	// If the city name doesn't exist, it is inserted to the cities array, and
	// return the array index of the city

	// If the dynamically allocated size of cities array is not large enough, 
	// the size of cities array is enlarged and the city name is inserted 
	// to the newly added region

	// Return the array index of the city.
}

/* A function that looks up if a city name
 * is already in the cities array. 
 */
int lookup_string(char str[30]) 
{
	for(int i = 0; i < cities.city_count; i++) {
		if(strncmp(str, cities.str[i], 30) == 0)
			return i;
	}
	printf("city %s is not found\n", str);
	return -1;
}

void printPath(int u, int v)  
{  
	// Write your code here  
  int k = shortest_paths[u][v]; //first city along the route
  printf("%s ", cities.str[u]);
  while(k != v){
  printf("%s ", cities.str[k]);
  k = shortest_paths[k][v];
  }
  printf("%s\n", cities.str[v]);
  printf("%d\n", city_graph[u][v]);
} 

int main(int argc, char *argv[])
{
	// Write your code here
cities.str = malloc(sizeof(char)*30);
cities.size = 0;
cities.city_count = 0;
roads.edge = malloc(sizeof(int)*3);
roads.size = 0;
roads.edge_count = 0;
city_graph = (int**)malloc(sizeof(int*)*16);
shortest_paths = (int**)malloc(sizeof(int*)*16);
for(int i = 0; i < 16;i++) {
	city_graph[i] = (int*) malloc(sizeof(int) * 16);
	shortest_paths[i] = (int*) malloc(sizeof(int) * 16);

}

for(int i = 0;i < 16;i++) {
	for(int j = 0; j < 16; j++) {
		city_graph[i][j] = INF;
	}
}
	// Allocate memory regions dynamically to cities array 
	// and roads array.
FILE *fp;
char str[4096];

fp = fopen("input.txt"
 , "r"); 
 if(fp == NULL){
   printf("Couldn't open file.\n");
   return 1;
 }

 while(fgets(str, 4096, fp) != NULL){
   char* word1 = strtok(str, " ");
   char* word2 = strtok(NULL, " ");
   char* number = strtok(NULL, " ");
   strtok(number, "\n");
   int num = atoi(number);
   int index1 = insert_to_cities(word1);
   int index2 = insert_to_cities(word2);
   roads.edge=realloc(roads.edge, roads.size + sizeof(int)*3);
   roads.size = roads.size + sizeof(int)*3;
   roads.edge[roads.edge_count][0]=index1;
   roads.edge[roads.edge_count][1]=index2;
   roads.edge[roads.edge_count][2]=num;
   roads.edge_count += 1;
   city_graph[index1][index2]=num;
   city_graph[index2][index1]=num;
 }
	// Read and parse the input file. Insert the city names to cities array.
	// The index of the city name in the cities array becomes the city id. 
	// Insert city ids and road lengths to roads array.

	// Allocate memory regions dynamically to city_graph, 
	// distance, and shortest_paths arrays.

	// Initialize the values in city_graph array with road lengths, 
	// such that the value in city_graph[i][j] is the road length 
	// between cities i and j if these cities are directly connected 
	// by a road 
	// For cities m and n that are not connected directly by a road, 
	// the value in city_graph[m][n] will be INF, 
    // which is a large value like 10M, 
	// that is assumed to be infinite. 
	initialise();
	floydWarshall();
	while(1) {
    char city1[30];
    char city2[30];
		// prompt user to enter two city names
    printf("Enter two city names: ");
    scanf("%s%s", &city1, &city2);
    int ind1 = lookup_string(city1);
    int ind2 = lookup_string(city2);
    printPath(ind1, ind2);
		// print the shortest path between the two cities
		// print the length of the path
	}
for(int i=0; i<cities.city_count; i++){
   free(city_graph[i]);
   free(shortest_paths[i]);
}
  free(cities.str);
  free(roads.edge);

  fclose(fp);

  	return 0;	
}
