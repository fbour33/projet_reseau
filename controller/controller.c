#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "components/prompt/prompt.h"


pthread_t thread_prompt;

int main(){
    int prompt = pthread_create(&thread_prompt, NULL,main_prompt_menu, NULL);
    if(prompt !=0){
        printf("error creating thread for the prompt\n");
    }
    pthread_join(thread_prompt, NULL);
    return 1;
}