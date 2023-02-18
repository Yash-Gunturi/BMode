#include "BmodeClass.h"
using namespace std;

BmodeClass::BmodeClass()
{
    // Variables for calculations
    imparams = NULL;
    RFData = NULL;
    next = NULL;
    line = 0;
}

BmodeClass::BmodeClass(imageParam *params,dataBuffer *data,int numline)
{
    // Variables for calculaions
    imparams = params;
    RFData = data;
    line = numline;
    scanline = createScanline(imparams->getNumPixel()); // Allocating memory for Scanline by using createScanline
    beamform(); // Beamforming the scanline W
}

BmodeClass::~BmodeClass()
{
    deleteScanline(); // Deleting all dynamically allocated memory for scanline 
}

float *BmodeClass::createScanline(int numPixel)
{
    // New float pointer array used to assign an array to it
    float *mem = new float [numPixel];
    return mem;
}

void BmodeClass::beamform()
{
    // Variables for calculations
    float tforward = 0;
    float tbackward = 0;
    float ttotal = 0;
    float sample = 0;

    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        // Setting variables to 0 before calculations
        float PReal = 0;
        float Pimag = 0;    
        // Calculations used to find variables same as in AMode 
        for (int j = 0; j < imparams->getNumElement(); j++)
        {
            tforward = (imparams->getYPosition(line,i))/(imparams->SOS);

            tbackward = (sqrt(pow(imparams->getYPosition(line,i), 2) + (pow(imparams->getXPosition(line,i) - imparams->getElementPosition(j), 2))))/(imparams->SOS);

            ttotal = tforward + tbackward;

            sample = floor(ttotal * (imparams->FS));

            // Ending the loop if it runs more than the number of samples 
            if (sample > imparams->getNumSample())
            {
                cerr << "Invalid sample number" << endl;
                break;
            }

            // Incrementing PReal/Pimag each time         
            if (sample < imparams->getNumSample())
            {
            PReal += (RFData->getRealRFData(j, sample));
            
            Pimag += (RFData->getImagRFData(j, sample));
            }
        }

        scanline[i] = sqrt(pow(PReal, 2) + pow(Pimag, 2));
    }
    
}

void BmodeClass::getScanline(float *data)
// Copy Pastes all data from scanline into data
{
    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        data[i] = scanline[i];
    }
    
}

void BmodeClass::deleteScanline()
// removes all memory in scanline
{
    delete scanline;
}