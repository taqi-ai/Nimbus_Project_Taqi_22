// src/cli.c
// Minimal, focused comments + small cleanups for readability
// - Keeps existing behavior
// - Adds a tiny input helper (clear_line)
// - Uses consistent messages and formatting

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cli.h"
#include "ui.h"          // colors / titles
#include "dynarray.h"
#include "models.h"
#include "io.h"
#include "kpi.h"
#include "sort_search.h"

// ---- In-memory state ----
static EmployeeArray emps;
static TaskLogArray  logs;
static KPI *kpis = NULL;
static size_t kpis_n = 0;

// ---- Small utility ----
static void clear_line(void) {
    int c; while ((c = getchar()) != '\n' && c != EOF) {}
}

// ---- Menu ----
static void print_menu(void) {
    ui_title("Employee KPI CLI");
    puts("  " C_BOLD "1" C_RESET ") Add employee");
    puts("  " C_BOLD "2" C_RESET ") List employees");
    puts("  " C_BOLD "3" C_RESET ") Load logs from CSV " C_GRAY "(data/sample_logs.csv)" C_RESET);
    puts("  " C_BOLD "4" C_RESET ") Compute KPI report");
    puts("  " C_BOLD "5" C_RESET ") Sort employees by name (A->Z)");
    puts("  " C_BOLD "6" C_RESET ") Rank employees by KPI score (high->low)");
    puts("  " C_BOLD "7" C_RESET ") Search employee by ID");
    puts("  " C_BOLD "8" C_RESET ") Filter employees by department");
    puts("  " C_BOLD "9" C_RESET ") Show KPI table");
    puts("  " C_BOLD "0" C_RESET ") Exit");
    ui_endbox();
}

// ---- Actions ----
static void add_employee(void) {
    Employee e;
    printf("Enter: id name department\n> ");
    if (scanf("%d %63s %31s", &e.id, e.name, e.department) != 3) {
        ui_badge_err(); puts(" Invalid input.");
        clear_line();
        return;
    }
    // Duplicate check
    for (size_t i = 0; i < emps.size; ++i) {
        if (emps.data[i].id == e.id) {
            ui_badge_warn(); puts(" Employee id already exists.");
            return;
        }
    }
    emp_array_push(&emps, e);
    ui_badge_ok(); puts(" Added.");
}

static void list_employees(void) {
    if (emps.size == 0) { puts(C_GRAY "(no employees)" C_RESET); return; }
    printf(C_BOLD "%-5s %-24s %-12s\n" C_RESET, "ID", "NAME", "DEPT");
    for (size_t i = 0; i < emps.size; ++i) {
        printf("%-5d %-24s %-12s\n",
               emps.data[i].id, emps.data[i].name, emps.data[i].department);
    }
}

static void load_logs_csv_action(void) {
    // Reset previous buffer (avoid leaks)
    log_array_free(&logs);
    log_array_init(&logs);

    if (load_csv("data/sample_logs.csv", &logs)) {
        ui_badge_ok(); printf(" Loaded %zu log rows from data/sample_logs.csv\n", logs.size);
    } else {
        ui_badge_err(); puts(" Failed to load CSV. Ensure data/sample_logs.csv exists.");
    }
}

static void free_kpis(void){
    free(kpis); kpis = NULL; kpis_n = 0;
}

static void compute_kpi_report(void) {
    if (emps.size == 0) { ui_badge_warn(); puts(" Add employees first."); return; }
    if (logs.size == 0) { ui_badge_warn(); puts(" Load logs first (option 3)."); return; }
    free_kpis();
    compute_kpis(&emps, &logs, &kpis, &kpis_n);
    if (kpis && kpis_n) { ui_badge_ok(); puts(" KPI computed."); }
    else { ui_badge_warn(); puts(" KPI not computed (no data?)."); }
}

static void show_kpis(void) {
    if (!kpis || !kpis_n) { puts(C_GRAY "Compute KPI first (option 4)." C_RESET); return; }
    printf(C_BOLD "%-6s %-5s %-6s %-6s %-6s %-8s %-6s %-6s %-6s %-6s %-5s\n" C_RESET,
           "emp", "tasks","errs","hrs","avgQ","errRate","TPH","PS","RI","ORS","FLAG");
    for (size_t i = 0; i < kpis_n; i++){
        const char *fclr = (strcmp(kpis[i].flag, "UNDER") == 0) ? C_RED :
                           (strcmp(kpis[i].flag, "WATCH") == 0) ? C_YELLOW : C_GREEN;
        printf("%-6d %-5d %-6d %-6.1f %-6.1f %-8.3f %-6.2f %-6.2f %-6.2f %-6.2f %s%s" C_RESET "\n",
               kpis[i].employee_id, kpis[i].tasks, kpis[i].errors,
               kpis[i].hours_total, kpis[i].avg_quality, kpis[i].error_rate_s,
               kpis[i].tph, kpis[i].ps, kpis[i].ri, kpis[i].ors, fclr, kpis[i].flag);
    }
}

static void sort_emps_by_name_action(void){
    if (emps.size == 0){ puts("No employees."); return; }
    sort_employees_by_name(&emps);
    ui_badge_ok(); puts(" Employees sorted by name.");
    list_employees();
}

static void rank_by_kpi_action(void){
    if (!kpis || !kpis_n){ puts("Compute KPI first (option 4)."); return; }
    sort_kpis_by_score(kpis, kpis_n);
    ui_badge_ok(); puts(" KPI ranked by score (high->low).");
    show_kpis();
}

static void search_by_id_action(void){
    if (emps.size == 0){ puts("No employees."); return; }
    int id; printf("Enter employee id: ");
    if (scanf("%d", &id) != 1){ ui_badge_err(); puts(" Invalid."); clear_line(); return; }
    int idx = find_employee_index_by_id(&emps, id);
    if (idx < 0){ ui_badge_warn(); puts(" Not found."); return; }
    printf(C_BOLD "Found: " C_RESET "%d %s %s\n",
           emps.data[idx].id, emps.data[idx].name, emps.data[idx].department);
    if (logs.size){
        const char* tr = trend_for_employee(&logs, id, 3);
        printf("Recent trend (last 3 quality): %s\n", tr);
    }
}

static void filter_by_dept_action(void){
    if (emps.size == 0){ puts("No employees."); return; }
    char dept[DEPT_MAX_LEN];
    printf("Enter department (no spaces): ");
    if (scanf("%31s", dept) != 1){ ui_badge_err(); puts(" Invalid."); clear_line(); return; }
    size_t cnt = 0;
    int* idx = filter_by_department(&emps, dept, &cnt);
    if (!idx || cnt == 0){ ui_badge_warn(); puts(" No matches."); free(idx); return; }
    printf(C_BOLD "Employees in %s:\n" C_RESET, dept);
    for (size_t i = 0; i < cnt; i++){
        Employee *e = &emps.data[idx[i]];
        printf("%d %s %s\n", e->id, e->name, e->department);
    }
    free(idx);
}

// ---- Main loop ----
int run_cli(void) {
    ui_init();                 // enable ANSI colors on Windows
    emp_array_init(&emps);
    log_array_init(&logs);

    int choice;
    do {
        print_menu();
        printf("> ");
        if (scanf("%d", &choice) != 1) { ui_badge_err(); puts(" Invalid input."); break; }

        switch (choice) {
            case 1: add_employee(); break;
            case 2: list_employees(); break;
            case 3: load_logs_csv_action(); break;
            case 4: compute_kpi_report(); break;
            case 5: sort_emps_by_name_action(); break;
            case 6: rank_by_kpi_action(); break;
            case 7: search_by_id_action(); break;
            case 8: filter_by_dept_action(); break;
            case 9: show_kpis(); break;
            case 0: puts("Bye!"); break;
            default: ui_badge_warn(); puts(" Invalid choice.");
        }
    } while (choice != 0);

    free_kpis();
    log_array_free(&logs);
    emp_array_free(&emps);
    return 0;
}
