#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <math.h>
#include <forward_list>
#include <queue>
#include <climits>

using namespace std;

class Channel
{
public:
	string color;
	bool blacklisted;
	forward_list<int> adj;
	int distance;
	//int predecessor;
	Channel()
	{
		distance = -1;
		//predecessor = -1;
		color = "w";
		blacklisted = false;
		//lista_adjacencia = new forward_list();
	}
};

void connectChannels(Channel channels[], int source, int maxChannels)
{
	int minChannel = 0;
	int opResults[5]; // minus1, plus1, half, times2, times3;
	// -1
	opResults[0] = source - 1;
	// +2
	opResults[1] = source + 1;
	// half
	opResults[2] = source % 2 == 0 ? source / 2 : -1;
	// times2
	opResults[3] = source * 2;
	// times3
	opResults[4] = source * 3;

	for (int i = 0; i < 5; i++)
	{
		if (opResults[i] >= 1 && opResults[i] <= maxChannels && !channels[opResults[i]].blacklisted)
		{
			channels[source].adj.push_front(opResults[i]);
		}
	}
};

int BFSChannels(Channel channels[], int startPos, int targetPos, int maxChannels)
{
	/*Channel source = channels[startPos];
	Channel target = channels[targetPos];
*/
	connectChannels(channels, startPos, maxChannels);

	channels[startPos].color = "g";
	channels[startPos].distance = 0;
	queue<int> Q;
	Q.push(startPos);

	while (Q.size() != 0)
	{
		int u = Q.front();
		Q.pop();
		for (int adj : channels[u].adj)
		{
			if (channels[adj].blacklisted)
				continue;

			if (channels[adj].color == "w")
			{
				channels[adj].color = "g";
				channels[adj].distance = channels[u].distance + 1;
				if (targetPos == adj)
					return channels[adj].distance;
				connectChannels(channels, adj, maxChannels);

				Q.push(adj);
			}
			
		}
		channels[u].color = "b";
	}
	return -1;
};

int main()
{
	string line;
	int lineNumber = 1;
	int firstChannel;
	int secondChannel;
	int nBlacklisted;
	Channel *channels;
	std::vector<int> result;
	int maxChannels = pow(10, 5);

	while (getline(cin, line))
	{
		if (lineNumber++ % 2 != 0)
		{
			channels = new Channel[maxChannels + 1];
			std::istringstream iss(line);

			std::vector<int> firstLine(std::istream_iterator<int>{iss},
				std::istream_iterator<int>());

			firstChannel = firstLine.at(0);
			secondChannel = firstLine.at(1);
			nBlacklisted = firstLine.at(2);

			if (firstChannel == 0 &&
				secondChannel == 0 &&
				nBlacklisted == 0) break;

			if (nBlacklisted == 0) {
				int distance = BFSChannels(channels, firstChannel, secondChannel, maxChannels);
				result.push_back(distance);
				printf("%d\n", distance);
				//printf("\n");
				lineNumber++;
			}
			firstLine.clear();
			
		}
		else 
		{
			if ((nBlacklisted != 0)) {
				std::istringstream iss2(line);
				int blacklistItem;
				while (iss2 >> blacklistItem)
				{
					channels[blacklistItem].blacklisted = true;
				}
				iss2.clear();
			}

			int distance = BFSChannels(channels, firstChannel, secondChannel, maxChannels);
			result.push_back(distance);
			printf("%d\n", distance);
			//printf("\n");
		}		
	}
	/*for (int& i : result) {
		cout << i << endl;
	}*/
	//cout << "" << endl;
	
	return 0;
}
