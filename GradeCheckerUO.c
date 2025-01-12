//Check the meaning of your uOttawa course grade, whether it is in Letter or Letters or in Number.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*  Connecter between letterGradeTable to GRADINGS 
    Allows GRADINGS be an integer array, thus avoid some parsing when dealing with number grades and grade points */
enum letterGradeENUM{
    A_PLUS  ,
    A       ,
    A_MINUS ,
    B_PLUS  ,
    B       ,
    C_PLUS  ,
    C       ,
    D_PLUS  ,
    D       ,
    E       ,
    F       ,
    ABS     ,
    EIN     ,
    CR      ,
    NC      ,
    P       ,
    S       ,
    NS      ,
};

int main(){

    //{Letter Grade, Number Grade, Grade Point}
    const int GRADINGS[][3] = {
        {   A_PLUS , 90 , 10    },
        {   A      , 85 , 9     },
        {   A_MINUS, 80 , 8     },
        {   B_PLUS , 75 , 7     },
        {   B      , 70 , 6     },
        {   C_PLUS , 65 , 5     },
        {   C      , 60 , 4     },
        {   D_PLUS , 55 , 3     },
        {   D      , 50 , 2     },
        {   E      , 40 , 1     },
        {   F      , 0  , 0     },
        {   ABS    , -1 , 0     }, 
        {   EIN    , -1 , 0     }, 
        {   CR     , -1 , -1    }, 
        {   NC     , -1 , -1    }, 
        {   P      , -1 , -1    },  
        {   S      , -1 , -1    },  
        {   NS     , -1 , -1    }  
    };

    /*  A look up table between the letter type inputGrade and GRADINGS */
    const char *letterGradeTable[] = {
        [A_PLUS]  = "A+",
        [A]       = "A",
        [A_MINUS] = "A-",
        [B_PLUS]  = "B+",
        [B]       = "B",
        [C_PLUS]  = "C+",
        [C]       = "C",
        [D_PLUS]  = "D+",
        [D]       = "D",
        [E]       = "E",
        [F]       = "F",
        [ABS]     = "ABS",
        [EIN]     = "EIN",
        [CR]      = "CR",
        [NC]      = "NC",
        [P]       = "P",
        [S]       = "S",
        [NS]      = "NS",
        NULL
    };

    //{Letter Grade, Meaning}
    const char *MEANINGS[][2] = {
        {"E"    , "Failure with the right to supplemental examination in certain faculties. This does not apply to graduate studies."},
        {"ABS"  , "Absent"},
        {"EIN"  , "Failure/Incomplete"},
        {"CR"   , "Credited course "},
        {"NC"   , "No units"},
        {"P"    , "Pass"},
        {"S"    , "Satisfactory"},
        {"NS"   , "Not satisfactory"}
    };

    //Description of the minimum passing grades of the courses in uOttawa
    const char *MINIMUM_PASSING = {
                            "\nUndergraduate Courses:  \n"
                            "       D for all, except:\n"
                            "           C   for Faculty of Education, Medical Education Program (MED and CLI), Doctor of Pharmacy (PHA) program.\n"
                            "           C+  for nursing courses (NSG), accreditation purposes, some undergraduate nutrition and dietetic courses (NUT).\n"
                            "\n"
                            "Graduate Courses:  \n"
                            "       C+  for all unless specified otherwise.\n"
                            "       *Note: The passing grades required in a course that includes students at more than one level are determined by each student’s level and not by the course level.\n\n"
    };
    //printf("%s", MINIMUM_PASSING);

    char letterGrade[10] = {0}, inputGrade[100] = {0}; 
    char *endPtrForNumericalInput;  
    double numberGrade;
    int gradePoint;

    printf( "\nGrade:   " );
    scanf( "%s", inputGrade );

    numberGrade = strtod( inputGrade, &endPtrForNumericalInput );

    if( *endPtrForNumericalInput=='\0' ){

        //Valid Grades should range from 0 to 100
        if( numberGrade > 100 || numberGrade < 0){
            printf( numberGrade>100 ? "INVALID_GRADE: Input Grade is Greater than 100\n\n" 
                                    : "INVALID_GRADE: Input Grade is Smaller than 0\n\n"   );
            return 0;
        }

        //inputGrade is a number
        for( int i=0; i < sizeof(GRADINGS)-1; i++ ){
            if( numberGrade >= GRADINGS[i][1] ){
                strcpy( letterGrade, letterGradeTable[i] );
                gradePoint = GRADINGS[i][2];
                break;
            }
        }
        printf( "Letter grade:  %s\n", letterGrade );
        printf( "Grade point(s) earned:    %d\n", gradePoint );
        printf("%s", MINIMUM_PASSING);

    }else if( *endPtrForNumericalInput==inputGrade[0] ){
        
        //inputGrade is letter type
        char *ptr = inputGrade;

        //  Make the string all uppercase
        while( *ptr != '\0' ){
            char temp[2] = { toupper( *ptr ), '\0' };
            strcat( letterGrade, temp );
            ptr++;
        }

        //  Formatize inputs like "X+" or "X-" to "X_PLUS" and "X_MINUS"
        /*while( *ptr != '\0' ){
            if( *ptr != '+' && *ptr != '-' ){
                char temp[2] = {toupper(*ptr), '\0'};
                strcat(letterGrade, temp);                
            }else{
                strcat(letterGrade, *ptr=='+' ? "_PLUS" : "_MINUS");
            }
            ptr++;
        }
        *ptr = '\0';*/

        for( int i=0; letterGradeTable[i] != NULL ; i++ ){
            if( strcmp( letterGrade, letterGradeTable[i] ) == 0 ){
                numberGrade = GRADINGS[i][1];
                gradePoint = GRADINGS[i][2];
                if( i==0 ){
                    printf( "Number grade:  %.2lf ~ 100\n", numberGrade );
                }else{
                    printf( "Number grade:  %.2lf ~ %d\n", numberGrade, GRADINGS[i-1][1] );
                }
                printf( "Grade point(s) earned:    %d\n", gradePoint );
                printf("%s", MINIMUM_PASSING);

                break;
            }
        }

    }else{
        printf( "Invalid Input!");
        return 0;
    }
    
    

    return 0;
}