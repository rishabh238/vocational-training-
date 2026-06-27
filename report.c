#include <stdio.h>
#include <stdlib.h>

int main()
{
    char name[100];
    int standard;
    char section;
    int maths, english, hindi, science, socialScience;
    int total;
    char grade;

    printf("=============================================\n");
    printf("\tREPORT CARD GENERATOR APP\n");
    printf("=============================================\n\n");

    // Input
    printf("Enter Student Name: ");
    scanf(" %[^\n]", name);

    while ((getchar()) != '\n');

    printf("Enter Standard: ");
    scanf("%d", &standard);

    while ((getchar()) != '\n');

    printf("Enter Section: ");
    scanf("%c", &section);

    printf("Enter Mathematics Marks: ");
    scanf("%d", &maths);

    printf("Enter English Marks: ");
    scanf("%d", &english);

    printf("Enter Hindi Marks: ");
    scanf("%d", &hindi);

    printf("Enter Science Marks: ");
    scanf("%d", &science);

    printf("Enter Social Science Marks: ");
    scanf("%d", &socialScience);

    // Calculate total
    total = maths + english + hindi + science + socialScience;

    // Validate total
    if (total > 500 || total < 0)
    {
        printf("\nInvalid Marks! Program Terminated.\n");
        return 0;
    }

    // Grade Calculation
    if (total >= 450)
        grade = 'A';
    else if (total >= 400)
        grade = 'B';
    else if (total >= 350)
        grade = 'C';
    else if (total >= 300)
        grade = 'D';
    else if (total >= 200)
        grade = 'E';
    else
        grade = 'F';

    // Report Card
    printf("\n---------------------------------------------\n");
    printf("\tJawahar Navodaya Vidyalaya\n");
    printf("\t    Annual Report Card\n");
    printf("---------------------------------------------\n");

    printf("Name      : %s\n", name);
    printf("Standard  : %d\n", standard);
    printf("Section   : %c\n\n", section);

    printf("Marks Secured out of 100\n");
    printf("Mathematics     : %d\n", maths);
    printf("English         : %d\n", english);
    printf("Hindi           : %d\n", hindi);
    printf("Science         : %d\n", science);
    printf("Social Science  : %d\n", socialScience);

    printf("\nTotal Marks : %d\n", total);
    printf("Grade       : %c\n", grade);

    printf("---------------------------------------------\n");

    return 0;
}