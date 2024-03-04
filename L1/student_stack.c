#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

struct StudentRecord {
    char IDNO[20];
    char NAME[50];
    char DOB[20];
    double CGPA;
};

struct Stack {
    struct StudentRecord records[MAX_SIZE];
    int top;
};

void push(struct Stack *stack, struct StudentRecord record) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack is full.\n");
        return;
    }

    stack->records[++stack->top] = record;
}

struct StudentRecord pop(struct Stack *stack) {
    if (stack->top == -1) {
        printf("Stack is empty.\n");
        exit(1);
    }

    return stack->records[stack->top--];
}

void display(const struct Stack *stack) {
    if (stack->top == -1) {
        printf("Stack is empty.\n");
        return;
    }

    for (int i = stack->top; i >= 0; i--) {
        printf("%s %s %s %.2f\n", stack->records[i].IDNO, stack->records[i].NAME, stack->records[i].DOB, stack->records[i].CGPA);
    }
}

int main() {
    struct Stack stack = { .top = -1 };

    FILE *fp = fopen("studentin.dat", "r");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    struct StudentRecord record;
    while (fscanf(fp, "%s %s %s %lf", record.IDNO, record.NAME, record.DOB, &record.CGPA) == 4) {
        push(&stack, record);
    }
    fclose(fp);

    printf("Records popped and displayed:\n");
    fp = fopen("studentout.dat", "w");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    while (stack.top != -1) {
        struct StudentRecord poppedRecord = pop(&stack);
        printf("%s %s %s %.2f\n", poppedRecord.IDNO, poppedRecord.NAME, poppedRecord.DOB, poppedRecord.CGPA);
        fprintf(fp, "%s %s %s %.2f\n", poppedRecord.IDNO, poppedRecord.NAME, poppedRecord.DOB, poppedRecord.CGPA);
    }
    fclose(fp);

    return 0;
}
