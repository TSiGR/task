#include "task1.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

void Task::solution_1()
{
    int b_size = 0;
    int a[10] = {1, 6, 9, 18, 27, 36, 51, 68, 82, 101};
    int b[1];
    for (int i = 0; i < 10; ++i)
    {
        if (a[i] % 2 == 0)
        {
            b[b_size] = a[i];
            b_size++;
        }
    }
    for (int i = 0; i < b_size; ++i)
        std::cout << b[i] << " ";
    std::cout << '\n';
}

void Task::solution_2()
{
    std::vector<int> looks;
    std::vector<int> checks;
    std::vector<int> res;
    std::ifstream look("simple.txt");
    std::ifstream check("happy.txt");
    if (!look.is_open() || !check.is_open())
    {
        std::cerr << "Can't open files for reading\n";
        exit(1);
    }
    make_converse(look, looks);
    make_converse(check, checks);
    
    for (auto& item : looks)
    {
        if (std::binary_search(checks.begin(), checks.end(), item))
        {
            res.push_back(item);
        }
    }

    std::ofstream look_new("simple_modified.txt");
    std::ofstream check_new("happy_modified.txt");


    delete_converse(look, look_new, res);
    delete_converse(check, check_new, res);

    look.close();
    look_new.close();
    check.close();
    check_new.close();
}

void Task::solution_3()
{
    std::vector<std::string> words = {"favourite", "interesting", "disarmement", "implementaion", "recognize", "substitute",
                                      "production", "neighbourhood", "wonderful", "generation", "trustment", "stronghold",
                                      "creature", "investment", "cucumber", "mushroom", "revolution", "workstation", 
                                      "elevator", "refridgerator", "forgiveness", "encouragement", "translation", "exhibition",
                                      "language", "reconstruction", "calculation", "development", "environment", "destination",
                                      "corporation", "significant", "considerable", "comfortable", "invisible", "unchecked",
                                      "emplacement", "government", "telephone", "container", "distribution"};
    srand(static_cast<unsigned int>(time(0)));
    int chos_number = rand();
    chos_number = get_randomnumber(0, words.size() - 1);
    std::cout << "Let's play the Gallows game. The word has been chosen\n";
    std::vector<char> chos_word(words[chos_number].size());
    std::cout << "The word: ";
    for (int i = 0; i < chos_word.size(); ++i)
        chos_word[i] = '_';
    for (auto& item : chos_word)
        std::cout << item << " ";
    std::cout << '\n';
    std::cout << "Guess the letter: ";
    int attempts = 6;
    while (true)
    {
        char chos_letter;
        bool count_right = 0;
        bool count_miss = 0;
        while ((std::cin >> chos_letter && (static_cast<int>(chos_letter) > 122 || 
                static_cast<int>(chos_letter) < 97)) || std::cin.peek() != '\n')
        {
            std::cout << "Input a letter in low case: ";
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
            }
            std::cin.ignore(32767, '\n');
        }
        auto iter = chos_word.begin();
        for (auto& item : words[chos_number])
        { 
            if (chos_letter == item && *iter == '_')
            {
                *iter = chos_letter;
                count_right = true;
                break;
            }
            else if (chos_letter == *iter && 
                    words[chos_number].find(chos_letter, std::distance(chos_word.begin(), iter) + 1) == std::string::npos)
            {
                std::cout << "You have fill in all the gaps with this letter\n";
                count_miss = true;
                break;
            }
            else
            {
                iter++;
            }
        }
        if (count_right)
        {
            if (check_fill(chos_word))
            {
                std::cout << "Congratulations. You win.\n";
                std::cout << "The guessed word: ";
                for (auto& item : chos_word)
                    std::cout << item << " ";
                std::cout << '\n';
                break;
            }
            else
            {
                std::cout << "That's right: ";
                for (auto& item : chos_word)
                    std::cout << item << " ";
                std::cout << '\n';
            }
        }
        else if (!count_right && !count_miss)
        {
            --attempts;
            std::cout << "Incorrectly! Such a letter is absent in the word. " <<
                      "You have left " << attempts << " attempts to point out the wrong letter.\n";
        }
        if (attempts != 0)
        {
            std::cout << "Guess the next letter: ";
        }
        else
        {
            std::cout << "You have lost. Try again. The right word was " << words[chos_number] << ".\n";
            break;
        }
    }
}

void Task::make_converse(std::ifstream& content, std::vector<int>& number)
{
    std::string conv;
    while (content >> conv)
    {
        int item;
        std::istringstream(conv) >> item;
        number.push_back(item);
    }
    content.clear();
    content.seekg(0, std::ios::beg);
}

void Task::delete_converse(std::ifstream& content, std::ofstream& content_new, std::vector<int>& number)
{
    std::string conv;
    auto iter = number.begin();
    while (content >> conv)
    {
        int item;
        std::istringstream(conv) >> item;
        if (item != *iter)
        {
            content_new << item;
            content_new << '\n';
        }
        else
        {
            iter++;
        }
    }
}

int Task::get_randomnumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

bool Task::check_fill(std::vector<char>& fill_word)
{
    for (auto& item : fill_word)
    {
        if (item == '_')
            return false;
    }
    return true;
}