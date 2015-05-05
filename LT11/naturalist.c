#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING 128

typedef char String[MAX_STRING];

typedef enum {
	Fish,
	Insect,
	Bird,
	Mammal
} AnimalType;

typedef struct {
	String name;
	float size;
	AnimalType type;
} Animal;


AnimalType InputAnimalType(void) {

	String wild;

	scanf("%s",wild);
	if (!strcmp(wild,"fish")) {
		return(Fish);
	}
	if (!strcmp(wild,"insect")) {
		return(Insect);
	}
	if (!strcmp(wild,"mammal")) {
		return(Mammal);
	}
	if (!strcmp(wild,"bird")) {
		return(Bird);
	}
	printf("Error. Try again.\n");
	return EXIT_FAILURE;
}

char * getAnimalType(AnimalType type) {

	switch(type) {
		case Mammal:
			return("mammal");
			break;
		case Fish:
			return("fish");
			break;
		case Bird:
			return("bird");
			break;
		case Insect:
			return("insect");
			break;
		default:
			return("Error. Try again.");
			break;
	}
}

int main(void) {

	int capacity = 1;
	int size = 0;
	Animal *pointerArray;
	Animal *pointerNewArray;
	String input;

	pointerArray = malloc(capacity*sizeof(Animal));
	if(pointerArray == NULL){
		printf("ERROR: malloc fail.\n");
		return EXIT_FAILURE;
	}

	printf("Enter animal information (\"exit\" to exit)\n");
	printf("What is the name: ");
	scanf("%s", input);

	while (strcmp(input, "exit")) {
		if (size >= capacity){
			capacity *= 2;
			pointerNewArray = realloc(pointerArray,capacity * sizeof(Animal));
			if (pointerNewArray == NULL){
				printf("ERROR: realloc fail.\n");
				return EXIT_FAILURE;
			} else {
				pointerArray = pointerNewArray;
			}
		}

		strncpy(pointerArray[size].name, input, MAX_STRING);
		printf("What is the size : ");
		scanf("%f", &pointerArray[size].size);

		printf("What is the type : ");
		pointerArray[size].type = InputAnimalType();

		size++;
		printf("Enter animal information (\"exit\" to exit)\n");
		printf("What is the name : ");
		scanf("%s", input);
	}

	printf("The following species were found:\n");

	int index;
	for (index = 0; index<size; index++) {
		printf("%-30s has size %5.2f and is a %s \n", pointerArray[index].name, pointerArray[index].size, getAnimalType(pointerArray[index].type));
	}

	return EXIT_SUCCESS;
}
