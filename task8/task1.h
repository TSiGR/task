#ifndef Task1_h
#define Task1_h

#include <vector>
#include <fstream>

class Task
{
    public:
    void solution_1();
    void solution_2();
    void solution_3();
    private:
    void make_converse(std::ifstream&, std::vector<int>&);
    void delete_converse(std::ifstream&, std::ofstream&, std::vector<int>&);
    int get_randomnumber(int, int);
    bool check_fill(std::vector<char>&);
};

#endif