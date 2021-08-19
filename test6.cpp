#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int n, sum;
    cin >> sum>>n;
    vector<long>vec(sum + 1, 0), input(n + 1, 0);
    vec[0] = 1;////这一步的目的是如果当前数字中的元素刚好等于要求的，就是多一种方法
               //如果不赋值为1，还是为0就没办法加一种方法
    vector<vector<long> >result(n + 1, vec);
    for (int i = 1; i <= n; i++)
    {
        cin >> input[i];
    }
    //程序多加一行的目的是，例如：result[1][5]=result[0][5]+result[0][5-input[1]](即result[0][0])
    //多加一行方便整体运算不需分类计算
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            if (j - input[i] >= 0)
            {
                //如果列所在数字减去该行数大于等于0，该格子内容为该列上一行数字与上一行差
                // 值所在格子数量和。什么意思呢？例如(10,3)，若想要用3之前的数列得到10，除了
                // 它上一行(即2)本身就能得到2个10外，只要之前的数字是7,7+3依然可以得到10。因
                // 此去看上一行中列数为7的格子数值，为2，即它上一个数有2中组合得到7,7+3=10。
                // 那该行数值即为2+2=4。
                result[i][j] = result[i - 1][j] + result[i - 1][j - input[i]];
            }
            else
            {//果列所在数字减去该行数小于0，那么该格子继承本列上一行的数字。
                result[i][j] = result[i - 1][j];
            }
        }
    }
    cout << result[n][sum] << endl;
    if(result[n][sum] > 0) {
        return result[n][sum];
    }
    return -1;
}