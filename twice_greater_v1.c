#include <string.h>
#include <stdio.h>

//char [ ]
char *twice_greater_v1(char *s1, char *s2)
{
    if (strcmp(s1, s2) >0) {
        strcpy(s2, strcat(s1, s1));
        return s2;
    } else  {
        strcpy(s1, strcat(s2, s2));
        return s1;
    }
}

void twice_greater_demo_v1()
{
    char firstname[5] = "Dave";
    int num_cows = 4;
    char lastname[10] = "Wonnacott";

    printf( "Name: %s %s\n", firstname, lastname );
    printf( "How many cows? %d\n", num_cows );

    char *g2name = twice_greater_v1(firstname, lastname);  // twice_greater(&firstname[0], &lastname[0])
    printf( "g2name = %s\n", g2name);
    printf( "Name: %s %s\n", firstname, lastname );
    printf( "How many cows? %d\n", num_cows );
    printf( "OK, tell me where you all live: %p %p %p\n", &firstname, &num_cows, &lastname);
    printf( "OK, start and end of arrays: %p to %p, and %p to %p\n",
            &firstname[0], &firstname[4], &lastname[0], &lastname[9]);

    printf( "all done\n");
}
