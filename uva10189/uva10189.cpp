#include <iostream>
#include <vector>
#include <list>
//#include <cstring>
using namespace std;

class MineSweeper {
    typedef struct pos {
        int x;
        int y;
        pos(int _x, int _y) : x(_x), y(_y) {}
    } pos_type;

    int CaseId;
    int dimM;
    int dimN;
    int MapSize;
    vector<char> answer;
    vector<pos_type> MineMap;
public:
    MineSweeper(int cid) : CaseId(cid) {
    };
    void MarkMinePosition(pos_type p);
    bool ReadInput(istream& in);
    void CalcAnswer();
    void PrintResult(ostream& out);
    int index(int x, int y);
};

int MineSweeper::index(int x, int y) {
    if (x < 0 || y < 0 || x >= dimM || y >= dimN) return -1;
    else return x + dimM*y;
}

void MineSweeper::MarkMinePosition(pos_type p) {
    int minepos = index(p.x, p.y);
    if (minepos >= 0 && minepos < MapSize) answer[minepos] = '*';

    for (int i = p.x - 1; i <= p.x + 1; i++)
    {
        for (int j = p.y - 1; j <= p.y + 1; j++)
        {
            int k = index(i, j);
            if (k >= 0 && k < MapSize)
            {
                if (answer[k] != '*') answer[k]++;
            }
        }
    }
}

bool MineSweeper::ReadInput(istream& in) {
    int m, n = 0;
    in >> n >> m;
    if (m == 0 || n == 0) return false;

    MapSize = m*n;
    char c = '.';
    for (int i = 0; i < MapSize; i++)
    {
        in >> c;
        if (c == '*') MineMap.push_back(pos_type(i % m, i / m));
    }

    dimM = m;
    dimN = n;
    answer = vector<char>(m*n, '0');

    return true;
}

void MineSweeper::CalcAnswer() {
    vector<pos_type>::iterator it = MineMap.begin();
    while (it != MineMap.end()) {
        MarkMinePosition(*it);
        it++;
    }
}
void MineSweeper::PrintResult(ostream& out) {
    if (CaseId >= 2) out << endl;
    out << "Field #" << CaseId << ":" << endl;
    int i = 0;
    while (true)
    {
        out << answer[i];
        if ((i + 1) % dimM == 0) out << endl;
            
        if (++i >= MapSize) break;
    }
}


int main()
{
    int caseid = 1;
    while (true)
    {
        MineSweeper ms(caseid);
        bool ret = ms.ReadInput(cin);
        if (ret == false) break;
        ms.CalcAnswer();
        ms.PrintResult(cout);
        caseid++;
    }
    return 0;
}
