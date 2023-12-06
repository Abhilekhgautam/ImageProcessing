#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;

void show_negative_image(Mat img);
void show_black_white_image(Mat img);
void show_brightend_image(Mat img);

int main(){
  Mat messi_img = imread("/home/abhilekh/Downloads/messi.jpg", IMREAD_COLOR); 
  Mat hazy_img  = imread("/home/abhilekh/Downloads/hazy_img.jpg", IMREAD_GRAYSCALE);

  const char window_with_orginal_messi_image[] = "Original Image";
  const char window_with_hazy_image[] = "Hazy Image";
  //imshow(window_with_orginal_messi_image, messi_img);
  imshow(window_with_hazy_image, hazy_img);
  //show_negative_image(messi_img);
  //show_black_white_image(messi_img);
  show_brightend_image(hazy_img);
  waitKey(0);
  return 0;
}

void show_negative_image(Mat img){
  const char window_with_negative_image[] = "Negative Image";
  MatIterator_<Vec3b> it, end;
  for( it = img.begin<Vec3b>(), end = img.end<Vec3b>(); it != end; ++it){
    (*it)[0] = 255 - (*it)[0];
    (*it)[1] = 255 - (*it)[1];
    (*it)[2] = 255 - (*it)[2];
   }
  imshow(window_with_negative_image, img);
}

void show_black_white_image(Mat img){
  const char window_with_black_and_white_image[] = "Window With Black & White Image";
  MatIterator_<Vec3b> it, end;
  for(it = img.begin<Vec3b>(), end = img.end<Vec3b>() ; it != end ; ++it){
    if(
      (*it)[0] > 128 && (*it)[1] > 128 && (*it)[2] > 128){
	 (*it)[0] = 0;
	 (*it)[1] = 0;
	 (*it)[2] = 0;    
    } else {
       (*it)[0] = 255;
       (*it)[1] = 255;
       (*it)[2] = 255;
    }
  }
  imshow(window_with_black_and_white_image, img);
}

//todo
void show_brightend_image(Mat img){
  const char window_with_brightened_image[] = "Brightened Image";

  pow(img, 3.0, img);
  imshow(window_with_brightened_image, img); 
}
