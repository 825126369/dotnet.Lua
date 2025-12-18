#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <cctype>
#include <stdexcept>

class resOpInfo {
public:
    int nOpState;
    int nOpValue;
    int nSheBeiID = -1;

    resOpInfo(int nOpState, int nOpValue) {
        this->nOpState = nOpState;
        this->nOpValue = nOpValue;
    }
};

void MainLogic(std::vector<resOpInfo*>& mOpList, std::vector<int>& mSheBeiResList) 
{
    for (int i = 0; i < mOpList.size(); i++) {
        if (mOpList[i]->nOpState == 1) {
            int nMinRemainSpace = 9999999;
            int nTargetIndex = -1;
            for (int j = 0; j < mSheBeiResList.size(); j++) {
                if (mSheBeiResList[j] > mOpList[i]->nOpValue) {
                    if (mSheBeiResList[j] - mOpList[i]->nOpValue < nMinRemainSpace) {
                        nMinRemainSpace = mSheBeiResList[j] - mOpList[i]->nOpValue;
                        nTargetIndex = j;
                    }
                }
            }

            if (nTargetIndex >= 0) {
                mOpList[i]->nSheBeiID = nTargetIndex;
                mSheBeiResList[nTargetIndex] -= mOpList[i]->nOpValue;
                std::cout << nTargetIndex + 1 << " ";
            }
            else {
                std::cout << 0 << " ";
            }
        }
        else if (mOpList[i]->nOpState == 2) {
            resOpInfo* nUseOpInfo = mOpList[i - 1];

            int nTargetIndex = nUseOpInfo->nSheBeiID;
            if (nTargetIndex >= 0) {
                mSheBeiResList[nTargetIndex] += mOpList[i]->nOpValue;
                mOpList[i]->nSheBeiID = -1;
            }
        }
    }
}

std::vector<std::string> split_ws(const std::string& s) {
    std::vector<std::string> v;
    auto p = s.begin(), end = s.end();
    while (p != end) {
        while (p != end && std::isspace(static_cast<unsigned char>(*p))) ++p;
        if (p == end) break;
        auto q = p;
        while (q != end && !std::isspace(static_cast<unsigned char>(*q))) ++q;
        v.emplace_back(p, q);
        p = q;
    }
    return v;
}

int main() {
    std::vector<int> mSheBeiResList = {};
    std::vector<resOpInfo*> mOpList = {};
    int nSheBeiCount, nOpCount;
    int nOpState, nOpValue;


    std::string resList;
    int n, a, b;
    char douhao;
    std::cin >> nSheBeiCount >> nOpCount;
    std::getline(std::cin, resList);
    std::getline(std::cin, resList);

    auto mStrList = split_ws(resList);
    for (int i = 0; i < std::min((int)mStrList.size(), nSheBeiCount); i++) {
        mSheBeiResList.push_back(std::stoi(mStrList[i]));
    }

    while (nOpCount-- > 0) {
        std::cin >> nOpState >> nOpValue;
        mOpList.push_back(new resOpInfo(nOpState, nOpValue));
        nOpState = 0;
        nOpValue = 0;
    }

    std::cout << std::endl;
    for (int i = 0; i < mSheBeiResList.size(); i++) {
        std::cout << mSheBeiResList[i] << " ";
    }

    MainLogic(mOpList, mSheBeiResList);

}