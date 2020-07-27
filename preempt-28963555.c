
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 11
#include "process-visualiser.h"

//#include "create-data.h"


typedef enum
{
BLANK, READY, RUNNING, EXIT, DEADEND  // DEADEND AND BLANK for more proper
} process_state_t;

typedef struct {
    char processName[11];
    int entryTime;
    int serviceTime;
    int remaningTime;
    int turnAroundTime;
    int waitingTime;
    int index; // stores the proper index according to the given file
    int sort_index;
    
    process_state_t state;
    
} proc_data_t;
int sort(proc_data_t a[], int counter);
int process_the_file(int infile);
int storing_the_data_in_struct(int infile, int file_pointer, int end_point, int process, int count);
int roundRobin(int number_of_process, proc_data_t array[]);
proc_data_t process_array[10];

int fcfs(int number_of_process, proc_data_t array[]);

int main(int argc, char *argv[]){
     int infile;
     char *fileread_error = "Error in opening the file.\n";
     
     if(argc == 1){
             if ((infile = open("process-data.txt", O_RDONLY)) < 0 ){
                                write(1, fileread_error, strlen(fileread_error));
                                close(infile);
                                exit(2);
                    }
     }
     else if(argc == 2){
             if ((infile = open(argv[1], O_RDONLY)) < 0 ){
                                write(1, fileread_error, strlen(fileread_error));
                                close(infile);
                                exit(2);
                    }
     
     }
     else{
        printf("Too many argumnet");
     
     }

      int number_of_process;
      number_of_process = process_the_file(infile);   // Number of the process is getting return one extra
      //fcfs(number_of_process, process_array);
      roundRobin(number_of_process, process_array);
      close(infile);
      exit(0);



}
// Queue function implementation 

proc_data_t queue[MAX];
int front = 0;
int rear = -1;
int itemCount = 0;
// top value in the queue
proc_data_t peek() {
   return queue[front];
}
// checking for the empty 
bool isEmpty() {
   return itemCount == 0;
}
// checking for the full of the queue
bool isFull() {
   return itemCount == MAX;
}
// checking the soze of the queue
int size() {
   return itemCount;
}  
// pushing the value in the queue
void push(proc_data_t data) {

   if(!isFull()) {
	
      if(rear == MAX-1) {
         rear = -1;            
      }       

      queue[++rear] = data;
      itemCount++;
   }
}
// removing the last value from the queue
proc_data_t pop() {
   proc_data_t data = queue[front++];
	
   if(front == MAX) {
      front = 0;
   }
	
   itemCount--;
   return data;  
}

// Round Robin Implementaion 

int roundRobin(int number_of_process, proc_data_t array[]){
     
    if (sizeof(proc_data_t) == 0)
    {
        return 0;
    }     
   char *colour1 = "white";
   char *colour2 ="blue";
   char okay[100]= "That's alright";
   int totalTime = 0;
   proc_data_t current_process;
   // printf("%s</n>", okay);
    
   initInterface(colour1, colour2);   // intializing the Interface for the display
   // Appending the row as given order in the file of the process name
   for(int i = 0; i < number_of_process-1; i++){
       appendRow(process_array[i].processName);
    
    }
 
   // General Sorting Funciton to sort it according to there entry time 
   sort(array, number_of_process-1);
   // calculating the totaltime and storing the remaining time in the process
   for(int i=0 ; i< number_of_process-1; i++){
        totalTime = totalTime + array[i].serviceTime;
        array[i].remaningTime = array[i].serviceTime;
        array[i].state = BLANK;
        array[i].sort_index = i;
        //array[i].finishTime = 0;
   
   }
   // intial process should be in ready state and printing for the arrival
   array[0].state = READY;
   printf("  %s entered the system at %d</n>",array[0].processName, array[0].entryTime);
   
  // first item in the queue state
   push(array[0]);
   // updated one
   appendBlank(array[0].index,array[0].entryTime); 
   // time starts at zero
   // updated one 
   int time = array[0].entryTime;
   // time_bar for the display
   int quantum = 2;
   int count = 0;
   while(totalTime != 0){
        // Checking for the size of the queue and for the newly entered for the quantum count 
        if(size() > 0 && count == 0){
             current_process = pop();
             current_process.state = RUNNING;
             if (count == 0){
                 printf("  %s is in running state (for the given quantun)</n>",current_process.processName);
             }
        } 
        else{   
                current_process.state = DEADEND;
               
        }
       
        
       // printf(" %d</n>", totalTime);
       // printf("total Time: %d</n>", totalTime);
       // Putting the current process into the Running state
        if (current_process.remaningTime == 1){
                // totalTime deduction from the current Time
                totalTime = totalTime - current_process.remaningTime;
               // time_bar = current_process.remaningTime;
                appendBar(current_process.index,current_process.remaningTime, colour2, current_process.processName, 0);
                current_process.remaningTime = 0;
                current_process.turnAroundTime = array[current_process.sort_index].waitingTime + current_process.serviceTime; 
                
                // updating the state of the process into the EXIT status
                current_process.state = EXIT;
               // printf("process_EXIT: %s Process State: %d</n>", current_process.processName,current_process.state);
                //current_process.finishTime = time;
                  //printf("waitingTime in the exit state: %d</n>",   array[current_process.sort_index].waitingTime);
                  printf("Process Name: %s Completed. Turnaround time: %d seconds  Total wait time: %d seconds </n>", current_process.processName, current_process.turnAroundTime, array[current_process.sort_index].waitingTime);
                array[current_process.sort_index] = current_process;
              
                // making the quatum count equals to zero
                count = 0;
              
               // slice = true;
                
        }
        // Running status for the process
        else if(current_process.remaningTime > 1){
             appendBar(current_process.index, 1, colour2, current_process.processName, 0);
             current_process.state = RUNNING;
             current_process.remaningTime = current_process.remaningTime - 1;
            // printf("Process Name: %s in the runnnig state</n>", current_process.processName);
             // total time deduction by the 1 secs
             totalTime = totalTime - 1;
             //time_bar = 1;
               count++;
             array[current_process.sort_index] = current_process;
           
          
        }
      
        // Checking for the next process, to update the status
        for(int k = 0; k < number_of_process-1; k++){
                      // Checking the entry time for the rest left process
                  if(array[k].entryTime ==  time && array[k].state == BLANK){ 
                             printf("%s entered the system in %d seconds</n>", array[k].processName, array[k].entryTime);
                             // Appending the blank till the EntryTime
                             appendBlank(array[k].index,time);  // Here index refers th
                             // Updating the status of the Proacess with the READY STATUS
                             array[k].state = READY;
                             // if next queue is nothing so next one should be first entry one
                             
                             push(array[k]);
                  }
                         
                    
                  if (array[k].state == READY && current_process.state != DEADEND){
                       // If the left process is in the READY status then another dotted bar should be displayed on the display according to the row
                       appendBar(array[k].index,1, colour2, array[k].processName, 1);
                       // Adding the waiting time for that particular process
                     
                       
                     
                  }
                   
                      
          }
         // printf("size(): %d</n>", size());
         // Updating the waiting time in the for queued item by one 
          for(int l = front; l < size()+front; l++){
                // if it is in the system then add in the queue only
                
               queue[l].waitingTime++;
                // update it in as well as in the array
              array[queue[l].sort_index].waitingTime++;
               // printf("processName: %s waitingTime: %d</n>", array[queue[l].sort_index].processName,  array[queue[l].sort_index].waitingTime);
              
          }
              
            
          // checking for the running state and time quatum to select another process
          if (current_process.state == RUNNING && count == quantum){
                   //printf("ready state to check the queue push process: %s Process State: %d</n>", current_process.processName,current_process.state);
              // putting back into the READY state
              current_process.state = READY;
             
             // updating the array with the current_process changes 
              array[current_process.sort_index] = current_process;
             // pushing back into the queue
              push(current_process);
             // array[current_process.sort_index].waitingTime++;
              // quantum initialzing becomes zero
              count = 0;
           }
           
          // time counter increases
          time ++;
          // sleep for a second
          sleep(1);
    
   }
   
   // display feature to wait
    waitExit();
    

}
int process_the_file(int infile){
            int i, file_pointer_start, end_point, read_bytes, file_pointer_end; ;
            char *fileread_error = "Error in opening the file.\n";
            char *line_buf = NULL;
            size_t line_buf_size = 0;
            int line_count = 0;
            ssize_t line_size;
            
                    
              char temp[1024];
              int number_of_lines =0 ;  // Setting default number of line read if there is no input for -n
              end_point = lseek(infile, 0, SEEK_END);
             
              //file_pointer_start = lseek(infile,  0 , SEEK_END);
             
   
             
              int count =0;   // Dummy value to count the shift
              int new_process =0; // Counting the new_process
              i =1;     // starting with the zero
              file_pointer_start=lseek(infile, 0 , SEEK_SET);  // Initial pointer should be at zero
                  //loop till the end of the file
                  while(end_point - i >= 0){
                      
                       file_pointer_end = lseek(infile,  (long)i , SEEK_SET);
                       // reading each character from the file      
                       read_bytes = read(infile, &temp, 1);
                       // Checking for the space
                       if(*temp == ' '){
                           // storing the data
                           storing_the_data_in_struct(infile, file_pointer_start, file_pointer_end, new_process, count);
                           //storing the last " " pointer in the file_pointer_start to read next time
                           file_pointer_start = file_pointer_end;
                           count++;
                           
                       }
                       // getting the element from the temp using the pointer "\n"
                       if(*temp == '\n'){
                         // printf("%c", *temp);
                           // storing the data 
                           storing_the_data_in_struct(infile,file_pointer_start, file_pointer_end, new_process, count);
                           //storing the last \n pointer in the file_pointer_start to read next time
                           file_pointer_start = file_pointer_end;
                           new_process++;
                           // count 0 for the new process
                           count = 0;
                            //printf("%s", temp);
                        }
                       
                        i++ ;
               }   // The last data before the end of the file because there is no \n hence need to hard code for it
                   count = 2;
                   storing_the_data_in_struct(infile,file_pointer_start, file_pointer_end, new_process, count);
                   file_pointer_start = file_pointer_end;
               
               
            //  printf("%d", new_process);
              return new_process;
              
          }
int storing_the_data_in_struct(int infile, int file_pointer, int end_point, int process, int count){
           char temp[12];
           int number, k;
           int shift_value = 1024;         // by default 1024 is good choice to take value at a time
           char c = '\0';
           // Start reading the file from the last break dude to " " or \n
           lseek(infile,  file_pointer , SEEK_SET);   
           k = end_point- file_pointer;
         
           number = read(infile, &temp, k);   // reading 1024 bytes or minimum
         // printf("%d", process);
         
          // string termiantion identification 
           temp[end_point-file_pointer] = '\0';
           // If the count is zero hence it is before the first space i.e. processName
           if (count == 0){
                 strcpy(process_array[process].processName, temp);
                 process_array[process].index = process;
               //  printf("%s ", process_array[process].processName);
                
           
           }
           // If the count is one hence it is before the second space i.e. process Entry Time
          else if(count == 1){
               //    strcpy(process_array[process].entryTime, temp);
                  process_array[process].entryTime = atoi(temp);
                  //printf("%d ", process_array[process].entryTime);
           }
           // If the count is two hence it is before the \n i.e. process service Time
           else if(count == 2){
              //    strcpy(process_array[process].serviceTime, temp);
                  process_array[process].serviceTime = atoi(temp);
                 // printf("%d\n", process_array[process].serviceTime);
          }
          // Just random thing
           else{
              printf("READING FILE DOSEN'T WORK");
           }
           //write(1, &temp, number);
           // Putting the last thing 
           // reset the lseek to read further details
           lseek(infile,  end_point , SEEK_SET);   
           
       
}


int sort(proc_data_t a[], int counter){
        int i,j;
        int n= counter;
        
        
        for (int i = 0; i < n; i++)                     //Loop for ascending ordering
	    {
		    for (int j = 0; j < n; j++)             //Loop for comparing other values
		    {
			    if (a[j].entryTime > a[i].entryTime)                //Comparing other array elements
			    {
				    proc_data_t tmp = a[i];         //Using temporary variable for storing last value
				    a[i] = a[j];            //replacing value
				    a[j] = tmp;             //storing last value
			    }  
		    }
	    }
}


