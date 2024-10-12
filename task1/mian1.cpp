#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main(){
 
   
   
   Mat img = cv::imread("/home/user/桌面/cv2/train/resources/task1_2.png");	// 读取图像
	if (img.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}
    
    
     namedWindow("max", cv::WINDOW_FREERATIO);
   namedWindow("min", cv::WINDOW_FREERATIO); 
    namedWindow("img", cv::WINDOW_FREERATIO);
     namedWindow("1", cv::WINDOW_FREERATIO);
    namedWindow("origin", cv::WINDOW_FREERATIO);
   imshow("origin",img);

   Mat img1, img2;
   img.copyTo(img1);//
   img.copyTo(img2);//
   
   imshow("img",img);

   //
   Mat canny;
   Canny(img, canny, 80, 160, 3, false);
  
   imshow("1",canny);

   //
   Mat kernel =getStructuringElement(0,Size(3, 3));


   Mat gray, binary;
   cvtColor(img,gray, COLOR_BGR2GRAY);//转换为灰度图
   GaussianBlur(gray, gray,Size(13, 13), 4, 4);//平滑滤波
   threshold(gray, binary, 100, 255, THRESH_BINARY | THRESH_OTSU);//自适应二值化

   //轮廓发现与检测
   vector<vector<Point>>contours;//轮廓
   vector<Vec4i>hierarchy;//存放轮廓结构变量

   findContours(binary, contours, hierarchy, 0, 2, Point());

   //
   for(int n=0;n < contours.size();n++){
    //
    Rect rect =boundingRect(contours[n]);
    rectangle(img1, rect, Scalar(0, 0, 255 ),2, 8 , 0);

    //
    RotatedRect rrect = minAreaRect(contours[n]);
    Point2f points[4];
    rrect.points(points);//
    Point2f cpt =rrect.center;//

    //
    for (int i=0;i<4;i++){
       
       if(i == 3)
       {
         line(img2, points[i],points[0],Scalar(0, 255, 0),2, 8, 0);
         break;

       }
       line(img2, points[i], points[i+1],Scalar(0,255,0),2,8, 0);


    }
     //
     circle(img2,cpt,4,Scalar(255,0,0),-1,8,0);

   }
   //
  
   
   imshow("max",img1);
   imshow("min",img2);

   cout<<"list"<<endl;
   waitKey(0);

   Mat approx=imread("/home/user/桌面/cv2/train/resources/task1_2.png");
   if (approx.empty())
   {
      cout<<"plese checkout"<<endl;
      return -1;
   }
    //
    Mat canny2;
    Canny(approx, canny2, 80, 160, 3,false);
    //
    Mat kernel2=getStructuringElement(0,Size(3, 3));
    
   //绘制

   for(int i=0; i< hierarchy.size();i++){

      cout<<hierarchy[i]<<endl;
   }
   
   for (int t = -1;t < contours. size();t++)
   {
      drawContours(img, contours, t, Scalar(0, 0, 255), 2, 8);
      imshow("the result", img);
      imwrite(" /home/user/桌面/cv2/train/resources/damn.png",img);
      waitKey(0);


}




return 0;


}
