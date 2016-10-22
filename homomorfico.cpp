#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <cv.h>
#include <math.h>

using namespace cv;
using namespace std;

void deslocaDFT(Mat& image ){
  Mat tmp, A, B, C, D;

  // se a imagem tiver tamanho impar, recorta a regiao para
  // evitar cópias de tamanho desigual
  image = image(Rect(0, 0, image.cols & -2, image.rows & -2));
  int cx = image.cols/2;
  int cy = image.rows/2;

  // reorganiza os quadrantes da transformada
  // A B   ->  D C
  // C D       B A
  A = image(Rect(0, 0, cx, cy));
  B = image(Rect(cx, 0, cx, cy));
  C = image(Rect(0, cy, cx, cy));
  D = image(Rect(cx, cy, cx, cy));

  // A <-> D
  A.copyTo(tmp);  D.copyTo(A);  tmp.copyTo(D);

  // C <-> B
  C.copyTo(tmp);  B.copyTo(C);  tmp.copyTo(B);
}

int main(int argc, char** argv){
  Mat imaginaryInput, complexImage, multsp;
  Mat padded, filter, mag;
  Mat image, imagegray, tmp;
  Mat_<float> realInput, zeros;
  vector<Mat> planos;
  char key;
  float gamaH, gamaL, c, D0;

  image = imread("vitruv.jpg",CV_LOAD_IMAGE_GRAYSCALE);

  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(0);
  }

  int dft_M, dft_N;

  dft_M = getOptimalDFTSize(image.rows);
  dft_N = getOptimalDFTSize(image.cols);

  int X = dft_M;
  int Y = dft_N;

  copyMakeBorder(image, padded, 0,
                 dft_M - image.rows, 0,
                 dft_N - image.cols,
                 BORDER_CONSTANT, Scalar::all(0));

  // parte imaginaria da matriz complexa (preenchida com zeros)
  zeros = Mat_<float>::zeros(padded.size());

  complexImage = Mat(padded.size(), CV_32FC2, Scalar(0));

  filter = complexImage.clone();

  tmp = Mat(dft_M, dft_N, CV_32F);

  cout << "gamaH = ";
  cin >> gamaH;
  cout << "gamaL = ";
  cin >> gamaL;
  cout << "c = ";
  cin >> c;
  cout << "D0 = ";
  cin >> D0;

  for(int i=0;i<dft_M;i++){
  	for(int j=0;j<dft_N;j++){
      tmp.at<float> (i,j) = (gamaH-gamaL)*(1.0-exp(-1.0*(float)c*((((float)i-X/2.0)*((float)i-X/2.0) + ((float)j-Y/2.0)*((float)j-Y/2.0))/(D0*D0)))) + gamaL;
  	}
  }

  Mat comps[]= {tmp, tmp};
  merge(comps, 2, filter);

  for(;;){
    planos.clear();

    realInput = Mat_<float>(padded);

    planos.push_back(realInput);
    planos.push_back(zeros);

    merge(planos, complexImage);

    dft(complexImage, complexImage);

    deslocaDFT(complexImage);

    mulSpectrums(complexImage,filter,complexImage,0);
    planos.clear();

    split(complexImage, planos);

    merge(planos, complexImage);

    deslocaDFT(complexImage);

    idft(complexImage, complexImage);

    planos.clear();

    split(complexImage, planos);

    normalize(planos[0], planos[0], 0, 1, CV_MINMAX);

    key = (char) waitKey(10);
    if( key == 27 ) break; // esc pressed!

    imshow("Original", image);
    imshow("Filtrada", planos[0]);

  }
  return 0;
} 

 