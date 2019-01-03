/* UI function */
void init_setting();
void init_map(vector<vector<int>>&);
void debug_print_map();
void draw_grid();
void update_map_of_warehouse(vector<vector<int>>&, vector<int>&, int);
void init_worker(int, int, vector<int>&);
void init_redbox();
void draw_wall(vector<vector<int> > &, int);
void draw_circle(int, int); 
void draw_rectangle(int, int);
void draw_yellow_rectangle(int, int);
void draw_red_rectangle(int, int);
void draw_purple_rectangle(int, int);
void map_1();
void init_yellowbox();
int if_yellowbox_on_target();


void init_setting()
{
	/* ��r */
	putText(img, "circle: worker", Point(30, 30), 3, 0.8, Scalar(255, 181, 181), 1, CV_AA);
	putText(img, "yellow rectangle: box", Point(30, 60), 3, 0.8, Scalar(15, 185, 255), 1, CV_AA);
	putText(img, "red rectangle: destination", Point(30, 90), 3, 0.8, Scalar(0, 0, 205), 1, CV_AA);
	/* �e��l */
	draw_grid();
	init_map(map_of_warehouse);
	/* ��l�Ƴ]�w */
	/* �i������ = 0, ��� = 1, ��� = 2, ���c = 3, ���c = 4 */
	draw_wall(map_of_warehouse, n);
	init_worker(6, 3, map_of_worker);
	draw_yellow_rectangle(7, 3);
	draw_red_rectangle(8, 3);
}
void init_map(vector<vector<int>>& map_of_warehouse)
{
	map_of_warehouse.resize(10);
	for (int i = 0; i < 10; i++)
	{
		map_of_warehouse[i].resize(10);
	}

	for(int i=0;i<10;i++)
		for (int j = 0; j < 10; j++)
		{
			map_of_warehouse[i][j] = 0;
		}
}
void debug_print_map()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << map_of_warehouse[i][j];

		cout << endl;
	}
}
void draw_grid()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			rectangle(img, Point(left_up_corner_x + i * side_length, left_up_corner_y + j * side_length),
				Point(left_up_corner_x + side_length + i * side_length, left_up_corner_y + side_length + j * side_length),
				Scalar(181, 181, 181), 3);
		}
	}
}
void init_worker(int x, int y, vector<int> &map_of_worker)
{
	map_of_worker[0] = x;
	map_of_worker[1] = y;
	draw_circle(map_of_worker[0], map_of_worker[1]);
}
void init_redbox()
{
	//int num;
	int x, y;
	cin >> num_red;
	map_of_redbox.resize(num_red);

	for (int i = 0; i < num_red; i++)
	{
		cin >> x >> y;
		map_of_redbox[i].push_back(x);
		map_of_redbox[i].push_back(y);
	}

	for (int i = 0; i < num_red; i++)
		draw_red_rectangle(map_of_redbox[i][0], map_of_redbox[i][1]);
}

void draw_wall(vector<vector<int> > &map_of_warehouse, int n)
{
	//map_of_warehouse.resize(n);

	/*for (int i = 0; i < n; i++)
		map_of_warehouse[i].resize(n);*/

	for (int i = 0; i < n; i++)
		map_of_warehouse[0][i] = 1;
	for (int i = 0; i < n; i++)
		map_of_warehouse[n - 1][i] = 1;
	for (int i = 0; i < n; i++)
		map_of_warehouse[i][0] = 1;
	for (int i = 0; i < n; i++)
		map_of_warehouse[i][n - 1] = 1;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map_of_warehouse[i][j] == 1)
			{
				rectangle(img, Point(left_up_corner_x + i * side_length, left_up_corner_y + j * side_length),
					Point(left_up_corner_x + side_length + i * side_length, left_up_corner_y + side_length + j * side_length),
					Scalar(181, 181, 181), -1);
			}
		}
	}
}

void update_map_of_warehouse(vector<vector<int>> &map_of_warehouse, vector<int> &map_of_worker, int direction)
{
	int x = 0, y = 0;
	x = map_of_worker[0];
	y = map_of_worker[1];

	/* ���W�� */
	if (direction == 0)
	{
		if (map_of_warehouse[x - 1][y] == 0)
		{
			draw_circle(x - 1, y);

			if (map_of_warehouse[x][y] == 5)
				draw_red_rectangle(x, y);
			else
				draw_rectangle(x, y);
		}

		else if (map_of_warehouse[x - 1][y] == 1)
			;//�W���O�� do nothing

		/* �W�������c */
		else if (map_of_warehouse[x - 1][y] == 3)
		{
			if (map_of_warehouse[x - 2][y] == 1)
				;//���c�W������Ado nothing

			/* ���c�W�����c */
			else if (map_of_warehouse[x - 2][y] == 4)
			{
				draw_purple_rectangle(x - 2, y);
				draw_rectangle(x - 1, y);
				draw_circle(x - 1, y);
				draw_rectangle(x, y);
			}

			else
			{
				draw_yellow_rectangle(x - 2, y);
				draw_rectangle(x - 1, y);
				draw_circle(x - 1, y);
				draw_rectangle(x, y);
			}
		}

		/* �W�������c */
		else if (map_of_warehouse[x - 1][y] == 4)
		{
			draw_circle(x - 1, y);
			draw_rectangle(x, y);
		}

		/* �W�������c */
		else if (map_of_warehouse[x - 1][y] == 6)
		{
			/* ���c�W������Ado nothing */
			if (map_of_warehouse[x - 2][y] == 1)
				;

			/* ���c�W�����c�Ado nothing */
			else if (map_of_warehouse[x - 2][y] == 3)
				;
			/* ���c�W�����c */
			else if (map_of_warehouse[x - 2][y] == 4)
			{
				draw_purple_rectangle(x - 2, y);
				draw_red_rectangle(x - 1, y);
				draw_circle(x - 1, y);
				draw_rectangle(x, y);
			}
			else
			{
				draw_yellow_rectangle(x - 2, y);
				draw_red_rectangle(x - 1, y);
				draw_circle(x - 1, y);
				//draw_rectangle(x, y);
			}
			draw_rectangle(x, y);
		}
	}

	/* ���U�� */
	else if (direction == 1)
	{
		if (map_of_warehouse[x + 1][y] == 0)
		{
			draw_circle(x + 1, y);

			if (map_of_warehouse[x][y] == 5)
				draw_red_rectangle(x, y);
			else
				draw_rectangle(x, y);
		}

		else if (map_of_warehouse[x + 1][y] == 1)
			;//�U���O�� do nothing

		/* �U�������c */
		else if (map_of_warehouse[x + 1][y] == 3)
		{
			if (map_of_warehouse[x + 2][y] == 1)
				;//���c�U������Ado nothing

			/* ���c�U�����c */
			else if (map_of_warehouse[x + 2][y] == 4)
			{
				draw_purple_rectangle(x + 2, y);
				draw_rectangle(x + 1, y);
				draw_circle(x + 1, y);
				draw_rectangle(x, y);
			}

			else
			{
				draw_yellow_rectangle(x + 2, y);
				draw_rectangle(x + 1, y);
				draw_circle(x + 1, y);
				draw_rectangle(x, y);
			}
		}

		/* �U�������c */
		else if (map_of_warehouse[x + 1][y] == 4)
		{
			draw_circle(x + 1, y);
			draw_rectangle(x, y);
		}

		/* �U�������c */
		else if (map_of_warehouse[x + 1][y] == 6)
		{
			/* ���c�U������Ado nothing */
			if (map_of_warehouse[x + 2][y] == 1)
				;

			/* ���c�U�����c�Ado nothing */
			else if (map_of_warehouse[x + 2][y] == 3)
				;
			/* ���c�U�����c */
			else if (map_of_warehouse[x + 2][y] == 4)
			{
				draw_purple_rectangle(x + 2, y);
				draw_red_rectangle(x + 1, y);
				draw_circle(x + 1, y);
				draw_rectangle(x, y);
			}
			else
			{
				draw_yellow_rectangle(x + 2, y);
				draw_red_rectangle(x + 1, y);
				draw_circle(x + 1, y);
				//draw_rectangle(x, y);
			}
			draw_rectangle(x, y);
		}
	}
	///////////////// ������ ///////////////////////
	else if (direction == 2)
	{
		if (map_of_warehouse[x][y - 1] == 0)
		{
			draw_circle(x, y - 1);

			if (map_of_warehouse[x][y] == 5)
				draw_red_rectangle(x, y);
			else
				draw_rectangle(x, y);
		}

		else if (map_of_warehouse[x][y - 1] == 1)
			;//����O�� do nothing

		/* ���䬰���c */
		else if (map_of_warehouse[x][y - 1] == 3)
		{
			if (map_of_warehouse[x][y - 2] == 1)
				;//���c��������Ado nothing

			/* ���c�������c */
			else if (map_of_warehouse[x][y - 2] == 4)
			{
				draw_purple_rectangle(x, y - 2);
				draw_rectangle(x, y - 1);
				draw_circle(x, y - 1);
				draw_rectangle(x, y);
			}

			else
			{
				draw_yellow_rectangle(x, y - 2);
				draw_rectangle(x, y - 1);
				draw_circle(x, y - 1);
				draw_rectangle(x, y);
			}
		}

		/* ���䬰���c */
		else if (map_of_warehouse[x][y - 1] == 4)
		{
			draw_circle(x, y - 1);
			draw_rectangle(x, y);
		}

		/* ���䬰���c */
		else if (map_of_warehouse[x][y - 1] == 6)
		{
			/* ���c��������Ado nothing */
			if (map_of_warehouse[x][y - 2] == 1)
				;

			/* ���c�������c�Ado nothing */
			else if (map_of_warehouse[x][y - 2] == 3)
				;
			/* ���c�������c */
			else if (map_of_warehouse[x][y - 2] == 4)
			{
				draw_purple_rectangle(x, y - 2);
				draw_red_rectangle(x, y - 1);
				draw_circle(x, y - 1);
				draw_rectangle(x, y);
			}
			else
			{
				draw_yellow_rectangle(x, y - 2);
				draw_red_rectangle(x, y - 1);
				draw_circle(x, y - 1);
				//draw_rectangle(x, y);
			}
			draw_rectangle(x, y);
		}
	}
	//////////////// ���k�� /////////////////
	else if (direction == 3)
	{
		if (map_of_warehouse[x][y + 1] == 0)
		{
			draw_circle(x, y + 1);

			if (map_of_warehouse[x][y] == 5)
				draw_red_rectangle(x, y);
			else
				draw_rectangle(x, y);
		}

		else if (map_of_warehouse[x][y + 1] == 1)
			;//�k��O�� do nothing

		/* �k�䬰���c */
		else if (map_of_warehouse[x][y + 1] == 3)
		{
			if (map_of_warehouse[x][y + 2] == 1)
				;//���c�k������Ado nothing

			/* ���c�k�����c */
			else if (map_of_warehouse[x][y + 2] == 4)
			{
				draw_purple_rectangle(x, y + 2);
				draw_rectangle(x, y + 1);
				draw_circle(x, y + 1);
				draw_rectangle(x, y);
			}

			else
			{
				draw_yellow_rectangle(x, y + 2);
				draw_rectangle(x, y + 1);
				draw_circle(x, y + 1);
				draw_rectangle(x, y);
			}
		}

		/* �k�䬰���c */
		else if (map_of_warehouse[x][y + 1] == 4)
		{
			draw_circle(x, y + 1);
			draw_rectangle(x, y);
		}

		/* �k�䬰���c */
		else if (map_of_warehouse[x][y + 1] == 6)
		{
			/* ���c�k������Ado nothing */
			if (map_of_warehouse[x][y + 2] == 1)
				;

			/* ���c�k�����c�Ado nothing */
			else if (map_of_warehouse[x][y + 2] == 3)
				;
			/* ���c�k�����c */
			else if (map_of_warehouse[x][y + 2] == 4)
			{
				draw_purple_rectangle(x, y + 2);
				draw_red_rectangle(x, y + 1);
				draw_circle(x, y + 1);
				draw_rectangle(x, y);
			}
			else
			{
				draw_yellow_rectangle(x, y + 2);
				draw_red_rectangle(x, y + 1);
				draw_circle(x, y + 1);
				//draw_rectangle(x, y);
			}
			draw_rectangle(x, y);
		}
	}
}

void draw_circle(int x, int y)
{
	circle(img, Point(left_up_corner_x + y * side_length + side_length / 2, left_up_corner_y + x * side_length + side_length / 2), 20,
		Scalar(255, 181, 181), -1, CV_AA, 0);

	if (map_of_warehouse[x][y] == 4)
		map_of_warehouse[x][y] = 5;

	else
		map_of_warehouse[x][y] = 2;

	map_of_worker[0] = x;
	map_of_worker[1] = y;
}
void draw_rectangle(int x, int y)
{
	if (map_of_warehouse[x][y] == 5)
	{
		draw_red_rectangle(x, y);
	}
	else
	{
		rectangle(img, Point(left_up_corner_x + y * side_length + 3, left_up_corner_y + x * side_length + 3),
			Point(left_up_corner_x + side_length + y * side_length - 3, left_up_corner_y + side_length + x * side_length - 3),
			Scalar(56, 50, 38), -1);
		map_of_warehouse[x][y] = 0;
	}


}
void draw_yellow_rectangle(int x, int y)
{
	rectangle(img,
		Point(left_up_corner_x + y * side_length + 3, left_up_corner_y + x * side_length + 3),
		Point(left_up_corner_x + side_length + y * side_length - 3, left_up_corner_y + side_length + x * side_length - 3),
		Scalar(15, 185, 255), -1);

	map_of_warehouse[x][y] = 3;
}

void init_yellowbox()
{
	int x, y;
	cin >> num_yellow;
	map_of_yellowbox.resize(num_yellow);

	for (int i = 0; i < num_yellow; i++)
	{
		cin >> x >> y;
		map_of_yellowbox[i].push_back(x);
		map_of_yellowbox[i].push_back(y);
	}

	for (int i = 0; i < num_yellow; i++)
		draw_yellow_rectangle(map_of_yellowbox[i][0], map_of_yellowbox[i][1]);
}

void draw_red_rectangle(int x, int y)
{
	rectangle(img,
		Point(left_up_corner_x + y * side_length + 3, left_up_corner_y + x * side_length + 3),
		Point(left_up_corner_x + side_length + y * side_length - 3, left_up_corner_y + side_length + x * side_length - 3),
		Scalar(0, 0, 205), -1);

	map_of_redbox[0].resize(2);
	map_of_redbox[0][0] = x;
	map_of_redbox[0][1] = y;

	map_of_warehouse[x][y] = 4;
}
void draw_purple_rectangle(int x, int y)
{
	rectangle(img, Point(left_up_corner_x + y * side_length + 3, left_up_corner_y + x * side_length + 3),
		Point(left_up_corner_x + side_length + y * side_length - 3, left_up_corner_y + side_length + x * side_length - 3),
		Scalar(139, 0, 139), -1);

	map_of_warehouse[x][y] = 6;
}

int if_yellowbox_on_target()
{
	int flag = 0;

	for (int i = 0; i < map_of_redbox.size(); i++)
	{
		if (map_of_warehouse[map_of_redbox[i][0]][map_of_redbox[i][1]] == 6)
			flag = 1;
		else
		{
			flag = 0;
			break;
		}
	}
	return flag;
}

void map_1()
{

}