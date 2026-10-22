#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Рекурсивне створення та заповнення масиву
void Create(double* a, const int n, const double Low, const double High, int i = 0) {
    if (i >= n) return;
    a[i] = Low + (rand() / (RAND_MAX / (High - Low)));
    Create(a, n, Low, High, i + 1);
}

// Рекурсивне виведення масиву
void Print(const double* a, const int n, int i = 0) {
    if (i >= n) {
        cout << endl;
        return;
    }
    cout << setw(8) << fixed << setprecision(2) << a[i];
    Print(a, n, i + 1);
}

// 1.1. Рекурсивне визначення максимального за модулем елемента
double MaxAbs(const double* a, const int n, int i = 1, double currentMax = -1.0) {
    if (n <= 0) return 0;
    if (currentMax < 0) currentMax = abs(a[0]);

    if (i >= n) return currentMax;

    if (abs(a[i]) > currentMax) {
        currentMax = abs(a[i]);
    }
    return MaxAbs(a, n, i + 1, currentMax);
}

// Допоміжні рекурсивні функції для пошуку індексів першого та другого додатних елементів
int FirstPositiveIndex(const double* a, const int n, int i = 0) {
    if (i >= n) return -1;
    if (a[i] > 0) return i;
    return FirstPositiveIndex(a, n, i + 1);
}

int SecondPositiveIndex(const double* a, const int n, int firstIdx, int i = -1) {
    if (i == -1) i = firstIdx + 1;
    if (i >= n) return -1;
    if (a[i] > 0) return i;
    return SecondPositiveIndex(a, n, firstIdx, i + 1);
}

// Рекурсивне обчислення суми між двома індексами
double SumBetweenIndices(const double* a, const int endIdx, int currentIdx) {
    if (currentIdx >= endIdx) return 0;
    return a[currentIdx] + SumBetweenIndices(a, endIdx, currentIdx + 1);
}

// 1.2. Головна рекурсивна функція для обчислення суми між 1-м та 2-м додатними
double SumBetweenPositives(const double* a, const int n) {
    int firstIdx = FirstPositiveIndex(a, n);
    if (firstIdx == -1) return 0;

    int secondIdx = SecondPositiveIndex(a, n, firstIdx);
    if (secondIdx == -1 || secondIdx - firstIdx <= 1) return 0;

    return SumBetweenIndices(a, secondIdx, firstIdx + 1);
}

// Допоміжна рекурсивна функція копіювання ненульових елементів у тимчасовий масив
void CopyNonZeros(const double* a, double* temp, const int n, int i, int& tempIdx) {
    if (i >= n) return;
    if (a[i] != 0.0) {
        temp[tempIdx++] = a[i];
    }
    CopyNonZeros(a, temp, n, i + 1, tempIdx);
}

// Допоміжна рекурсивна функція дозаповнення нулями
void FillZeros(double* temp, const int n, int tempIdx) {
    if (tempIdx >= n) return;
    temp[tempIdx] = 0.0;
    FillZeros(temp, n, tempIdx + 1);
}

// Допоміжна рекурсивна функція копіювання масиву назад
void CopyArray(double* dest, const double* src, const int n, int i = 0) {
    if (i >= n) return;
    dest[i] = src[i];
    CopyArray(dest, src, n, i + 1);
}

// 2. Рекурсивне перетворення масиву (переміщення нулів у кінець)
void MoveZerosToEnd(double* a, const int n) {
    double* temp = new double[n];
    int tempIdx = 0;

    CopyNonZeros(a, temp, n, 0, tempIdx);
    FillZeros(temp, n, tempIdx);
    CopyArray(a, temp, n, 0);

    delete[] temp;
}

int main() {
    srand((unsigned)time(0));

    int n;
    cout << "Enter size of array n: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid size!" << endl;
        return 1;
    }

    double* a = new double[n];

    const double LOW = -10.0;
    const double HIGH = 10.0;

    Create(a, n, LOW, HIGH);

    cout << "\nInitial array:" << endl;
    Print(a, n);

    cout << "\n1.1. Max abs element (recursive): " << MaxAbs(a, n) << endl;
    cout << "1.2. Sum between 1st and 2nd positive (recursive): " << SumBetweenPositives(a, n) << endl;

    MoveZerosToEnd(a, n);

    cout << "\nModified array (zeros moved to end, recursive):" << endl;
    Print(a, n);

    delete[] a;

    return 0;
}