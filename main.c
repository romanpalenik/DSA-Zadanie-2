#include <stdio.h>
#include <stdlib.h>
#include <rpc.h>
#include <math.h>
#include "Red-Black.c"
#include "hash.c"
#include "avl.c"
#include "hash_linear.c"
#include "BVS.c"
#define N1 0
#define SIZE 10000
#define SIZE_FACTOR 1.5
#define KONIEC_TESTU       QueryPerformanceCounter(&end); printf("%f\n", (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart);
#define ZACIATOK_TESTU  QueryPerformanceFrequency(&frequency); QueryPerformanceCounter(&start);





int* random_array() {

    int len = 20000000 - N1 + 1, i, r, temp;
    int *num= (int*)malloc(len* sizeof(int));

    //Fill array with desired numbers
    for (temp = 0, i = N1; temp < len; i++, temp++)
        num[temp] = i;

    srand(0);  //seed rand()

    //Fisher–Yates shuffle algorithm
    for (i = len - 1; i > 0; i--) {
        r = (rand() * rand())% i;   //pop random number
        //swaping using temp
        temp = num[i];
        num[i] = num[r];
        num[r] = temp;
    }
    return num;
}


int *create_array_0_to_n(int n)
{
    int *array=(int*)malloc(n* sizeof(int));
    for(int i=0;i<n;i++)
    {
        array[i] = i;
    }
    return array;

}

int *create_array_n_to_0(int n)
{
    int *array=(int*)malloc(n* sizeof(int));
    for(int i=n-1;i>=0;i--)
    {
        array[i] = i;
    }
    return array;

}

int *create_array_aleternujuco(int n)
{
    int j=0;
    int *array=(int*)malloc(n* sizeof(int));
    for(int i=0;i<n/2;i++)
    {

        array[j] = i;
        array[j+1] = n-i;
        j = j+2 ;
    }
    return array;

}



void insert_test_AVL(int *array)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    TREE *root = NULL;

    ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++)
    {
        root = insert(array[i], root);
    }

    KONIEC_TESTU
    deleteTree(&root);
}

void insert_RB(int *array)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;

    ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        red_black_insert(array[i]);
    }

    KONIEC_TESTU
}

void insert_test_chain_hash(int *array)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    INFO *info = (INFO*)malloc(sizeof(INFO));
    info->size=13;
    info->number_of_elements = 0;
    create_new_table(info);
    int old_size;

    ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++)
    {
        insert_hash(array[i],info);
        if ((double )(info->number_of_elements) / (info->size) > 2.5)
        {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
    }

    KONIEC_TESTU
    freeTable(&info);


}

void insert_test_linear_hash(int *array)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    hashArray = (struct DataItem**) malloc(SIZE_Hash *sizeof(struct DataItem*));
    init();

    ZACIATOK_TESTU

    for(int i = 0; i < SIZE; i++){
        insert_Linear(array[i],1);
    }

    KONIEC_TESTU


}

void insert_test_BVS(int *array)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    TREE_BVS *root=NULL;

    ZACIATOK_TESTU

    for(int i=0 ;i<SIZE ;i++) {
        root = insert_BVS(array[i], root);
    }

    KONIEC_TESTU
    deleteTree_BVS(&root);

}



void test_search_AVL(int *array)
{
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    for (int i = 0; i < SIZE; i++)
    {
        root = insert(array[i], root);
    }

    ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++)
    {
        search_AVL(array[i],root);
    }

    KONIEC_TESTU
    deleteTree(&root);
}

void test_search_RB(int *array)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;


    for (int i = 0; i < SIZE; i++) {
        red_black_insert(array[i]);
    }

    ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        tree_search(array[i]);
    }

    KONIEC_TESTU

}

void test_search_hash_chain(int *array)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;


    INFO *info = (INFO*)malloc(sizeof(INFO));
    info->size=13;
    info->number_of_elements = 0;
    create_new_table(info);
    int old_size;


    for (int i = 0; i < SIZE; i++)
    {
        insert_hash(array[i],info);
        if ((double )(info->number_of_elements) / (info->size) > SIZE_FACTOR)
        {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
    }
    ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        search_hash(info,array[i]);
    }

    KONIEC_TESTU


}

void test_search_hash_linear(int *array)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    struct DataItem *premena;

    hashArray = (struct DataItem**) malloc(SIZE_Hash *sizeof(struct DataItem*));
    init();

    for(int i = 0; i < SIZE; i++){
        insert_Linear(array[i],1);

    }

    ZACIATOK_TESTU

    for(int i = 0; i < SIZE; i++){
      search_hash_linear(array[i]);
    }

    KONIEC_TESTU

}

void test_search_BVS(int *array)
{

    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    TREE_BVS *root=NULL;

    for(int i=0 ;i<SIZE ;i++) {
        root = insert_BVS(array[i], root);
    }

    ZACIATOK_TESTU

    for(int i=0 ;i<SIZE ;i++) {
        search_BVS(array[i], root);
    }

    KONIEC_TESTU
    deleteTree_BVS(&root);

}




void test_insert_search_AVL(int *array)
{
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++)
    {
        root = insert(array[i], root);
        search_AVL(array[i],root);
    }


    KONIEC_TESTU
    deleteTree(&root);


}

void test_insert_search_RB(int *array)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;
    ROOT = NILL;

    ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        red_black_insert(array[i]);
        tree_search(array[i]);
    }


    KONIEC_TESTU

}

void test_insert_search_hash_chain(int *array)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    INFO *info = (INFO*)malloc(sizeof(INFO));
    info->size=13;
    info->number_of_elements = 0;
    create_new_table(info);
    int old_size;

    ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++)
    {
        insert_hash(array[i],info);
        if ((double )(info->number_of_elements) / (info->size) > SIZE_FACTOR)
        {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
        search_hash(info,array[i]);
    }

    freeTable(&info);
    KONIEC_TESTU



}

void test_insert_search_hash_linear(int *array)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    hashArray = (struct DataItem**) malloc(SIZE_Hash *sizeof(struct DataItem*));
    init();

    ZACIATOK_TESTU

    for(int i = 0; i < SIZE; i++){
        insert_Linear(array[i],1);
        search_hash_linear(array[i]);
    }

    KONIEC_TESTU


}

void test_insert_search_BVS(int *array)
{

    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    TREE_BVS *root=NULL;

    ZACIATOK_TESTU

    for(int i=0 ;i<SIZE ;i++) {
        root = insert_BVS(array[i], root);
        search_BVS(array[i], root);
    }

    KONIEC_TESTU
    deleteTree_BVS(&root);


}



void test_insert(int *array)
{

    insert_test_BVS(array);
    insert_test_AVL(array);
    insert_RB(array);
    insert_test_chain_hash(array);
    insert_test_linear_hash(array);


}

void test_search(int *array)
{
    test_search_BVS(array);
    test_search_AVL(array);
    test_search_RB(array);
    test_search_hash_chain(array);
    test_search_hash_linear(array);
}

void test_insert_search(int *array)
{
    test_insert_search_BVS(array);
    test_insert_search_AVL(array);
    test_insert_search_RB(array);
    test_insert_search_hash_chain(array);
    test_insert_search_hash_linear(array);

}




void test_linear(int n)
{
    int *array=NULL;
    array = create_array_0_to_n(n);
    //test_insert(array);
    //test_search(array);
    //test_insert_search(array);
}

void test_linear_nto0(int n)
{
    int *array=NULL;
    array = create_array_n_to_0(n);
    //test_insert(array);
    //test_search(array);
    //test_insert_search(array);
}

void test_alter(int n)
{
    int *array=NULL;
    array = create_array_aleternujuco(n);
    //test_insert(array);
   // test_search(array);
    //test_insert_search(array);
}

void test_random(int n)
{
    int *array=NULL;
    array = random_array();
    //test_insert(array);
    test_search(array);
    //test_insert_search(array);
}







int main() {

    int n=SIZE;
    //test_linear(n);
    //test_linear_nto0(n);
    //test_alter(n);
    test_random(n);


        return 0;

}