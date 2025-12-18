//#include <iostream>
//#include <vector>
//#include <cstdio>
//
//class peopleInfo
//{
//public:
//    int nDaoDaTime;
//    int nSpendTime;
//
//    peopleInfo(int nDaoDaTime, int nSpendTime)
//    {
//        this->nDaoDaTime = nDaoDaTime;
//        this->nSpendTime = nSpendTime;
//    }
//};
//
//void MainLogic(std::vector<peopleInfo*> mPeopleList)
//{
//    std::cout << "[";
//    int nLastEndTime = 0;
//    for (int i = 0; i < mPeopleList.size(); i++)
//    {
//        if (nLastEndTime > mPeopleList[i]->nDaoDaTime + 30)
//        {
//            if(i == mPeopleList.size() - 1)
//            {
//                std::cout << "-1";
//            }
//            else
//            {
//                std::cout << "-1,";
//            }
//        }
//        else
//        {
//            int nLastJiuZhenTime = 0;
//            if (nLastEndTime < mPeopleList[i]->nDaoDaTime)
//            {
//                nLastJiuZhenTime = mPeopleList[i]->nDaoDaTime;
//            }
//            else
//            {
//                nLastJiuZhenTime = nLastEndTime;
//            }
//            
//            if (i == mPeopleList.size() - 1)
//            {
//                std::cout << nLastJiuZhenTime;
//            }
//            else
//            {
//                std::cout << nLastJiuZhenTime << ",";
//            }
//
//            nLastEndTime = nLastJiuZhenTime + mPeopleList[i]->nSpendTime;
//        }
//    }
//
//    std::cout << "]\n";
//}
//
//int main() 
//{
//    std::vector<peopleInfo*> mPeopleList = {};
//    int n, a, b;
//    char douhao;
//    std::cin >> n;
//    while (n-- > 0)
//    {
//        std::cin >> a >> douhao >> b;
//        mPeopleList.push_back(new peopleInfo(a, b));
//    }
//
//    MainLogic(mPeopleList);
//}