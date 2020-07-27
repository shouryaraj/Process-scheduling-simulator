/*
PROCESS VISUALISER API FOR FIT2100 ASSIGNMENT 2 (Scheduling simulator)
Written by Daniel Kos, Sep 2019.


This file provides access to 5 functions used to plot visual information
on the screen for this assignment.

* When running your program, place 'iol --' in front of the command, to
  run your program in the ioL markup console environment.


TO INCLUDE THESE FUNCTIONS IN YOUR PROGRAM:
* Place this file and process-visualiser.c in the same directory as your assignment.
* Place the following line at the top of any source file that requires these
  functions: (This includes the function header information in your program)
       #include "process-visualiser.h
* When COMPILING your program: add ' process-visualiser.c' to the end of the
  gcc command used to compile your program. (This links the function implementations
  with your compiled program.)
       e.g. gcc your-program.c -o your-program process-visualiser.c
       
  
  DO NOT RENAME THESE FILES IN YOUR SUBMISSION, OR COPY THE FUNCTIONS INTO
  YOU CODE DIRECTLY.
  
  You may modify the functions in process-visualiser.c if you wish, however
  you are not required to do so.

*/

#ifndef PROCESS_VISUALISER_H_ //guard against multiple #includes.
#define PROCESS_VISUALISER_H_

void initInterface(const char* backgroundColor, const char* foregroundColor);
/*
This function must be called first (prior to producing any output) to set up the user interface

RETURN VALUE: none.

ARGUMENTS:
* backgroundColor: a string defining the background color for the window.
* foregroundColor: a string defining the foreground color for the window.

NOTE: the following color values are accepted:
"black", "silver", "gray", "white", "maroon", "red", "purple", "fuchsia", "green",
"lime", "olive", "yellow", "navy", "blue", "teal", "aqua".
*/



int appendRow(const char* processName);
/*
This function adds a new process row to the chart displayed on the screen

RETURN VALUE: the row index of the new row in the chart. Use this value with
the appendBar and appendBlank functions when you want to specify which process
to append a bar or a blank space to.

ARGUMENTS:
* processName: a string used to label the row in the chart as displayed on screen.
               (This should be the name of the process being added to the system.)
*/



void appendBar(int rowIndex, int length, const char* color, const char* caption, int dotted);
/*
This function draws a bar segment to the end of the specified row.
This is useful to represent that the process is in a certain state for a certain
length of time.

RETURN VALUE: none

ARGUMENTS:
* rowIndex: the row index of the row where you want to append the bar segment.
* length: the length of the bar (measured in seconds) -- represents how much time
          the process is in a certain state
* color: a string defining the color to use for the bar segment (see below).
* caption: a string to be displayed when the user moves the mouse over the bar.
* dotted: Either 1 or 0. If 1, a dotted bar will be drawn (process in ready state/waiting).
          If 0, a solid bar will be drawn (process is running).

NOTE: the following color values are accepted:
"black", "silver", "gray", "white", "maroon", "red", "purple", "fuchsia", "green",
"lime", "olive", "yellow", "navy", "blue", "teal", "aqua".
*/



void appendBlank(int rowIndex, int length);
/*
This function adds a blank space to the end of the specified row.
This is useful to represent that a process has not arrived in the system yet. 
The next bar to be added to the row will be added after the end of the blank
space.

RETURN VALUE: none

ARGUMENTS:
* rowIndex: the row index of the row where you want to append the bar segment.
* length: the length of the bar (measured in seconds).
*/



void waitExit();
/*
This function allows the user to close the window once all the output has been printed.
It will not return *until* the user clicks the 'close' or 'exit' button,
so it allows you to keep the window on the screen until the user is ready to exit.

RETURN VALUE: none (function returns when user has clicked the close button)

ARGUMENTS: none.

NOTE: This function does not close the window. The window will close when the program exits.
*/

//end of header file.
#endif
