#include <stdio.h>    // Standard input/output functions
#include <stdlib.h>   // Standard library functions, such as memory allocation
#include <string.h>   // String manipulation functions

//.......... (unchanged code)----->
// Function prototypes
// Function to handle user signup
void signUp();

// Function to perform user login
// Takes username and password as parameters
// Returns 1 on successful login, 0 on failure
int login(char *username, char *password);

// Function to add a task to the tasks.txt file
// Takes username as a parameter
void addTask(char *username);

// Function to view tasks from the tasks.txt file
// Takes username and date as parameters
void viewTasks(char *username, char *date);

// Function to delete the user account
// Takes username and password as parameters
void deleteAccount(char *username, char *password); //..........(unchanged code)..........

// Function to check if a date is valid
// Takes a date string as a parameter
// Returns 1 if the date is valid, 0 otherwise
int isValidDate(char *date);


// Main function
int main() {
    // Declare variables
    int choice;
    char username[50], password[50];

    // Main menu loop
    do {
        // Display main menu options
        printf("Task Management System\n");
        printf("1. SignUp\n2. Login\n3. Exit\n");
        printf("Enter your choice: ");

        // Get user choice
        scanf("%d", &choice);

        // Switch based on user choice
        switch (choice) {
            case 1:
                // User chooses to sign up
                signUp();
                break;
            case 2:
                // User chooses to login
                if (login(username, password)) {
                    // Logged-in menu loop
                    int loggedInChoice;
                    do {
                        // Display logged-in menu options
                        printf("1. Add Tasks\n2. View Tasks\n3. Delete Account\n4. Exit\n");
                        printf("Enter your choice: ");
                        
                        // Get logged-in user choice
                        scanf("%d", &loggedInChoice);

                        // Switch based on logged-in user choice
                        switch (loggedInChoice) {
                            case 1:
                                // User chooses to add tasks
                                addTask(username);
                                break;
                            case 2: {
                                // User chooses to view tasks for a specific date
                                char date[11];
                                printf("Enter date (DD/MM/YYYY): ");
                                scanf("%s", date);
                                if (isValidDate(date)) {
                                    viewTasks(username, date);
                                } else {
                                    printf("Invalid date format. Please try again.\n");
                                }
                                break;
                            }
                            case 3:
                                // User chooses to delete account
                                deleteAccount(username, password);
                                loggedInChoice = 4; // Exit the logged-in menu loop
                                break;
                            case 4:
                                // User chooses to exit
                                printf("Exiting...\n");
                                break;
                            default:
                                // Invalid choice within the logged-in menu
                                printf("Invalid choice. Please try again.\n");
                        }
                    } while (loggedInChoice != 4); // Continue the logged-in menu loop until user chooses to exit
                }
                break;
            case 3:
                // User chooses to exit the program
                printf("Exiting...\n");
                break;
            default:
                // Invalid choice within the main menu
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3); // Continue the main menu loop until user chooses to exit

    return 0;
}

/// Function to handle user signup
void signUp() {
    // Declare variables to store username and password
    char username[50], password[50];

    // Prompt user to enter username
    printf("Enter your username: ");

    // Read username from user input
    scanf("%s", username);

    // Open the file for reading
    FILE *file = fopen("signup.txt", "r");

    // Check if the file is opened successfully
    if (file != NULL) {
        // Declare variable to store existing usernames
        char existingUsername[50];

        // Loop through existing usernames in the file
        while (fscanf(file, "%s", existingUsername) != EOF) {
            // Check if the entered username already exists
            if (strcmp(username, existingUsername) == 0) {
                fclose(file); // Close the file
                printf("Username already exists. Please choose a different username.\n");
                return; // Exit the function if username already exists
            }
        }

        fclose(file); // Close the file after checking existing usernames
    }

    // Prompt user to enter password
    printf("Enter your password: ");

    // Read password from user input
    scanf("%s", password);

    // Open the file for appending (creating if not exists)
    file = fopen("signup.txt", "a");

    // Check if the file is opened successfully for appending
    if (file != NULL) {
        // Write the new username and password to the file
        fprintf(file, "%s %s\n", username, password);

        // Close the file after writing
        fclose(file);

        // Display success message
        printf("Signup successful!\n");
    } else {
        // Display an error message if unable to open the file
        printf("Error saving user information.\n");
    }
}

// Function to perform user login
int login(char *username, char *password) {
    // Declare variables to store user input
    char inputUsername[50], inputPassword[50];

    // Prompt the user to enter their username
    printf("Enter your username: ");
    
    // Read the username input from the user
    scanf("%s", inputUsername);

    // Prompt the user to enter their password
    printf("Enter your password: ");
    
    // Read the password input from the user
    scanf("%s", inputPassword);

    // Open the file "signup.txt" in read mode
    FILE *file = fopen("signup.txt", "r");

    // Check if the file was successfully opened
    if (file != NULL) {
        // Loop through each line in the file
        while (fscanf(file, "%s %s", username, password) != EOF) {
            // Check if the input username and password match the current line in the file
            if (strcmp(inputUsername, username) == 0 && strcmp(inputPassword, password) == 0) {
                // Close the file and notify the user of successful login
                fclose(file);
                printf("Login successful!\n");
                return 1; // Return 1 to indicate successful login
            }
        }
        
        // Close the file if the end of file is reached
        fclose(file);
    }

    // Notify the user of invalid username or password and prompt them to try again
    printf("Invalid username or password. Please try again.\n");

    // Return 0 to indicate unsuccessful login
    return 0;
}


// Function to add a task to the tasks.txt file
void addTask(char *username) {
    // Declare variables to store date and task description
    char date[11], taskDescription[100];
    
    // Prompt the user to enter the date in the format DD/MM/YYYY
    printf("Enter date (DD/MM/YYYY): ");
    
    // Read the date input from the user
    scanf("%s", date);

    // Check if the entered date is in a valid format using the isValidDate function
    if (!isValidDate(date)) {
        // Display an error message and return if the date is invalid
        printf("Invalid date format. Please try again.\n");
        return;
    }

    // Prompt the user to enter the task description (no spaces, use underscores)
    printf("Enter task description (no spaces, use underscores): ");
    
    // Read the task description input from the user
    scanf("%s", taskDescription);

    // Open the tasks.txt file in append mode
    FILE *file = fopen("tasks.txt", "a");
    
    // Check if the file was successfully opened
    if (file != NULL) {
        // Write the task information to the file in the format: username date task_description
        fprintf(file, "%s %s %s\n", username, date, taskDescription);
        
        // Close the file after writing
        fclose(file);
        
        // Display a success message
        printf("Task added successfully!\n");
    } else {
        // Display an error message if the file cannot be opened
        printf("Error adding task. Unable to open the file.\n");
    }
}

// Function to view tasks from the tasks.txt file
void viewTasks(char *username, char *date) {
    // Declare variables to store data from the file
    char fileUsername[50], fileDate[11], fileTask[100];
    
    // Variable to track if any tasks were found for the given username and date
    int found = 0;

    // Open the tasks.txt file in read mode
    FILE *file = fopen("tasks.txt", "r");

    // Check if the file was opened successfully
    if (file != NULL) {
        // Loop through each line in the file and read username, date, and task
        while (fscanf(file, "%s %s %s", fileUsername, fileDate, fileTask) != EOF) {
            // Check if the current line matches the given username and date
            if (strcmp(username, fileUsername) == 0 && strcmp(date, fileDate) == 0) {
                // Task found, set the found flag to true and print the task
                found = 1;
                printf("Task: %s\n", fileTask);
            }
        }
        
        // Close the file after reading
        fclose(file);
    }

    // Check if any tasks were found
    if (!found) {
        // Print a message if no tasks were found for the given username and date
        printf("No Tasks Found.\n");
    }
}


// Function to delete the user account
void deleteAccount(char *username, char *password) {
    // Prompting the user to enter their password for account deletion
    char inputPassword[50];
    printf("To delete your account, enter your password: ");
    scanf("%s", inputPassword);

    // Opening the file containing user accounts for reading
    FILE *inputFile = fopen("signup.txt", "r");
    // Opening a temporary file for writing
    FILE *outputFile = fopen("temp.txt", "w");

    // Checking if file operations were successful
    if (inputFile != NULL && outputFile != NULL) {
        // Variables to store username and password read from the file
        char fileUsername[50], filePassword[50];

        // Loop through each line of the file
        while (fscanf(inputFile, "%s %s", fileUsername, filePassword) != EOF) {
            // Check if the current line matches the specified username and password
            if (strcmp(username, fileUsername) == 0 && strcmp(inputPassword, filePassword) == 0) {
                // Notify user of successful account deletion
                printf("Account deleted successfully!\n");
            } else {
                // Write the current line to the temporary file if it doesn't match the specified account
                fprintf(outputFile, "%s %s\n", fileUsername, filePassword);
            }
        }

        // Close both input and output files
        fclose(inputFile);
        fclose(outputFile);

        // Remove the original file and rename the temporary file to the original filename
        remove("signup.txt");
        rename("temp.txt", "signup.txt");
    } else {
        // Notify user of an error if file operations were not successful
        printf("Error deleting account.\n");
    }
}

// Function to check if a date is valid
int isValidDate(char *date) {
    // Variables to store day, month, and year components of the date
    int day, month, year;

    // Use sscanf to parse the date string into day, month, and year
    if (sscanf(date, "%2d/%2d/%4d", &day, &month, &year) != 3) {
        return 0; // Return 0 if the date format is invalid (not enough or too many components)
    }

    // Check if month, day, and date are within valid ranges
    if (month < 1 || month > 12 || day < 1 || day > 31 ||
        (month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return 0; // Return 0 if the date components are out of valid ranges
    }

    // If all checks pass, return 1 indicating a valid date
    return 1; // Valid date
}

