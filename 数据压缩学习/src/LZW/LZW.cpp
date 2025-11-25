#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <opencv2/opencv.hpp>
#include <stdexcept>

template<typename Ty>
std::vector<size_t> LZW_encode(const std::vector<Ty> & input_vec, const Ty lower_bound, const Ty upper_bound) {
    std::map<std::vector<Ty>, size_t> LZW_map;
    std::map<size_t, std::vector<Ty>> LZW_map_rev;
    size_t pos{0};
    for (Ty it=lower_bound; it<=upper_bound;) {
        std::vector<Ty> t_vec{it};
        LZW_map[t_vec]=pos;
        LZW_map_rev[pos]=t_vec;
        pos++;
        if (it==upper_bound) {
            break;
        }
        ++it;
    }
    std::vector<Ty> P{};
    std::vector<size_t> LZW_code{};
    size_t pos_new_link=upper_bound-lower_bound+1;
    for (const auto &C:input_vec) {
        auto PpC=P;
        PpC.push_back(C);
        if (!LZW_map.contains(PpC)) {
            LZW_code.push_back(LZW_map[P]);
            LZW_map[PpC]=pos_new_link;
            LZW_map_rev[pos_new_link]=PpC;
            ++pos_new_link;
            P=std::vector<Ty>{C};
        }else {
            P=PpC;
        }
    }
    if (!P.empty()) {
        LZW_code.push_back(LZW_map[P]);  // 正确输出最后一段
    }
    return LZW_code;
}
template<typename Ty>
auto LZW_decode(const std::vector<size_t> & input_vec, const Ty lower_bound, const Ty upper_bound) {
    std::map<std::vector<Ty>, size_t> LZW_map;
    std::map<size_t, std::vector<Ty>> LZW_map_rev;
    size_t pos{0};
    for (Ty it=lower_bound; it<=upper_bound;) {
        std::vector<Ty> t_vec{it};
        LZW_map[t_vec]=pos;
        LZW_map_rev[pos]=t_vec;
        pos++;
        if (it==upper_bound) {
            break;
        }
        ++it;
    }
    size_t pW{};
    std::vector<std::vector<Ty>> LZW_decode{};
    size_t pos_new_link=upper_bound-lower_bound+1;
    for (size_t n_pos{0};const auto &cW:input_vec) {
        if (!n_pos) {
            LZW_decode.push_back(LZW_map_rev[cW]);
            pW=cW;
            ++n_pos;
            continue;
        }
        if (LZW_map_rev.contains(cW)) {
            LZW_decode.push_back(LZW_map_rev[cW]);
            auto P=LZW_map_rev[pW];
            auto C=LZW_map_rev[cW].front();
            auto PpC=P;PpC.push_back(C);
            LZW_map[PpC]=pos_new_link;
            LZW_map_rev[pos_new_link]=PpC;
            ++pos_new_link;
            pW=cW;
        }else {
            auto P=LZW_map_rev[pW];
            auto C=LZW_map_rev[pW].front();
            auto PpC=P;PpC.push_back(C);
            LZW_decode.push_back(PpC);
            LZW_map[PpC]=pos_new_link;
            LZW_map_rev[pos_new_link]=PpC;
            ++pos_new_link;
            pW=cW;
        }
        ++n_pos;
    }
    return LZW_decode;
}
int png_example_gray() {
    cv::Mat img = cv::imread("./dic.png", cv::IMREAD_UNCHANGED);
    if (img.empty()) {
        std::cerr << "Failed to read image\n";
        return -1;
    }

    // 如果是多通道（例如 RGB 或 RGBA），可以把它转换为灰度（单通道）
    cv::Mat gray;
    if (img.channels() == 3) {
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    } else if (img.channels() == 4) {
        cv::cvtColor(img, gray, cv::COLOR_BGRA2GRAY);
    } else if (img.channels() == 1) {
        gray = img;  // 本身就是灰度
    } else {
        std::cerr << "Unsupported number of channels: " << img.channels() << "\n";
        return -1;
    }
    // 确保灰度图是 8-bit（0-255）
    if (gray.depth() != CV_8U) {
        std::cerr << "Unexpected image depth. Expected CV_8U.\n";
        return -1;
    }
    int rows = gray.rows;
    int cols = gray.cols;
    std::vector<int> pixels;
    pixels.reserve(rows * cols);
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            uchar v = gray.at<uchar>(r, c);
            pixels.push_back(static_cast<int>(v));
        }
    }
    std::cout<<"pixels: "<<pixels.size()<<std::endl;
    auto encoded=LZW_encode<int>(pixels, 0,255);
    auto decoded=LZW_decode<int>(encoded,0,255);
    std::cout<<"Encoded length:"<<encoded.size()<<std::endl;
    std::cout<<"Compression Rate: "<<static_cast<double>(encoded.size())/pixels.size()<<std::endl;
    std::vector<int> pixels2;
    for (size_t iit{0}; iit<decoded.size();++iit) {
        pixels2.insert(pixels2.end(), decoded[iit].begin(), decoded[iit].end());
    }
    for (size_t iit{0}; iit<pixels2.size();++iit) {
        if (pixels2[iit]!=pixels[iit]) {
            std::cout<<"Err"<<iit<<std::endl;
        }
    }
    std::cout<<"Original pixels: "<<pixels.size()<<std::endl;
    std::cout<<"Decoded pixels: "<<pixels2.size()<<std::endl;
    return 0;
}
int png_example_color() {
    const std::string in_path = "./Jupiter.png";
    const std::string out_path = "./decoded_out.png";

    cv::Mat img = cv::imread(in_path, cv::IMREAD_UNCHANGED);
    if (img.empty()) {
        std::cerr << "Failed to read image: " << in_path << "\n";
        return -1;
    }

    int rows = img.rows;
    int cols = img.cols;
    int channels = img.channels();
    std::cout << "Input image: " << cols << "x" << rows << " channels=" << channels << "\n";

    // Flatten 成 std::vector<int> （值范围 0..255）
    std::vector<int> pixels;
    pixels.reserve(rows * cols * channels);

    if (channels == 1) {
        // 灰度
        for (int r = 0; r < rows; ++r) {
            const uchar* ptr = img.ptr<uchar>(r);
            for (int c = 0; c < cols; ++c) {
                pixels.push_back(static_cast<int>(ptr[c]));
            }
        }
    } else if (channels == 3) {
        // B G R order (OpenCV 默认)
        for (int r = 0; r < rows; ++r) {
            const cv::Vec3b* ptr = img.ptr<cv::Vec3b>(r);
            for (int c = 0; c < cols; ++c) {
                const cv::Vec3b &v = ptr[c];
                pixels.push_back(static_cast<int>(v[0])); // B
                pixels.push_back(static_cast<int>(v[1])); // G
                pixels.push_back(static_cast<int>(v[2])); // R
            }
        }
    } else if (channels == 4) {
        // B G R A order (OpenCV BGRA)
        for (int r = 0; r < rows; ++r) {
            const cv::Vec4b* ptr = img.ptr<cv::Vec4b>(r);
            for (int c = 0; c < cols; ++c) {
                const cv::Vec4b &v = ptr[c];
                pixels.push_back(static_cast<int>(v[0])); // B
                pixels.push_back(static_cast<int>(v[1])); // G
                pixels.push_back(static_cast<int>(v[2])); // R
                pixels.push_back(static_cast<int>(v[3])); // A
            }
        }
    } else {
        std::cerr << "Unsupported number of channels: " << channels << "\n";
        return -1;
    }

    std::cout << "pixels size: " << pixels.size() << "\n";

    // 编码 -> 解码 (保持你原来的接口调用)
    auto encoded = LZW_encode<int>(pixels, 0, 255);
    auto decoded = LZW_decode<int>(encoded, 0, 255);

    // 输出编码信息
    // 注意：encoded.size() 的含义取决于你的 LZW 实现（可能是代码数个数或字节数）
    std::cout << "Encoded length: " << encoded.size() << "\n";
    if (pixels.size() > 0) {
        double rate = static_cast<double>(encoded.size()) / static_cast<double>(pixels.size());
        std::cout << "Compression Rate (encoded.size()/pixels.size()): " << rate << "\n";
    }

    // 将 decoded (假定为 vector<vector<int>> 每个元素为一段符号序列) 串联回 pixels2
    std::vector<int> pixels2;
    // 预分配估计大小（尽量减少额外分配）
    {
        size_t total_est = 0;
        for (size_t i = 0; i < decoded.size(); ++i) total_est += decoded[i].size();
        pixels2.reserve(total_est);
    }

    for (size_t i = 0; i < decoded.size(); ++i) {
        // 关键：append 到末尾
        pixels2.insert(pixels2.end(), decoded[i].begin(), decoded[i].end());
    }

    // 校验长度一致性
    if (pixels2.size() != pixels.size()) {
        std::cerr << "Size mismatch after decode: pixels2.size()=" << pixels2.size()
                  << " original pixels.size()=" << pixels.size() << "\n";
        // 仍然尝试尽可能地写出图像（如果尺寸是原来的整数倍）
    } else {
        // 校验内容一致（可选）
        bool ok = true;
        for (size_t i = 0; i < pixels.size(); ++i) {
            if (pixels2[i] != pixels[i]) {
                std::cerr << "Mismatch at index " << i << ": decoded=" << pixels2[i]
                          << " orig=" << pixels[i] << "\n";
                ok = false;
                break;
            }
        }
        if (ok) std::cout << "Round-trip verified: decoded == original\n";
    }
    try {
        // 首先确保 pixels2 的长度能被 width*height*channels 整除（否则报错）
        size_t expected = static_cast<size_t>(rows) * cols * channels;
        if (pixels2.size() < expected) {
            throw std::runtime_error("decoded pixel count is smaller than expected");
        }
        // 使用前 expected 个元素（如果 decoded 更长则截断）
        cv::Mat out_img;
        if (channels == 1) {
            out_img.create(rows, cols, CV_8UC1);
            for (int r = 0; r < rows; ++r) {
                uchar* row_ptr = out_img.ptr<uchar>(r);
                for (int c = 0; c < cols; ++c) {
                    row_ptr[c] = static_cast<uchar>(pixels2[r * cols + c]);
                }
            }
        } else if (channels == 3) {
            out_img.create(rows, cols, CV_8UC3);
            size_t idx = 0;
            for (int r = 0; r < rows; ++r) {
                cv::Vec3b* row_ptr = out_img.ptr<cv::Vec3b>(r);
                for (int c = 0; c < cols; ++c) {
                    uchar B = static_cast<uchar>(pixels2[idx++]);
                    uchar G = static_cast<uchar>(pixels2[idx++]);
                    uchar R = static_cast<uchar>(pixels2[idx++]);
                    row_ptr[c] = cv::Vec3b(B, G, R);
                }
            }
        } else { // channels == 4
            out_img.create(rows, cols, CV_8UC4);
            size_t idx = 0;
            for (int r = 0; r < rows; ++r) {
                cv::Vec4b* row_ptr = out_img.ptr<cv::Vec4b>(r);
                for (int c = 0; c < cols; ++c) {
                    uchar B = static_cast<uchar>(pixels2[idx++]);
                    uchar G = static_cast<uchar>(pixels2[idx++]);
                    uchar R = static_cast<uchar>(pixels2[idx++]);
                    uchar A = static_cast<uchar>(pixels2[idx++]);
                    row_ptr[c] = cv::Vec4b(B, G, R, A);
                }
            }
        }

        if (!cv::imwrite(out_path, out_img)) {
            std::cerr << "Failed to write output image: " << out_path << "\n";
            return -1;
        } else {
            std::cout << "Wrote decoded image to: " << out_path << "\n";
        }
    } catch (const std::exception &ex) {
        std::cerr << "Exception during image reconstruction: " << ex.what() << "\n";
        return -1;
    }
    return 0;
}
int main() {
    std::string test_str{"ababcababac"};
    std::vector<char> test_vec{test_str.begin(), test_str.end()};
    auto r=LZW_encode<char>(test_vec, 'a', 'c');
    for (const auto &it:r) {
        std::cout<<it<<" ";
    }
    std::cout<<std::endl;
    auto d=LZW_decode<char>(r, 'a', 'c');
    for (const auto& it1:d) {
        std::cout<<std::string(it1.begin(), it1.end());
    }
    std::cout<<std::endl;
    png_example_gray();
    png_example_color();
    return 0;
}