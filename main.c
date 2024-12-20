#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void basic_test(){
    float *f1 = malloc(sizeof(float));
    *f1 = 50;

    float *f2 = malloc(sizeof(float));

    *f2 = 100;

    char *op = malloc(sizeof(float));
    *op = '-';

    Node *node_1 = cria_node('v', f1);
    Node *node_2 = cria_node('o', op);
    Node *node_3 = cria_node('v', f2);
    

    Tree *t = cria_arvore();    
    
    
    insere_node_arvore(t, node_1);
    insere_node_arvore(t, node_2);
    insere_node_arvore(t, node_3);

    float v = eval_tree(t);
    printf("\n");
    // float *test = (float *)node->info;
    printf("Valor das operacoes: %.2f\n", v);

    libera_arvore(t);
}


int main(){

    char *exp = "12+12*3/3";

    Tree *t = create_expression_tree(exp);

    //printf("Node(type: %c, info: %c)\n", t->root->type, *(char *)t->root->info);
    float result_eval = eval_tree(t);
    printf("\n");
    printf("Result: %.2f\n", result_eval);
    //libera_arvore(t);

    return 0;
}