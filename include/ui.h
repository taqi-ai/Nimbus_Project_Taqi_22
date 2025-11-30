// include/ui.h
#ifndef UI_H
#define UI_H
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
static inline void ui_init(void){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0; GetConsoleMode(h, &mode);
    mode |= 0x0004; /* ENABLE_VIRTUAL_TERMINAL_PROCESSING */
    SetConsoleMode(h, mode);
}
#else
static inline void ui_init(void){}
#endif

#define C_RESET  "\x1b[0m"
#define C_DIM    "\x1b[2m"
#define C_BOLD   "\x1b[1m"
#define C_CYAN   "\x1b[36m"
#define C_GREEN  "\x1b[32m"
#define C_YELLOW "\x1b[33m"
#define C_RED    "\x1b[31m"
#define C_GRAY   "\x1b[90m"

static inline void ui_title(const char *t){
    printf("\n" C_CYAN C_BOLD "┌─ %s ───────────────────────────────┐" C_RESET "\n", t);
}
static inline void ui_endbox(void){
    puts(C_CYAN "└────────────────────────────────────┘" C_RESET);
}
static inline void ui_badge_ok(void){   printf(C_GREEN  "[OK]"   C_RESET); }
static inline void ui_badge_warn(void){ printf(C_YELLOW "[WARN]" C_RESET); }
static inline void ui_badge_err(void){  printf(C_RED    "[ERR]"  C_RESET); }
#endif
