
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>

char usrnm[20];
char usrpwd[20]; 
char salt[]="55";//for the moment beig the salt is hard coded

char buffer[100];//used for reading lines from the pwd file to be used in case 2 of the prog
char logusrnm[20];
char logpwd[20]; 
char storedsalt[10];
char storedencrpwd[20];

/*
struct user{
    char name[20];
    char pwd[50];
    char storedsalt[2];
};*/


int main(){

    
    int choice;
    printf("%sPlease choose one option : 1 for Register, 2 for Login, 0 for exit.\n");
    scanf("%d",&choice);
    switch (choice){

    case 1:
        // Registering new user and write to file.

         printf("%s Register by entering your User Name followed by your Password\n");
        scanf("%s",usrnm);
        scanf("%s",usrpwd);

        char *encrpwd = crypt(usrpwd,salt);

        //struct user line = {*usrnm,*encrpwd,*salt};


        int fd=open("pwdfile.txt",O_CREAT|O_WRONLY|O_APPEND,0777);

         // write(fd,&line,sizeof(struct user)); //I tried to use this but I found it better to add colons and use strtok

        write(fd,usrnm,strlen(usrnm));
        write(fd,":",1);
        write(fd,encrpwd,strlen(encrpwd));
        write(fd,":",1);
        write(fd,salt,strlen(salt));
        write(fd,":",1);
        write(fd,"\n",1);
        close(fd);

        
      break;

    case 2:
        // Login and read from file and strcmp usrname and pwd.

        
        printf("%s LOGIN by entering your User Name followed by your Password\n");
        scanf("%s",logusrnm);
        scanf("%s",logpwd);

        const char s[2] = ":";
        char *token;
        

        int fdread = open("/pwdfolder/pwdfile.txt",O_RDONLY);
    
        int r=read(fdread,buffer,100);

        while(r>0){
            
            token = strtok(buffer, s);//this takes the username

            if(strcmp(logusrnm,token)==0){ //compares the token(stored username) with the one just entereds

            //since the user exits we now take the next 2 tokens that is the stored encrypted and salt.
                token = strtok(NULL, s);
                strcpy(token,storedencrpwd);//taking the stored encypted passwored from the token into the array of char for comparisons
                token =strtok(NULL,s);
                strcpy(token,storedsalt);
                
            char *encrlogpwd = crypt(logpwd,storedsalt);//encrypting the password entered when login with the stored salt.
            
            if(strcmp(storedencrpwd,encrlogpwd)==0){
                printf("%s Authentication Passed \n");
                return 0;
            }

        }
    
        printf("%s  Authentication Failed\n");

        }

        printf("%s  Authentication Failed\n");//this is when we went through all the lines and the user is non existant! 
        close(fdread);

      break;


    case 0:
        // EXIT THE PROG
        return 0;

    default:
       printf("%sPlease choose valid option.\n");


    }

    return 0;

}