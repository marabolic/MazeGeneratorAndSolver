#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX 40
#define scanf_s scanf

typedef struct egde {
	int pointA;
	int pointB;
}Edge;


typedef struct elem { 
	Edge* e;
	struct elem* next;
} Elem;


#include <stdio.h>
#include <stdlib.h>
#define DIM 20
#define QMAX 100

int Q[QMAX];
//implementacija reda

void insertQ(int Q[], int x, int n, int *rear, int *front) {
	*rear = (*rear + 1) % n;
	if (*front == *rear) printf("ne moze se dodati element\n");
	else Q[*rear] = x;
	if (*front == -1) *front = 0;
}
int deleteQ(int Q[], int cnt, int *front, int *rear) {
	int x;
	if (*front == -1) {
		printf("ne moze se obrisati element\n");
		return;
	}
	else {
		x = Q[*front];
		if (*front == *rear) *front = *rear = -1;
		else *front = *front % cnt + 1;
	}
	return x;
}
int QueueIsEmpty(int Q[], int front, int rear) {
	if (front == -1) return 1;
	else return 0;
}

//kraj implementacije reda

//pravljenje lavirinta
int nodeID(int columns, int i, int j) {
	return i * columns + j;
}

void addEdge(int **mat, int pointA, int pointB) {
	mat[pointA][pointB] = 1;
	mat[pointB][pointA] = 1;
}

void removeEdge(int **mat, int pointA, int pointB) {
	mat[pointA][pointB] = 0;
	mat[pointB][pointA] = 0;
}

void addNode(int *nodes, int newNode) {
	nodes[newNode] = 1;
}

int setEntrance(int columns) {
	printf("postavi ulaz\n");
	int entrI, entrJ;
	scanf("%d%d", &entrI, &entrJ);
	int entrance = nodeID(columns, entrI, entrJ);
	return entrance;
}

int setExit(int columns) {
	printf("postavi izlaz\n");
	int extI, extJ;
	scanf("%d%d", &extI, &extJ);
	int exit = nodeID(columns, extI, extJ);
	return exit;
}

int isEntr(int node, int entr) {
	int flag = 0;
	if (node == entr) 
		flag = 1;
	return flag;
}

int isExit(int node, int exit) {
	int flag = 0;
	if (node == exit)
		flag = 1;
	return flag;
}

void removeNode(int *nodes, int newNode) {
	nodes[newNode] = 0;
}

int getNode(int *nodes, int node) {
	return nodes[node];
}

Elem *addEdges(Elem *edges, int *numOfEdges, int newNode, int i, int j, int rows, int columns) {  
	if (i > 0) {
		Elem *up = (Elem*)malloc(sizeof(Elem));
		up->e = (Edge*)malloc(sizeof(Edge));
		int pointB = nodeID(columns, i - 1, j);
		up->e->pointB = pointB;
		up->e->pointA = newNode;
		up->next = edges;
		edges = up;
		*numOfEdges += 1;
	}
	if (j > 0) {
		Elem *left = (Elem*)malloc(sizeof(Elem));
		left->e = (Edge*)malloc(sizeof(Edge));
		int pointB = nodeID(columns, i, j - 1);
		left->e->pointB = pointB;
		left->e->pointA = newNode;
		left->next = edges;
		edges = left;
		*numOfEdges += 1;
	}
	if (j < columns - 1) {
		Elem *right = (Elem*)malloc(sizeof(Elem));
		right->e = (Edge*)malloc(sizeof(Edge));
		int pointB = nodeID(columns, i, j + 1);
		right->e->pointB = pointB;
		right->e->pointA = newNode;
		right->next = edges;
		edges = right;
		*numOfEdges += 1;
	}
	if (i < rows - 1) {
		Elem *down = (Elem*)malloc(sizeof(Elem));
		down->e = (Edge*)malloc(sizeof(Edge));
		int pointB = nodeID(columns, i + 1, j);
		down->e->pointB = pointB;
		down->e->pointA = newNode;
		down->next = edges;
		edges = down;
		*numOfEdges += 1;
	}
	return edges;
}

void print(int **mat, int rows, int columns, int entrance, int exit) { 
	char wall = atoi("219"), pass = ' ', entr = 'o', ext = 'x', cell = '\'';
	for (int i = 0; i < columns; i++)
		printf("%c%c", wall, wall);
	printf("%c\n", wall);
	for (int i = 0; i < rows - 1; i++) {
		printf("%c", wall);
		for (int j = 0; j < columns - 1; j++) {
			int n = nodeID(columns, i, j);
			int right = nodeID(columns, i, j + 1);
			char x = mat[n][right] ? pass : wall;
			if (isExit(n, exit))
				printf("%c%c", cell, ext);
			else
				if (isEntr(n, entrance))
					printf("%c%c", cell, entr);
				else
					printf("%c%c", cell, x);
		}
		printf("%c%c\n%c", cell, wall, wall);
		for (int j = 0; j < columns; j++) {
			int n = nodeID(columns, i, j);
			int down = nodeID(columns, i + 1, j);
			char x = mat[n][down] ? pass : wall;
			printf("%c%c", x, wall);
		}
		printf("\n");
	}
	printf("%c", wall);
	for (int j = 0; j < columns - 1; j++) {
		int n = nodeID(columns, rows - 1, j);
		int right = nodeID(columns, rows - 1, j + 1);
		char x = mat[n][right] ? pass : wall;
		if (isExit(n, exit))
			printf("%c%c", cell, ext);
		else
			if (isEntr(n, entrance))
				printf("%c%c", cell, entr);
			else
				printf("%c%c", cell, x);
	}

	printf("%c%c\n", cell, wall);
	for (int i = 0; i < columns; i++)
		printf("%c%c", wall, wall);
	printf("%c\n", wall);
	printf("\n");
}

void printFile(FILE *out, int **mat, int rows, int columns, int entrance, int exit) {
	char wall = '#', pass = ' ', entr = 'o', ext = 'x', cell = '\'';


	for (int i = 0; i < columns; i++)
		fprintf(out, "%c%c", wall, wall);

	fprintf(out, "%c\n", wall);

	for (int i = 0; i < rows - 1; i++) {
		fprintf(out, "%c", wall);
		for (int j = 0; j < columns - 1; j++) {
			int n = nodeID(columns, i, j);
			int right = nodeID(columns, i, j + 1);
			char x = mat[n][right] ? pass : wall;
			if (isExit(n, exit))
				fprintf(out, "%c%c", cell, ext);
			else
				if (isEntr(n, entrance))
					fprintf(out, "%c%c", cell, entr);
				else
					fprintf(out, "%c%c", cell, x);
		}
		fprintf(out, "%c%c\n%c", cell, wall, wall);
		for (int j = 0; j < columns; j++) {
			int n = nodeID(columns, i, j);
			int down = nodeID(columns, i + 1, j);
			char x = mat[n][down] ? pass : wall;
			fprintf(out, "%c%c", x, wall);
		}
		fprintf(out, "\n");
	}

	fprintf(out, "%c", wall);

	for (int j = 0; j < columns - 1; j++) {
		int n = nodeID(columns, rows - 1, j);
		int right = nodeID(columns, rows - 1, j + 1);
		char x = mat[n][right] ? pass : wall;
		if (isExit(n, exit))
			fprintf(out, "%c%c", cell, ext);
		else
			if (isEntr(n, entrance))
				fprintf(out, "%c%c", cell, entr);
			else
				fprintf(out, "%c%c", cell, x);
	}

	fprintf(out, "%c%c\n", cell, wall);
	for (int i = 0; i < columns; i++)
		fprintf(out, "%c%c", wall, wall);

	fprintf(out, "%c\n", wall);
	fprintf(out, "\n");
}

void input(int **mat, int rows, int columns, int numOfNodes) {
	Elem *edges = NULL;
	int *nodes = (int*)calloc(numOfNodes, sizeof(int));
	srand(time(0));
	int newNodeI = ((double)rand() / (RAND_MAX + 1.0)) * rows;
	int newNodeJ = ((double)rand() / (RAND_MAX + 1.0)) * columns;
	int newNode = nodeID(columns, newNodeI, newNodeJ);
	int numOfEdges = 0;
	do {
		if (!getNode(nodes, newNode)) { 
			edges = addEdges(edges, &numOfEdges, newNode, newNodeI, newNodeJ, rows, columns);
			addNode(nodes, newNode);
		}
		int edgeIndex;
		Edge *newEdge;
		Elem* tempEdge = edges;
		edgeIndex = ((double)rand() / (RAND_MAX + 1.0)) * numOfEdges;
		if (edgeIndex == 0) { 
			newEdge = edges->e;
			edges = edges->next;
			free(tempEdge);
			numOfEdges--;
		}
		else {
			for (int i = 0; i<edgeIndex - 1; i++) {
				tempEdge = tempEdge->next;
			}
			Elem* x = tempEdge;
			tempEdge = tempEdge->next;
			x->next = tempEdge->next;
			newEdge = tempEdge->e;
			numOfEdges--;
			free(tempEdge);
		}

		int pointB = newEdge->pointB;
		int pointA = newEdge->pointA;
		if (!getNode(nodes, pointB)) {
			addEdge(mat, pointA, pointB);
		}
		free(newEdge);

		newNode = pointB;
		newNodeJ = newNode % columns;
		newNodeI = newNode / columns;
	} while (numOfEdges); 
}
//kraj lavirinta

//prolaz od pocetka do kraja

void addNodes(int Q[], int **mat, int *nodes, int newNode, int i, int j, int rows, int columns, int *front, int *rear, int n) {
	if (i > 0) {
		int pointB = nodeID(columns, i - 1, j);
		if (nodes[pointB] == -1 && mat[newNode][pointB] == 1) {
			insertQ(Q, pointB, n, rear, front);
			nodes[pointB] = newNode;
		}
	}
	if (j > 0) {
		int pointB = nodeID(columns, i, j - 1);
		if (nodes[pointB] == -1 && mat[newNode][pointB] == 1) {
			insertQ(Q, pointB, n, rear, front);
			nodes[pointB] = newNode;
		}
	}
	if (j < columns - 1) {
		int pointB = nodeID(columns, i, j + 1);
		if (nodes[pointB] == -1 && mat[newNode][pointB] == 1) {
			insertQ(Q, pointB, n, rear, front);
			nodes[pointB] = newNode;
		}
	}
	if (i < rows - 1) {
		int pointB = nodeID(columns, i + 1, j);
		if (nodes[pointB] == -1 && mat[newNode][pointB] == 1) {
			insertQ(Q, pointB, n, rear, front);
			nodes[pointB] = newNode;
		}
	}
}

void BFS(int Q[], int **mat, int startNode, int exitNode, int rows, int columns, int *front, int *rear, int n, int numOfNodes) {
	int *prevNode = (int)malloc(numOfNodes * sizeof(int));
	for (int i = 0; i < numOfNodes; i++){
		prevNode[i] = -1;
	}
	prevNode[startNode] = 0;
	insertQ(Q, startNode, n, &rear, &front);
	while (QueueIsEmpty) {
		int newNode = deleteQ(Q, n, &front, &rear);
		int newNodeJ = newNode % columns;
		int newNodeI = newNode / columns;
		if (isExit(newNode, exitNode)) {
			printf("nadjen izlaz\n");
			break;
		}
		addNodes(Q, mat, prevNode, newNode, newNodeI, newNodeJ, rows, columns, &front, &rear, n);
	}
	int tempNode = exitNode;
	int nodeI = tempNode % columns;
	int nodeJ = tempNode / columns;
	printf("(%d, %d) ", nodeI, nodeJ);
	int i = 0;
	while (1) {
		if (tempNode == startNode) break;
		int nextNode = prevNode[tempNode];
		tempNode = nextNode;
		int nodeI = nextNode % columns;
		int nodeJ = nextNode / columns;
		printf("(%d, %d) ", nodeI, nodeJ);
		i++;
	}
}

//meni 
void menu() {
	printf("1. kreiraj \n");
	printf("2. ispis u konzolu\n");
	printf("3. ispis u datoteku\n");
	printf("4. nadji put\n");
	printf("5. zavrsi rad\n");
}

int main() {
	int val, command, rows, columns, numOfNodes, **mat =NULL, rear = -1, front = -1, entrance, exit;
	FILE * out = fopen("output.txt", "w");
	menu();
	printf("upisi komandu: \n");
	scanf("%d", &command);

	while (command >= 1 && command <= 4) {
		switch (command) {
		case 1: printf("uneti broj vrsta i kolona\n");
			scanf("%d %d", &rows, &columns);
			numOfNodes = rows * columns;
			mat = malloc(numOfNodes * sizeof(int*));
			for (int i = 0; i < numOfNodes; i++) {
				mat[i] = calloc(numOfNodes, sizeof(int));
			}
			input(mat, rows, columns, numOfNodes); break;
		case 2: if (rows > 80 || columns > 50) printf("prevelike dimenzije, stampaj u datoteku\n");
			entrance = setEntrance(columns); exit = setExit(columns); 
			print(mat, rows, columns, entrance, exit); break;
		case 3: 
			entrance = setEntrance(columns); exit = setExit(columns);
			printFile(out, mat, rows, columns, entrance, exit); fclose(out); break;
		case 4: BFS(Q, mat, entrance, exit, rows, columns, front, rear, QMAX, numOfNodes); break;
		case 5: printf("kraj programa"); continue;
		}
		printf("upisi komandu: ");
		scanf("%d", &command);
	}
	return 0;
}