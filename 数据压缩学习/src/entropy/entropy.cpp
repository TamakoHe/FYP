#include <iostream>
#include <vector>
#include <cmath>
#include <map>
template<typename Ty>
double entropy(const std::vector<Ty> &data) {
    std::map<Ty, size_t> counts;
    for (const auto &d:data) {
        if (!counts.contains(d)) {
            counts[d] = 1;
        }else {
            ++counts[d];
        }
    }
    double result = 0;
    for (auto &[val,freq]:counts) {
        auto pr=static_cast<double>(freq)/data.size();
        result+=-pr*std::log2(pr);
    }
    return result;
}
int main() {
    std::vector<char> data{'A','B','B','C','C','C','D','D','D','D'};
    auto res=entropy(data);
    std::cout << res << std::endl;
    return 0;
}