#include "refocus.h"

int main(int argc,char** argv){
    vector<Mat> views;
	Mat largeIm = imread(argv);
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
//            views.push_back(view_f);
//            Mat view_pad;
//            copyMakeBorder(view_f, view_pad, m_border, m_border, m_border, m_border, BORDER_CONSTANT, Scalar(0.0, 0.0, 0.0));
            views.push_back(view_f);
/           SHOW_IMG_WAIT(view_pad);
//            viewsPad.push_back(view_pad);
        }
    }

}