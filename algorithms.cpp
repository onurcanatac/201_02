#include <iostream>
#include <chrono>
#include <cstdlib>
#include <random>

int algorithm1(int *arr1, int *arr2, int n, int m)
{
	int i = 0;
	int j = 0;
	
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (arr2[i] == arr1[j])
                break;
        }

        if (j == n)
            return 0;
    }

    return 1;
}

int binarySearch(int *arr, int low,
    int high, int x)
{
    if (high >= low)
    {
        int mid = (low + high) / 2;

        if ((mid == 0 || x > arr[mid - 1]) && (arr[mid] == x))
            return mid;
        else if (x > arr[mid])
            return binarySearch(arr, (mid + 1), high, x);
        else
            return binarySearch(arr, low, (mid - 1), x);
    }
    return -1;
}

int algorithm2(int *arr1, int *arr2, int n, int m)
{
    int i;
    for (i = 0; i < m; i++)
    {
        if (binarySearch(arr1, 0, n - 1, arr2[i]) == -1)
            return 0;
    }
    return 1;
}

int algorithm3(int *arr1, int *arr2, int n, int m)
{
    int max = arr1[1];
    for (int i = 0; i < n; i++)
    {
        if (arr1[i] > max)
        {
            max = arr1[i];
        }
    }
    
    //int freqArr[max];
    int* freqArray = new int[max];//dynamic array declaration

    for (int i = 0; i < max; i++)
    {
        freqArray[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int value = arr1[i];
        freqArray[value - 1]++;
    }

    for (int i = 0; i < m; i++)
    {
        if (freqArray[arr2[i] - 1] == 0)
        {
            return 0;
        }
        else if (arr2[i] > max)
        {
            return 0;
        }
        else
        {
            freqArray[arr2[i] - 1]--;
        }
    }
    delete[] freqArray;
    return 1;
}

int randomMake(int range_to) 
{
    const int range_from = 0;
    range_to--;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to);

    return distr(generator);

}


int main()
{
    int n = 1*1000000;
    int m = 10000;

    int* arr1 = new int[n];
    int* arr2 = new int[m];

    for (int i = 0; i < n; i++)
    {
        arr1[i] = i + 1;
    }

    for (int i = 0; i < m; i++)
    {
        arr2[i] = randomMake(n);
    }

    //algo1

    int average1 = 0;
    int count1 = 0;
    for (int i = 0; i < 10; i++)
    {
        std::chrono::time_point< std::chrono::system_clock > startTime;
        std::chrono::duration< double, std::milli > elapsedTime;
        //Store the starting time
        startTime = std::chrono::system_clock::now();
        //Code block

        //std::cout << algorithm1(arr1, arr2, n, m);
        algorithm1(arr1, arr2, n, m);

        //Compute the number of seconds that passed since the starting time
        elapsedTime = std::chrono::system_clock::now() - startTime;
        std::cout << "Execution took " << elapsedTime.count() << " milliseconds." << std::endl;

        average1 += (double) elapsedTime.count();
        count1++;
    }
    
    std::cout << (double) average1 / (double) count1 << std::endl;
    
    //algo2

    int average2 = 0;
    int count2 = 0;

    std::chrono::time_point< std::chrono::system_clock > startTime;
    std::chrono::duration< double, std::milli > elapsedTime;
    //Store the starting time
    startTime = std::chrono::system_clock::now();

    for (int i = 0; i < 10000; i++)
    {

        //Code block

        //std::cout << algorithm1(arr1, arr2, n, m);
        algorithm2(arr1, arr2, n, m);

        count2++;
    }

    //Compute the number of seconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    std::cout << "Execution took " << elapsedTime.count() << " milliseconds." << std::endl;

    average2 += (double)elapsedTime.count();

    std::cout << (double) average2 / (double) count2 << std::endl;//change
    
    //algo3

    int average3 = 0;
    int count3 = 0;
    {
        std::chrono::time_point< std::chrono::system_clock > startTime;
        std::chrono::duration< double, std::milli > elapsedTime;
        //Store the starting time
        startTime = std::chrono::system_clock::now();

        for (int i = 0; i < 1000; i++)
        {

            //Code block

            //std::cout << algorithm1(arr1, arr2, n, m);
            algorithm3(arr1, arr2, n, m);

            count3++;

        }

        //Compute the number of seconds that passed since the starting time
        elapsedTime = std::chrono::system_clock::now() - startTime;
        std::cout << "Execution took " << elapsedTime.count() << " milliseconds." << std::endl;

        average3 += (double)elapsedTime.count();
    }
    std::cout << (double)average3 / (double)count3 << std::endl;

    delete[] arr1;
    delete[] arr2;
}