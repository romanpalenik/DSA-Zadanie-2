
typedef struct cell{
    int key;
    struct cell* next;
}CELL;

typedef struct Info{
    CELL **table;
    int size;
    int number_of_elements;
}INFO;

int hash(int number,int size);
void create_new_table(INFO *info);
void insert_hash(int number, INFO *info);
void resize(INFO *info,int stara_vyska);
void print_hash(INFO *info);
void freeTable(INFO **table);
int isPrime(int n);
int nextPrime(int N);
CELL* search_hash(INFO *info,int key);
CELL* new_node_hash(int number);


int hash(int number, int size)
{
    return (number)%(size);

}

void create_new_table(INFO *info)
{
    CELL** new_table = (CELL**)malloc(info->size* sizeof(CELL*));
    for (int i = 0; i < info->size; i++) {
        new_table[i] = NULL;
    }
    info->table = new_table;
}

CELL* new_node_hash(int number) {
    CELL *new;
    new = (CELL *) malloc(sizeof(CELL));
    new->key = number;
    new->next = NULL;
    return new;
}


void insert_hash(int number, INFO *info) {
    CELL *temp;
    int size = info->size;
    info->number_of_elements +=1;
    CELL **table = info->table;
    int position_in_table = hash(number,size);
    if(table[position_in_table]!=NULL && table[position_in_table]->key == number) return;
    if(table[position_in_table]==NULL) {
        table[position_in_table] = new_node_hash(number);
    }
    else
    {
        temp = table[position_in_table];
        while(temp->next!=NULL) {
            if(temp->key == number) return;
            temp = temp->next;
        }
        temp->next = new_node_hash(number);
    }
    info->table = table;

}


void resize(INFO *info,int stara_vyska)
{

    CELL *vypis;
    info->number_of_elements=0;
    CELL **table = info->table;

    create_new_table(info);

    for(int i=0;i<stara_vyska;i++)
    {
        if(table[i]!=NULL) {
            vypis = table[i];
            if(table[i]->next==NULL) insert_hash(vypis->key,info);
            else //chcem vypísať ten linked list
            {
                while(vypis->next!=NULL){
                    insert_hash(vypis->key,info);
                    vypis = vypis->next;
                }
                insert_hash(vypis->key,info);
            }
        }

    }
}

void print_hash(INFO *info)
{
    CELL *vypis;
    for(int i=0;i<info->size;i++)
    {
        if(info->table[i]!=NULL) {
            vypis = info->table[i];
            if(info->table[i]->next==NULL) printf("%d",info->table[i]->key);
            else //chcem vypísať ten linked list
            {
                while(vypis->next!=NULL){
                    printf("%d", vypis->key);
                    printf("->");
                    vypis = vypis->next;
                }
                printf("%d", vypis->key);
            }

        }
        else
        {
            printf("NULL");
        }
        printf("\n");
    }


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

CELL* search_hash(INFO *info,int key) {

    int size = info->size;
    CELL *temp;
    CELL **table = info->table;
    int position_in_table = (key) % (size);
    if (table[position_in_table]->key == key) return table[position_in_table];
    else {
        temp = table[position_in_table]->next;
        {
            while (temp->next != NULL) {
                if(temp->key==key)
                {
                    return temp;
                }
                temp = temp->next;
            }
            return temp;

        }
    }
}

void freeTable(INFO **table) {                                                     //uvoľnenie tabuľky
    CELL *temp, *next;
    for (int i = 0; i < (*table)->size; i++) {
        temp = (*table)->table[i];
        while (temp != NULL) {
            next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(*table);
    *table = NULL;
}

