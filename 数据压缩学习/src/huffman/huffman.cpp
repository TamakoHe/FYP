#include <iostream>
#include <vector>
#include <map>
#include <optional>
#include <queue>
template<typename Ty>
class HuffmanNode {
public:
    std::optional<Ty> node_data{std::nullopt};
    size_t freq{0};
    HuffmanNode<Ty> *left{nullptr};
    HuffmanNode<Ty> *right{nullptr};
};
template<typename Ty>
HuffmanNode<Ty>* construct_HuffmanTree(const std::vector<Ty> &input_data) {
    std::map<Ty, size_t> counts;
    for (const auto &d:input_data) {
        if (!counts.contains(d)) {
            counts[d] = 1;
        }else {
            ++counts[d];
        }
    }
    class DataWithCounts {
    public:
        size_t freq;
        HuffmanNode<Ty> *current_node{nullptr};
        explicit DataWithCounts(size_t freq):  freq(freq) {
            current_node=new HuffmanNode<Ty>();
            current_node->freq=freq;

        }
        DataWithCounts( size_t freq, HuffmanNode<Ty> *current_node):  freq(freq), current_node(current_node) {}
        bool operator<(const DataWithCounts &other) const {
            return freq > other.freq;
        }
        void set_val(Ty val)  {
            if (current_node) {
                current_node->node_data=val;
            }
        }
    };
    std::priority_queue<DataWithCounts> data_counts;
    for (auto &[val,freq]:counts) {
        DataWithCounts tt{freq};
        tt.set_val(val);
        data_counts.push(tt);
    }
    while (!data_counts.empty()) {
        auto t1=data_counts.top();
        data_counts.pop();
        auto t2=data_counts.top();
        data_counts.pop();
        auto temp_root=new HuffmanNode<Ty>();
        auto temp_left=t1.current_node;
        auto temp_right=t2.current_node;
        temp_left->freq=t1.freq;
        temp_right->freq=t2.freq;
        temp_root->left=temp_left;
        temp_root->right=temp_right;
        temp_root->freq=t1.freq+t2.freq;
        if (data_counts.empty()) {
            return temp_root;
        }
        data_counts.emplace(temp_root->freq, temp_root);
    }
    return nullptr;
}
template<typename Ty>
void __generate_huffman_map(HuffmanNode<Ty> *c_root, std::map<Ty,std::vector<int>>& c_map, std::vector<int> &c_path) {
    if (c_root&&c_root->node_data.has_value()) {
        c_map[c_root->node_data.value()]=c_path;
    }else if (c_root) {
        auto temp_path=c_path;
        c_path.push_back(0);
        __generate_huffman_map(c_root->left,c_map,c_path);
        c_path=temp_path;
        c_path.push_back(1);
        __generate_huffman_map(c_root->right,c_map,c_path);
        c_path=temp_path;
    }
}
template<typename Ty>
std::map<Ty, std::vector<int>> generate_huffman_map(HuffmanNode<Ty> *root) {
    std::map<Ty, std::vector<int>> result;
    std::vector<int> path;
    __generate_huffman_map(root, result, path);
    return result;
}
int main() {
    const std::vector<char> test_vector{'A','A','B','B','B','B','C','D','D','E','E','E','E','E'};
    auto huffman_root=construct_HuffmanTree(test_vector);
    auto res_map=generate_huffman_map(huffman_root);
    for (auto &[val, vec]:res_map) {
        std::cout << val << ":";
        for (auto &it:vec) {
            std::cout << it << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
