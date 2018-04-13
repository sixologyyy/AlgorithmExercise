//计数排序，升序
/*
对一定范围内的整数排序时，它的复杂度为Ο(n+k)，其中k是整数的范围，快于任何比较排序算法
用额外的存储空间O(k)来换取速度,当k>nlogn的时候效率就不高了

对于给定的输入序列中的每一个元素x，确定该序列中值小于x的元素的个数，那么可以直接确定排序后放置的位置
1.用count[i]记录数字i出现的次数
2.依次用count[i-1]更新count[i]，此时count[i]记录了<=i的数字出现的次数
3.把数i放入count[i]的位置

*/

#include <iostream>
#define MAXN 1000

using namespace std;

int k = 1000;      //整数不超过1000
int a[MAXN], cnt[MAXN], ranked[MAXN];
 
int main() 
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) 
    {
        cin >> a[i]; 
        cnt[a[i]]++;
    }
    for (int i = 1; i < k; ++i)
        cnt[i] += cnt[i-1];
    for (int i = n-1; i >= 0; --i)
        ranked[--cnt[a[i]]] = a[i];   //如果是i表达的是原数标号，a[i]就是排序后的正确序列

    cout<<endl;
    for (int i = 0; i < n; ++i)
        cout << ranked[i] << " ";
    cout<<endl;
    return 0;
}