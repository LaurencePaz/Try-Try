#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 50
#define TASK_LEN 100

typedef struct {
    int id;
    char text[TASK_LEN];
    int completed;
} Task;

Task tasks[MAX_TASKS];
int task_count = 0;

void load_tasks() {
    FILE *file = fopen("tasks.txt", "r");
    if (!file) return;
    
    while (fscanf(file, "%d|%d|%[^\n]\n", &tasks[task_count].id, &tasks[task_count].completed, tasks[task_count].text) == 3) {
        task_count++;
    }
    fclose(file);
}

void save_tasks() {
    FILE *file = fopen("tasks.txt", "w");
    if (!file) return;
    
    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%d|%d|%s\n", tasks[i].id, tasks[i].completed, tasks[i].text);
    }
    fclose(file);
}

void show_tasks() {
    printf("\n--- YOUR TO-DO LIST ---\n");
    if (task_count == 0) {
        printf("No tasks found!\n");
        return;
    }
    for (int i = 0; i < task_count; i++) {
        printf("%d. [%s] %s\n", tasks[i].id, tasks[i].completed ? "X" : " ", tasks[i].text);
    }
}

void add_task() {
    if (task_count >= MAX_TASKS) {
        printf("Task list full!\n");
        return;
    }
    printf("Enter task description: ");
    getchar();
    fgets(tasks[task_count].text, TASK_LEN, stdin);
    tasks[task_count].text[strcspn(tasks[task_count].text, "\n")] = 0;
    
    tasks[task_count].id = task_count + 1;
    tasks[task_count].completed = 0;
    task_count++;
    
    save_tasks();
    printf("Task added successfully!\n");
}

void complete_task() {
    int id;
    show_tasks();
    if (task_count == 0) return;
    
    printf("\nEnter task ID to mark complete: ");
    scanf("%d", &id);
    
    if (id > 0 && id <= task_count) {
        tasks[id - 1].completed = 1;
        save_tasks();
        printf("Task marked as complete!\n");
    } else {
        printf("Invalid Task ID.\n");
    }
}

int main() {
    int choice;
    load_tasks();
    
    while (1) {
        printf("\n=== TO-DO MANAGER ===\n");
        printf("1. View Tasks\n");
        printf("2. Add Task\n");
        printf("3. Complete Task\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: show_tasks(); break;
            case 2: add_task(); break;
            case 3: complete_task(); break;
            case 4: printf("Goodbye!\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}