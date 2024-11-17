#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <algorithm>

void splitPush(const std::string& s, std::vector<std::string>& v) {
    std::istringstream iss(s);
    std::string w;
    while (iss >> w) {
        v.push_back(w);
    }
}

int main() {
    int l1, l2;
    std::cin >> l1 >> l2;
    std::cin.ignore();

    std::string s;
    std::vector<std::string> attributes1;
    std::getline(std::cin, s);
    splitPush(s, attributes1);

    std::vector<std::vector<std::string>> r1(l1);
    for (int i = 0; i < l1; i++) {
        std::getline(std::cin, s);
        splitPush(s, r1[i]);
    }

    std::getline(std::cin, s);
    std::vector<std::string> attributes2;
    splitPush(s, attributes2);

    std::vector<std::vector<std::string>> r2(l2);
    for (int i = 0; i < l2; i++) {
        std::getline(std::cin, s);
        splitPush(s, r2[i]);
    }

    std::unordered_set<std::string> common_fields;
    std::string x;
    while (std::cin >> x) {
        common_fields.insert(x);
    }

    std::vector<int> indx1, indx2;

    for (const auto& field : common_fields) {
        auto elem1 = std::find(attributes1.begin(), attributes1.end(), field);
        auto elem2 = std::find(attributes2.begin(), attributes2.end(), field);
        if (elem1 != attributes1.end()) {
            indx1.push_back(std::distance(attributes1.begin(), elem1));
        }
        if (elem2 != attributes2.end()) {
            indx2.push_back(std::distance(attributes2.begin(), elem2));
        }
    }

    std::vector<std::vector<std::string>> joined_records;

    for (const auto& record1 : r1) {
        for (const auto& record2 : r2) {
            bool match = true;
            for (int i = 0; i < indx1.size(); i++) {
                if (record1[indx1[i]] != record2[indx2[i]]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                std::vector<std::string> joined_record = record1;
                for (int i = 0; i < attributes2.size(); i++) {
                    if (common_fields.find(attributes2[i]) == common_fields.end()) {
                        joined_record.push_back(record2[i]);
                    }
                }
                joined_records.push_back(joined_record);
            }
        }
    }

    std::vector<std::string> joined_attributes = attributes1;
    for (const auto& attr : attributes2) {
        if (common_fields.find(attr) == common_fields.end()) {
            joined_attributes.push_back(attr);
        }
    }

    for (const auto& attr : joined_attributes) {
        std::cout << attr << " ";
    }
    std::cout << std::endl;

    for (const auto& record : joined_records) {
        for (const auto& field : record) {
            std::cout << field << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
