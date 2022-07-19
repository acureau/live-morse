#include <windows.h>
#include <iostream>
#include <conio.h>
#include <queue>
#include <map>

DWORD frequency = 750;
DWORD interval = 50;
std::map<char, std::string> char_map = {
    {'A', ".-"},
    {'B', "-..."},
    {'C', "-.-."},
    {'D', "-.."},
    {'E', "."},
    {'F', "..-."},
    {'G', "--."},
    {'H', "...."},
    {'I', ".."},
    {'J', ".---"},
    {'K', "-.-"},
    {'L', ".-.."},
    {'M', "--"},
    {'N', "-."},
    {'O', "---"},
    {'P', ".--."},
    {'Q', "--.-"},
    {'R', ".-."},
    {'S', "..."},
    {'T', "-"},
    {'U', "..-"},
    {'V', "...-"},
    {'W', ".--"},
    {'X', "-..-"},
    {'Y', "-.--"},
    {'Z', "--.."},
    {'1', ".----"},
    {'2', "..---"},
    {'3', "...--"},
    {'4', "....-"},
    {'5', "....."},
    {'6', "-...."},
    {'7', "--..."},
    {'8', "---.."},
    {'9', "----."},
    {'0', "-----"},
    {32, "......."},// Space
};
std::queue<char> beeps;

void do_beep() {
    while (1) {
        if (beeps.size() > 0) {
            char letter = beeps.front();
            beeps.pop();

            std::string morse = char_map.find(letter)->second;
            if (morse == ".......") {
                Sleep(7*interval);
            }
            else {
                for (auto &ch : morse) {
                    if (ch == '.') {
                        Beep(frequency, interval);
                    }
                    else {
                        Beep(frequency, 3*interval);
                    }
                    Sleep(interval);
                }
                Sleep(3*interval);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        frequency = (DWORD)atoi(argv[1]);
        interval = (DWORD)atoi(argv[2]);
    }

    HANDLE beeper = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)do_beep, 0, 0, NULL);
    std::cout << "<CTRL-C to Exit>\n";
    std::cout << "Frequency: " << frequency << "hz\n";
    std::cout << "Time Unit: " << interval << "ms\n\n";
    
    while (1) {
        char letter = toupper(_getch());

        if ((&letter != NULL) && (char_map.find(letter) != char_map.end()) || (letter == 3 || letter == 13)) {
            if (letter == 3) {
                break;
            }
            else if (letter == 13) {
                std::cout << "\n";
            }
            else {
                std::cout << letter;
                beeps.push(letter);
            }
        }
    }
}
