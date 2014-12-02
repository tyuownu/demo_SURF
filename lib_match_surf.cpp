/*
 Lib match file for SURF
 
 Copyright 2013: Edouard Oyallon, Julien Rabin
 
 Version for IPOL.
 */

#include "lib_match_surf.h"
#include "time.h"
#include "sys/time.h"




std::vector<Match> matchDescriptor(listDescriptor * l1, listDescriptor * l2, std::vector<MatchWithHessian>* matcheswithhessian)
{
    // The match uses a ratio between a selected descriptor of l1 and the two closest descriptors
    // of l2.
    float thrm=RATE*RATE;
	// RATE = 0.6
	std::cout<<"error why?????"<<std::endl;
	clock_t t_start, t_end;    
    std::vector<Match> matches;

//	t_start = clock();
	long long L1,L2,L3;
	timeval tv1;
	gettimeofday(&tv1,NULL);
	L1 = tv1.tv_sec*1000*1000+tv1.tv_usec;
    
    // Matching is not symmetric.
	std::ofstream f("/home/tyu/match1.txt",std::ios::trunc);
	if( !f )
	{
		std::cerr<<" Error: Can't open match.txt"<<std::endl;
		exit(1);
	}
	f<<"x1  x2  y1  y2  sign1  sign2  Hess1  Hess2  d1  d2  dis\n";
    for(int i=0;i<l1->size();i++)
    {
        int position=-1;
        float d1=3;
        float d2=3;
		int flag=1;
        
        for(int j=0;j<l2->size();j++)
        {
			if ( (((*l1)[i])->kP)->integral_ty/2 <= (((*l2)[j])->kP)->integral_ty &&
					(((*l1)[i])->kP)->integral_ty*2 >= (((*l2)[j])->kP)->integral_ty)
			{
				if((((*l1)[i])->kP)->signLaplacian==(((*l2)[j])->kP)->signLaplacian)
				{
					float d=euclideanDistance((*l1)[i],(*l2)[j]);
					// We select the two closes descriptors
/*					d2=((d2>d)?d:d2);
					if( d1>d)
					{
						position=j;
						d2=d1;
						d1=d;
					}*/
					if(flag == 1)
					{
						position = j;
						d1 = d;
						d2 = d;
						flag++;
					}
					else if(flag == 2)
					{
						if(d < d1)
						{
							d1 = d;
							position = j;
						}
						else if(d >= d1)
							d2 = d;
						flag++;
					}
					else
					{
						if(d < d1)
						{
							d2 = d1;
							d1 = d;
							position = j;
						}
						else if(d <= d2 && d > d1)
							d2 = d;
					}
					/*
					 *if((((*l1)[i])->kP)->x == 237.8)
					 *    std::cout<<"d = "<<d<<" d1 = "<<d1<<" d2 = "<<d2<<std::endl;
					 */
				}
			}
		}
//		std::cout<<d1<<"---------"<<d2<<"----00000--------"<<position<<std::endl;
			



		
		// Try to match it
		if(position>=0  && thrm*d2>d1)
		{
		f<< (((*l1)[i])->kP)->x <<" "<< (((*l2)[position])->kP)->x <<" "
			<<(((*l1)[i])->kP)->y<<" "<<(((*l2)[position])->kP)->y<<" "
			<<(((*l1)[i])->kP)->signLaplacian<<" "<<(((*l2)[position])->kP)->signLaplacian<<" "
			<<(((*l1)[i])->kP)->integral_ty<<" "<<(((*l2)[position])->kP)->integral_ty<<" "
			<<d1<<" "<<d2<<" "
			<<euclideanDistance((*l1)[i],(*l2)[position])<<"\n";
            Match match;
			match.x1=((*l1)[i]->kP)->x;
            match.y1=((*l1)[i]->kP)->y;
			match.x2=((*l2)[position]->kP)->x;
			match.y2=((*l2)[position]->kP)->y;
			matches.push_back(match);


			/*
			 *MatchWithHessian matchH;
			 *matchH.x1=((*l1)[i]->kP)->x;
             *matchH.y1=((*l1)[i]->kP)->y;
			 *matchH.x2=((*l2)[position]->kP)->x;
			 *matchH.y2=((*l2)[position]->kP)->y;
			 *matchH.hessian1=((*l1)[i]->kP)->integral_ty;
			 *matchH.hessian2=((*l2)[position]->kP)->integral_ty;
			 *matcheswithhessian->push_back(matchH);
			 */
		}
	}
	f.close();
//	t_end = clock();
	gettimeofday(&tv1,NULL);
	L2 = tv1.tv_sec*1000*1000 + tv1.tv_usec;
	std::cout<<"L2 - L1= "<<L2 - L1<<std::endl;
//	std::cout<<"total time is: "<<((double)(t_end-t_start)/CLOCKS_PER_SEC)<<std::endl;
	std::cout<<"matches size = "<<matches.size()<<std::endl;
	return matches;
}



// Square of euclidean distance between two descriptors
float euclideanDistance(descriptor* a,descriptor* b)
{
	float sum=0;
	for(int i=0;i<16;i++)
	{
		sum+=((a->list)[i].sumDx-(b->list)[i].sumDx)*((a->list)[i].sumDx-(b->list)[i].sumDx)
		+((a->list)[i].sumDy-(b->list)[i].sumDy)*((a->list)[i].sumDy-(b->list)[i].sumDy)
		+((a->list)[i].sumAbsDy-(b->list)[i].sumAbsDy)*((a->list)[i].sumAbsDy-(b->list)[i].sumAbsDy)
		+((a->list)[i].sumAbsDx-(b->list)[i].sumAbsDx)*((a->list)[i].sumAbsDx-(b->list)[i].sumAbsDx);
	}
	return sum;
}


// Clean the multiple-to-one in SURF.
void cleanMatch( std::vector<Match>* list)
{
	
    bool* toRemove=new bool[list->size()];
    memset(toRemove,0,sizeof(bool)*list->size());
    for(int i=0;i<list->size();i++)
    {
        
        int x=(*list)[i].x1;
        int y=(*list)[i].y1;
        if(!toRemove[i])
            for(int j=i+1;j<list->size();j++)
            {
                int x_=(*list)[i].x2;
                int y_=(*list)[i].y2;
                
                if(x_==x && y==y_)
                {
                    toRemove[i]=true;
                    toRemove[j]=true;
                }
            }
    }
    
    for(int i=(int)list->size()-1;i>=0;i--)
        if(toRemove[i])
        {
            list->erase(list->begin()+i);
        }
    delete[] toRemove;
}


std::vector<Match> cleanMatchORSA( std::vector<Match> match_coor)
{
    // Use ORSA to filter out the incorrect matches.
    // store the coordinates of the matching points ; ORSA need 10 points min. Taken from ASIFT code.
    
    std::vector<float> index;
    // Guoshen Yu, 2010.09.23
    // index.clear();
    
    int t_value_orsa=10000;
    int verb_value_orsa=0;
    int n_flag_value_orsa=0;
    int mode_value_orsa=2;
    int stop_value_orsa=0;
    
    std::vector<Match>  finalMatches;
    float width=0;
    float height=0;
    for (int i=0;i<match_coor.size();i++)
    {
        
        // try to guess the size of the images
        width=(match_coor[i].x1>width)?match_coor[i].x1:width;
        width=(match_coor[i].x2>width)?match_coor[i].x2:width;
        height=(match_coor[i].y1>height)?match_coor[i].y1:height;
        height=(match_coor[i].y2>height)?match_coor[i].y2:height;
    }
    
    // epipolar filtering with the Moisan-Stival ORSA algorithm.
    orsa(width, height, match_coor, index, t_value_orsa, verb_value_orsa, n_flag_value_orsa, mode_value_orsa, stop_value_orsa);

    for ( int cc = 0; cc < (int) index.size(); cc++ )
        finalMatches.push_back(match_coor[index[cc]]);

    return finalMatches;
}



