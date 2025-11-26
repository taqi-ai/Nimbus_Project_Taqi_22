#include <stdio.h>
#include <string.h>
#include "dynarray.h"
#include "cli.h"

static EmployeeArray emps;   // employee list

static void menu(void) {
    puts("\n=== Employee KPI CLI ===");
    puts("1) Add employee");
    puts("2) List employees");
    puts("0) Exit");
}

static void add_employee(void) {
    Employee e;
    printf("Enter: id name department\n> ");
    if (scanf("%d %63s %31s", &e.id, e.name, e.department) != 3) {
        puts("Invalid input.");
        return;
    }
    // (duplicate check will be added later)
    emp_array_push(&emps, e);
    puts("Employee added.");
}

static void list_employees(void) {
    if (emps.size == 0) {
        puts("No employees.");
        return;
    }
    puts("ID    NAME                     DEPT");
    for (size_t i = 0; i < emps.size; ++i) {
        printf("%-5d %-24s %-12s\n",
               emps.data[i].id, emps.data[i].name, emps.data[i].department);
    }
}
int run_cli(void) {
    emp_array_init(&emps);

    int choice;
    do {
        menu();
        printf("> ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: add_employee(); break;
            case 2: list_employees(); break;
            case 0: puts("Exiting..."); break;
            default: puts("Invalid choice.");
        }
    } while (choice != 0);

    emp_array_free(&emps);
    return 0;
}

