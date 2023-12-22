#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <filesystem>
#include <iostream>
#include <array>
namespace fs = std::filesystem;

const int width = 255 * 1;
const int height = 510;

//plots the Histogram for given frequencies.
//I don't know but I couldn't set the argument const..
void plotHistogram(cv::Mat& srcMat){
  std::array<int, 256> counts;
  counts.fill(0);
  cv::MatIterator_<uchar> It, end;
  for(It = srcMat.begin<uchar>(), end = srcMat.end<uchar>(); It != end ; ++It){
      counts[*It] = counts[*It] + 1;	   
  }

  cv::Mat histogram = cv::Mat::zeros(height, width, CV_8UC3);
  auto max = std::max_element(counts.begin(), counts.end());
  int maxVal = *max;
  std::cout << "Max:" << maxVal;
  float factor = (float) height / (float) maxVal;
  std::cout << factor << '\n';
  for(int i = 0 ; i < 256; ++i){
   
    //debugging stuff
    std::cout << "(" << i << ", " << height << ")" << " and " << "(" << i << "," <<  ( height - factor * counts[i])  << ")" << '\n';
    // this is a bug, leaving here so that you won't do this again
    // we are trying to fit in numbers from 0 to max Frequency to range 0 to height and that is kinda freaking right?
    //cv::line(histogram, cv::Point(i , height),cv::Point(i , height - (counts[i]) % height), cv::Scalar_<int>(0, 0, 255));
    cv::line(histogram, cv::Point(i * 1 , height),cv::Point(i * 1 ,  ( height - (factor * counts[i]))), cv::Scalar_<int>(0, 0, 255));
 
    }
   cv::imshow("Histogram", histogram);
   cv::waitKey(0);
}

int main(int argc, char** argv){
  if(argc != 2){
    std::cerr << "Error: Usage: " << argv[0] << " <filename>";
    std::exit(1);
  }
  if(!fs::exists(argv[1])){
    std::cerr << "Error: " << argv[1] << " : No such file exists";	  
    std::exit(1);
  }
  std::array<int, 256> counts;
  counts.fill(0);
  cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  const char window_name[] = "Source Image";

  //cv::imshow(window_name, img);
  //cv::waitKey(0);
   cv::MatIterator_<uchar> It, end;
   for(It = img.begin<uchar>(), end = img.end<uchar>(); It != end ; ++It){
      counts[*It] = counts[*It] + 1;	   
   }
   int count = 0;
   for(auto elt: counts){
      std::cout << count << ": " << elt << '\n';
      count++;
   }
   //auto add = [](const int& a, const int& b){return a + b;};
   //auto val = std::accumulate(counts.begin(), counts.end(), 0, add);
   plotHistogram(img);
  //cv::waitKey(0);
  return 0;
}
