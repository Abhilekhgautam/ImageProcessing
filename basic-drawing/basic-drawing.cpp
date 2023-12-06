#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

const int W = 400;

void MyEllipse(cv::Mat img, double angle);
void MyFilledCircle(cv::Mat img, cv::Point center);

void MyTriangle(cv::Mat img);

int main(){
 const char atom_window[] = "Drawing 1: Atom";

 const char triangle_window[] = "Drawing 2: Triangle";

 cv::Mat atom_image = cv::Mat::zeros(W, W, CV_8UC3);
 cv::Mat triangle_image = cv::Mat::zeros(W, W, CV_8UC3);

 MyEllipse(atom_image, 90);
 MyEllipse( atom_image, 0 );
 MyEllipse( atom_image, 45 );
 MyEllipse( atom_image, -45 );

 MyFilledCircle(atom_image, cv::Point(W / 2, W / 2));
 MyTriangle(triangle_image);
 cv::imshow(atom_window, atom_image);
 cv::imshow(triangle_window, triangle_image);
 cv::waitKey(0);
 return 0;
}

void MyEllipse(cv::Mat img, double angle){
 cv::ellipse(img, cv::Point(W / 2, W/2), cv::Size(W / 4, W / 16), angle
 ,0, 360, cv::Scalar(255, 0, 0), 2, 8);	
}

void MyFilledCircle(cv::Mat img, cv::Point center){
   cv::circle(img, center, W / 32, cv::Scalar(0, 0, 255),cv:: FILLED, cv::LINE_8);	
}

void MyTriangle(cv::Mat img){
  cv::Point pts[1][3] = {cv::Point(W / 2, 0), cv::Point(0, W / 2), cv::Point(W , W /2)};

  const cv::Point* ppt[1] = {pts[0]};
  int npt[] = {3};

  cv::fillPoly(img, ppt, npt, 1, cv::Scalar(255, 0, 0));
}
