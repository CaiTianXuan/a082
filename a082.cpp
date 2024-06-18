#include<stdio.h>
#include<map>
#include<iostream>
#include <bitset>

using namespace std;

int pow(int times)
{
    int ans = 1;
    ans <<= times;
    return ans;
}

int main()
{
    const int pow13 = pow(13)-1;
    int is_num=0;
    int is_equal=0;
    int equal_sign;
    equal_sign = pow13;
    int equal_pos;
    int n;
    scanf("%d",&n);
    char equation[n][11];
    int bit_equation[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%s",equation[i]);
        int len = sizeof(equation)/sizeof(char);
        bit_equation[i]=0;
        //is num => aa is num; abcde ae is num
        is_num |=pow(equation[i][0]-'a');
        is_num |=pow(equation[i][len-1]-'a');
        bit_equation[i] |= pow(equation[i][0]-'a');
        for (int j = 1; j < len; j++)
        {
            if(equation[i][j] == equation[i][j-1])
            {
                is_num |=pow(equation[i][j]-'a');
            }
            bit_equation[i] |= pow(equation[i][j]-'a');
        }
        is_equal = is_num ^pow13;
        equal_sign &= bit_equation[i];
        cout<<bitset<13>(bit_equation[i])<<endl;
        equal_sign &= is_num;
        cout<<bitset<13>(equal_sign)<<endl;
        if(__builtin_popcount(equal_sign) == 1)
        {
            equal_pos=__builtin_ctz(equal_sign);
            printf("equal position: %d\n",&equal_pos);
        }
    }
    
}