#include "task1.h"
#include <iostream>

int main()
{
    Task task;
    int num_task;
    std::cout << "This task is created to perform 3 tasks\n\n";
    std::cout << "Input the task {1, 2 or 3}: ";
    std::cin >> num_task;
    while (num_task > 0 && num_task < 4)
    {
        switch (num_task)
        {
            case 1:
                task.solution_1();
                break;
            case 2:
                task.solution_2();
                break;
            case 3:
                task.solution_3();
                break;
            default:
                std::cout << "This task doesn't exist\n";
                break;
        }
        std::cout << "Do you want to make any task again? {1, 2 or 3}";
        std::cin >> num_task;
    }
    return 0;
}