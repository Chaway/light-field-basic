#include "utils/FastImage.h"

cv::Mat FAST::CFastImage::FastAddImages( const ImageSet& _imgs) {
	if (_imgs.empty())
		DEBUG_ERROR("NO IMAGES");
	int nImgs = (int)_imgs.size(); 
	int middle1 = ROUND(nImgs/2);
	Mat outImg, outImg2;
	
	#pragma omp parallel sections 
	{
		#pragma omp section 
		{
			outImg = Mat::zeros(_imgs[0].size(), _imgs[0].type());
			FOR (i, middle1)
				cv::add(outImg, _imgs[i], outImg); 
		}
		#pragma omp section 
		{
			outImg2 = Mat::zeros(_imgs[0].size(), _imgs[0].type());
			for (int i = middle1; i < nImgs; i++)
				cv::add(outImg2, _imgs[i], outImg2); 
		}
	}

	add(outImg, outImg2, outImg); 
	return outImg; 
}

cv::Mat FAST::CFastImage::AddImages( const ImageSet& _imgs) {
    if (_imgs.empty())
        DEBUG_ERROR("NO IMAGES");
    int nImgs = (int)_imgs.size();
    Mat outImg;
    outImg = Mat::zeros(_imgs[0].size(), _imgs[0].type());
    FOR (i, nImgs)
        cv::add(outImg, _imgs[i], outImg);

    return outImg;
}

cv::Mat FAST::CFastImage::FastAddImages4thread( const ImageSet& _imgs) {
	if (_imgs.empty())
		DEBUG_ERROR("NO IMAGES");
	int nImgs = (int)_imgs.size();
	int middle2 = ROUND(nImgs/2);
	int middle1 = ROUND(middle2/2);
	int middle3 = ROUND((nImgs + middle2)/2);
	Mat outImg,outImg1,outImg2,outImg3;
    #pragma omp parallel sections
	{
        #pragma omp section
		{
			outImg = Mat::zeros(_imgs[0].size(), _imgs[0].type());
			FOR (i, middle1)
				cv::add(outImg, _imgs[i], outImg);
		}
        #pragma omp section
		{
			outImg1 = Mat::zeros(_imgs[0].size(), _imgs[0].type());
			for (int i = middle1; i < middle2; i++)
				cv::add(outImg1, _imgs[i], outImg1);
		}
        #pragma omp section
		{
			outImg2 = Mat::zeros(_imgs[0].size(), _imgs[0].type());
			for (int i = middle2; i < middle3; i++)
				cv::add(outImg2, _imgs[i], outImg2);
		}
        #pragma omp section
		{
			outImg3 = Mat::zeros(_imgs[0].size(), _imgs[0].type());
			for (int i = middle3; i < nImgs; i++)
				cv::add(outImg3, _imgs[i], outImg3);
		}
	}

	add(outImg, outImg1, outImg);
	add(outImg, outImg2, outImg);
	add(outImg, outImg3, outImg);
	return outImg;
}

float FAST::CFastImage::FastSum( Mat& _img, int _pVec[], int _n ) {
	size_t elemSize = _img.elemSize(); 
	float sum = 0.0f; 
	FOR (i, _n)
		sum += (float)(*(uchar*)(_img.data+_pVec[i]*elemSize)); 
	return sum; 
}
