#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <queue>
#include <cstdlib>
#include <algorithm>


using namespace std;
ifstream fin("data_in.txt");
ofstream fout("data_out.txt");


vector <int> arr;


void swap(int &a, int &b)
{
    int aux;
    aux = b;
    b = a;
    a = aux;
}

// maximul din arr
int getMax(vector <int> &arr, int N)
{
    int max = arr[0];
    for(int i = 0; i < arr.size(); i++)
        if( arr[i]  > max)
            max = arr[i];
    
    return max;
}

// Generating random numbers
void generate(vector <int> &arr, int N,int Max)
{
    int x;
    arr.clear();
    for(int i = 0; i < N; ++i)
        {
            x = rand() % (Max ) +1;
            arr.push_back(x);
        }
}

// afisarea unui vector
void afisare(int N, vector <int> arr)
{
    for(int i = 0; i < arr.size(); ++i)
        cout<<arr[i]<<" ";
    
    cout<<endl;
}

// testare sortare corecta
bool Test(vector <int> arr, int N, int Max)
{
    // check is arr is ascending

    for(int i = 0; i < arr.size()-1; ++i)
            if(arr[i] > arr[i+1])
                return 0;
        

    return 1;
}

// alta implementare Count Sort (pentru Radix Sort)
void countSort(vector <int> &arr, int N, int exp)
{
    vector <int> sol(N,0);
    vector <int> count(N,0);

    for(int i = 0; i < N; ++i)
        count[(arr[i] / exp) %10] ++ ;

    for(int i = 1; i < 10; ++i)
        count[i] += count[i-1];

    for(int i = N-1; i >= 0; i--)
    {
        sol[count[(arr[i] / exp) %10] - 1] = arr[i];
        count[ ( arr[i] / exp ) % 10]--;
    }

    for(int i = 0; i < N; ++i)
        arr[i] = sol[i];

}

vector <int> Bubble_sort(vector <int> arr, int N, int Max)
{
    bool ok = 0;
    
    while( ok == 0)
    {
        ok = 1;
        for(int i = 0; i < arr.size()-1; i++)
                if(arr[i] > arr[i+1] )
                {
                    swap(arr[i], arr[i+1]);
                    ok = 0;
                }
    }
    return arr;
}


vector <int> Count_sort(vector <int> arr, int N, int Max)
{
    vector <int> sol;
    vector <int> count(Max+ 1, 0);

    for(int i = 0; i < arr.size(); ++i)
        count[arr[i]]++;

    for(int i = 0 ; i <= Max; ++i)
        while(count[i] --)
            sol.push_back(i);
   
   
    return sol;
    
}

vector <int> Radix_Sort(vector <int> arr, int N, int Max)
{
    int m = getMax(arr, N);

    for( int exp = 1; m/exp > 0; exp *=10)
        countSort(arr, N, exp);
    
    return arr;
}

// Radix Sort baza 16
vector <int> Radix_Sort16(vector <int> arr, int N, int Max)
{
    //lista de cozi
    queue <int> q[16];
    int k;
    
    for( int i = 0; i <= 24; i += 4 )
    {
        for(int j = 0; j < N; ++j) 
            q[( arr[j] >> i)& 15].push(arr[j]);

        k = 0; 

        for(int j = 0; j <= 15 && k <  N; ++j)
            while(!q[j].empty())
            {
                arr[k++] = q[j].front();
                q[j].pop();
            }
    }
    return arr;
}

void radix_sort256(vector <int> &arr, int N)
{
    queue<int> q[256];
    int k;

    for(int i = 0; i <= 24; i += 8)
    {
        for(int j = 0; j < N; ++j)
            q[(arr[j] >> i) & 255].push(arr[j]);

        k = 0;

        for(int j = 0; j <= 255 && k < N; ++j)
            while(!q[j].empty())
            {
                arr[k++] = q[j].front();
                q[j].pop();
            }
    }
}

void Interclasare(vector <int> &arr, int st, int mij, int dr)
{
    int i = st;
    int j = mij+1;
    int k = 1;

    vector <int> aux;

    while( i <= mij && j <= dr)
        if(arr[i] < arr[j])
            aux.push_back(arr[i++]);
        else
            aux.push_back(arr[j++]);
    
    while(i <= mij)
        aux.push_back(arr[i++]);
    while(j <= dr)
        aux.push_back(arr[j++]);

    for( i = st; i <= dr; ++i)
        arr[i] = aux[i-st];
}

void Merge_Sort(vector <int> &arr, int st, int dr)
{
    if(dr > st)
    {
        int mij = (st + dr)/2;
        Merge_Sort(arr,st, mij);
        Merge_Sort(arr, mij+1, dr);

        Interclasare(arr,st, mij, dr);
    }
}

// Quick Sort pivot - random
void Quick_Sort_Rand(vector <int> &arr, int st, int dr)
{
    int i = st;
    int j = dr;

    int x = arr[rand() % (dr - st +1) + st];

    while( i < j)
    {
        while(arr[i] < x) i++;
        while(arr[j] > x) j--;

        if( i <= j)
            swap(arr[i++],arr[j--]);
    }

    if(j > st)
        Quick_Sort_Rand(arr, st, j);
    if( i < dr)
        Quick_Sort_Rand(arr, i, dr);
}

// Partitionarea vectorului dupa pivot
int Partition( vector <int> &arr, int st, int dr, int p)
{
    while(st <= dr)
    {
        while(arr[st] < p) st++;
        while(arr[dr] > p) dr--;
        
        if(st <= dr)
        {
            swap(arr[st], arr[dr]);
            st++;
            dr--;
        }
    }
    return st;
}


// Quick sort with pivot as median of 3
void Quick_Sort_Med(vector <int> &arr, int st, int dr)
{
    if( st < dr)
    {
        int mij = (st + dr) / 2;
        int p; //pivot
        // arr[st] , arr[dr] , arr[mij] 
        if(arr[st] > arr[dr])
            swap(arr[st], arr[dr]);
        if(arr[st] > arr[mij])
            swap(arr[st], arr[mij]);
        if(arr[mij] > arr[dr])
            swap(arr[mij], arr[dr]);

        p = arr[mij];
        int index = Partition(arr, st, dr, p);

        Quick_Sort_Med(arr, st, index-1);
        Quick_Sort_Med(arr, index, dr);

    }
}

void Sortari(vector <int> arr, int N, int Max)
{
    clock_t start;
    clock_t end;
    vector <int> copy;

    double elapsed;
    
    
    // Bubble sort - n <= 10^6
    if(N < 100000)
    {
        start = clock();
        
        copy = Bubble_sort(arr, N, Max);
        
        end = clock();
        elapsed = double(end - start)/CLOCKS_PER_SEC;
        if(Test(copy, N, Max) == 1)
                cout<<"SUCCESS   "<<"Timpul de executare Bubble Sort este "<<elapsed<<" secunde"<<endl;
        else
            cout<<"Bubble Sort FAILED"<<endl;
    }
    else
        cout<<"Datele de intrare sunt prea mari pentru Bubble Sort"<< endl;
    

    if(Max < 1000000 && N < 100000000)
    {
        start = clock();
        copy.clear();
        copy = Count_sort(arr, N, Max);
        
        
        end = clock();
        elapsed = double(end - start)/CLOCKS_PER_SEC;
        
        if(Test(copy, N, Max) == 1) 
                cout<<"SUCCESS   "<<"Timpul de executare Count Sort este "<<elapsed<<" secunde"<<endl;
        else
            cout<<"Count Sort FAILED"<<endl;
    }
    else
        cout<<"Datele de intrare sunt prea mari pentru Count Sort"<< endl;
    
    if(N < 100000000)
    {
        start = clock();
        copy.clear();
        copy = Radix_Sort(arr, N, Max);
        end = clock();

        elapsed = double(end - start)/CLOCKS_PER_SEC;

        if(Test(copy, N, Max))
            cout<<"SUCCESS   "<<"Timpul de executare Radix Sort este "<<elapsed<<" secunde"<<endl;
        else
            cout<<"Radix sort FAILED"<<endl;
        
        start = clock();
        copy.clear();
        copy = Radix_Sort16(arr, N, Max);
        end = clock();

        elapsed = double(end - start)/CLOCKS_PER_SEC;

        if(Test(copy, N, Max))
            cout<<"SUCCESS   "<<"Timpul de executare Radix Sort in baza 16 este "<<elapsed<<" secunde"<<endl;
        else
            cout<<"Radix Sort 16 FAILED"<<endl;
    }
    else
        cout<<"Datele de intrare sunt prea mari pentru Radix Sort"<<endl;
    

    if(N < 10000000)
    {
        copy = arr;

        start = clock();
        Merge_Sort(copy, 0, N-1);
        end = clock();

        elapsed = double(end - start)/CLOCKS_PER_SEC;
         if(Test(copy, N, Max))
            cout<<"SUCCESS   "<<"Timpul de executare Merge Sort este "<<elapsed<<" secunde"<<endl;
        else
            cout<<"Merge sort FAILED"<<endl;
    }
    else
        cout<<"Datele de intrare sunt prea mari pentru Merge Sort"<<endl;
    
    if(N < 100000000)
    {
        copy = arr;

        start = clock();
        Quick_Sort_Rand(copy, 0, N-1);
        end = clock();

        elapsed = double(end - start)/CLOCKS_PER_SEC;
         if(Test(copy, N, Max))
            cout<<"SUCCESS   "<<"Timpul de executare Quick Sort Rand este "<<elapsed<<" secunde"<<endl;
        
        else
            cout<<"Quick Sort Rand FAILED"<<endl;
    }
    else
        cout<<"Datele de intrare sunt prea mari pentru Quick Sort Rand"<<endl;
    

    if(N < 100000000)
    {
        copy = arr;

        start = clock();
        Quick_Sort_Med(copy, 0, N-1);
        end = clock();

        elapsed = double(end - start)/CLOCKS_PER_SEC;
         if(Test(copy, N, Max))
            cout<<"SUCCESS   "<<"Timpul de executare Quick Sort Med este "<<elapsed<<" secunde"<<endl;
        
        else
            cout<<"Quick Sort Med FAILED"<<endl;
    }
    else
        cout<<"Datele de intrare sunt prea mari pentru Quick Sort Med"<<endl;

    if( N < 100000000)   
    {
        copy = arr;
        
        start = clock();
        sort(copy.begin(), copy.end());
        end = clock();

        elapsed = double(end - start)/CLOCKS_PER_SEC;
        
        cout<<"SUCCESS   "<<"Timpul de executare Stl Native Sort este "<<elapsed<<" secunde"<<endl;
    }
    else
        cout<<"Datele de intrare sunt prea mari pentru Stl Native Sort"<<endl;

   cout<<endl;
}

int main()
{
    int Num_tests;
    int N,Max;
    
    fin>>Num_tests;
    cout<<"Numarul de teste: "<<Num_tests<<endl;
    

    for( int i = 1; i <= Num_tests; i++)
        {
            cout<<"Testul "<<i<<endl;
            fin>>N>>Max;
            generate(arr, N, Max);
            cout<<"N = "<<N<<" "<<"Max = "<<Max<<endl;
            
            // all sorts
            Sortari(arr, N, Max);            
        }
    fin.close();
    fout.close();
    return 0;

}
