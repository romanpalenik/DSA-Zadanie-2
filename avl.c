
typedef struct tree{
        int value;
        int height;
        struct tree* left;
        struct tree* right;
    }TREE;




int SetHeight(TREE *akt)
{
    if(akt!=NULL) {
        int lava = 0, prava = 0, max = 0;

        if ((akt->left) == NULL) lava = 0;
        if ((akt->right) == NULL) prava = 0;
        if ((akt->left) != NULL) lava = (akt->left)->height;
        if ((akt->right) != NULL) prava = (akt->right)->height;

        max = __max(lava, prava);
        akt->height = 1 + max;
    }

}

int CalculateBalanceFactor(TREE *akt){

    int lava,prava;
    if ((akt->left) == NULL) lava = 0;
    if ((akt->right) == NULL) prava = 0;
    if ((akt->left) != NULL) lava = (akt->left)->height;
    if ((akt->right) != NULL) prava = (akt->right)->height;
    return lava-prava;


}

TREE* create(int paVal)
    {
        TREE *new = malloc(sizeof(TREE));
        new->value = paVal;
        new->left = NULL;
        new->right = NULL;
        new->height=1;
        return new;

        }

TREE* Left_Right(TREE *akt)
{

    TREE *stred = NULL, *pravy = NULL, *lavy = NULL, *pravy_lave_dieta = NULL,*lavy_prave_dieta;

    stred = akt->left->right;
    lavy = akt->left;
    pravy = akt;


    lavy_prave_dieta = stred->left;
    pravy_lave_dieta = stred->right;

    stred->right = pravy;
    stred->left = lavy;

    lavy->right = lavy_prave_dieta;
    pravy->left = pravy_lave_dieta;

    SetHeight(lavy);
    SetHeight(pravy);
    SetHeight(stred);

    return stred;
}


TREE* Right_LEFT(TREE *akt){

    TREE *stred = NULL, *pravy = NULL, *lavy = NULL,  *pravy_lave_dieta = NULL,  *lavy_prave_dieta=NULL;

    stred = akt->right->left;
    lavy = akt;
    pravy = akt->right;

    pravy_lave_dieta = stred->right;
    lavy_prave_dieta = stred->left;

    stred->right = pravy;
    stred->left = lavy;

    lavy->right = lavy_prave_dieta;
    pravy->left =  pravy_lave_dieta;

    SetHeight(lavy);
    SetHeight(pravy);
    SetHeight(stred);

    return stred;
}

TREE* LL_Balance(TREE *akt)
    {
        TREE *stred = NULL, *pravy = NULL, *lavy = NULL, *docasny =NULL;

        docasny = akt->left->right;
        stred = akt->left;
        lavy = stred->left;
        pravy = akt;

        stred->right =pravy;
        stred->left = lavy;
        pravy->left = docasny;

        SetHeight(lavy);
        SetHeight(pravy);
        SetHeight(stred);

        return stred;
    }

TREE* PP_Balance(TREE *akt)
{
    TREE *stred = NULL, *pravy = NULL, *lavy = NULL, *docasny = NULL;

    stred = akt->right;    //vytvorenie stredneho, laveho a pravého
    docasny = stred->left; //ak stredný mal potomka naľavo nemôžem ho stratiť ale presmerovať na opačnú vetvu stromu
    lavy = akt;
    pravy = stred->right;

    stred->right = pravy;
    stred->left = lavy;
    lavy->right = docasny;

    SetHeight(lavy);
    SetHeight(pravy);
    SetHeight(stred);

    return stred;

}

TREE* insert(long value, TREE *akt) {

        int max = 0,lava,prava;
        if (akt == NULL) {

            return create(value);

        } else {
            if (akt->value < value) {

                akt->right = insert(value, akt->right);
                
            } else if (akt->value > value) {

                akt->left = insert(value, akt->left);
            }
            else return akt;

        }
        if((akt->left)==NULL) lava=0;
        if((akt->right)==NULL) prava = 0;
        if((akt->left)!=NULL) lava = (akt->left)->height;
        if((akt->right)!=NULL) prava = (akt->right)->height;

        max=__max(lava,prava);
        akt->height = 1 + max;

        int balanceFactor = lava - prava; //na základe tohto výpočtu kontrolujem, či je strom prevážený na nejakú stranu

        if(balanceFactor == -2)
        {
            if(CalculateBalanceFactor(akt->right)>0){ //pozriem sa na základ výšok, či som ešte aj preťaženy na ľavo

                akt = Right_LEFT(akt); //riešim to preskupenie v jednej funkcii
            }
            else akt = PP_Balance(akt);
        }

        if(balanceFactor == 2)
        {
            if(CalculateBalanceFactor(akt->left)<0){ //pozriem sa na základ výšok, či som ešte aj preťaženy na pravo

                akt = Left_Right(akt); //riešim to preskupenie v jednej funkcii
            }
            else akt = LL_Balance(akt);
        }
        return akt; //vráti mi to do predchádzajúceho smerníka aktuálny, čím zabezpečím spojeneie podstromu s jeho "rodičom"
    }

TREE* search_AVL(int value, TREE *akt) {

   while(1)
   {
       if(akt->value==value)
       {
           return akt;
       }
       else
           {
           if(akt->value > value) akt = akt->left;
           if(akt->value < value) akt = akt->right;
           }

   }
}

void inOrder(TREE* node) {
    if (node == NULL) {
        return;
    }

    inOrder(node->left);
    printf(" %d", node->value);
    inOrder(node->right);
}
