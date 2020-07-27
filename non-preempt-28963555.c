
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "process-visualiser.h"

//#include "create-data.h"


typedef enum
{
Nothing, READY, RUNNING, EXIT
} process_state_t;

typedef struct {
    char processName[11];
    int entryTime;
    int serviceTime;
    int remaningTime;
    int turnAroundTime;
    int waitingTime;
    int index; // stores the proper index according to the given file
    process_state_t state;
    
} proc_data_t;
proc_data_t process_array[10];


int sort(proc_data_t a[], int counter);
int fcfs(int number_of_process, proc_data_t array[]);
int process_the_file(int infile);
int storing_the_data_in_struct(int infile, int file_pointer, int end_point, int process, int count);

int main(int argc, char *argv[]){
     int infile;
     int number_of_process;
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
        printf("Too many argumnets");
     
     }

     
      number_of_process = process_the_file(infile);   // Number of the process is getting return one extra
      //fcfs(number_of_process, process_array);umber of the process is getting return one extra
    
      fcfs(number_of_process, process_array);
      close(infile);
      exit(0);

}

int fcfs(int number_of_process, proc_data_t array[]){
     
    
    if (sizeof(proc_data_t) == 0)
    {
        return 0;
    }
    
   char *colour1 = "white";
   char *colour2 ="blue";
   char okay[100]= "That's alright";
    
   initInterface(colour1, colour2);   // intializing the Interface for the display
   // Appending the row as given order in the file of the process name
   for(int i = 0; i < number_of_process-1; i++){
       appendRow(process_array[i].processName);
    
    }
 
   // General Sorting Funciton to sort it according to there entry time 
   sort(array, number_of_process-1);
     int totalTime = 0;
     for(int i=0 ; i< number_of_process-1; i++){
        totalTime = totalTime + array[i].serviceTime;
        array[i].remaningTime = array[i].serviceTime;
 
   } 
   
   
    
    int time =  array[0].entryTime; // Time Begins from 1 secs otherwise there are chances for the overlap
    char* caption = "Process";
    appendBlank(array[0].index,array[0].entryTime);
    array[0].state =READY;
    // Each process 
    // Printing the details for the first Process
    int counter = 0;
    int i;
    printf("%s entered the system in %d seconds</n>", array[0].processName, array[0].entryTime);
    // loop Begins to execute the each process
    while(totalTime> 0){
        // Checking for intial time for the entry of the first process
                         if(array[counter].state != READY){
                               appendBlank(array[counter].index,array[counter].entryTime);
                         }
                   
                          i = counter;
                          
                             array[i].state = RUNNING;
                             for (int j=0; j < array[i].serviceTime; j++){
                             // Checking for any new process time 
                                    if(array[i].state == RUNNING){
                                        appendBar(array[i].index,1, colour2, array[i].processName, 0);
                                    }
                                    // Checking for the next process, to update the status
                                  for(int k = i+1; k < number_of_process-1; k++){
                                  // Checking the entry time for the rest left process
                                         
                                          if(array[k].entryTime ==  time){ 
                                                 
                                                 printf("%s entered the system in %d seconds</n>", array[k].processName, array[k].entryTime);
                                                 //printf("Process entry Time: %d</t>", array[k].entryTime);
                                                 // Appending the blank till the EntryTime
                                                 appendBlank(array[k].index,time);  // Here index refers th
                                                 // Updating the status of the Process with the READY STATUS
                                                 array[k].state = READY;
                                        
                                           }
                                          if (array[k].state == READY){
                                              // If the left process is in the READY status then another dotted bar should be displayed on the display according to the row
                                              appendBar(array[k].index,1, colour2, array[k].processName, 1);
                                              // Adding the waiting time for that particular process
                                              array[k].waitingTime++;
                                   
                                           }
                                           
                                    }
                                    // Time counter
                                    time++;
                                    sleep(1);
                                    
                                    
                             }
                          
                             
                             
                              // Updating the finished status for the process by EXIT enum
                              array[i].state = EXIT;
                              // Calculating the total time for process
                              process_array[i].turnAroundTime = process_array[i].waitingTime + process_array[i].serviceTime; 
                              // Printing out all the end of the process with the valid details
                              printf("%s Completed.  TurnAroundTime: %d Waiting Time: %d</n>", process_array[i].processName, process_array[i].turnAroundTime,   process_array[i].waitingTime);
                              totalTime = totalTime - array[i].serviceTime;
                              counter ++;
                          
        }
      waitExit();


}


int process_the_file(int infile){
            int i, file_pointer_start, end_point, read_bytes, file_pointer_end; ;
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
