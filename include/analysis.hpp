//Copyright 2019 CrazyOverdose

#ifndef  INCLUDE_ANALYSIS_HPP_
#define  INCLUDE_ANALYSIS_HPP_
#include <boost/filesystem.hpp>
#include <vector>
#include <string>
#include <cstdlib>

struct Date {
    int day;
    int month;
    int year;
};

struct information {
    std::string title; //название файла
    std:: string broker; //папка
    std:: string type;
    int account; //аккаунт
    Date data; // дата
};

std::ostream& operator<< (std::ostream &out, const Date &date)
{
    out << date.day << "." << date.month << "." << date.year;

    return out;
}

bool lastdate(information file1, information file2)
{
    if (file1.data.year < file2.data.year)
        return 1;
    if (file1.data.year > file2.data.year)
        return 0;

    if (file1.data.month < file2.data.month)
        return 1;
    if (file1.data.month > file2.data.month)
        return 0;

    if (file1.data.day < file2.data.day)
        return 1;
    if (file1.data.day > file2.data.day)
        return 0;

    return 0;
}

class analysis
{
protected:
    boost::filesystem :: path path_to_ftp;
    std::vector <information> informations;

    std::unordered_map<int, std::vector<information>> accounts_groups;

public:
    explicit analysis(boost::filesystem :: path path)
    {
        this->path_to_ftp = path;
    }

    void work(boost::filesystem :: path path) {
        for (boost::filesystem::directory_entry dir_iter :
                boost::filesystem::directory_iterator{ path })
        {
            if (boost::filesystem::is_regular_file(dir_iter))
                file(dir_iter);
            if (boost::filesystem::is_directory(dir_iter))
                work(dir_iter); }
    }

    void file(boost::filesystem :: path path)
    {
        try {
            information new_file = parcer(path.filename().string());

            informations.push_back(new_file);
            accounts_groups[new_file.account].push_back(new_file);
        }
        catch (const std::logic_error&){}
    }



    void print_name_files()
    {
        std::cout << "Task one " << std::endl;
        for (size_t i = 0; i < informations.size(); ++i)
        {
            std::cout << informations[i].broker << "  ";
            std::cout << informations[i].title << std::endl;
        }
    }

    void print_information()
    {
        std::cout << "Task two " << std::endl;

        for (const auto& i : accounts_groups )
        {
            std::cout << "broker: " << i.second[0].broker << "| ";

            std::cout << "account: " << i.first << "| ";

            std::cout << "files: " << i.second.size() << "| ";

            std::cout << "lastdate: ";

std::cout << std::max_element(i.second.begin(), i.second.end(), lastdate)->data;

            std::cout << " ";

            std::cout << std::endl;
        }
    }

    information parcer(std::string file)
    {
        information new_file;

        new_file.title = file;

        new_file.type = file.substr(0, file.find('_'));

        file = file.substr(file.find('_') + 1);

new_file.account = std::stoi(file.substr(0, file.find('_')));
        file = file.substr(file.find('_') + 1);

        new_file.data.year = std::stoi(file.substr(0, 4));
        new_file.data.month = std::stoi(file.substr(4, 2));
        new_file.data.day = std::stoi(file.substr(6, 2));
        file = file.substr(8);

        if (file[0] != '.' || file.substr(0, 4) == ".old")
            throw std::logic_error("");

        if (file.substr(1).find('.') != std::string::npos)
            throw std::logic_error("");

        return new_file;
    }
};
#endif // INCLUDE_ANALYSIS_HPP_
