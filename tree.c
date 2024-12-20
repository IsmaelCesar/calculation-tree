#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Node  *cria_node(char type, void *info){
    Node *node = malloc(sizeof(Node));

    node->type = type;
    node->info = info;
    node->parent = NULL;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

void _imprime_arvore_pre_ordem(Node *node){
    if(node->lchild != NULL){
        _imprime_arvore_pre_ordem(node->lchild);
    }

    if(node->type == 'o'){
        printf(" %c ", *(char *) node->info);
    }

    if(node->type == 'v'){
        printf(" %.2f ", *(float *) node->info);
    }

    if(node->rchild != NULL){
        _imprime_arvore_pre_ordem(node->rchild);
    }
}

void libera_node(Node *nd){ 
    free(nd);
}

Tree * cria_arvore(){ 
    Tree *t = malloc(sizeof(Tree));
    t->root = NULL;
    return t;
}

void _libera_node_tree(Node *nd){
    if(nd->lchild != NULL){
        _libera_node_tree(nd->lchild);
    }
    if (nd->rchild != NULL){
        _libera_node_tree(nd->rchild);
    }
    libera_node(nd);
}

void libera_arvore(Tree *t){ 
    _libera_node_tree(t->root);
}

Node * _insere_node_valor(Node *node_tree, Node *value_node){
    if (node_tree->lchild == NULL){
        node_tree->lchild = value_node;
        value_node->parent = node_tree;
        return value_node->parent;
    }
    else if(node_tree->rchild == NULL){
        node_tree->rchild = value_node;
        value_node->parent = node_tree;
        return value_node->parent;
    }
    else{
        // verifica sub árvore mais a direita
        node_tree->rchild =  _insere_node_valor(node_tree->rchild, value_node);
        return node_tree;
    }
}

int _get_precedence_value(char operation){
    if (operation == '-' || operation == '+'){
        return 0;
    }
    else if(operation == '*' || operation == '/'){
        return 1;
    }
    return 2;
}

void _set_op_node_lchild(Node *node_tree, Node *op_node){
    op_node->parent = node_tree->parent;
    node_tree->parent = op_node;
    op_node->lchild=node_tree;
}

Node * _insert_new_op_node(Node *node_tree, Node *op_node){

    if(node_tree->type == 'o'){
        char new_node_op = *((char *) op_node->info);
        char node_tree_op  = *((char *) node_tree->info);

        int prec_new_node_op = _get_precedence_value(new_node_op);
        int prec_node_tree_op = _get_precedence_value(node_tree_op);

        if(prec_new_node_op > prec_node_tree_op ){
            node_tree->rchild = _insert_new_op_node(node_tree->rchild, op_node);
            return node_tree;
        }
        else{
            _set_op_node_lchild(node_tree, op_node);
            return op_node;
        }
    }


    _set_op_node_lchild(node_tree, op_node);
    return op_node;

}

void insere_node_arvore(Tree *t, Node *new_node){
    if (t->root == NULL){ // empty tree
        t->root = new_node;
    }
    else if(new_node->type == 'v'){
        t->root = _insere_node_valor(t->root, new_node);
    }
    else{
        t->root = _insert_new_op_node(t->root, new_node);
    }
}


// operations with node
float _get_v_node(Node *node){
    return *((float *) node->info);
}


float _apply_operation(char op_value, float a, float b){
    float result_op = 0; 
    switch (op_value){
    case '+':
        result_op = a + b;
        break;
    case '-':
        result_op = a - b;
        break;
    case '*':
        result_op = a * b;
        break;
    case '/':
        result_op = a / b;
        break;
    }
    return result_op;
}

float _eval_nodes(Node *node){
    float a = 0;
    float b = 0;
    
    if(node->type == 'v'){
        return _get_v_node(node);
    }   

    char operation = *((char *) node->info);

    a = _eval_nodes(node->lchild);
    b = _eval_nodes(node->rchild);

    return _apply_operation(operation, a, b);
}


float eval_tree(Tree *t){
    return _eval_nodes(t->root);
}

// lidando com strings

char * _get_substring(char *my_string, int start, int finish){
    int substring_size = finish - start + 1;

    char *substr = malloc(substring_size *sizeof(char));

    // compia subtring
    for(int substr_idx = 0; substr_idx < substring_size; substr_idx++){
        substr[substr_idx] = my_string[start+substr_idx];
    }
    return substr;
}

Tree *create_expression_tree(char *expression){
    int expression_size = strlen(expression);

    Tree *t = cria_arvore();

    char *val = NULL;
    int start = 0 , finish = 0;

    int exp_idx = 0;

    while(exp_idx < expression_size){

        if(!isdigit(expression[exp_idx])){
            char *operation_char = malloc(sizeof(char));
            *operation_char = expression[exp_idx];

            Node *operation_node = cria_node('o', operation_char);
            insere_node_arvore(t, operation_node);

            exp_idx++;
            start = finish = exp_idx;
        }
        
        while(isdigit(expression[exp_idx])){
            exp_idx++;
            finish++;
        }

        char * number_string = _get_substring(expression, start, finish - 1);

        float *value_c = malloc(sizeof(float));

        *value_c = atof(number_string);

        // inserindo node valor
        Node * value_node = cria_node('v', value_c);

        insere_node_arvore(t, value_node);

    }

    return t;
}
