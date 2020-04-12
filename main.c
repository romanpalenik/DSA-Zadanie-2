#include <stdio.h>
#include <stdlib.h>
#include <rpc.h>
#include "Red-Black.c"
#include "hash.c"
#include "avl.c"
#include "hash_linear.c"
#define SIZE 10000000
#define KONIEC_TESTU      printf("%f\n", (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart);
#define ZACIATOK_TESTU  QueryPerformanceFrequency(&frequency); QueryPerformanceCounter(&start);

#define ERR_NO_NUM -1
#define ERR_NO_MEM -2



int myRandom(int size) {

    srand(0);
    int i, n;
    static int numNums = 0;
    static int *numArr = NULL;

    // Initialize with a specific size.

    if (size >= 0) {
        if (numArr != NULL)
            free(numArr);
        if ((numArr = malloc(sizeof(int) * size)) == NULL)
            return ERR_NO_MEM;
        for (i = 0; i < size; i++)
            numArr[i] = i;
        numNums = size;
    }

    // Error if no numbers left in pool.

    if (numNums == 0)
        return ERR_NO_NUM;

    // Get random number from pool and remove it (rnd in this
    //   case returns a number between 0 and numNums-1 inclusive).

    n = rand() *rand() % numNums;
    i = numArr[n];
    numArr[n] = numArr[numNums - 1];
    numNums--;
    if (numNums == 0) {
        free(numArr);
        numArr = 0;
    }
    return i;

}
int* random_array(int array[]) {

    int i,pozicia=0;
    i = myRandom(SIZE);
    while (i >= 0) {
        array[pozicia] = i;
        pozicia++;
        i = myRandom(-1);
    }
    return array;
}


void test1_insert();
void test2_search();
void test3_insert_search();

void test1_insert_a();
void test2_a_search();
void test3_a_insert_search();


void test1_random();
void test2_random();
void test3_random();



void test1_insert()
{
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    ZACIATOK_TESTU

        for (int i = 0; i < SIZE; i++)
        {
            root = insert(i, root);
        }
        
    KONIEC_TESTU
    deleteTree(&root);


    ////red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;

  ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        red_black_insert(i);
    }
    
    KONIEC_TESTU


//hash

    INFO *info = (INFO*)malloc(sizeof(INFO));
    info->size=13;
    info->number_of_elements = 0;
    create_new_table(info);
    int old_size;

    ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++)
    {
        insert_hash(i,info);
        if ((double )(info->number_of_elements) / (info->size) > 1.5)
        {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
    }

    KONIEC_TESTU
    freeTable(&info);


//hash linear

    hashArray = (struct DataItem**) malloc(SIZE_Hash *sizeof(struct DataItem*));
    init();
   
    ZACIATOK_TESTU
    
    for(int i = 0; i < SIZE; i++){
        insert_Linear(i,1);
    }
    
    
    KONIEC_TESTU

}

void test2_search()
{
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    for (int i = 0; i < SIZE; i++)
    {
        root = insert(i, root);
    }

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++)
    {
        search_AVL(i,root);
    }
    


    KONIEC_TESTU
    deleteTree(&root);



    ////red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;


    for (int i = 0; i < SIZE; i++) {
        red_black_insert(i);
    }

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        tree_search(i);
    }
    

    KONIEC_TESTU


//hash

    INFO *info = (INFO*)malloc(sizeof(INFO));
    info->size=13;
    info->number_of_elements = 0;
    create_new_table(info);
    int old_size;


    for (int i = 0; i < SIZE; i++)
    {
        insert_hash(i,info);
        if ((double )(info->number_of_elements) / (info->size) > 1.5)
        {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
    }
   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        search_hash(info,i);
    }

    
    freeTable(&info);
    KONIEC_TESTU


//hash linear
    hashArray = (struct DataItem**) malloc(SIZE_Hash *sizeof(struct DataItem*));
    init();

    for(int i = 0; i < SIZE; i++){
        insert_Linear(i,1);
    }

   ZACIATOK_TESTU

    for(int i = 0; i < SIZE; i++){
        search_hash_linear(i);
    }

    
    
    KONIEC_TESTU
}

void test3_insert_search()
{
    ///AVL
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++)
    {
        root = insert(i, root);
    }
    for (int i = 0; i < SIZE; i++)
    {
        search_AVL(i,root);
    }

    
    deleteTree(&root);
    KONIEC_TESTU


    /////red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;
    ROOT = NILL;

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        red_black_insert(i);
    }

    for (int i = 0; i < SIZE; i++) {
        tree_search(i);
    }

    
    KONIEC_TESTU


    ///chaining-hash

    INFO *info = (INFO*)malloc(sizeof(INFO));
    info->size=13;
    info->number_of_elements = 0;
    create_new_table(info);
    int old_size;

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++)
    {
        insert_hash(i,info);
        if ((double )(info->number_of_elements) / (info->size) > 1.5)
        {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
    }
    for (int i = 0; i < SIZE; i++) {
        search_hash(info,i);
    }

    
    freeTable(&info);
    KONIEC_TESTU


    ///hash linear

    hashArray = (struct DataItem**) malloc(SIZE_Hash *sizeof(struct DataItem*));
    init();

   ZACIATOK_TESTU

    for(int i = 0; i < SIZE; i++){
        insert_Linear(i,1);
    }
    for(int i = 0; i < SIZE; i++){
        search_hash_linear(i);
    }

    
    
    KONIEC_TESTU


}

void test1_insert_a()
{
    ///AVL
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE/2; i++) {
        root = insert(i, root);
        root = insert(SIZE-i,root);
    }
    
    KONIEC_TESTU


    /////red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;
    ROOT = NILL;

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE/2; i++) {
        red_black_insert(i);
        red_black_insert(SIZE-i);
    }

    
   KONIEC_TESTU


    ///chain-hash
    INFO *info = (INFO*)malloc(sizeof(INFO));
    info->size=13;
    info->number_of_elements = 0;
    create_new_table(info);
    int old_size;

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE/2; i++)
    {
        insert_hash(i,info);
        if ((double )(info->number_of_elements) / (info->size) > 1.5)
        {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
        insert_hash(SIZE-i,info);
        if ((double )(info->number_of_elements) / (info->size) > 1.5)
        {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
    }

    
    KONIEC_TESTU


    ///linear hash

    hashArray = (struct DataItem**) malloc(SIZE_Hash *sizeof(struct DataItem*));
    init();
   ZACIATOK_TESTU

    for(int i = 0; i < SIZE; i++){
        insert_Linear(i,1);
        insert_Linear(SIZE-i,1);
    }

    
    
    KONIEC_TESTU
}

void test2_a_search()
{
    ///AVL
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    for (int i = 0; i < SIZE/2; i++) {
        root = insert(i, root);
        root = insert(SIZE-i,root);
    }

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE/2; i++) {
        search_AVL(i, root);
        search_AVL(SIZE-i, root);
    }

    
    KONIEC_TESTU


    /////red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;
    ROOT = NILL;

    for (int i = 0; i < SIZE/2; i++) {
        red_black_insert(i);
        red_black_insert(SIZE-i);
    }

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE/2; i++) {
        tree_search(i);
        tree_search(SIZE-i);
    }

    
    KONIEC_TESTU

    ///hash

    INFO *info = (INFO*)malloc(sizeof(INFO));
    info->size=13;
    info->number_of_elements = 0;
    create_new_table(info);
    int old_size;


    for (int i = 0; i < SIZE/2; i++)
    {
        insert_hash(i,info);
        if ((double )(info->number_of_elements) / (info->size) > 1.5)
        {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
        insert_hash(SIZE-i,info);
        if ((double )(info->number_of_elements) / (info->size) > 1.5)
        {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
    }
   ZACIATOK_TESTU

    for (int i = 0; i <SIZE/2 ; ++i)
    {
        search_hash(info,i);
        search_hash(info,SIZE-i);
    }

    
    KONIEC_TESTU

    ///linear hash
    hashArray = (struct DataItem**) malloc(SIZE_Hash *sizeof(struct DataItem*));
    init();

    for(int i = 0; i < SIZE/2; i++){
        insert_Linear(i,1);
        insert_Linear(SIZE-i,1);
    }

   ZACIATOK_TESTU
    for(int i = 0; i < SIZE/2; i++){
        search_hash_linear(i);
        search_hash_linear(SIZE-i);
    }

    
    
    KONIEC_TESTU
}

void test3_a_insert_search()
{
    ///AVL
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE/2; i++) {
        root = insert(i, root);
        root = insert(SIZE-i,root);
    }
    for (int i = 0; i < SIZE/2; i++) {
        search_AVL(i, root);
        search_AVL(SIZE-i, root);
    }

    
    KONIEC_TESTU


    /////red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;
    ROOT = NILL;

   ZACIATOK_TESTU
    for (int i = 0; i < SIZE/2; i++) {
        red_black_insert(i);
        red_black_insert(SIZE-i);
    }
    for (int i = 0; i < SIZE/2; i++) {
        tree_search(i);
        tree_search(SIZE-i);
    }

    
    KONIEC_TESTU

    ///hash

    INFO *info = (INFO*)malloc(sizeof(INFO));
    info->size=13;
    info->number_of_elements = 0;
    create_new_table(info);
    int old_size;

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE/2; i++)
    {
        insert_hash(i,info);
        if ((double )(info->number_of_elements) / (info->size) > 1.5)
        {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
        insert_hash(SIZE-i,info);
        if ((double )(info->number_of_elements) / (info->size) > 1.5)
        {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
    }

    for (int i = 0; i <SIZE/2 ; ++i)
    {
        search_hash(info,i);
        search_hash(info,SIZE-i);
    }


    
    KONIEC_TESTU


    ///linear hash

    hashArray = (struct DataItem**) malloc(SIZE_Hash *sizeof(struct DataItem*));
    init();

   ZACIATOK_TESTU

    for(int i = 0; i < SIZE/2; i++){
        insert_Linear(i,1);
        insert_Linear(SIZE-i,1);
    }
    for(int i = 0; i < SIZE/2; i++){
        search_hash_linear(i);
        search_hash_linear(SIZE-i);
    }

    KONIEC_TESTU
}

void test1_random() {

   int array2 = (int*)malloc(SIZE* sizeof(int));
   int *array;
   array = random_array(array2);


    ///AVL
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        root = insert(array[i], root);
    }

    
    deleteTree(&root);

    KONIEC_TESTU

    /////red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;
    ROOT = NILL;

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        red_black_insert(array[i]);
    }

    KONIEC_TESTU

    ///chain-hash

    INFO *info = (INFO *) malloc(sizeof(INFO));
    info->size = 13;
    info->number_of_elements = 0;
    create_new_table(info);
    int old_size;

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        insert_hash(array[i], info);
        if ((double) (info->number_of_elements) / (info->size) > 1.5) {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
    }

    
    KONIEC_TESTU


    ///linear hash

    hashArray = (struct DataItem **) malloc(SIZE_Hash * sizeof(struct DataItem *));
    init();

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        insert_Linear(array[i], 1);
    }

    
    
    KONIEC_TESTU
}

void test2_random()
{
    int array2 = (int*)malloc(SIZE* sizeof(int));
    int *array;
    array = random_array(array2);

    ///AVL
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    for (int i = 0; i < SIZE; i++) {
        root = insert(array[i], root);
    }

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        search_AVL(array[i],root);
    }

    
    deleteTree(&root);
    KONIEC_TESTU


    /////red-black
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

    ///chain-hash

    INFO *info = (INFO *) malloc(sizeof(INFO));
    info->size = 13;
    info->number_of_elements = 0;
    create_new_table(info);
    int old_size;


    for (int i = 0; i < SIZE; i++) {
        insert_hash(array[i], info);
        if ((double) (info->number_of_elements) / (info->size) > 1.5) {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
    }
   ZACIATOK_TESTU

    for(int i=0;i<SIZE;i++)
    {
        search_hash(info,array[i]);
    }

    
    KONIEC_TESTU


    ///linear hash

    hashArray = (struct DataItem **) malloc(SIZE_Hash * sizeof(struct DataItem *));
    init();

    for (int i = 0; i < SIZE; i++) {
        insert_Linear(array[i], 1);
    }
   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        search_hash_linear(array[i]);
    }

    
    
    KONIEC_TESTU

}

void test3_random()
{
    int array2 = (int*)malloc(SIZE* sizeof(int));
    int *array;
    array = random_array(array2);

    ///AVL
    TREE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        root = insert(array[i], root);
    }

    for (int i = 0; i < SIZE; i++) {
        search_AVL(array[i],root);
    }

    
    deleteTree(&root);
    KONIEC_TESTU


    /////red-black
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;
    ROOT = NILL;

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        red_black_insert(array[i]);
    }

    for (int i = 0; i < SIZE; i++) {
        tree_search(array[i]);
    }

    
    KONIEC_TESTU

    ///chain-hash

    INFO *info = (INFO *) malloc(sizeof(INFO));
    info->size = 13;
    info->number_of_elements = 0;
    create_new_table(info);
    int old_size;

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        insert_hash(array[i], info);
        if ((double) (info->number_of_elements) / (info->size) > 1.5) {
            old_size = info->size;
            info->size = nextPrime(info->size * 2);
            resize(info, old_size);
        }
    }


    for(int i=0;i<SIZE;i++)
    {
        search_hash(info,array[i]);
    }

    
    KONIEC_TESTU


    ///linear hash

    hashArray = (struct DataItem **) malloc(SIZE_Hash * sizeof(struct DataItem *));
    init();

   ZACIATOK_TESTU

    for (int i = 0; i < SIZE; i++) {
        insert_Linear(array[i], 1);
    }
    for (int i = 0; i < SIZE; i++) {
        search_hash_linear(array[i]);
    }

    
    
    KONIEC_TESTU

}


void test_linear_small_to_big()
{
   // test1_insert();
    //test2_search();
    //test3_insert_search();

}

void test_alternujuco()
{
    test1_insert_a();
    // test2_a_search();
    //test3_a_insert_search();
}

void test_random()
{
    test1_random();
    //test2_random();
    //test3_random();
}






int main() {

    //test_linear_small_to_big();
    //test_alternujuco();
    // test_random();

        return 0;

}