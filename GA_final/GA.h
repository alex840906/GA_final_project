void init(vector<vector<int>> &);
void crossover();
void selectionD();
void fitness();
void mutation();

void init(vector<vector<int>> &chromosome)
{
	chromosome.resize(8);

	int r;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			r = rand() % 4;
			chromosome[i].push_back(r);
		}
	}
}

void fitness(vector<vector<int>> &map_of_warehouse)
{
	int i, j;
	int redbox_count=0;
	vector<vector<int>> redbox;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{

		}
	}
}