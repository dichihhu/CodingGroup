// uva10189.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <list>


class MineSweeper {
    struct pos {
        int x;
        int y;
        pos(int _x, int _y) : x(_x), y(_y)
        {}
    };

    int CaseId;
    int dimM;
    int dimN;
    int MapSize;
    char* answer;
    vector<struct pos> MineMap;

    void Initialize(int m, int n) {
        dimM = m;
        dimN = n;
        answer = new char[dimM*dimN];
        memset(answer, '0', sizeof(char)*dimM*dimN);
    }

    inline int index(int x, int y) {
        if (x < 0 || y < 0 || x >= dimM || y >= dimN) return -1; 
        else return x + dimN*y;
};

    void MarkMinePosition(struct pos p) {
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
        //if (MapSize>1) 
            delete [] answer;
        //else delete answer;
    };

    bool ReadInput(istream& in) {
        int m, n = 0;
        in >> m >> n;
        if (m == 0 || n == 0) return false;

        MapSize = m*n;
        char c = '.';
        for (int i = 0; i < MapSize; i++)
        {
            in >> c;
            if (c == '*') MineMap.push_back(struct pos(i % m, i / m));
        }

        Initialize(m, n);
    };

    const void CalcAnswer() {
        vector<struct pos>::iterator it = MineMap.begin();
        while (it != MineMap.end()) {
            MarkMinePosition(*it);
            it++;
        }
    };
    const void PrintResult(ostream& out) {
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


int _tmain(int argc, _TCHAR* argv[])
{
    list<class MineSweeper> vms;
    int caseid=1;
    while (true)
    {
        MineSweeper* ms = new MineSweeper(caseid);
        bool ret = ms->ReadInput(cin);
        if (ret == false) break;
        ms->CalcAnswer();
        vms.push_back(*ms);
        caseid++;
    }
    list<class MineSweeper>::iterator it = vms.begin();
    while (!vms.empty())
    {
        vms.front().PrintResult(cout);
        vms.pop_front();
    }
    vms.clear();
    return 0;
}

