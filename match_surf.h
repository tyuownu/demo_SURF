/*
 Header of the match file for SURF
 
 Copyright 2013: Edouard Oyallon, Julien Rabin
 
 Version for IPOL.
 */

#ifndef MATCH
#define MATCH


#include "descriptor.h"

#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;


// Return descriptor using the txt file generated by extract_surf
listDescriptor* getDescriptorFromRawFile(string nameFile);

listDescriptor* getDescriptorFromRawFile(string nameFile)
{
    // Read each line of a text file
    ifstream infile(nameFile.c_str());
    listDescriptor* listDesc=new listDescriptor();
    int k=0;
    while (infile)
    {
        
        // Two first rows are not useful
        if(k<2)
        {
            k++;
            continue;
        }
        string line;
        if (!getline( infile, line )) break;
        istringstream ss( line );
        
        int i=0;
        keyPoint* kp=new keyPoint();
        descriptor* desc=new descriptor();
        desc->kP=kp;
        
        while (ss)
        {
            
            // x y scale orientation d1 ... d64 signLaplacian
            string word;
            if (!getline( ss, word, ' ' )) break;
            if(i==0)
                kp->x=strtod(word.c_str(),NULL);
            else if(i==1)
                kp->y=strtod(word.c_str(),NULL);
            else if(i==2)
                kp->scale=strtod(word.c_str(),NULL);
            else if(i==3)
                kp->orientation=strtod(word.c_str(),NULL);
            else if(i==68)
                kp->signLaplacian=strtod(word.c_str(),NULL);
			else if(i==69)
				kp->integral_ty=strtod(word.c_str(),NULL);
            else
            {
                int j=(i-4)/4;
                int k=(i-4)%4;
                switch(k)
                {
                    case 0:
                        ((desc->list)[j]).sumDx=strtod(word.c_str(),NULL);
                        break;
                    case 1:
                        ((desc->list)[j]).sumDy=strtod(word.c_str(),NULL);
                        break;
                    case 2:
                        ((desc->list)[j]).sumAbsDx=strtod(word.c_str(),NULL);
                        break;
                        
                    case 3:
                        ((desc->list)[j]).sumAbsDy=strtod(word.c_str(),NULL);
                        break;
                }
            }

            i++;
        }
     
        listDesc->push_back(desc);
    }
    return listDesc;
}

#endif
