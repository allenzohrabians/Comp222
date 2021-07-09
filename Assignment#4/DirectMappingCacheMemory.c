// Allen Zohrabians
// Comp 222
// Assignment #4 - Direct Mapping Cache Memory

#include <stdio.h>
#include <stdlib.h>

struct Line {
    int * block;
    int tag;
};

int * main_memory;
int main_memory_size = 0;
struct Line * cache;
int cache_size_int = 0;
int cache_size_line = 0;
int block_size = 0;


void reset_parameters() {
    if (main_memory_size > 0) {
        free(main_memory);
        int i;
        for (i = 0; i < cache_size_line; i++) {
            free(cache[i].block);
        }
        free(cache);
        main_memory_size = 0;
        cache_size_int = 0;
        cache_size_line = 0;
        block_size = 0;
    }
}

int is_power_of_two(int number) {
    if (number == 1) {
        return 1;
    } else if (number > 1 && number % 2 == 0) {
        return is_power_of_two(number / 2);
    } else {
        return 0;
    }
}

void enter_parameters() {
    reset_parameters();
    printf("\nEnter main memory size (words): ");
    scanf("%i", &main_memory_size);
    printf("\nEnter cache size (words): ");
    scanf("%i", &cache_size_int);
    printf("\nEnter block size (words/blocks): ");
    scanf("%i", &block_size);
    if (is_power_of_two(main_memory_size)) {
        if (is_power_of_two(cache_size_int) && main_memory_size >= cache_size_int) {
            if (is_power_of_two(block_size) && cache_size_int >= block_size) {
                main_memory = (int *)malloc(main_memory_size * sizeof(int));
                int i;
                for (i = 0; i < main_memory_size; i++) {
                    main_memory[i] = main_memory_size + i;
                }
                cache_size_line = cache_size_int / block_size;
                cache = (struct Line *)malloc(cache_size_line * sizeof(struct Line));
                for (i = 0; i < cache_size_line; i++) {
                    cache[i].block = (int *)malloc(block_size * sizeof(int));
                    int j;
                    for (j = 0; j < block_size; j++) {
                        cache[i].block[j] = -1;
                    }
                    cache[i].tag = -1;
                }
            } else {
                main_memory_size = 0;
                cache_size_int = 0;
                block_size = 0;
                printf("Invalid block size.\n");
            }
        } else {
            main_memory_size = 0;
            cache_size_int = 0;
            printf("Invalid cache size.\n");
        }
    } else {
        main_memory_size = 0;
        printf("Invalid main memory size.\n");
    }
}

void access_cache() {
    if (main_memory_size > 0) {
        int option = -1;
        int address = -1;
        int current_tag;
        int current_line;
        int current_word;
        int value_to_write = -1;
        printf("\nSelect read (0) or write (1): ");
        scanf("%i", &option);
        if (option == 0 || option == 1) {
            if (option == 0) {
                printf("\nEnter main memory address to read from: ");
            } else {
                printf("\nEnter main memory address to write to: ");
            }
            scanf("%i", &address);
            if (address > -1 && address < main_memory_size) {
                current_tag = address / cache_size_int;
                current_line = (address % cache_size_int) / block_size;
                current_word = address % block_size;
                if (option == 1) {
                    printf("\nEnter value to write: ");
                    scanf("%i", &value_to_write);
                }
                if (option == 0 || (option == 1 && value_to_write > -1)) {
                    printf("\nAccess result from address %i:\n", address);
                    if (option == 0) {
                        printf("\tRead ");
                    } else {
                        printf("\tWrite ");
                    }
                    if (cache[current_line].tag == current_tag) {
                        printf("Hit!\n");
                    } else {
                        printf("miss!\n");
                        int i;
                        for (i = 0; i < block_size; i++) {
                            int main_memory_index = (current_tag * cache_size_int) + (current_line * block_size) + i;
                            cache[current_line].block[i] = main_memory[main_memory_index];
                        }
                        cache[current_line].tag = current_tag;
                    }
                    if (option == 1) {
                        cache[current_line].block[current_word] = value_to_write;
                        main_memory[address] = value_to_write;
                    }
                    printf("\tTag: %i\n", current_tag);
                    printf("\tBlock: %i\n", current_line);
                    printf("\tWord: %i\n", current_word);
                    printf("\tData: %i\n", cache[current_line].block[current_word]);
                } else {
                    printf("Invalid value to write.\n");
                }
            } else {
                printf("Invalid main memory address.\n");
            }
        } else {
            printf("Invalid option.\n");
        }
    } else {
        printf("Input parameters first.\n");
    }
}

int main() {
    int option = 0;
    while (option != 3) {
        option = 3;
        printf("\nDirect-Mapped Cache Memory:\n");
        printf("---------------------------\n");
        printf("1) Enter parameters\n");
        printf("2) Access cache\n");
        printf("3) Quit program\n\n");
        printf("Enter option: ");
        scanf("%i", &option);
        switch (option) {
            case 1:
                enter_parameters();
                break;
            case 2:
                access_cache();
                break;
            case 3:
                reset_parameters();
                break;
            default:
                printf("Try again.\n");
        }
        printf("\n");
    }
    return 0;
}
