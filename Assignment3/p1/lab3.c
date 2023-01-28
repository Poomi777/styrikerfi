#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct ListItem {
    struct ListItem *next;
    int value;
};


struct ListItem *listHead = NULL;

void appendItem(int number) {
    // ... implement this
    // append at the end of the list
    struct ListItem *item = (struct ListItem *)malloc(sizeof(struct ListItem));

    item->value = number;
    item->next = NULL;

    if(listHead == NULL){
        listHead = item;
        return;
    }

    struct ListItem *lastel = listHead;
    while(lastel->next != NULL){
        lastel = lastel->next;
    }

    lastel->next = item;

}

int removeFirstItem() {
    // implement this
    // removes the first item from the list and returns its value; returns −1 if list is empty
    if (listHead == NULL){
        return -1;
    }
    
    //tbr means "to be removed"
    struct ListItem *tbr = listHead;
    listHead = listHead->next;

    int val = tbr->value;
    free(tbr);
    return val;
}

    int containsItem(int value) {
    // implement this
    // return true (1) if list contains value, false (0) if not
    struct ListItem *listElement = listHead;
    int isContained = 0;

    while(listElement != NULL){
        if (listElement->value){
            isContained = 1;
        }
        listElement = listElement->next;
    }
    
    return isContained;
}

int isEmpty() {
    // implement this
    // return true (1) if list is empty, false (0) otherweise
    if (listHead == NULL){
        return 1;
    }
    else {
        return 0;
    }

    //nota eitt af þessum, fyrir ofan
    //EÐA
    return listHead == ? 1 : 0;

    //EÐA
    return (listHead==NULL);
}

int main() {
    appendItem(42);
    appendItem(4711);
    removeFirstItem();
    appendItem(42);
    appendItem(4);
    
    for(int i=0; i<5; i++) printf(”%d\n”, removeFirstItem());
}