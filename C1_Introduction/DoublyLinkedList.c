#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
  - Define a doubly-linked list of heap-allocated strings
  - Write functions to insert, find, and delete items from it
  - Test them
*/

typedef struct Node {
  struct Node* next;
  struct Node* prev;
  char* data;
} Node;

const char* RESET = "\033[0m";
const int totColors = 7;
const char *colors[totColors] = {"\033[0;31m", "\033[0;32m", "\033[0;33m",
				 "\033[0;34m", "\033[0;35m", "\033[0;36m",
				 "\033[0;37m"};
int colorCounter = 0;
char targetS[50];

// cycle through colors when printing data
char* prettify(char* data)
{
  colorCounter++;
  if (colorCounter == totColors) {
    colorCounter = 0;
  }
  sprintf(targetS, "%s%s%s", colors[colorCounter], data, RESET);
  return targetS;
}

// not currently used anywhere but could be useful
int getLength(Node* head)
{
  int i = 0;
  while (head != NULL) {
    i++;
    head = head->next;
  }
  return i;
}

int printList(Node* head)
{
  printf("printing list\n");
  /* printf("list's length: %d\n", getLength(head)); */
  if (head == NULL) {
    printf("head is NULL");
  }
  int i = 0;
  while (head != NULL) {
    printf("index: %d\n", i);
    printf("value: %s\n\n", prettify(head->data));
    i++;
    head = head->next;
  }
  printf("finished printing list\n");
  return 0;
}

int printNode(Node* n)
{
  if (n == NULL) {
    printf("node is NULL");
    return 0;
  }
  
  printf("value: %s\n", n->data);
  Node* prev = n->prev;
  if (prev != NULL) {
    printf("prev's value: %s\n", prev->data);
  } else {
    printf("prev NULL\n");
  }
  Node* next = n->next;
  if (next != NULL) {
    printf("next's value: %s\n", next->data);
  } else {
    printf("next NULL\n");
  }
  printf("\n");
  return 0;
}

Node* findByIndex(int index, Node* head)
{
  int i = 0;
  while (i < index && head != NULL) {
    head = head->next;
    i++;
  }
  if (head == NULL) {
    printf("list index beyond bounds! the list is only %d elements long\n", i);
  }
  return head;
}

Node* findByValue(char dataToFind[], Node* head)
{
  while (head != NULL) {
    if (strcmp(head->data, dataToFind) == 0) {
      return head;
    }
    head = head->next;
  }
  if (head == NULL) {
    printf("element not found! the list does not contain this string: %s\n",
	   dataToFind);
  }
  return head;
}

void insertAfterNode(Node* n, char data[])
{
  Node* new = (Node*)malloc(sizeof(Node));
  new->data = data;
  new->prev = n;

  new->next = n->next;
  n->next = new;
}

Node* insertByIndex(int index, char data[], Node* head)
{
  Node* n = findByIndex(index, head);
  if (n != NULL) {
    insertAfterNode(n, data);
  }
  return head;
}

Node* insertByValue(char dataToFind[], char data[], Node* head)
{
  Node* n = findByValue(dataToFind, head);
  if (n != NULL) {
    insertAfterNode(n, data);
  }
  return head;
}

Node* deleteNode(Node* n, Node* head)
{
  Node* prev = n->prev;
  Node* next = n->next;
  if (prev != NULL) {
    prev->next = next;
  } else {
    head = next;
  }
  if (next != NULL) {
    next->prev = prev;
  }
  
  free(n);
  return head;
}

Node* deleteByIndex(int index, Node* head)
{
  Node* n = findByIndex(index, head);
  if (n != NULL) {
    head = deleteNode(n, head);
  }
  return head;
}

Node* deleteByValue(char dataToFind[], Node* head)
{
  Node* n = findByValue(dataToFind, head);
  if (n != NULL) {
    head = deleteNode(n, head);
  }
  return head;
}

Node* append(char data[], Node* head)
{
  Node* new = (Node*)malloc(sizeof(Node));
  new->data = data;

  if (head == NULL) {
    return new;
  }

  Node* traverse = head;
  while (traverse->next != NULL) {
    traverse = traverse->next;
  }

  new->prev = traverse;
  traverse->next = new;
  return head;
}

int main()
{
  Node* head = append("hello", NULL);
  printList(head);

  append("world", head);
  printList(head);

  char *strings[5] = {"how", "are", "you", "today", "?"};
  for (int i = 0; i < 5; i++) {
    append(strings[i], head);
    printf("\nlist after appending: %s\n", strings[i]);
    printList(head);
  }

  printf("\nfinding by index: %d\n", 3);
  printNode(findByIndex(3, head));

  printf("\nfinding by value: %s\n", "hello");
  printNode(findByValue("hello", head));

  printf("\ninserting by index: %d\n", 0);
  insertByIndex(0, "beautiful", head);
  printList(head);

  printf("\ninserting by value: %s\n", "you");
  insertByValue("you", "doing", head);
  printList(head);

  printf("\ndeleting by index: %d\n", 0);
  head = deleteByIndex(0, head);
  printList(head);

  printf("\ndeleting by value: %s\n", "?");
  head = deleteByValue("?", head);
  printList(head);

  return 0;
}
