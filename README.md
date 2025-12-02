# Employee Performance & KPI Dashboard (CLI)

A simple Command Line Interface (CLI) based project to manage employees, load task logs, compute Key Performance Indicators (KPIs), sort/search employees, and generate performance insights.

This project applies **C programming**, **structures**, **dynamic memory**, **file handling**, **sorting**, **searching**, **statistics**, and **modular design**.

---

## 📌 Features Implemented

### 👤 Employee Management
- Add employee  
- List employees  
- Filter employees by department  
- Search employee by ID  

### 📄 Log File Management
- Load performance logs from CSV (`data/sample_logs.csv`)
- Stores task info: task_id, date, hours, quality score

### 📈 KPI Computation
- Tasks completed  
- Error count  
- Hours spent  
- Average quality  
- Error rate (smoothed)  
- Reliability Index (RI)  
- Productivity Score (PS)  
- Overall Rank Score (ORS)  
- Trend detection using linear regression  

### 🔍 Sorting & Searching
- Sort employees by name (A→Z)  
- Rank employees by KPI score (high → low)  
- Search employee by ID  
- Filter by department  

### 📊 Reports
- Show complete KPI report in table form  
- Rankers list  
- Trend: Improving / Worsening / Stable  

---

## 🧱 Project Architecture

Project/
│
├── include/
│ ├── cli.h
│ ├── dynarray.h
│ ├── io.h
│ ├── kpi.h
│ ├── models.h
│ ├── sort_search.h ← Poorvi
│ ├── stats.h ← Shiv
│
├── src/
│ ├── main.c
│ ├── cli.c ← Taqi
│ ├── dynarray.c ← Aditya
│ ├── io.c ← Aditya
│ ├── stats.c ← Shiv
│ ├── kpi.c ← Shiv
│ ├── sort_search.c ← Poorvi
│
├── data/
│ └── sample_logs.csv ← Aditya
│
├
└── README.md


---

## 👥 Team Members & Contributions

### **1. Mohd Taqi Abbas Haideri**
- CLI module (`cli.c`, `cli.h`)
- App workflow, menus, command handling
- Integration of all modules into working CLI
- Repo management, merging PRs

### **2. Aditya Singh**
- `models.h` — Employee & TaskLog structures  
- `dynarray.h / dynarray.c` — dynamic arrays  
- `io.h / io.c` — CSV loader, date parser  
- `sample_logs.csv`

### **3. Shivdarshan**
- `stats.h / stats.c` — mean, median, slope calculation  
- `kpi.h / kpi.c` — KPI formulas, trend detection  
- Reliability, Productivity, ORS scoring  
- Error smoothing model

### **4. Poorvi**
- `sort_search.h / sort_search.c`  
- Search by ID  
- Filter by department  
- Sort employees by name  
- Sort KPIs by ORS  

---

## 🚀 Build & Run Instructions
a ready made exe file is present
with the project which can be used to run the project

SAMPLE MENU:
=== Employee KPI CLI ===
1) Add employee
2) List employees
3) Load logs from CSV
4) Compute KPI report
5) Sort employees by name
6) Rank employees by KPI score
7) Search employee by ID
8) Filter employees by department
9) Show KPI table
0) Exit


🎓 Technologies Used

C Programming

Dynamic Memory (malloc, free, realloc)

Structures & Header Files

Sorting (qsort)

Searching

File Handling (CSV)

Basic Statistics (mean, median, regression slope)

Modular & Clean Architecture


🏁 Final Notes

This project demonstrates:

Modular C design

Real-world KPI modeling

Team collaboration with Git & GitHub

Clean separation of logic into multiple files.

SAMPLE IMAGES:

<img width="1724" height="923" alt="Screenshot 2025-11-30 135042" src="https://github.com/user-attachments/assets/deddabfc-b2e0-40b9-ae9a-18f1def912a3" />

<img width="1707" height="910" alt="image" src="https://github.com/user-attachments/assets/ff9b593d-b4f9-4a93-819e-8c999c596ebf" />


