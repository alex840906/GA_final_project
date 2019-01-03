#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <time.h>

using namespace cv;
using namespace std;

/* 全域變數 */
vector<vector<int> > map_of_warehouse,map_of_redbox(1);
vector<int>  map_of_worker(2);
const int left_up_corner_x = 250, left_up_corner_y = 150;
const int side_length = 50;
const int n = 10;
Mat img(800, 1000, CV_8UC3, Scalar(56, 50, 38));
#include "GUI.h"

int main(int argc, char const *argv[]) {
	
	namedWindow("Warehouse", WINDOW_AUTOSIZE);
	srand(time(NULL));

	/* 畫格子 */
	draw_grid();

	/* 文字 */
	putText(img, "circle: worker", Point(30, 30), 3, 0.8, Scalar(255, 181, 181), 1, CV_AA);
	putText(img, "yellow rectangle: box", Point(30, 60), 3, 0.8, Scalar(15, 185, 255), 1, CV_AA);
	putText(img, "red rectangle: destination", Point(30, 90), 3, 0.8, Scalar(0, 0, 205), 1, CV_AA);

	
	/* 初始化設定 */
	/* 可走的路 = 0, 牆壁 = 1, 圓形 = 2, 黃箱 = 3, 紅箱 = 4 */
	draw_wall(map_of_warehouse, n);
	init_worker(6, 3, map_of_worker);
	draw_yellow_rectangle(7, 3 );
	draw_red_rectangle(8, 3);
	//init_redbox();
	

	imshow("Warehouse", img);
	cvWaitKey(1000);

	int cvWaitKey (int delay = 1000);

	/* 解 0:上 1:下 2:左 3:右 */
	vector<int> chromosome(100, 0);

	for (int i = 0; i < 100; i++)
	{
		int r;
		r = rand() % 4;
		chromosome[i] = r;
	}
		
	int flag = 0;

		for (int s = 0; s < chromosome.size(); s++)
		{
			update_map_of_warehouse(map_of_warehouse, map_of_worker,chromosome[s]);
			debug_print_map();
			cout << endl;
			
			imshow("Warehouse", img);
			cvWaitKey(100);

			flag = if_yellowbox_on_target();

			if (flag == 1)
			{
				putText(img, "WIN", Point(250, 500), 1, 20, Scalar(255, 191, 0), 10, CV_AA);
				imshow("Warehouse", img);
				break;
			}
		}

	waitKey(0);
	return 0;
}

