#pragma once
#include <vector>
#include <utility>
class Port
{
private:
public:
    Port()
    {
        for (int i = 2000; i != 40000 ; i++) {
            std::pair<unsigned short, bool> port;
            port.first = i;
            port.second = false;
        }
    }

    unsigned short useNewPort()
    {
        for (int i = 0; i  != ports_.size(); i++) {
            if (ports_[i].second == false){
                return ports_[i].first;
            }
        }
    }
    ~Port(){}
    std::vector<std::pair<unsigned short, bool>> ports_;
};
