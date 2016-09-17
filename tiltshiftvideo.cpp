#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int height;

double d = 7; //Setando o valor de d
int decay_slider = 0;

int top_slider = 0;
int vertical = 0;

int strip = 20;
int height_slider = 0;


Mat img1, img2, ref1, ref2, tilt;

char TrackbarName[50];

void TS(){
  Mat m1, m2, tiltshift;
  int l1 = - strip/2;
    int l2 = -l1;
    ref1 = Mat::zeros(img1.rows, img1.cols, CV_32F);
    ref2 = Mat::zeros(img1.rows, img1.cols, CV_32F);
    int i, j;
    for (i = 0; i < ref1.rows; i++) {
        int x = i - (vertical + strip/2);
        float alfa = 0.5f * (tanh((x-l1)/d) - tanh((x-l2)/d));
        for (j = 0; j < ref1.cols; j++) {
            ref1.at<float>(i, j) = alfa;
            ref2.at<float>(i, j) = 1 - alfa;
        }
    }
    Mat auxA[] = {ref1, ref1, ref1};
    Mat auxB[] = {ref2, ref2, ref2};
    merge(auxA, 3, ref1);
    merge(auxB, 3, ref2);

  img1.convertTo(m1, CV_32FC3);
  img2.convertTo(m2, CV_32FC3);

    multiply(m1, ref1, m1);
    multiply(m2, ref2, m2);

    add(m1, m2, tiltshift);
    tiltshift.convertTo(tiltshift, CV_8UC3);
    imshow("tiltshift", tiltshift);

}

void on_trackbar_decay(int, void*){
    d = (double) decay_slider;
    if (d < 1) {
        d = 1;
    }
    TS();
}

void on_trackbar_vertical(int, void *){
    vertical = top_slider*height/100;
    TS();
}

void on_trackbar_height(int, void*) {
    strip = height_slider*height/100;
    if (strip == 0) {
        strip = 1;
    }

    if (strip > height) {
        strip = height;
    }
    TS();
}

int main(int argvc, char** argv){
  Mat aux, mask, mask1;
  VideoCapture video_in;
  int width = static_cast<int>(video_in.get(CV_CAP_PROP_FRAME_WIDTH));
  int height = static_cast<int>(video_in.get(CV_CAP_PROP_FRAME_HEIGHT));
  double FPS = video_in.get(CV_CAP_PROP_FPS);
  VideoWriter video_out("saida.mp4", CV_FOURCC('m','p', '4', 'v'), 15, cv::Size(width, height));

  video_in.open("entrada.mp4");

  if(!video_in.isOpened()){
    return -1;
  }

  for(;;){
    video_in >> img1;
    img2 = img1.clone();

    float media[] = {1,1,1,1,1,
                     1,1,1,1,1,
                     1,1,1,1,1,
                     1,1,1,1,1,
                     1,1,1,1,1};
    //para efeito de borramento
    mask = Mat(5, 5, CV_32F, media);
    scaleAdd(mask, 1/25.0, Mat::zeros(5,5,CV_32F), mask1);
    swap(mask, mask1);
    img2.convertTo(aux, CV_32F);
    for (int i = 0; i < 10; i++) {
        filter2D(aux, aux, aux.depth(), mask, Point(1, 1), 0);
    }
    aux=abs(aux);
    aux.convertTo(img2, CV_8UC3);

    namedWindow("tiltshift", 1);

    sprintf( TrackbarName, "Altura");
    createTrackbar( TrackbarName, "tiltshift",
                    &height_slider,
                    100,
                    on_trackbar_height);

    sprintf( TrackbarName, "Decaimento");
    createTrackbar( TrackbarName, "tiltshift",
                    &decay_slider,
                    100,
                    on_trackbar_decay);

    sprintf( TrackbarName, "Deslocamento");
    createTrackbar( TrackbarName, "tiltshift",
                    &top_slider,
                    100,
                    on_trackbar_vertical);
    TS();
    video_out.write(tilt);
  }

  waitKey(0);
  return 0;
}