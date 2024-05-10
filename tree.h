#ifndef TREE_H
#define TREE_H

typedef struct node { 
    char type; // v for value, o for operation
    void *info; // generic pointer
    struct node *parent;
    struct node *lchild; 
    struct node *rchild;
} Node;


typedef struct tree{ 
    Node *root;
} Tree;

Node * cria_node(char type, void *info);

void libera_node(Node *node);


// Operações com árvore
Tree * cria_arvore();

void libera_arvore(Tree *t);

void insere_node_arvore(Tree *t, Node *new_node);

float eval_tree(Tree *t);

char * _get_substring(char *my_string, int start, int finish);

Tree *create_expression_tree(char *expression);

#endif