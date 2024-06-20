# 一、這是一個在Zerojudge上的題目
## 1.題目為解碼一組等式，找到各項符號的意義
## 2.網址為：https://zerojudge.tw/ShowProblem?problemid=a082
# 二、目前思路
## 1.先找必為數字的位置，求出符號可能的位置
## 2.數字必在符號、頭尾及重複的情況
## 3.只有13個符號，因此目前使用int做位元運算
<br/>

# 三、目前程式作用
## 1.目前已可找出等號的位置
## 2.變數意義
```cpp
    const int pow13 = pow(13)-1;//節省多次使用的計算時間
    int is_num=0;//是數字的位置
    int is_sign=0;//是符號的位置(is_num ^ pow13)
    int equal_sign= pow13;//等號的位置(位元運算用)
    int equal_pos;//等號的位置
    int n;//等式數量
    string equation[n];//輸入等式的儲存區
    int bit_equation[n];//紀錄出現過的符號
```