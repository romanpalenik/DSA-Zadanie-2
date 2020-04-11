#include <stdio.h>
#include <stdlib.h>
#include <rpc.h>
#include "Red-Black.c"
#include "hash.c"
#include "avl.c"
#include "hash_linear.c"
#define SIZE 20000000


void test1_radnom();
void test2_random();
void test3_random();



void test1_insert()
{
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;


    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < SIZE; i++) {
        root = insert(i, root);
    }
    QueryPerformanceCounter(&end);


    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);
    temp =0;


    //red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < SIZE; i++) {
        red_black_insert(i);
    }
    QueryPerformanceCounter(&end);


    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);
    temp =0;


//hash
    int size = 13;
    CELL **table;
    int number_of_elements = 0;
    int stara_size;
    table = (CELL **) malloc(size * sizeof(CELL *));
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);


    for (int i = 0; i < SIZE; i++)
    {
        insert_hash(i, table, size, &number_of_elements);
        if ((double )(number_of_elements) / (size) > 1.5)
        {
            stara_size = size;
            size = nextPrime(size * 2);
            table = resize(table, size, stara_size);
        }
    }

    QueryPerformanceCounter(&end);
    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);

    temp = 0;
    hashArray = (struct DataItem**) malloc(SIZE_Hash *sizeof(struct DataItem*));
    init();
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i < SIZE; i++){
        insert_Linear(i,1);
    }

    QueryPerformanceCounter(&end);
    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);

}

void test2_search()
{
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    TREE *najdeny_smernik=NULL;

    {
        for (int i = 0; i < SIZE; i++) {
            root = insert(i, root);
        }
    } //vytvorenie stromu

    TREE* right_root=NULL;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    right_root=root;

    for (int i = 0; i < SIZE; i++) {
       root = search_AVL(i, right_root);
    }

    QueryPerformanceCounter(&end);

    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);
    temp =0;


    //red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;
    {


        for (int i = 0; i < SIZE; i++) {
            red_black_insert(i);
        }
    } //vytvorenie stromu

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < SIZE; i++) {
        tree_search(i);
    }
    QueryPerformanceCounter(&end);

    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);
    temp =0;


//hash
    int size = 13;
    CELL **table;
    int number_of_elements = 0;
    int stara_size;
    {

        table = (CELL **) malloc(size * sizeof(CELL *));
        for (int i = 0; i < size; i++) {
            table[i] = NULL;
        }

        for (int i = 0; i < SIZE; i++) {
            insert_hash(i, table, size, &number_of_elements);
            if ((double) (number_of_elements) / (size) > 1.5) {
                stara_size = size;
                size = nextPrime(size * 2);
                table = resize(table, size, stara_size);
            }
        }
    }


    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);


    for (int i = 0; i < SIZE; i++) {
        search_hash(table,i,size);
    }

    QueryPerformanceCounter(&end);
    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);

}

void test3_insert_search()
{
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    TREE *najdeny_smernik=NULL;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    {
        for (int i = 0; i < SIZE; i++) {
            root = insert(i, root);
        }
    } //vytvorenie stromu

    TREE* right_root;


    right_root=root;
    for (int i = 0; i < SIZE; i++) {

        search_AVL(i, right_root);
    }

    QueryPerformanceCounter(&end);

    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);
    temp =0;


    //red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    {

        for (int i = 0; i < SIZE; i++) {
            red_black_insert(i);
        }
    } //vytvorenie stromu


    for (int i = 0; i < SIZE; i++) {
        tree_search(i);
    }
    QueryPerformanceCounter(&end);

    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);
    temp =0;


//hash
    int size = 13;
    CELL **table;
    int number_of_elements = 0;
    int stara_size;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    {

        table = (CELL **) malloc(size * sizeof(CELL *));
        for (int i = 0; i < size; i++) {
            table[i] = NULL;
        }

        for (int i = 0; i < SIZE; i++) {
            insert_hash(i, table, size, &number_of_elements);
            if ((double) (number_of_elements) / (size) > 1.5) {
                stara_size = size;
                size = nextPrime(size * 2);
                table = resize(table, size, stara_size);
            }
        }
    }




    for (int i = 0; i < SIZE; i++) {
        search_hash(table,i,size);
    }

    QueryPerformanceCounter(&end);
    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);



}

void test1_insert_a()
{
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;


    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < SIZE/2; i++) {
        root = insert(i, root);
        root = insert(SIZE-i,root);
    }
    QueryPerformanceCounter(&end);


    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("AVL: It took %f\n", temp);
    temp =0;


    //red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < SIZE/2; i++) {
        red_black_insert(i);
        red_black_insert(SIZE-i);
    }
    QueryPerformanceCounter(&end);


    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("RB: It took %f\n", temp);
    temp =0;


//hash
    int size = 13;
    CELL **table;
    int number_of_elements = 0;
    int stara_size;
    table = (CELL **) malloc(size * sizeof(CELL *));
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);


    for (int i = 0; i < SIZE/2; i++)
    {
        insert_hash(i, table, size, &number_of_elements);
        if ((double )(number_of_elements) / (size) > 1.5)
        {
            stara_size = size;
            size = nextPrime(size * 2);
            table = resize(table, size, stara_size);
        }
        insert_hash(SIZE-i, table, size, &number_of_elements);
        if ((double )(number_of_elements) / (size) > 1.5)
        {
            stara_size = size;
            size = nextPrime(size * 2);
            table = resize(table, size, stara_size);
        }
    }

    QueryPerformanceCounter(&end);
    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("Hash: It took %f\n", temp);



}

void test2_a_search()
{
    TREE *root = NULL;
    TREE *najdeny_smernik = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;

    for (int i = 0; i < SIZE/2; i++) {
        root = insert(i, root);
        root = insert(SIZE-i,root);
    }
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < SIZE/2; i++) {
        search_AVL(i, root);
        search_AVL(SIZE-i, root);
    }

    QueryPerformanceCounter(&end);


    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);
    temp =0;


    //red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;

    for (int i = 0; i < SIZE/2; i++) {
        red_black_insert(i);
        red_black_insert(SIZE-i);
    }

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < SIZE/2; i++) {
        tree_search(i);
        tree_search(SIZE-i);
    }

    QueryPerformanceCounter(&end);


    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);
    temp =0;


//hash
    int size = 13;
    CELL **table;
    int number_of_elements = 0;
    int stara_size;
    table = (CELL **) malloc(size * sizeof(CELL *));
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
    for (int i = 0; i < SIZE/2; i++)
    {
        insert_hash(i, table, size, &number_of_elements);
        if ((double )(number_of_elements) / (size) > 1.5)
        {
            stara_size = size;
            size = nextPrime(size * 2);
            table = resize(table, size, stara_size);
        }
        insert_hash(SIZE-i, table, size, &number_of_elements);
        if ((double )(number_of_elements) / (size) > 1.5)
        {
            stara_size = size;
            size = nextPrime(size * 2);
            table = resize(table, size, stara_size);
        }
    }

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);


    for (int i = 0; i < SIZE/2; i++) {
        search_hash(table, i, size);
        search_hash(table, SIZE - i, size);
    }
    QueryPerformanceCounter(&end);
    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);
}

void test3_a_insert_search()
{
    TREE *root = NULL;
    TREE *najdeny_smernik = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < SIZE/2; i++) {
        root = insert(i, root);
        root = insert(SIZE-i,root);
    }

    for (int i = 0; i < SIZE/2; i++) {
        search_AVL(i, root);
        search_AVL(SIZE-i, root);
    }

    QueryPerformanceCounter(&end);

    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);
    temp =0;


    //red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < SIZE/2; i++) {
        red_black_insert(i);
        red_black_insert(SIZE-i);
    }

    for (int i = 0; i < SIZE/2; i++) {
        tree_search(i);
        tree_search(SIZE-i);
    }

    QueryPerformanceCounter(&end);


    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);
    temp =0;


//hash
    int size = 13;
    CELL **table;
    int number_of_elements = 0;
    int stara_size;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    table = (CELL **) malloc(size * sizeof(CELL *));
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
    for (int i = 0; i < SIZE/2; i++)
    {
        insert_hash(i, table, size, &number_of_elements);
        if ((double )(number_of_elements) / (size) > 1.5)
        {
            stara_size = size;
            size = nextPrime(size * 2);
            table = resize(table, size, stara_size);
        }
        insert_hash(SIZE-i, table, size, &number_of_elements);
        if ((double )(number_of_elements) / (size) > 1.5)
        {
            stara_size = size;
            size = nextPrime(size * 2);
            table = resize(table, size, stara_size);
        }
    }

    for (int i = 0; i < SIZE/2; i++) {
        search_hash(table, i, size);
        search_hash(table, SIZE - i, size);
    }

    QueryPerformanceCounter(&end);
    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);
}

void test1_radnom()
{
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    srand(1);

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < SIZE; i++) {

        root = insert(rand()*rand(), root);
    }
    QueryPerformanceCounter(&end);


    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);
    temp =0;


    //red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < SIZE; i++) {
        red_black_insert(rand()*rand());
    }
    QueryPerformanceCounter(&end);


    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);
    temp =0;


//hash
    int size = 13;
    CELL **table;
    int number_of_elements = 0;
    int stara_size;
    table = (CELL **) malloc(size * sizeof(CELL *));
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);


    for (int i = 0; i < SIZE; i++)
    {
        insert_hash(rand()*rand(), table, size, &number_of_elements);
        if ((double )(number_of_elements) / (size) > 1.5)
        {
            stara_size = size;
            size = nextPrime(size * 2);
            table = resize(table, size, stara_size);
        }
    }

    QueryPerformanceCounter(&end);
    temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%f\n", temp);


}


void test2_random()
{

}

void test3_random()
{

}


void test_linear()
{
    test1_insert();
    //test2_search();
    //test3_insert_search();

}

void test_alternujuco()
{
    //test1_a_insert();
   // test2_a_search();
    //test3_a_insert_search();
}

void test_random()
{
    //test1_radnom();
    //test2_random();
    //test3_random();
}







int main() {

    test_linear();
    //test_alternujuco();
    // test_random();
//    root = insert(6,root);
//    root = insert(5,root);
//    root = insert(10,root);
//    root = insert(8,root);
//    root = insert(11,root);
//    root = insert(9,root);


    return 0;

}
