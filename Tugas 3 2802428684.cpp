#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 26

char hashTable[TABLE_SIZE][100];

int hashFunction(char data[]) {
    return (tolower(data[0]) - 'a') % TABLE_SIZE;
}

void insertData(char data[]) {
    int hashKey = hashFunction(data);
    int originalKey = hashKey;

    while (strlen(hashTable[hashKey]) != 0) {
        hashKey = (hashKey + 1) % TABLE_SIZE;
        if (hashKey == originalKey) {
            printf("Hash Table penuh! Tidak bisa menambahkan '%s'\n", data);
            return;
        }
    }

    
    strcpy(hashTable[hashKey], data);
    printf("Data '%s' dimasukkan ke index [%d].\n", data, hashKey);
}


void viewHashTable() {
    printf("\n===== HASH TABLE =====\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (strlen(hashTable[i]) != 0) {
            printf("INDEX [%d]: %s\n", i, hashTable[i]);
        }
    }
}


void deleteData(char data[]) {
    int hashKey = hashFunction(data);
    int originalKey = hashKey;

    while (strlen(hashTable[hashKey]) != 0) {
        if (strcasecmp(hashTable[hashKey], data) == 0) {
            hashTable[hashKey][0] = '\0'; 
            printf("Data '%s' berhasil dihapus.\n", data);
            return;
        }
        hashKey = (hashKey + 1) % TABLE_SIZE;
        if (hashKey == originalKey) {
            break;
        }
    }
    printf("Data '%s' tidak ditemukan.\n", data);
}


void menu() {
    int choice;
    char data[100];

    do {
        printf("1. Input Data\n");
        printf("2. Lihat Hash Table\n");
        printf("3. Hapus Data\n");
        printf("4. Keluar\n");
        printf("(1-4): ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Input Data: ");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0'; 
                insertData(data);
                break;
            case 2:
                viewHashTable();
                break;
            case 3:
                printf("Masukkan data yang ingin dihapus: ");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0';
                deleteData(data);
                break;
            case 4:
                printf("Keluar dari program...\n");
                return;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (choice != 4);
}


int main() {
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i][0] = '\0';
    }

    
    menu();

    return 0;
}

