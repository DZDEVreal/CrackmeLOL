#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

typedef enum { END_OF_SCRIPT=0, ERROR_INVALID=1, WIN=2 } R;
typedef struct { int code; } U;

static int r(int v, int s){ s&=31; return (v<<s)|(v>>(32-s)); }

static int d(){
    FILE*f=fopen("/proc/self/status","r");
    if(!f)return 0;
    char b[256];
    while(fgets(b,256,f)){
        if(!strncmp(b,"TracerPid:",10)){
            int p=atoi(b+10);
            fclose(f);
            return p!=0;
        }
    }
    fclose(f);
    return 0;
}

int um(){
    volatile int q=(rand()^(time(NULL)&0xFFFF));
    volatile int s=(0xDEADBEEF^q)+(0x1337BEEF&~q);
    if(((s*s)%3)==((s%3)*(s%3))) s^=r(s^0xA5A5A5A5,(s&7));
    volatile int a=(0xABCDEF12^s)+r(0x12345678,s&7);
    volatile int b=(0xDEAD1234+(s>>3))^r(0xCAFEBABE,(s>>5)&7);
    int v=a;
    for(int i=0;i<7;i++){
        v^=r(b,i);
        v+=((i*0x1337)^(s>>(i&3)));
        v=r(v,(v^s)&7);
        v^=(a&b)^(0x55AA55AA+i);
        v+=((a>>((i+1)&3))^(b<<((i+2)&7)));
    }
    int k=(a^(b<<1))+(s>>2);
    k^=r(0xCAFEBABE^v,(s&15));
    int z=v^k^r(s,k&7);
    if(d()) z^=0xF0F0F0F0,z+=0x12345678;
    return z;
}

int main(){
    srand(time(NULL));
    U A;
    A.code=um();
    int x;
    printf("Enter\nCode: ");
    if(scanf("%d",&x)!=1) return ERROR_INVALID;
    if(x==A.code) return WIN;
    printf("Hi User!\nsrry noob :)\n");
    return END_OF_SCRIPT;
}
