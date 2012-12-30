#include "AuxiliaryFunctions.h"

vector <string> stringExplode(string str, string separator)
{
	vector <string> results;

	int found;
	found = str.find_first_of(separator);
	while (found != string::npos)
	{
		if (found > 0)
		{
			results.push_back(str.substr(0, found));
		}
		str = str.substr(found + 1);
		found = str.find_first_of(separator);
	}
	if (str.length() > 0)
	{
		results.push_back(str);
	}

	return results;
}


vector <int> idToLinCol(int id)
{
	vector <int> toReturn;

	int lin = id % 10;

	toReturn.push_back(abs(lin - 8));

	int col = id / 10;

	toReturn.push_back(col - 1);

	return toReturn;
}

int linColToId(int lin, int col)
{
	int id = 0;

	id = col + 1;
	id *= 10;
	id += abs(lin - 8);

	return id;
}