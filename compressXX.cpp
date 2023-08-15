#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>

// yep, it's from forkpezda, from other repo not by me
class InputParser {
    public:
        InputParser(int& argc, char** argv) {
            for (int i = 1; i < argc; ++i)
                this->tokens.push_back(std::string(argv[i]));
        }
        /// @author iain
        const std::string& getCmdOption(const std::string& option) const {
            std::vector<std::string>::const_iterator itr;
            itr = std::find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
                return *itr;
            }
            static const std::string empty_string("");
            return empty_string;
        }
        /// @author iain
        bool cmdOptionExists(const std::string& option) const {
            return std::find(this->tokens.begin(), this->tokens.end(), option)
                != this->tokens.end();
        }
    private:
        std::vector <std::string> tokens;
};

int main(int argc, char** argv)
{
    InputParser input(argc, argv);
    int compressLevel = 9;

    if (input.cmdOptionExists("-h")) {
        fprintf(stderr, "usage: compressxx [-f file] [-l 9]\n" \
            "Options:\n" \
            "\t-f\tyour_file\n" \
            "\t-l\tcompress level (3,5,7,9)\n" \
            "\t-t\thow many times the file will be compressed\n" \
            "\t-h\tShow this message\n");
    }
    if (input.cmdOptionExists("-f")) {
        std::string compressLvl = input.getCmdOption("-l");
        std::string times = input.getCmdOption("-t");
        std::int16_t timesInt = stoi(times);
        std::string file = input.getCmdOption("-f");
        if (compressLvl != "") {
            compressLevel = stoi(compressLvl);
            system(("7z a -mx9 "+file+".xz "+file).c_str());
            system(("7z a -mx9 " + file + "_1.xz " + file).c_str());
            for (int i = 2; i < timesInt; ++i) {
                system(
                    (
                        "7z a -mx"+std::to_string(compressLevel)+" " +
                        file+
                        "_"+std::to_string(i)+
                        ".xz "+
                        file+"_"+
                        std::to_string(i-1)+
                        ".xz"
                    ).c_str()
                );
            }
        }
    }
    else {
        std::cout << "error: no command";
    }
    return 0;
}