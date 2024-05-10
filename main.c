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

    char *str = "abcdef123456hijklmn";

    printf("String: %s\n", str);
    printf("Substring: %s\n", _get_substring(str, 12, 18));

    return 0;
}