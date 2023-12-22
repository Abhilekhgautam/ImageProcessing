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
void plotHistogram(cv::Mat&);

void equalizeHistogram(cv::Mat srcMat){
 // new mat of same width and height
 cv::Mat destMat = srcMat.clone();
 cv::MatIterator_<uchar> it, end;
 cv::MatIterator_<uchar> It, End;
 // just for the sake of storing frequencies.
 std::array<int, 256> counts; 
 counts.fill(0);
 for(It = srcMat.begin<uchar>(), End = srcMat.end<uchar>(); It != End ; ++It){
   counts[*It] = counts[*It] + 1;	   
 }

 std::array<float, 256> prob;
 for(int i = 0 ; i < 256 ; ++i){
   prob[i] = (float)counts[i] /(float) (srcMat.rows * srcMat.cols);	 
 }
 // summing up probabilities
 for (int i = 1; i < 256; ++i) {
   prob[i] += prob[i - 1];
 }
 // (L - 1) times the sum of probabilities 
 for(it = destMat.begin<uchar>(), end = destMat.end<uchar>() ; it != end ; ++it){
   *it = 255 * prob[*it]; 
 }

 std::array<int, 256> newCounts;
 newCounts.fill(0);

 for(It = destMat.begin<uchar>(), End = destMat.end<uchar>(); It != End ; ++It){
   newCounts[*It] = counts[*It] + 1;	   
 }

 cv::imshow("Equalized",destMat);
 cv::waitKey(0);
 plotHistogram(destMat);
 cv::waitKey(0);
}
//plots the Histogram for given image.
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

  cv::imshow(window_name, img);
  cv::waitKey(0);
  cv::MatIterator_<uchar> It, end;
  for(It = img.begin<uchar>(), end = img.end<uchar>(); It != end ; ++It){
      counts[*It] = counts[*It] + 1;	   
  }
  int count = 0;
  for(auto elt: counts){
     std::cout << count << ": " << elt << '\n';
     count++;
  }
 // plotHistogram(counts);
  equalizeHistogram(img);
  return 0;
}


/*

sk = T(rk) = (L - 1) Summation_j_0_to_k(pr(rj))


rk -> kth intensity level
nk -> frequency of kth intensity pixel
probablity of occurence of rk intensity level.
pr(rk) = nk / total_pixels

*/
