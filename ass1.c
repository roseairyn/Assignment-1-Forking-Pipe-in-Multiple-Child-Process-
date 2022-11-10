#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

#define ID_LENGTH 4

void getID(char userID[ID_LENGTH + 1]){
    srand(getpid() + getppid());
    
    userID[0] = 49 + rand() % 7;
    
    for(int x = 1; x < ID_LENGTH; x++){
        userID[x] = 48 + rand() % 7;
    }
    
    userID[ID_LENGTH] = '\0';
}

int main(void){

        int pipefds[2];
        char userID[ID_LENGTH + 1];
        char ID_buffering[ID_LENGTH + 1];
        
        char username[50];
        char s[50];
        
        void(sigint_handler(int sig));
        
        if(signal(SIGINT, sigint_handler) == SIG_ERR){
            perror("signal");
            exit(1);
        }
        
        pipe(pipefds);
        pid_t pid = fork();
        
        if(pid > 0){    //This is parent process
            wait(NULL);
            
            close(pipefds[1]);
            read(pipefds[0], ID_buffering, ID_LENGTH + 1);
            close(pipefds[0]);
            printf("User ID generated:\n%s", ID_buffering);
        }
        
        if(pid == 0){   //This is child process
            getID(userID);
            close(pipefds[0]);
            write(pipefds[1], userID, ID_LENGTH + 1);
            
            printf("\n\nPlease enter your username:\n");
            scanf("%s", username);
            
            printf("\nUsername registered are: %s\n", username);
            
            exit(EXIT_SUCCESS);
        }
    
    return 0;
    return EXIT_SUCCESS;
}

void(sigint_handler(int sig)){
    printf("\nRegistration Ended!\n");
    exit(1);
}