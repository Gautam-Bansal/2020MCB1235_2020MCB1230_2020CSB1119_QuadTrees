#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define K 1000000000


// node
struct Node{
    double x , y; // co-ordinates
    double charge;   // charge/mass value
    
    struct Node* nw; // NorthWest
    struct Node* ne; // NorthEast
    struct Node* sw; // SouthWest
    struct Node* se; // SouthEast
};

// function to allocate memory and values to node
// returns node
struct Node* newNode(double xCoordinate, double yCoordinate, double _charge){
    
    // allocating memory
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    
    // assigning values
    temp->x = xCoordinate;
    temp->y = yCoordinate;
    temp->charge = _charge;
    
    // childrens to NULL
    temp->nw = NULL;
    temp->ne = NULL;
    temp->sw = NULL;
    temp->se = NULL;
    
    return temp;
}

// utility function to initialize root 
struct Node* initializeRoot(){
    struct Node* temp = newNode(0.0, 0.0, 0.0);
    return temp;
}

// Finds distance between two points in two-dimensional plane
// returns the calculated distance
double dist(double x1, double x2, double y1, double y2){
    return sqrt(pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0));
}

double electrofield(struct Node* root, double x, double y, double *field){
    if(root==NULL){
        return 0.0;
    }
    double dis = dist(root->x, x, root->y, y);
    double new;
    if(dis==0){
        new = 0.0;
    }
    else{
        new = (K*root->charge)/pow(dis, 2.0);
    }
    *field = *field + new + electrofield(root->ne, x, y, field) + electrofield(root->nw, x, y, field) + electrofield(root->se, x, y, field) + electrofield(root->sw, x, y, field);
    return *field;
}

struct Node* nearestPoint(struct Node* root, double x, double y, double *min){
    if(root==NULL){
        return NULL;
    }
    double distance = dist(root->x, x, root->y, y);
    struct Node* closest = NULL;
    if(distance <= *min){
        closest = root;
        *min = distance;
    }
    struct Node* temp1, *temp2, *temp3;
    if(x<root->x && y > root->y){
        temp1 = nearestPoint(root->nw, x, y, min);
        temp2 = nearestPoint(root->ne, x, y, min);
        temp3 = nearestPoint(root->sw, x, y, min);
    }
    else if(x>=root->x && y >= root->y){
        temp1 = nearestPoint(root->ne, x, y, min);
        temp2 = nearestPoint(root->nw, x, y, min);
        temp3 = nearestPoint(root->se, x, y, min);
    }
    else if(x<=root->x && y <= root->y){
        temp1 = nearestPoint(root->sw, x, y, min);
        temp2 = nearestPoint(root->nw, x, y, min);
        temp3 = nearestPoint(root->se, x, y, min);
    }
    else if(x>root->x && y < root->y){
        temp1 = nearestPoint(root->se, x, y, min);
        temp2 = nearestPoint(root->ne, x, y, min);
        temp3 = nearestPoint(root->sw, x, y, min);
    }
    if(temp1!=NULL){
        closest = temp1;
    }
    if(temp2!=NULL){
        closest = temp2;
    }
    if(temp3!=NULL){
        closest = temp3;
    }
    return closest;

}


// insert function 
// NOTE : According to standard graphing method/axes
//        ne (NorthEast) contains 1st quadrant and +x and +y axes
//        nw contains 2nd quadrant
//        sw contains 3rd quadrant along with -x and -y axes
//        se contains 4th quadrant
struct Node* insert(struct Node* root, double xCoordinate, double yCoordinate, int charge){
    if(root == NULL)
        root = newNode(xCoordinate, yCoordinate, charge);
    else if(xCoordinate < root->x && yCoordinate > root->y)
        root->nw = insert(root->nw, xCoordinate, yCoordinate, charge);
    else if((xCoordinate > root->x && yCoordinate > root->y) || (xCoordinate == root->x && yCoordinate > root->y) || (xCoordinate > root->x && yCoordinate == root->y))
        root->ne = insert(root->ne, xCoordinate, yCoordinate, charge);
    else if((xCoordinate < root->x && yCoordinate < root->y) || (xCoordinate == root->x && yCoordinate < root->y) || (xCoordinate < root->x && yCoordinate == root->y))
        root->sw = insert(root->sw, xCoordinate, yCoordinate, charge);
    else if(xCoordinate > root->x && yCoordinate < root->y)
        root->se = insert(root->se, xCoordinate, yCoordinate, charge);
    return root;    
    //else 
     //   printf("Error! Could not insert because some charge is already present there.\n");
}

// search function
// NOTE : this should NOT be called in main as
//        the utility function written below
//          makes use of it
struct Node* searchFun(struct Node* root, double xCoordinate, double yCoordinate){
    if(root == NULL)
        return NULL;
    
    if(xCoordinate == root->x && yCoordinate == root->y)
        return root;
    else if(xCoordinate < root->x && yCoordinate > root->y)
        searchFun(root->nw, xCoordinate, yCoordinate);
    else if((xCoordinate > root->x && yCoordinate > root->y) || (xCoordinate == root->x && yCoordinate > root->y) || (xCoordinate > root->x && yCoordinate == root->y))
        searchFun(root->ne, xCoordinate, yCoordinate);
    else if((xCoordinate < root->x && yCoordinate < root->y) || (xCoordinate == root->x && yCoordinate < root->y) || (xCoordinate < root->x && yCoordinate == root->y))
        searchFun(root->sw, xCoordinate, yCoordinate);
    else if(xCoordinate > root->x && yCoordinate < root->y)
        searchFun(root->se, xCoordinate, yCoordinate);
    else
        return NULL;
}

// utlity function 
// this function needs to be called in 'main'
void find(struct Node* root, double xCoordinate, double yCoordinate){
    struct Node* temp = searchFun(root, xCoordinate, yCoordinate);
    
    if(temp == NULL) printf("No charge is present at this co-ordinate!");
    else printf("Charge of value %f is present at this co-ordinate.", temp->charge);
}

// Performs range search
// Prints all points inside a rectangular area with a given point at it's center 
void rangeQuery(struct Node* root, double xCoordinate, double yCoordinate, double length, double breadth){

	if(root == NULL)
		return;
	if(dist(root->x, xCoordinate, root->y, yCoordinate) < sqrt(pow(length, 2) + pow(breadth, 2))/2){
		if(dist(root->x, xCoordinate, root->y, yCoordinate) != 0){printf("(%f, %f)\n", root->x, root->y);}
		rangeQuery(root->nw, xCoordinate, yCoordinate, length, breadth);
		rangeQuery(root->ne, xCoordinate, yCoordinate, length, breadth);
		rangeQuery(root->sw, xCoordinate, yCoordinate, length, breadth);
		rangeQuery(root->se, xCoordinate, yCoordinate, length, breadth);
	}
	else{
		if(xCoordinate < root->x && yCoordinate > root->y)
			rangeQuery(root->nw, xCoordinate, yCoordinate, length, breadth);
		else if((xCoordinate > root->x && yCoordinate > root->y) || (xCoordinate == root->x && yCoordinate > root->y) || (xCoordinate > root->x && yCoordinate == root->y))
			rangeQuery(root->ne, xCoordinate, yCoordinate, length, breadth);
		else if((xCoordinate < root->x && yCoordinate < root->y) || (xCoordinate == root->x && yCoordinate < root->y) || (xCoordinate < root->x && yCoordinate == root->y))
			rangeQuery(root->sw, xCoordinate, yCoordinate, length, breadth);
		else if(xCoordinate > root->x && yCoordinate < root->y)
			rangeQuery(root->se, xCoordinate, yCoordinate, length, breadth);
	}
	return;
}

void main(){
    struct Node* root;
    root = initializeRoot();
    if(searchFun(root, 0.1, 0.1)==NULL)//since new implementation of insert function removes the else statement, adding error exception here
        root = insert(root, 0.1, 0.1, 2.0);
    else 
        printf("Error! Could not insert because some charge is already present there.\n");    
    if(searchFun(root, 0.2, 0.2)==NULL)
        root = insert(root, 0.2, 0.2, 3.0);
    else 
        printf("Error! Could not insert because some charge is already present there.\n");
    if(searchFun(root, -1, -1)==NULL)
        root = insert(root, -1, -1, -4);
    else 
        printf("Error! Could not insert because some charge is already present there.\n");   
	if(searchFun(root, 1, 1.6)==NULL)
        root = insert(root, 1, 1.6, 0);
    else 
        printf("Error! Could not insert because some charge is already present there.\n");   
	if(searchFun(root, 5, 3)==NULL)
        root = insert(root, 5, 3, -2);
    else 
        printf("Error! Could not insert because some charge is already present there.\n");   
		
	rangeQuery(root, 0.1, 0.1, 4, 4);
    find(root, 0.1, 0.1); // not working don't know why, will look later maybe //fixed - AS
    double min = dist(0.0, 0.04, 0.0, 0.04);
    printf("\nClosest point to (0.04,0.04) is (%f,%f)", nearestPoint(root, 0.04, 0.04, &min)->x, nearestPoint(root, 0.04, 0.04, &min)->y);
    double pot = 0.0;
    printf("\nPotential at (0,0) is %f", electrofield(root, 0.0, 0.0, &pot));
}
