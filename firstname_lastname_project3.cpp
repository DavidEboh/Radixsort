/*
  Course: CS 1412 Fall 2013 
  Project Number: Project 3
  Date: 
  Name:
  
  This program will use radix sorting algorithm to sort the array 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 1
#define PRINTARRAY 1
#define PRINTQUEUE 1 

/* declare the node */
struct node
{
    int value;
    struct node* next;
};

typedef struct node* pnode;

/* Use radix sort to sort the data */
void radixSort(int* data, int size, int numDigits);

/* create a new node */
pnode createNode();

/* enqueue the node p to the queue */
void enqueue(pnode head, pnode* tailptr, pnode p);

/* dequeue from the queue */
pnode dequeue(pnode head, pnode* tailptr);

/* print the array */
void printArray(int* data, int size);

/* print the queue with index */
void printQueue(pnode head, int idx);

/* create and return the array */
int* createArray(int size, int numDigits);

int main()
{
    int size = 0, numDigits = 0;   /* size of the array,  number of digits*/
    int* data;                     /* integer array */
    clock_t start2, finish2;       /* variable to calculate the time*/
    
    /* initialize the seed */
    srand((unsigned)time(0));
    
    /* input the size of array and validate */
    do
    {
        printf("Enter the size of the array to ( > 0 ): ");
        scanf("%d", &size);
        if (size <= 0)
            printf("You entered %d, please enter a positive integer\n", 
                    size);
    } while (size <= 0);
                                           
    /* input the number of digits and validate */
    do
    {
        printf("Enter the number of digis in each number in [1,5]: ");
        scanf("%d", &numDigits);
        if (numDigits <= 0 || numDigits > 5)
            printf("You entered %d, please enter a positive integer\n", 
                    numDigits);
    } while (numDigits <= 0 || numDigits > 5);
    
    data = createArray(size, numDigits);
    
    if (PRINTARRAY)
        printArray(data, size);
                        
    /* sort the array */               
    start2 = clock();
    radixSort(data, size, numDigits);                                 
    finish2 = clock();
    printf("\nSort Time = %f seconds\n",
        ((double) (finish2-start2))/CLOCKS_PER_SEC);

    if (PRINTARRAY)
        printArray(data, size);
        
    free(data);
    return 0;
}

void radixSort(int* data, int size, int numDigits)
{
    struct node heads[11];     /* dummy head array */
    pnode tails[11];           /* tail array contains the last node*/
    pnode curr;                /* current node to process*/
    int i;                     /* counter */
    int pos;                   /* position of the queue */
    int div = 10;              /* used to calculate each digit */

    if (DEBUG)    
        printf("\nRadixSort...\n");
        
    /* initialize the queue array  */
    for (i = 0; i < 11; i++)    
    {
        heads[i].next = NULL;
        tails[i] = NULL;
    }
    
    /* first round , process the array */
    for (i = 0; i < size; i++)
    {
        curr = createNode();
        curr->value = data[i];
        pos = data[i] % 10;
        enqueue(&(heads[pos]), &(tails[pos]), curr);
    }
    
    for (i = 0; i < numDigits; i++)
    {
        /* print queue, and dequeue to queue11 */
        for (pos = 0; pos < 10; pos++)
        {
            if (PRINTQUEUE)
                printQueue(&(heads[pos]), pos);
            curr = dequeue(&(heads[pos]), &(tails[pos]));
            while (curr != NULL)
            {
                enqueue(&(heads[10]), &(tails[10]), curr);     
                curr = dequeue(&(heads[pos]), &(tails[pos]));
            }
        }   
        if (PRINTQUEUE)
            printf("\n");
        
        /* check for next digit, only need to do numDigits-1 rounds*/
        if (i < numDigits - 1)
        {
            curr = dequeue(&(heads[10]), &(tails[10]));
            while (curr != NULL)
            {
                pos = (curr->value / div) % 10;
                enqueue(&(heads[pos]), &(tails[pos]), curr);     
                curr = dequeue(&(heads[10]), &(tails[10]));
            }
        }
        
        div = div * 10;  /* move to next digit */
    }
    
    /* copy data in queue to array */
    for (i = 0; i < size; i++)
    {
        curr = dequeue(&(heads[10]), &(tails[10]));
        data[i] = curr->value;
        free(curr);
    }
    
}

pnode createNode()
{
    pnode p = (pnode)malloc(sizeof(struct node));
    p->value = 0;
    p->next = NULL;
    return p;
}

void enqueue(pnode head, pnode* tailptr, pnode p)
{
    pnode tail = *tailptr;
    if (tail == NULL)
        head->next = p;
    else
        tail->next = p;
    /* tail points to p now */
    *tailptr = p;
    p->next = NULL;    
}

pnode dequeue(pnode head, pnode* tailptr)
{                          
    pnode p = head->next;
    if (p != NULL)
    {
        head->next = p->next;
        /* modify tail if necessary */
        if (head->next == NULL)
            *tailptr = NULL;
    }
    return p;
}

void printArray(int* data, int size)
{
    int i;            
    if (DEBUG)    
        printf("\nPrinting Array...\n");
    printf("\nThe Array\n");
    for (i = 0; i < size; i++)
    {
        printf("%6d", data[i]);
        if ((i+1) % 10 == 0)
            printf("\n");
    }     
    printf("\n");
}

void printQueue(pnode head, int idx)
{
    int i = 0;
    pnode p;
    printf("Queue %d: ", idx);
    if (head->next == NULL)
    {
        printf("<empty>\n");
    }
    else
    {        
        /* print each integer in the list */
        for (p = head->next; p != NULL; p = p->next)
        {
            printf("%6d", p->value);
            if ((++i) % 10 == 0)
                printf("\n         ");
        }   
        printf("\n");
    }
}

int* createArray(int size, int numDigits)
{
    int i;
    int maxV = 1;
    int* data = (int*)malloc(size * sizeof(int));
    
    if (DEBUG)    
        printf("\nCreating Array size %d...\n", size);
    
    /* initialize the array */
    for (i = 0; i < numDigits; i++)
        maxV = maxV * 10;
    for (i = 0; i < size; i++)
        data[i] = rand() % maxV;
    return data;
}

