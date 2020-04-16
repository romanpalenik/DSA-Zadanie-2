
typedef struct tree_BVS{
    int value;
    struct tree_BVS* left;
    struct tree_BVS* right;
}TREE_BVS;

TREE_BVS* create_BVS(int paVal)
{
    TREE_BVS *new = malloc(sizeof(TREE_BVS));
    new->value = paVal;
    new->left = NULL;
    new->right = NULL;
    return new;

}



TREE_BVS* insert_BVS(long value,TREE_BVS*root) {

    TREE_BVS *akt = root;
    if (root == NULL) {
        return create_BVS(value);

    }

    while (1) {
        if (akt->value < value && akt->right != NULL) {
            akt = akt->right;
        } else if (akt->value > value && akt->left != NULL) {
            akt = akt->left;
        } else if (akt->value < value && akt->right == NULL) {
            akt->right = create_BVS(value);
            return root;
        } else if (akt->value > value && akt->left == NULL) {
            akt->left = create_BVS(value);
            return root;
        }
    }
}

TREE_BVS* search_BVS(int value, TREE_BVS *akt) {

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

void deleteTree_BVS(TREE_BVS** root){
    if(*root == NULL) {
        free(*root);
        return;
    }
    deleteTree_BVS(&(*root)->left);
    deleteTree_BVS(&(*root)->right);
    free(*root);
    *root = NULL;
}
