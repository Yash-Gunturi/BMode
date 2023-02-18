#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    // Variables for calculations
    numElement = 0;
    numSample = 0;
    scanline = 0;
    dataMatrix = NULL;
    next = NULL;
}

dataBuffer::dataBuffer(std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{   // Creating new varibales that correlate to previous variables
    numElement = inputNumElement;
    numSample = inputNumSample;
    scanline = inputScanline;
    dataMatrix = createDataMatrix();
    loadRFData(dataMatrix, imagFile, realFile); // populating the dataMatrix, imagFile and realFile are two ifstream pointers that point to the file object for data reading

} 

dataBuffer::~dataBuffer()
{
    deleteDataMatrix(); // Deleting memory in dataMatrix
}

complex **dataBuffer::createDataMatrix()
{
    complex **RFData = new complex *[numElement];

    // Creating an array with length of numElement to RFData
    for (int i = 0; i < numElement; i++)
    {
        RFData[i] = new complex[numSample];
    }

    return RFData;
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 
    // Assigning an intial value to real and imag for the input file data
    char real[50];
    char imag[50];

    // Getting data from txt files
    for (int i = 0; i < numElement; i++)
    {
        for (int j = 0; j < numSample; j++)
        {
            imagFile->getline(imag, 50);
            realFile->getline(real, 50);

            RFData[i][j].imag = atof(imag);
            RFData[i][j].real = atof(real);
        }
    }

    return 0;
}

float dataBuffer::getRealRFData(int element,int sample)
{
    return dataMatrix[element][sample].real; // Return the real component stored in dataMatrix
}
float dataBuffer::getImagRFData(int element,int sample)
{
    return dataMatrix[element][sample].imag; // Return the imag component stored in dataMatrix
}

void dataBuffer::deleteDataMatrix()
// Deleting memory in dataMatrix
{
    for (int i = 0; i < numElement; i++)
    {
        delete dataMatrix[i];
    }
    delete dataMatrix;
}




