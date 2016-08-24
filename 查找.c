#include "sort.h"
#define OK 0
#define ERROR -1
#define Status int

Status Sequ_Search(int a[],int length,int target);
//顺序查找，设置哨兵在最后一个元素之后
Status Binary_Search(int a[],int length,int target);
//折半查找(迭代法)
Status BinarySearch_sub(int a[],int start,int end,int target);
//折半查找(递归法)的子过程
Status BinarySearch(int a[],int length,int target);
//折半查找(递归法)，封装了具体实现的子过程，只需要提供长度即可
Status Fibonacci_Search(int a[],int length,int target);
//斐波那契查找(迭代法)
void getFibonacci(int f[],int length);
//求斐波那契数列的前length个存在f中
Status FibonacciSearch_sub(int a[],int start,int end,int target,int f[],int n);
//斐波那契查找(递归法)的子过程
Status FibonacciSearch(int a[],int length,int target);
//斐波那契查找(递归法)，求斐波那契数列和其他准备工作，然后调用子过程查找

Status Sequ_Search(int a[],int length,int target){
    int i;
    a[length]=target;
    for(i=0;a[i] != target;i++);    //不用判断i是否小于length，提高效率
    return i==length?ERROR:i;
}
Status Binary_Search(int a[],int length,int target){
    int but=length-1,top=0;
    int mid;
    while(top<=but){
        mid=(top+but)/2;
        if(target==a[mid])return mid;
        else if(target>a[mid])top=mid+1;
        else but=mid-1;
    }
    return ERROR;
}
int BinarySearch_sub(int a[],int start,int end,int target){    //递归法折半查找
    int mid=(start+end)/2;
    if(target==a[mid])return mid;
    else if(start>end)return ERROR;        //注意这里要大于，如果只是等于，则如果出现start=53,end=53,这是mid=53,若end=mid-1则出现问题
    else if(target<a[mid])return BinarySearch_sub(a,start,mid-1,target);
    else if(target>a[mid])return BinarySearch_sub(a,mid+1,end,target);
}
int BinarySearch(int a[],int length,int target){
    return BinarySearch_sub(a,0,length-1,target);
}
void getFibonacci(int f[],int length){
    int i;
    f[0]=f[1]=1;
    for(i=2;i<length;i++){
        f[i]=f[i-1]+f[i-2];
    }
}
Status Fibonacci_Search(int a[],int length,int target){
    int f[45];			//斐波那契数列40多就超过long int能表示的最大数了 
    int index,i;
    int low,high,mid;
    getFibonacci(f,45);
    index=0;
    low=0;
    high=length-1;
    while(f[index]-1 < length)index++;
    for(i=length;i<f[index]-1;i++)a[i]=a[length-1]; //不够则填充满
    while(low<=high){
        mid=f[index-1]-1+low;
        if(target == a[mid]){
            if(mid < length)return mid;
            else return length-1;
        }else if(target < a[mid]){
            high=mid-1;
            index--;
        }else{
            low=mid+1;
            index-=2;
        }
    }
    return ERROR;
}
Status FibonacciSearch_sub(int a[],int start,int end,int target,int f[],int n){
    int mid;
    mid=f[n-1]-1+start;
    if(start > end)return ERROR;
    else if(a[mid] == target)return mid;
    else if(target < a[mid])return FibonacciSearch_sub(a,start,mid-1,target,f,n-1);
    else return FibonacciSearch_sub(a,mid+1,end,target,f,n-2);
}
Status FibonacciSearch(int a[],int length,int target){
    int f[45];
    int index,i;
    getFibonacci(f,45);
    index=0;
    while(f[index]-1 < length)index++;
    for(i=length;i<f[index]-1;i++)a[i]=a[length-1];
    index=FibonacciSearch_sub(a,0,length-1,target,f,index);
    return index>=length?length-1:index;
}
int main(){
	int *a;
    int i;
    int num;
    int find1,find2;
    creatarr(&a,100,100);
    BinInsertSort(a,100);
    display(a,100);
    printf("\n");
    for(i=0;i<100;i++){
	    num=rand()%100;
	    find1=Fibonacci_Search(a,100,num);
	    find2=FibonacciSearch(a,100,num);
	    printf("%d:%d  %d:%d",num,find1,num,find2);
	    if(find1 != find2)printf(" false\n");
	    else printf("\n");
	}
    return 0;
}
