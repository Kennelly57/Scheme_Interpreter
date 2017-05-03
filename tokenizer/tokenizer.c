#include "value.h"
#include "tokenizer.h"
#include <string.h>
#include "linkedlist.h"
#include "talloc.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Read all of the input from stdin, and return a linked list consisting of the
// tokens.
Value *tokenize(){
    char charRead;
    Value *list = makeNull();
    charRead = fgetc(stdin);
    char* symbolSet = "!$%&*/:<=>?~_^+-";
    char* letterSet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* numberSet = ".0123456789";
    while (charRead != -1) {
        if (charRead == '(') {
            Value *val = talloc(sizeof(Value));
            val->type = OPEN_TYPE;
            val->s = "(";
            list = cons(val, list);
        } else if (charRead == ')') {
            Value *val = talloc(sizeof(Value));
            val->type = CLOSE_TYPE;
            val->s = ")";
            list = cons(val, list);
        } else if (charRead == ';'){
            while (charRead != '\n' && charRead != -1){
                charRead = fgetc(stdin);
            }
        }else if(charRead == '\''){
            printf("entered");
            char *temp = talloc(100*sizeof(char));
            int counter = 0;
            while (charRead != '\''){
                temp[counter] = charRead;
                counter++;
                charRead = fgetc(stdin);
            }
            Value *val = talloc(sizeof(Value));
            val->type = STR_TYPE;
            val->s = temp;
            list = cons(val, list);
        } else if (strchr(symbolSet, charRead)){
            Value *val = talloc(sizeof(Value));
            val->type = SYMBOL_TYPE;
            char *temp = talloc(2*sizeof(char));
            if(charRead == '#'){
                val->s = talloc(3*sizeof(char));
                val->s[0] = charRead;
                charRead = fgetc(stdin);
                if(charRead == 't' || charRead == 'f'){
                    val->s[1] = charRead;
                }else{
                    printf("Syntax error: untokenizable");
                }
            }else{
                temp[0] = charRead;
                val->s = temp;
            }
            list = cons(val, list);
        } else if (strchr(letterSet, charRead)){
            char *temp = talloc(100*sizeof(char));
            int counter = 0;
            while ((strchr(letterSet, charRead) || (strchr(numberSet, charRead)))){
                temp[counter] = charRead;
                counter++;
                charRead = fgetc(stdin);
            }
            charRead = ungetc(charRead, stdin);
            Value *val = talloc(sizeof(Value));
            val->type = SYMBOL_TYPE;
            val->s = temp;
            list = cons(val, list);
        } else if(strchr(numberSet, charRead)){
            char *temp = talloc(100*sizeof(char));
            int counter = 0;
            int flag = 0;
            while (strchr(numberSet, charRead)){
                temp[counter] = charRead;
                counter++;
                charRead = fgetc(stdin);
                if (charRead == '.'){
                    flag = 1;
                }
            }
            charRead = ungetc(charRead, stdin);
            Value *val = talloc(sizeof(Value));
            char *end;
            if (flag == 0){
                val->type = INT_TYPE;
                val->i = strtol(temp, &end, 10);
            } else {
                val->type = DOUBLE_TYPE;
                val->d = strtod(temp, &end);
            }
            list = cons(val, list);
        }
        charRead = fgetc(stdin);
    }
    Value *revList = reverse(list);
    return revList;
}

// Displays the contents of the linked list as tokens, with type information

void displayTokens(Value *list){
    assert(list->type == CONS_TYPE);
    while(list->type != NULL_TYPE){
        switch (list->c.car->type) {
            case INT_TYPE:
                printf("%i: integer\n", list->c.car->i);
                break;
            case DOUBLE_TYPE:
                printf("%f: float\n" , list->c.car->d);
                break;
            case STR_TYPE:
                printf("%s: string\n", list->c.car->s);
                break;
            case NULL_TYPE:
                break;
            case CONS_TYPE:
                break;
            case PTR_TYPE:
                break;
            case OPEN_TYPE:
                printf("%s: open\n", list->c.car->s);
                break;
            case CLOSE_TYPE:
                printf("%s: close\n", list->c.car->s);
                break;
            case BOOL_TYPE:
                printf("%i: boolean\n", list->c.car->i);
                break;
            case SYMBOL_TYPE:
                printf("%s: symbol\n", list->c.car->s);
                break;
        }
        list = list -> c.cdr;
  }
}
