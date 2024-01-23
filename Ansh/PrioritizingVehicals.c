#include "header_file.h"

// Function:    isEmpty
// Description: Checks if the queue is empty
// Input parameter: head - the head of the queue
// Return type: int - 1 if the queue is empty, 0 otherwise
int isEmpty(Queue head)
{
    if(head == NULL)
    {
        return 1;
    }
    return 0;
}

// Function:    FindMid
// Description: Finds the middle node of the queue using slow and fast pointers
// Input parameter: head - the head of the queue
// Return type: Queue - the middle node of the queue
Queue FindMid(Queue head)
{
    Queue slow = head;
    Queue fast = head->next;

    while(fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

// Function:    Merge
// Description: Merges two sorted queues into a single sorted queue
// Input parameters: left - the left queue to be merged
//                   right - the right queue to be merged
// Return type: Queue - the merged sorted queue
Queue Merge(Queue left, Queue right)
{
    if(left == NULL)
    {
        return right;
    }
    if(right == NULL)
    {
        return left;
    }

    Queue head = (Queue)malloc(sizeof(struct queue));
    Queue temp = head;


    while(left != NULL && right != NULL)
    {
        if(left->priority < right->priority)
        {
            temp->next = left;
            temp = left;
            left = left->next;
        }
        else
        {
            temp->next = right;
            temp = right;
            right = right->next;

        }
    }
    while(left != NULL)
    {
        temp->next = left;
        temp = left;
        left = left->next;
    }
    while(right != NULL)
    {
        temp->next = right;
        temp = right;
        right = right ->next;
    }
    head = head->next;

    return head;
}

// Function:    MergeSort
// Description: Sorts the queue using merge sort algorithm
// Input parameter: head - the head of the queue
// Return type: Queue - the sorted queue
Queue MergeSort(Queue head)
{
    if(head == NULL || head->next == NULL)
    {
        return head;
    }
    // thoda computation karte hai
    Queue mid = FindMid(head);

    Queue left = head;
    Queue right = mid->next;
    mid->next = NULL;

    // recursively call karo
    left = MergeSort(left);
    right = MergeSort(right);

    // merge karo dono linked list
    Queue result = Merge(left, right);

    return result;
}

// Function:    Generate_random_string
// Description: Generates a random string of specified length
// Input parameter: length - length of the random string
// Return type: char* - pointer to the generated random string
char* Generate_random_string(int length)
{
    // Define the characters that can be used in the random string
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    // Allocate memory for the string, including space for the null terminator
    char* random_string = (char*)malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; i++)
    {
        int index = rand() % (sizeof(charset) - 1);
        random_string[i] = charset[index];
    }

    random_string[length] = '\0';
    return random_string;
}

// Function:    insert_data
// Description: Inserts data into a new node in the queue
// Input parameter: n - the new node
// Return type: Queue - the new node after inserting data
Queue insert_data(Queue n)
{
    n->priority = rand()%3 + 1;
    if(n->priority == 1)
    {
        strcpy(n->name, "AMBULANCE");
    }
    else if(n->priority == 2)
    {
        strcpy(n->name, "PUBLIC_VEHICAL");
    }
    else
    {
        strcpy(n->name, "OTHERS");
    }
    strcpy(n->number, Generate_random_string(10));
    n->next = NULL;
    return n;
}

// Function: create
// Description: Creates a new queue node and initializes it by calling insert_data
// Return type: Queue - the newly created node
Queue create()
{
    Queue newnode = (Queue)malloc(sizeof(struct queue));
    newnode = insert_data(newnode);
    return newnode;
}

// Function: insert_at_end
// Description: Inserts a new node at the end of the queue
// Input parameter: head - the head of the queue
// Return type: Queue - the updated head of the queue
Queue insert_at_end(Queue head)
{
    Queue temp = head;
    if(head == NULL)
    {
        return (create());
    }
    Queue newnode = create();
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newnode;
    return head;
}

// Function: delete_from_front
// Description: Deletes the node from the front of the queue and frees the memory
// Input parameter: head - the head of the queue
// Return type: Queue - the updated head of the queue
Queue delete_from_front(Queue head)
{
    Queue temp = head;
    head = head->next;
    printf("%s %s %d\n",temp->number, temp->name, temp->priority);
    free(temp);
    return head;
}

// Function: writeToFileQueue
// Description: Writes the contents of the queue to a file named "PriorityQueue.txt"
// Input parameters: fp - file pointer, head - the head of the queue
// Return type: void
void writeToFileQueue(FILE* fp, Queue head)
{
    Queue temp = head;
    fp = fopen("PriorityQueue.txt", "w");
    while(temp != NULL)
    {
        fprintf(fp, "%d %s %s\n",temp->priority, temp->number, temp->name);
        temp = temp->next;
    }
    fclose(fp);
    return;
}

