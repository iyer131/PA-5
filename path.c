#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "path.h"
#include <limits.h>

static Gnode *createGnode() //create Gnode function 
{
    Gnode *newNode = malloc(sizeof(Gnode)); 
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

Gnode **Read_file(FILE *fptr, int *m, int *n)
{
    if (fscanf(fptr, "%d %d\n", m, n) != 2)
    {
        return 0;
    }

    int total_elements = (*m - 1) * (*n);
    Gnode **boardArr = malloc(sizeof(Gnode *) * total_elements); //store whether board exists 
    char digit;
    int ind = 0;
    for (int i = 0; i < *m - 1; i++)
    {
        for (int j = 0; j < *n; j++)
        {
            if (fscanf(fptr, " %c", &digit) != 1) //read file 
            {
                return 0;
            }

            boardArr[ind] = createGnode(); //update boardArr nodes 
            boardArr[ind]->rowStart = i;
            boardArr[ind]->rowEnd = i + 1;
            boardArr[ind]->colStart = j;
            boardArr[ind]->colEnd = j;
            boardArr[ind]->boardExists = digit;
        
            ind += 1;
        }
    }

    return boardArr;
}

Gnode **createhArray(int m, int n)
{
    Gnode **hArray = calloc(sizeof(Gnode *), (m * n + m)); // m horizontal board positions
    if (hArray == NULL)
    {
        return NULL;
    }
    return hArray;
}

Gnode **createvArray(int m, int n)
{
    Gnode **vArray = calloc(sizeof(Gnode *), (m - 1) * n); // m - 1 vertical board positions
    if (vArray == NULL)
    {
        return NULL;
    }
    return vArray;
}

static Gedge *createEdge() //create Gedge function 
{
    Gedge *newEdge = malloc(sizeof(Gedge)); 
    if (newEdge != NULL)
    { 
        newEdge->weight = 0;
        newEdge->dest = NULL;
        newEdge->next = NULL;
    }
    return newEdge; 
}

static Gedge *addEdge(Gnode *source, Gnode *dest) //adds edge to create adjlist 
{
    Gedge *edge = createEdge();
    if (dest->boardExists == '0') //no board exists there already 
    {
        edge->weight = 1;
    }
    else //board exists 
    {
        edge->weight = 0;
    }

    edge->dest = dest;
    edge->next = source->adjlist; 
    source->adjlist = edge;
    return edge;
}

void createGraph(Gnode *dummyStart, Gnode *dummyEnd, Gnode **boardArr, Gnode **vArray, Gnode **hArray, int m, int n)
{
    for (int i = 0; i < (m * n + m); i++) //initialize horizontal board positions 
    {
        hArray[i] = createGnode(); 
        if (hArray[i] == NULL)
        {
            return;
        }
    }
    for (int i = 0; i < (m - 1) * n; i++) //initialize vertical board positions 
    {
        vArray[i] = createGnode(); 
        if (vArray[i] == NULL)
        {
            return;
        }
    }

    int ind = 0;
    for (int i = -1; i < n; i += 1) // all possible horizontal positions 
    {
        for (int j = 0; j < m; j += 1)
        {
            hArray[ind]->rowStart = j;
            hArray[ind]->colStart = i;
            hArray[ind]->rowEnd = j;
            hArray[ind]->colEnd = i + 1;
            ind++;
        }
    }

    ind = 0;
    for (int i = 0; i < n; i += 1) //all possible vertical positions 
    {
        for (int j = 0; j < m - 1; j += 1)
        {
            vArray[ind]->rowStart = j;
            vArray[ind]->colStart = i;
            vArray[ind]->rowEnd = j + 1;
            vArray[ind]->colEnd = i;
            ind++;
        }
    }

    for (int i = 0; i < (m - 1) * n; i++) //update board exists field for vertical positions 
    {
        for (int j = 0; j < (m - 1) * n; j++)
        {
            if (boardArr[i]->rowStart == vArray[j]->rowStart && boardArr[i]->rowEnd == vArray[j]->rowEnd && boardArr[i]->colStart == vArray[j]->colStart && boardArr[i]->colEnd == vArray[j]->colEnd)
            {
                vArray[j]->boardExists = boardArr[i]->boardExists;
            }
        }
    }

    int topCnt = 0;
    int midCnt = 1;
    int botCnt = 1;
    int rowCount = 0;

    for (ind = 0; ind < (m * n + m); ind++) //creates adjacency list and graph 
    {
        if (ind % m == 0) //if position exists at the top 
        {
            if (ind == 0)
            {
                addEdge(hArray[ind], vArray[ind]); 
            }

            else if (ind != 0 && ind != m * n)
            {
                addEdge(hArray[ind], vArray[ind - (m + topCnt)]);
                topCnt += 1;
                addEdge(hArray[ind], vArray[ind - topCnt]);
            }
        }
        else if ((ind - (m - 1)) % m == 0) //if position exists at the bottom 
        {
            if (ind == m - 1)
            {
                addEdge(hArray[ind], vArray[ind - 1]);
            }
    
            else if (ind != m - 1 && ind != m*n + m - 1)
            {
                int vInd = ind - (m + botCnt);
                addEdge(hArray[ind], vArray[vInd]);
                addEdge(hArray[ind], vArray[vInd + (m - 1)]);
                botCnt += 1;
            }
        }
        else //if positions exist in the middle 
        {
            if (ind > 0 && ind < m - 1)
            {
                addEdge(hArray[ind], vArray[ind]);
                addEdge(hArray[ind], vArray[ind - 1]);
            }
            else if (ind > m - 1 && ind < m * n)
            {
                int vInd = ind - (m + midCnt);
                rowCount += 1;
                addEdge(hArray[ind], vArray[vInd]);
                addEdge(hArray[ind], vArray[vInd + 1]);
                addEdge(hArray[ind], vArray[vInd + (m - 1)]);
                addEdge(hArray[ind], vArray[vInd + m]);
                if (rowCount == m - 2)
                {
                    rowCount = 0;
                    midCnt += 1;
                }
            }
        }
    }

    int vertCnt = 0;
    for (ind = 0; ind < (m - 1) * n; ind++)  
    {
        //cases for vertical board positions 
        if (ind < m - 1)
        {
            addEdge(vArray[ind], hArray[ind + m]);
            addEdge(vArray[ind], hArray[ind + m + 1]);
        }
        else
        {
            if (ind % (m - 1) == 0)
            {
                vertCnt += 1;
            }
            addEdge(vArray[ind], hArray[ind + m + vertCnt]);
            addEdge(vArray[ind], hArray[ind + m + vertCnt + 1]);
            addEdge(vArray[ind], hArray[ind + vertCnt]);
            addEdge(vArray[ind], hArray[ind + vertCnt + 1]);
        }

        //adding vertical board position adjacencies for existing boards 
        if (ind % (m - 1) == 0) 
        {
            if (vArray[ind + 1]->boardExists == '1')
            {
                addEdge(vArray[ind], vArray[ind + 1]);
            }
        }
        else if ((ind - (m - 2)) % (m - 1) == 0)
        {
            if (vArray[ind - 1]->boardExists == '1')
            {
                addEdge(vArray[ind], vArray[ind - 1]);
            }
        }
        else
        {
            if (vArray[ind - 1]->boardExists == '1' && vArray[ind + 1]->boardExists == '1')
            {
                addEdge(vArray[ind], vArray[ind - 1]);
                addEdge(vArray[ind], vArray[ind + 1]);
            }
            else if (vArray[ind - 1]->boardExists == '1')
            {
                addEdge(vArray[ind], vArray[ind - 1]);
            }
            else if (vArray[ind + 1]->boardExists == '1')
            {
                addEdge(vArray[ind], vArray[ind + 1]);
            }
        }
    }

    for (int i = 0; i < m; i++) //attach dummy start 
    {
        hArray[i]->boardExists = '1';
        addEdge(dummyStart, hArray[i]);
    }

    for (int i = (m * n + m) - m; i < m * n + m; i++) //attach dummy end 
    {

        dummyEnd->boardExists = '1';
        addEdge(hArray[i], dummyEnd);
    }
}

Gnode **makeHeap(Gnode *dummyStart, Gnode *dummyEnd, Gnode **boardArr, Gnode **vArray, Gnode **hArray, int m, int n)
{
    Gnode **PQ = malloc(sizeof(Gnode *) * ((m * n + m + (m - 1) * n) + 2));

    //assign dummy start and dummy end 
    PQ[0] = dummyStart; 
    PQ[m * n + m + (m - 1) * n + 1] = dummyEnd;
    PQ[m * n + m + (m - 1) * n + 1]->index = m * n + m + (m - 1) * n + 1;

    int ind = 0;
    for (int i = 1; i < (m * n + m + 1); i++) //horizontal positions 
    {
        PQ[i] = hArray[ind];
        PQ[i]->index = i;
        ind++;
    }

    ind = 0;
    for (int j = m * n + m + 1; j < (m * n + m + (m - 1) * n + 1); j++) //vertical positions 
    {
        PQ[j] = vArray[ind];
        PQ[j]->index = j;
        ind++;
    }

    for (int i = 0; i < (m * n + m + (m - 1) * n + 2); i++) //assign pathweight and indexes for dijkstra 
    {
        if (i == 0)
        {
            PQ[i]->pathWeight = 0;
            PQ[i]->index = 0;
        }
        else
        {
            PQ[i]->pathWeight = INT_MAX;
        }
    }

    return PQ;
}

static void downwardHeapify(Gnode **priorityQueue, int ind, int size)
{
    int minInd = ind;

    if (2 * ind + 1 < size) //left child check 
    {
        if (priorityQueue[2 * ind + 1]->pathWeight < priorityQueue[minInd]->pathWeight)
        {
            minInd = 2 * ind + 1;
        }
    }

    if (2 * ind + 2 < size) //right child check 
    {
        if (priorityQueue[2 * ind + 2]->pathWeight < priorityQueue[minInd]->pathWeight)
        {
            minInd = 2 * ind + 2;
        }
    }

    if (minInd != ind) //swap nodes at indexes if a left or right child is greater than the node 
    {
        Gnode * temp = priorityQueue[ind];
        priorityQueue[ind] = priorityQueue[minInd];
        priorityQueue[minInd] = temp;
        priorityQueue[minInd]->index = minInd;
        priorityQueue[ind]->index = ind;

        downwardHeapify(priorityQueue, minInd, size);
    }
}

static void upwardHeapify(Gnode **priorityQueue, int ind)
{
    Gnode *node = priorityQueue[ind];

    while (ind > 0)
    {
        if (priorityQueue[(ind - 1) / 2]->pathWeight <= node->pathWeight) //check if parent pathweight is greater than node path weight  
        {
            break;
        }
        priorityQueue[ind] = priorityQueue[(ind - 1) / 2]; //if parent pathweight is greater switch with node 
        priorityQueue[ind]->index = ind;
        ind = (ind - 1) / 2; //reset ind to next parent 
    }

    priorityQueue[ind] = node; 
    priorityQueue[ind]->index = ind;
}

void printPath(FILE *fptr, Gnode *end)
{
    if (end == NULL)
    {
        return;
    }

    if (end->pred != NULL)
    {
        printPath(fptr, end->pred); //use pred to reveal shortest path 
    }

    if (!(end->rowStart == 0 && end->colStart == 0 && end->rowEnd == 0 && end->colEnd == 0)) //print path nodes 
    {
        fprintf(fptr, "(%d,%d)(%d,%d)\n", end->rowStart, end->colStart, end->rowEnd, end->colEnd);
    }
}

void dijkstra(FILE * fptr, Gnode **priorityQueue, int m, int n)
{
    int size = m * n + m + (m - 1) * n + 2; 
    Gnode * u = NULL; 
    while (size > 0)
    {
        u = priorityQueue[0]; //extract min 
        priorityQueue[0]->index = 0;
        priorityQueue[0] = priorityQueue[size - 1];
        size -= 1;

        //fix priority queue 
        downwardHeapify(priorityQueue, 0, size);

        Gedge *edge = u->adjlist;
        while (edge != NULL)
        { 
            Gnode *v = edge->dest;
            if (v->pathWeight > u->pathWeight + edge->weight)
            {
                v->pathWeight = u->pathWeight + edge->weight; //appropriately assign pathweight 
                v->pred = u;

                //fix priority queue 
                upwardHeapify(priorityQueue, v->index);
            }
            edge = edge->next;
        }
    }
    fprintf(fptr, "%d\n", u->pathWeight); //account for second output file 
}
