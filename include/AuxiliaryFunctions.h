#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H

#include <string>
#include <vector>

using namespace std;

vector<string> stringExplode(string str, string separator);
vector<int> idToLinCol(int id);
int linColToId(int lin, int col);

#endif /* AUX_FUNCTIONS_H */