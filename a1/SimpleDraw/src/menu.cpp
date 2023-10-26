#include "menu.hpp"
#include "file.hpp"
#include "object.hpp"
#include "edit.hpp"
#include <iostream>
#include <GL/glut.h>

bool drawRectangle = true;

/*  Set color values according to the submenu option selected.  */
void editSubMenu(GLint editOption) {

   switch(editOption) {
      case 1: // Enable select mode
         drawMode = false;
         editMode = true;
         dragMode = false;
      case 2: // Delete selected object
         if (listPtr->selectedNode != NULL) {
            remove(listPtr, listPtr->selectedNode);
            listPtr->selectedNode = NULL;
         }
      case 3: // Move front
         if (listPtr->selectedNode != NULL) {
            Node* temp = remove(listPtr, listPtr->selectedNode);
            insert(listPtr ,temp);
         }
         break;
      case 4: // Move back
         if (listPtr->selectedNode != NULL) {
            Node* temp = remove(listPtr, listPtr->selectedNode);
            insertFront(listPtr, temp);
         }
         break;
      case 5: // Move around
         drawMode = false;
         editMode = true;
         dragMode = true;
         break;

   }
   glutPostRedisplay( );
}

/*  Draw shape according to the submenu option selected.  */
void drawSubMenu(GLint drawOption)
{
   drawMode = true;
   editMode = false;
   dragMode = false;
   switch(drawOption) {
	   case 1: {rectMode = true; break; }
	   case 2: {rectMode = false; break; }
   }
   glutPostRedisplay( );
}

/*  Set color values according to the submenu option selected.  */
void styleSubMenu(GLint styleOption) {
   glutPostRedisplay( );
}

/*  Set color values according to the submenu option selected.  */
void fileSubMenu(GLint fileOption)
{
   switch(fileOption) {
	   case 1: // Save SVG
         exportSVG("output.svg", listPtr->head, winWidth, winHeight);
		   break;
      case 2: // Open SVG
         importSVG("output.svg");
         break;
      case 3: // ExportBitmap
         exportBitmap("output.Bmp", 0, 0, winWidth, winHeight);
         break;
   }
   glutPostRedisplay( );
}

/*  Set color values according to the submenu option selected.  */
void strokeColorSubMenu(GLint colorOption)
{
   switch(colorOption) {
	   case 1: // Red
		   {strokeRed = 1.0; strokeGreen = 0.0; strokeBlue = 0.0; break;}
      case 2: // Green
         {strokeRed = 0.0; strokeGreen = 1.0; strokeBlue = 0.0; break;}
      case 3: // Blue
         {strokeRed = 0.0; strokeGreen = 0.0; strokeBlue = 1.0; break;}
      case 4: // White
         {strokeRed = 0.0; strokeGreen = 0.0; strokeBlue = 0.0; break;}
      case 5: // Black
         {strokeRed = 1.0; strokeGreen = 1.0; strokeBlue = 1.0; break;}

   }
   glutPostRedisplay( );
}

/*  Set color values according to the submenu option selected.  */
void strokeWidthSubMenu(GLint sizeOption)
{
   strokeWidth = sizeOption;
   glutPostRedisplay( );
}

/*  Set color values according to the submenu option selected.  */
void fillColorSubMenu(GLint colorOption)
{
   switch(colorOption) {
      case 1: // Red
         {red = 1.0; green = 0.0; blue = 0.0; break;}
      case 2: // Green
         {red = 0.0; green = 1.0; blue = 0.0; break;}
      case 3: // Blue
         {red = 0.0; green = 0.0; blue = 1.0; break;}
      case 4: // White
         {red = 0.0; green = 0.0; blue = 0.0; break;}
      case 5: // Black
         {red = 1.0; green = 1.0; blue = 1.0; break;}
   }
   glutPostRedisplay( );
}
