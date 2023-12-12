#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
// These prototypes declare the functions that will be defined later in the code.
// Function for user signup, prompting for a username and password and saving the information.
void signUp();
// Function for user login, asking for a username and password and verifying against stored credentials.
// Returns 1 on successful login, 0 on failure.
int login();
// Function to add a task for a logged-in user, taking a username as a parameter.
void addTask(char *username);
// Function to view tasks for a specific user on a given date, taking a username and date as parameters.
void viewTasks(char *username, char *date);
// Function to delete a user account, requiring the username and password for verification.
void deleteAccount(char *username, char *password);


int main() {
    int choice;  // Variable to store user's main menu choice
    char username[50], password[50];  // Variables to store user credentials

    // Main menu loop
    do {
        printf("1. SignUp\n2. Login\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signUp();  // Call the function for user signup
                break;
            case 2:
                // Login
                if (login(username, password)) {
                    int loggedInChoice;  // Variable to store user's logged-in menu choice
                    // Logged-in user menu loop
                    do {
                        printf("1. Add Tasks\n2. View Tasks\n3. Delete Account\n4. Exit\n");
                        printf("Enter your choice: ");
                        scanf("%d", &loggedInChoice);

                        switch (loggedInChoice) {
                            case 1:
                                addTask(username);  // Call the function to add a task
                                break;
                            case 2: {
                                char date[11];
                                printf("Enter date (DD/MM/YYYY): ");
                                scanf("%s", date);
                                viewTasks(username, date);  // Call the function to view tasks for a specific date
                                break;
                            }
                            case 3:
                                deleteAccount(username, password);  // Call the function to delete the user account
                                loggedInChoice = 4;  // To exit the inner loop after deleting the account
                                break;
                            case 4:
                                printf("Exiting...\n");
                                break;
                            default:
                                printf("Invalid choice. Please try again.\n");
                        }
                    } while (loggedInChoice != 4);
                }
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;  // Return 0 to indicate successful program execution
}


void signUp() {
    char username[50], password[50];

    printf("Enter your username: ");
    scanf("%s", username);

    // Check if the username already exists
    FILE *file = fopen("signup.txt", "r");
    if (file != NULL) {
        char existingUsername[50];
        while (fscanf(file, "%s", existingUsername) != EOF) {
            if (strcmp(username, existingUsername) == 0) {
                fclose(file);
                printf("Username already exists. Please choose a different username.\n");
                return;
            }
        }
        fclose(file);
    }

    printf("Enter your password: ");
    scanf("%s", password);

    // Save the user information to signup.txt
    file = fopen("signup.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s\n", username, password);
        fclose(file);
        printf("Signup successful!\n");
    } else {
        printf("Error saving user information.\n");
    }
}

int login(char *username, char *password) {
    char inputUsername[50], inputPassword[50];

    printf("Enter your username: ");
    scanf("%s", inputUsername);
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    FILE *file = fopen("signup.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s", username, password) != EOF) {
            if (strcmp(inputUsername, username) == 0 && strcmp(inputPassword, password) == 0) {
                fclose(file);
                printf("Login successful!\n");
                return 1;  // Success
            }
        }
        fclose(file);
    }

    printf("Invalid username or password. Please try again.\n");
    return 0;  // Failure
}

void addTask(char *username) {
    char date[11], taskDescription[100];

    printf("Enter date (DD/MM/YYYY): ");
    scanf("%s", date);
    printf("Enter task description (no spaces, use underscores): ");
    scanf("%s", taskDescription);

    FILE *file = fopen("tasks.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s %s\n", username, date, taskDescription);
        fclose(file);
        printf("Task added successfully!\n");
    } else {
        printf("Error adding task.\n");
    }
}

void viewTasks(char *username, char *date) {
    char fileUsername[50], fileDate[11], fileTask[100];
    int found = 0;

    FILE *file = fopen("tasks.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s %s", fileUsername, fileDate, fileTask) != EOF) {
            if (strcmp(username, fileUsername) == 0 && strcmp(date, fileDate) == 0) {
                found = 1;
                printf("Task: %s\n", fileTask);
            }
        }
        fclose(file);
    }

    if (!found) {
        printf("No Tasks Found.\n");
    }
}

void deleteAccount(char *username, char *password) {
    char inputPassword[50];

    printf("To delete your account, enter your password: ");
    scanf("%s", inputPassword);

    FILE *inputFile = fopen("signup.txt", "r");
    FILE *outputFile = fopen("temp.txt", "w");

    if (inputFile != NULL && outputFile != NULL) {
        char fileUsername[50], filePassword[50];
        while (fscanf(inputFile, "%s %s", fileUsername, filePassword) != EOF) {
            if (strcmp(username, fileUsername) == 0 && strcmp(inputPassword, filePassword) == 0) {
                // Skip the line (i.e., do not write to the output file) to delete the account
                printf("Account deleted successfully!\n");
            } else {
                fprintf(outputFile, "%s %s\n", fileUsername, filePassword);
            }
        }
        fclose(inputFile);
        fclose(outputFile);

        // Rename the temporary file to the original file
        remove("signup.txt");
        rename("temp.txt", "signup.txt");
    } else {
        printf("Error deleting account.\n");
    }
}
