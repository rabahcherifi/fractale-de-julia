#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <complex> 
#include <thread>
#include <semaphore.h> 
#include <chrono>
#include <pthread.h> 
#include <time.h> 
#include <iostream>
#include <fstream>
typedef std::chrono::high_resolution_clock Clock;

//mesure de temps code pris sur http://stackoverflow.com/questions/3220477/how-to-use-clock-in-c

using namespace std;
using namespace cv;
Mat image;

 #define ITERATIONMAX 400
 #define V 4
 #define HEIGHT 500
 #define WIDTH 500
#define Nb_Thread 10


long double r=0.400,i=-0.192;
double H = 0;
double W = 0;

void *Julia(void *arg);
void hsvtorgb(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char h, unsigned char s, unsigned char v);

int main( int argc, char** argv )
{
pthread_t thread[Nb_Thread];
  image = cv::Mat(WIDTH, HEIGHT, CV_8UC3);//décalaration de l'image
 auto t1 = Clock::now(); 
refresh:
for(int i=0;i<Nb_Thread;i++)
{  
pthread_create(&thread[i], NULL, Julia, (void*)NULL);
}
 auto t2 = Clock::now();
    std::cout << "temps de calcul: " 
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " nanoseconds -> " <<(std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count())*pow(10,-9)<<" secondes"<< std::endl;

     
 while(char key = cvWaitKey(66)) {
    switch(key){
      case 'a':
      

      // Modification de la fractale à la volée 
      r = r + 0.1;
      goto refresh;
      break;
      case 'z':
      
      r = r - 0.1;
      goto refresh;
      break;
      case 'o':
      
      i = i + 0.1;
      goto refresh;
      break;
      case 'p':
      
      i = i - 0.05;
      goto refresh;
      break;

      /* Zoom/Dezomm */
      case 'd':
      
      H -= 100;
      W -= 100;
      goto refresh;
      break;
      case 's':
     
      H += 100;
      W += 100;
      goto refresh;
      break;

      default:
      break;
    }
    if (key == 'q')
    break;
    imshow("fractale",image ); 
  }
  cvDestroyWindow("fractale"); // ferme la fenêtre
  
 
  return 0;
}

 void *Julia(void *arg){// calcul de julia
std::complex<long double> c(r, i);// constante c
  for(int x=0;x<WIDTH;x++){
      for(int y=0;y<HEIGHT;y++){
        long double newX=((long double)((long double)x-((long double)((WIDTH)-H)/2))/((long double)((WIDTH)-H)/2));
        long double newY=((long double)((long double)y-((long double)((HEIGHT)-W)/2))/((long double)((HEIGHT)-W)/2));
        std::complex<long double> point(newX,newY);//initialisation z=x+iy
        int iteration=0; //calcul de la suite debut
        long double norm = std::norm(point);
        while(iteration<ITERATIONMAX && norm<V){
          point=(point*point)+c;//calcul z+1=z*z+c
          norm = std::norm(point);//on regarde la norme du nouveau point 
          iteration++;
        } //calcul de la suite fin
        if(iteration==ITERATIONMAX && norm<V){//si la suite est borné on est dans julia et on met du noir o
          image.at<Vec3b>(x,y)[0]=0; 
          image.at<Vec3b>(x,y)[1]=0; 
          image.at<Vec3b>(x,y)[2]=0;
        }
       =r; 
      }
    } 
  }
return NULL;
 }



/*
code HSV TO BGR
https://www.google.fr/url?sa=t&rct=j&q=&esrc=s&source=web&cd=2&ved=0ahUKEwj5iou-p8HQAhWhDMAKHboNDrMQFgghMAE&url=http%3A%2F%2Fweb.mit.edu%2Fstorborg%2FPublic%2Fhsvtorgb.c&usg=AFQjCNHe9EYe6Aj2imOGGEWkkRJIMQfK5A&bvm=bv.139782543,d.ZGg
*/

void
hsvtorgb(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char h, unsigned char s, unsigned char v)
{
    unsigned char region, fpart, p, q, t;
    
 
    }
    
    return;
}
