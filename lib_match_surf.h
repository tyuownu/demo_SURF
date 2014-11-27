/*
 Lib match header for SURF
 
 Copyright 2013: Edouard Oyallon, Julien Rabin
 
 Version for IPOL.
 */


#ifndef LIB_MATCH_SURF
#define LIB_MATCH_SURF
#include "descriptor.h"
#include "libMatch/match.h"
#include "orsa.h"

#include <iostream>
// Function to match two sets of descriptors
std::vector<Match>  matchDescriptor(listDescriptor * l1, listDescriptor * l2, std::vector<MatchWithHessian>* match_with_hessian);

// Clean repetetitive matches
void cleanMatch( std::vector<Match>* list);

// Return the euclidean distance between 2 descriptors
float euclideanDistance(descriptor *a,descriptor* b);

// Clean matches via ORSA
std::vector<Match> cleanMatchORSA( std::vector<Match> match_coor);
#endif
