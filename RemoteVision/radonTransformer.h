/************************************************************************************
 *	Radon Transform Implmentation
 *	-----------------------------
 *	code by : bobby anguelov - banguelov@cs.up.ac.za
 *	downloaded from : takinginitiative.wordpress.org
 *
 *	code is free for use in whatever way you want, however if you work for a game
 *	development firm you are obliged to offer me a job :P (haha i wish)
 ************************************************************************************/
#ifndef _RADONTRANSFORMER
#define _RADONTRANSFORMER

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

// define PI
#ifndef PI
#define PI 3.14159265358979323846
#endif

using namespace std;

//pixel helper struct
struct pixel
{
    int x, y;
};

//should be a singleton class
class radonTransformer
{

private:

    //preprocessed expressions
    float cos45, sin45, cos22, sin22, sec22, cos67, sin67, sqrt2, halfsqrt2, halfsqrt2divsin22, doublesqrt2;

    //number of beams - odd number to ensure symmetry when centroid is projected on the middle beam
    //static const int halfBeams = 25, beams = 2*halfBeams + 1;
    static const int halfBeams = 5, beams = 2*halfBeams + 1;

    //other variables
    int numPixels, subBeams, totalSubBeams, halfSubBeams, centroid[2];
    float radius, beamWidth;

    //Pixel Contributions Storage
    float sbTotals[8][100000];		//fixed size to avoid allocation of memory during each step (max 1000 sub-beams)
    float bTotals[8][beams];

public:

    radonTransformer()
    {
        //initialize math variables once
        sqrt2 = sqrt(2.0);
        halfsqrt2 = 0.5 * sqrt2;
        halfsqrt2divsin22 = 0.5 * sqrt2 / sinf(PI/8);
        doublesqrt2 = 2 * sqrt2;
        cos45 = sqrt2/2;
        sin45 = cos45;
        cos22 = cosf(PI/8);
        sin22 = sinf(PI/8);
        sec22 = 1/cos22;
        cos67 = cosf(3*PI/8);
        sin67 = sinf(3*PI/8);
    }

    //tranforms the object provided into its radon representation
    void transform(vector<pixel> object)
    {
        //prepare for projections
        prepare(object);

        //for each pixel
        for ( int i=0; i < numPixels; i++ )
        {
            project0degrees(object[i]);
            project22degrees(object[i]);
            project45degrees(object[i]);
            project67degrees(object[i]);
            project90degrees(object[i]);
            project112degrees(object[i]);
            project135degrees(object[i]);
            project157degrees(object[i]);
        }

        //convert to 50 beam final result
        formatsbTotals();
    }

    //get totals
    float* getTotals() { return &bTotals[0][0]; }

private:

    void calculateCentroid( vector<pixel> object )
    {
        int sumX = 0, sumY = 0;

        //sum all x and y values for all pixels
        for ( int i = 0; i < numPixels; i++)
        {
            sumX += object[i].x;
            sumY += object[i].y;
        }

        //centroid is the average position
        centroid[0] = sumX / numPixels;
        centroid[1] = sumY / numPixels;
    }

    void calculateRadius( vector<pixel> object )
    {
        //set radius to 0
        radius = 0;

        //find the max length from centroid to a pixel
        for ( int i = 0; i < numPixels; i++)
        {
            //euclidian distance from pixel to centroid (no sqrt for performance reasons)
            float len = pow((double)(object[i].x - centroid[0]), 2) + pow((double)(object[i].y - centroid[1]), 2);

            //set radius to longest distance found
            radius = max(radius, len);
        }

        //calculate radius (include missing sqrt from above) to a midpoint of a pixel
        //Note: since distance is to midpoint add sqrt2/2 (approximation)
        radius = sqrt((float)radius) + halfsqrt2;
    }

    void prepare(vector<pixel> object)
    {
        //get number of pixels
        numPixels = object.size();

        //calculate centroid
        calculateCentroid( object );

        //calculate radius
        calculateRadius( object );

        //calculate sub-beams (estimation where there are 5 sub-beams per pixel)
        subBeams = 2 * ceil( (10 * radius + halfBeams + 1) / beams ) + 1;
        totalSubBeams = beams * subBeams;
        halfSubBeams = (totalSubBeams - 1) / 2;

        //for each projection clear result storage
        for (int i=0; i<8; i++)
        {
            //clear sub-beam totals
            for ( int j=0; j < totalSubBeams; j++ ) sbTotals[i][j] = 0 ;

            //clear beam totals
            for ( int j=0; j < beams; j++ ) bTotals[i][j] = 0 ;
        }

        //calculate beam width
        beamWidth = radius / halfSubBeams;

    /*	//debug: print radon details of object
        cout << "Radius: " << radius << endl;
        cout << "numPixels: " << numPixels << endl;
        cout << "totalSubBeams: " << totalSubBeams << endl;
        cout << "Centroid: " << centroid[0] << ":" << centroid[1] << endl;
        cout << "beamWidth: " << beamWidth << endl << endl;*/
    }

    //*****************************************************************************************************************************************
    //*	PROJECTION FUNCTIONS - 8 projections -> 0 to 157.5 degrees in 22.5 degree increments
    //*****************************************************************************************************************************************

    void project0degrees(pixel point)	//horizontal
    {
        //projection of center of pixel on new axis
        float c = (point.x - centroid[0]) / beamWidth;

        //rounded projected left and right corners of pixel
        int l = ceil( c - 0.5/beamWidth ) + halfSubBeams;
        int r = floor( c + 0.5/beamWidth ) + halfSubBeams;

        //add contributions to sub-beams
        for ( int i=l; i<=r; i++ )
        {
            sbTotals[0][i] += 1;
        }
    }

    void project22degrees(pixel point)
    {
        //projected left & right corners of pixel
        float cl = ( (point.y - centroid[1] - 0.5) * cos22 + (point.x - centroid[0] - 0.5 ) * sin22 ) / beamWidth;
        float cr = ( (point.y - centroid[1] + 0.5) * cos22 + (point.x - centroid[0] + 0.5 ) * sin22 ) / beamWidth;

        //average of cl and cr (center point of pixel)
        float c = (cl + cr) / 2;

        //rounded values - left and right sub-beams affected
        int l = ceil( cl ) + halfSubBeams;
        int r = floor( cr ) + halfSubBeams;

        //length of incline
        float incl = floor(0.293 * (cr - cl + 1) );

        //add contributions to sub-beams
        for ( int i=l; i<=l+incl-1; i++ )
        {
            sbTotals[1][i] += halfsqrt2divsin22 - doublesqrt2 * abs( i - halfSubBeams - c) * beamWidth;
        }

        for ( int i=l+incl; i<=r-incl; i++ )
        {
            sbTotals[1][i] += sec22;
        }

        for ( int i=r-incl+1; i<=r; i++ )
        {
            sbTotals[1][i] += halfsqrt2divsin22 - doublesqrt2*abs( i - halfSubBeams - c) * beamWidth;
        }
    }

    void project45degrees(pixel point)
    {
        //projected left & right corners of pixel
        float cl = ( (point.y - centroid[1] - 0.5) * cos45 + (point.x - centroid[0] - 0.5 ) * sin45 ) / beamWidth;
        float cr = ( (point.y - centroid[1] + 0.5) * cos45 + (point.x - centroid[0] + 0.5 ) * sin45 ) / beamWidth;

        //average of cl and cr (center point of pixel)
        float c = (cl + cr) / 2;

        //rounded values - left and right sub-beams affected
        int l = ceil( cl ) + halfSubBeams;
        int r = floor( cr ) + halfSubBeams;

        //add contributions to sub-beams
        for ( int i=l; i<=r; i++ )
        {
            sbTotals[2][i] += sqrt2 - 2*abs( i - halfSubBeams - c) * beamWidth;
        }
    }

    void project67degrees(pixel point)
    {
        //projected left & right corners of pixel
        float cl = ( (point.y - centroid[1] - 0.5) * cos67 + (point.x - centroid[0] - 0.5 ) * sin67 ) / beamWidth;
        float cr = ( (point.y - centroid[1] + 0.5) * cos67 + (point.x - centroid[0] + 0.5 ) * sin67 ) / beamWidth;

        //average of cl and cr (center point of pixel)
        float c = (cl + cr) / 2;

        //rounded values - left and right sub-beams affected
        int l = ceil( cl ) + halfSubBeams;
        int r = floor( cr ) + halfSubBeams;

        //length of incline
        float incl = floor(0.293 * (cr - cl + 1) );

        //add contributions to sub-beams
        for ( int i=l; i<=l+incl-1; i++ )
        {
            sbTotals[3][i] += halfsqrt2divsin22 - doublesqrt2*abs( i - halfSubBeams - c) * beamWidth;
        }

        for ( int i=l+incl; i<=r-incl; i++ )
        {
            sbTotals[3][i] += sec22;
        }

        for ( int i=r-incl+1; i<=r; i++ )
        {
            sbTotals[3][i] += halfsqrt2divsin22 - doublesqrt2*abs( i - halfSubBeams - c) * beamWidth;
        }
    }

    void project90degrees(pixel point)
    {
        //projection of center of pixel on new axis
        float c = (point.y - centroid[1]) / beamWidth;

        //rounded projected left and right corners of pixel
        int l = ceil( c - 0.5/beamWidth ) + halfSubBeams;
        int r = floor( c + 0.5/beamWidth ) + halfSubBeams;

        //add contributions to sub-beams
        for ( int i=l; i<=r; i++ )
        {
            sbTotals[4][i] += 1;
        }
    }

    void project112degrees(pixel point)
    {
        //projected left & right corners of pixel
        float cl = ( -(point.y - centroid[1] + 0.5) * cos22 + (point.x - centroid[0] - 0.5 ) * sin22 ) / beamWidth;
        float cr = ( -(point.y - centroid[1] - 0.5) * cos22 + (point.x - centroid[0] + 0.5 ) * sin22 ) / beamWidth;

        //average of cl and cr (center point of pixel)
        float c = (cl + cr) / 2;

        //rounded values - left and right sub-beams affected
        int l = ceil( cl ) + halfSubBeams;
        int r = floor( cr ) + halfSubBeams;

        //length of incline
        float incl = floor(0.293 * (cr - cl + 1) );

        //add contributions to sub-beams
        for ( int i=l; i<=l+incl-1; i++ )
        {
            sbTotals[5][i] += halfsqrt2divsin22 - doublesqrt2*abs( i - halfSubBeams - c) * beamWidth;
        }

        for ( int i=l+incl; i<=r-incl; i++ )
        {
            sbTotals[5][i] += sec22;
        }

        for ( int i=r-incl+1; i<=r; i++ )
        {
            sbTotals[5][i] += halfsqrt2divsin22 - doublesqrt2*abs( i - halfSubBeams - c) * beamWidth;
        }
    }

    void project135degrees(pixel point)
    {
        //projected left & right corners of pixel
        float cl = ( -(point.y - centroid[1] + 0.5) * cos45 + (point.x - centroid[0] - 0.5 ) * sin45 ) / beamWidth;
        float cr = ( -(point.y - centroid[1] - 0.5) * cos45 + (point.x - centroid[0] + 0.5 ) * sin45 ) / beamWidth;

        //average of cl and cr (center point of pixel)
        float c = (cl + cr) / 2;

        //rounded values - left and right sub-beams affected
        int l = ceil( cl ) + halfSubBeams;
        int r = floor( cr ) + halfSubBeams;

        //add contributions to sub-beams
        for ( int i=l; i<=r; i++ )
        {
            sbTotals[6][i] += sqrt2 - 2*abs( i - halfSubBeams - c) * beamWidth;
        }
    }

    void project157degrees(pixel point)
    {
        //projected left & right corners of pixel
        float cl = ( -(point.y - centroid[1] + 0.5) * cos67 + (point.x - centroid[0] - 0.5 ) * sin67 ) / beamWidth;
        float cr = ( -(point.y - centroid[1] - 0.5) * cos67 + (point.x - centroid[0] + 0.5 ) * sin67 ) / beamWidth;

        //average of cl and cr (center point of pixel)
        float c = (cl + cr) / 2;

        //rounded values - left and right sub-beams affected
        int l = ceil( cl ) + halfSubBeams;
        int r = floor( cr ) + halfSubBeams;

        //length of incline
        float incl = floor(0.293 * (cr - cl + 1) );

        //add contributions to sub-beams
        for ( int i=l; i<=l+incl-1; i++ )
        {
            sbTotals[7][i] += halfsqrt2divsin22 - doublesqrt2*abs( i - halfSubBeams - c) * beamWidth;
        }

        for ( int i=l+incl; i<=r-incl; i++ )
        {
            sbTotals[7][i] += sec22;
        }

        for ( int i=r-incl+1; i<=r; i++ )
        {
            sbTotals[7][i] += halfsqrt2divsin22 - doublesqrt2*abs( i - halfSubBeams - c) * beamWidth;
        }
    }

    //*****************************************************************************************************************************************
    //*	Convert sub-beam sbTotals into beam sbTotals -> return 50 beams
    //*****************************************************************************************************************************************

    void formatsbTotals()
    {
        float scalingFactor = beamWidth / numPixels;

        //for each projection
        for ( int h=0; h < 8; h++ )
        {
            //beam counter
            int beam = 0;

            //for each beam grouping
            for ( int i=0; i < totalSubBeams; i += subBeams )
            {
                float sum = 0;

                //add all the beams together in grouping
                for ( int j=i; j < i + subBeams; j++ ) sum += sbTotals[h][j];

                //store in final result with scaling
                bTotals[h][beam] = sum * scalingFactor;
                beam++;
            }
        }

        /*//debug: print sum of beams
        for ( int h=0; h < 8; h++ )
        {
            float sum = 0;

            for (int i=0; i<beams; i++)
            {
                sum += bTotals[h][i];
            }

            cout << "Projection " << h << ": " << sum << endl;
        }*/
    }
};

#endif
