#include <GL/glut.h>
#include "object.hpp"
#include "edit.hpp"
#include "file.hpp"
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

#define GL_BGR_EXT 0x80E0
#define GL_BGR     0x80E0
#define GL_BGRA    0x80E1

std::string extractValue(std::string line) {
    size_t firstQuotePos = line.find('"');
    
    if (firstQuotePos != std::string::npos) {
        // Find the position of the second quote after the first quote
        size_t secondQuotePos = line.find('"', firstQuotePos + 1);
        
        if (secondQuotePos != std::string::npos) {
            // Extract the value between the quotes
            std::string extractedValue = line.substr(firstQuotePos + 1, secondQuotePos - firstQuotePos - 1);
            return extractedValue;       
        }
    }
}

int convertInt(std::string str){
    int temp;
    std::stringstream ss(str);
    ss >> temp;
    return temp;
}

int exportBitmap(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight) 
{
	FILE *fp = fopen(ptrcFileName, "wb");
	if (fp == NULL) {
		return 0;
	}
		
	// allocate memory to store image data
	int bitsize = nWidth*nHeight*3 +  ((3*nWidth)%4 == 0 ? 0 : (4-(3*nWidth)%4)*nHeight);
		
	unsigned char *ptrImage = (unsigned char*) malloc(bitsize);
	if (ptrImage == NULL) {
		fclose(fp);
		return 0;
	}
	
	//read pixels from frame buffer, byte order is BGR	
	glReadPixels(nX, nY, nWidth, nHeight, GL_BGR, GL_UNSIGNED_BYTE, ptrImage);

	// clean memory buffer of bitmap header and information header
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	memset(&bfh, 0, sizeof(bfh));
	memset(&bih, 0, sizeof(bih));

	// set the bitmap header with the give parameters
	bfh.bfType = 0x4d42; // 'MB'
	bfh.bfSize = sizeof(bfh) + sizeof(bih) + bitsize;
	bfh.bfOffBits = sizeof(bfh) + sizeof(bih);
	
    // set bitmap information header 
	bih.biSize = sizeof(bih);
	bih.biWidth = nWidth + nWidth%4;
	bih.biHeight = nHeight;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biSizeImage = bitsize;

	// write to file
	if (fwrite(&bfh, sizeof(bfh), 1, fp) < 1) {
		free(ptrImage);
		fclose(fp);
		return 0;
	};
	
	if (fwrite(&bih, sizeof(bih), 1, fp)<1) {
		free(ptrImage);
		fclose(fp);
		return 0;
	}

	if ( fwrite(ptrImage, 1, bitsize, fp) < bitsize ) {
		free(ptrImage);
		fclose(fp);
		return 0;
	}
	
	fclose(fp);
	free(ptrImage);
	
	return 1;
}

int exportSVG(const char *filename, node* head, int winWidth, int winHeight){
    // Open an SVG file for writing
    std::ofstream svgFile("output.svg");

    // Check if the file is successfully opened
    if (!svgFile.is_open()) {
        return 1;
    }

    // Write the SVG header
    svgFile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << std::endl;
    svgFile << "<svg width=\"" << winWidth  << "\" height=\"" << winHeight << "\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;

    // Draw a red rectangle
    node* current = head;
    while (current != NULL) {

        char color[20];
        if (current-> red == 0 && current->green == 0 && current->blue == 0) { sprintf(color, "black"); } 
        else if (current->red == 1 && current->green == 1 &&  current->blue == 1) { sprintf(color, "white"); } 
        else if (current->red == 1 &&  current->green == 0 &&  current->blue == 0) { sprintf(color, "red"); } 
        else if (current->red == 0 &&  current->green == 1 &&  current->blue == 0) { sprintf(color, "green"); } 
        else if (current->red == 0 &&  current->green == 0 &&  current->blue == 1) { sprintf(color, "blue"); }

        char strokeColor[20];
        if (current->strokeRed == 0 &&  current->strokeGreen == 0 &&  current->strokeBlue == 0) { sprintf(strokeColor, "black"); }
        else if (current->strokeRed == 1 &&  current->strokeGreen == 1 &&  current->strokeBlue == 1) { sprintf(strokeColor, "white"); }
        else if (current->strokeRed == 1 &&  current->strokeGreen == 0 &&  current->strokeBlue == 0) { sprintf(strokeColor, "red"); }
        else if (current->strokeRed == 0 &&  current->strokeGreen == 1 &&  current->strokeBlue == 0) { sprintf(strokeColor, "green"); }
        else if (current->strokeRed == 0 &&  current->strokeGreen == 0 &&  current->strokeBlue == 1) { sprintf(strokeColor, "blue"); }

        if (current->isRectangle) {

            int minX; int minY; int width; int height;
            if (current->x1 > current->x2) {minX = current->x2; width = current->x1 - current->x2;}
            else {minX = current->x1; width = current->x2 - current->x1;}

            if (current->y1 > current->y2) {minY = current->y2; height = current->y1 - current->y2;}
            else {minY = current->y1; height = current->y2 - current->y1;}

            svgFile << "<rect width=\"" << width << "\" height=\"" << height << "\" x=\"" << minX << "\" y=\"" << (winHeight - minY - height ) << "\" fill=\"" << color << "\" stroke=\"" << strokeColor << "\" stroke-width=\"" << current->strokeWidth << "\" />" << std::endl;

        } else {
            int trueY = winHeight - current->y1;
            svgFile << "<circle cx=\"" << current->x1 << "\" cy=\"" << winHeight - current->y1 << "\" r=\"" << current->radius << "\" fill=\"" << color << "\" stroke=\"" << strokeColor << "\" stroke-width=\"" << current->strokeWidth << "\" />" << std::endl;
        }

        current = current->prev;
    }

    // Close the SVG tag
    svgFile << "</svg>" << std::endl;

    // Close the file
    svgFile.close();

    std::cout << "SVG file created successfully." << std::endl;

    return 0;
}

int importSVG(const char *filename) {

    std::ifstream svgFile(filename);
    if (!svgFile.is_open()) { return 0; }

    // listPtr->destroy();
    listPtr->head = NULL;
    listPtr->tail = NULL;

    std::string line;
    int winWidth; int winHeight;
    std::string token;
    std::string value;
    bool inWindowDefLine; bool inRectangleLine; bool inCircleLine;

    while (std::getline(svgFile, line)) {
        
        node *node = new Node;
        std::string delimiter = " ";
        size_t pos = 0;
        int x = -1;  int y = -1; int width = -1;  int height = -1;  int radius = -1;

        inWindowDefLine = line.find("svg") != std::string::npos;
        inRectangleLine = line.find("rect") != std::string::npos;
        inCircleLine = line.find("circle") != std::string::npos;

        while ((pos = line.find(delimiter)) != std::string::npos && (inRectangleLine || inCircleLine || inWindowDefLine)) {

            token = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());

            if (inWindowDefLine) { // Line for window dimensions
                if (token.find("svg") != std::string::npos) {
                    value = "";
                } else {
                    value = extractValue(token); 
                }
                
                if (token.find("width") != std::string::npos) { winWidth = convertInt(value); } 
                else if (token.find("height") != std::string::npos) { winHeight = convertInt(value); }
            } 
            else { // Parse shape data

                if (token.find("rect") != std::string::npos || token.find("circle") != std::string::npos) {
                    value = "";
                } else {
                    value = extractValue(token); 
                }

                if (token.find("fill") != std::string::npos) { // Get generic shape color
                    if (value == "red") { node->red = 1; node->green = 0; node->blue = 0; }
                    else if (value == "green") { node->red = 0; node->green = 1; node->blue = 0; }
                    else if (value == "blue") { node->red = 0; node->green = 0; node->blue = 1; }
                    else if (value == "black") { node->red = 0; node->green = 0; node->blue = 0; }
                    else if (value == "white") { node->red = 1; node->green = 1; node->blue = 1; }
                }  
                else if (token.find("stroke-width") != std::string::npos) { // Get stroke width
                    node->strokeWidth = convertInt(value); 
                }
                else if (token.find("stroke") != std::string::npos) { // Get stroke color
                    if (value == "red") { node->strokeRed = 1; node->strokeGreen = 0; node->strokeBlue = 0; }
                    else if (value == "green") { node->strokeRed = 0; node->strokeGreen = 1; node->strokeBlue = 0; }
                    else if (value == "blue") { node->strokeRed = 0; node->strokeGreen = 0; node->strokeBlue = 1; }
                    else if (value == "black") { node->strokeRed = 0; node->strokeGreen = 0; node->strokeBlue = 0; }
                    else if (value == "white") { node->strokeRed = 1; node->strokeGreen = 1; node->strokeBlue = 1; }
                } 

                if (inRectangleLine) {
                    if (token.find("width") != std::string::npos && token.find("stroke") == std::string::npos) { width = convertInt(value); }  
                    else if (token.find("height") != std::string::npos) { height = convertInt(value); }
                    else if (token.find("x") != std::string::npos) { x = convertInt(value); }
                    else if (token.find("y") != std::string::npos) { y = convertInt(value); }

                } else if (inCircleLine) {
                    if (token.find("cx") != std::string::npos) { x = convertInt(value); }
                    else if (token.find("cy") != std::string::npos) { y = convertInt(value); }
                    else if (token.find("r=") != std::string::npos) { radius = convertInt(value); }
                }
            }
        }

        if (width != -1 && height != -1 && x != -1 && y != -1) {
            std::cout << "RRR x: " << x << " y: " << y << " width: " << width << " height: " << height << std::endl;
            node->x1 = x; 
            node->y1 = winHeight - height - y; 

            node->x2 = x + width;
            node->y2 = y + height;
        } else if (x != -1 && y != -1 && radius != -1) {
            std::cout << "CCC x: " << x << " y: " << y << " radius: " << radius << std::endl;
            node->x1 = x; node->y1 = winHeight-y; node->radius = radius;
        }

        insert(listPtr, node);
    }

    svgFile.close();
    return 1;

}
