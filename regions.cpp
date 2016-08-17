#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image;
  Vec3b val;
  int x1, x2, y1, y2;

  image= imread("triforce.jpg",CV_LOAD_IMAGE_COLOR);
  if(!image.data)
    cout << "nao abriu triforce.jpg" << endl;

  namedWindow("janela",WINDOW_AUTOSIZE);

  cout << "*** A IMAGEM TEM " << image.size().width << " PIXELS DE LARGURA E " << image.size().height << " PIXELS DE ALTURA ***" << endl;
  
  cout << "Digite as coordenadas do ponto 1: ";
  cin >> x1 >> y1;
  
  cout << endl;
  
  cout << "Digite as coordenadas do ponto 2: ";
  cin >> x2 >> y2;
  

  val[0] = 255; //B
  val[1] = 255; //G
  val[2] = 255; //R

  
  if(x1>x2 || y1>y2){
    cout << "ERRO! INDICE INVALIDO!" << endl;
  }
 
  else{
    for(int i=x1;i<x2;i++){
      for(int j=y1;j<y2;j++){
        image.at<Vec3b>(i,j)= val - image.at<Vec3b>(i,j);
      }
    }
  }

  imshow("janela", image);
  waitKey();
  return 0;
}
