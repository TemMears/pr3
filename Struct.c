#include "server.h"
#include "struct.h"

int hash(const char* key) {
	int hashValue = 0;
	for (int i = 0; key[i] != '\0'; i++) {
		hashValue += key[i];
	}
	return hashValue % SIZE;
}
int hash2(const char* key) {
	int hashValue = 0;
	for (int i = 0; key[i] != '\0'; i++) {
		hashValue += key[i];
	}
	return (hashValue + 1) % SIZE;
}
HashTable* createHashTable() {
	HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
	if (hashTable == NULL) {
		printf("error\0");
		return NULL;
	}
	for (int i = 0; i < SIZE; i++) {
		hashTable->table[i].key = NULL;
		hashTable->table[i].value = NULL;
		hashTable->table[i].occupied = false;
	}
	return hashTable;
}
void printHashMap(const HashTable* hashTable) {
	printf("Your hash map:\0");
	for (int i = 0; i < SIZE; i++) {
		if (hashTable->table[i].occupied) {
			printf("KEY %s  VALUE %s\0", hashTable->table[i].key, hashTable->table[i].value);
		}
	}
	printf("\0");
}
bool addEntry(HashTable* hashTable, char* key, char* value) {
	int index = hash(key);
	int step = hash2(key);
	while (hashTable->table[index].occupied) {
		if (strcmp(hashTable->table[index].key, key) == 0) {
			printf("The key is already exist\0");
			return false;
		}
		index = (index + step) % SIZE;
	}
	hashTable->table[index].key = _strdup(key);
	hashTable->table[index].value = _strdup(value);
	hashTable->table[index].occupied = true;
	return true;
}
char* getValue(HashTable* hashTable, char* key) {
	int index = hash(key);
	int step = hash2(key);
	while (hashTable->table[index].occupied) {
		if (strcmp(hashTable->table[index].key, key) == 0) {
			return hashTable->table[index].value;
		}
		index = (index + step) % SIZE;
	}
	return NULL;
}
bool removeEntry(HashTable* hashTable, char* key) {
	int index = hash(key);
	int step = hash2(key);
	int count = 0;

	while (hashTable->table[index].occupied && count < SIZE - 1) {
		if (strcmp(hashTable->table[index].key, key) == 0) {
			free(hashTable->table[index].key);
			free(hashTable->table[index].value);
			hashTable->table[index].key = NULL;
			hashTable->table[index].value = NULL;
			hashTable->table[index].occupied = false;
			return true;
		}
		index = (index + step) % SIZE;
		count++;
	}

	return false;
}

int hashSet(char* value) {
	int hash = 0;
	for (int i = 0; i < strlen(value); i++) {
		hash = (hash * 31 + value[i]) % SIZE;
	}
	return hash;
}

char* pr2(char* str) {

	static HashTable* hashTable = NULL;
	if (hashTable == NULL)
	{
		hashTable = malloc(sizeof(HashTable));
		for (int i = 0; i < SIZE; i++) {
			hashTable->table[i].key = NULL;
			hashTable->table[i].value = NULL;
			hashTable->table[i].occupied = false;
		}
	}
			if (strstr(str, "PUSH") != NULL)
			{
				char temp[] = "!";
				char* stroka;
				int count = 0;
				char short_link[9];
				char original_link[100];
				stroka = strtok(str, temp);
				while (stroka != NULL) {
					count++;
					if (count == 2) {
						strncpy(short_link, stroka, 8);
						short_link[8] = '\0';
					}
					if (count == 3) {
						strcpy(original_link, stroka);
						break;
					}
					stroka = strtok(NULL, temp);
				}
				if (addEntry(hashTable, short_link, original_link) == true)
					return "Success\0";
				else
					return "Success\0";
			}
			else if (strstr(str, "HGET") != NULL) {
				char temp[] = " ";
				char* stroka;
				int count = 0;
				char key[100];
				stroka = strtok(str, temp);
				while (stroka != NULL) {
					count++;
					if (count == 2) {
						// ÑPÑÄÑ|ÑÖÑâÑuÑ~ÑyÑu short_link ÑyÑx ÑÉÑÑÑÇÑÄÑ{Ñy
						char* shortLink = stroka + 5; // ÑPÑÇÑÄÑÅÑÖÑÉÑ{ÑpÑuÑ} "HGET!"
						if (strlen(shortLink) == 8) {
							strcpy(key, shortLink);
							break;
						}
						else {
							return "error\0";
						}
					}
					stroka = strtok(NULL, temp);
				}
				char* copystr = _strdup(key);
				copystr[strlen(copystr) - 1] = '\0';
				if (getValue(hashTable, copystr) != NULL) {
					return getValue(hashTable, copystr);
				}
				else {
					return "error\0";
				}
			}
			else
			{
				return"error\0";
			}	
}