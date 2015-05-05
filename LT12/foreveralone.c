#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 128
typedef char String[LIMIT];

typedef struct LinkedNodeTag {
  String name;
  struct LinkedNodeTag *nextNode;
  struct LinkedNodeTag *ally;
} LinkedNode;

typedef LinkedNode *LinkedNodePoint;

LinkedNodePoint searchLinkedList(LinkedNodePoint p, String s) {
  while (p != NULL) {
    if (strcmp(p->name, s) == 0)
      return p;
    p = p->nextNode;
  }
  return NULL;
}

int main(void) {
  LinkedNodePoint head = NULL;
  LinkedNodePoint newNode;
  String input;

  do {
    newNode = (LinkedNodePoint)malloc(sizeof(LinkedNode));
    strcpy(newNode->name, input);
    newNode->nextNode = head;
    head = newNode;
    printf("Enter nation name (exit to finish) : ");
    scanf("%s", input);
  } while (strcmp(input, "") != 0 && strcmp(input, "exit") !=0); 

  LinkedNodePoint iterator = head;
  do {
    printf("Enter best ally for %s : ", iterator->name);
    scanf("%s", input);
    if (searchLinkedList(head, input) == NULL) {
      printf("Error! %s does not exist in the nations entered. Try again.\n", input);
      continue;
    } else {
      iterator->ally = searchLinkedList(head, input);
    }
    iterator = iterator->nextNode;
  } while (iterator != NULL); 

  do {
    printf("The best ally of %s is %s\n", head->name, head->ally->name);
    newNode = head;
    head = head->nextNode;
    free(newNode);
  } while (head != NULL); 

  return EXIT_SUCCESS;
}

