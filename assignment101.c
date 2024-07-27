#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// STRUCTURE TO STORE EMPLOYEE DATA
struct s
{
    char name[20];
    char lastname[20];
    int id;
    int salary;
    char contact_no[12];
    char dob[15];
    char position[50];
    char doj[11];
    char gender[3];
    char gmail[30];
    char blood[3];
    char qualifications[30];
};

typedef struct s Employee;
void sortemployees(Employee *employees, int numEmployees);                                         // FUNCTION TO SORT EMPLOYEES
void addEmployee(Employee *employees, int *numEmployees);                                          // FUNCTION TO ADD EMPLOYEES
void updateEmployee(Employee *employees, int numEmployees);                                        // FUNCTION TO UPDATE EMPLOYEES
void deleteEmployee(Employee *employees, int *numEmployees, int *NumExEmp, Employee *ExEmployees); // FUNCTION TO DELETE EMPLOYEES
void displayEmployees(Employee *employees, int numEmployees);                                      // FUNCTION TO DISPLAY EMPLOYEES
void saveEmployeesToFile(Employee *employees, int numEmployees);                                   // FUNCTION TO SAVE EMPLOYEES
void readEmployeesFromFile(Employee *employees, int *numEmployees);                                // FUNCTION TO READ EMPLOYEES FILE
void displayExEmployees(Employee *employees, int numEmployees);                                    // FUNCTION TO DISPLAY EX EMPLOYEES
void DisplayEmployee(Employee employee[], int id, int numEmployees);                               // FUNCTION TO DISPLAY EMPLOYEES

// FUNCTION TO READ DELETED EMPLOYEES
void readDeletedEmployeesFromFile(Employee *employees, int *nEmployees)
{
    FILE *file = fopen("deleted_employees.txt", "r");
    char c;
    if (file == NULL)
    {
        return;
    }

    while (fscanf(file, "%s %s %d %d %s %s %s %s %s %s %s %s", employees[*nEmployees].name, &employees[*nEmployees].lastname,
                  &employees[*nEmployees].id, &employees[*nEmployees].salary, &employees[*nEmployees].dob, &employees[*nEmployees].contact_no, &employees[*nEmployees].position, &employees[*nEmployees].doj, &employees[*nEmployees].gmail, &employees[*nEmployees].blood, &employees[*nEmployees].gender, &employees[*nEmployees].qualifications) == 12)
    {
        (*nEmployees)++;
    }

    fclose(file);
}
// FUNCTION TO SAVE DELETED EMPLOYEES
void saveDeletedEmployeesToFile(Employee *employees, int nuEmployees)
{
    FILE *file = fopen("deleted_employees.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < nuEmployees; i++)
    {
        fprintf(file, "%s %s %d %d %s %s %s %s %s %s %s %s\n", employees[i].name, employees[i].lastname, employees[i].id, employees[i].salary, employees[i].dob, employees[i].contact_no, employees[i].position, employees[i].doj, employees[i].gmail, employees[i].blood, employees[i].gender, employees[i].qualifications);
    }

    fclose(file);
}
// FUNCTION FOR LOGO
void Logo()
{
    printf("\n");
    printf("      *****  **     **  ***** *     ****** *       * ***** *****      **     **     **     *    *     **     ******  ***** *****  \n");
    printf("      *      *  * *  *  *   * *     *    *   *   *   *     *          *  * *  *    *  *    * *  *    *  *    *       *     *   *  \n");
    printf("      ***    *   *   *  ***** *     *    *     *     ***   ***        *   *   *   ******   *  * *   ******   *  ***  ***   *****  \n");
    printf("      *      *       *  *     *     *    *     *     *     *          *       *  *      *  *   **  *      *  *    *  *     *  *    \n");
    printf("      *****  *       *  *     ***** ******     *     ***** *****      *       * *        * *    * *        * ******  ***** *    * \n");
    printf("      ___________________________________________________________________________________________________________________________");
}

// FUNCTION TO DISPLAY INTERFACE
void Display_name()
{
    printf("\n");
    printf("      *****  **     **  ***** *     ****** *       * ***** *****      **     **     **     *    *     **     ******  ***** *****  \n");
    printf("      *      *  * *  *  *   * *     *    *   *   *   *     *          *  * *  *    *  *    * *  *    *  *    *       *     *   *  \n");
    printf("      ***    *   *   *  ***** *     *    *     *     ***   ***        *   *   *   ******   *  * *   ******   *  ***  ***   *****  \n");
    printf("      *      *       *  *     *     *    *     *     *     *          *       *  *      *  *   **  *      *  *    *  *     *  *    \n");
    printf("      *****  *       *  *     ***** ******     *     ***** *****      *       * *        * *    * *        * ******  ***** *    * \n");
    printf("      ___________________________________________________________________________________________________________________________");
    printf("\n\n\n\n\n\n\n\n");
    printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
    printf("\t\t\t*                                                                         *\n");
    printf("\t\t\t*    1. Add Employee                                                      *\n");
    printf("\t\t\t*    2. Update Employee                                                   *\n");
    printf("\t\t\t*    3. Delete Employee                                                   *\n");
    printf("\t\t\t*    4. Display All Employees                                             *\n");
    printf("\t\t\t*    5. Display Past Employees                                            *\n");
    printf("\t\t\t*    6. Display Info of Employee                                          *\n");
    printf("\t\t\t*    7. Exit                                                              *\n");
    printf("\t\t\t*                                                                         *\n");
    printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
}

// FUNCTION FOR STRING COMPARISON
int strcmp(char s1[], char s2[])
{
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        else
            i++;
    }
    return (s1[i] - s2[i]);
}

// MAIN FUNCTION
int main()
{
    Employee employees[100];
    int numEmployees = 0;
    int choice;
    Employee ExEmployees[100];
    int NumExEmp = 0;
    Logo();
    char id[10];
    char pass[10];
    printf("\n\n\n\n\n\t\t\tENTER LOGIN CREDENTIALS :\n");
    printf("\t\t\tID: ");
    scanf("%s", id);
    printf("\t\t\tPassword: ");
    scanf("%s", pass);
    for (int i = 0; i < 6; i++)
    {
        if (strcmp("UDAY", id) == 0 && strcmp("uday9536", pass) == 0)
        {
            readEmployeesFromFile(employees, &numEmployees);
            readDeletedEmployeesFromFile(ExEmployees, &NumExEmp);
            do
            {
                system("cls");
                Display_name();
                printf("\t\t\tEnter your choice: ");
                scanf("%d", &choice);
                char c;
                switch (choice)
                {
                case 1:
                    system("cls");
                    addEmployee(employees, &numEmployees);
                    system("cls");
                    break;
                case 2:
                    updateEmployee(employees, numEmployees);
                    break;
                case 3:
                    deleteEmployee(employees, &numEmployees, &NumExEmp, ExEmployees);
                    scanf("%c", &c);
                    scanf("%c", &c);
                    system("cls");
                    break;
                case 4:
                    system("cls");
                    sortemployees(employees, numEmployees);
                    displayEmployees(employees, numEmployees);
                    system("cls");
                    break;
                case 5:
                    system("cls");
                    sortemployees(ExEmployees, NumExEmp);
                    displayExEmployees(ExEmployees, NumExEmp);
                    scanf("%c", &c);
                    scanf("%c", &c);
                    system("cls");
                    break;
                case 6:
                    system("cls");
                    Logo();
                    int id;
                    printf("\n\t\t\tEnter Employee ID: ");
                    scanf("%d", &id);
                    system("cls");
                    Logo();
                    DisplayEmployee(employees, id, numEmployees);
                    scanf("%c", &c);
                    scanf("%c", &c);
                    break;
                case 7:
                    saveEmployeesToFile(employees, numEmployees);
                    saveDeletedEmployeesToFile(ExEmployees, NumExEmp);
                    system("cls");
                    Logo();
                    printf("\n\nExiting program. Goodbye!\n");
                    printf("Live Long and Prosper !!");
                    scanf("%c", &c);
                    scanf("%c", &c);
                    return 0;
                default:
                    printf("Invalid choice. Please try again.\n");
                    break;
                }
            } while (choice != 7);
        }
        else
        {
            system("cls");
            Logo();
            char c;
            printf("\n\t\tWrong Credentials.\n");
            scanf("%c", &c);
            scanf("%c", &c);
            system("cls");
            Logo();
            printf("\n\n\n\n\n\tENTER LOGIN CREDENTIALS :\n");
            printf("\t\tID: ");
            scanf("%s", id);
            printf("\t\tPassword: ");
            scanf("%s", pass);
        }
    }
    printf("\t\t\t\tSORRY NO ACCESS FOR SCAMMERS (:"); // FUNNY STATEMENT.
    char c;
    scanf("%c", &c);
    scanf("%c", &c);
    return 0;
}

int str_len(char x[])
{
    int i = 0;
    while (x[i] != '\0')
    {
        i++;
    }
    return i;
}
// FUNCTION FOR STRING COMPARISON
int strcomp(char *x, char *y, int lenx, int leny)
{
    int i = 0, p = 0;
    while (x[i] != '\0' || y[i] != '\0')
    {
        if (x[i] > y[i])
        {
            return -1;
            break;
        }
        else if (x[i] == y[i])
        {
            p++;
        }
        else
        {
            return 1;
            break;
        }
        i++;
    }
    if (p == lenx || p == leny)
    {
        return 0;
    }
}

// FUNCTION TO DISPLAY EMPLOYEES
void DisplayEmployee(Employee employee[], int id, int numEmployees)
{
    int flag = 0;
    for (int i = 0; i < numEmployees; i++)
    {
        if (id == employee[i].id)
        {
            printf("\n\nEMPLOYEE ID:               %d\n", employee[i].id);
            printf("EMPLOYEE FISRTNAME:        %s\n", employee[i].name);
            printf("EMPLOYEE LASTNAME:         %s\n", employee[i].lastname);
            printf("EMPLOYEE GENDER:           %s\n", employee[i].gender);
            printf("EMPLOYEE POSITION:         %s\n", employee[i].position);
            printf("EMPLOYEE DATE OF BIRTH:    %s\n", employee[i].dob);
            printf("EMPLOYEE SALARY:           %d\n", employee[i].salary);
            printf("EMPLOYEE DATE OF JOINING:  %s\n", employee[i].doj);
            printf("EMPLOYEE QUALIFICATION:    %s\n", employee[i].qualifications);
            printf("EMPLOYEE CONTACT INFO:     %s\n", employee[i].contact_no);
            printf("EMPLOYEE GMAIL:            %s@gmail.com\n", employee[i].gmail);
            printf("EMPLOYEE BLOOD GRP:        %s\n", employee[i].blood);
            flag = 1;
        }
        else
        {
            flag = 0;
        }
    }
    if (flag = 0)
    {
        char c;
        printf("\n\n\t\t\tID not found.");
        scanf("%c", &c);
        return;
    }
}

// FUNCTION TO SORT EMPLOYEES
void sortemployees(Employee employees[], int numEmployees)
{
    for (int i = 0; i < numEmployees; i++)
    {
        for (int j = i + 1; j < numEmployees; j++)
        {
            if (strcomp(employees[i].name, employees[j].name, str_len(employees[i].name), str_len(employees[j].name)) == -1)
            {
                Employee temp;
                temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }
    for (int i = 0; i < numEmployees; i++)
    {
        for (int j = i + 1; j < numEmployees; j++)
        {
            if (strcomp(employees[i].name, employees[j].name, str_len(employees[i].name), str_len(employees[j].name)) == 0)
            {
                if (employees[i].id > employees[j].id)
                {
                    Employee temp;
                    temp = employees[i];
                    employees[i] = employees[j];
                    employees[j] = temp;
                }
            }
        }
    }
}
// FUNCTION TO ADD EMPLOYEES
void addEmployee(Employee *employees, int *numEmployees)
{
    if (*numEmployees == 100)
    {
        printf("Maximum number of employees reached.\n");
        return;
    }

    Employee newEmployee;
    Logo();
    printf("\n\n");
    printf("\t\tEnter ID: ");
    scanf("%d", &newEmployee.id);
    for (int i = 0; i < *numEmployees; i++)
    {
        if (employees[i].id == newEmployee.id)
        {
            printf("\t\tID in use.\n");
            printf("\t\tEnter ID: ");
            scanf("%d", &newEmployee.id);
            i = -1;
        }
        else
        {
            continue;
        }
    }

    printf("\t\tEMPLOYEE FIRSTNAME: ");
    scanf("%s", &newEmployee.name);
    printf("\t\tEMPLOYEE LASTNAME: ");
    scanf("%s", &newEmployee.lastname);
    printf("\t\tEMPLOYEE SALARY: ");
    scanf("%d", &newEmployee.salary);
    printf("\t\tCONTACT DETAILS: ");
    scanf("%s", &newEmployee.contact_no);
    printf("\t\tDATE OF BIRTH: ");
    scanf("%s", &newEmployee.dob);
    printf("\t\tEMPLOYEE GENDER(M/F): ");
    scanf("%s", &newEmployee.gender);
    printf("\t\tPOSITION IN COMPANY: ");
    scanf("%s", &newEmployee.position);
    printf("\t\tDATE OF JOINING: ");
    scanf("%s", &newEmployee.doj);
    printf("\t\tEMAIL ID: ");
    scanf("%s", &newEmployee.gmail);
    printf("\t\tQUALIFICATIONS: ");
    scanf("%s", &newEmployee.qualifications);
    printf("\t\tBLOOD GRP: ");
    scanf("%s", &newEmployee.blood);
    employees[*numEmployees] = newEmployee;

    (*numEmployees)++;

    printf("Employee added successfully.\n");
}
// FUNCTION TO UPDATE EMPLOYEES
void updateEmployee(Employee *employees, int numEmployees)
{
    int id, found = 0;
    system("cls");
    Logo();
    printf("\n\n\t\tEnter employee ID to update: ");
    scanf("%d", &id);
    // TAKING INPUT
    for (int i = 0; i < numEmployees; i++)
    {
        if (employees[i].id == id)
        {
            int s;
            printf("\t\t1.Update firstname\n");
            printf("\t\t2.Update lastname\n");
            printf("\t\t3.Update salary\n");
            printf("\t\t4.Update contact no\n");
            printf("\t\t5.Update Position\n");
            printf("\t\t6.Update Gmail\n");
            printf("\t\tEnter Choice: ");
            scanf("%d", &s);
            switch (s)
            {
            case (1):
                printf("\t\tEnter updated name: ");
                scanf("%s", employees[i].name);
                break;
            case (2):
                printf("\t\tEnter updated lastname: ");
                scanf("%s", employees[i].lastname);
                break;
            case (3):
                printf("\t\tEnter updated salary: ");
                scanf("%d", &employees[i].salary);
                break;
            case (4):
                printf("\t\tEnter contact no: ");
                scanf("%s", employees[i].contact_no);
                break;
            case (5):
                printf("\t\tEnter new Position: ");
                scanf("%s", employees[i].position);
                break;
            case (6):
                printf("\t\tEnter new Gmail: ");
                scanf("%s", employees[i].gmail);
                break;
            default:
                printf("Enter valid option.");
            }
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("\tEmployee updated successfully.\n");
        char c;
        scanf("%c", &c);
        scanf("%c", &c);
        system("cls");
    }
    else
        printf("\tEmployee not found.\n");
}
// FUNCTION TO DELETE EMPLOYEES
void deleteEmployee(Employee *employees, int *numEmployees, int *NumExEmp, Employee *ExEmployees)
{
    int id, found = 0;

    printf("Enter employee ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *numEmployees; i++)
    {
        if (employees[i].id == id)
        {
            ExEmployees[(*NumExEmp)] = employees[i];
            (*NumExEmp)++;
            for (int j = i; j < *numEmployees - 1; j++)
            {
                employees[j] = employees[j + 1];
            }
            (*numEmployees)--;
            found = 1;
            break;
        }
    }

    if (found)
        printf("Employee deleted successfully.\n");
    else
        printf("Employee not found.\n");
}
// FUNCTION TO DISPLAY EMPLOYEES
void displayEmployees(Employee *employees, int numEmployees)
{
    char c;
    if (numEmployees == 0)
    {
        printf("No employees to display.\n");
        return;
    }

    printf("Employee List:\n\n");
    printf("======================================================================================================================\n");
    printf("    ID       NAME    DATE OF BIRTH    POSITION    SALARY  DATE OF JOINING   EMAIL ID(@gmail.com)    CONTACT NO.  GENDER\n");
    printf("======================================================================================================================\n");
    for (int i = 0; i < numEmployees; i++)
    {
        printf("%6d%12s%15s%12s%10d%17s%24s%14s  %s\n",
               employees[i].id, employees[i].name, employees[i].dob, employees[i].position, employees[i].salary,
               employees[i].doj, employees[i].gmail, employees[i].contact_no, employees[i].gender);
    }
    printf("\n\n\n\n");
    scanf("%c", &c);
    scanf("%c", &c);
}

// FUNCTION TO SAVE EMPLOYEES
void saveEmployeesToFile(Employee *employees, int numEmployees)
{
    FILE *file = fopen("employees.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numEmployees; i++)
    {
        fprintf(file, "%s %s %d %d %s %s %s %s %s %s %s %s\n", employees[i].name, employees[i].lastname, employees[i].id, employees[i].salary, employees[i].dob, employees[i].contact_no, employees[i].position, employees[i].doj, employees[i].gmail, employees[i].blood, employees[i].gender, employees[i].qualifications);
    }

    fclose(file);
}
// FUNCTION TO READ EMPLOYEES
void readEmployeesFromFile(Employee *employees, int *numEmployees)
{
    FILE *file = fopen("employees.txt", "r");
    char c;
    if (file == NULL)
    {
        printf("No existing employee data found.\n");
        scanf("%c", &c);
        scanf("%c", &c);
        return;
    }

    while (fscanf(file, "%s %s %d %d %s %s %s %s %s %s %s %s", employees[*numEmployees].name, &employees[*numEmployees].lastname,
                  &employees[*numEmployees].id, &employees[*numEmployees].salary, &employees[*numEmployees].dob, &employees[*numEmployees].contact_no, &employees[*numEmployees].position, &employees[*numEmployees].doj, &employees[*numEmployees].gmail, &employees[*numEmployees].blood, &employees[*numEmployees].gender, &employees[*numEmployees].qualifications) == 12)
    {
        (*numEmployees)++;
    }

    fclose(file);
}
// FUNCTION TO DISPLAY EX EMPLOYEES
void displayExEmployees(Employee *employees, int numEmployees)
{
    if (numEmployees == 0)
    {
        printf("No employees to display.\n");
        char c;
        scanf("%c", &c);
        return;
    }

    printf("Past Employee List:\n\n");
    printf("======================================================================================================================\n");
    printf("    ID       NAME    DATE OF BIRTH    POSITION    SALARY  DATE OF JOINING   EMAIL ID(@gmail.com)    CONTACT NO.  GENDER\n");
    printf("======================================================================================================================\n");
    for (int i = 0; i < numEmployees; i++)
    {
        printf("%6d%12s%15s%12s%10d%17s%24s%14s   %s\n",
               employees[i].id, employees[i].name, employees[i].dob, employees[i].position, employees[i].salary,
               employees[i].doj, employees[i].gmail, employees[i].contact_no, employees[i].gender);
    }
}
