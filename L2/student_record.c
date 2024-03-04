#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

struct StudentRecord {
    char IDNO[20];
    char NAME[50];
    char DOB[20];
    double CGPA;
};

struct Queue {
    struct StudentRecord records[MAX_SIZE];
    int front, rear;
};

void initializeQueue(struct Queue *q) {
    q->front = q->rear = -1;
}

int isQueueEmpty(const struct Queue *q) {
    return q->front == -1;
}

int isQueueFull(const struct Queue *q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

void enqueue(struct Queue *q, struct StudentRecord record) {
    if (isQueueFull(q)) {
        printf("Queue is full.\n");
        return;
    }

    if (isQueueEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_SIZE;
    }

    q->records[q->rear] = record;
}

struct StudentRecord dequeue(struct Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty.\n");
        exit(1);
    }

    struct StudentRecord dequeuedRecord = q->records[q->front];

    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_SIZE;
    }

    return dequeuedRecord;
}

void display(const struct Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    int i = q->front;
    do {
        printf("%s %s %s %.2f\n", q->records[i].IDNO, q->records[i].NAME, q->records[i].DOB, q->records[i].CGPA);
        i = (i + 1) % MAX_SIZE;
    } while (i != (q->rear + 1) % MAX_SIZE);
}

int main() {
    struct Queue q;
    initializeQueue(&q);

    FILE *fp = fopen("studentin.dat", "r");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    struct StudentRecord record;
    while (fscanf(fp, "%s %s %s %lf", record.IDNO, record.NAME, record.DOB, &record.CGPA) == 4) {
        enqueue(&q, record);
    }
    fclose(fp);

    printf("Records dequeued and displayed:\n");
    fp = fopen("studentout.dat", "w");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    while (!isQueueEmpty(&q)) {
        struct StudentRecord dequeuedRecord = dequeue(&q);
        printf("%s %s %s %.2f\n", dequeuedRecord.IDNO, dequeuedRecord.NAME, dequeuedRecord.DOB, dequeuedRecord.CGPA);
        fprintf(fp, "%s %s %s %.2f\n", dequeuedRecord.IDNO, dequeuedRecord.NAME, dequeuedRecord.DOB, dequeuedRecord.CGPA);
    }
    fclose(fp);

    printf("Student names whose CGPA is less than 9:\n");
    fp = fopen("studentout.dat", "r");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    while (fscanf(fp, "%s %s %s %lf", record.IDNO, record.NAME, record.DOB, &record.CGPA) == 4) {
        if (record.CGPA < 9) {
            printf("%s\n", record.NAME);
        }
    }
    fclose(fp);

    return 0;
}
