#include <iostream>
#include <fstream>
#include <queue>
#include <cctype>

int main() {
    std::ifstream inFile("input.txt");
    std::ofstream outFile("output_filter.txt");
    std::queue<char> charQueue;

    if (!inFile || !outFile) {
        std::cerr << "Error opening files!" << std::endl;
        return 1;
    }

    char ch;
    while (inFile.get(ch)) {
        charQueue.push(ch);
    }

    while (!charQueue.empty()) {
        outFile.put(std::toupper(charQueue.front()));
        charQueue.pop();
    }

    inFile.close();
    outFile.close();
    return 0;
}
