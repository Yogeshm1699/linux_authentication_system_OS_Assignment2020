#define _XOPEN_SOURCE

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>

char usrnm[20];
char usrpwd[20];
char logusrnm[20];
char logpwd[20];

int main(){

    printf("%sRegister, enter username and password\n");
    scanf("%s",usrnm);
    scanf("%s",usrpwd);

    printf("%s Now Login\n");
    scanf("%s",logusrnm);
    scanf("%s",logpwd);

    if(strcmp(usrnm,logusrnm)!=0){
        printf("%sUsername Authentication Failed\n");

    }else if(strcmp(usrnm,logusrnm)==0){

        if(strcmp(usrpwd,logpwd)!=0){
            printf("%s Password Authentication Failed\n");

        }else if(strcmp(usrpwd,logpwd)==0){
            printf("%s Authentication Passed \n");

        }

    }

return 0;

}