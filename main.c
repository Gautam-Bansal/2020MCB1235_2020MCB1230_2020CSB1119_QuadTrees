#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// node
struct Node{
    double x , y; // co-ordinates
    int charge;   // charge/mass value
    
    struct Node* nw; // NorthWest
    struct Node* ne; // NorthEast
    struct Node* sw; // SouthWest
    struct Node* se; // SouthEast
};

// function to allocate memory and values to node
// returns node
struct Node* newNode(double xCoordinate, double yCoordinate, int _charge){
    
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
    struct Node* temp = newNode(0.0, 0.0, 0);
    return temp;
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
    else printf("Charge of value %d is present at this co-ordinate.", temp->charge);
}

void main(){
    struct Node* root;
    root = initializeRoot();
    if(searchFun(root, 0.1, 0.1)==NULL)//since new implementation of insert function removes the else statement, adding error exception here
        root = insert(root, 0.1, 0.1, 2);
    else 
        printf("Error! Could not insert because some charge is already present there.\n");    
    if(searchFun(root, 0.2, 0.2)==NULL)
        root = insert(root, 0.2, 0.2, 3);
    else 
        printf("Error! Could not insert because some charge is already present there.\n");
    
    find(root, 0.1, 0.1); // not working don't know why, will look later maybe //fixed - AS
}
