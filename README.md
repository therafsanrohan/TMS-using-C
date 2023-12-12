## Problem Statement:
You have to design a task management system where it must have a signup
and login system. Users will sign up by entering his/her Username (each user name needs to be
unique), and Password. This signup data will be stored in the "signup.txt" file. After successful
signup, the user will log in to the system by checking his/her credentials (Username and
Password). If the credentials do not match, the system will show the error message and suggest
logging in again.



## Functionalities:
1. Add Tasks: After successful login, the User can add tasks. To add a task, the user needs to
select the option to add tasks and then, the user needs to give the date, and then the task
description.

Let’s say the user named jmsbond007 wants to add a task about his Structured
Programming Language assignment on 10 December 2023. So the user will enter the task
as follows:
10/12/2023 Structured_Programming_Language_Project

Please note that the task description won’t have any space. Instead of space, we are using
underscore between the words. You need to store the tasks in a text file named
"tasks.txt". So, you need to write the details of the tasks in the file by maintaining the
following format:
jmsbond007 10/12/2023 Structured_Programming_Language_Project

3. View Tasks: To view the tasks of a particular date, the user needs to select the option of
view tasks first, then the user needs to provide the date as follows: DD/MM/YYYY. For
example, the user named jmsbond007 enters the date: 10/12/2023. Then, the system will
look for the tasks of jmsbond007 on the file named “tasks.txt” on that day. Then, it will
show the tasks of that day of jmsbond007 in the console. If no task is found of
jmsbond007 on that day, you need to print "No Tasks Found" on the console.

5. Delete Account: A user can remove his/her account from the system forever. To remove
an account, the user needs to give his/her username and password. If the password
matches, then his/her information will be deleted from the system. It can be handled
either by deleting information from the “signup.txt” file or storing deleted accounts in
another text file. After successful deletion, the user will be automatically exited from the
system.

7. Exit: It will terminate the program.







## Project Instructions:

So there will be 3 options before login:
1. SignUp
2. Login
3. Exit
   
There will be also 3 options after login.
1. Add Tasks
2. View Task
3. Delete Account
4. Exit


