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

const int width = 256;
const int height = 800;

//plots the Histogram for given frequencies.
void plotHistogram(const std::array<int, 256>& counts){
 cv::Mat histogram = cv::Mat::zeros(height, width, CV_8UC3);
 for(int i = 0 ; i < 256; ++i){
   cv::line(histogram, cv::Point(i, height),cv::Point(i, height -(counts[i]) % height), cv::Scalar_<int>(0, 0, 255));	 
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
  }
  std::array<int, 256> counts;
  counts.fill(0);
  cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  const char window_name[] = "Source Image";

  //cv::imshow(window_name, img);

   cv::MatIterator_<uchar> It, end;
   for(It = img.begin<uchar>(), end = img.end<uchar>(); It != end ; ++It){
      counts[*It] = counts[*It] + 1;	   
   }

   for(auto elt: counts){
      std::cout << elt << '\n';	   
   }
   //auto add = [](const int& a, const int& b){return a + b;};
   //auto val = std::accumulate(counts.begin(), counts.end(), 0, add);
   plotHistogram(counts);
  //cv::waitKey(0);
  return 0;
}
