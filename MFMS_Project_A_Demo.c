/*
 * PAP521S - Programming in Practice
 * PROJECT A DEMONSTRATION SOLUTION
 * Municipal Financial Management System (MFMS)
 *
 * Teaching example: single-file C99 implementation.
 * Data is stored in arrays while the program runs; it is not saved
 * permanently after exit. This is acceptable as a foundation demo,
 * but groups may extend it.
 *
 * Compile: gcc -std=c99 -Wall -Wextra -pedantic main.c -o mfms
 * Run:     ./mfms
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RECORDS 100
#define NAME_LEN 80
#define jkoli 50
#define EMAIL_LEN 100
#define PHONE_LEN 30
#define TYPE_LEN 40
#define CONDITION_LEN 30

typedef struct {
    int id;][NAME_LEN];
    char department[DEPT_LEN];
    double basicSalary;
    double housingAllowance;
    double transportAllowance;
} Employee;

typedef struct {
    char department[DEPT_LEN];
    double allocated;
    double expenditure;
} Budget;

typedef struct {
    int id;
    char name[NAME_LEN];
    char email[EMAIL_LEN];
    char phone[PHONE_LEN];
    char town[NAME_LEN];
} Supplier;

typedef struct {
    int id;
    char name[NAME_LEN];
    char type[TYPE_LEN];
    double purchaseValue;
    char department[DEPT_LEN];
    char condition[CONDITION_LEN];
} Asset;

//The keyword static means that the array retains its values throughout the entire execution of the program, rather than being created and destroyed each time a function is called.
static Employee employees[MAX_RECORDS];
static Budget budgets[MAX_RECORDS];
static Supplier suppliers[MAX_RECORDS];
static Asset assets[MAX_RECORDS];
static int employeeCount = 0, budgetCount = 0, supplierCount = 0, assetCount = 0;

/* Read a whole line safely, including spaces. */
static void readLine(const char *prompt, char *buffer, size_t size) { //static here - 	Restricts the function to use within the current C source file.
    printf("%s", prompt); //prompt the user 
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0'; //store an empty string if reading fails, done by putting a null terminator at the first position of a string 
        return; //immediately ends the function and returns control to the function that called it 
    }
    buffer[strcspn(buffer, "\n")] = '\0'; //removes the newline / enter charecter 
}

/* Read an integer and reject non-numeric input. */
static int readInt(const char *prompt) { //as explained in the previous function 
    char line[100], *end; //variable end will help determine whether the entire input was a valid integer 
    long value; //why long because strtol function converts text into a long integer 
    while (1) { //1 means true so this creates an infinite loop unless something inside the loop will exit the loop or returns from the function 
        readLine(prompt, line, sizeof line); //calls the readline function. we already discussed the readline function before. 
        value = strtol(line, &end, 10); //strtol means string to long integer. line is the text to convert, &end is the address of the pointer where strtol will record as where conversation stopped, 10 is the number base 
        if (end != line && *end == '\0') return (int)value; //end == line if something not a number is entered. end == \0 at end of string. The two checks together ensure that at least part of the input was converted and that no extra characters remain after the number.
        puts("Invalid integer. Please try again."); //displays a string and automatically adds a newline at the end 
    }
}

/* Read a non-negative amount. */
static double readAmount(const char *prompt) { //this function ask a user to enter a number, check that the input is valid and non negative, keep asking until acceptable input is provided 
    char line[100], *end;
    double value;
    while (1) {
        readLine(prompt, line, sizeof line);
        value = strtod(line, &end); //converts string to decimal almost similar to string to login int in above function 
        if (end != line && *end == '\0' && value >= 0.0) return value; //just like above but we added an extra check for positivity 
        puts("Enter a valid number greater than or equal to zero.");
    }
}

static int readNonEmpty(const char *prompt, char *buffer, size_t size) {
    while (1) {
        readLine(prompt, buffer, size);
        if (strlen(buffer) > 0) return 1;
        puts("This field cannot be empty.");
    }
}

static int findEmployeeIndex(int id) {
    int i;
    for (i = 0; i < employeeCount; i++)
        if (employees[i].id == id) return i;
    return -1;
}
static int findSupplierIndex(int id) {
    int i;
    for (i = 0; i < supplierCount; i++)
        if (suppliers[i].id == id) return i;
    return -1;
}
static int findAssetIndex(int id) {
    int i;
    for (i = 0; i < assetCount; i++)
        if (assets[i].id == id) return i;
    return -1;
}
static int findBudgetIndex(const char *department) {
    int i;
    for (i = 0; i < budgetCount; i++)
        if (strcmp(budgets[i].department, department) == 0) return i;
    return -1;
}

static double calculateSalary(const Employee *e) {
    return e->basicSalary + e->housingAllowance + e->transportAllowance;
}

static void addEmployee(void) {
    Employee e;
    if (employeeCount >= MAX_RECORDS) { puts("Employee storage is full."); return; }
    e.id = readInt("Employee ID: ");
    if (findEmployeeIndex(e.id) >= 0) { puts("That employee ID already exists."); return; }
    readNonEmpty("Full name: ", e.name, sizeof e.name);
    readNonEmpty("Department: ", e.department, sizeof e.department);
    e.basicSalary = readAmount("Basic salary (N$): ");
    e.housingAllowance = readAmount("Housing allowance (N$): ");
    e.transportAllowance = readAmount("Transport allowance (N$): ");
    employees[employeeCount++] = e;
    printf("Employee added. Total monthly package: N$%.2f\n", calculateSalary(&e));
}

static void displayEmployees(void) {
    int i;
    if (employeeCount == 0) { puts("No employees registered."); return; }
    puts("\n--- EMPLOYEE REGISTER ---");
    for (i = 0; i < employeeCount; i++)
        printf("ID: %d | Name: %s | Dept: %s | Basic: N$%.2f | Total: N$%.2f\n",
               employees[i].id, employees[i].name, employees[i].department,
               employees[i].basicSalary, calculateSalary(&employees[i]));
}

static void searchEmployee(void) {
    int id = readInt("Enter employee ID to search: ");
    int index = findEmployeeIndex(id);
    if (index < 0) { puts("No employee found with that ID."); return; }
    printf("Found: %d | %s | %s | Total monthly package: N$%.2f\n",
           employees[index].id, employees[index].name, employees[index].department,
           calculateSalary(&employees[index]));
}

static void employeeMenu(void) {
    int choice;
    do {
        puts("\nEMPLOYEE MANAGEMENT\n1. Add employee\n2. Display employees\n3. Search by ID\n0. Back");
        choice = readInt("Choice: ");
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 0: break;
            default: puts("Invalid employee menu option.");
        }
    } while (choice != 0);
}

static void addOrUpdateBudget(void) {
    char department[DEPT_LEN];
    double allocated, expenditure;
    int index;
    readNonEmpty("Department: ", department, sizeof department);
    allocated = readAmount("Allocated budget (N$): ");
    expenditure = readAmount("Expenditure to date (N$): ");
    index = findBudgetIndex(department);
    if (index < 0) {
        if (budgetCount >= MAX_RECORDS) { puts("Budget storage is full."); return; }
        index = budgetCount++;
        strcpy(budgets[index].department, department);
    }
    budgets[index].allocated = allocated;
    budgets[index].expenditure = expenditure;
    printf("Budget saved. Remaining: N$%.2f | Status: %s\n",
           allocated - expenditure,
           expenditure <= allocated ? "WITHIN BUDGET" : "OVER BUDGET");
}

static void displayBudgets(void) {
    int i;
    if (budgetCount == 0) { puts("No budgets registered."); return; }
    puts("\n--- BUDGET REGISTER ---");
    for (i = 0; i < budgetCount; i++) {
        double remaining = budgets[i].allocated - budgets[i].expenditure;
        printf("%s | Allocated: N$%.2f | Spent: N$%.2f | Balance: N$%.2f | %s\n",
               budgets[i].department, budgets[i].allocated, budgets[i].expenditure,
               remaining, budgets[i].expenditure <= budgets[i].allocated ?
               "WITHIN BUDGET" : "OVER BUDGET");
    }
}

static void budgetMenu(void) {
    int choice;
    do {
        puts("\nBUDGET MANAGEMENT\n1. Add/update department budget\n2. Display budgets\n0. Back");
        choice = readInt("Choice: ");
        switch (choice) {
            case 1: addOrUpdateBudget(); break;
            case 2: displayBudgets(); break;
            case 0: break;
            default: puts("Invalid budget menu option.");
        }
    } while (choice != 0);
}

static void addSupplier(void) {
    Supplier s;
    if (supplierCount >= MAX_RECORDS) { puts("Supplier storage is full."); return; }
    s.id = readInt("Supplier ID: ");
    if (findSupplierIndex(s.id) >= 0) { puts("That supplier ID already exists."); return; }
    readNonEmpty("Supplier name: ", s.name, sizeof s.name);
    readNonEmpty("Email: ", s.email, sizeof s.email);
    readNonEmpty("Telephone: ", s.phone, sizeof s.phone);
    readNonEmpty("Town/location: ", s.town, sizeof s.town);
    suppliers[supplierCount++] = s;
    puts("Supplier added.");
}
static void displaySuppliers(void) {
    int i;
    if (supplierCount == 0) { puts("No suppliers registered."); return; }
    puts("\n--- SUPPLIER REGISTER ---");
    for (i = 0; i < supplierCount; i++)
        printf("ID: %d | %s | %s | %s | %s\n", suppliers[i].id,
               suppliers[i].name, suppliers[i].email, suppliers[i].phone, suppliers[i].town);
}
static void searchSupplier(void) {
    int id = readInt("Enter supplier ID: "), i;
    i = findSupplierIndex(id);
    if (i < 0) puts("No supplier found with that ID.");
    else printf("Found: %d | %s | %s | %s | %s\n", suppliers[i].id,
                suppliers[i].name, suppliers[i].email, suppliers[i].phone, suppliers[i].town);
}
static void supplierMenu(void) {
    int choice;
    do {
        puts("\nSUPPLIER MANAGEMENT\n1. Add supplier\n2. Display suppliers\n3. Search by ID\n0. Back");
        choice = readInt("Choice: ");
        switch (choice) {
            case 1: addSupplier(); break;
            case 2: displaySuppliers(); break;
            case 3: searchSupplier(); break;
            case 0: break;
            default: puts("Invalid supplier menu option.");
        }
    } while (choice != 0);
}

static void addAsset(void) {
    Asset a;
    if (assetCount >= MAX_RECORDS) { puts("Asset storage is full."); return; }
    a.id = readInt("Asset ID: ");
    if (findAssetIndex(a.id) >= 0) { puts("That asset ID already exists."); return; }
    readNonEmpty("Asset name: ", a.name, sizeof a.name);
    readNonEmpty("Asset type: ", a.type, sizeof a.type);
    a.purchaseValue = readAmount("Purchase value (N$): ");
    readNonEmpty("Department: ", a.department, sizeof a.department);
    readNonEmpty("Condition: ", a.condition, sizeof a.condition);
    assets[assetCount++] = a;
    puts("Asset added.");
}
static void displayAssets(void) {
    int i;
    if (assetCount == 0) { puts("No assets registered."); return; }
    puts("\n--- ASSET REGISTER ---");
    for (i = 0; i < assetCount; i++)
        printf("ID: %d | %s | Type: %s | Value: N$%.2f | Dept: %s | Condition: %s\n",
               assets[i].id, assets[i].name, assets[i].type, assets[i].purchaseValue,
               assets[i].department, assets[i].condition);
}
static void searchAsset(void) {
    int id = readInt("Enter asset ID: "), i;
    i = findAssetIndex(id);
    if (i < 0) puts("No asset found with that ID.");
    else printf("Found: %d | %s | %s | N$%.2f | %s | %s\n", assets[i].id,
                assets[i].name, assets[i].type, assets[i].purchaseValue,
                assets[i].department, assets[i].condition);
}
static void assetMenu(void) {
    int choice;
    do {
        puts("\nASSET MANAGEMENT\n1. Add asset\n2. Display assets\n3. Search by ID\n0. Back");
        choice = readInt("Choice: ");
        switch (choice) {
            case 1: addAsset(); break;
            case 2: displayAssets(); break;
            case 3: searchAsset(); break;
            case 0: break;
            default: puts("Invalid asset menu option.");
        }
    } while (choice != 0);
}

static double averageSalary(void) {
    int i; double total = 0.0;
    if (employeeCount == 0) return 0.0;
    for (i = 0; i < employeeCount; i++) total += calculateSalary(&employees[i]);
    return total / employeeCount;
}
static void reportsMenu(void) {
    int i;
    double allocated = 0.0, spent = 0.0, high = 0.0, low = 0.0;
    puts("\n========== MFMS REPORTS ==========");
    printf("Employee count: %d\n", employeeCount);
    if (employeeCount > 0) {
        high = low = calculateSalary(&employees[0]);
        for (i = 1; i < employeeCount; i++) {
            double salary = calculateSalary(&employees[i]);
            if (salary > high) high = salary;
            if (salary < low) low = salary;
        }
        printf("Average total monthly package: N$%.2f\n", averageSalary());
        printf("Highest total monthly package: N$%.2f\n", high);
        printf("Lowest total monthly package: N$%.2f\n", low);
    } else puts("No salary data available yet.");

    for (i = 0; i < budgetCount; i++) {
        allocated += budgets[i].allocated;
        spent += budgets[i].expenditure;
    }
    printf("\nBudget departments: %d\nTotal allocated: N$%.2f\nTotal expenditure: N$%.2f\n"
           "Overall balance: N$%.2f\n", budgetCount, allocated, spent, allocated - spent);
    puts("Departments over budget:");
    {
        int found = 0;
        for (i = 0; i < budgetCount; i++) {
            if (budgets[i].expenditure > budgets[i].allocated) {
                printf(" - %s (over by N$%.2f)\n", budgets[i].department,
                       budgets[i].expenditure - budgets[i].allocated);
                found = 1;
            }
        }
        if (!found) puts(" - None");
    }
    printf("\nRegistered suppliers: %d\n", supplierCount);
    displaySuppliers();
    printf("\nRegistered assets: %d\n", assetCount);
    displayAssets();
}

static void displayMainMenu(void) {
    puts("\n========================================");
    puts(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM");
    puts("========================================");
    puts("1. Employee Management");
    puts("2. Budget Management");
    puts("3. Supplier Management");
    puts("4. Asset Management");
    puts("5. Reports");
    puts("6. Exit");
}

int main(void) {
    int choice;
    do {
        displayMainMenu();
        choice = readInt("Enter your choice: ");
        switch (choice) {
            case 1: employeeMenu(); break;
            case 2: budgetMenu(); break;
            case 3: supplierMenu(); break;
            case 4: assetMenu(); break;
            case 5: reportsMenu(); break;
            case 6: puts("Thank you for using MFMS."); break;
            default: puts("Invalid menu choice. Enter a number from 1 to 6.");
        }
    } while (choice != 6);
    return 0;
}
