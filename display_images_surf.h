/*
 Display images header for SURF
 
 Wrapper to display images and info from generated text files.
 
 Copyright 2013: Edouard Oyallon, Julien Rabin
 
 Version for IPOL.
 */


#include "descriptor.h"
#include "image.h"

#ifndef SURF_DISPLAY
#define SURF_DISPLAY

// Show descriptors represented by a circle whose radius is proportional to the scale.
image*	 showDescriptors(image* img1,listDescriptor* listeDesc);

// Draw a line
void line(image *img,float xa,float ya,float xb,float yb,float intensite);

#endif
