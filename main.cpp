#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
ofstream out("rezultate.txt");
void swap(long *a, long *b)
{
    long temp = *a;
    *a = *b;
    *b = temp;
}
void bubbleSort(long* v, long n)
{
    long i, j;
    for (i = 0; i < n-1; i++)
    for (j = 0; j < n-i-1; j++){
        if (v[j] > v[j+1])
            swap(&v[j], &v[j+1]);
            }
}
void countSort(long* v, long n,long m)
{
    vector<long> frecv(m+1);
    vector<long> output(n+1);
    for(int i=0;i<n;i++){
        output[i]=0;
    }
    for(int i=0;i<m;i++){
        frecv[i]=0;
    }
    for (long i = 0; i<n; i++)
        frecv[v[i]]++;
    for (long i = 1; i <= m; i++){
        frecv[i] += frecv[i - 1];
    }
    for (long i = 0; i<n; i++) {
        output[frecv[v[i]]-1] = v[i];
        frecv[v[i]]--;
    }

    for (long i = 0; i<n; i++)
        v[i] = output[i];
}
void merge(long* v, long l, long m, long r)
{
    long n1 = m - l + 1;
    long n2 = r - m;
    vector<long>L(n1);
    vector<long>R(n2);
    for (long i = 0; i < n1; i++)
        L[i] = v[l + i];
    for (long j = 0; j < n2; j++)
        R[j] = v[m + 1 + j];
    long i = 0;
    long j = 0;
    long k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            v[k] = L[i];
            i++;
        }
        else {
            v[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        v[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(long* v,long l,long r){
    if(l>=r){
        return;
    }
    long m = l + (r-l)/2;
    mergeSort(v,l,m);
    mergeSort(v,m+1,r);
    merge(v,l,m,r);
}
long part(long* v, long l, long r)
{
    long pivot = v[r];
    long i = (l - 1);

    for (long j = l; j <= r - 1; j++)
    {
        if (v[j] < pivot)
        {
            i++;
            swap(&v[i], &v[j]);
        }
    }
    swap(&v[i+1], &v[r]);
    return (i + 1);
}
int mediana3(long* v, long l, long r)
{
    long m = (l + r + 1)/2;
    if (v[l] < v[m]) swap(&v[l], &v[m]);
    if (v[r] < v[m]) swap(&v[r], &v[m]);
    if (v[l] < v[r]) swap(&v[r], &v[l]);
    return part(v, l, r);
}
void quickSort(long* v, long l, long r)
{
    if (l < r)
    {
        long pi = mediana3(v, l, r);
        quickSort(v, l, pi - 1);
        quickSort(v, pi + 1, r);
    }
}
void countSortRadix(long* v, const long n, long cif)
{
    int frecv[10] = { 0 };
    long* output = new long[n+1];
    int i;

    for (i = 0; i < n; i++)
        frecv[(v[i] / cif) % 10]++;
    for (i = 1; i <= 9; i++)
        frecv[i] += frecv[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[frecv[(v[i] / cif) % 10] - 1] = v[i];
        frecv[(v[i] / cif) % 10]--;
    }
    for (i = 0; i < n; i++)
        v[i] = output[i];

    delete[] output;
}

void radixSort(long* v, long n)
{
    long m{ 0 };
    for (long i = 0; i < n; i++)
        if (v[i] > m)
            m = v[i];
    for (long cif = 1; cif <= m; cif *= 10) {
        countSortRadix(v, n, cif);
    }
}
bool verify(long* v, long n){
    for(long i=0;i<n-1;i++){
        if(v[i]>v[i+1]){return 0;}
    }
    return 1;
}
void generator(long* v,long n,long m){
    for(int i=0;i<n;i++){
        v[i]= rand()%m;
    }
}
void copyV(long* a,long* b,long n){
    for(int i=0;i<n;i++){
        a[i]=b[i];
    }
}
void driver(long n,long m){
    long* v = new long[n];
    long* c = new long[n];

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    cout << "N=" << n <<"   M=" <<m<<  "\n\n";
    out << "N=" << n <<"   M=" <<m<<  "\n\n";
    generator(v,n,m);
    copyV(c,v,n);

    auto t1 = high_resolution_clock::now();
    auto t2 = high_resolution_clock::now();
    duration<double> ms_double = t2 - t1;
    cout << "Array sorted: " << (verify(v,n)?"Yes":"No")<<"\n";
    cout << "Sorting with BUBBLE SORT\n";
    if(n < 10001){
        bubbleSort(v,n);
        t2 = high_resolution_clock::now();
        ms_double = t2 - t1;
        out  << ms_double.count() << "\n";
        cout << "Sort duration: " << ms_double.count()<< "s"<<  "\n";
        cout << "Array sorted: " << (verify(v,n)?"Yes":"No")<<"\n" <<  "\n";
    }else{
        out << "Bubble " << 9999 << "\n";
        cout << "Number too large for bubble sort.\n";
    }


    copyV(v,c,n);
    t1 = high_resolution_clock::now();
    cout << "Array sorted: " << (verify(v,n)?"Yes":"No")<<"\n";
    cout << "Sorting with COUNT SORT\n";
    countSort(v, n, m);
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    out << ms_double.count() << "\n";
    cout << "Sort duration: " << ms_double.count()<< "s"<<  "\n";
    cout << "Array sorted: " << (verify(v,n)?"Yes":"No")<< "\n" << "\n";

    copyV(v,c,n);
    t1 = high_resolution_clock::now();
    cout << "Array sorted: " << (verify(v,n)?"Yes":"No")<<"\n";
    cout << "Sorting with RADIX SORT\n";
    radixSort(v, n);
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    out <<  ms_double.count() << "\n";
    cout << "Sort duration: " << ms_double.count()<< "s"<<  "\n";
    cout << "Array sorted: " << (verify(v,n)?"Yes":"No")<< "\n" << "\n";

    copyV(v,c,n);
    t1 = high_resolution_clock::now();
    cout << "Array sorted: " << (verify(v,n)?"Yes":"No")<<"\n";
    cout << "Sorting with MERGE SORT\n";
    mergeSort(v,0,n-1);
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    out <<ms_double.count() << "\n";
    cout << "Sort duration: " << ms_double.count()<< "s"<<  "\n";
    cout << "Array sorted: " << (verify(v,n)?"Yes":"No")<< "\n" << "\n";

    copyV(v,c,n);
    t1 = high_resolution_clock::now();
    cout << "Array sorted: " << (verify(v,n)?"Yes":"No")<<"\n";
    cout << "Sorting with QUICK SORT\n";
    quickSort(v,0, n-1);
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    out <<  ms_double.count() << "\n";
    cout << "Sort duration: " << ms_double.count()<< "s"<<  "\n";
    cout << "Array sorted: " << (verify(v,n)?"Yes":"No")<< "\n" << "\n";

    copyV(v,c,n);
    t1 = high_resolution_clock::now();
    cout << "Array sorted: " << (verify(v,n)?"Yes":"No")<<"\n";
    cout << "Sorting with C++ STL SORT\n";
    sort(v,v+n);
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    out << ms_double.count() << "\n\n\n";
    cout << "Sort duration: " << ms_double.count()<< "s"<<  "\n";
    cout << "Array sorted: " << (verify(v,n)?"Yes":"No")<< "\n" << "\n";

}
int main() {
    ifstream in("teste.in");
    string word;
    vector<long> numbers;
    srand((unsigned) time(0));
    size_t pos = 0;

     while (in >> word) {
        try {
            long f = std::stof(word, &pos);
             if (pos == word.size()) {
                numbers.push_back(f);
            }
        }
        catch (std::invalid_argument const& ) {
            continue;
        }
    }
    for(int i=1;i<=numbers[0]*2;i+=2){
        cout << "Test nr: " << (i+1)/2 << "\n\n";
        driver(numbers[i],numbers[i+1]);
    }


    return 0;
}
