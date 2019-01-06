void GA_init_setting();
void init(vector<vector<int>> &);
void crossover(vector<vector<int>>&);
void selection_tournament(vector<int> &, vector<vector<int>> &);
void selectionD(vector<int> &, vector<vector<int>> &);
void fitness(vector<vector<int>> &,int , vector<vector<int>> &);
void mutation(vector<vector<int>> &);
#define mutation_rate 1
#define limit_path 15
#define crossover_rate 0.7

void GA_init_setting()
{

}
void init(vector<vector<int>> &chromosome)
{
	chromosome.resize(8);

	int r;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < limit_path; j++)
		{
			r = rand() % 4;
			chromosome[i].push_back(r);
		}
	}
	best_chromosome.resize(limit_path);
}

void fitness(vector<vector<int>> &map_of_warehouse,int num_of_chromosome , vector<vector<int>> &chromosome)
{
	int count=0;
	vector<vector<int>> distance;
	distance.resize(num_red);
	
	int total_distance = 0;
	for (int i = 0; i < num_red; i++)
	{
		int count = 0;
		if (map_of_warehouse[map_of_redbox[i][0]][map_of_redbox[i][1]] == 4 || map_of_warehouse[map_of_redbox[i][0]][map_of_redbox[i][1]]==5)
		{
			for (int j = 0; j < 10; j++)
			{
				for (int k = 0; k < 10; k++)
				{
					if (map_of_warehouse[j][k] == 3)
					{
						int sum = 0;
						sum = abs(j - map_of_redbox[i][0]) + abs(k - map_of_redbox[i][1]);
						distance[count].push_back(sum);
						distance[count].push_back(j);
						distance[count].push_back(k);
						count++;
					}
				}
			}
			int shortest = 100;
			int x, y;
			for (int j = 0; j < count; j++)
			{
				if (distance[j][0] <= shortest)
				{
					shortest = distance[j][0];
					x = distance[j][1];
					y = distance[j][2];
				}
			}
			total_distance += shortest;

			map_of_warehouse[x][y] = 0;
		}

	}

	fitness_of_chromosome[num_of_chromosome]=total_distance;

	if (fitness_of_bestchromosome > fitness_of_chromosome[num_of_chromosome])
	{
		fitness_of_bestchromosome = fitness_of_chromosome[num_of_chromosome];
		for (int i = 0; i < limit_path; i++)
			best_chromosome[i] = chromosome[num_of_chromosome][i];
	}

	if (fitness_of_bestchromosome == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
				cout << map_of_warehouse[i][j];
			cout << endl;
		}
	}
	//cout << "fitness of best" << fitness_of_bestchromosome << endl;
	cout << total_distance << endl;
}

void mutation(vector<vector<int>> &chromosome)
{
	int i, j,r;
	int direction;
	double possibility_to_mutation;

	for (i = 0; i < chromosome.size(); i++)
	{
		possibility_to_mutation = (double)rand() / RAND_MAX;
		if (possibility_to_mutation < mutation_rate)
		{
			r = rand() % limit_path;
			direction = rand() % 4;
			chromosome[i][r] = direction;
		}
	}
}

void selectionD(vector<int> &fitness_of_chromosome, vector<vector<int>> &chromosome)
{
	vector<float> pie_chart;
	int sum_of_fitnee=0;
	float dart;

	for (int i = 0; i < limit_path; i++)
		chromosome[7][i] = best_chromosome[i];

	for (int i = 0; i < chromosome.size(); i++)
		sum_of_fitnee += fitness_of_chromosome[i];
	
	pie_chart.resize(fitness_of_chromosome.size() + 1);

	pie_chart[0] = 0;

	float den=0;

	for (int i = 0; i < chromosome.size(); i++)
		pie_chart[i + 1] += (float)fitness_of_chromosome[i]/sum_of_fitnee;

	for (int i = 0; i < chromosome.size(); i++)
		den += (float)1 / pie_chart[i + 1];
	
	for (int i = 0; i < chromosome.size(); i++)
		pie_chart[i+1] = pie_chart[i] + (float)1/pie_chart[i + 1]/den;
	

	vector<int> selection_chromosome(8);

	for (int i = 0; i < chromosome.size(); i++)
	{ 
		dart = (double)rand() / RAND_MAX;

		for (int j = 0; j < chromosome.size(); j++)
		{
			if (dart >= pie_chart[j] && dart <= pie_chart[j + 1])
				selection_chromosome[i] = j;
		}
	}

	vector<vector<int>> tmp;
	tmp.assign(chromosome.begin(), chromosome.end());

	for (int i = 0; i < chromosome.size(); i++)
	{
		for (int j = 0; j < limit_path; j++)
		{
			chromosome[i][j] = tmp[selection_chromosome[i]][j];
		}
	}
}

void selection_tournament(vector<int> &fitness_of_chromosome, vector<vector<int>> &chromosome)
{
	vector<int> tournament(3);
	vector<vector<int>> tmp;
	int fitness_best_chromosome=100;
	int winner;

	for (int i = 0; i < limit_path; i++)
		chromosome[7][i] = best_chromosome[i];

	tmp.assign(chromosome.begin(),chromosome.end());
	
	for (int i = 0; i < chromosome.size(); i++)
	{
		fitness_best_chromosome = 100;
		for (int j = 0; j < tournament.size(); j++)
			tournament[j] = rand() % chromosome.size();

		for (int j = 0; j < tournament.size(); j++)
		{
			if (fitness_best_chromosome > fitness_of_chromosome[tournament[j]])
			{
				fitness_best_chromosome = fitness_of_chromosome[tournament[j]];
				winner = tournament[j];
			}
		}
		for (int j = 0; j < limit_path; j++)
		{
			chromosome[i][j] = tmp[winner][j];
		}
		
	}
}

void crossover(vector<vector<int>> &chromosome)
{
	int segmentation_point_1, segmentation_point_2;
	vector<int> index;

	index.resize(chromosome.size());
	for (int i = 0; i < chromosome.size(); i++)
		index[i] = i;

	int r_1, r_2;
	float possibility_to_cross;

	for (int i = 0; i < chromosome.size() / 2; i++)
	{
		r_1 = rand() % (index.size());
		r_2 = rand() % (index.size());
		while (r_2 == r_1)
			r_2 = rand() % (index.size());

		segmentation_point_1 = rand() % (limit_path - 1);
		segmentation_point_2 = rand() % (limit_path - segmentation_point_1 - 1) + segmentation_point_1 + 1;

		possibility_to_cross = (float)rand() / RAND_MAX;

		if (possibility_to_cross < crossover_rate)
		{
			int tmp;
			for (int j = segmentation_point_1 + 1; j <= segmentation_point_2; j++)
			{
				tmp = chromosome[index[r_1]][j];
				chromosome[index[r_1]][j] = chromosome[index[r_2]][j];
				chromosome[index[r_2]][j] = tmp;
			}

			r_1 = index[r_1];
			r_2 = index[r_2];
			vector<int>::iterator it = index.begin();

			for (; it != index.end();)
			{
				if (*it == r_1 || *it == r_2)
					it = index.erase(it);
				else
					++it;
			}
		}

		else
		{
			r_1 = index[r_1];
			r_2 = index[r_2];
			vector<int>::iterator it = index.begin();

			for (; it != index.end();)
			{
				if (*it == r_1 || *it == r_2)
					it = index.erase(it);
				else
					++it;
			}
		}
	}
}