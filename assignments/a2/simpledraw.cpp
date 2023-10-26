/*
 * Description: Example from textbook chapter 20, GUI menu
 * Compile: g++ opengl_menu.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe
*/
#include <GL/glut.h>
#include <iostream>

GLsizei winWidth = 800, winHeight = 600;      // Initial Display-window size.
GLfloat red = 1.0, green = 1.0, blue = 1.0;   // Initial color values.
GLenum renderingMode = GL_SMOOTH;             // Initial fill method.

class Rectangle {
    public:
        int x1;
        int y1;
        int x2;
        int y2;
        Rectangle(int x1, int y1, int x2, int y2): x1(x1), y1(y1), x2(x2), y2(y2) {
};

class Node {
    public:
        Rectangle *data;
        Node *prev;
        Node *next;
        Node(Rectangle value, Node *prev, Node *next): data(new Rectangle(value)), prev(NULL), next(NULL) {}
};

class DoubleLinkedList {
    private:
        Node* head;
        Node* tail;

    public:
        DoubleLinkedList(): head(NULL), tail(NULL) {}

        void insert(Rectangle rectObject) {
            Node* newNode = new Node(rectObject);
            if (tail == NULL) {
                head = tail = newNode;
            } else {
                tail -> next - newNode;
                newNode -> prev = tail;
                tail = newNode;
            }
        }

        void display() {
            Node* current = head;
            while (current != NULL) {
                std::cout << current -> data << " ";
                current = current -> next;
            }
            std::cout << std::endl;
        }
};

void init (void)
{
   glClearColor (red, green, blue, 1.0);  // Set display-window color to gray.
   glMatrixMode (GL_PROJECTION);
   gluOrtho2D (0.0, 300.0, 0.0, 300.0);
}

void mainMenu(GLint renderingOption)
{
   switch(renderingOption) {
	   case 1:  renderingMode = GL_FLAT;    break;
	   case 2:  renderingMode = GL_SMOOTH;  break;
   }
   glutPostRedisplay( );
}

/*  Draw shape according to the submenu option selected.  */
void drawSubMenu(GLint drawOption)
{
   switch(drawOption) {
	   case 1: // Square
		   break;
       case 2: // Circle
            break;
   }
   glutPostRedisplay( );
}

/*  Set color values according to the submenu option selected.  */
void styleSubMenu(GLint styleOption)
{
   switch(styleOption) {
	   case 1:
		   break;

       case 2:
           break;

       case 3:
           break; 
   }
   glutPostRedisplay( );
}

/*  Set color values according to the submenu option selected.  */
void editSubMenu(GLint colorOption)
{
   switch(colorOption) {
	   case 1:
		   {red = 0.0;  green = 0.0;  blue = 1.0;}
		   break;
   }
   glutPostRedisplay( );
}

/*  Set color values according to the submenu option selected.  */
void fileSubMenu(GLint colorOption)
{
   switch(colorOption) {
	   case 1:
		   {red = 0.0;  green = 0.0;  blue = 1.0;}
		   break;
   }
   glutPostRedisplay( );
}

/*  Set color values according to the submenu option selected.  */
void strokeColorSubMenu(GLint colorOption)
{
   switch(colorOption) {
	   case 1:
		   {red = 0.0;  green = 0.0;  blue = 1.0;}
		   break;
   }
   glutPostRedisplay( );
}

/*  Set color values according to the submenu option selected.  */
void fillColorSubMenu(GLint colorOption)
{
   switch(colorOption) {
	   case 1:
		   {red = 0.0;  green = 0.0;  blue = 1.0;}
		   break;
   }
   glutPostRedisplay( );
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(red, green, blue); // Set color for first two vertices.
   glShadeModel(renderingMode); // Set fill method for triangle.

   glBegin(GL_TRIANGLES);
	   glVertex2i(280, 20);
	   glVertex2i(160, 280);
	   if(renderingMode == GL_SMOOTH)
	   glColor3f(1.0, 0.0, 0.0);  // Set color of last vertex to red.
	   glVertex2i(20, 100);
   glEnd( );

   glFlush( );
}

void reshapeFcn(GLint newWidth, GLint newHeight)
{
   glViewport(0, 0, newWidth, newHeight);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity( );
   gluOrtho2D(0.0, newWidth, 0.0, newHeight);

   displayTriangle( );
   glFlush( );
}

int main(int argc, char **argv)
{
   GLint drawsubMenu;             // Identifier for submenu.
   GLint stylesubMenu;             // Identifier for submenu.
   GLint editsubMenu;             // Identifier for submenu.
   GLint filesubMenu;             // Identifier for submenu.
   GLint strokeColorsubMenu;             // Identifier for submenu.
   GLint fillColorsubMenu;             // Identifier for submenu.

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition(200, 200);
   glutInitWindowSize(winWidth, winHeight);
   glutCreateWindow("Ryan Kim");
   init( );
   glutDisplayFunc(display);

   drawsubMenu = glutCreateMenu(drawSubMenu);
   glutAddMenuEntry("Rectangle", 1);
   glutAddMenuEntry("Circle", 2);

   strokeColorsubMenu = glutCreateMenu(strokeColorSubMenu);
   glutAddMenuEntry("Red", 1);
   glutAddMenuEntry("Green", 2);
   glutAddMenuEntry("Blue", 3);
   
   fillColorsubMenu = glutCreateMenu(fillColorSubMenu);
   glutAddMenuEntry("Red", 1);
   glutAddMenuEntry("Green", 2);
   glutAddMenuEntry("Blue", 3);
   glutAddMenuEntry("Black", 4);

   stylesubMenu = glutCreateMenu(styleSubMenu);
   glutAddMenuEntry("Fill Color", 1);
   glutAddMenuEntry("Stroke Color", 2);
   glutAddMenuEntry("Stroke Width", 3);
   glutAddSubMenu("Fill Color", fillColorsubMenu);
   glutAddSubMenu("Stroke Color", strokeColorsubMenu);

   editsubMenu = glutCreateMenu(editSubMenu);
   glutAddMenuEntry("Select", 1);
   glutAddMenuEntry("Delete", 2);
   glutAddMenuEntry("Move front", 3);
   glutAddMenuEntry("Move back", 4);
   glutAddMenuEntry("Move around", 5);

   filesubMenu = glutCreateMenu(fileSubMenu);
   glutAddMenuEntry("Save SVG", 1);
   glutAddMenuEntry("Open SVG", 2);
   glutAddMenuEntry("Export bitmap", 3);   

   glutCreateMenu(mainMenu);   // Create main pop-up menu.
   glutAddMenuEntry("New", 1);
   glutAddSubMenu("Draw", drawsubMenu);
   glutAddSubMenu("Style", stylesubMenu);

   glutAddSubMenu("Edit", editsubMenu); 
   glutAddSubMenu("File", filesubMenu);
   glutAddMenuEntry("Quit", 2);

   /* Select menu option using right mouse button.  */
   glutAttachMenu(GLUT_RIGHT_BUTTON);
   glutReshapeFunc(reshapeFcn);
   glutMainLoop( );
}
