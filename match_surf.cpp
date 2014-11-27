/*
 Match file for SURF
 
 Copyright 2013: Edouard Oyallon, Julien Rabin
 
 Version for IPOL.
 */

#include "match_surf.h"
#include "lib_match_surf.h"

using namespace std;

// This executive computes the matches given 2 sets of descriptors
// d1.txt d2.txt output_matches.txt -orsa
int main(int argc, char** argv)
{
    
    string keypoints1=argv[1];
    string keypoints2=argv[2];
    string outputmatch=argv[3];
    
    // ORSA ?
    bool isOrsa=false;
    if(argc>4)
        isOrsa=true;

    if(argc!=4 && argc!=5)
    {
        cerr<<"Error: Missing arguments"<<endl;
        return EXIT_FAILURE;
    }
    
    // Recover the list of descriptors
    listDescriptor* listDesc1=getDescriptorFromRawFile(keypoints1);
	std::cout<<"list descriptor 1: "<<listDesc1->size()<<std::endl;
    listDescriptor* listDesc2=getDescriptorFromRawFile(keypoints2);
	std::cout<<"list descriptor 2: "<<listDesc2->size()<<std::endl;
    
    // Matching
    std::vector<Match> match_coor=matchDescriptor(listDesc1,listDesc2);
	std::cout<<"match RAW: "<<match_coor.size()<<std::endl;
	saveMatch(outputmatch.c_str(),match_coor);
    // Cleaning identical matches
    cleanMatch(&match_coor);
	std::cout<<"match RAW2: "<<match_coor.size()<<std::endl;
    
    // Cleaning via ORSA
    if(match_coor.size()>10 && isOrsa)
        match_coor=cleanMatchORSA(match_coor);
	std::cout<<"match RAW3: "<<match_coor.size()<<std::endl;
    
    // Save matches
    //saveMatch(outputmatch.c_str(), match_coor);
    
    /*MemCheck*/
	for(int i=0;i<listDesc1->size();i++)
		delete((*listDesc1)[i]);
	for(int i=0;i<listDesc2->size();i++)
		delete((*listDesc2)[i]);
    
    delete listDesc1;
    delete listDesc2;

    return 0;
}




