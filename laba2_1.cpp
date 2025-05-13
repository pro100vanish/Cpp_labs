#include <iostream>
using namespace std;

int maxDigit(int n) {
    if (n < 10)
        return n;
    else
        return max(n % 10, maxDigit(n / 10));
}

int main() {
    int N;
    cout << "Введите число N: ";
    cin >> N;

    cout << "Максимальная цифра: " << maxDigit(N) << endl;
    return 0;
}
