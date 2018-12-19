#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;
using namespace cv;



int erosion_size = 20;
int erosion_elem = 20;

float rotation = 0.0;

int minH = 50;
int minS = 90;
int minV = 250;

int maxH = 255;
int maxS = 255;
int maxV = 255;

vector<vector<int > > pointCloud;

void calibration ( Mat & imgOriginal ) 
{
	CvPoint mid_bottom , mid_top ;
	mid_bottom . x = 640/2;
	mid_bottom . y = 0;
	mid_top . x = 640/2;
	mid_top . y = 480;
	IplImage frame_ipl = imgOriginal ;
	cvLine (& frame_ipl , mid_bottom , mid_top , CV_RGB (0 ,255 ,0) , 2) ;
}

void media(vector<vector<Point> > contours, map<int,int> &mPoints)
{
    if(contours.size()){
        map<int,int>::iterator it;

        for(unsigned int i=0; i<contours.size(); ++i){
            for(unsigned int j =0; j < contours[i].size(); ++j)
            {
                it = mPoints.find( contours[i][j].y );
                if( it != mPoints.end() )
                    mPoints[contours[i][j].y ] = ( mPoints[ contours[i][j].y ] + contours[i][j].x )/2;
                else
                    mPoints[ contours[i][j].y ] = contours[i][j].x;
            }
        }
    }
}

void triangulation(int x, int y, int &_X, int &_Z){
    x = (180-x)*1.0; 
    _X = x*cos(rotation);
    _Z = -x*sin(rotation);
}


void saveObj(){
    ofstream pcdFile("output.pcd");
    
	pcdFile<<"# .PCD v.5 - Point Cloud Data file format"<<endl;
	pcdFile<<"VERSION .5"<<endl;
	pcdFile<<"FIELDS x y z"<<endl;
	pcdFile<<"SIZE 4 4 4"<<endl;
	pcdFile<<"TYPE F F F"<<endl;
	pcdFile<<"COUNT 1 1 1"<<endl;
	pcdFile<<"WIDTH "<<pointCloud.size()<<endl;
	pcdFile<<"HEIGHT "<<1<<endl;
	pcdFile<<"POINTS "<<pointCloud.size()<<endl;
	pcdFile<<"DATA ascii"<<endl;

    for(unsigned int i=0;i<pointCloud.size();++i){
       pcdFile<<pointCloud[i][0]<<" "<<pointCloud[i][1]<<" "<<pointCloud[i][2]<<endl;
    }
    pcdFile.close();
}

int main(int, char**)
{
    VideoCapture cap(0);
    if(!cap.isOpened()) 
        return -1;
    Mat edges,grayScale;
	float ang = 0.0;	
    for(;;)
    {
    
        Mat frame;
        cap >> frame; 
		Mat hsv;
		cvtColor(frame, edges, CV_BGR2HSV);

		edges=edges + Scalar(1, 10, 10);
		inRange(edges, Scalar(minH, minS, minV),Scalar(maxH,maxS,maxV), edges); 
		erode( edges, edges, Mat(), Point(-1, -1), 1,0, 0);
		resize(edges, edges, Size(edges.cols/2, edges.rows/2)); 
		
		Mat salida =edges.clone();

        Canny(edges, salida, 100, 200);
        
		//imshow(" Bordes ", salida);
		calibration(frame);
		imshow(" Original ", frame);
		
		
        vector< vector< Point> > contours;
        map<int,int> mPoints;
        findContours(salida, contours, RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
		
        media(contours,mPoints);

		vector<Point> mp;
		int _X,_Z;
        

        for(const auto &myPair : mPoints)
		{ 
			if(myPair.second < salida.cols/2)
			{
				triangulation(myPair.second,myPair.first,_X,_Z);
				vector<int> tmp;
				tmp.push_back(_X);
				tmp.push_back(myPair.first);
				tmp.push_back(_Z);

				pointCloud.push_back(tmp);
			}
		    
        }
        
        rotation= ang*((22/7)/180.0);
        
        ang+=1.72;
        cout<<"rotation: "<<rotation<<" , angle: "<<ang<<endl;

        if(ang > 380) break;

        if(waitKey(30) >= 0) break;
    }
	saveObj();
	
	system("./viewer/build/cloud_viewer output.pcd");
    
    return 0;
}

