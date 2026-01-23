#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "path.h"

static void freeArr(Gnode **arr, int size) //free array 
{
    for (int i = 0; i < size; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

static void freeGraph(Gnode **arr, int size) //free graph 
{
    for (int i = 0; i < size; i++)
    {
        Gedge *edge = arr[i]->adjlist;
        while (edge != NULL)
        {
            Gedge *temp = edge;
            edge = edge->next;
            free(temp);
        }
        free(arr[i]);
    }
    free(arr);
}

static void freeDummy(Gnode *node) //free dummies 
{
    Gedge *edge = node->adjlist;
    while (edge != NULL)
    {
        Gedge *temp = edge;
        edge = edge->next;
        free(temp);
    }
    free(node);
}

static Gnode *createGnode()
{
    Gnode *newNode = malloc(sizeof(Gnode)); 
    if (newNode != NULL)
    { 
        newNode->pred = NULL;
        newNode->adjlist = NULL;
        newNode->distance = 0;
        newNode->rowStart = 0;
        newNode->colStart = 0;
        newNode->rowEnd = 0;
        newNode->colEnd = 0;
        newNode->index = 0;
        newNode->pathWeight = 0;
        newNode->boardExists = '0';
    }
    return newNode; 
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        return EXIT_FAILURE;  
    }
    if (argc == 4)
    {
        char *filename = argv[1];
        FILE *fptr = fopen(filename, "r");
        char *filename_2 = argv[2];
        FILE *fptr_2 = fopen(filename_2, "w");
        char * filename_3 = argv[3]; 
        FILE * fptr_3 = fopen(filename_3, "w"); 
        int m;
        int n;
        Gnode **boardArr = Read_file(fptr, &m, &n);
        Gnode **hArray = createhArray(m, n);
        Gnode **vArray = createvArray(m, n);
        Gnode *dummyStart = createGnode();
        Gnode *dummyEnd = createGnode();
        createGraph(dummyStart, dummyEnd, boardArr, vArray, hArray, m, n);
        Gnode ** PQ = makeHeap(dummyStart, dummyEnd, boardArr, vArray, hArray, m, n);
        dijkstra(fptr_3, PQ, m, n);
        printPath(fptr_2, dummyEnd);
        freeArr(boardArr, (m - 1) * n);
        freeGraph(hArray, m * n + m);
        freeGraph(vArray, (m - 1) * n);
        free(PQ);
        freeDummy(dummyStart);
        freeDummy(dummyEnd);
        fclose(fptr);
        fclose(fptr_2);
        fclose(fptr_3); 
    }

    return EXIT_SUCCESS;
}