#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <cv.h>
#include <time.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, final, q1, q2, q3, q4;
  int width, height, t;

  image = imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);

  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(0);
  }

  width=image.size().width;     //image.size().width = image.rows
  height=image.size().height;   //image.size().height = image.cols

  final = image.clone();

  //Divide a imagem em quatro quadrantes e os copia
  q1 = image(Rect(0, 0, width/2, height/2));
  q2 = image(Rect(width/2, 0, width/2, height/2));
  q3 = image(Rect(0, height/2, width/2, height/2));
  q4 = image(Rect(width/2, height/2, width/2, height/2));

  //Faz uma atribuição aleatória para as posições dos quadrantes e os copia para a imagem final
  t = rand() % 23;

  if(t==0){
    q4.copyTo(final(Rect(0, 0, width/2, height/2)));
    q3.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q2.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q1.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==1){
    q4.copyTo(final(Rect(0, 0, width/2, height/2)));
    q3.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q1.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q2.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==2){
    q4.copyTo(final(Rect(0, 0, width/2, height/2)));
    q1.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q2.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q3.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==3){
    q4.copyTo(final(Rect(0, 0, width/2, height/2)));
    q1.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q3.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q2.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==4){
    q4.copyTo(final(Rect(0, 0, width/2, height/2)));
    q2.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q1.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q3.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==5){
    q4.copyTo(final(Rect(0, 0, width/2, height/2)));
    q2.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q3.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q1.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==6){
    q3.copyTo(final(Rect(0, 0, width/2, height/2)));
    q1.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q2.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q4.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==7){
    q3.copyTo(final(Rect(0, 0, width/2, height/2)));
    q1.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q4.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q2.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==8){
    q3.copyTo(final(Rect(0, 0, width/2, height/2)));
    q2.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q1.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q4.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==9){
    q3.copyTo(final(Rect(0, 0, width/2, height/2)));
    q2.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q4.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q1.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==10){
    q3.copyTo(final(Rect(0, 0, width/2, height/2)));
    q4.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q1.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q2.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==11){
    q3.copyTo(final(Rect(0, 0, width/2, height/2)));
    q4.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q2.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q1.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==12){
    q2.copyTo(final(Rect(0, 0, width/2, height/2)));
    q1.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q3.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q4.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==13){
    q2.copyTo(final(Rect(0, 0, width/2, height/2)));
    q1.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q4.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q3.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==14){
    q2.copyTo(final(Rect(0, 0, width/2, height/2)));
    q3.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q1.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q4.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==15){
    q2.copyTo(final(Rect(0, 0, width/2, height/2)));
    q3.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q4.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q1.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==16){
    q2.copyTo(final(Rect(0, 0, width/2, height/2)));
    q4.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q1.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q3.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==17){
    q2.copyTo(final(Rect(0, 0, width/2, height/2)));
    q4.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q3.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q1.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==18){
    q1.copyTo(final(Rect(0, 0, width/2, height/2)));
    q2.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q3.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q4.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==19){
    q1.copyTo(final(Rect(0, 0, width/2, height/2)));
    q2.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q4.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q3.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==20){
    q1.copyTo(final(Rect(0, 0, width/2, height/2)));
    q3.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q2.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q4.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==21){
    q1.copyTo(final(Rect(0, 0, width/2, height/2)));
    q3.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q4.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q2.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==22){
    q1.copyTo(final(Rect(0, 0, width/2, height/2)));
    q4.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q2.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q3.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  if(t==23){
    q1.copyTo(final(Rect(0, 0, width/2, height/2)));
    q4.copyTo(final(Rect(width/2, 0, width/2, height/2)));
    q3.copyTo(final(Rect(0, height/2, width/2, height/2)));
    q2.copyTo(final(Rect(width/2, height/2, width/2, height/2)));
  }

  imwrite("trocaregioes.png", final);
  imshow("imagem final", final);
  cout << "A imagem tem " << image.rows << " pixels de largura e " << image.cols << " pixels de altura" << endl;
  waitKey();
  return 0;
}

