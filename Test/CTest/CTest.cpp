// CTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <vector>
#include <format>

void assert(bool bTrue);
std::string strformat(const char* fmt, ...);
void QuickSort(std::vector<int>& mArray);
void QuickSort(std::vector<int>& mArray, int nBegin, int nEnd);

int main()
{
    std::cout << "Hello World!\n";

    std::vector<int> mArray = {0, 1, 2, 3, 4, 5};
    QuickSort(mArray);
    for (int i = 0; i < mArray.size(); i++)
    {
        std::cout << strformat("%d ", mArray[i]);
    }
    std::cout << "\n";

    mArray = { 5, 4, 3, 2, 1, 0 };
    QuickSort(mArray);
    for (int i = 0; i < mArray.size(); i++)
    {
        std::cout << strformat("%d ", mArray[i]);
    }
    std::cout << "\n";

    mArray = { 1, 5, 2, 4, 3, 0 };
    QuickSort(mArray);
    for (int i = 0; i < mArray.size(); i++)
    {
        std::cout << strformat("%d ", mArray[i]);
    }
    std::cout << "\n";
}



void QuickSort(std::vector<int>& mArray)
{
    QuickSort(mArray, 0, mArray.size() - 1);
}

void QuickSort(std::vector<int>& mArray, int nBegin, int nEnd)
{
    if (nBegin >= nEnd)
    {
        return;
    }

    int Key = mArray[nBegin];
    int nBeginIndex = nBegin;
    int nEndIndex = nEnd;
    while (nBeginIndex < nEndIndex)
    {
        while (nBeginIndex < nEndIndex && mArray[nEndIndex] >= Key)
        {
            nEndIndex--;
        }

        if (nBeginIndex < nEndIndex)
        {
            mArray[nBeginIndex] = mArray[nEndIndex];
        }

        while (nBeginIndex < nEndIndex && mArray[nBeginIndex] <= Key)
        {
            nBeginIndex++;
        }

        if (nBeginIndex < nEndIndex)
        {
            mArray[nEndIndex] = mArray[nBeginIndex];
        }
    }
    
    mArray[nBeginIndex] = Key;
    assert(nBeginIndex == nEndIndex);
    if (nBegin < nEnd)
    {
        QuickSort(mArray, nBegin, nBeginIndex - 1);
        QuickSort(mArray, nBeginIndex + 1, nEnd);
    }

}

void assert(bool bTrue)
{
    if (!bTrue)
    {
        std::cerr << "assert failed" << std::endl;
    }
}

std::string strformat(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int len = std::snprintf(nullptr, 0, fmt, args);
    char* buffer = new char[len];
    std::vsnprintf(buffer, len, fmt, args);
    va_end(args);

    return std::string(buffer);
}
