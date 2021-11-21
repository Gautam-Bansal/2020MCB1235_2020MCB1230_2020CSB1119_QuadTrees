# 2020MCB1235_2020MCB1230_2020CSB1119_QuadTrees
CS-201 Project on QuadTrees
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Compiler Details :

The code is completely written in C language and compiled using the following gcc version.
gcc (tdm64-1) 9.2.0

However, pretty much any C compiler should run it.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How to give input :

On running the executable file the user will be asked to choose between 7 options shown on the screen and will have to enter the index of whatever option they want to choose.
For example, if they want to insert, enter 1. If they want to exit the program, enter 7 at the menu.

Whenever (on any option that needs co-ordinates) user needs to enter co-ordinates they need to do so in (x, y) format. 
For example, if user wants to insert a point with x-coordiante as 2.0 and y-coordinate as 3.0 then they need to enter (2.0, 3.0) after entering 1 from the options menu.
If they need to input charge q, just enter q.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What to expect from each option :

1. Insert option just inserts the charge at specified co-ordiante.
2. Search option tells the value of charge (if there is one) at the entered co-ordinate.
3. Nearest option outputs the co-ordinates of nearest charge to the entered co-ordinate.
4. Range Query prints out all the co-ordinates present in a rectangle with entered centre point and length, breadth.
5. Electric field options prints out the magnitude of electrostatic field and/or force at entered co-ordinate.
6. Display option prints out all the co-ordinates present in 2-D space / tree.
7. Quit option terminates the program.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Sample test case :

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
<a/>
Enter your choice:
1<br>
Enter coordinates of point:<br>
(0.1, 0.1)<br>
Enter charge of point:<br> 
2<br><br>

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
<a/>
Enter your choice:
1<br>
Enter coordinates of point:<br> 
(0.1, 0.1)<br>
Enter charge of point:<br> 
3<br>
Error! Could not insert because a charge is already present there.<br><br>

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
<a/>
Enter your choice:
1<br>
Enter coordinates of point:<br> 
(0.2, 0.2)<br>
Enter charge of point:<br> 
3<br><br>

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
<a/>
Enter your choice:
1<br>
Enter coordinates of point:<br> 
(-1, -1)<br>
Enter charge of point:<br> 
-4<br><br>

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
<a/>
Enter your choice:
1<br>
Enter coordinates of point:<br> 
(1, 1.6)<br>
Enter charge of point:<br> 
0<br><br>

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
<a/>
Enter your choice:
4<br>
Enter the midpoint of your range:<br> 
(0.1, 0.1)<br>
Specify the length and breadth of the range:<br> 
4 4<br>
The point(s) present inside range is/are as follows:<br>
(0.200000, 0.200000)<br>
(1.000000, 1.600000)<br>
(-1.000000, -1.000000)<br><br>

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
<a/>
Enter your choice:
2<br>
Enter the point to be searched:<br> 
(0.1, 0.1)<br>
Charge of value 2.000000 is present at this co-ordinate.<br><br>

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
<a/>
Enter your choice:
2<br>
Enter the point to be searched:<br> 
(0, 0)<br>
No charge is present at this co-ordinate!<br><br>

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
<a/>
Enter your choice:
3<br>
Enter the point whose nearest point you would like to find out:<br> 
(0.4, 0.4)<br>
Closest point to (0.400000, 0.400000) is (0.200000, 0.200000)<br><br>

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
<a/>
Enter your choice:
5<br>
Enter the point at which you would like to find out the magnitude of net electric field:<br> 
(0, 0)<br>
Magnitude of electric field at (0.000000, 0.000000) is 172999999999.999939<br><br>

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
<a/>
Enter your choice:
5<br>
Enter the point at which you would like to find out the magnitude of net electric field:<br> 
(0.1, 0.1)<br>
Magnitude of electric field at (0.100000, 0.100000) is 298347107438.016418<br>
Force acting on charge present at (0.100000, 0.100000) is 596694214876.032837<br><br>

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
<a/>
Enter your choice:
6<br>
The point(s) present in the tree is/are as follows:<br>
(0.100000, 0.100000)<br>
(0.200000, 0.200000)<br>
(1.000000, 1.600000)<br>
(-1.000000, -1.000000)<br><br>

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
<a/>
Enter your choice:
7<br>
Program has been successfully terminated.<br><br>

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
