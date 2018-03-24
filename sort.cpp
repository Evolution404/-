#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

//排序类
class Sort
{
  public:
    void insertSort(int *num, int n)
    {
        int i = 0;
        int j = 0;
        int tmp = 0;
        for (i = 1; i < n; i++)
        {
            tmp = num[i];                  //从待插入组取出第一个元素。
            j = i - 1;                     //i-1即为有序组最后一个元素（与待插入元素相邻）的下标
            while (j >= 0 && tmp < num[j]) //注意判断条件为两个，j>=0对其进行边界限制。第二个为插入判断条件
            {
                num[j + 1] = num[j]; //若不是合适位置，有序组元素向后移动
                j--;
            }
            num[j + 1] = tmp; //找到合适位置，将元素插入。
        }
    }

    void bubbleSort(int *array, int n)
    {
        int i = 0;
        int j = 0;
        int temp = 0;

        for (i = 0; i < n; ++i)
        {
            for (j = 1; j < n - i; ++j)
            {
                if (array[j - 1] > array[j])
                {
                    temp = array[j - 1];
                    array[j - 1] = array[j];
                    array[j] = temp;
                }
            }
        }
    }

    void selectSort(int *array, int n)
    {
        int i = 0;
        int j = 0;
        int min = 0;
        int temp = 0;

        for (int i = 0; i < n; i++)
        {
            min = i;
            for (j = i + 1; j < n; j++)
            {
                if (array[min] > array[j])
                    min = j;
            }
            temp = array[min];
            array[min] = array[i];
            array[i] = temp;
        }
    }

    void quickSort(int *array, int l, int r)
    {
        int i = 0;
        int j = 0;
        int x = 0;

        if (l < r)
        {
            i = l;
            j = r;
            x = array[l];
            while (i < j)
            {
                while (i < j && array[j] >= x)
                {
                    j--;
                }
                if (i < j)
                {
                    array[i++] = array[j];
                }
                while (i < j && array[i] <= x)
                {
                    i++;
                }
                if (i < j)
                {
                    array[j--] = array[i];
                }
            }
            array[i] = x;
            quickSort(array, l, i - 1);
            quickSort(array, i + 1, r);
        }
    }
};

//文件操作类
class File
{
  public:
    void writeRs(int *num, int n, string funName)
    {
        ofstream f(funName + ".txt");
        if (f.is_open())
        {
            for (int i = 0; i < 30000; i++)
            {
                f << num[i] << endl;
            }
        }
    }

    void writeRand(int num)
    {
        srand((unsigned)time(NULL));
        ofstream random("random.txt");
        if (random.is_open())
        {
            for (int i = 0; i < num; i++)
            {
                random << rand() % 100000 << endl;
            }
        }
    }

    int *readRand(int n)
    {
        char line[20];
        ifstream random_out("random.txt");
        int *num = new int[n];
        int i = 0;
        while (!random_out.eof())
        {
            random_out.getline(line, 20);
            stringstream ss;
            ss << line;
            ss >> num[i];
            i++;
        }
        return num;
    }
};

int main()
{
    File f;
    Sort s;

    time_t start, end;
    double sp; //算法执行消耗的时间
    int randNums = 30000;
    f.writeRand(randNums);
    int *base = f.readRand(randNums);
    cout << "读取完成\n";
    int num[randNums];

    memcpy(num, base, randNums * sizeof(int));
    start = clock();
    s.insertSort(num, randNums);
    end = clock();
    cout << "插入排序完成\n";
    sp = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    cout << "插入排序耗时:" << sp << "ms" << endl;
    f.writeRs(num, randNums, "InsertSort");
    cout << "写入插入排序结果完成\n";

    memcpy(num, base, randNums * sizeof(int));
    start = clock();
    s.bubbleSort(num, randNums);
    end = clock();
    cout << "冒泡排序完成\n";
    sp = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    cout << "冒泡排序耗时:" << sp << "ms" << endl;
    f.writeRs(num, randNums, "BubbleSort");
    cout << "写入冒泡排序结果完成\n";

    memcpy(num, base, randNums * sizeof(int));
    start = clock();
    s.selectSort(num, randNums);
    end = clock();
    cout << "选择排序完成\n";
    sp = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    cout << "选择排序耗时:" << sp << "ms" << endl;
    f.writeRs(num, randNums, "SelectSort");
    cout << "写入选择排序结果完成\n";

    memcpy(num, base, randNums * sizeof(int));
    start = clock();
    s.quickSort(num, 0, randNums - 1);
    end = clock();
    cout << "快速排序完成\n";
    sp = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    cout << "快速排序耗时:" << sp << "ms" << endl;
    f.writeRs(num, randNums, "QuickSort");
    cout << "写入快速排序结果完成\n";

    delete base;
}
