#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

const int NUMBER = 100000;
const int DELAY = 5;


const int window_width = 900;
const int window_height = 600;

int x_1 = -window_width/2;
int x_2 = window_width*3/2;
int y_1 = -window_width/2;
int y_2 = window_width*3/2;

int DrawRandomLines(Mat img, const char* window_name, RNG rng);

static Scalar randomColor( RNG& rng ){
  int icolor = (unsigned) rng;
  return Scalar( icolor&255, (icolor>>8)&255, (icolor>>16)&255 );
}

int main(){
 // SHOULD BE A RAND NUM GENERATOR
 RNG rng(0xFFFFFFFF);	

 const char* window_name = "Random Number Generation";

 Mat image = Mat::zeros(window_height, window_width, CV_8UC3);

 DrawRandomLines(image, window_name, rng);
 waitKey(0);

 return 0;
}

int DrawRandomLines(Mat img, const char* window_name, RNG rng){
  
  Point p1, p2;	

  for(int i = 0 ; i < NUMBER ; ++i){
    p1.x = rng.uniform(x_1,x_2);
    p1.y = rng.uniform(y_1, y_2);
    p2.x = rng.uniform(x_1, x_2);
    p2.y = rng.uniform(y_1, y_2);

    line(img, p1, p2, randomColor(rng),rng.uniform(1, 10), 8 );
    imshow(window_name, img);

    waitKey( DELAY ); 
  }
  return 0;
}
