// ***
// *** Do NOT modify this file
// ***

#include "hw5.h"

int main(int argc, char **argv)
{

    // argv[1]: input file name
    // argv[2]: output file name, sorted by ID
    // argv[3]: output file name, sorted by name
    if (argc < 4)
    {
        return EXIT_FAILURE;
    }

    Student *stu;
    int numelem;
    if (StudentRead(argv[1], &stu, &numelem) == false)
    {
        return EXIT_FAILURE;
    }

    // You can use StudentPrint function to print the data from StudentRead
    // StudentPrint(stu, numelem);

    // sort students by ID
    sortStudents(stu, numelem, compareID);
    if (!areStudentsSorted(stu, numelem, compareID))
    {
        return EXIT_FAILURE;
    }
    if (StudentWrite(argv[2], stu, numelem) == false)
    {
        return EXIT_FAILURE;
    }

    // sort students by name
    sortStudents(stu, numelem, compareName);
    if (!areStudentsSorted(stu, numelem, compareName))
    {
        return EXIT_FAILURE;
    }
    if (StudentWrite(argv[3], stu, numelem) == false)
    {
        return EXIT_FAILURE;
    }

    free(stu);
    return EXIT_SUCCESS;
}
