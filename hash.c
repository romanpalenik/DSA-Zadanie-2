#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct cell{
    int value;
    struct cell* next;
}CELL;

typedef struct tabulka{
    int velkost;

}TABULKA;


void insert_hash(int number, CELL **table, int size,int *number_of_elements) {
    CELL *temp,*new,*pred;
    *number_of_elements +=1;
    int position_in_table = (number)%(size);
    if(table[position_in_table]->value == number) return;
    if(table[position_in_table]==NULL) {
        new = (CELL*)malloc(sizeof(CELL));
        new->value = number;
        new->next = NULL;
        table[position_in_table] = new;
    }
    else
    {
        temp = table[position_in_table];
        while(temp->next!=NULL) {
            if(temp->value == number) return;
            temp = temp->next;
        }
        new = (CELL*)malloc(sizeof(CELL));
        new->value = number;
        new->next = NULL;
        temp->next = new;
    }
    //vypočí či treba resize

}


CELL** resize(CELL **table,int size, int stara_vyska)
{
    TABULKA **tabulka;
    tabulka = (TABULKA**)malloc(sizeof(TABULKA*));
    CELL **new_table;
    CELL *vypis;
    int number_of_elemets_r=0;
    new_table=(CELL **)malloc(size *sizeof(CELL *));
    for(int i=0;i<size;i++)
    {
        new_table[i]=NULL;
    }

    for(int i=0;i<stara_vyska;i++)
    {
        if(table[i]!=NULL) {
            vypis = table[i];
            if(table[i]->next==NULL) insert_hash(vypis->value,new_table,size,&number_of_elemets_r);
            else //chcem vypísať ten linked list
            {
                while(vypis->next!=NULL){
                    insert_hash(vypis->value,new_table,size,&number_of_elemets_r);
                    vypis = vypis->next;
                }
                insert_hash(vypis->value,new_table,size,&number_of_elemets_r);
            }
        }

    }
return new_table;
}


int isPrime(int n)
{
    // Corner cases
    if (n <= 1)  return 0;
    if (n <= 3)  return 1;

    // This is checked so that we can skip
    // middle five numbers in below loop
    if (n%2 == 0 || n%3 == 0) return 0;

    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
            return 0;

    return 1;
}

// Function to return the smallest
// prime number greater than N

int nextPrime(int N)
{

    // Base case
    if (N <= 1)
        return 2;

    int prime = N;
    int found = 0;

    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (!found) {
        prime++;

        if (isPrime(prime))
            found = 1;
    }

    return prime;
}

CELL* search_hash(CELL** table,int key,int size) {

    CELL *vypis;
    int position_in_table = (key) % (size);
    if (table[position_in_table]->value == key) return table[position_in_table];
    else {
        vypis = table[position_in_table]->next;
        {
            while (vypis->next != NULL) {
                if(vypis->value==key)
                {
                    return vypis;
                }
                vypis = vypis->next;

            }
            return vypis;

        }

    }
}