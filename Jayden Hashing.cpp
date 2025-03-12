#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define TABLE_SIZE 100

struct HashTable {
	char key[100];
} ht[TABLE_SIZE];

void initializationHT() {
	for(int i = 0; i < TABLE_SIZE; i++) {
		strcpy(ht[i].key, "");
	}
}

int StoI(char key[]) {
	int sum = 0;
	for(int i = 0; key[i] != '\0'; i++) {
		sum += key[i];		
	}
	return sum;
}

int DivHash(char key[]) {
	int intKey = StoI(key);
	return intKey % TABLE_SIZE;
}

int firstchar(char key[]) {
	if(key[0] == '\0') {
		return -1;
	}
	char firstChar = key[0];
	if(!isalpha(firstChar)) {
		return -1;
	}
	return tolower(firstChar) - 'a';
}

int rotate(char key[]) {
	int a = DivHash(key);
	int rotatedNum;
	if(a == 0) {
		return a;
	} else if(a < 10) {
		return a;
	} else if(a == 10) {
		return 1;
	} else {
		int tens = a / 10;
		int ones = a % 10;
		rotatedNum = (ones * 10) + tens;
		return rotatedNum;
	}
} 
int linearProbing(int index) {
   
    int i = index;
    while (ht[i].key[0] != '\0') {
        i = (i + 1) % TABLE_SIZE;  
        if (i == index) {
           
            printf("Hash Table Penuh! \n");
            return -1; 
        }
    }
    return i; 
}
	void insert(char key[], int (*hashFunction)(char[])) {
    int index = hashFunction(key);
    
    
    if (ht[index].key[0] == '\0') {
        strcpy(ht[index].key, key);
        printf("Key '%s' dimasukkan ke index %d.\n", key, index);
    } else {
       
        printf("Kolasi ditemukan di key %d.\n", index);
        int newIndex = linearProbing(index);
        if (newIndex != -1) {
            strcpy(ht[newIndex].key, key);
            printf("Key '%s' dimasukkan ke key %d after probing.\n", key, newIndex);
        }
    }
}

void displayHT() {
	printf("\nHash Table\n");	
	for(int i = 0; i < TABLE_SIZE; i++) {
		if(strcmp(ht[i].key, "") != 0) {
			printf("Index %d: %s\n", i, ht[i].key);
		} else {
			printf("Index %d: - \n", i);
		}
	}
}

int main() {
	initializationHT();
	char key[100];
	
	int(*hashFunction)(char[]) = NULL;
	

	hashFunction = rotate;
	while(1) {
		printf("Masukkan key (string) atau exit untuk berhenti:");
		scanf("%s", key);
		if(strcmp(key,"exit")==0) break;
		insert(key, hashFunction);
	}
	
	displayHT();
}
