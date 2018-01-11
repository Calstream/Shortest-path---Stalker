#include<fstream>
#include<vector>
#include<deque>
#include<climits>
#include<unordered_map>
#include<iostream>

class Graph
{
public:
	int n; // количество зданий
	int k; // количество карт
	std::unordered_map<int, std::vector<std::pair<int, int>>> adj; // пара(карта,здание) - cписок смежности
	std::vector<int> dist; // расстояние
	std::deque<int> deq;

	void make_graph()
	{
		std::ifstream inp;
		inp.open("input.txt");
		/*string ignore;
		getline(input, ignore);*/
		for (int i = 1; i <= k; ++i)
		{
			int roads_on_map;
			inp >> roads_on_map;
			for (int j = 1; j <= roads_on_map; ++j)
			{
				int b1;
				inp >> b1;
				int b2;
				inp >> b2;

				int b1_on_i = i * n + ((b1 - 1) % n); // первое здание на iй карте
				int b2_on_i = i * n + ((b2 - 1) % n); // второе здание на iй карте

				//соединить здания бесплатной дорогой
				adj[b1_on_i].emplace_back(b2_on_i, 0);
				adj[b2_on_i].emplace_back(b1_on_i, 0);

				//соединить здания с фиктивной картой бесплатной дорогой
				adj[b1_on_i].emplace_back(b1_on_i % n, 0);
				adj[b2_on_i].emplace_back(b2_on_i % n, 0);

				//соединить фиктивную карту с зданиями платной дорогой  
				adj[(b1 - 1) % n].emplace_back(b1_on_i, 1);
				adj[(b2 - 1) % n].emplace_back(b2_on_i, 1);
			}
		}
		inp.close();
	}

	void bfs()
	{
		deq.push_back(0);
		dist[0] = 0;
		while (!deq.empty())
		{
			int v = deq.front();
			deq.pop_front();
			for (int i = 0; i < adj[v].size(); ++i)
				if (dist[adj[v][i].first] > dist[v] + adj[v][i].second)
				{
					dist[adj[v][i].first] = dist[v] + adj[v][i].second;
					if (adj[v][i].second == 0)
						deq.push_front(adj[v][i].first);
					else
						deq.push_back(adj[v][i].first);
				}
		}
	}

	void out()
	{
		
	}
};


int main()
{
	Graph g = Graph();

	std::ifstream inp;
	inp.open("input.txt");
	int n1;
	inp >> n1;
	inp >> g.n;
	inp >> g.k;
	inp.close();
	int t = g.n * g.k + g.n;
	g.dist.resize(t);
	for (int i = 0; i < g.dist.size(); ++i)
		g.dist[i] = INT_MAX;

	g.make_graph();
	g.bfs();
	if (g.dist[g.n - 1] == INT_MAX)
		std::cout << -1;
	else
		std::cout << g.dist[g.n - 1];
}
