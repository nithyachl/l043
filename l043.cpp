// A C++ program to demonstrate operations of KD tree
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <utility>
#include <fstream>
#include <iterator>


void drawCircle(double r, double xcenter, double ycenter, int color);
void drawLine(int x1, int y1, int x2, int y2);
using namespace std;

const int k = 7;
int in = 1;
// A structure to represent node of kd tree
struct Node
{
    int point[k]; // To store k dimensional point 
    Node *left, *right;
};

// A method to create a node of K D tree 
struct Node* newNode(int arr[])
{
    struct Node* temp = new Node;

    for (int i=0; i<k; i++)
        temp->point[i] = arr[i];

    temp->left = temp->right = nullptr;
    return temp;
}

void part3();

void traverse(Node *root, int level, int i);

void drawExtendedHorizontal(int i, int i1);

void drawExtendedVertical(int i, int i1);

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison 
Node *insertRec(Node *root, int point[], unsigned depth)
{
    // Tree is empty? 
    if (root == nullptr)
        return newNode(point);

    // Calculate current dimension (cd) of comparison 
    unsigned cd = depth % k;

    // Compare the new point with root on current dimension 'cd' 
    // and decide the left or right subtree 
    if (point[cd] < (root->point[cd]))
        root->left  = insertRec(root->left, point, depth + 1);
    else
        root->right = insertRec(root->right, point, depth + 1);

    return root;
}

// Function to insert a new point with given point in 
// KD Tree and return new root. It mainly uses above recursive 
// function "insertRec()" 
Node* insert(Node *root, int point[])
{
    return insertRec(root, point, 0);
}

int matrix[800][800];

// Driver program to test above functions 
int main()
{
    std::ofstream test;

    test.open ("diagram.ppm");
    test << "P3" << endl << 800 << ' ' << 800 << endl << "1" << endl;

    for (int n = 0; n < 800; ++n) {
        for (int m = 0; m < 800; ++m) {
            matrix[n][m] = 1;
        }
    }

    //srand( time(NULL) );

    part3();

    for (int n = 0; n < 800; ++n) {
        for (int m = 0; m < 800; ++m) {

            if(matrix[n][m] == 4)
            {
                test<< 1 << " "<< 0 << " " << 0 << "     ";
            }

            else
                test<< matrix[n][m] << " "<< matrix[n][m] << " " << matrix[n][m] << "     ";          //std::to_string(matrix[n][m]) << " ";

        }
        test << endl;
    }

    test.close();

    return 0;

}

void part3() {
    struct Node *root = nullptr;
    int points[][k] = {{3, 6}, {17, 15}, {13, 15}, {6, 12},
                       {9, 1}, {2, 7}, {10, 19}};
    

    int n = sizeof(points)/sizeof(points[0]);

    for (int i=0; i<n; i++)
    {
        //cout << points[i][0] <<"  " << points[i][1]<< endl;
        root = insert(root, points[i]);
        cout << points[i][0] <<"  " << points[i][1]<< endl;
//        drawCircle(2,points[i][0], points[i][1], 4);

        drawCircle(2,points[i][0]*40, points[i][1]*40, 4);

    }
    cout << "Root: " << root->point[0] <<"  " <<root->point[1];
    //drawLine(root->point[0]*40, 0, root->point[0]*40, 800);

    struct Node *ptr = root;

    drawLine(root->point[0]*40 , 0, root->point[0]*40, 800);

    int rootX = root->point[0]*40;
    int rootY = root->point[1]*40;

//    // *1  0  *1  800
//
//    drawLine(0, root->left->point[1]*40, rootX, root->left->point[1]*40);
//
//    // 0 *2a *1 *2a
//
//    drawLine(800, root->right->point[1]*40, rootX, root->right->point[1]*40);
//
//    // 800 *2b *1 *2b
//
//    drawLine(root->right->left->point[0]*40, 0, root->right->left->point[0]*40, root->right->point[1]*40);
//
//    // *3c  0  *3c *2b
//
//    drawLine(root->right->right->point[0]*40, 800, root->right->right->point[0]*40, root->right->point[1]*40);
//
//    // *3d *2b  *3d  800
//
//    drawLine(800, root->right->left->right->point[1]*40, root->right->left->point[0]*40, root->right->left->right->point[1]*40);
//
//    // *3d  *4b  800  *4b
//
//    drawLine(rootX, root->right->right->right->point[1]*40, root->right->right->point[0]*40, root->right->right->right->point[1]*40);
//
//    // *1  *4c  *3d  *4c
//



        while (in <= 4) {
            traverse(root, in, 0);
            in++;
        }




}

void traverse(Node *root, int level, int i)
{
    if (root == NULL)
        return;
    if (level == 1) {
        cout << "Traverse: " << root->point[0] << " " << root->point[1] << endl;
        if(in%2 == 1 && i==0) {
            //drawLine(root->point[0] * 40, 0, root->point[0] * 40, root->point[1] * 40);
            drawExtendedVertical(root->point[0] * 40, root->point[1] * 40);

        }

        if(in%2 == 1 && i==1) {
            //drawLine(root->point[0] * 40, 800, root->point[0] * 40, root->point[1] * 40);
            drawExtendedVertical(root->point[0] * 40, root->point[1] * 40);
        }

        if(in%2 == 0 && i == 0) {
            //drawLine(root->point[0] * 40, root->point[1] * 40, 0, root->point[1] * 40);
            drawExtendedHorizontal(root->point[0] * 40, root->point[1] * 40);
        }
        if(in%2 == 0 && i == 1) {
            //drawLine(root->point[0] * 40, root->point[1] * 40, 800, root->point[1] * 40);
            drawExtendedHorizontal(root->point[0] * 40, root->point[1] * 40);
        }
        }
    else if (level > 1)
    {
        traverse(root->left, level - 1, 0);
        //drawLine(root->left->point[0]*40, 0, root->left->point[0]*40, root->point[1]*40);


        traverse(root->right, level - 1, 1);

        //drawLine(root->right->point[0]*40, 800, root->right->point[0]*40, root->point[1]*40);


    }
}

void drawExtendedVertical(int i, int i1) {

    int ymax = i1;
    int ymin = i1;
    int x1 = i;
    int x2 = i;

//    cout << "YMaXorii: " <<  i << endl;
//    cout << "color: " <<  matrix[ymin][i] << endl;

    ymax = ymax+1;
    while(matrix[ymax][i] != 0 && ymax <=800)
    {
        ymax = ymax+1;
//        cout << "color: " <<  matrix[i][ymin] << endl;
//        cout << "YMaX: " <<  ymax << endl;
    }

    ymin = ymin-1;
//    cout << "color: " <<  matrix[i][ymin] << endl;
    cout << "ymin: " <<  ymin << endl;
    while(matrix[ymin][i] != 0 && ymin>=0)
    {
        ymin = ymin-1;
        cout << "ymin: " <<  ymin << endl;
    }

    cout << "YMaX: " <<  ymax << endl;
    cout << "YMin: " <<  ymin << endl;


    if (ymax>800)
        ymax = 800;



    if (ymin<0)
        ymin = 0;

    int y2 = ymax;
    int y1 = ymin;

    int dx = x2 - x1 ;
    int dy = y2 - y1 ;
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
    if (dy<0){
        dy1 = -1 ;
    }
    else if (dy>0){
        dy1 = 1 ;
    }
    if (dx<0) {
        dx1 = -1;
    }
    else if (dx>0){
        dx1 = 1 ;}
    if (dy<0){
        dy2 = -1;
    }
    else if (dy>0){
        dy2 = 1 ;
    }
    int longest = abs(dy) ;
    int shortest = abs(dx) ;
    if (!(longest>shortest)) {
        longest = abs(dx) ;
        shortest = abs(dy) ;
        if (dx<0)
        {
            dx2 = -1 ;
        }

        else if (dx>0) {
            dx2 = 1;
        }
        dy2 = 0 ;
    }
    int numerator = longest >> 1 ;

    for (int i=0;i<=longest;i++) {
        matrix[y1][x1] = 0;
        numerator += shortest ;
        if (!(numerator<longest)) {
            numerator -= longest ;
            x1 += dx1 ;
            y1 += dy1 ;
        } else {
            x1 += dx2 ;
            y1 += dy2 ;
        }
    }

}

void drawExtendedHorizontal(int i, int i1) {

    int y2 = i1;
    int y1 = i1;
    int xmax = i;
    int xmin = i;

//    cout << "YMaXorii: " <<  i << endl;
//    cout << "color: " <<  matrix[i][xmin] << endl;

    xmax = xmax++;
    while(matrix[i1][xmax] != 0 && xmax <=800)
    {
        xmax = xmax+1;
//        cout << "color: " <<  matrix[i][xmin] << endl;
//        cout << "YMaX: " <<  xmax << endl;
    }

    xmin = xmin--;
    while(matrix[i1][xmin] != 0 && xmin>=0)
    {
        xmin = xmin-1;
    }

//    cout << "YMaX: " <<  xmax << endl;
//    cout << "YMin: " <<  xmin << endl;

    int x2 = xmax;
    int x1 = xmin;

    int dx = x2 - x1 ;
    int dy = y2 - y1 ;
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
    if (dy<0){
        dy1 = -1 ;
    }
    else if (dy>0){
        dy1 = 1 ;
    }
    if (dx<0) {
        dx1 = -1;
    }
    else if (dx>0){
        dx1 = 1 ;}
    if (dy<0){
        dy2 = -1;
    }
    else if (dy>0){
        dy2 = 1 ;
    }
    int longest = abs(dy) ;
    int shortest = abs(dx) ;
    if (!(longest>shortest)) {
        longest = abs(dx) ;
        shortest = abs(dy) ;
        if (dx<0)
        {
            dx2 = -1 ;
        }

        else if (dx>0) {
            dx2 = 1;
        }
        dy2 = 0 ;
    }
    int numerator = longest >> 1 ;

    for (int i=0;i<=longest;i++) {
        matrix[y1][x1] = 0;
        numerator += shortest ;
        if (!(numerator<longest)) {
            numerator -= longest ;
            x1 += dx1 ;
            y1 += dy1 ;
        } else {
            x1 += dx2 ;
            y1 += dy2 ;
        }
    }

}


void drawLine(int x1, int y1, int x2, int y2)//int x0, int y0, int x1, int y1)
{

    int dx = x2 - x1 ;
    int dy = y2 - y1 ;
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
    if (dy<0){
        dy1 = -1 ;
    }
    else if (dy>0){
        dy1 = 1 ;
    }
    if (dx<0) {
        dx1 = -1;
    }
    else if (dx>0){
        dx1 = 1 ;}
    if (dy<0){
        dy2 = -1;
    }
    else if (dy>0){
        dy2 = 1 ;
    }
    int longest = abs(dy) ;
    int shortest = abs(dx) ;
    if (!(longest>shortest)) {
        longest = abs(dx) ;
        shortest = abs(dy) ;
        if (dx<0)
        {
            dx2 = -1 ;
        }

        else if (dx>0) {
            dx2 = 1;
        }
        dy2 = 0 ;
    }
    int numerator = longest >> 1 ;

    for (int i=0;i<=longest;i++) {
        matrix[y1][x1] = 0;
        numerator += shortest ;
        if (!(numerator<longest)) {
            numerator -= longest ;
            x1 += dx1 ;
            y1 += dy1 ;
        } else {
            x1 += dx2 ;
            y1 += dy2 ;
        }
    }

}


void drawCircle(double r, double xcenter, double ycenter, int color){
    int x = 0, y, xmax, y2, y2_new, ty;
    xmax = (int) (r * 0.70710678); // maximum x at radius/sqrt(2)

    y = r;

    y2 = y * y;
    ty = (2 * y) - 1;
    y2_new = y2;



    for (x = 0; x <= xmax ; x++) {



        if ((y2 - y2_new) >= ty) {
            y2 -= ty;
            y -= 1;
            ty -= 2;
        }


        if(xcenter + x < 800 && ycenter + y < 800 && xcenter + x > 0 && ycenter + y > 0 )
            matrix[(int) (ycenter + y)][(int) (xcenter + x)] = color;

        if(xcenter + x < 800 && ycenter - y < 800 && xcenter + x > 0 && ycenter - y > 0  )
            matrix[(int) (ycenter - y)][(int) (xcenter + x)] = color;

        if(xcenter - x < 800 && ycenter + y < 800 && xcenter - x > 0 && ycenter + y > 0 )
            matrix[(int) (ycenter + y)][(int) (xcenter - x)] = color;

        if(xcenter - x < 800 && ycenter - y < 800 && xcenter - x > 0 && ycenter - y > 0 )
            matrix[(int) (ycenter - y)][(int) (xcenter - x)] = color;

        if(xcenter + y < 800 && ycenter + x < 800 && xcenter + y > 0 && ycenter + x > 0)
            matrix[(int) (ycenter + x)][(int) (xcenter + y)] = color;

        if(xcenter + y < 800 && ycenter - x < 800 && xcenter + y > 0 && ycenter - x > 0)
            matrix[(int) (ycenter - x)][(int) (xcenter + y)] = color;

        if(xcenter - y < 800 && ycenter + x < 800 && xcenter - y > 0 && ycenter + x > 0  )
            matrix[(int) (ycenter + x)][(int) (xcenter - y)] = color;

        if(xcenter - y < 800 && ycenter - x < 800 && xcenter - y > 0 && ycenter - x > 0 )
            matrix[(int) (ycenter - x)][(int) (xcenter - y)] = color;


        y2_new -= (2 * x) - 3;
    }
}
