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

// Main function
int main() {
    int choice;  // Variable to store the user's main menu choice
    char username[50], password[50];  // Variables to store user credentials

    // Main menu loop
    do {
        // Display the main menu options
        printf("Task Management System\n");
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
                    int loggedInChoice;  // Variable to store the user's logged-in menu choice
                    // Logged-in user menu loop
                    do {
                        // Display the logged-in user menu options
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


// Function to handle user signup
void signUp() {
    // Declare variables to store user input
    char username[50], password[50];

    // Prompt the user to enter a username
    printf("Enter your username: ");
    scanf("%s", username);

    // Check if the username already exists in the signup.txt file
    FILE *file = fopen("signup.txt", "r");
    if (file != NULL) {
        char existingUsername[50];

        // Iterate through existing usernames in the file
        while (fscanf(file, "%s", existingUsername) != EOF) {
            // Check if the entered username already exists
            if (strcmp(username, existingUsername) == 0) {
                fclose(file); // Close the file
                printf("Username already exists. Please choose a different username.\n");
                return; // Exit the function if the username already exists
            }
        }

        fclose(file); // Close the file after checking for existing usernames
    }

    // Prompt the user to enter a password
    printf("Enter your password: ");
    scanf("%s", password);

    // Save the user information (username and password) to the signup.txt file
    file = fopen("signup.txt", "a"); // Open the file in append mode
    if (file != NULL) {
        // Write the username and password to the file
        fprintf(file, "%s %s\n", username, password);
        fclose(file); // Close the file after writing
        printf("Signup successful!\n");
    } else {
        printf("Error saving user information.\n");
    }
}

// Function to perform user login
int login(char *username, char *password) {
    // Declare variables to store user input
    char inputUsername[50], inputPassword[50];

    // Prompt the user to enter their username
    printf("Enter your username: ");
    scanf("%s", inputUsername);

    // Prompt the user to enter their password
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    // Open the file containing user credentials for reading
    FILE *file = fopen("signup.txt", "r");

    // Check if the file was successfully opened
    if (file != NULL) {
        // Loop through the file to read username and password pairs
        while (fscanf(file, "%s %s", username, password) != EOF) {
            // Compare the entered username and password with the stored values
            if (strcmp(inputUsername, username) == 0 && strcmp(inputPassword, password) == 0) {
                // Close the file and indicate a successful login
                fclose(file);
                printf("Login successful!\n");
                return 1;  // Success
            }
        }

        // Close the file after reading all credentials
        fclose(file);
    }

    // If the loop completes without finding a match, indicate login failure
    printf("Invalid username or password. Please try again.\n");
    return 0;  // Failure
}


// Function to add a task to the tasks.txt file
void addTask(char *username) {
    // Declare variables to store date and task description
    char date[11], taskDescription[100];

    // Prompt the user to enter the date in the format DD/MM/YYYY
    printf("Enter date (DD/MM/YYYY): ");
    scanf("%s", date);

    // Prompt the user to enter the task description (no spaces, use underscores)
    printf("Enter task description (no spaces, use underscores): ");
    scanf("%s", taskDescription);

    // Open the tasks.txt file in append mode
    FILE *file = fopen("tasks.txt", "a");

    // Check if the file is successfully opened
    if (file != NULL) {
        // Write the task information to the file in the format "username date task_description"
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

// Function to view task to the tasks.txt file
void viewTasks(char *username, char *date) {
    // Declare variables to store data read from the file
    char fileUsername[50], fileDate[11], fileTask[100];
    // Variable to track whether tasks were found for the given user and date
    int found = 0;

    // Open the "tasks.txt" file in read mode
    FILE *file = fopen("tasks.txt", "r");

    // Check if the file was opened successfully
    if (file != NULL) {
        // Read data from the file until the end of the file is reached
        while (fscanf(file, "%s %s %s", fileUsername, fileDate, fileTask) != EOF) {
            // Check if the current line of the file matches the provided username and date
            if (strcmp(username, fileUsername) == 0 && strcmp(date, fileDate) == 0) {
                // Set the found flag to true
                found = 1;
                // Print the task for the given user and date
                printf("Task: %s\n", fileTask);
            }
        }

        // Close the file after reading
        fclose(file);
    }

    // If no tasks were found, print a message
    if (!found) {
        printf("No Tasks Found.\n");
    }
}

// Function to delete the user account
void deleteAccount(char *username, char *password) {
    char inputPassword[50];

    // Prompt the user to enter their password for account deletion
    printf("To delete your account, enter your password: ");
    scanf("%s", inputPassword);

    // Open the signup.txt file for reading (input)
    FILE *inputFile = fopen("signup.txt", "r");
    // Open a temporary file for writing (output)
    FILE *outputFile = fopen("temp.txt", "w");

    // Check if both files were successfully opened
    if (inputFile != NULL && outputFile != NULL) {
        char fileUsername[50], filePassword[50];

        // Read the signup.txt file line by line
        while (fscanf(inputFile, "%s %s", fileUsername, filePassword) != EOF) {
            // Check if the current line matches the provided username and password
            if (strcmp(username, fileUsername) == 0 && strcmp(inputPassword, filePassword) == 0) {
                // Skip the line (i.e., do not write to the output file) to delete the account
                printf("Account deleted successfully!\n");
            } else {
                // Write the current line to the temporary file (except for the line to be deleted)
                fprintf(outputFile, "%s %s\n", fileUsername, filePassword);
            }
        }

        // Close both files
        fclose(inputFile);
        fclose(outputFile);

        // Remove the original signup.txt file
        remove("signup.txt");
        // Rename the temporary file to the original file
        rename("temp.txt", "signup.txt");
    } else {
        // Print an error message if there was an issue opening files
        printf("Error deleting account.\n");
    }
}

