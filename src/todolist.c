#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define myFile "tasks.txt"

int taskCount = 0;

void RemoveTask();
void AddTask();
void ViewAll();
void ReadTasks();
void MarkComplete();
void SaveOnExit();
void FreeMemory();
FILE* openFile(const char* MODE);

int main(){
    ReadTasks();
    while(1){
        
        char choice = 0;

        printf("Choose an option:\n1.View all tasks\n2.Add task\n3.Remove task\n4.Mark task as complete\n5.Exit program\n");
        scanf(" %c", &choice);
        getchar();

        switch (choice)
        {
        case '1': ViewAll(); break;
            
        case '2': AddTask();break;
            
        case '3':RemoveTask(); break;
            
            
        case '4':MarkComplete(); break;
        case '5':SaveOnExit(); FreeMemory();exit(0); 
        default:
            printf("\nNot a valid option!\n\n");
            break;
        }
        
        
    }
    


}

typedef struct{
    char description[101];
    char completed;


} Task;


Task *tasks = NULL;

FILE* openFile(const char* MODE){
    FILE *fptr;
    fptr = fopen(myFile, MODE);
    if (fptr == NULL) {
        printf("Error opening file.\n");
        exit(1); 
    }
    return fptr;
    
}



void AddTask(){
    Task task;
    printf("Enter a description for the task:");

    fgets(task.description, 101, stdin);
    
    if(task.description[0] == '\n'){
        printf("Error, empty description\n");
    }
        
    

    task.completed = 0;

    FILE* fptr = openFile("a+");
    size_t len = strlen(task.description);
    if(len != 0 && task.description[len-1] == '\n'){
        task.description[len-1] = '\0';
    }
    fprintf(fptr,"%s;%d\n",task.description, task.completed);
    fclose(fptr);
    printf("Succesfully added task!\n");
    ReadTasks();

    
    
}

void ViewAll(){
    if(taskCount == 0){
        printf("\nThere are no tasks\n\n");
        return;
    }
    for(int i = 0; i < taskCount; i++){
        printf("\n%d: %s->%s\n", i+1, tasks[i].description, tasks[i].completed?"Completed":"Incomplete");
    }
    
    printf("\n");

}

void RemoveTask(){
    printf("Enter which task you want to be deleted: ");
    for(int i = 0; i < taskCount; i++){
        printf("\n%d: %s->%s\n", i+1, tasks[i].description, tasks[i].completed?"Completed":"Incomplete");
    }
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > taskCount) {
        printf("Invalid task number.\n");
        return;
    }
    for (int i = choice - 1; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    FILE* fptr = openFile("w");
    for (int i = 0; i < taskCount; i++) {
        fprintf(fptr, "%s;%d\n", tasks[i].description, tasks[i].completed);
    }
    fclose(fptr);
    printf("Successfully removed task!");
    ReadTasks();
    taskCount--;
    


}

void ReadTasks(){
    FILE *fptr = openFile("r");
    char line[105];
    taskCount = 0;
    tasks = NULL;

    while (fgets(line, sizeof(line), fptr))
    {
        Task newTask = {0};

        char *token = strtok(line, ";");
        if(token){
            strncpy(newTask.description, token, 101);
        }

        token = strtok(NULL, ";");
        if(token){
            newTask.completed = atoi(token);
        }
        
        Task *temp = realloc(tasks, (taskCount + 1) * sizeof(Task));
        if (temp == NULL) {
            printf("Memory allocation failed!\n");
            return;  
        }
        
        tasks = temp;
        tasks[taskCount] = newTask;
        taskCount++;
    
    }
    fclose(fptr);
    

}

void MarkComplete(){
    printf("Which task is complete: \n");
    int choice = 0;

    for(int i = 0; i < taskCount; i++){
        printf("\n%d: %s->%s\n", i+1, tasks[i].description,tasks[i].completed?"Completed":"Incomplete");
    }
    scanf(" %d", &choice);
    
    if(choice >= 1 || choice <= taskCount){
        if(tasks[choice-1].completed != 1){
            tasks[choice - 1].completed = 1;
            printf("Successfully marked the task as complete!\n\n");
            return;
        }
        printf("The task is already completed!\n");
        return;
    }
    printf("invalid number of task!\n");
    return;
        
}

void SaveOnExit(){
    FILE* fptr = openFile("w");
    for (int i = 0; i < taskCount; i++) {
        fprintf(fptr, "%s;%d\n", tasks[i].description, tasks[i].completed);
    }
    fclose(fptr);
}
void FreeMemory(){
    free(tasks);

}


