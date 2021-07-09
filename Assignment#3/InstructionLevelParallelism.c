// Allen Zohrabians
// Comp 222
// Assignment #3 - Instruction-Level Parallelism

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Inst {
    char str[80];
    int dest;
    int src1;
    int src2;
    int delay;
};

struct Inst * inst;
int instSize = 0;

void freeMemory() {
    if (instSize > 0) {
        free(inst);
        instSize = 0;
    }
}

int isValid(char * str) {
    if (strlen(str) == 12) {
        if (str[5] >= '0' && str[5] <= '9') {
            if (str[8] >= '0' && str[8] <= '9') {
                if (str[11] >= '0' && str[11] <= '9') {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

int computeDelay(int index) {
    int result = 0;
    if (index > 0) {
        result = 1;
        if (inst[index].src1 == inst[index - 1].dest || inst[index].src2 == inst[index - 1].dest) {
            result = 3;
        } else if (index > 1 && inst[index - 1].delay == 1) {
            if (inst[index].src1 == inst[index - 2].dest || inst[index].src2 == inst[index - 2].dest) {
                result = 2;
            }
        }
    }
    return result;
}

void enterInsts() {
    freeMemory();
    printf("\nEnter total number of instructions: ");
    scanf("%i", &instSize);
    printf("\n");
    if (instSize >= 1 && instSize <= 100) {
        inst = (struct Inst *)malloc(instSize * sizeof(struct Inst));
        int i;
        for (i = 0; i < instSize; i++) {
            //printf("%i) ", i);
            scanf("%s", inst[i].str);
            if (isValid(inst[i].str) == 1) {
                inst[i].dest = inst[i].str[5] - '0';
                inst[i].src1 = inst[i].str[8] - '0';
                inst[i].src2 = inst[i].str[11] - '0';
                inst[i].delay = computeDelay(i);
            } else {
                freeMemory();
                printf("Invalid instruction\n");
                break;
            }
        }
    } else {
        instSize = 0;
        printf("Invalid size of instructions.\n");
    }
    printf("\n");
}

void showPipeline(int showExtra) {
    if (instSize > 0) {
        int totalCycles = 5;
        int i;
        for (i = 0; i < instSize; i++) {
            totalCycles += inst[i].delay;
        }
        printf("\nTotal cycles: %i\n\n", totalCycles);
        int currentDelay = 0;
        for (i = 0; i < instSize; i++) {
            int j;
            if (showExtra == 1 && inst[i].delay > 1) {
                for (j = 1; j < inst[i].delay; j++) {
                    printf("NOP         :\t");
                    int k;
                    for (k = 0; k < currentDelay + j; k++) {
                        printf("\t");
                    }
                    printf("IF\tID\tEX\tME\tWB\n");
                }
            }
            printf("%s:\t", inst[i].str);
            currentDelay += inst[i].delay;
            for (j = 0; j < currentDelay; j++) {
                printf("\t");
            }
            printf("IF\tID\tEX\tME\tWB\n");
        }
    } else {
        printf("Enter instructions first.\n");
    }
    printf("\n");
}

int main() {
    int option = 0;
    while (option != 4) {
        option = 4;
        printf("Instruction-level parallelism\n");
        printf("-----------------------------\n");
        printf("1) Enter instructions\n");
        printf("2) Calculate and show total cycle count on a 5-stage dynamic pipeline processor\n");
        printf("3) Calculate and show total cycle count on a 5-stage static pipeline processor (w/ NOPs)\n");
        printf("4) Quit program\n");
        printf("\nEnter selection: ");
        scanf("%i", &option);
        printf("\n");
        switch (option) {
            case 1:
                enterInsts();
                break;
            case 2:
                showPipeline(0);
                break;
            case 3:
                showPipeline(1);
                break;
            case 4:
                freeMemory();
                break;
            default:
                printf("Invalid selection, try again.\n\n");
        }
    }
    return 0;
}
