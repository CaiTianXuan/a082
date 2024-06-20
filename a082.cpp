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
    char question[13]={'a','b','c','d','e','f','g','h','i','j','k','l','m'};//corresponent character
    //bitset<13>type
    static const int pow13 = pow(13)-1;//全域常數
    int is_num=0;
    int is_sign=0;
    int not_equal_sign=0;
    int equal_sign= pow13;
    int all_appeared_type = 0;//紀錄
    //normal
    int equal_pos = -1;
    int n;
    scanf("%d",&n);
    string equation[n];
    int bit_equation[n];
    int len[n];
    for (int i = 0; i < n; i++)
    {
        cin>>equation[i];
        len[i] = equation[i].size();
        printf("len: %d\n",len);
        bit_equation[i]=0;
        //is num => aa is num; abcde ae is num
        is_num |=pow(equation[i][0]-'a');//head
        is_num |=pow(equation[i][len[i]-1]-'a');//end
        //printf("equation[%d]= %c",i,equation[i][0]);
        bit_equation[i] |= pow(equation[i][0]-'a');
        for (int j = 1; j < len[i]; j++)
        {
            if(equation[i][j] == equation[i][j-1])
            {
                is_num |=pow(equation[i][j]-'a');
            }
            bit_equation[i] |= pow(equation[i][j]-'a');
            //printf("%c",equation[i][j]);
        }
        //printf("\n");
        all_appeared_type |= bit_equation[i];
        is_sign = is_num ^pow13;//符號非數字
        equal_sign &= bit_equation[i];//每一等式皆有=
        equal_sign &= is_sign;//等號必為符號
        cout<<"equal_sign= "<<bitset<13>(equal_sign)<<endl;
        cout<<"is_num= "<<bitset<13>(is_num)<<endl;
        cout<<"is_sign= "<<bitset<13>(is_sign)<<endl;
        if(__builtin_popcount(equal_sign) == 1)
        {
            equal_pos=__builtin_ctz(equal_sign);
            printf("equal position: %d\n",equal_pos);
        }
    }
    if(equal_pos != -1)//actions after finding equal
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < len[i]; j++)
            {
                if(equation[i][j] - 'a' == equal_pos)
                {
                    if(j>0)
                        is_num |=pow(equation[i][j-1]-'a');
                    if(j+1<len[i])
                        is_num |=pow(equation[i][j+1]-'a');
                }
            }
        }
        is_sign = is_num ^ pow13;
        is_sign &= all_appeared_type;//去除沒出現的數字及符號
        not_equal_sign = is_sign ^ equal_sign;//找到加和乘
        cout<<"is_sign= "<<bitset<13>(not_equal_sign)<<endl;
        if(__builtin_popcount(not_equal_sign) == 0)//太快樂了只能確定等號
        {
            cout<<question[equal_pos]<<'='<<endl;
        }
        else if(__builtin_popcount(not_equal_sign) == 1)//加號或乘號
        {
            
        }
        else if(__builtin_popcount(not_equal_sign) == 2)//加號和乘號
        {
            //分析假設

        }
        else{return 1;}//你要不要看看自己在幹啥
    }
    else//沒找到等號還分析個鳥
    {
        cout<<"noway"<<endl;
    }
    return 0;
    
}