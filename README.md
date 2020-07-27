<h1 align="center" >Process-scheduling-simulator <h1>
<p>Created programs to simulate two diﬀerent scheduling algorithms i.e. First come, first served and Preemptive Round Robin scheduling<p>
<p>
<img src="resource/scheduler_pic.png" alt="Logo" align="center" width="600px">
</p>

	
	
## Instruction 

```
FCFS and ROUND_ROBIN user commands
Name
	non-preemtive-28963555 - graphic display the ROUND_ROBIN  scheduler work
        preemtive-28963555 -graphic display the FCFS scheduler work

SYNOPSIS
	./non-preemtive-28963555 [fileName]
	or
	./non-preemtive-28963555
        &
        ./preemtive-28963555 [fileName]
        or 
	./preemtive-28963555
Description
	Graphic display of the given process in the file accordinf to the choosen scheduler
     
        commands:
        ./non-preemtive-28963555 [fileName],  it reads the given fileName and display the graphic of the process execution using the 
                                              ROUND_ROBIN scheduler
	Limitaion:
			filename should be there is same directory
      
	./non-preemtive-28963555, it reads by default fileName "process-data.txt" and display the graphic of the process execution using the 
                                              ROUND_ROBIN scheduler
     
 	./preemtive-28963555 [fileName], it reads the given fileName and display the graphic of the process execution using the 
                                              FCFS scheduler
	Limitaion:
			filename should be there is same directory

	./preemtive-28963555, it reads by default fileName "process-data.txt" and display the graphic of the process execution using the 
                                              FCFS scheduler
Overall Limitation:
     filename should be there and Process time should be a natural number, process name should not more than 10 characters.
```
