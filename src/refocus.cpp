#include "common.h"
#include "utils/Timer.h"
#include "utils/FastImage.h"

const int GRID_SIZE = 8;

Mat RenderLFFull(float _alpha,ImageSet &views) {
    int m_numViews = views.size();
    ImageSet views_t(m_numViews);
    Size sz(views[0].cols, views[0].rows);
    double alpha = double(_alpha);
    CTimer* timer = new CTimer("all views shift", false);
    #pragma omp parallel for
   //500 times results: With pargma running time is 27 sec compared to 38 sec without it
    FOR (n, m_numViews) {
        //cout << n << endl;
        Mat H = Mat::zeros(2, 3, CV_64FC1);
        int u = n % GRID_SIZE;
        int v = (n-u) / GRID_SIZE;
        double deltaX = (u-3) * alpha/4.0;
        double deltaY = (v-3) * alpha/4.0;
        H.at<double>(0, 0) = 1.0; H.at<double>(1, 1) = 1.0;
        H.at<double>(0, 2) = -deltaX; H.at<double>(1, 2) = -deltaY;
        warpAffine(views[n], views_t[n], H, sz, 1, 0, Scalar(0, 0, 0));
    }
    double t = timer->Time() * 1000;
    //cout << "t = " << t << " ms" << endl;

    Mat tmpF = FAST::CFastImage::AddImages(views_t)/m_numViews;
    t = timer->Time() * 1000;
    //cout << "t = " << t << " ms" << endl;
    Mat m_renderLF;
    tmpF.convertTo(m_renderLF, CV_8UC3);
    return m_renderLF.clone();
}
/*

Mat RenderLFWeighted(int _frameId, float _alpha, float _aperture) {
    ImageSet views_t(m_numViews);
    ImageSet views = m_seq[_frameId];
    Size sz(views[0].cols, views[0].rows);
    double alpha = double(_alpha);
    float C= (GRID_SIZE-1)/2.0;
    // compute weights
    vectorf weights;
    float sigma = (1 - _aperture) * 4;
    FOR (n, m_numViews) {
        int u = n % GRID_SIZE;
        int v = (n-u) / GRID_SIZE;
        float dist = ((u - C) * (u - C) + (v - C) * (v -C)) / (C*C);
        float weight = exp(-dist * sigma);
        weights.push_back(weight);
    }

    float weight_sum = vecSum(weights);
    FOR (n, m_numViews)
        weights[n] /= weight_sum;

    #pragma omp parallel for
    FOR (n, m_numViews) {
        Mat H = Mat::zeros(2, 3, CV_64FC1);
        int u = n % GRID_SIZE;
        int v = (n-u) / GRID_SIZE;
        double deltaX = (u-3) * alpha/4.0;
        double deltaY = (v-3) * alpha/4.0;
        H.at<double>(0, 0) = 1.0; H.at<double>(1, 1) = 1.0;
        H.at<double>(0, 2) = -deltaX; H.at<double>(1, 2) = -deltaY;
        warpAffine(views[n], views_t[n], H, sz, 1, 0, Scalar(0, 0, 0));
        views_t[n] = views_t[n] * weights[n];
    }


    Mat tmpF = FAST::CFastImage::FastAddImages(views_t);
    tmpF.convertTo(m_renderLF, CV_8UC3);
    return m_renderLF.clone();
}
*/

Mat freemove(Point3f loc,ImageSet &views){


}

int main(int argc,char** argv){
	vector<string> allArgs(argv, argv + argc);
    ImageSet views;
    Mat largeIm = imread(allArgs[1]);
    int H = 8;
    int W = 8;
    int height = largeIm.rows / H;
    int width = largeIm.cols / W;
    FOR (h, H) {
        FOR (w, W) {
            Mat view = largeIm(Rect(w*width, h*height, width, height));
            Mat view_f;
            view.convertTo(view_f, CV_32FC3);
//            SHOW_IMG_WAIT(view_f);
            views.push_back(view_f);
//            Mat view_pad;
//            copyMakeBorder(view_f, view_pad, m_border, m_border, m_border, m_border, BORDER_CONSTANT, Scalar(0.0, 0.0, 0.0));
//              views.push_back(view_f);
//              SHOW_IMG_WAIT(view_pad);
//            viewsPad.push_back(view_pad);
        }
    }

    float _alpha = 1.0;
    CTimer* timer = new CTimer("One time refocus", false);
    Mat rend_img;
    FOR(i,500)
        rend_img= RenderLFFull(_alpha,views);
    double t = timer->Time() * 1000;
    cout << "t = " << t << " ms" << endl;
    //SHOW_IMG_WAIT(rend_img);
    //imwrite("rend_img.png",rend_img);
    return 0;
}

