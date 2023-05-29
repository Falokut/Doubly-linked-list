#include "List.h"
#include <ctime>
#include <iostream>

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    int num{};

    std::cout << "¬ведите кол-во узлов списка: " << std::endl;
    std::cin >> num;

    List<int> lst;
    for (int i = 0; i < num; i++)
    {
        lst.Push_Back(rand() % 21 - 10);
    }

    std::cout << std::endl;
    lst.Print_Forward();
	lst.Insert(999, lst.GetSize()-1);
    std::cout << "\n";
    lst.Print_Backward();
    std::cout << "\n";
    system("pause");
    return 0;
}
