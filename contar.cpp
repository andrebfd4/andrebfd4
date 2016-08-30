#include <iostream>
#include <opencv2/opencv.hpp>
#include <stack>

using namespace cv;
using namespace std;

class coordenada{
  public:
    int x, y;
}; 

void seedfill (coordenada C, int rotulo, Mat img){
  stack <coordenada> ponto;

  for(int i=0;i<img.size().width;i++){
    for(int j=0;j<img.size().height;j++){
      if(img.at<uchar>(i,j) == 255){
        C.x = i;
        C.y = j;
        ponto.push(C);
        ponto.pop();
        img.at<uchar>(i,j) = rotulo+1;
        if(img.at<uchar>(i+1,j) == 255){
          C.x = i+1;
          C.y = j;  
          ponto.push(C);
          img.at<uchar>(i,j) = rotulo+1;
          if(img.at<uchar>(i-1,j) == 255){
            C.x = i-1;
            C.y = j;
            ponto.push(C);
            img.at<uchar>(i,j) = rotulo+1;
            if(img.at<uchar>(i,j+1) == 255){
              C.x = i;
              C.y = j+1;
              ponto.push(C);
              img.at<uchar>(i,j) = rotulo+1;
              if(img.at<uchar>(i,j-1) == 255){
                C.x = i;
                C.y = j-1;
                ponto.push(C);
                img.at<uchar>(i,j) = rotulo+1;
              }
            }
          }
        }
      }
    }
  }
}


int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int n_objects, n_bolhas;
  coordenada C;
  CvPoint p;

  image = imread("bolhas.png",CV_LOAD_IMAGE_GRAYSCALE);

  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(0);
  }
  width=image.size().width;     //image.size().width = image.rows
  height=image.size().height;   //image.size().height = image.cols

  
  n_objects = 0;
  n_bolhas = 0;

  //Apagando as bolhas nos cantos da imagem
  for(int i=0;i<width;i++){
    for (int j=0;j<1;j++){
      if(image.at<uchar>(i,j) == 255){ //Achou objeto
        p.x=j;
        p.y=i;
        floodFill(image, p, 0);
      }
    }
  }

  for(int i=0;i<1;i++){
    for(int j=0;j<height;j++){
      if(image.at<uchar>(i,j) == 255){ //Achou objeto
        p.x=j;
        p.y=i;
        floodFill(image, p, 0);
      }
    }
  }

  for(int i=0;i<width;i++){
    for (int j=(height-1);j<height;j++){
      if(image.at<uchar>(i,j) == 255){ //Achou objeto
        p.x=j;
        p.y=i;
        floodFill(image, p, 0);
      }
    }
  }

  for(int i=(width-1);i<width;i++){
    for (int j=0;j<height;j++){
      if(image.at<uchar>(i,j) == 255){ //Achou objeto
        p.x=j;
        p.y=i;
        floodFill(image, p, 0);
      }
    }
  } //Terminou

  p.x=0; 
  p.y=0;
  floodFill(image, p, 1); 

  //Busca por bolhas
  for(int i=0;i<width;i++){
    for(int j=0;j<height;j++){
      if(image.at<uchar>(i,j) == 0){ //Achou região preta
        if(image.at<uchar>(i,j-1) == 255){ //Achou região branca à esquerda do pixel preto (bolha). Também acha objetos.
          n_bolhas++;
          n_objects++;
          p.y=i;
          p.x=j-1;
          floodFill(image, p, 100); //Pinta objeto com bolha de cinza
        }
      }
    }
  }

   //Objetos sem bolha ainda estão preenchidos com branco. Busca por eles.
   for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
        n_objects++;
        p.x=j;
        p.y=i;
        floodFill(image,p,254);
      }
    }
  }

  //seedfill(C, rotulo, image);
  
  imshow("image", image);
  imwrite("contar.png", image);
  cout << "A imagem tem " << image.rows << " pixels de largura e " << image.cols << " pixels de altura" << endl;
  cout << "A imagem tem " << n_objects << " objetos, dos quais " << n_bolhas << " contêm bolhas" << endl;
  waitKey();
  return 0;
}

