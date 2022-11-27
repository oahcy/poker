#include <vector>
#include <string>
#include <algorithm>

std::string sort(const std::vector<int>& input) {
    if (input.empty()) {
        return "";
    }
    auto sortInput = input;
    std::sort(sortInput.begin(), sortInput.end());
    std::string sortStr;
    for (auto const &num : sortInput) {
        sortStr += std::to_string(num);
        sortStr += " ";
    }
    sortStr.erase(sortStr.size() - 1);
    return sortStr;
}