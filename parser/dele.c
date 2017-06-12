#include "value.h"
#include "linkedlist.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

Value *addToParseTree(Value *tree, int *depth, Value *token){
    
    if(length(tree) == 0){
        cons()
    }
    
    /*
    printf("problem\n");
    Value *current = tree;
    int i;
    if(current->type == NULL_TYPE){
        return cons(tree, current);
    }
    else {
        for (i = 0; i < *depth; i++){
            while (current->type == CONS_TYPE){
                printf("innerproblem\n");
                fflush(stdout);
                current = cdr(current);
                if (current->type == NULL_TYPE){
                    break;
                }
            }
            current = car(car(current));
        }  
    tree = cons(tree, current);
    return tree;
    } */ 
}

Value *parse(Value *tokens) {

    Value *tree = makeNull();
    int depth = 0;
    Value *stack = makeNull;

    Value *current = tokens;
    assert(current != NULL && "Error (parse): null pointer");
    while (current->type != NULL_TYPE) {
        printf("LoopOUTER\n");
        Value *token = car(current);
        if (token->type == CLOSE_TYPE){
            printf("LoopINNER\n");
            Value *tempList = makeNull;
            while(stack->type != OPEN_TYPE){
                tempList = cons(car(tempCurrent), tempList);
                stack = cdr(stack);
            }
            stack = cdr(stack);
            addToParseTree(tree, &depth, tempList);
            depth--;
        } else if (token->type == OPEN_TYPE){
            printf("LoopINNER2\n");
            depth++;
            cons(token, stack);
            current = cdr(current);
        }
        else {
            printf("LoopINNER3\n");
            cons(token, stack);
            current = cdr(current);
        }
    }
    if (depth != 0) {
        //syntaxError(); // error case 4
    }
    return tree;
}

void printTree(Value *tree){
    int x = 0;
}