#include "imageParam.h"
using namespace std;

imageParam::imageParam()
{
    // Variables for calculations
    numElement = 128;
    numSample = 3338;
    numScanline = 127;
    elementPosition = genElementPosition();
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition);
}

imageParam::~imageParam()
// Deletes memory for elementPosition and scanlinePosition
{
    deletePositionArray();
}

float *imageParam::genElementPosition()
{
    // Creating pointer elementPosition and create a new array for it
    float *elementPosition;
    elementPosition = new float [numElement];

    // Creating numElement amount of elementPosition 
    for (int n = 0; n < numElement; n++)
    {
        elementPosition[n] = ((n - (((float)numElement - 1) / 2)) * PITCH);
    }
    return elementPosition;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float* elementLocation)
{
    //Asking for user input 
    cout << "Depth" << endl;
    cin >> desiredDepth;

    cout << "Number of pixels" << endl;
    cin >> numPixel;

    // Incrementing variable 
    float increment = desiredDepth / (numPixel - 1);
    
    // New double pointer scanlinePosition that gets assignned to float2 that has a size of numScanline
    float2 **scanlinePosition = new float2 *[numScanline];

    // Finding lateral postion of the nth scanline value 
    for (int n = 0; n < numScanline; n++)
    {
        scanlinePosition[n] = new float2[numPixel];
        for (int i = 0; i <= numPixel; i++)
        {
            scanlinePosition[n][i].x = (n - ((numScanline - 1) / 2)) * PITCH;
            scanlinePosition[n][i].y = i * increment;
        }
    }
    
    return scanlinePosition;

}

float imageParam::getXPosition(int scanline, int pixel)
// Return the x-coordinate of a pixel
{
    return scanlinePosition[scanline][pixel].x; 
}

float imageParam::getYPosition(int scanline, int pixel)
// Return the y-coordinate of a pixel
{
    return scanlinePosition[scanline][pixel].y;
}

float imageParam::getElementPosition(int element)
// Return the position of an element 
{
    return elementPosition[element];
}

// IReturn the private data components of the class
int imageParam::getNumElement()
{
    return numElement;
}

int imageParam::getNumSample()
{
    return numSample;
}

int imageParam::getNumScanline() 
{
    return numScanline;
}

int imageParam::getNumPixel() 
{
    return numPixel;
}

// Deleting memory allocated for scanlinePosition and elementPosition
void imageParam::deletePositionArray()
{
    delete elementPosition;

    for (int i = 0; i < numScanline; i++)
    {
        delete scanlinePosition[i];
    }

    delete scanlinePosition;

}









