#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void creatarr(int **a,int n,int ran);
//初始化动态数组,为a分配长为n的数字，内容大小在区间[0,ran)中
//举例：int *a;
//      creatarr(&a,100,1000)   产生100个内容在0到1000的动态数组
void display(int a[],int n);
//打印数组的内容
void SelectSort(int a[],int n);
//选择排序
void Sort(int a[],int n);
//自己随便搞的排序
void BubbleSort(int a[],int n);
//冒泡排序
void InsertSort(int a[],int n);
//插入排序
void BinInsertSort(int a[],int n);
//折半插入排序
void ShellSort(int a[],int n);
//希尔排序
void QuickSort_sub(int a[],int start,int end);
//快速排序的子过程
void QuickSort(int a[],int length);
//快速排序，封装了快速排序具体实现的子过程，只需要提供长度即可
void MergeSort_sub(int a[],int start,int end,int *p);
//归并排序的子过程
void MergeSort(int a[],int length);
//归并排序，封装了归并排序具体实现的子过程，为其申请辅助空间p，调用子过程后释放，只需要提供长度即可
void HeapSort_sub(int a[],int start,int length);
//堆排序的子过程，假设[start,length)中除start外均满足堆的定义，调整start的位置使成为一个堆
void HeapSort(int a[],int length);
//堆排序，先建立初始堆，再循环处理，将堆顶元素移到末尾，对其余元素调整成为新堆

void creatarr(int **a,int n,int ran){
	int i;
    *a=(int*)malloc(sizeof(int)*n);
    srand(time(NULL));
    for(i=0;i<n;i++)(*a)[i]=rand()%ran;
}
void display(int a[],int n){
    int i;
    for(i=0;i<n;i++){
        printf("%2d ",a[i]);
        if(!((i+1)%10))printf("\n");
    }
    printf("\n");
}
void SelectSort(int a[],int n){
    int min,k,i,j;
    for(i=0;i<n;i++){
        min=a[i];
        k=i;
        for(j=i+1;j<n;j++){
            if(min>a[j]){
                min=a[j];
                k=j;
            }
        }
        if(k!=i){
            a[k]=a[i];
            a[i]=min;
        }
    }
}
void Sort(int a[],int n){
    int t,i,j;
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(a[i]>a[j]){
                t=a[j];
                a[j]=a[i];
                a[i]=t;
            }
        }
    }
}
void BubbleSort(int a[],int n){
    int t,i,j;
    int issort;
    for(i=n;i>0;i--){
        issort=0;
        for(j=0;j<i-1;j++){
            if(a[j]>a[j+1]){
                issort=1;
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
        if(issort == 0)break;
    }
}
void InsertSort(int a[],int n){
    int i,j,t,k;
    for(i=1;i<n;i++){
        for(j=0;j<i;j++){       //其实在这里可以与前一个相比，若比前一个大，则不用交换，若小，则一边比较一边交换
        	if(a[j]>a[i]){      //不用从第一个开始比较
                t=a[i];
                for(k=i-1;k>=j;k--)a[k+1]=a[k];
                a[j]=t;
            }
        }
    }
}
void BinInsertSort(int a[],int n){
    int low,high,mid;
    int i,j,temp;
    for(i=1;i<n;i++){
        low=0;
        high=i-1;
        while(low<=high){
            mid=(low+high)/2;
            if(a[mid] <= a[i])low=mid+1;
            else high=mid-1;
        }
        temp=a[i];
        for(j=i;j>high+1;j--)a[j]=a[j-1];
        a[j]=temp;
    }
}
void ShellSort(int a[],int n){
    int i,j,k,t,q,d;
    for(d=n/2;d>=1;d/=2){                   //设定增量，但这样的增量并不科学
        for(q=0;q<d;q++){                   //理论上应该是两两互质的整数
            for(i=q+d;i<n;i+=d){            //如9,5,3,1或40,23,17,13,9,5,3,1
                for(j=q;j<i;j+=d){
                    if(a[i]<a[j]){
                        t=a[i];
                        for(k=i-d;k>=j;k-=d)a[k+d]=a[k];
                        a[j]=t;
                    }
                }
            }
        }
    }
}
void QuickSort_sub(int a[],int start,int end){
    int low=start,high=end;
    int key=a[start];
    while(low!=high){
        for(;low!=high&&key<=a[high];high--);
        a[low]=a[high];
        for(;low!=high&&key>=a[low];low++);
        a[high]=a[low];
    }
    a[low]=key;
    if(high-start>1)QuickSort_sub(a,start,high-1);
    if(end-low>1)QuickSort_sub(a,low+1,end);
}
void QuickSort(int a[],int length){
    QuickSort_sub(a,0,length-1);
}
void MergeSort_sub(int a[],int start,int end,int *p){
    int mid=(start+end)/2;
    int i,j,n=0;
    if(end-start>1){                       //对左右两边分别进行排序
        MergeSort_sub(a,start,mid,p);      //递归进行
        MergeSort_sub(a,mid+1,end,p);
    }
    for(i=start,j=mid+1;i<=mid&&j<=end;){  //将左右两边进行归并
        if(a[i]<a[j])*(p+n++)=a[i++];
        else *(p+n++)=a[j++];
    }
    while(i<=mid)*(p+n++)=a[i++];
    while(j<=end)*(p+n++)=a[j++];
    for(i=start,n=0;i<=end;i++,n++)a[i]=*(p+n);
}
void MergeSort(int a[],int length){
    int *p;
    p=(int*)malloc(sizeof(int)*length);
    MergeSort_sub(a,0,length-1,p);
    free(p);
}
void HeapSort_sub(int a[],int start,int length){
    int t,i;
    t=a[start];
    start++;                        //将[0,length)元素映射到[1,length+1)
    for(i=start*2;i<length+1;i*=2){ //否则0*2会出错
        if(i<length && a[i-1]<a[i])i++;
        if(t>=a[i-1])break;
        a[start-1]=a[i-1];
        start=i;
    }
    a[start-1]=t;
}
void HeapSort(int a[],int length){                  //堆排序
    int i,t;
    for(i=length/2-1;i>=0;i--)
        HeapSort_sub(a,i,length);
    for(i=length;i>0;i--){
        t=a[i-1];
        a[i-1]=a[0];
        a[0]=t;
        HeapSort_sub(a,0,i-1);
    }
}
int main(){
    // int a[]={1,5,3,6,10,55,9,2,87,12,34,75,33,47};
    // display(a,14);
    // HeapSort(a,14);
    // display(a,14);
    int *a;
    creatarr(&a,20,100);
    display(a,20);
    BinInsertSort(a,20);
    display(a,20);
    return 0;
}
