#include "sort.h"
void creatarr(int **a,int n,int ran){
	int i;
    *a=(int*)malloc(sizeof(int)*n);
    srand(time(NULL));
    for(i=0;i<n;i++)(*a)[i]=rand()%ran;
}
void display(int a[],int n){
    int i;
    for(i=0;i<n;i++)printf("%2d ",a[i]);
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
        for(j=0;j<i;j++){
        	if(a[j]>a[i]){
                t=a[i];
                for(k=i-1;k>=j;k--)a[k+1]=a[k];
                a[j]=t;
            }
        }
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
void Search(int a[],int length,int target){           //折半查找
    int but=length-1,top=0;
    int mid;
    while(top<=but){
        mid=(top+but)/2;
        if(target==a[mid]){
            printf("%d",mid);
            break;
        }else if(target>a[mid])top=mid+1;
        else but=mid-1;
    }
    if(top>but)printf("The number is not in the list.");
}
int BinarySearch_sub(int a[],int start,int end,int target){    //递归法折半查找
    int mid=(start+end)/2;
    if(target==a[mid])return mid;
    else if(start==end)return -1;
    else if(target<a[mid])return BinarySearch_sub(a,start,mid-1,target);
    else if(target>a[mid])return BinarySearch_sub(a,mid+1,end,target);
}
int BinarySearch(int a[],int length,int target){
    return BinarySearch_sub(a,0,length-1,target);
}
