#include <stdio.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    int age;
    char course[50];
    float marks;
};

void addStudent() {
    FILE *fp = fopen("data.txt", "a");
    struct Student s;

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Course: ");
    scanf("%s", s.course);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %d %s %.2f\n", s.roll, s.name, s.age, s.course, s.marks);

    fclose(fp);

    printf("\nStudent added successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen("data.txt", "r");
    struct Student s;

    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    printf("\n======== All Students ========\n");

    while (fscanf(fp, "%d %s %d %s %f", &s.roll, s.name, &s.age, s.course, &s.marks) != EOF) {
        printf("\nRoll: %d\nName: %s\nAge: %d\nCourse: %s\nMarks: %.2f\n",
        s.roll, s.name, s.age, s.course, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("data.txt", "r");
    struct Student s;
    int roll, found = 0;

    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %d %s %f", &s.roll, s.name, &s.age, s.course, &s.marks) != EOF) {
        if (s.roll == roll) {
            printf("\nRecord Found:\n");
            printf("Roll: %d\nName: %s\nAge: %d\nCourse: %s\nMarks: %.2f\n",
            s.roll, s.name, s.age, s.course, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nRecord not found.\n");

    fclose(fp);
}

void updateStudent() {
    FILE *fp = fopen("data.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Student s;
    int roll, found = 0;

    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %d %s %f", &s.roll, s.name, &s.age, s.course, &s.marks) != EOF) {
        if (s.roll == roll) {
            printf("\nEnter New Name: ");
            scanf("%s", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Course: ");
            scanf("%s", s.course);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            found = 1;
        }
        fprintf(temp, "%d %s %d %s %.2f\n", s.roll, s.name, s.age, s.course, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove("data.txt");
    rename("temp.txt", "data.txt");

    if (found)
        printf("\nRecord Updated Successfully!\n");
    else
        printf("\nRecord Not Found!\n");
}

void deleteStudent() {
    FILE *fp = fopen("data.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct Student s;
    int roll, found = 0;

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %d %s %f", &s.roll, s.name, &s.age, s.course, &s.marks) != EOF) {
        if (s.roll != roll) {
            fprintf(temp, "%d %s %d %s %.2f\n", s.roll, s.name, s.age, s.course, s.marks);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("data.txt");
    rename("temp.txt", "data.txt");

    if (found)
        printf("\nRecord Deleted Successfully!\n");
    else
        printf("\nRecord Not Found!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n======== Student Database Management System ========\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: return 0;
            default: printf("\nInvalid choice!\n");
        }
    }

    return 0;
}
