#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace cv;

#define STEP 10
#define JITTER 5
#define RAIO 3

int main(int argc, char** argv){
  vector<int> yrange;
  vector<int> xrange;

  Mat image, frame, points, border;

  int width, height, gray;
  int x, y;

  Vec3b val;

  image = imread("eiffel.jpg",CV_LOAD_IMAGE_COLOR);

  srand(time(0));

  if(!image.data){
  cout << "Erro ao abrir" << argv[1] << endl;
    cout << argv[0] << " imagem.jpg";
    exit(0);
  }

  width=image.size().width;
  height=image.size().height;

  xrange.resize(height/STEP);
  yrange.resize(width/STEP);

  iota(xrange.begin(), xrange.end(), 0);
  iota(yrange.begin(), yrange.end(), 0);

  for(uint i=0; i<xrange.size(); i++){
    xrange[i]= xrange[i]*STEP+STEP/2;
    yrange[i]= yrange[i]*STEP+STEP/2;
  }

  points = Mat(height, width, CV_8UC3, Scalar(255, 255, 255));

  random_shuffle(xrange.begin(), xrange.end());

  for(auto i : xrange){
    random_shuffle(yrange.begin(), yrange.end());
    for(auto j : yrange){
      x = i+rand()%(2*JITTER)-JITTER+1;
      y = j+rand()%(2*JITTER)-JITTER+1;
      val = image.at<Vec3b>(x,y);
      circle(points,
             cv::Point(y,x),
             RAIO,
             CV_RGB(val[2],val[1],val[0]),
             -1,
             CV_AA);
    }
  }


  int L, R;

  cout << "Limiar = ";
  cin >> L;
  cout << "Raio = ";
  cin >> R;

  Canny(image, border, L, 3*L);
  for(int i=1; i<width; i++){
      for(int j=1; j<height; j++){
        if(border.at<uchar>(i,j) == 255){ //Identifica a borda (cor branca)
          val = image.at<Vec3b>(i,j);
          circle(points,
                 cv::Point(j,i),
                 R,
                 CV_RGB(val[2],val[1],val[0]),
                 -1,
                 CV_AA);
        }
      }
  }
  imshow("Cannypoints", points);
  waitKey();

 }