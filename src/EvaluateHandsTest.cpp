#include "Util/Evaluator.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

void generateCombinations(const std::vector<std::string>& cards, int start, int depth, int size, std::vector<std::string>& current, std::ofstream& output) {
    if (depth == size) {
        HandResult result = evalHand(current);
        output << result.handName << "," << result.handType << "," << result.handRank << "\n";
        return;
    }

    for (int i = start; i <= cards.size() - (size - depth); ++i) {
        current[depth] = cards[i];
        generateCombinations(cards, i + 1, depth + 1, size, current, output);
    }
}

void generateCSV(const std::vector<std::string>& cards, const std::string& filename, int handSize) {
    std::ofstream output(filename);
    output << "Name,Type,Rank\n";
    std::vector<std::string> current(handSize);
    generateCombinations(cards, 0, 0, handSize, current, output);
    output.close();
}

int main() {
    const char* path = "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/src/HandRanks.dat";

    if (!loadHandRanks(path)) {
        std::cerr << "Failed to load HandRanks.dat file\n";
        return 1;
    }

    std::vector<std::string> cards = {
        "2c", "2d", "2h", "2s", "3c", "3d", "3h", "3s", "4c", "4d", "4h", "4s",
        "5c", "5d", "5h", "5s", "6c", "6d", "6h", "6s", "7c", "7d", "7h", "7s",
        "8c", "8d", "8h", "8s", "9c", "9d", "9h", "9s", "Tc", "Td", "Th", "Ts",
        "Jc", "Jd", "Jh", "Js", "Qc", "Qd", "Qh", "Qs", "Kc", "Kd", "Kh", "Ks",
        "Ac", "Ad", "Ah", "As"
    };

    generateCSV(cards, "5_card_hands.csv", 5);
    generateCSV(cards, "6_card_hands.csv", 6);
    generateCSV(cards, "7_card_hands.csv", 7);

    std::cout << "CSV files generated successfully.\n";
    return 0;
}
