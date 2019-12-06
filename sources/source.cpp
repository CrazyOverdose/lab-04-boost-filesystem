//Copyright 2019 CrazyOverdose
#include <string>
#include <iostream>
#include "../include/analysis.hpp"

int main(){
    analysis example("misc/ftp");
    example.work("misc/ftp");
    example.print_name_files();
    example.print_information();
}
