This file implements an algorithm possibly linked to the patent
SURF.
This file is made available for the exclusive aim of serving as
scientific tool to verify the soundness and completeness of the
algorithm description. Compilation, execution and redistribution
of this file may violate patents rights in certain countries.
The situation being different for every country and changing
over time, it is your responsibility to determine which patent
rights restrictions apply to you before you compile, use,
modify, or redistribute this file. A patent lawyer is qualified
to make this determination.
If and only if they don't conflict with any patent terms, you
can benefit from the following license terms attached to this
file.

This program is provided for research and education only: you can
use and/or modify it for these purposes, but you are not allowed
to redistribute this work or derivative works in source or
executable form. A license must be obtained from the patent right
holders for any other use.


SURF for IPOL

This software is divided into 3 bins that can compute SURF descriptors, SURF matches and display them on images.

The article reference can be found on IPOL.

Last update: —— (3rd release)
Main changes:
* normalization of the Hessian
* cleaner code
* bin file is separated into 3 files

1) Compilation
Do make in command line.

2) Usage
Cd in /bin folder. For detecting keypoints:

extract_surf ../examples/gobelet.png k1.txt
extract_surf ../examples/gobelet2.png k1.txt

For matching:

match_surf k1.txt k2.txt matches.txt

And for display:

display_surf k1.txt k2.txt matches.txt ../examples/gobelet.png ../examples/gobelet2.png descriptor.png matches.png

3) Copyrights

ORSA has not to be reviewed. ORSA and libMatch are not production of the author. If you are the owner and want your copyright to appear, please send us an email.

4) Contact
If you see any bugs or have any comments, please send an email to the authors.

Authors :
E Oyallon edouard.oyallon@ens.fr
J Rabin julien.rabin@unicaen.fr


display_images_surf.cpp: Display pictures given keypoints, input images and matches
	input: d1.txt d2.txt matchs.txt img1 img2 
	output: output_desc.png output_matches.png
match_surf.cpp: computes the matches given 2 sets of descriptors
	input: d1.txt d2.txt
	output: output_matches.txt
extract_surf.cpp: execute as surf file1.png descriptors.txt
	input: img
	output: descriptors.txt
	option: threshold
keypoint.cpp: compute the list of descriptors and keypoints, for a given threshold


lib.h:
	type
		typedef long int INTEGRAL_IMAGE
		typedef double REGULAR_IMAGE
	constant
		pi 3.14159265358979323846
		NUMBER_SECTOR 20
		RATE 0.6
		OCTAVE 4
		INTERVAL 4
		SAMPLE_IMAGE 2
		DESCRIPTOR_SIZE_1D 4
	function
		inline double gaussian(double x,double y,double sig)  //gaussian
		inline int fround                                     //round-off functions
		inline REGULAR_IMAGE absval                           //absolute value
		inline std::string convertIntToChar                   //int->char


integral.h:
	function
		inline double squareConvolutionXY                     //convolution by a square defined by the bottom-left(a,b) and top-right (c,d)
		inline INTEGRAL_IMAGE haarX                           //convolution by a box[-1,+1]
		inline INTEGRAL_IMAGE haarY                           //convolution by a box[-1;+1]

image.h:
#include "io_png.h"
#include "lib.h"
	class
		image->
			function
				image(int x, int y)                         //constructors & clone constructors
				image(int x ,int y , unsigned char* data)
				image(image* im)
				inline int getWidth
				inline int getHeight
				void print ImagePara                        //print 3 images to show the matches using ORSA
				void normalizeImage                         //Linearly sets the min and max value of an image to be 0 dans 255
				void getSampledImage                        //returns the sampled image size using references
				image* padImage                             //returns a padded image
			data
				width
				height
				REGULAR_IMAGE* img
		imageIntegral->
			function
				imageIntegral(image* im)
				void computeIntegralImage
				inline INTEGRAL_IMAGE& operator()
				inline INTEGRAL_IMAGE  operator()
			data
				width
				height
				INTEGRAL_IMAGE* img
				int padding



io_png.h:
	constant
		IO_PNG_VERSION "0.20100817"



keypoint.h:
#include "lib.h"
#include "image.h"
#include "integral.h"
#include "descriptor.h"
	class
		keyPoint->
			data
				double x,y,scale,orientation
				bool signLaplacian
			funtcion
				keyPoint(REGULAR_IMAGE x_,REGULAR_IMAGE y_,REGULAR_IMAGE scale_,REGULAR_IMAGE orientation_,bool signLaplacian_):x(x_),scale(scale_),orientation(orientation_),signLaplacian(signLaplacian_){}
	type
		typedef std::vector<keyPoint*> listKeyPoints
	function
		void addKeyPoint(imageIntegral* img,REGULAR_IMAGE i,REGULAR_IMAGE j,bool signLapl,REGULAR_IMAGE scale,listKeyPoints* listKeyPoints);
		//create a keypoint
		float getOrientation(imageIntegral* imgInt,int x,int y,int numberSector,REGULAR_IMAGE scale)    //compute the orientation of a keypoint
		bool interpolationScaleSpace(image** img,int x,int y,int i,REGULAR_IMAGE &x_,REGULAR_IMAGE &y_,REGULAR_IMAGE &s_,int sample,int octaveValue);
		//Reject or interpolate the coordinate of a keypoint
		inline bool isMaximum(image** imageStamp,int x,int y,int scale,float threshold)    //Check if a point is a local maximum or not, and more than a given threshold

/libMatch/match.h
	struct:
		Match
			float x1,y1,x2,y2


	keypoint.txt structure:
	64
	number
	x,y,scale,orientation,discriptor*64,signLaplacian
