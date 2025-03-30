#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPS 1000

typedef struct {
    char op[4];  // "add", "sub", "mul", "div"
    int value;
} Operation;

int apply_operations(int current, Operation* ops, int op_count) {
    for (int i = 0; i < op_count; ++i) {
        if (strcmp(ops[i].op, "add") == 0) {
            current += ops[i].value;
        } else if (strcmp(ops[i].op, "sub") == 0) {
            current -= ops[i].value;
        } else if (strcmp(ops[i].op, "mul") == 0) {
            current *= ops[i].value;
        } else if (strcmp(ops[i].op, "div") == 0) {
            if (ops[i].value != 0) {
                current /= ops[i].value;
            }
        }
    }
    return current;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <initial_value>\n", argv[0]);
        return 1;
    }

    int current = atoi(argv[1]);
    Operation ops[MAX_OPS];
    int op_count = 0;

    char cmd[10];
    int val;

    while (scanf("%s", cmd) != EOF) {
        if (strcmp(cmd, "n") == 0) {
            current = apply_operations(current, ops, op_count);
            printf("%d\n", current);
        } else {
            if (scanf("%d", &val) != 1) break;
            if (op_count < MAX_OPS) {
                strcpy(ops[op_count].op, cmd);
                ops[op_count].value = val;
                op_count++;
            }
        }
    }

    return 0;
}
