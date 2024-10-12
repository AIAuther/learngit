#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include <iostream>
#include <vector>


using namespace cv;
using namespace std;

std::string getColorName(const Scalar& color) {
    if (color[2] > 200 && color[1] > 50 && color[0] > 50) return "红";
    else if (color[2] > 100 && color[1] > 200 && color[0] > 100) return "绿";
    else if (color[2] > 50 && color[1] > 50 && color[0] > 200) return "蓝";
    else if (color[2] > 200 && color[1] > 200 && color[0] < 50) return "黄";
    else return "黑";
}


int main(){
 
   
   
   Mat img = cv::imread("/home/user/桌面/cv2/task1/resources/task1_2.png");	// 读取图像
	if (img.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}
   namedWindow("result", cv::WINDOW_FREERATIO);
   
    // 转换为灰度图像
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // 进行边缘检测
    Mat edges;
    Canny(gray, edges, 50, 150);

    // 查找轮廓
    vector<vector<Point>> contours;
    findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    int shapeCount = 0;
    for (const auto& contour : contours) {
        // 近似轮廓为多边形
        vector<Point> approx;
        approxPolyDP(contour, approx, arcLength(contour, true) * 0.02, true);

        int vertices = approx.size();
        Scalar shapeColor;
        string shapeName;

        if (vertices == 3) {
            shapeColor = Scalar(0, 0, 255); // 三角形为red
            shapeName = "三角形";
        } else if (vertices == 4) {
            shapeColor = Scalar(255, 0, 0); // 四边形为蓝色
            shapeName = "四边形";
        } else if (isContourConvex(approx) && vertices > 4) {
            shapeColor = Scalar(0, 255, 0); // 圆形（近似）为绿色
            shapeName = "圆形";
        }

        // 计算图形的平均颜色
        cv::Rect boundingRect = cv::boundingRect(approx);
        Scalar avgColor = mean(img(boundingRect));

        // 在控制台输出图形的颜色信息
            string colorName = getColorName(avgColor);
          cout << "序号：" << shapeCount + 1 << "，形状：" << shapeName << "，颜色：" << colorName << endl;


        drawContours(img, vector<vector<Point>>{approx}, -1, shapeColor, 5);

        Point textPosition = approx[0];
        shapeCount++;
        putText(img, to_string(shapeCount), textPosition, FONT_HERSHEY_SIMPLEX, 5, Scalar(0, 0, 0), 2);
    }

    imshow("result", img);
    waitKey(0);

    return 0;
}