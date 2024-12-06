#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum number of students and courses
#define MAX_STUDENTS 100
#define MAX_SUBJECTS 6 // Number of subjects

// Define a structure to hold student information 
struct Student {
    int id;
    char name[50];
    int age;
    char gender;
    float marks[MAX_SUBJECTS]; // Marks for 6 subjects
    float percentage; // Percentage based on marks
};

struct User {
    char username[50];
    char password[50];
};

// Declare an array of students structure array
struct Student students[MAX_STUDENTS];
int student_count = 0;

// Function prototypes
void add_student();
void display_students();
void update_student();
void delete_student();
void input_grades(struct Student* student); // ali hamza
void calculate_percentage(struct Student* student);// ali hamza
void detailed_report(struct Student* student); // ali hamza
void check_pass_status(struct Student* student); // ali hamza
void save_data();
void load_data();
void backup_data(); // ali hamza
void print_reports(); // ali hamza 
void search_student();
void user_login();
void menu();

// Function to handle user login (Admin/Student)
void user_login() {
    struct User admin = {"admin", "adminpass"};
    struct User user_input;

    printf("Enter username: ");
    scanf("%s", user_input.username);
    printf("Enter password: ");
    scanf("%s", user_input.password);

    if (strcmp(user_input.username, admin.username) == 0 && strcmp(user_input.password, admin.password) == 0) {
        printf("Login successful as Admin.\n");
    } else {
        printf("Invalid username or password. Exiting program...\n");
        exit(1);
    }
}

// Menu-driven system for interaction
void menu() {
    int choice;
    do {
        printf("\n------ Student Management System ------\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Input Grades\n");
        printf("6. Calculate Percentage\n");
        printf("7. Detailed Report\n");
        printf("8. Check Pass Status\n");
        printf("9. Save Data\n");
        printf("10. Load Data\n");
        printf("11. Backup Data\n");
        printf("12. Print Reports\n");
        printf("13. Search Student\n");
        printf("14. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_student(); break;
            case 2: display_students(); break;
            case 3: update_student(); break;
            case 4: delete_student(); break;
            case 5: {
                int id;
                printf("Enter student ID: ");
                scanf("%d", &id);
                if (id >= 0 && id < student_count)
                    input_grades(&students[id]);
                else
                    printf("Student not found!\n");
                break;
            }
            case 6: {
                int id;
                printf("Enter student ID: ");
                scanf("%d", &id);
                if (id >= 0 && id < student_count)
                    calculate_percentage(&students[id]);
                else
                    printf("Student not found!\n");
                break;
            }
            case 7: {
                int id;
                printf("Enter student ID: ");
                scanf("%d", &id);
                if (id >= 0 && id < student_count)
                    detailed_report(&students[id]);
                else
                    printf("Student not found!\n");
                break;
            }
			case 8: {
    			int id;
    			printf("Enter student ID: ");
    			scanf("%d", &id);
    			if (id >= 0 && id < student_count)
        			check_pass_status(&students[id]);  // Updated function call
    			else
        			printf("Student not found!\n");
    			break;
			}

            case 9: save_data(); break;
            case 10: load_data(); break;
            case 11: backup_data(); break;
            case 12: print_reports(); break;
            case 13: search_student(); break;
            case 14: printf("Exiting program...\n"); break;
            default: printf("Invalid choice! Please try again.\n"); break;
        }
    } while (choice != 14);
}

// Function to add a new student
void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("Maximum student limit reached.\n");
        return;
    }

    struct Student new_student;
    new_student.id = student_count;

    // Clear the input buffer before reading the name
    while (getchar() != '\n');  // Clear the buffer

    printf("Enter student name: ");
    fgets(new_student.name, sizeof(new_student.name), stdin);
    new_student.name[strcspn(new_student.name, "\n")] = 0;  // remove trailing newline

    printf("Enter age: ");
    scanf("%d", &new_student.age);

    printf("Enter gender (M/F): ");
    getchar();  // consume leftover newline
    scanf("%c", &new_student.gender);

    // Validate gender input
    if (new_student.gender != 'M' && new_student.gender != 'F') {
        printf("Invalid gender input. Please enter M or F.\n");
        return;
    }

    students[student_count++] = new_student;
    printf("Student added successfully.\n");
}

// Function to display all students
void display_students() {
    if (student_count == 0) {
        printf("No students found.\n");
        return;
    }
    for (int i = 0; i < student_count; i++) {
        printf("ID: %d, Name: %s, Age: %d, Gender: %c\n",
               students[i].id, students[i].name, students[i].age, students[i].gender);
    }
}

// Function to input grades for a student
void input_grades(struct Student* student) {
    const char* subjects[] = {"Urdu", "English", "Science", "Math", "Pak Studies", "Islamiyat"};
    printf("Enter grades for %s (6 subjects, each out of 100):\n", student->name);
    
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        float grade;
        int valid_input = 0;
        
        while (!valid_input) {
            printf("Enter marks for %s (out of 100): ", subjects[i]);
            scanf("%f", &grade);
            
            // Input validation: Marks must be between 0 and 100
            if (grade < 0 || grade > 100) {
                printf("Error: Marks for %s cannot exceed 100. Please enter again.\n", subjects[i]);
            } else {
                student->marks[i] = grade;
                valid_input = 1;
            }
        }
    }
}

// Function to calculate percentage
void calculate_percentage(struct Student* student) {
    float total_marks = 0;
    
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        total_marks += student->marks[i];
    }

    // Percentage is the total marks out of 600 (6 subjects, each 100 marks)
    student->percentage = (total_marks / (MAX_SUBJECTS * 100)) * 100;
    printf("Percentage for %s: %.2f%%\n", student->name, student->percentage);
}

// Function to check pass status based on percentage
void check_pass_status(struct Student* student) {
    if (student->percentage >= 50.0) {
        printf("%s has passed with a percentage of %.2f%%\n", student->name, student->percentage);
    } else {
        printf("%s has not passed. Percentage is %.2f%%\n", student->name, student->percentage);
    }
}

// Function to display a detailed report of a student
void detailed_report(struct Student* student) {
    printf("\n------ Detailed Report for %s ------\n", student->name);
    printf("Student ID: %d\n", student->id);
    printf("Name: %s\n", student->name);
    printf("Age: %d\n", student->age);
    printf("Gender: %c\n", student->gender);

    // Print marks for each subject
    const char* subjects[] = {"Urdu", "English", "Science", "Math", "Pak Studies", "Islamiyat"};
    printf("Marks:\n");
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        printf("%s: %.2f\n", subjects[i], student->marks[i]);
    }

    // Print percentage
    printf("Percentage: %.2f%%\n", student->percentage);
}

// Save student data to a file
void save_data() {
    FILE *file = fopen("students_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving data.\n");
        return;
    }

    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%d %s %d %c %.2f ", students[i].id, students[i].name, students[i].age,
                students[i].gender, students[i].percentage);
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            fprintf(file, "%.2f ", students[i].marks[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Data saved successfully.\n");
}

// Load student data from a file
void load_data() {
    FILE *file = fopen("students_data.txt", "r");
    if (file == NULL) {
        printf("Error opening file for loading data.\n");
        return;
    }

    student_count = 0;
    while (fscanf(file, "%d %s %d %c %f", &students[student_count].id,
                   students[student_count].name, &students[student_count].age,
                   &students[student_count].gender, &students[student_count].percentage) != EOF) {
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            fscanf(file, "%f", &students[student_count].marks[j]);
        }
        student_count++;
    }

    fclose(file);
    printf("Data loaded successfully.\n");
}

// Backup student data
void backup_data() {
    FILE *source = fopen("students_data.txt", "r");
    if (source == NULL) {
        printf("Error opening source file for backup.\n");
        return;
    }

    FILE *destination = fopen("backup_students_data.txt", "w");
    if (destination == NULL) {
        printf("Error opening backup file.\n");
        fclose(source);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes, destination);
    }

    fclose(source);
    fclose(destination);
    printf("Data backed up successfully.\n");
}

// Print all reports for students
void print_reports() {
    if (student_count == 0) {
        printf("No student reports available.\n");
        return;
    }

    for (int i = 0; i < student_count; i++) {
        detailed_report(&students[i]);
    }
}

// Search for a student by name
void search_student() {
    char name[50];
    printf("Enter student name to search: ");
    getchar(); // Consume leftover newline
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove trailing newline

    int found = 0;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Student found!\n");
            detailed_report(&students[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

// Function to update a student's information
void update_student() {
    int id;
    printf("Enter student ID to update: ");
    scanf("%d", &id);

    if (id < 0 || id >= student_count) {
        printf("Student not found!\n");
        return;
    }

    struct Student *student = &students[id];

    // Clear the input buffer before reading the name
    while (getchar() != '\n');  // Clear the buffer

    printf("Updating student: %s\n", student->name);
    printf("Enter new name: ");
    fgets(student->name, sizeof(student->name), stdin);
    student->name[strcspn(student->name, "\n")] = 0;

    printf("Enter new age: ");
    scanf("%d", &student->age);

    printf("Enter new gender (M/F): ");
    getchar();  // consume leftover newline
    scanf("%c", &student->gender);

    // Validate gender input
    if (student->gender != 'M' && student->gender != 'F') {
        printf("Invalid gender input. Please enter M or F.\n");
    }

    printf("Student information updated successfully.\n");
}

// Function to delete a student's record
void delete_student() {
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    if (id < 0 || id >= student_count) {
        printf("Student not found!\n");
        return;
    }

    for (int i = id; i < student_count - 1; i++) {
        students[i] = students[i + 1]; // Shift students left
    }
    student_count--;
    printf("Student deleted successfully.\n");
}

int main() {
    user_login();  // Admin login
    menu();  // Show menu and handle user choices

    return 0;
}
