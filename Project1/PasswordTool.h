#include <stdio.h>
#include <string.h>
#include <conio.h>
void getPassword(char* storePw){
    char c = '\0';
    char* pc = storePw; 
    int pwlen = 0; 
    while (1){
        c = getch();
        if (c == '\r') {
            printf("\n");
            break;
        }
        if (c == '\b') {
            if (pwlen > 0){
                pwlen--;
                pc--;
                printf("\b \b");
                *pc = '\0';
                continue;
            }
        } else if (pwlen >= 0 ){
            *pc = c;
            pc++;
            pwlen++;
            putchar('*');
        }
    }
}