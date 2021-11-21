#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <math.h>

#define K 1000000000

int flag = 0;

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
struct Node* newNode(double xCoordinate, double yCoordinate, double _charge) {
    // allocating memory
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));

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

// Finds distance between two points in two-dimensional plane
// returns the calculated distance
double dist(double x1, double x2, double y1, double y2) {
    return sqrt(pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0));
}

struct Node* searchFun(struct Node* root, double xCoordinate, double yCoordinate);


// Finds force acting on charge if present at (x,y)
void coulumbForce(struct Node *root, double x, double y, double field) {
    struct Node *temp = searchFun(root, x, y);
	if(temp == NULL) {return;}
    else {printf("Force acting on charge present at (%f, %f) is %f\n", x, y, field*(temp -> charge));}
}

// should NOT be called in 
// main as the utlity function 
// makes use of it
double electrofieldFun(struct Node *root, double x, double y, double *field) {
    if (root == NULL) {
        return 0.0;
    }
    double dis = dist(root -> x, x, root -> y, y);  // Find distance between root and (x, y)
    double new;
    if (dis == 0) {
        new = 0.0;
    } else {
        new = (K * root -> charge) / pow(dis, 2.0); // Calculate electric field at (x, y) due to root 
    }
    // Visit all children of root point
    *field = *field + new + electrofieldFun(root -> ne, x, y, field) + electrofieldFun(root -> nw, x, y, field) + electrofieldFun(root -> se, x, y, field) + electrofieldFun(root -> sw, x, y, field); 
    return *field;
}

void display(struct Node* root) {
    	if(root == NULL)
        	return;
    printf("(%f, %f)\n", root -> x , root -> y); // Print root
    // Visit all children of root point
    display(root -> nw);
    display(root -> ne);
    display(root -> sw);
    display(root -> se);
    return;
}

// utility function for 'electrofieldFun'
// this should be called in main
void electrofield(struct Node* root, double x, double y) {

	double field = 0.0;
	electrofieldFun(root, x, y, &field);
	printf("Magnitude of electric field at (%f, %f) is %f\n", x, y, field);
    coulumbForce(root, x, y, field);
    return;
}

// this should NOT be 
// called in main
struct Node* nearestPointFun(struct Node* root, double x, double y, double* min) {
    if (root == NULL) {
        return NULL;
    }
    double distance = dist(root -> x, x, root -> y, y); // Find distance between root and (x, y)
    struct Node* closest = NULL;
    if (distance <= *min) { // If distance is less than minimum distance
        closest = root; // Update closest point
        *min = distance; // Update minimum distance
    }
    struct Node * temp1, * temp2, * temp3;
    // If root lies in southeast direction of (x, y) point, Visit all children of root not lying in southeast direction of root
    if (x < root -> x && y > root -> y) { 
        temp1 = nearestPointFun(root -> nw, x, y, min);
        temp2 = nearestPointFun(root -> ne, x, y, min);
        temp3 = nearestPointFun(root -> sw, x, y, min);
    } 
    // If root lies in southwest direction of (x, y) point, Visit all children of root not lying in southwest direction of root
    else if (x >= root -> x && y >= root -> y) { 
        temp1 = nearestPointFun(root -> ne, x, y, min);
        temp2 = nearestPointFun(root -> nw, x, y, min);
        temp3 = nearestPointFun(root -> se, x, y, min);
    // If root lies in northeast direction of (x, y) point, Visit all children of root not lying in northeast direction of root
    } else if (x <= root -> x && y <= root -> y) { 
        temp1 = nearestPointFun(root -> sw, x, y, min);
        temp2 = nearestPointFun(root -> nw, x, y, min);
        temp3 = nearestPointFun(root -> se, x, y, min);
    // If root lies in northwest direction of (x, y) point, Visit all children of root not lying in northwest direction of root
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

	double min = dist(root->x, x, root->y, y);
	struct Node* temp = nearestPointFun(root, x, y, &min);
    if(temp == NULL){printf("No charge around!\n");}
	else{printf("Closest point to (%f, %f) is (%f, %f)\n", x , y, temp -> x, temp -> y);}
    return;
}

// insert function 
// NOTE : According to standard graphing method/axes
//        ne (NorthEast) contains 1st quadrant and +x and +y axes
//        nw contains 2nd quadrant
//        sw contains 3rd quadrant along with -x and -y axes
//        se contains 4th quadrant
struct Node* insertFun(struct Node* root, double xCoordinate, double yCoordinate, double charge) {
    if (root == NULL)
        root = newNode(xCoordinate, yCoordinate, charge); 
    // If root lies in southeast direction of (x, y) point
    else if (xCoordinate < root -> x && yCoordinate > root -> y)  
        root -> nw = insertFun(root -> nw, xCoordinate, yCoordinate, charge); // Visit southeast child of root and insert (x, y) at right position
    // If root lies in southwest direction of (x, y) point
    else if ((xCoordinate > root -> x && yCoordinate > root -> y) || (xCoordinate == root -> x && yCoordinate > root -> y) || (xCoordinate > root -> x && yCoordinate == root -> y))
        root -> ne = insertFun(root -> ne, xCoordinate, yCoordinate, charge); // Visit southwest child of root and insert (x, y) at right position
    // If root lies in northeast direction of (x, y) point
    else if ((xCoordinate < root -> x && yCoordinate < root -> y) || (xCoordinate == root -> x && yCoordinate < root -> y) || (xCoordinate < root -> x && yCoordinate == root -> y))
        root -> sw = insertFun(root -> sw, xCoordinate, yCoordinate, charge); // Visit northeast child of root and insert (x, y) at right position
    // If root lies in northwest direction of (x, y) point
    else if (xCoordinate > root -> x && yCoordinate < root -> y) 
        root -> se = insertFun(root -> se, xCoordinate, yCoordinate, charge); // Visit northwest child of root and insert (x, y) at right position
    return root;
}

// utility function for insertFun
void insert(struct Node** root,struct Node* rootRef, double xCoordinate, double yCoordinate, double charge) {

	struct Node *temp = searchFun(rootRef, xCoordinate, yCoordinate);
	if(temp == NULL)
		*root = insertFun(rootRef, xCoordinate, yCoordinate, charge);
	else printf("Error! Could not insert because a charge is already present there.\n");
    return;
}

// search function
// NOTE : this should NOT be called in main as
//        the utility function written below
//          makes use of it
struct Node* searchFun(struct Node* root, double xCoordinate, double yCoordinate) {
   
    if (root == NULL)
        return NULL;

    if (xCoordinate == root -> x && yCoordinate == root -> y) 
        return root;
    // If root lies in southeast direction of (x, y) point
    else if (xCoordinate < root -> x && yCoordinate > root -> y)
        searchFun(root -> nw, xCoordinate, yCoordinate); // Search southeast child of root
    // If root lies in southwest direction of (x, y) point
    else if ((xCoordinate > root -> x && yCoordinate > root -> y) || (xCoordinate == root -> x && yCoordinate > root -> y) || (xCoordinate > root -> x && yCoordinate == root -> y)) 
        searchFun(root -> ne, xCoordinate, yCoordinate); // Search southwest child of root
    // If root lies in northeast direction of (x, y) point
    else if ((xCoordinate < root -> x && yCoordinate < root -> y) || (xCoordinate == root -> x && yCoordinate < root -> y) || (xCoordinate < root -> x && yCoordinate == root -> y))
        searchFun(root -> sw, xCoordinate, yCoordinate); // Search northeast child of root
    // If root lies in northwest direction of (x, y) point
    else if (xCoordinate > root -> x && yCoordinate < root -> y)
        searchFun(root -> se, xCoordinate, yCoordinate); // Search northwest child of root
    else
        return NULL;
}

// utlity function 
// this function needs to be called in 'main'
void find(struct Node* root, double xCoordinate, double yCoordinate) {
    struct Node* temp = searchFun(root, xCoordinate, yCoordinate);

    if (temp == NULL) printf("No charge is present at this co-ordinate!\n");
    else printf("Charge of value %lf is present at this co-ordinate.\n", temp -> charge);
    return;
}

// Performs range search
// Prints all points inside a rectangular area with a given point at it's center 
void rangeQuery(struct Node* root, double xCoordinate, double yCoordinate, double length, double breadth) {

    if (root == NULL)
        return;
    // If root lies inside rectangular region
    if (dist(root -> x, xCoordinate, root -> y, yCoordinate) < sqrt(pow(length, 2) + pow(breadth, 2)) / 2) {
        if (dist(root -> x, xCoordinate, root -> y, yCoordinate) != 0) {
            flag++;
            if(flag == 1){printf("The point(s) present inside range is/are as follows:\n");}
            printf("(%f, %f)\n", root -> x, root -> y);
        }
        // Range search all children of root
        rangeQuery(root -> nw, xCoordinate, yCoordinate, length, breadth);
        rangeQuery(root -> ne, xCoordinate, yCoordinate, length, breadth);
        rangeQuery(root -> sw, xCoordinate, yCoordinate, length, breadth);
        rangeQuery(root -> se, xCoordinate, yCoordinate, length, breadth);
    } else { 
        // If root lies in southeast direction of (x, y) point
        if (xCoordinate < root -> x && yCoordinate > root -> y)
        rangeQuery(root -> nw, xCoordinate, yCoordinate, length, breadth); // Range search northwest child of root
        // If root lies in southwest direction of (x, y) point
        else if ((xCoordinate > root -> x && yCoordinate > root -> y) || (xCoordinate == root -> x && yCoordinate > root -> y) || (xCoordinate > root -> x && yCoordinate == root -> y))
        rangeQuery(root -> ne, xCoordinate, yCoordinate, length, breadth); // Range search northeast child of root
        // If root lies in northeast direction of (x, y) point
        else if ((xCoordinate < root -> x && yCoordinate < root -> y) || (xCoordinate == root -> x && yCoordinate < root -> y) || (xCoordinate < root -> x && yCoordinate == root -> y))
        rangeQuery(root -> sw, xCoordinate, yCoordinate, length, breadth); // Range search southwest child of root
        // If root is in northwest direction of (x, y) point
        else if (xCoordinate > root -> x && yCoordinate < root -> y)
        rangeQuery(root -> se, xCoordinate, yCoordinate, length, breadth); // Range search southeast child of root
    }
    return;
}

int main() {
    struct Node * root = NULL;
    int choice = 0;
    double x, y, length, breadth, charge;
    while(choice != 7){
		printf("Which operation would you like to perform:"
             "\n1. Insert"
             "\n2. Search" 
             "\n3. Nearest point"
             "\n4. Range Search"
             "\n5. Electric field/force" 
             "\n6. Display"
             "\n7. Quit"
             "\nEnter your choice: ");
		scanf("\n%d", &choice);
		switch(choice){
            case 1:{
                printf("Enter coordinates of point: \n");
                scanf(" (%lf, %lf)", &x, &y);
                printf("Enter charge of point: \n");
                scanf(" %lf", &charge);
                insert(&root, root, x, y, charge);
                break;
            }
            case 2:{
                printf("Enter the point to be searched: \n");
                scanf(" (%lf, %lf)", &x, &y);
                find(root, x, y);
                break;
            }
            case 3:{
                printf("Enter the point whose nearest point you would like to find out: \n");
                scanf(" (%lf, %lf)", &x, &y);
                nearestPoint(root, x, y);
                break;
            }
            case 4:{
                flag = 0;
                printf("Enter the midpoint of your range: \n");
                scanf(" (%lf, %lf)", &x, &y);
                printf("Specify the length and breadth of the range: \n");
                scanf(" %lf %lf", &length, &breadth);
                rangeQuery(root, x, y, length, breadth);
                if(flag == 0){printf("No points found in range!\n");}
                break;
            }
            case 5:{
                printf("Enter the point at which you would like to find out the magnitude of net electric field: \n");
                scanf(" (%lf, %lf)", &x, &y);
                electrofield(root, x, y);
                break;
            }
            case 6:{
                if(root==NULL){
                    printf("Tree is empty!\n");
                    break;
                }
                else{
                    printf("The point(s) present in the tree is/are as follows:\n");
                    display(root);
                    break;
                }
            }
            case 7:{
                choice = 7;
		printf("Program has been successfully terminated.");
                break;
            }
            default:{printf("Choose a valid option.\n");}
        }
	}
    return 0;
}
