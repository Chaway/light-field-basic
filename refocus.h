#ifndef REFOCUS_H
#define REFOCUS_H

#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
#include <cassert>
#include <omp.h>
#include <cstdio>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <set>
//logging

//include OpenCV 
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv/cxcore.h"
//#include "opencv2/contrib/contrib.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

#define ELEM(type,m_start,step,size,xpos,ypos) *((type*)(m_start+step*(ypos)+(xpos)*size))
#define ELEM3(type,m_start,step,size,xpos,ypos,ichannel) \
	*((type*)(m_start+step*(ypos)+(xpos)*size+ichannel))
#define DELETE_OBJECT(x)	if ((x)) { delete (x); (x) = NULL; }
#define DELETE_ARRAY(x)		if ((x)) { delete [] (x); (x) = NULL; }
#define DELETE_OBJECT_ARRAY(n,x)		if ((x)) { for (int i = 0; i < n; i++) { DELETE_OBJECT(((x)[i])); } delete [] (x); (x) = NULL; }
#define ROUND(a)	((a)>0 ? (int)(a+0.5) : -(int)(0.5-a))	
#define CLAMP(v,l,h)	v = ((v)<(l) ? (l) : (v) > (h) ? (h) : v)
#define InSideImage(x,y,img) ((x)>-1&&(x)<(img)->width&&(y)>-1&&(y)<(img)->height)
#define Img_For(i,j,img) for (int i=0;i<(img)->height;(i)++)for (int j=0;j<(img)->width;(j)++)
#define CLAMP(v,l,h)	v = ((v)<(l) ? (l) : (v) > (h) ? (h) : v)
#define FOR(i,n) for( int i=0; i<n; i++ )
#define FOR_u(i, n) for (size_t i = 0; i < n; i++)
#define SHOW(a) std::cout << #a << ": " << (a) << std::endl
#define SHOW_VECTOR(a){\
	std::cout << #a << ": ";\
	for (int i = 0; i < (int)a.size(); i++)\
	std::cout << a[i] << " ";\
	std::cout << std::endl;\
}
#define SHOW_ARRAY(a, n){\
	std::cout << #a << ": ";\
	for (int i = 0; i < n; i++)\
			std::cout << a[i] << " ";\
		std::cout << std::endl;\
}

#define SHOW_IMG_WAIT(img){\
	imshow(#img, img); \
	waitKey(); \
}

#define SHOW_IMG(img){\
    imshow(#img, img); \
}

#define PI				   3.141592653589793238512808959406186204433
#define SQUARE(x) ((x)*(x))
#define RAD_2_DEGREE(x)		((x)/PI*180.)
#define DEGREE_2_RAD(x)		((x)/180.*PI)

#define EPSILON 1e-10
#define SHOW_PATCH_BORDER 8

// typedefs
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef vector<int> vectori;
typedef vector<float> vectorf;
typedef vector<double> vectord;
typedef vector<bool> vectorb; 
typedef vector<uchar> vectoru;
typedef vector<ushort> vectorus;
typedef vector<string> vectorString;
typedef Point2f PointF;
typedef vector<PointF> PointSetF;
typedef vector<Point2i> PointSeti;
typedef const Mat CMat;
typedef const string CStr;
typedef vector<Mat> MatSet; 
typedef vector<Mat> ImageSet; 
typedef vector<Rect> Rects; 
#endif