#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define KEY_SIZE 30
#define MAX_WIRES 1000
#define MAX_COMMANDS 1000

typedef enum {
    NONE,
    NOT,
    AND,
    OR,
    LSHIFT,
    RSHIFT
} gate_t;

typedef struct {
    int num;
    char key[KEY_SIZE];
    bool is_wire;
} arg_t;

typedef struct {
    char key[KEY_SIZE];
    uint16_t count;
    bool completed;
} wire_t;

typedef struct {
    wire_t *wires;
    uint16_t wire_counter;
    uint16_t max_wires;
} wirelist_t;

typedef struct {
    arg_t args[2];
    gate_t gate_type;
    uint8_t arg_counter;
    char target[KEY_SIZE];
} command_t;



void wreset(wirelist_t *list){
    for(int i=0;i<list->wire_counter;i++){

    }
}

wire_t* wappend(wirelist_t *list, char *key){
    if(list->wire_counter >= list->max_wires){
        return NULL;
    }
    wire_t new_wire;
    strcpy(new_wire.key, key);
    new_wire.count = 0;
    new_wire.completed = false;
    list->wires[list->wire_counter] = new_wire;
    list->wire_counter += 1;
    //printf("Wire Counter: %u\n", list->wire_counter);
    return &(list->wires[list->wire_counter - 1]);
    
}

wire_t* wfind(wirelist_t *list, char *key){
    for(int i=0; i<list->wire_counter; i++){
        //printf("Check key: \"%s\", with target \"%s\"\n", list->wires[i].key, key);
        if(strcmp(key, (list->wires[i]).key) == 0){
            //printf("Found %s with value %u\n", list->wires[i].key, list->wires[i].count);
            return &(list->wires[i]);
        }
    }
    return wappend(list, key);
}


FILE *fptr;

bool isNumeric(char*);
void strstrip(char* str);

bool runCommand(wirelist_t *list, command_t command){
    //printf("Running Command!\n");
    //printf("Trying to find target: \"%s\"\n", command.target);
    wire_t *target = wfind(list, command.target);
    if(target->completed){
        return true;
    }
    uint16_t args[2] = {0}, arg_counter = command.arg_counter;
    for(int i=0; i<arg_counter; i++){
        if(command.args[i].is_wire == true){
            //printf("Trying to find target: \"%s\"\n", command.args[i].key);
            wire_t* argwire = wfind(list, command.args[i].key);
            if(!argwire->completed){
                return false;
            }
            args[i] = argwire->count;
            
        }else{
            args[i] = command.args[i].num;
        }
    }

    switch(command.gate_type){
        case NONE:
            target->count = args[0];
            //printf("Target %s set to %u, arg was %u \n", target->key, target->count, args[0]);
            break;
        case NOT:
            target->count = ~args[0];
            break;
        case AND:
            target->count = args[0] & args[1];
            break;
        case OR:
            target->count = args[0] | args[1];
            break;
        case LSHIFT:
            target->count = args[0] << args[1];
            break;
        case RSHIFT:
            target->count = args[0] >> args[1];
            break;
    }
    target->completed = true;
    return true;
    
}

int main(){

    wire_t *pWirelist = malloc(sizeof(wire_t) * MAX_WIRES);
    wirelist_t wirelist;
    wirelist.wire_counter = 0;
    wirelist.max_wires = MAX_WIRES;
    wirelist.wires = pWirelist;

    command_t *commandlist = malloc(sizeof(command_t) * MAX_COMMANDS);
    uint16_t commmand_counter = 0;

    fptr = fopen("input7-1.txt", "r");
    char buffer[30] = {0};

    while(fgets(buffer, 30, fptr) != NULL){
        // strip end newlines
        strstrip(buffer);
        //printf("New Line \n");
        // Prepare for getting arguments
        arg_t args[2] = {0};
        uint8_t arg_counter = 0;

        bool target = false;
        gate_t gate_type = NONE;

        char* token = strtok(buffer, " ");

        while(token != NULL){
            //printf("New Token \n", token);
            if(isNumeric(token)){
                arg_t new_arg;
                new_arg.num = atoi(token);
                new_arg.is_wire = false;
                args[arg_counter] = new_arg;
                arg_counter++;
            }else{
                if(strcmp(token, "->") == 0){
                    target = true;
                }else if(strcmp(token, "OR") == 0){
                    gate_type = OR;
                }else if(strcmp(token, "AND") == 0){
                    gate_type = AND;
                }else if(strcmp(token, "RSHIFT") == 0){
                    gate_type = RSHIFT;
                }else if(strcmp(token, "NOT") == 0){
                    gate_type = NOT;
                }else if(strcmp(token, "LSHIFT") == 0){
                    gate_type = LSHIFT;
                }else{
                    if(target){
                        //printf("New Target\n");
                        command_t new_command;
                        new_command.args[0] = args[0];
                        new_command.args[1] = args[1];
                        new_command.arg_counter = arg_counter;
                        new_command.gate_type = gate_type;
                        strcpy(new_command.target, token);
                        commandlist[commmand_counter] = new_command;
                        ////printf("Current_command: %u", commmand_counter);
                        commmand_counter++;
                        //printf("Command Counter: %u\n", commmand_counter);
                    }else{
                        arg_t new_arg;
                        new_arg.is_wire = true;
                        new_arg.num = 0;
                        strcpy(new_arg.key, token);
                        args[arg_counter] = new_arg;
                        arg_counter++;
                    }
                }
            }

            token = strtok(NULL, " ");
        }
    }
    
    while(1){
        bool completed = true;
        for(int i=0; i<commmand_counter; i++){
            ////printf("Gate_type: %u, target: %s\n", commandlist[i].gate_type, commandlist[i].target);
            //printf("completed: %u", completed);
            completed = runCommand(&wirelist, commandlist[i]) && completed;
        }
        if(completed){
            break;
        }
    }

    wire_t* check_key = wfind(&wirelist, "a");
    printf("%s: %u",check_key->key, check_key->count);
    return 0;
}



bool isNumeric(char *a){
    return strspn(a, "0123456789") == strlen(a);
}
void strstrip(char* str){
    str[strcspn(str, "\n")] = 0;
}