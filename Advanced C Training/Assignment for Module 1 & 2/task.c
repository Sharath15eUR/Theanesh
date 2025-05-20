#include <stdio.h>
#include <string.h>

#define DAYS 7
#define MAX_TASKS 3
#define TASK_LENGTH 100

struct Day {
    char dayName[10];
    char tasks[MAX_TASKS][TASK_LENGTH];
    int taskCount;
};

void initWeek(struct Day week[]) {
    char *names[DAYS] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int i = 0; i < DAYS; i++) {
        strcpy(week[i].dayName, names[i]);
        week[i].taskCount = 0;
    }
}

void addTask(struct Day week[]) {
    int dayIndex;
    printf("\nEnter day number to add task (1=Monday, ..., 7=Sunday): ");
    scanf("%d", &dayIndex);
    getchar(); 

    if (dayIndex < 1 || dayIndex > DAYS) {
        printf("Invalid day number.\n");
        return;
    }

    if (week[dayIndex - 1].taskCount >= MAX_TASKS) {
        printf("Task limit reached for %s.\n", week[dayIndex - 1].dayName);
        return;
    }

    printf("Enter task for %s: ", week[dayIndex - 1].dayName);
    fgets(week[dayIndex - 1].tasks[week[dayIndex - 1].taskCount], TASK_LENGTH, stdin);
    week[dayIndex - 1].tasks[week[dayIndex - 1].taskCount][strcspn(week[dayIndex - 1].tasks[week[dayIndex - 1].taskCount], "\n")] = 0;
    week[dayIndex - 1].taskCount++;
    printf("Task added!\n");
}

void displayCalendar(struct Day week[]) {
    printf("\nWeekly Calendar:\n");
    printf("----------------\n");
    for (int i = 0; i < DAYS; i++) {
        printf("%s:\n", week[i].dayName);
        if (week[i].taskCount == 0) {
            printf("  No tasks\n");
        } else {
            for (int j = 0; j < week[i].taskCount; j++) {
                printf("  %d. %s\n", j + 1, week[i].tasks[j]);
            }
        }
        printf("\n");
    }
}

int main() {
    struct Day week[DAYS];
    initWeek(week);

    int choice;
    do {
        printf("\n1. Add Task\n2. Display Calendar\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        if (choice == 1) {
            addTask(week);
        } else if (choice == 2) {
            displayCalendar(week);
        } else if (choice == 3) {
            printf("Exiting...\n");
        } else {
            printf("Invalid choice.\n");
        }
    } while (choice != 3);

    return 0;
}
