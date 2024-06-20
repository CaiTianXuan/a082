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

char question[13]={'a','b','c','d','e','f','g','h','i','j','k','l','m'};//corresponent character
char checked[13];//a to m record its num or sign
//bitset<13>type
const int pow13 = pow(13)-1;//全域常數
int is_num=0;
int is_sign=0;
int not_equal_sign=0;
int equal_sign= pow13;
int all_appeared_type = 0;//紀錄
//normal
int equal_pos = -1;
int n;
string equation[1000];

bool try_Add(char add_sign, char multi_sign);//true for add is right

int main()
{
    for (int j = 0; j < 13; j++)checked[j]='0';
    scanf("%d",&n);
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
            checked[equal_pos] = '=';
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
        cout<<"not_equal_sign= "<<bitset<13>(not_equal_sign)<<endl;
        if(__builtin_popcount(not_equal_sign) == 0)//太快樂了只能確定等號
        {
            cout<<question[equal_pos]<<'='<<endl;
        }
        else if(__builtin_popcount(not_equal_sign) == 1)//加號或乘號
        {
            //嘗試加法
            bool result = try_Add(question[__builtin_ctz(not_equal_sign)],' ');
            if(result)//is add
                checked[__builtin_ctz(not_equal_sign)] = '+';
            else//is multi
                checked[__builtin_ctz(not_equal_sign)] = '*';
        }
        else if(__builtin_popcount(not_equal_sign) == 2)//加號和乘號
        {
            //分析假設
            int right_one = __builtin_ctz(not_equal_sign);
            int left_one = __builtin_ctz(not_equal_sign ^ pow(right_one));
            bool result = try_Add(question[right_one]
                ,question[left_one]);
            //because we won't use "not_equal_sign" again, so I don't recaculate it
            if(result)//is add
            {
                cout<<"find! correct guess"<<endl;
                checked[right_one] = '+';checked[left_one] = '*';
            }
            else//is multi
            {
                cout<<"find! wrong guess"<<endl;
                checked[right_one] = '*';checked[left_one] = '+';
            }
        }
        else{return 1;}//你要不要看看自己在幹啥
    }
    else//沒找到等號還分析個鳥
    {
        cout<<"noway"<<endl;
    }
    cout<<"line 130 runnnnnn!"<<endl;
    for (int i = 0; i < 13; i++)
    {
        if(checked[i]!='0')
            cout<<question[i]<<checked[i]<<endl;
    }
    
    return 0;
    
}

bool try_Add(char add_sign, char multi_sign)//check if add sign is real adding
{
// a + b = c ; b + c = d ; a + c + d = e (1,2,3,5,9)
// a + b = cd c=1
// a + b = cb 不成立
    bool mode = false;//recognize two signs or not
    int count_char[13];//record how many times the char should have
    if(multi_sign == ' ')
    {
        //only one sign to recognize
        mode = true;
    }
    if(mode)
    {
        for (int i = 0; i < n; i++)
        {
            cout<<"diagnozing equation i= "<<i<<endl;
            int accumulate = 1;
            bool state = 1;
            for (int j = 0; j < 13; j++)count_char[j]=0;
            for ( std::string::iterator it=equation[i].end(); it!=equation[i].begin(); --it)//倒寫
            {
                if(*it == add_sign)
                {
                    cout<<"+ ";
                    accumulate = (state)? 1 : -1;
                }
                else if(*it == question[equal_pos])
                {
                    cout<<"= ";
                    accumulate = -1;//等號另一側用扣的
                    state = 0;
                }
                else
                {
                    cout<<*it<<' ';
                    count_char[*it-'a']+=accumulate;
                    accumulate*=10;
                }
                
            }
            cout<<endl;
            int count_l=0,count_r=0;
            for (int j = 0; j < 13; j++)
            {
                if(count_char[j]>0)
                    count_r += count_char[j];
                else if(count_char[j]<0)
                    count_l -= count_char[j];
            }
            if(count_l/count_r >=10 || count_r/count_l >=10)
                return false;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)//test pure adding equation
        {
            cout<<"diagnozing equation i= "<<i<<endl;
            int accumulate = 1;
            bool state = 1;
            bool multi_appear = false;
            for (int j = 0; j < 13; j++)count_char[j]=0;
            for ( std::string::iterator it=equation[i].end()-1; it+1!=equation[i].begin(); --it)//倒寫
            {
                if(*it == add_sign)
                {
                    cout<<"+ ";
                    accumulate = (state)? 1 : -1;
                }
                else if(*it == question[equal_pos])
                {
                    cout<<"= ";
                    accumulate = -1;//等號另一側用扣的
                    state = 0;
                }
                else if(*it == multi_sign)
                {
                    cout<<"* ";
                    multi_appear=true;
                }
                else
                {
                    cout<<*it<<' ';
                    count_char[*it-'a']+=accumulate;
                    accumulate*=10;
                }
            }
            cout<<endl;
            if(multi_appear)continue;
            int count_l=0,count_r=0;
            for (int j = 0; j < 13; j++)
            {
                if(count_char[j]>0)
                    count_r += count_char[j];
                else if(count_char[j]<0)
                    count_l -= count_char[j];
            }
            if(count_l/count_r >=10 || count_r/count_l >=10)
                return false;
        }
        for (int i = 0; i < n; i++)//maybe multi sign is the real adding
        {
            cout<<"diagnozing equation i= "<<i<<endl;
            int accumulate = 1;
            bool state = 1;
            bool multi_appear = false;
            for (int j = 0; j < 13; j++)count_char[j]=0;
            for ( std::string::iterator it=equation[i].end(); it!=equation[i].begin(); --it)//倒寫
            {
                if(*it == multi_sign)
                {
                    cout<<"+ ";
                    accumulate = (state)? 1 : -1;
                }
                else if(*it == question[equal_pos])
                {
                    cout<<"= ";
                    accumulate = -1;//等號另一側用扣的
                    state = 0;
                }
                else if(*it == add_sign)
                {
                    cout<<"* ";
                    multi_appear=true;
                }
                else
                {
                    cout<<*it<<' ';
                    count_char[*it-'a']+=accumulate;
                    accumulate*=10;
                }
            }
            cout<<endl;
            if(multi_appear)continue;
            int count_l=0,count_r=0;
            for (int j = 0; j < 13; j++)
            {
                if(count_char[j]>0)
                    count_r += count_char[j];
                else if(count_char[j]<0)
                    count_l -= count_char[j];
            }
            if(count_l/count_r >=10 || count_r/count_l >=10)//multi sign must not be add sign
                return true;
        }
    }
    return true;
}