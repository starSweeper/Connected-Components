/*
	Program that finds sets of connected components.
	
	Based of MST-Kruskal pseudo code, and connected-compnents pseudo code in text book.
	Using linked-list created for a diffrent assignment, and edited to fit this program.
*/


#include<iostream>
#include<fstream>
#include<string>
#include"SLL.h"

using namespace std;

int processFile(string, int[][50], char[]); //Opens the file, gets graph information and closes the file
int kruskal(int[][50], int, char[], SLList[]); //Finds connected components
SLList makeSet(char); //Creates a set with 1 element
bool findSet(SLList,SLList); //Sees if one set is apart of another set
SLList setUnion(SLList, SLList); //Joins two sets in holy matramony
void bouncer(SLList[], SLList, int&); //Checks to see if a set is worthy of joining the list of connected components
void printArray(SLList[], int); //Prints the list of connected components


int main(int argc, char *argv[]) {
	int graph[50][50];
	int vertexCount = 0;
	char vertexList[50];
	SLList connectedComponents[50];

	vertexCount = processFile(argv[1], graph, vertexList);
	int connectedCount = kruskal(graph, vertexCount, vertexList, connectedComponents);
	printArray(connectedComponents, connectedCount);

}

int processFile(string filePath, int graph[][50], char vertexList[]) {
	ifstream inputFile;
	int vertexCount = 1;
	char temp;

	inputFile.open(filePath);

	inputFile >> temp; //Read in the a
	vertexList[0] = temp;
	inputFile >> temp;
	while(temp != 'a') {
		vertexList[vertexCount] = temp;
		vertexCount++;
		inputFile >> temp;
	}

	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			inputFile >> graph[i][j];
		}
		inputFile >> temp;
	}

	inputFile.close();

	return vertexCount;
}

int kruskal(int graph[][50], int vertexCount, char vertexList[], SLList edges[]) {
	SLList verticies[50];
	int edgesCount = 0;

	//For each vertex in the graph
	for (int i = 0; i < vertexCount; i++) {
		verticies[i] = makeSet(vertexList[i]);
	}
	
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			//Find the edges
			if (graph[i][j] != -1) {
				if (!findSet(verticies[i],verticies[j])){
					verticies[i] = setUnion(verticies[i], verticies[j]);
					bouncer(edges, verticies[i], edgesCount); //Will add the set if it ought to be added. Will also update the edgesCount
				}
			}
		}
	}

	return edgesCount;
}

SLList makeSet(char element) {
	SLList newList;
	newList.sortedAdd(element);

	return newList;
}

bool findSet(SLList set1, SLList set2) {
	char tempSet[50]; //Only needed to satisfy parameter list for isInList

	for (int i = 0; i < set2.getAllElements(tempSet); i++) {
		if (set1.isInList(set2.getElement(i)) == false) {
			return false;
		}
	}

	return true;
}

SLList setUnion(SLList set1, SLList set2) {

	set1.addSet(&set2);

	return set1;
}

//Checks if a set should be added to the list or not
void bouncer(SLList list[], SLList set, int &count) {

	//Check to see if set is already in the list
	bool inList = false;
	for (int i = 0; i < count; i++) {
		if (findSet(list[i], set)) {
			inList = true;
		}
	}

	//Check to see if any of the list items are within the set
	if (!inList) {
		bool aListItemIsWithinSet = false;
		int theListItemWithinSet;
		for (int i = 0; i < count; i++) {
			if (findSet(set, list[i])) {
				aListItemIsWithinSet = true;
				theListItemWithinSet = i;
			}
		}
		if (aListItemIsWithinSet) {
			list[theListItemWithinSet] = set; //Replace the list item with the new set
		}
		else {
			list[count] = set;
			count++;
		}	
	}
}

void printArray(SLList toPrint[], int size) {
	int length;
	char elements[50];

	cout << size << " connected component(s) found:\n\n";
	for (int i = 0; i < size; i++) {
		length = toPrint[i].getAllElements(elements);
		cout << i + 1 << ": [";
		for (int j = 0; j < length - 1; j++) {
			cout << elements[j] << ", ";
		}
		cout << elements[length - 1] << "]" << endl;
	}

	cout << endl;
	system("pause");
}
