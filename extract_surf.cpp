/*
    Keypoint extractor file for SURF
 
    Copyright 2013: Edouard Oyallon, Julien Rabin
 
    Version for IPOL.
*/

#include "extract_surf.h"
using namespace std;

// Should be execute as surf file1.png descriptors.txt
int main(int argc, char** argv)
{
    
    // Image input
	string imgName=argv[1];
    // Descriptors output txt
    string txtFile=argv[2];
    
    size_t nx,ny;
    unsigned char* data;
    
    // Threshold on the Hessian
    float threshold=1000;
    if(argc==4)
        threshold=atoi(argv[4]);; // You can modify the threshold for the detection of the Hessian
    if(argc>4)
    {
        cerr<<"Error: too many arguments"<<endl;
        return EXIT_FAILURE;
    }
	

	if (NULL == (data = read_png_u8_gray(imgName.c_str(), &nx, &ny)) || nx<2 || ny<2)
    {
        cerr<<"Error: Image is not read. Use at least a valid 2x2 PNG image and try again the software."<<endl;
        return EXIT_FAILURE;
    }
    
	//Input images in SURF IPOL format
	image* img=new image((int) nx,(int) ny,data);

    free(data);
    
    // Normalize the image by setting the minimum value of the image to 0 and its maximum value to 256. Several technics like histogram equalization, linearization could be used. Standardization can not be used since the algorithm works with non negative integers.
    img->normalizeImage();

    
	// The list of key points.
	listKeyPoints* l=new listKeyPoints();
	listDescriptor* listDesc;
    
	// Keypoints detection and description
    listDesc=getKeyPoints(img,l,threshold);
   
    
    // Write results in a text file
		std::ofstream f(txtFile.c_str(), std::ios::trunc);
	
		if ( !f )
		{
			std::cerr << "Error: Can't make a text file." << std::endl;
			exit(1);
		}
	
		f<<64<<"\n";
		f<<listDesc->size()<<"\n";
		for(int i=0;i<listDesc->size();i++)
		{
        	f<<((*listDesc)[i]->kP)->x<<" "<<((*listDesc)[i]->kP)->y<<" "<<((*listDesc)[i]->kP)->scale<<" "<<((*listDesc)[i]->kP)->orientation<<" ";
            for(int j=0;j<16;j++)
				f<<(((*listDesc)[i]->list)[j]).sumDx<<" "<<(((*listDesc)[i]->list)[j]).sumDy<<" "<<(((*listDesc)[i]->list)[j]).sumAbsDx<<" "<<(((*listDesc)[i]->list)[j]).sumAbsDy<<" ";
			f<<((((*listDesc)[i]->kP)->signLaplacian)?1:-1);
            f<<"\n";
		}
		f.close();
		
	
	
	// Free memory
    /*MemCheck*/
	for(int i=0;i<l->size();i++)
		delete((*l)[i]);
	for(int i=0;i<listDesc->size();i++)
		delete((*listDesc)[i]);
    delete l;
	delete listDesc;
	delete img;
  	
	return 0;	
} 