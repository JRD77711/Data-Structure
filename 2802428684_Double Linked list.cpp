#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int x;
    struct tnode *prev;
    struct tnode *next;
} *head, *tail;


void push_front(int value) {
    struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));
    node->x = value;
    node->prev = NULL;
    node->next = head;

    if (head == NULL) {
        head = tail = node;
    } else {
        head->prev = node;
        head = node;
    }
}


void push_back(int value) {
    struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));
    node->x = value;
    node->next = NULL;
    node->prev = tail;

    if (head == NULL) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
}


void push_mid(int value, int searchKey) {
    if (head == NULL) {
        printf("List masih kosong, menambahkan di depan.\n");
        push_front(value);
        return;
    }

    struct tnode *curr = head;
    while (curr != NULL) {
        if (curr->x == searchKey) {
            struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));
            node->x = value;
            node->prev = curr;
            node->next = curr->next;

            if (curr->next != NULL) {
                curr->next->prev = node;
            } else {
                tail = node; 
            }

            curr->next = node;
            return;
        }
        curr = curr->next;
    }
    printf("Data %d tidak ditemukan\n", searchKey);
}


void delete_front() {
    if (head == NULL) {
        printf("List kosong, tidak ada data untuk dihapus\n");
        return;
    }

    struct tnode *del = head;
    head = head->next;

    if (head != NULL) {
        head->prev = NULL;
    } else {
        tail = NULL; 
    }

    free(del);
}


void delete_back() {
    if (head == NULL) {
        printf("List kosong, tidak ada data untuk dihapus\n");
        return;
    }

    struct tnode *del = tail;
    tail = tail->prev;

    if (tail != NULL) {
        tail->next = NULL;
    } else {
        head = NULL; 
    }

    free(del);
}


void delete_mid(int searchKey) {
    if (head == NULL) {
        printf("List kosong, tidak ada data untuk dihapus\n");
        return;
    }

    struct tnode *curr = head;
    while (curr != NULL) {
        if (curr->x == searchKey) {
            if (curr == head) {
                delete_front();
            } else if (curr == tail) {
                delete_back();
            } else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                free(curr);
            }
            return;
        }
        curr = curr->next;
    }
    printf("Data %d tidak ditemukan\n", searchKey);
}


void printList() {
    if (head == NULL) {
        printf("List kosong\n");
        return;
    }

    struct tnode *curr = head;
    while (curr != NULL) {
        printf("%d ", curr->x);
        curr = curr->next;
    }
    printf("\n");
}


int main() {
    printf("Double Linked list:\n");
    push_back(13);
    push_back(1);
    push_back(3);
    printList();


    printf("Delete back:\n");
    delete_back();
    printList();

    printf("Delete Mid:\n");
    delete_mid(1);
    printList();

    return 0;
}


