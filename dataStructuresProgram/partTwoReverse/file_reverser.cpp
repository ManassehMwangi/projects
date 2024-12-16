
#include <iostream>
#include <fstream>
#include <stack>

int main() {
    std::ifstream inFile("input.txt");
    std::ofstream outFile("output_reverse.txt");
    std::stack<char> charStack;

    if (!inFile || !outFile) {
        std::cerr << "Error opening files!" << std::endl;
        return 1;
    }

    char ch;
    while (inFile.get(ch)) {
        charStack.push(ch);
    }

    while (!charStack.empty()) {
        outFile.put(charStack.top());
        charStack.pop();
    }

    inFile.close();
    outFile.close();
    return 0;
}
