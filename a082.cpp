#include<stdio.h>
#include<map>
#include<iostream>
#include <bitset>
#include<string.h>

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
    int is_sign=0;
    int equal_sign= pow13;
    int equal_pos;
    int n;
    scanf("%d",&n);
    string equation[n];
    int bit_equation[n];
    for (int i = 0; i < n; i++)
    {
        cin>>equation[i];
        int len = equation[i].size();
        printf("len: %d\n",len);
        bit_equation[i]=0;
        //is num => aa is num; abcde ae is num
        is_num |=pow(equation[i][0]-'a');//head
        is_num |=pow(equation[i][len-1]-'a');//end
        //printf("equation[%d]= %c",i,equation[i][0]);
        bit_equation[i] |= pow(equation[i][0]-'a');
        for (int j = 1; j < len; j++)
        {
            if(equation[i][j] == equation[i][j-1])
            {
                is_num |=pow(equation[i][j]-'a');
            }
            bit_equation[i] |= pow(equation[i][j]-'a');
            //printf("%c",equation[i][j]);
        }
        //printf("\n");
        is_sign = is_num ^pow13;
        equal_sign &= bit_equation[i];
        equal_sign &= is_sign;
        cout<<"equal_sign= "<<bitset<13>(equal_sign)<<endl;
        cout<<"is_num= "<<bitset<13>(is_num)<<endl;
        cout<<"is_sign= "<<bitset<13>(is_sign)<<endl;
        if(__builtin_popcount(equal_sign) == 1)
        {
            equal_pos=__builtin_ctz(equal_sign);
            printf("equal position: %d\n",equal_pos);
        }
    }
    
}