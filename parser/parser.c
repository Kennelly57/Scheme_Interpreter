/* Written by Jack Kennelly on 5/11/2017. Parses through tokenized scheme code. */

#include "value.h"
#include "linkedlist.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include "talloc.h"


// Prints a parse tree
void printTree(Value *tree){
    
    while(tree->type != NULL_TYPE){
        
        //Recursively prints the different layers of the parse tree.
        if(car(tree)->type == CONS_TYPE){
            printf("(");
            printTree(car(tree));
            printf(")");
        }
        
        switch (car(tree)->type) {
            case INT_TYPE:
                printf("%i ", tree->c.car->i);
                break;
            case DOUBLE_TYPE:
                printf("%f ", tree->c.car->d);
                break;
            case STR_TYPE:
                printf("%s ", tree->c.car->s);
                break;
            case NULL_TYPE:
                break;
            case CONS_TYPE:
                break;
            case PTR_TYPE:
                break;
            case BOOL_TYPE:
                printf("%i ", car(tree)->i);
                break;
            case OPEN_TYPE:
                break;
            case CLOSE_TYPE:
                break;
            case SYMBOL_TYPE:
                printf("%s ", tree->c.car->s);
                break;
        }
        tree = cdr(tree);
      }
}


//Parses the tokenized list, and returns a parse tree.
Value *parse(Value *tokens) {

    Value *stack = makeNull();
    int depth = 0;

    Value *current = tokens;
    assert(current != NULL && "Error (parse): null pointer");
    
    // Iterates through tokens, and appropriately places them into parse tree
    while (current->type != NULL_TYPE) {
        Value *token = car(current);
        
        //Handles close types, which often require adding a new list to the stack
        if (token->type == CLOSE_TYPE){
            Value *tempList = makeNull();
                
            while(stack->type != NULL_TYPE && car(stack) -> type != OPEN_TYPE){
                tempList = cons(car(stack), tempList);
                stack = cdr(stack);
            }
            
            //Handles errors where there are too few open parenthesis
            if (stack->type == NULL_TYPE){
                printf("Parsing Error: Null Type error, check parenthesis\n");
                texit(1);
            }
            
            stack = cdr(stack);
            stack = cons(tempList, stack);
            current = cdr(current);
            depth--;
            
        // Handles open types
        } else if (token->type == OPEN_TYPE){
            depth++;
            stack = cons(token, stack);
            current = cdr(current);
        }
        
        // Handles all other types
        else {
            stack = cons(token, stack);
            current = cdr(current);
        }
    }
    
    // Checks for matching parenthesis issues
    if (depth != 0) {
        printf("Parsing Error: Check parenthesis\n");
        texit(1);
    }
    return reverse(stack);
}
