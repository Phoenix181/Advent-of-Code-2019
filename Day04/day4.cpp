#include <iostream>
#include <map>

long criteriaCheck(long lower, long higher)
{
    int passwordsCount = 0;
    for (int i = lower; i <= higher; i++)
    {
        int temp = i;
        bool password = true, repeating = false, firstTime = true;
        std::map<int, int> repeatingCount;
        while (temp != 0)   
        {
            int rema = temp % 10;
            temp /= 10;
            if (rema < temp % 10)
                password = false;
            if (repeatingCount.find(rema) == repeatingCount.end())
                repeatingCount.insert({rema, 1});
            else
                repeatingCount.at(rema)+=1;
        }

        for(auto num = repeatingCount.begin(); num != repeatingCount.end(); ++num) {
            if(num -> second == 2)
                repeating = true;
        }

        if (repeating && password)
            passwordsCount++;
    }
    return passwordsCount;
}

int main()
{
    int lower, higher;
    char temp;
    std::cin >> lower >> temp >> higher;

    std::cout << "Result:" << criteriaCheck(lower, higher) << std::endl;
}