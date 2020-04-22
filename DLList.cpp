/** An implementation of Insertion Sort on a Doubly-Linked List,
 * which takes input from the user to decide the length of said
 * list, creates a list of random numbers, and then sorts the list
 * using insertion sort. The sorted list is then printed to the
 * console, along with the time taken to sort the list, to the
 * nearest millisecond. NOTE: Any list over 100,000 elements long
 * may take quite a while to sort.
 * **/

#include <iostream>
#include <string>
#include <ctime>
#include <random>

using namespace std;

struct Node //creates a Node data type
{
    int data;   //this will hold the value in the Node
    struct Node* prev;  //this is the pointer to the previous Node
    struct Node* next;  //this is the pointer to the next Node
};


struct Node* head = NULL;   //creates a pointer to a head Node set to NULL

void insertNode(int newData);
void displayList();
void batchInsert(int howMany);
void sortedInsert(struct Node** head_ref, struct Node* newNode);
void insertionSort(struct Node** head_ref);

int main()
{

    clock_t start, end; //initialize clock time variables for start and end times
    ios_base::sync_with_stdio(false); //turn off syncing of C and C++ I/O operations, speeding up output

    int num;
    cout << "Enter desired number of Nodes: ";
    cin >> num; //take input from user to determine number of nodes in doubly-linked list

    batchInsert(num);   //create specified list size of random numbers

/** 
 * The following three lines of code were intentionally left out,
 * as printing the list before sorting seemed unnecessary.
**/
    // cout << "The Doubly-Linked List is: ";
    // displayList();
    // cout << "\n" << endl;

    start = clock();    //before sorting begins, record the current time
    insertionSort(&head);
    end = clock();      //after sorting ends, record the time
    cout << "The Sorted List is: ";
    displayList();      //print sorted list to console
    cout << "\n" << endl;

    double timeTaken = double(end - start) / (double (CLOCKS_PER_SEC));  //timeTaken is end time minus start time,
                                                                        //divided by clock ticks per second
    cout << "Sorting Execution Time: " << timeTaken;
    cout << " sec\n" << endl;
    return 0;
}
/*
 * Inserts a node into Doubly-Linked List
 * 
 * newData: value that the node will hold
 */
void insertNode(int newData)    //a function which will insert new nodes
{
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));  //create a pointer to a new Node,
                                                                        //using malloc to allocate exactly the memory that we need
    newNode->data = newData;    //insert into the data slot of 'newNode' the value passed into the function
    newNode->prev = NULL;   //set the prev slot to NULL
    newNode->next = head;   //tell the next slot to point to the head Node
    if(head != NULL)    //if the head Node is not NULL
        head->prev = newNode;   //set the prev pointer in head to point to this newNode
    head = newNode;     //otherwise, if there is no head, make this newNode the head
}
/*
 * Prints the Doubly-Linked List to console
 */
void displayList()  //a function which will print the full list
{    
    struct Node* temp;  //create a temporary Node pointer
    temp = head;    //set this Node pointer equal to the head pointer
    while (temp != NULL)    //while our temp pointer is not NULL
    {
        cout << temp->data << " "; //print the data in the Node temp is pointing to
        temp = temp->next;  //reassign the temp pointer to point to the next Node in the list
    }
}
/*
 * Takes an integer input and creates a doubly-linked list
 * of that length, populated by random numbers.
 * 
 * howMany: integer determining how many nodes in the list
 */
void batchInsert(int howMany) 
{
    random_device rd;  //non-deterministic random number generator
    mt19937 prng(rd()); //pseudorandom number generator, using random_device as a seed
    uniform_int_distribution<int> distr;   //uses mt19937 to generate a uniform distribution of random integers

    for (int i = 0; i < howMany; i++)
    {
        insertNode(distr(prng));    //creates howMany nodes, each with a random integer value
    }
}
/*
 * Takes input from insertionSort() and inserts the Node
 * into the correct place in the sorted list.
 * 
 * head_ref: pointer to pointer of the head of the list
 * newNode: pointer to the node being inserted
 */
void sortedInsert(struct Node** head_ref, struct Node* newNode)
{
    struct Node* current;

    if (*head_ref == NULL)  //if list is empty
    {
        *head_ref = newNode;    //insert 'newNode' as head
    }
    else if ((*head_ref)->data >= newNode->data)    //if newNode will be inserted at the beginning of the list
    {
        newNode->next = *head_ref;  //make newNode's 'next' pointer point to the current head
        newNode->next->prev = newNode;  //make the 'prev' pointer of the former head point to newNode
        *head_ref = newNode;    //make newNode the new head
    }
    else
    {
        current = *head_ref;    //make a 'current' node equal to the head

        //locate the node after which newNode will be inserted
        while (current->next != NULL && current->next->data < newNode->data)    //while there are still more elements in the list AND 
        {                                                                       //the data in the node after 'current' is less than newNode's data
            current = current->next;    //make 'current' point to the next node in the list
        }
        newNode->next = current->next;  //once the data in the node after 'current' is not less than newNode's data,
                                        //set newNode's next pointer equal to current's next pointer.
        if (current->next != NULL)  //if current->next does not point to a NULL value
        {
            newNode->next->prev = newNode;  //the node that newNode->next points to will point back to newNode with its 'prev' pointer
        }
        current->next = newNode;    //current will point forward to newNode
        newNode->prev = current;    //newNode will point back to current
    }
}
/*
 * Implementation of Insertion Sort
 * 
 * head_ref: pointer to head pointer of the input list
 */
void insertionSort(struct Node** head_ref)
{
    struct Node* sorted = NULL;     //creates a new list to store the sorted nodes
    struct Node* current = *head_ref;   //set Node pointer 'current' as dereferenced *head_ref

    while (current != NULL)     //Traverse the list and insert each Node into 'sorted'
    {
        struct Node* next = current->next;  //store the current Node's next pointer for later
        current->prev = current->next = NULL;   //remove pointers from 'current' so it can be inserted as a new Node
        sortedInsert(&sorted, current); //insert 'current' into 'sorted' list
        current = next; //update 'current' to point to the next node in the list, that we stored in 'next' earlier
    }
    *head_ref = sorted; //update *head_ref to point to sorted list
}