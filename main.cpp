#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include <time.h>
int main(void)
{
    // seed random
    srand(time(NULL));

    // read the file for the participants
    std::string line;
    std::ifstream input_file("santas.txt");
    std::vector<std::string> santas;
    if(input_file.is_open()){
        while(getline(input_file, line)){
            santas.push_back(line);
        }
        input_file.close();
    }

    // who can still be draw
    auto possiblities = santas;

    // who drew who
    std::map<std::string, std::string> results;
    for(const auto& santa : santas){
        int draw = -1;
        std::string result;

        // keep drawing until you get someone other than yourself and who didn't get you
        // this way in odd groups you don't run the risk of being stuck with only one left to draw 
        // and they can only draw themselves
        do {
            draw = rand() % possiblities.size();
            result = possiblities[draw];
        } while(santa == result || santa == results[result]);

        // remove the drawn from the posibilites and then record in the map of results
        possiblities.erase(possiblities.begin() + draw);
        results[santa] = result;
    }

    // print out the results so it can be piped into a result file
    for(const auto& x : results)
    {
        std::cout << x.first << " -> " << x.second << std::endl;
    }
    return 0;
}