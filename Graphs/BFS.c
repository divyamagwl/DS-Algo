#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct AdjacencyListNode
{
    int i;
    struct AdjacencyListNode *next;
};

void push(struct AdjacencyListNode **head_ref, int new_data)
{
    struct AdjacencyListNode *new_node = (struct AdjacencyListNode *)malloc(sizeof(struct AdjacencyListNode));
    new_node->i = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void BFS(struct AdjacencyListNode **AdjacencyList, int source, int n)
{
    bool *Visited = malloc(n * sizeof(int));
    int *Phi = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        Phi[i] = -2;
        Visited[i] = false;
    }
    int *Queue = malloc(n * sizeof(int));
    int head = 0;
    int tail = 0;
    Queue[tail] = source;
    Visited[source] = true;
    Phi[source] = -1;
    printf("BFS traversal of the graph from source %d is: ", source);
    while (head <= tail)
    {
        int node = Queue[head];
        head++;
        printf("%d ", node);
        struct AdjacencyListNode *temp = AdjacencyList[node];
        while (temp != NULL)
        {
            if (Visited[temp->i] == false)
            {
                Queue[++tail] = temp->i;
                Visited[temp->i] = true;
                Phi[temp->i] = node;
            }
            temp = temp->next;
        }
    }
    printf("\nPhi[i] and i combinations are: \n");
    for (int i = 0; i < n; ++i)
        printf("(%d,%d)", Phi[i], i);
}
int main()
{
    int n;
    scanf("%d", &n);
    struct AdjacencyListNode **AdjacencyList = malloc(n * sizeof(struct AdjacencyListNode *));
    for (int i = 0; i < n; i++)
    {
        AdjacencyList[i] = NULL;
    }
    for (int i = 0; i < n; i++)
    {
        int node;
        printf("Enter a number: ");
        scanf("%d", &node);
        printf("Enter its number of adjacent nodes: ");
        int m;
        scanf("%d", &m);
        for (int j = 0; j < m; j++)
        {
            int num;
            printf("Enter its adjcaent edge number %d: ", j + 1);
            scanf("%d", &num);
            push(&AdjacencyList[node], num);
        }
    }

    for (int i = 0; i < n; i++)
    {
        struct AdjacencyListNode *temp = AdjacencyList[i];
        while (temp != NULL)
        {
            printf("i = %d j = %d\n", i, temp->i);
            temp = temp->next;
        }
    }

    BFS(AdjacencyList, 0, n);
    return 0;
}