# Municipal Financial Management System (MFMS) — Project A Demo

**Course:** PAP521S – Programming in Practice  
**Language:** ANSI C / C99  
**Purpose:** A teaching example illustrating the expected *foundation* system, not a complete municipal ERP.

## Features demonstrated
- Main menu and separate module menus.
- Employee records, search, and salary-package calculation.
- Department budget entry/update, remaining balance and over-budget status.
- Supplier records and search.
- Asset register and search.
- Summary reports: employee salary statistics, total budget/expenditure, over-budget departments, supplier and asset listings.
- Arrays, structures, strings, loops, decisions, functions, parameters and return values.
- Basic validation for numeric input, negative amounts, empty text, duplicate IDs and invalid menu options.

## Compile and run
Linux/macOS:
```bash
gcc -std=c99 -Wall -Wextra -pedantic MFMS_Project_A_Demo.c -o mfms
./mfms
```
Windows (GCC/MinGW):
```bash
gcc -std=c99 -Wall -Wextra -pedantic MFMS_Project_A_Demo.c -o mfms.exe
mfms.exe
```

## Important limitation
Records are stored in arrays in memory only. They are lost when the program exits. Persistent file/database storage, authentication, audit trails and advanced municipal workflows are outside this small foundation demonstration unless your group chooses to add them.

## Suggested demonstration data
- Employee: ID 1001, Amalia Nghidinwa, Finance, basic 18000, housing 2500, transport 1200. Total package = N$21,700.
- Employee: ID 1002, Petrus Hamukwaya, Engineering, basic 15000, housing 2000, transport 1000. Total package = N$18,000.
- Budget: Finance, allocated 500000, expenditure 420000. Balance = N$80,000, WITHIN BUDGET.
- Budget: Engineering, allocated 300000, expenditure 325000. Balance = -N$25,000, OVER BUDGET.
- Supplier: ID 501, Northern Office Supplies, sales@example.com, 061123456, Windhoek.
- Asset: ID 801, Office Laptop, Computer, 14500, Finance, Good.

## Suggested live demo order
1. Show the main menu and explain each option.
2. Add two employees; display the register; search for ID 1001.
3. Add Finance and Engineering budgets; show the within-budget and over-budget outcomes.
4. Add and search a supplier.
5. Add and search an asset.
6. Open reports and explain totals and salary statistics.
7. Enter an invalid menu choice and a negative amount to show validation.
8. Open the source code and explain one structure, array, loop, `strcmp()`, function call, parameter and return value.
9. Show the GitHub repository, README, and real member commits.

## Discussion points for students
- Why use arrays? To store multiple records of the same type during execution.
- Why use structures? To keep related fields for each employee, supplier, asset or budget together.
- Why use functions? To separate responsibilities and make code easier to test and explain.
- Why `strcmp()`? C strings are character arrays; `strcmp()` compares their contents.
- What is not production-ready? No permanent storage, access control, backups, audit logging, concurrency handling or full financial controls.
