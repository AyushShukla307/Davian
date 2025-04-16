#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void commandList(char[], char[]);

#define MAX_SIZE_OF_OUTPUT 200
#define MAX_SIZE_OF_EXPRESSION 100
#define MAX_SIZE_OF_COMMAND 20
#define MAX_SIZE_OF_VARIABLE 30
#define MAX_SIZE_OF_STRING 50
#define MAX_SIZE_OF_ITERATIONS 100

struct node {
    char output[MAX_SIZE_OF_OUTPUT];
    // char* output;
    struct node *next;
};

struct integerNode {
    char variableName[MAX_SIZE_OF_VARIABLE];
    int data;
    struct integerNode *next;
};

struct decimalNode {
    char variableName[MAX_SIZE_OF_VARIABLE];
    float data;
    struct decimalNode *next;
};

struct stringNode {
    char variableName[MAX_SIZE_OF_VARIABLE];
    char data[MAX_SIZE_OF_STRING];
    struct stringNode *next;
};

int LoopIteration = 0;
struct loopNode {
    char command[MAX_SIZE_OF_COMMAND];
    char expression[MAX_SIZE_OF_EXPRESSION];
    struct loopNode *next;
};

typedef struct node Node;
typedef struct integerNode IntegerNode;
typedef struct decimalNode DecimalNode;
typedef struct stringNode StringNode;
typedef struct loopNode LoopNode;


Node *outputHead = NULL;
IntegerNode *integerVariablesHead = NULL;
DecimalNode *decimalVariablesHead = NULL;
StringNode *stringVariablesHead = NULL;
LoopNode *loopNodeHead = NULL;

void output() {
    Node *temp = outputHead;
    while(temp!=NULL) {
        printf("%s\n",temp->output);
        temp = temp->next;
    }
    outputHead = NULL;
}

void endprogram() {
    output();
    printf("\n----Program Ended with Code 0----\n");
    outputHead = NULL;
    integerVariablesHead = NULL;
    decimalVariablesHead = NULL;
    stringVariablesHead = NULL;
}

float findDecimalValue(char variableName[MAX_SIZE_OF_VARIABLE]) {
    // displayDecimalDEBUG();
    DecimalNode *temp = decimalVariablesHead;
    if(decimalVariablesHead == NULL) {
        return -9999.9999;
    }
    
    while(temp->next != NULL) {
        if(strcmp(temp->variableName,variableName) == 0) {
            // printf("%f",temp->data);
            return temp->data;
        }
        temp = temp->next;
    }
    //IF ONLY ONE VARIABLE
    if(strcmp(temp->variableName,variableName) == 0) {
        return temp->data;
    }
    return -9999.9999;
}

void addDecimalVariableToList(char variableName[MAX_SIZE_OF_VARIABLE], float value) {
    DecimalNode *newnode = (DecimalNode*)malloc(sizeof(DecimalNode));
    strcpy(newnode->variableName, variableName);
    newnode->data = value;
    newnode->next = NULL;

    if(decimalVariablesHead == NULL) {
        decimalVariablesHead = newnode;
        return;
    }

    DecimalNode *temp = decimalVariablesHead;
    while(temp->next != NULL) {
        if(strcmp(temp->variableName,variableName) == 0) {
            temp->data = value;
            return;
        }
        temp = temp->next;
    }
    if(strcmp(temp->variableName,variableName) == 0) {
        temp->data = value;
        return;
    }
    temp->next = newnode;
    return;
}

void decimalVariableAddition(char expression[MAX_SIZE_OF_EXPRESSION]) {
    char variableName[MAX_SIZE_OF_VARIABLE] = "";
    char value[MAX_SIZE_OF_VARIABLE] = "";
    int switchVariableValue = 0; // 0- Variable, 1-Value
    for(int i=0; i<strlen(expression); i++) {
        if(expression[i] == 32) {
            continue;
        }
        if(expression[i] == '=') {
            switchVariableValue = 1;
            continue;
        }
        if(switchVariableValue == 0) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(variableName, letter);
            continue;
        }
        if(switchVariableValue == 1) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(value, letter);
            continue;
        }
    }

    float floatvalue = -9999.9999;
    if(value[0] >= 65 && value[0] <=90 || value[0] >= 97 && value[0] <= 122) {
        floatvalue = findDecimalValue(value);
    } else {
        floatvalue = atof(value);
    }

    addDecimalVariableToList(variableName, floatvalue);
}

int findIntegerValue(char variableName[MAX_SIZE_OF_VARIABLE]) {
    // displayIntegerDEBUG();
    IntegerNode *temp = integerVariablesHead;
    // printf("VARIABLE: |%s|",variableName);
    if(integerVariablesHead == NULL) {
        return -9999;
    }
    
    while(temp->next != NULL) {
        if(strcmp(temp->variableName,variableName) == 0) {
            // printf("%d",temp->data);
            return temp->data;
        }
        temp = temp->next;
    }
    //IF ONLY ONE VARIABLE
    if(strcmp(temp->variableName,variableName) == 0) {
        // printf("%d",temp->data);
        return temp->data;
    }
    return -9999;
}

void addIntegerVariableToList(char variableName[MAX_SIZE_OF_VARIABLE], int value) {
    IntegerNode *newnode = (IntegerNode*)malloc(sizeof(IntegerNode));
    strcpy(newnode->variableName, variableName);
    newnode->data = value;
    newnode->next = NULL;

    if(integerVariablesHead == NULL) {
        integerVariablesHead = newnode;
        return;
    }

    IntegerNode *temp = integerVariablesHead;
    while(temp->next != NULL) {
        if(strcmp(temp->variableName,variableName) == 0) {
            temp->data = value;
            return;
        }
        temp = temp->next;
    }
    if(strcmp(temp->variableName,variableName) == 0) {
        temp->data = value;
        return;
    }
    temp->next = newnode;
    return;
}

void integerVariableAddition(char expression[MAX_SIZE_OF_EXPRESSION]) {
    char variableName[MAX_SIZE_OF_VARIABLE] = "";
    char value[MAX_SIZE_OF_VARIABLE] = "";
    int switchVariableValue = 0; // 0- Variable, 1-Value
    //JUST FOR ADDITION PROGRAMS LEN - 1
    for(int i=0; i<strlen(expression); i++) {
        if(expression[i] == 32) {
            continue;
        }
        if(expression[i] == '=') {
            switchVariableValue = 1;
            continue;
        }
        if(switchVariableValue == 0) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(variableName, letter);
            continue;
        }
        if(switchVariableValue == 1) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(value, letter);
            continue;
        }
    }
    int integervalue = -9999;
    if(value[0] >= 'A' && value[0] <='Z' || value[0] >= 'a' && value[0] <= 'z') {
        // printf("VALUE FUNCTION\n");
        // printf("|%s|",value);
        integervalue = findIntegerValue(value);
        // printf("VALUE:%d\n",integervalue);
    } else {
        integervalue = atoi(value);
    }
    
    addIntegerVariableToList(variableName, integervalue);
}

const char* findStringValue(char variableName[MAX_SIZE_OF_VARIABLE]) {
    // displayIntegerDEBUG();
    // printf("VARIABLE: |%s|",variableName);
    if(stringVariablesHead == NULL) {
        return "";
    }
    
    StringNode *temp = stringVariablesHead;
    while(temp->next != NULL) {
        if(strcmp(temp->variableName,variableName) == 0) {
            // printf("%d",temp->data);
            return temp->data;
        }
        temp = temp->next;
    }
    //IF ONLY ONE VARIABLE
    if(strcmp(temp->variableName,variableName) == 0) {
        // printf("%d",temp->data);
        return temp->data;
    }
    return "";
}

void addStringVariableToList(char variableName[MAX_SIZE_OF_VARIABLE], char value[MAX_SIZE_OF_STRING]) {
    StringNode *newnode = (StringNode*)malloc(sizeof(StringNode));
    strcpy(newnode->variableName, variableName);
    strcpy(newnode->data,value);
    newnode->next = NULL;

    if(stringVariablesHead == NULL) {
        stringVariablesHead = newnode;
        return;
    }

    StringNode *temp = stringVariablesHead;
    while(temp->next != NULL) {
        if(strcmp(temp->variableName,variableName) == 0) {
            strcpy(temp->data , value);
            return;
        }
        temp = temp->next;
    }
    if(strcmp(temp->variableName,variableName) == 0) {
        strcpy(temp->data , value);
        return;
    }
    temp->next = newnode;
    return;
}


void stringVariableAddition(char expression[MAX_SIZE_OF_EXPRESSION]) {
    char variableName[MAX_SIZE_OF_VARIABLE] = "";
    char value[MAX_SIZE_OF_VARIABLE] = "";
    int switchVariableValue = 0; // 0- Variable, 1-Value
    int spaceIgnore = 0; // 0 - true, 1 - false
    //JUST FOR ADDITION PROGRAMS LEN - 1
    for(int i=0; i<strlen(expression)-1; i++) {
        if(expression[i] == '"') {
            spaceIgnore = 1;
            continue;
        }
        if(expression[i] == 32 && spaceIgnore == 0 || expression[i] == '"') {
            continue;
        }
        if(expression[i] == '=') {
            switchVariableValue = 1;
            continue;
        }
        if(switchVariableValue == 0) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(variableName, letter);
            continue;
        }
        if(switchVariableValue == 1) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(value, letter);
            continue;
        }
    }
    
    addStringVariableToList(variableName, value);
}

void displayStringDEBUG() {
    StringNode *temp = stringVariablesHead;
    while(temp!=NULL) {
        printf("VARIABLE NAME: %s, VARIABLE DATA: %s\n", temp->variableName, temp->data);
        temp = temp->next;
    }
}

void displayIntegerDEBUG() {
    IntegerNode *temp = integerVariablesHead;
    while(temp!=NULL) {
        printf("VARIABLE NAME: %s, VARIABLE DATA: %d\n", temp->variableName, temp->data);
        temp = temp->next;
    }
}

void displayDecimalDEBUG() {
    DecimalNode *temp = decimalVariablesHead;
    while(temp!=NULL) {
        printf("VARIABLE NAME: %s, VARIABLE DATA: %f\n", temp->variableName, temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void displayOutputDEBUG() {
    Node *temp = outputHead;
    while(temp!=NULL) {
        printf("OUTPUT: %s\n", temp->output);
        temp = temp->next;
    }
    printf("\n");    
}

void loopDEBUG() {
    LoopNode *temp = loopNodeHead;
    while(temp!=NULL) {
        // printf("COMMAND: %s, EXPRESSION: %s\n", temp->command, temp->expression);
        temp = temp->next;
    }
    printf("END\n");
}

int evaluatingIntegerExpression(char expression[MAX_SIZE_OF_EXPRESSION]) {
    int total = 0;
    char variable1[MAX_SIZE_OF_VARIABLE] = "";
    char variable2[MAX_SIZE_OF_VARIABLE] = "";
    int switchvalue = 0; // 0 - value1, 1-value2
    char operator;

    for(int i=0;i<strlen(expression); i++) {
        if(expression[i] == 32) {
            continue;
        }
        if (expression[i] == '+' || expression[i] == '-' || 
            expression[i] == '*' || expression[i] == '/' || 
            expression[i] == '%' || expression[i] == '^' || 
            expression[i] == '&' || expression[i] == '|') {
            switchvalue = 1;
            operator = expression[i];
            continue;
        }
        if(switchvalue == 0) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(variable1, letter);
            continue;
        }
        if(switchvalue == 1) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(variable2, letter);
            continue;
        }
    }
    // printf("%s,%s", variable1, variable2);
    int value1 = 0;
    int value2 = 0;
    if(variable1[0] >= 65 && variable1[0] <=90 || variable1[0] >= 97 && variable1[0] <= 122) {
        value1 = findIntegerValue(variable1);
    } else {
        value1 = atoi(variable1);
    }

    if(variable2[0] >= 65 && variable2[0] <=90 || variable2[0] >= 97 && variable2[0] <= 122) {
        value2 = findIntegerValue(variable2);
    } else {
        value2 = atoi(variable2);
    }

    switch(operator) {
        case '+':
            total = (value1) + (value2);
            break;
        case '-':
            total = (value1) - (value2);
            break;
        case '*':
            total = (value1) * (value2);
            break;
        case '/':
            total = (int)(value1 / value2);
            break;
        case '%':
            total = (value1) % (value2);
            break;
        case '^':
            total = (int)pow((value1),(value2));
            break;
        case '&':
            total = (value1) & (value2);
            break;
        case '|':
            total = (value1) | (value2);
            break;
        default:
            total = -9999;
            break;
    }

    return total;
}

float evaluatingDecimalExpression(char expression[MAX_SIZE_OF_EXPRESSION]) {
    float total = 0.0;
    char variable1[MAX_SIZE_OF_VARIABLE] = "";
    char variable2[MAX_SIZE_OF_VARIABLE] = "";
    int switchvalue = 0; // 0 - value1, 1-value2
    char operator;

    for(int i=0;i<strlen(expression); i++) {
        if(expression[i] == 32) {
            continue;
        }
        if (expression[i] == '+' || expression[i] == '-' || 
            expression[i] == '*' || expression[i] == '/' || 
            expression[i] == '^' ) 
        {
            switchvalue = 1;
            operator = expression[i];
            continue;
        }
        if(switchvalue == 0) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(variable1, letter);
            continue;
        }
        if(switchvalue == 1) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(variable2, letter);
            continue;
        }
    }
    // printf("%s,%s", variable1, variable2);
    float value1 = 0.0;
    float value2 = 0.0;
    if(variable1[0] >= 65 && variable1[0] <=90 || variable1[0] >= 97 && variable1[0] <= 122) {
        value1 = findDecimalValue(variable1);
    } else {
        value1 = atof(variable1);
    }

    if(variable2[0] >= 65 && variable2[0] <=90 || variable2[0] >= 97 && variable2[0] <= 122) {
        value2 = findDecimalValue(variable2);
    } else {
        value2 = atof(variable2);
    }

    switch(operator) {
        case '+':
            total = (value1) + (value2);
            break;
        case '-':
            total = (value1) - (value2);
            break;
        case '*':
            total = (value1) * (value2);
            break;
        case '/':
            total = (value1) / (value2);
            break;
        case '^':
            total = (int)pow((value1),(value2));
            break;
        default:
            total = -9999.9999;
            break;
    }

    return total;
}

void evalint(char expression[MAX_SIZE_OF_EXPRESSION]) {
    char storeVariable[MAX_SIZE_OF_VARIABLE] = "";
    char evaluatingExpression[MAX_SIZE_OF_EXPRESSION] = "";
    int switchVariableorExpression = 0; //0-variable, 1-expression

    for(int i=0; i<strlen(expression); i++) {
        if(expression[i] == 32) {
            continue;
        }
        if(expression[i] == '=') {
            switchVariableorExpression = 1;
            continue;
        }
        if(switchVariableorExpression == 0) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(storeVariable, letter);
        }
        if(switchVariableorExpression == 1) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(evaluatingExpression, letter);
        }
    }

    int value = evaluatingIntegerExpression(evaluatingExpression);
    // printf("%s, %d",storeVariable,value);
    addIntegerVariableToList(storeVariable, value);
}

void evaldec(char expression[MAX_SIZE_OF_EXPRESSION]) {
    char storeVariable[MAX_SIZE_OF_VARIABLE] = "";
    char evaluatingExpression[MAX_SIZE_OF_EXPRESSION] = "";
    int switchVariableorExpression = 0; //0-variable, 1-expression

    for(int i=0; i<strlen(expression); i++) {
        if(expression[i] == 32) {
            continue;
        }
        if(expression[i] == '=') {
            switchVariableorExpression = 1;
            continue;
        }
        if(switchVariableorExpression == 0) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(storeVariable, letter);
        }
        if(switchVariableorExpression == 1) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(evaluatingExpression, letter);
        }
    }

    float value = evaluatingDecimalExpression(evaluatingExpression);
    // printf("%s, %d",storeVariable,value);
    addDecimalVariableToList(storeVariable, value);
}

void printExpressionProcessor(char expression[MAX_SIZE_OF_EXPRESSION]) {
    // printf("PROCESSOR CALLED - |%s|\n",expression);
    char processedExpression[MAX_SIZE_OF_EXPRESSION] = "";
    char variableName[MAX_SIZE_OF_VARIABLE] = "";
    int varcount = 0;
    int variableOrexpression = 0; // 0 - expression, 1 - variable
    for(int i=0; i<strlen(expression); i++) {
        if (expression[i] == '{') {
            variableOrexpression = 1;
            continue;
        } 
        if (expression[i] == '}') {
            variableOrexpression = 0;
            char stringValue[MAX_SIZE_OF_VARIABLE] = "";
            // printf("%s",variableName);
            int IntegerValue = findIntegerValue(variableName);
            // printf("PROCESSED INTEGER VALUE: %d\n", IntegerValue);
            if(IntegerValue != -9999) {
                itoa(IntegerValue,stringValue, 10);
            }
            else {
                float DecimalValue = findDecimalValue(variableName);
                if(DecimalValue != -10000) {
                    gcvt(DecimalValue, 6, stringValue);
                } else {
                    itoa(-9999,stringValue, 10);
                }
            }
            const char* StringValue = findStringValue(variableName);
            if (strcmp(StringValue,"") != 0) {
                strcpy(stringValue,StringValue);
            }

            strcat(processedExpression, stringValue);
            strcpy(variableName, "");
            continue;
        }
        if (variableOrexpression == 0) {
            char letter[2];
            letter[0] = expression[i];
            letter[1] = '\0';
            strcat(processedExpression, letter);
            continue;
        }
        if (variableOrexpression == 1) {
            char letterX[2];
            letterX[0] = expression[i];
            letterX[1] = '\0';
            strcat(variableName, letterX);
            continue;
        }
    }
    // const char* exp = processedExpression;
    // printf("PROCESSED EXPRESSION: |%s|\n",processedExpression);
    strcpy(expression, processedExpression);
}

void inputIntegerfunction(char expression[MAX_SIZE_OF_EXPRESSION]) {
    // expression[strlen(expression)] = '\0';
    Node *outputs = outputHead;
    while(outputHead != NULL) {
        printf("%s\n", outputHead->output);
        outputHead = outputHead->next;
    }
    int value = -9999;
    scanf("%d",&value);
    addIntegerVariableToList(expression,value);
}

void inputDecimalfunction(char expression[MAX_SIZE_OF_EXPRESSION]) {
    // expression[strlen(expression)-1] = '\0';
    Node *outputs = outputHead;
    while(outputHead != NULL) {
        printf("%s", outputHead->output);
        outputHead = outputHead->next;
    }
    float value = -9999.9999;
    scanf("%f",&value);
    addDecimalVariableToList(expression,value);
}

void inputStringfunction(char expression[MAX_SIZE_OF_EXPRESSION]) {
    // expression[strlen(expression)-1] = '\0';
    Node *outputs = outputHead;
    while(outputHead != NULL) {
        printf("%s", outputHead->output);
        outputHead = outputHead->next;
    }
    char value[MAX_SIZE_OF_STRING] = "";
    fgets(value,MAX_SIZE_OF_STRING,stdin);
    value[strlen(value)-1] = '\0';
    addStringVariableToList(expression,value);
}

void printfunction(char expression[MAX_SIZE_OF_EXPRESSION]) {
    // displayIntegerDEBUG();
    // printf("PRINT FUNCTION CALLED\n");
    char originalExpression[MAX_SIZE_OF_EXPRESSION] = "";
    strcpy(originalExpression,expression);
    printExpressionProcessor(expression);
    // printf("PRINT FUNCTION: |%s|\n",expression);
    
    // char variable[MAX_SIZE_OF_EXPRESSION];
    // strcpy(variable, expressionP);
    // printf("DEBUG: |%s|\n", variable);
    //--------------TEST-----------
    // printf("DEBUG: ");
    // // int i = 0;
    // for(int i=0; i<strlen(expressionP); i++)
    // {
    //     printf("%c", expressionP[i]);
    // }
    // printf("\n");
    // char ss[MAX_SIZE_OF_EXPRESSION] = "";
    // // strcpy(ss,expressionP);
    // snprintf(ss,MAX_SIZE_OF_EXPRESSION, "%s", expressionP);
    // printf("DEBUG: |%s|\n",ss);
    // // printf("LENGTH OF EXPRESSION: %d\n",strlen(expressionP));
    // strncpy(ss,expressionP,MAX_SIZE_OF_EXPRESSION-1);
    // ss[MAX_SIZE_OF_EXPRESSION-1] = '\0';
    // for(int i=0; i<strlen(expressionP); i++) {
    // }
    //--------------TEST-----------
    Node *newnode = (Node*)malloc(sizeof(Node));
    strcpy(newnode->output,expression); //CHANGE THIS
    newnode->next = NULL;

    if(outputHead == NULL) {
        outputHead = newnode;
        strcpy(expression,originalExpression);
        return;
    }

    Node *temp = outputHead;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newnode;
    strcpy(expression,originalExpression);
    return;
    // printf("%s\n",expression);
}

void addCommandInLoop(char command[MAX_SIZE_OF_COMMAND], char expression[MAX_SIZE_OF_EXPRESSION]) {
    // printf("ADDING\n");
    // expression[strlen(expression)-1] = '\0';
    // printf("%s, %s",command,expression);
    LoopNode *newcommand = (LoopNode*)malloc(sizeof(LoopNode));
    strcpy(newcommand->command,command);
    strcpy(newcommand->expression,expression);
    newcommand->next = NULL;

    if (loopNodeHead == NULL) {
        loopNodeHead = newcommand;
        return;
    }

    LoopNode *temp = loopNodeHead;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newcommand;
    // printf("ADDED SUCC\n");
}

void loopend() {
    // printf("JJJ");
    

    for(int i=0; i<LoopIteration; i++) {
        LoopNode *loop = loopNodeHead;
        while(loop!=NULL) {
            // printf("COM: %s,EXP: |%s|\n",loop->command, loop->expression);
            commandList(loop->command,loop->expression);
            loop = loop->next;
        }
    }

    // Node *outputs2 = outputHead;
    // while(outputs2 != NULL) {
    //     printf("%s", outputs2->output);
    //     outputs2 = outputs2->next;
    // }
    // outputHead = NULL;

    loopNodeHead = NULL;
}

void loopinitialization(char expression[MAX_SIZE_OF_EXPRESSION]) {
    // expression[strlen(expression)-1] = '\0';
    // Node *outputs = outputHead;
    // while(outputs != NULL) {
    //     printf("%s\n", outputs->output);
    //     outputs = outputs->next;
    // }
    // outputHead = NULL;
    char iterations[MAX_SIZE_OF_COMMAND] = "";
    for(int i=0; i<strlen(expression); i++) {
        if(expression[i] == 32) {
            continue;
        }
        char letter[2];
        letter[0] = expression[i];
        letter[1] = '\0';
        strcat(iterations,letter);
    }    
    int integervalue = 0; // 0-0 times running loop
    if(iterations[0] >= 'A' && iterations[0] <='Z' || iterations[0] >= 'a' && iterations[0] <= 'z') {
        // printf("VALUE FUNCTION\n");
        // printf("|%s|",value);
        integervalue = findIntegerValue(iterations);
        // printf("VALUE:%d\n",integervalue);
    } else {
        integervalue = atoi(iterations);
    }
    LoopIteration = integervalue;
    // printf("Program init to run %d times",LoopIteration);
}


int main(int argc, char **argv) {
    char command[MAX_SIZE_OF_COMMAND] = "";
    // int comcount = 0;
    char expression[MAX_SIZE_OF_EXPRESSION] = "";
    // int expcount = 0;
    int swithcommandexpression = 0; //0 - command , 1 - expression
    int metFirstSpace = 0; // 0- false, 1 -true
    int inloop = 0; // 0-not in loop, 1- in loop

    // system("cls");

    FILE* file = fopen(argv[1], "r");
    char line[256];
    if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
            // char _line[MAX_SIZE_OF_EXPRESSION];
            // strcpy(_line, line);
            //FOR EMPTY LINE
            if (line[1] == '\0') {
                continue;
            }

            line[strlen(line)-1] = '\0';
            // printf("%s",line);
            if (line[0] == '@') {
                continue; //WILL BE COMMENTS
            }
            for(int i=0; i<strlen(line); i++) {
                if (line[i] == 32 && metFirstSpace == 0) {
                    swithcommandexpression = 1;
                    metFirstSpace = 1;
                    continue;
                }
                if(swithcommandexpression == 0) {
                    char letter[2];
                    letter[0] = line[i];
                    letter[1] = '\0';
                    strcat(command, letter);
                    continue;
                }
                if(swithcommandexpression == 1) {
                    char letter[2];
                    letter[0] = line[i];
                    letter[1] = '\0';
                    strcat(expression, letter);
                    continue;
                }
            }
            // printf("COMMAND: %s,EXPRESSION: |%s|\n",command,expression);
            if (strcmp(command, "loop") == 0) {
                loopinitialization(expression);
                inloop += 1;
                strcpy(command, "");
                strcpy(expression, "");
                swithcommandexpression = 0;
                metFirstSpace = 0;
                continue;
            }
            if (strcmp(command, "endloop") == 0) {
                loopend();
                inloop -= 1;
                LoopIteration = 0;
                strcpy(command, "");
                strcpy(expression, "");
                swithcommandexpression = 0;
                metFirstSpace = 0;
                continue;
            }
            // printf("|%s|, |%s|\n",command,expression);

            if (inloop == 0) {
                // printf("OUT OF LOOP\n");
                commandList(command,expression);
            }
            else {
                // printf("IN LOOP\n");
                addCommandInLoop(command,expression);
            }

            strcpy(command, "");
            strcpy(expression, "");
            swithcommandexpression = 0;
            metFirstSpace = 0;
        }
        fclose(file);
    }
    else {
        fprintf(stderr, "Unable to open file!\n");
    }

    // system("pause");
    return 0;
}

void commandList(char command[MAX_SIZE_OF_COMMAND], char expression[MAX_SIZE_OF_EXPRESSION]) {

    //ENDPROG
    if (strcmp(command,"endprog") == 0) {
        endprogram();
    }
    //DISPLAY
    else if (strcmp(command,"display") == 0) {
        printfunction(expression);
    }
    //INPUT INTEGER
    else if (strcmp(command,"inputint") == 0) {
        inputIntegerfunction(expression);
    }
    //INPUT DECIMAL
    else if (strcmp(command,"inputdec") == 0) {
        inputDecimalfunction(expression);
    }
    //INPUT STRING
    else if (strcmp(command,"inputstr") == 0) {
        inputStringfunction(expression);
    }
    //INTEGER VARIABLE DECLARATION
    else if (strcmp(command,"integer") == 0) {
        integerVariableAddition(expression);
    }
    //DECIMAL VARIABLE DECLARATION
    else if (strcmp(command,"decimal") == 0) {
        decimalVariableAddition(expression);
    }
    //STRING VARIABLE DECLARATION
    else if (strcmp(command,"string") == 0) {
        stringVariableAddition(expression);
    }
    //EVALINT 
    else if (strcmp(command,"evalint") == 0 || strcmp(command,"evaluateinteger") == 0 ||
        strcmp(command,"evalinteger") == 0 || strcmp(command,"evaluateint") == 0
    ) {
        evalint(expression);
    }
    //EVALDEC 
    else if (strcmp(command,"evaldec") == 0 || strcmp(command,"evaluatedecimal") == 0 ||
        strcmp(command,"evaldecimal") == 0 || strcmp(command,"evaluatedec") == 0 
    ) {
        evaldec(expression);
    }
    //ERROR
    else {
        printf("--ERROR--\n");
        printf("\n----Program Ended with Code 1----\n");
        outputHead = NULL;
        integerVariablesHead = NULL;
        decimalVariablesHead = NULL;
        stringVariablesHead = NULL;
        exit(0);
    }
}
