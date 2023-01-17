//
// Created by Cole Sutton on 10/4/22.
//

#ifndef CS236PROJECT1_PARAMETER_H
#define CS236PROJECT1_PARAMETER_H

class Parameter{
private:
    std::string myParam;
public:
    Parameter(std::string myParam) {
        this->myParam = myParam;
    }

    const std::string &getMyParam() const {
        return myParam;
    }
};

#endif //CS236PROJECT1_PARAMETER_H
