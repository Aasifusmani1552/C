#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000
int mgetline(char* s, int limit) {  // getline function to get user input
    int   c;
    char* s_start = s;
    while (limit > 0 && ((c = getchar())) != EOF && c != '\n') {
        *s++ = c;
        limit--;
    }
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return s - s_start;
}
int main(int argc, char* argv[]) {  // argument count and argument vector used
                                    // (command line arguments)
    char  line[MAXLINE];            // to store user input
    long  lineno = 0;               // give line number to input
    char* ffound;  //  to store pointer and show error if no match found within
                   //  current line
    int c, except = 0,
           number = 0;  // c to store flags, except for boolean logic for not
                        // printing matching lines and number for boolean logic
                        // for printing line number before line
    while (--argc > 0 &&
           (*++argv)[0] ==
               '-') {  // decrementing argc to 0 and *++argv[0] is used because
                       // argv is a pointer to pointer array(eventually)
        while (c = *++argv[0]) {  // checking if dereferenced argv is x or n
                                  // after '-'
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;

                default:
                    printf("illegal flag used %c!!\n",
                           c);  // if argv is not either x or n
                    argc = 0;
                    break;
            }
        }
    }
    if (argc != 1) {  // if no argument given or more arguments given than 2(one
                      // is to invoke program and other is flag)
        printf("Usage: find -x -npattern\n");
    } else {
        while (mgetline(line, MAXLINE) > 0) {  // getting user input
            lineno++;  // to show the index where match found
            ffound = strstr(line, *argv);  // store the pointer where match
                                           // found or null if no match found
            if ((ffound != NULL) != except) {  // if match found and except on
                                               // the basic of used or not used
                if (number) {  // if number is not zero that is if -n used
                    printf("%ld:", lineno);  // print index number
                }
                printf("%s", line);
            } else if (ffound ==
                       NULL) {  // if match not found print error message
                printf("error: no match found!!\n");
            }
        }
    }

    return 0;
}