// uva10189.cpp : Defines the entry point for the console application.
//

using namespace std;

#include <iostream>
#include <vector>
#include <list>
#include <cstring>

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
    char* answer;
    vector<pos_type> MineMap;

    void Initialize(int m, int n) {
        dimM = m;
        dimN = n;
        answer = new char[dimM*dimN];
        //memset(answer, '0', sizeof(char)*dimM*dimN);
        for (int i=0;i<dimM*dimN;i++) answer[i] = '0';
    }

    inline int index(int x, int y) {
        if (x < 0 || y < 0 || x >= dimM || y >= dimN) return -1; 
        else return x + dimM*y;
    };

    void MarkMinePosition(pos_type p) {
        int minepos = index(p.x, p.y);
        if (minepos >=0 && minepos < MapSize) answer[minepos] = '*';
        for (int i = p.x - 1; i <= p.x + 1; i++)
        {
            for (int j = p.y - 1; j <= p.y + 1; j++)
            {
                int k = index(i, j);
                if (k >= 0 && k < MapSize)
                {
                    if (answer[k] != '*' ) answer[k]++;
                }
            }
        }
    };

public:
    MineSweeper(int cid) : CaseId(cid) {
    };
    ~MineSweeper() {
        delete [] answer;
    };

    bool ReadInput(istream& in) {
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

        Initialize(m, n);
    };

    const void CalcAnswer() {
        vector<pos_type>::iterator it = MineMap.begin();
        while (it != MineMap.end()) {
            MarkMinePosition(*it);
            it++;
        }
    };
    const void PrintResult(ostream& out) {
        out << endl;
        out << "Field #" << CaseId << ":" << endl;
        for (int i = 0; i < MapSize; i++);
        int i = 0;
        while (true)
        {
            out << answer[i];
            if ((i + 1) % dimM == 0) out << endl;
            
            if (++i == MapSize) break;
        }
    };
};


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

