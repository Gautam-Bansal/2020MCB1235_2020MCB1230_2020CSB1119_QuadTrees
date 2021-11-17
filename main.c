#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <math.h>

#define K 1000000000

// node
struct Node {
  double x, y; // co-ordinates
  double charge; // charge/mass value

  struct Node * nw; // NorthWest
  struct Node * ne; // NorthEast
  struct Node * sw; // SouthWest
  struct Node * se; // SouthEast
};

// function to allocate memory and values to node
// returns node
struct Node * newNode(double xCoordinate, double yCoordinate, double _charge) {

  // allocating memory
  struct Node * temp = (struct Node * ) malloc(sizeof(struct Node));

  // assigning values
  temp -> x = xCoordinate;
  temp -> y = yCoordinate;
  temp -> charge = _charge;

  // childrens to NULL
  temp -> nw = NULL;
  temp -> ne = NULL;
  temp -> sw = NULL;
  temp -> se = NULL;

  return temp;
}

// utility function to initialize root 
struct Node * initializeRoot() {
  struct Node * temp = newNode(0.0, 0.0, 0.0);
  return temp;
}

// Finds distance between two points in two-dimensional plane
// returns the calculated distance
double dist(double x1, double x2, double y1, double y2) {
  return sqrt(pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0));
}

// should NOT be called in 
// main as the utlity function 
// makes use of it
double electrofieldFun(struct Node * root, double x, double y, double * field) {
  if (root == NULL) {
    return 0.0;
  }
  double dis = dist(root -> x, x, root -> y, y);
  double new;
  if (dis == 0) {
    new = 0.0;
  } else {
    new = (K * root -> charge) / pow(dis, 2.0);
  }
  * field = * field + new + electrofieldFun(root -> ne, x, y, field) + electrofieldFun(root -> nw, x, y, field) + electrofieldFun(root -> se, x, y, field) + electrofieldFun(root -> sw, x, y, field);
  return *field;
}

// utility function for 'electrofieldFun'
// this should be called in main
void electrofield(struct Node * root,double x,double y){
	double field = 0.0;
	
	electrofieldFun(root, x, y, &field);
	
	printf("Potential at (%f, %f) is %f\n", x, y, field);
}

// this should NOT be 
// called in main
struct Node * nearestPointFun(struct Node * root, double x, double y, double * min) {
  if (root == NULL) {
    return NULL;
  }
  double distance = dist(root -> x, x, root -> y, y);
  struct Node * closest = NULL;
  if (distance <= * min) {
    closest = root;
    * min = distance;
  }
  struct Node * temp1, * temp2, * temp3;
  if (x < root -> x && y > root -> y) {
    temp1 = nearestPointFun(root -> nw, x, y, min);
    temp2 = nearestPointFun(root -> ne, x, y, min);
    temp3 = nearestPointFun(root -> sw, x, y, min);
  } else if (x >= root -> x && y >= root -> y) {
    temp1 = nearestPointFun(root -> ne, x, y, min);
    temp2 = nearestPointFun(root -> nw, x, y, min);
    temp3 = nearestPointFun(root -> se, x, y, min);
  } else if (x <= root -> x && y <= root -> y) {
    temp1 = nearestPointFun(root -> sw, x, y, min);
    temp2 = nearestPointFun(root -> nw, x, y, min);
    temp3 = nearestPointFun(root -> se, x, y, min);
  } else if (x > root -> x && y < root -> y) {
    temp1 = nearestPointFun(root -> se, x, y, min);
    temp2 = nearestPointFun(root -> ne, x, y, min);
    temp3 = nearestPointFun(root -> sw, x, y, min);
  }
  if (temp1 != NULL) {
    closest = temp1;
  }
  if (temp2 != NULL) {
    closest = temp2;
  }
  if (temp3 != NULL) {
    closest = temp3;
  }
  return closest;
}


// utility function for 'nearestPointFun'
// should be called in main
void nearestPoint(struct Node* root, double x, double y){
	double min = dist(0.0, x, 0.0, y);
	struct Node* temp = nearestPointFun(root, x, y, &min);
	printf("Closest point to (%f, %f) is (%f, %f)\n", x , y, temp -> x, temp -> y);
}

// insert function 
// NOTE : According to standard graphing method/axes
//        ne (NorthEast) contains 1st quadrant and +x and +y axes
//        nw contains 2nd quadrant
//        sw contains 3rd quadrant along with -x and -y axes
//        se contains 4th quadrant
struct Node * insertFun(struct Node * root, double xCoordinate, double yCoordinate, int charge) {
  if (root == NULL)
    root = newNode(xCoordinate, yCoordinate, charge);
  else if (xCoordinate < root -> x && yCoordinate > root -> y)
    root -> nw = insertFun(root -> nw, xCoordinate, yCoordinate, charge);
  else if ((xCoordinate > root -> x && yCoordinate > root -> y) || (xCoordinate == root -> x && yCoordinate > root -> y) || (xCoordinate > root -> x && yCoordinate == root -> y))
    root -> ne = insertFun(root -> ne, xCoordinate, yCoordinate, charge);
  else if ((xCoordinate < root -> x && yCoordinate < root -> y) || (xCoordinate == root -> x && yCoordinate < root -> y) || (xCoordinate < root -> x && yCoordinate == root -> y))
    root -> sw = insertFun(root -> sw, xCoordinate, yCoordinate, charge);
  else if (xCoordinate > root -> x && yCoordinate < root -> y)
    root -> se = insertFun(root -> se, xCoordinate, yCoordinate, charge);
  return root;
  //else 
  //   printf("Error! Could not insert because some charge is already present there.\n");
}

struct Node * searchFun(struct Node * root, double xCoordinate, double yCoordinate);

// utility function for insertFun
void insert(struct Node** root,struct Node* rootRef, double xCoordinate, double yCoordinate, int charge) {
	struct Node * temp = searchFun(rootRef, xCoordinate, yCoordinate);
	if(temp == NULL)
		*root = insertFun(rootRef, xCoordinate, yCoordinate, charge);
	else printf("Error! Could not insert because a charge is already present there.\n");
}

// search function
// NOTE : this should NOT be called in main as
//        the utility function written below
//          makes use of it
struct Node * searchFun(struct Node * root, double xCoordinate, double yCoordinate) {
  if (root == NULL)
    return NULL;

  if (xCoordinate == root -> x && yCoordinate == root -> y)
    return root;
  else if (xCoordinate < root -> x && yCoordinate > root -> y)
    searchFun(root -> nw, xCoordinate, yCoordinate);
  else if ((xCoordinate > root -> x && yCoordinate > root -> y) || (xCoordinate == root -> x && yCoordinate > root -> y) || (xCoordinate > root -> x && yCoordinate == root -> y))
    searchFun(root -> ne, xCoordinate, yCoordinate);
  else if ((xCoordinate < root -> x && yCoordinate < root -> y) || (xCoordinate == root -> x && yCoordinate < root -> y) || (xCoordinate < root -> x && yCoordinate == root -> y))
    searchFun(root -> sw, xCoordinate, yCoordinate);
  else if (xCoordinate > root -> x && yCoordinate < root -> y)
    searchFun(root -> se, xCoordinate, yCoordinate);
  else
    return NULL;
}

// utlity function 
// this function needs to be called in 'main'
void find(struct Node * root, double xCoordinate, double yCoordinate) {
  struct Node * temp = searchFun(root, xCoordinate, yCoordinate);

  if (temp == NULL) printf("No charge is present at this co-ordinate!\n");
  else printf("Charge of value %f is present at this co-ordinate.\n", temp -> charge);
}

// Performs range search
// Prints all points inside a rectangular area with a given point at it's center 
void rangeQuery(struct Node * root, double xCoordinate, double yCoordinate, double length, double breadth) {

  if (root == NULL)
    return;
  if (dist(root -> x, xCoordinate, root -> y, yCoordinate) < sqrt(pow(length, 2) + pow(breadth, 2)) / 2) {
    if (dist(root -> x, xCoordinate, root -> y, yCoordinate) != 0) {
      printf("(%f, %f)\n", root -> x, root -> y);
    }
    rangeQuery(root -> nw, xCoordinate, yCoordinate, length, breadth);
    rangeQuery(root -> ne, xCoordinate, yCoordinate, length, breadth);
    rangeQuery(root -> sw, xCoordinate, yCoordinate, length, breadth);
    rangeQuery(root -> se, xCoordinate, yCoordinate, length, breadth);
  } else {
    if (xCoordinate < root -> x && yCoordinate > root -> y)
      rangeQuery(root -> nw, xCoordinate, yCoordinate, length, breadth);
    else if ((xCoordinate > root -> x && yCoordinate > root -> y) || (xCoordinate == root -> x && yCoordinate > root -> y) || (xCoordinate > root -> x && yCoordinate == root -> y))
      rangeQuery(root -> ne, xCoordinate, yCoordinate, length, breadth);
    else if ((xCoordinate < root -> x && yCoordinate < root -> y) || (xCoordinate == root -> x && yCoordinate < root -> y) || (xCoordinate < root -> x && yCoordinate == root -> y))
      rangeQuery(root -> sw, xCoordinate, yCoordinate, length, breadth);
    else if (xCoordinate > root -> x && yCoordinate < root -> y)
      rangeQuery(root -> se, xCoordinate, yCoordinate, length, breadth);
  }
  return;
}

void main() {
  struct Node * root = NULL;
  
  root = initializeRoot(); // just comment this to make first the inserted
						   // element 'centre' if no function till 
						   // end makes use of (0,0 being centre)
  
  insert(&root, root, 0.1, 0.1, 2);
  insert(&root, root, 0.1, 0.1, 2);
  
  insert(&root, root, 0.2, 0.2, 3);
  insert(&root, root, -1.0, -1.0, -4);
  insert(&root, root, 1.0, 1.6, 0);
  insert(&root, root, 5.0, 3.0, -2);

  rangeQuery(root, 0.1, 0.1, 4, 4);
  find(root, 0.1, 0.1); // not working don't know why, will look later maybe //fixed - AS
  find(root, 0.0, 0.0);
  
  nearestPoint(root, 0.4, 0.4);
  
  electrofield(root, 0.0, 0.0);
}