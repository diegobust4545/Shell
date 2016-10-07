#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFERSIZE 512

int i = 0;
int boo = 0;
char buffer[BUFFERSIZE];
char *filename;
char *token;
char *tokenFun[512];

void error_message(){
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
}

int main(int argc, char **argv)
{ 
    FILE *file = stdin;  
    if(argv[1]){
        boo = 1;
        file = fopen(argv[1],"r");
    }
    for(;;){
        i = 0;
        if(!boo)
        {  
            printf("mysh> ");
        }


        // if(strstr(buffer, ">")){

        //     tokenFun[0] = strtok(buffer, ">");
        //     tokenFun[1] = strtok(NULL, " ");
        //     if(!strstr(tokenFun[1], "\n") || strstr(tokenFun[1], ">"))
        //     {
        //         error_message();
        //         continue;
        //     }
        //     tokenFun[0] = strtok(buffer, " ");
        //     tokenFun[1] = strtok(NULL, "\n");
        //     if(fork() == 0){
        //         file = open(tokenFun[1], O_WRONLY| O_CREAT, S_IRUSR |  S_IWUSR|);
        //         (file, STDOUT_FILENO);
        //         close(file);
        //         tokenFun[1] = NULL;
        //         execvp(tokenFun[0], token); 
        //     }
            

        // }

        fgets(buffer, BUFFERSIZE, file);
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
        if(strcmp("exit", tokenFun[0]) == 0)
        {
            if(boo){
                fclose(file);
            }
            exit(0);
        }
         else if(strcmp("ls", tokenFun[0])==0)
        {
            int pid = fork();
            if(pid == 0)
            {
                execvp(tokenFun[0], tokenFun);
                // printf("\n");
            }
        }
        else if(strcmp("wait", tokenFun[0])==0)
        {
            printf("wait\n");
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
        else if(strcmp("cd", tokenFun[0])==0)
        {
            if(tokenFun[1] == NULL){
                chdir(getenv("HOME"));
            }
            else{
                chdir(tokenFun[1]);
            }
        }
        else if(strcmp(".py", &filename[length-4]) == 0 || tokenFun[1] != 0)
        {    
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
            error_message();
        }
    }
    return 0;
}
