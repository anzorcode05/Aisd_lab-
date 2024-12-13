#include <iostream> 
#include <vector> 
#include <cmath>
#include "DoubleList.h"

void FindPrimesInRange(const MyList<int>& my_list, int N) {
    std::vector<bool> sieve(N + 1, true);
    sieve[0] = sieve[1] = false; // 0 и 1 не являются простыми числами 

    // Реализация решета Эратосфена 
    for (int i = 2; i * i <= N; ++i) {
        if (sieve[i]) {
            for (int j = i * 2; j <= N; j += i) {
                sieve[j] = false;
            }
        }
    }

    for (int i = 0; i < my_list.size(); ++i) {
        if (my_list[i] <= N && sieve[my_list[i]] == true) {
            std::cout << my_list[i] << ' ';
        }
    }
    std::cout << std::endl;
}

int main() {
    // Пример использования 
    MyList<int> list;
    int N;
    std::cout << "Enter the number N\n";
    std::cin >> N;

    // Добавляем числа от 1 до N 
    for (int i = 1; i <= N; ++i) {
        list.push_tail(i);
    }

    std::cout << "Prime numbers in the list (up to N): ";
    FindPrimesInRange(list, N);

    return 0;
}