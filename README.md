# 2020MCB1235_2020MCB1230_2020CSB1119_QuadTrees
CS-201 Project on QuadTrees
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Compiler Details :

The code is completely written in c language and compiled using the following gcc version.
gcc (tdm64-1) 9.2.0

However, pretty much any c compiler should run it.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How to give input :

On running the executable file the user will be asked to choose between 7 options shown on the screen and will have to enter the index of whatever option they want to choose.
For example, if they want to insert just enter 1. If they want to exit the program just enter 7 whenever asked to choose between the options.

Whenever (any option that needs co-ordinates) user needs to enter co-ordinates they need to do so in (x, y) format. 
For example, if user wants to insert a point with x-coordiante as 2.0 and y-coordinate as 3.0 then they need to enter (2.0, 3.0) after entering 1 from the options menu.
If they need to input charge q just enter q.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What to expect from each option :

1. Insert option just inserts the charge at specified co-ordiante.
2. Search option tells the value of charge (if there is) at the entered co-ordinate.
3. Nearest option outputs the co-ordinates of nearest charge to the entered co-ordinate.
4. Range Query prints out all the co-ordinates present in a rectangle with entered centre point and length, breadth.
5. Electric field options prints out the magnitude of electric field at entered co-ordinate.
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
Enter your choice: 1
Enter coordinates of point: 
(0.1, 0.1)
Enter charge of point: 
2

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
Enter your choice: 1
Enter coordinates of point: 
(0.1, 0.1)
Enter charge of point: 
3
Error! Could not insert because a charge is already present there.

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
Enter your choice: 1
Enter coordinates of point: 
(0.2, 0.2)
Enter charge of point: 
3

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
Enter your choice: 1
Enter coordinates of point: 
(-1, -1)
Enter charge of point: 
-4

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
Enter your choice: 1
Enter coordinates of point: 
(1, 1.6)
Enter charge of point: 
0

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
Enter your choice: 4
Enter the midpoint of your range: 
(0.1, 0.1)
Specify the length and breadth of the range: 
4 4
The point(s) present inside range is/are as follows:
(0.200000, 0.200000)
(1.000000, 1.600000)
(-1.000000, -1.000000)

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
Enter your choice: 2
Enter the point to be searched: 
(0.1, 0.1)
Charge of value 2.000000 is present at this co-ordinate.

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
Enter your choice: 2
Enter the point to be searched: 
(0, 0)
No charge is present at this co-ordinate!

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
Enter your choice: 3
Enter the point whose nearest point you would like to find out: 
(0.4, 0.4)
Closest point to (0.400000, 0.400000) is (0.200000, 0.200000)

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
Enter your choice: 5
Enter the point at which you would like to find out the magnitude of net electric field: 
(0, 0)
Magnitude of electric field at (0.000000, 0.000000) is 172999999999.999939

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
Enter your choice: 5
Enter the point at which you would like to find out the magnitude of net electric field: 
(0.1, 0.1)
Magnitude of electric field at (0.100000, 0.100000) is 298347107438.016418
Force acting on charge present at (0.100000, 0.100000) is 596694214876.032837:

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
Enter your choice: 6
The point(s) present in the tree is/are as follows:
(0.100000, 0.100000)
(0.200000, 0.200000)
(1.000000, 1.600000)
(-1.000000, -1.000000)

Which operation would you like to perform:
1. Insert
2. Search
3. Nearest point
4. Range Search
5. Electric field/force
6. Display
7. Quit
Enter your choice: 7

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
