#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFERSIZE 512

char *token;
char *tokenFun[512];
char input[512];

char buffer[BUFFERSIZE];
char *filename;

int exitComp;
int cdComp;
int waitComp;
int pwdComp;
int i = 0;


int main()
{   
    for(;;){
        i = 0;
        printf("mysh> ");
        fgets(buffer, BUFFERSIZE, stdin);
        token = strtok(&buffer[0], " ");
        tokenFun[0] = token;
        i++;    
        char *filename = tokenFun[0];
        int length = strlen(filename);

        while(token != NULL){
            token = strtok(NULL, " ");
            tokenFun[i] = token;
            i++;
        }        
        
        if(strcmp("\n", tokenFun[0])==0)
        {
            continue;
        }
        else
        {
            tokenFun[i - 2] = strtok(tokenFun[i - 2], "\n"); 
        }

        if(strcmp("exit", tokenFun[0])==0)
        {
            printf("Exit\n");
            exit(0);
        }
        else if(strcmp("batch", tokenFun[0])==0)
        {
            for(;;)
            {
                i = 0;
                printf("> ");
                fgets(buffer, BUFFERSIZE, stdin);
                token = strtok(&buffer[0], " ");
                tokenFun[0] = token;
                if(strcmp("exit\n", tokenFun[0])==0)
                {
                    break; 
                }
                else if(strcmp("\n", tokenFun[0])==0)
                {
                    break; 
                }

                while(token != NULL){
                    token = strtok(NULL, " ");
                }
                if(strcmp("\n", tokenFun[0])==0)
                {
                    continue;
                }

                else
                {
                    tokenFun[i - 2] = strtok(tokenFun[i - 2], "\n"); 
                }
                i++;
            } 
        }
        else if(strcmp("cd", tokenFun[0])==0)
        {
            if(tokenFun[1] == NULL){
                chdir(getenv("HOME"));
            }
            else{
                chdir(tokenFun[1]);
            }
        }
        else if(strcmp("ls", tokenFun[0])==0 || strstr(">",tokenFun[0])==0)
        {
            int pid = fork();
            if(pid == 0)
            {
                execvp(tokenFun[0], tokenFun);
            }
        }
        else if(strcmp("wait", tokenFun[0])==0)
        {
            printf("Run wait!\n");
        }
        else if(strcmp("pwd", tokenFun[0])==0)
        {     
            if (tokenFun[1] == NULL)
            {
                char current[1024];
                getcwd(current, sizeof(current));
                printf("mysh> %s\n", current);
            }

        }
         // && (strcmp(filename[length - 1], "p")) == 0 && (strcmp(filename[length], "y")) == 0)
        else if(strcmp(".py", &filename[length-4]) == 0 || tokenFun[1] != 0)
        {    
            // printf("%s\n", &filename[length-2]);
            int pid2 = fork();
            if(pid2 == 0)
            {
                int j;
                for(j = i; j >=0; j--){
                    tokenFun[j+1]=tokenFun[j];
                }
                tokenFun[0]="/usr/bin/python";
                execvp(tokenFun[0],tokenFun);
            }
        }
        else
        {
            printf("An error has occurred\n");
        }
        
        i = 0;    
    }
    return 0;
}




