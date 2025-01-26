#include <stdio.h>
#include <string.h>

int login();
void searchStudent();
void searchLaptop();

int main()
{
    int userchoice;
    char role[10];

    if (!login(role))
    {
        printf("Login failed. Exiting program.\n");
        return 0;
    }

    while (1)
    {

        printf("\n--- Menu ---\n");
        if (strcmp(role, "admin") == 0)
        {
            printf("1. search student\n");
            printf("2. search laptop\n");
            printf("3. Exit\n");
        }
        else if (strcmp(role, "user") == 0)
        {
            printf("2. search laptop\n");
            printf("3. Exit\n");
        }
        else
        {
            printf("invalid role");
            return 0;
        }
        printf("enter your choice: ");
        scanf("%d", &userchoice);
        if (strcmp(role, "admin") == 0)
        {

            switch (userchoice)
            {
            case 1:
                searchStudent();
                break;
            case 2:
                searchLaptop();
                break;
            case 3:
                printf("Exit\n");
                return 0;
            default:
                printf("Wrong choice.\n");
            }
        }
        else if (strcmp(role, "user") == 0)
        {
            switch (userchoice)
            {
            case 2:
                searchLaptop();
                break;
            case 3:
                printf("Exit\n");
                return 0;
            default:
                printf("Wrong choice.\n");
            }
        }
    }

    return 0;
}

int login(char *role)
{
    char line[100];
    char inputUsername[50], inputPassword[50];
    int loginSuccess = 0;

    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    FILE *ftpr = fopen("user.txt", "r");

    if (ftpr == NULL)
    {
        printf("Cannot open file.\n");
        return 0;
    }

    printf("\n--- Reading File ---\n");

    // Read each line
    while (fgets(line, sizeof(line), ftpr) != NULL)
    {
        char fileUsername[50], filePassword[50], fileRole[10];

       if (sscanf(line, "Username: %s Password: %s Role: %s", fileUsername, filePassword, fileRole) == 3)
        {
            if (strcmp(inputUsername, fileUsername) == 0 && strcmp(inputPassword, filePassword) == 0)
            {
               printf("Login successful. Role: %s\n", fileRole);
               strcpy(role, fileRole);
                loginSuccess = 1;
                break;
            }
        }
    }

    if (!loginSuccess)
    {
        printf("Invalid username or password.\n");
    }

    fclose(ftpr);
    return loginSuccess;
}

void searchLaptop()
{
    char line[100];
    char searchQuery[50];
    int found = 0;

    // Input search
    printf("Enter laptop name or model to search: ");
    scanf("%s", searchQuery);

    FILE *ftpr = fopen("laptops.txt", "r");

    if (ftpr == NULL)
    {
        printf("Cannot open file.\n");
        return;
    }

    printf("\n--- Searching for Laptop ---\n");

    // Read each line from the file
    while (fgets(line, sizeof(line), ftpr) != NULL)
    {
        int i = 0, j = 0, matchFound = 0;

        while (line[i] != '\0' && line[i] != '\n')
        {
            if (line[i] == searchQuery[j])
            {
                j++;
                if (searchQuery[j] == '\0') // Full match of searchQuery
                {
                    matchFound = 1;
                    break;
                }
            }
            else
            {
                j = 0;
            }
            i++;
        }

        if (matchFound)
        {
            printf("Found: %s", line);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("No laptop found.\n");
    }

    fclose(ftpr);
}

void searchStudent()
{
    char line[100];
    char searchQuery[50];
    int found = 0;

    printf("Enter student ID or Name to search: ");
    scanf("%s", searchQuery);

    FILE *ftpr = fopen("students.txt", "r");

    if (ftpr == NULL)
    {
        printf("Cannot open file.\n");
        return;
    }

    printf("\n--- Searching for Student ---\n");

    // Read each line
    while (fgets(line, sizeof(line), ftpr) != NULL)
    {
        int i = 0, j = 0, matchFound = 0;

        while (line[i] != '\0' && line[i] != '\n')
        {
            if (line[i] == searchQuery[j])
            {
                j++;
                if (searchQuery[j] == '\0')
                {
                    matchFound = 1;
                    break;
                }
            }
            else
            {
                j = 0;
            }
            i++;
        }

        if (matchFound)
        {
            printf("Found: %s", line);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("No student found.\n");
    }

    fclose(ftpr);
}