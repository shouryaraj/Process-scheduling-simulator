/*
PROCESS VISUALISER API FOR FIT2100 ASSIGNMENT 2 (Scheduling simulator)
Written by Daniel Kos, Sep 2019.

Refer to process-visualiser.h for instructions.

You are not required to understand the contents of this file to complete
the assignment.
*/

#include <stdio.h>

void initInterface(const char* backgroundColor, const char* foregroundColor) {

    //prevent user exiting until waitExit() is called.
    printf("<program.onExit.push <null>>\n");
    printf("<program.margin = 0> \n");
    printf("<program.backgroundColor={%s}>\n", backgroundColor);
    printf("<program.color={%s}>\n", foregroundColor);

    printf(
        "<ganttChart:box visible=false inline=false width=100,{%%} height=50,{%%} scroll=true { \n"
        "  <caption:span marginLeft=10,{em}italic=true {...}></p> \n"  //provide a space for mouse-over caption to be displayed.
	    "  <inner:box width=4000,{px} border=0 {\n" //make the box much wider than needed
        "  }>\n"
        "}>\n"
    );

    //print a visual time scale along the top of the chart...
    printf("<ganttChart.inner.push {</n><scale:box border=0 borderBottom=1 height=30 align={right},{bottom} {\n");
    printf("  <box border=0 width=10,{em} spacing=0 margin=0 borderRight=2 {Time}>");
    for(int time=1; time<=90; time++)
        printf("<box size=10 border=0 borderRight=1 align={right} width=30 {%d}>", time);
    printf("<box size=14 border=0 width=200 align={right} {time (seconds) </#x2192>}>"); //label the axis.
    printf("}>}>\n");

    printf("<ganttChart.visible=true>\n"); //show the chart area ready for rows and bars.
    printf("<content:box inline=false scroll=true width=100,{%%} top=50,{%%} height=50,{%%} {");
    //all further content printed by the user will be appended here.
}


int appendRow(const char* processName) {
    static int numRows = 0;

    printf("<ganttChart.inner.push {</n><row%d:box border=0 {", numRows);
    printf("  <box border=0 width=10,{em} height=30 align={right},{bottom} spacing=0 margin=0 borderRight=2 {%s}>", processName);
    printf("}>}>\n");

    return numRows++; //return the row index and increment for next time.
}


void appendBar(int rowIndex, int length, const char* color, const char* caption, int dotted) {

    printf("<ganttChart.inner.row%d.push <box color={%s} ", rowIndex, color);
    printf("onMouseIn=<caption.clear>,<caption.push {%s}> ", caption);
    if(dotted) printf("borderStyle={dotted} ");
    else printf("backgroundColor={%s} ", color);
    printf("height=30 width=%d {}", length*30);
    printf(">>\n");
}

void appendBlank(int rowIndex, int length) {

    printf("<ganttChart.inner.row%d.push <box ", rowIndex);
    printf("border=0 height=30 width=%d {}", length*30);
    printf(">>\n");

}




void waitExit() {
//This function places an exit button on the screen and allows the user to exit the program.
//It will not return until the user has clicked the exit (or window X) button.
//After return, the program is free to handle the exit condition (e.g. by
//exiting the program.

    

    printf("<program.onExit.clear><program.onExit.push <put {X}>>\n");
    printf("<xButton:button {Exit} onClick=program.onExit>\n");

    getchar(); //block until "X" input is received on stdin.

    //prevent the user repeating the operation 
    printf("<program.onExit.clear><program.onExit.push <null>>\n");
    printf("<xButton.delete>\n");
    
}
