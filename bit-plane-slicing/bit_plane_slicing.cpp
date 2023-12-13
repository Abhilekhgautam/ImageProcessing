#include <cstdlib>
#include <opencv2/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/base.hpp>
// c++17
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void display_msb_contribution(cv::Mat mat){
  const char* window_name = "MSB Contribution";
  // manipulatation logic

  cv::MatIterator_<char> it, end;
  for(it = mat.begin<char>(), end = mat.end<char>() ;  it != end ; ++it){
    *it = *it >> 7; 	  
  }

  cv::imshow(window_name, mat);
  cv::waitKey(0);
}

void display_msb_min_1_contribution(cv::Mat mat){
  const char* window_name = "MSB - 1 Contribution";
  // manipulatation logic

  cv::MatIterator_<uchar> it, end;
  for(it = mat.begin<uchar>(), end = mat.end<uchar>() ;  it != end ; ++it){
    *it = (*it & 0x40) >> 6; 
  }
  cv::imshow(window_name, mat);
  cv::waitKey(0);
}
void display_msb_min_2_contribution(cv::Mat mat){
  const char* window_name = "MSB - 2 Contribution";
  // manipulatation logic

  cv::MatIterator_<uchar> it, end;
  for(it = mat.begin<uchar>(), end = mat.end<uchar>() ;  it != end ; ++it){
    *it = (*it & 0x20) >> 5; 
  }
  cv::imshow(window_name, mat);
  cv::waitKey(0);
}

void display_msb_min_3_contribution(cv::Mat mat){
  const char* window_name = "MSB - 3 Contribution";
  // manipulatation logic

  cv::MatIterator_<uchar> it, end;
  for(it = mat.begin<uchar>(), end = mat.end<uchar>() ;  it != end ; ++it){
    *it = (*it & 0x10) >> 4; 
  }
  cv::imshow(window_name, mat);
  cv::waitKey(0);
}

void display_msb_min_4_contribution(cv::Mat mat){
  const char* window_name = "MSB - 4 Contribution";
  // manipulatation logic

  cv::MatIterator_<uchar> it, end;
  for(it = mat.begin<uchar>(), end = mat.end<uchar>() ;  it != end ; ++it){
    *it = (*it & 0x08) >> 3; 
  }
  cv::imshow(window_name, mat);
  cv::waitKey(0);
}

void display_msb_min_5_contribution(cv::Mat mat){
  const char* window_name = "MSB - 5 Contribution";
  // manipulatation logic

  cv::MatIterator_<uchar> it, end;
  for(it = mat.begin<uchar>(), end = mat.end<uchar>() ;  it != end ; ++it){
    *it = (*it & 0x04) >> 2; 
  }
  cv::imshow(window_name, mat);
  cv::waitKey(0);
}

void display_msb_min_6_contribution(cv::Mat mat){
  const char* window_name = "MSB - 6 Contribution";
  // manipulatation logic

  cv::MatIterator_<uchar> it, end;
  for(it = mat.begin<uchar>(), end = mat.end<uchar>() ;  it != end ; ++it){
    *it = (*it & 0x02) >> 1; 
  }
  cv::imshow(window_name, mat);
  cv::waitKey(0);
}


void display_lsb_contribution(cv::Mat mat){
  const char* window_name = "LSB Contribution";
  // manipulatation logic

  cv::MatIterator_<uchar> it, end;
  for(it = mat.begin<uchar>(), end = mat.end<uchar>() ;  it != end ; ++it){
    *it = *it << 7; 
  }
  cv::imshow(window_name, mat);
  cv::waitKey(0);
}


int main(int argc, char** argv){

 if(argc != 2){
   std::cerr << "Error: Usage: " << argv[0] << " <file_name>";
   exit(-1);
 }


 if(!fs::exists(argv[1])){
   std::cerr << "Error: " << argv[1] << " doen't exists";
   exit(-1);
 }
 
 const char original_image_window[] = "Orginal Window";
 cv::Mat org_image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
 cv::imshow(original_image_window, org_image);
 
 display_msb_contribution(org_image);
 display_msb_min_1_contribution(org_image);
 display_msb_min_2_contribution(org_image);
 display_msb_min_3_contribution(org_image);
 display_msb_min_4_contribution(org_image);
 //display_lsb_contribution(org_image);
 cv::waitKey(0);


 return 0; //happy compiler
}
