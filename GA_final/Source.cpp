#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <time.h>
#include <cmath>

using namespace cv;
using namespace std;

/* 全域變數 */
vector<vector<int> > map_of_warehouse,map_of_redbox(1),map_of_yellowbox;
vector<int> fitness_of_chromosome(8),best_chromosome;
vector<int>  map_of_worker(2);
const int left_up_corner_x = 250, left_up_corner_y = 150;
const int side_length = 50;
const int n = 10;
int num_yellow=1, num_red=1;
int fitness_of_bestchromosome=100;
Mat img(800, 1000, CV_8UC3, Scalar(56, 50, 38)),ini_img(800, 1000, CV_8UC3, Scalar(56, 50, 38));
#include "GUI.h"
#include "GA.h"

int main(int argc, char const *argv[]) {
	
	namedWindow("Warehouse", WINDOW_AUTOSIZE);
	srand(time(NULL));
	
	//imshow("Warehouse", img);
	//cvWaitKey(1000);

	int cvWaitKey (int delay = 1000);

	/* 解 0:上 1:下 2:左 3:右 */
	vector<vector<int>> chromosome;
	bool flag = 0;

	init(chromosome);
	
	int iteration = 0;
	char buf[32];
	while (iteration <= 1000 && flag==0)
	{
		sprintf_s(buf, "%d", iteration);
		
		for (int i = 0; i < 8; i++)
		{
			img = ini_img.clone();
			init_setting();
			putText(img, buf, Point(30, 150), 3, 0.8, Scalar(255, 255, 255), 1, CV_AA);
			imshow("Warehouse", img);
			cvWaitKey(1);
			for (int j = 0; j < chromosome[i].size(); j++)
			{
				update_map_of_warehouse(map_of_warehouse, map_of_worker, chromosome[i][j]);

				imshow("Warehouse", img);
				cvWaitKey(1);

				flag = if_yellowbox_on_target();

				if (flag == 1)
				{
					putText(img, "WIN", Point(250, 500), 1, 20, Scalar(255, 191, 0), 10, CV_AA);
					imshow("Warehouse", img);
					cvWaitKey(100);
					break;
				}
			}
			if (flag == 1)
				break;
			fitness(map_of_warehouse, i,chromosome);
		}
		//selectionD(fitness_of_chromosome, chromosome);
		selection_tournament(fitness_of_chromosome, chromosome);
		crossover(chromosome);
		mutation(chromosome);
		iteration++;
		cout << "fitness of best chromosome " << fitness_of_bestchromosome << endl;
	}

	waitKey(0);
	return 0;
}

