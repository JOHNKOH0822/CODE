#include <iostream>
#include "Sales_item.h"

int main(){
    std::cout << "Enter integers ";
    int currVal, val ;
    if (std::cin >> currVal)
    {
        int count = 1;
        while (std::cin >> val)
        {
            if (val == currVal)
            {
                count ++;
            }
            else{
                std::cout << currVal << " occurs " << count << " times " << std::endl;
                currVal = val, count = 1;
            }
        }
        std::cout << currVal << " occurs " << count << " times " << std::endl;
    }
    
    return 0;
}