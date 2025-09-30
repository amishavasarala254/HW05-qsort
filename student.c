// ***
// *** You MUST modify this file
// ***

#include "hw5.h" 
#include <stdio.h> // for fopen, fclose, printf, fprintf, sscanf
#include <stdlib.h> // for malloc, qsort
#include <stdbool.h> // for bool, true, false
#include <string.h> // for strcmp

// Assuming Student struct is defined in hw5.h as:
// typedef struct {
//     int ID;
//     char name[50]; // Assuming size 50 or larger for the name field
// } Student;


void StudentPrint(Student *stu, int num)
{
    printf("There are %d students\n", num);
    for (int ind = 0; ind < num; ind++)
    {
        printf("ID = %d, Name = %s\n", stu[ind].ID, stu[ind].name);
    }
}

// count the number of '\n' to determine the number of records
int countNewLine(FILE *fptr)
{
    int numline = 0;
    while (!feof(fptr))
    {
        int onechar = fgetc(fptr);
        if (onechar == '\n')
        {
            numline++;
        }
    }
    return numline;
}

/* This is the first function you need to implement */
bool StudentRead(char *filename, Student **stu, int *numelem)
{
    /* 1.1: open the file to read */
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        return false;
    }
    /* end of 1.1: open the file to read */

    int numline = countNewLine(fptr);

    // return to the beginning of the file
    // Check whether fseek fails (returns non-zero value)
    int rtv = fseek(fptr, 0, SEEK_SET);
    if (rtv != 0) // fseek returns 0 on success
    {
        fclose(fptr);
        return false;
    }

    /* 1.2 allocate memory for the data */
    // Allocate memory for the array of Student structs
    Student *stuptr = (Student *)malloc(numline * sizeof(Student));
    if (stuptr == NULL) { // Check whether memory allocation fails
        fclose(fptr);
        return false;
    }
    /* end of 1.2: allocate memory for the data */

    /* 1.3: read data from the file */
    char line[1024]; // Buffer to hold one line from the file
    int i = 0; // Counter for successfully read students

    // Read the data from the file line by line
    while (fgets(line, sizeof(line), fptr) != NULL && i < numline) {
        // Parse line into ID and name. Use %s to read name.
        // %49s prevents buffer overflow, assuming name[50] or larger
        if (sscanf(line, "%d %s", &stuptr[i].ID, stuptr[i].name) == 2) {
           i++; // Increment only on successful parse
        }
    }
    
    // Close the file after reading
    fclose(fptr);
    /* end of 1.3: read data from the file */

    // Update the number of elements with the count of successfully read records
    *numelem = i; 
    // Assign the dynamically allocated array pointer to the output pointer
    *stu = stuptr;
    
    return true;
}

/* This is the second function you need to implement */
bool StudentWrite(char *filename, Student *stu, int numelem)
{
    // open the file to write. Use "w" to create or overwrite.
    FILE *f = fopen(filename, "w"); // Corrected mode from "*r" to "w"
    if (f == NULL) 
    {
        return false;
    }
    
    // Write the data from array stu to the opened file
    for (int i = 0; i < numelem; i++) 
    {
        // Write ID and Name, followed by a newline
        if (fprintf(f, "%d %s\n", stu[i].ID, stu[i].name) < 0) {
             // Handle write error
             fclose(f);
             return false;
        }
    }
    
    // fclose the file in the end
    if (fclose(f) == EOF) {
        return false; // Error closing file
    }

    return true;
}

/* This is the third function you need to implement */
void sortStudents(Student *stu, int numelem, int (*compar)(const void *, const void *))
{
    /* Fill in to call qsort function to sort array stu */
    // qsort parameters: base, nitems, size, compar
    // The size of each element is the size of the Student struct
    qsort(stu, numelem, sizeof(Student), compar);
}

/* This is the fourth function you need to implement */
int compareID(const void *p1, const void *p2)
{
    /* Fill in to compare p1 and p2 by id */
    // Cast the generic pointers to Student pointers
    const Student *s1 = (const Student *)p1;
    const Student *s2 = (const Student *)p2;

    // Return the difference (s1->ID - s2->ID). This inherently gives:
    // < 0 if ID1 < ID2
    // = 0 if ID1 == ID2
    // > 0 if ID1 > ID2
    return s1->ID - s2->ID;
}

/* This is the fifth function you need to implement */
int compareName(const void *p1, const void *p2)
{
    /* Fill in to compare p1 and p2 by name */
    // Cast the generic pointers to Student pointers
    const Student *s1 = (const Student *)p1;
    const Student *s2 = (const Student *)p2;

    // Use strcmp function on the name field
    // strcmp returns the comparison result expected by qsort
    return strcmp(s1->name, s2->name);
}

/* This is the sixth function you need to implement */
bool areStudentsSorted(Student *stu, int numelem, int (*compar)(const void *, const void *))
{
    /* Fill in to check if the stu array is sorted according to compar */
    // return true if the stu array is sorted according to compar
    int i; 

    if (numelem <= 1) 
    {
        return true;
    }
    
    for (i = 0; i < numelem - 1; i++) 
    {
        // Check for an inversion (where stu[i] is "greater than" stu[i+1])
        if (compar(&stu[i], &stu[i+1]) > 0) 
        {
            return false; // return false otherwise
        }
    }
    
    return true;
}
