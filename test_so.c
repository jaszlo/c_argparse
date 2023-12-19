
#include <stdio.h>

#include "src/argparse.h"

int main(int argc, char *argv[]) {
    parse_create(argc, argv);
    Arg *args;
    unsigned int arg_count;
    parse_lookup_args(&args, &arg_count);
    for (unsigned int i = 0; i < arg_count; i++) {
        printf("Arg %d: %s\n", i, args[i].key);
        for (unsigned int j = 0; j < args[i].value_count; j++) {
            printf("\tValue %d: %s\n", j, args[i].values[j]);
        }
        printf("\n");
    }
}