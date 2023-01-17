//
// Created by Cole Sutton on 10/31/22.
//

#ifndef CS236PROJECT1_HEADER_H
#define CS236PROJECT1_HEADER_H
#include <vector>

class Header{
private:
    std::vector<std::string> columnNames;
public:
    Header() = default;
    Header(std::vector<std::string> columnNames) {
        this->columnNames = columnNames;
    }

    const std::vector<std::string> &getColumnNames() const {
        return columnNames;
    }


    void updateHeader(std::vector<std::string> columnNamesNew) {
        this->columnNames = columnNamesNew;
    }
};

#endif //CS236PROJECT1_HEADER_H
