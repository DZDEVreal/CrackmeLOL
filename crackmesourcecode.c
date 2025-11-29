#include <stdlib.h>
#include <stdio.h>

typedef enum Returns{
    END_OF_SCRIPT =0,
    ERROR_INVALID = 1,
    WIN = 2,
}Returns_t;
typedef struct User {
    int code;
} User_t;
int umasked() {
    volatile int p1 = 0xDEAD0000 ^ 0x7530ABCD;  
    volatile int p2 = 0xAA5500FF ^ 0xFFAABB55;   
    volatile int k1 = 0xABCDEFFF ^ 0xFF00B555;  
    int x = (p1 ^ (p2 >> 3)) + (k1 << 1);
    x ^= (p2 << 2) ^ (p1 >> 5);
    x = (x ^ 0xCAFEBABE) + (p1 & 0x00FF00FF);
    x ^= (k1 | 0x12345678);
    int real = ((p1 | p2) ^ k1);
    return real ^ (x & 0);   
}
int main(void){
    int i;
    User_t admin;
    admin.code = umasked();
    printf("Enter\n");
    printf("Code: ");
    if (scanf("%d" ,&i) != 1){
        printf("Invalid Operator!\n");
        return ERROR_INVALID;
    }
    else if (i == admin.code){
        printf("WELCOME U GOT IT\n");
        return WIN;
    }
    printf("Hi User!\n");
    printf("srry noob :)\n");
    return END_OF_SCRIPT;
}
