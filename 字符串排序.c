#include <stdio.h>
#include <string.h>
void display(char *p[],int n);
//打印字符串数组
void StrSelectSort(char *p[],int n);
//字符串选择排序
void StrBubbleSort(char *p[],int n);
//字符串冒泡排序
void StrInsertSort(char *p[],int n);
//字符串插入排序
void StrShellSort(char *p[],int n);
//字符串希尔排序
void StrSort(char *p[],int n);
//自己瞎捣鼓的字符串排序
void StrQuickSort_sub(char *p[],int start,int end);
//字符串快速排序的子过程
void StrQuickSort(char *p[],int length);
//字符串快速排序，封装了快速排序具体实现的子过程，只需要提供长度即可
void StrMergeSort_sub(char *a[],int start,int end,int *p[]);
//字符串归并排序的子过程
void StrMergeSort(char *p[],int length);
//字符串归并排序，封装了归并排序具体实现的子过程，为其申请辅助空间p，调用子过程后释放，只需要提供长度即可
void StrHeapSort_sub(char *p[],int start,int length);
//堆排序的子过程，假设[start,length)中除start外均满足堆的定义，调整start的位置使成为一个堆
void StrHeapSort(char *p[],int length);
//堆排序，先建立初始堆，再循环处理，将堆顶元素移到末尾，对其余元素调整成为新堆
void StrSearch(char *p[],int length,char *target);
//字符串折半查找排序(迭代法)
int StrSearch2_sub(char *p[],int start,int end,char *target);
//字符串折半查找排序(递归法)的子过程
int StrSearch2(char *p[],int length,char *target);
//字符串折半查找排序(递归法)

void display(char *p[],int n){
	int i;
	for(i=0;i<n;i++)printf("%s ",*(p+i));
	printf("\n");
}
void StrSelectSort(char *p[],int n){
	int i,j,k;
	char *t;
	for(i=0;i<n-1;i++){
		k=i;
		for(j=i+1;j<n;j++){
			if(strcmp(*(p+k),*(p+j))>0)k=j;
		}
		if(k!=j){
			t=*(p+k);
			*(p+k)=*(p+i);
			*(p+i)=t;
		}
	}
}
void StrBubbleSort(char *p[],int n){
	int i,j;
	char *t;
	for(i=n;i>0;i--){
		for(j=0;j<i-1;j++){
			if(strcmp(*(p+j),*(p+j+1))>0){
                t=*(p+j);
                *(p+j)=*(p+j+1);
                *(p+j+1)=t;
            }
        }
    }
}
void StrInsertSort(char *p[],int n){
	int i,j,k;
	char *t;
	for(i=1;i<n;i++){
        for(j=0;j<i;j++){
            if(strcmp(*(p+i),*(p+j))<0){
                t=*(p+i);
                for(k=i-1;k>=j;k--)*(p+k+1)=*(p+k);
                *(p+j)=t;
            }
        }
    }
}
void StrShellSort(char *p[],int n){
	int i,j,d,q,k;
	char *t;
    for(d=n/2;d>=1;d/=2){                           //设定增量，但这样的增量并不科学
        for(q=0;q<d;q++){                           //理论上应该是两两互质的整数
            for(i=q+d;i<n;i+=d){                    //如9,5,3,1或40,23,17,13,9,5,3,1
                for(j=q;j<i;j+=d){
                	if(strcmp(*(p+i),*(p+j))<0){
                		t=*(p+i);
                        for(k=i-d;k>=j;k-=d)*(p+k+d)=*(p+k);
                        *(p+j)=t;
                	}
                }
            }
        }
    }
}
void StrSort(char *p[],int n){
	int i,j,k;
	char *t;
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(strcmp(*(p+i),*(p+j))>0){
                t=*(p+j);
                *(p+j)=*(p+i);
                *(p+i)=t;
            }
        }
    }
}
void StrQuickSort_sub(char *p[],int start,int end){
    int i=start,j=end;
    char *key=*(p+start);
    while(i!=j){
        while(i!=j&&strcmp(key,*(p+j))<=0)j--;
        *(p+i)=*(p+j);
        while(i!=j&&strcmp(key,*(p+i))>=0)i++;
        *(p+j)=*(p+i);
    }
    *(p+i)=key;
    if(j-start>1)StrQuickSort_sub(p,start,j-1);
    if(end-i>1)StrQuickSort_sub(p,i+1,end);
}
void StrQuickSort(char *p[],int length){
    StrQuickSort_sub(p,0,length-1);
}
void StrMergeSort_sub(char *a[],int start,int end,int *p[]){
    int mid=(start+end)/2;
    int i,j,n=0;
    if(end-start>1){
        StrMergeSort_sub(a,start,mid,p);
        StrMergeSort_sub(a,mid+1,end,p);
    }
    for(i=start,j=mid+1;i<=mid&&j<=end;){
        if(strcmp(*(a+i),*(a+j))<0)*(p+n++)=*(a+i++);
        else *(p+n++)=*(a+j++);
    }
    if(i<=mid){
        while(i<=mid)*(p+n++)=*(a+i++);
    }
    if(j<=end){
        while(j<=end)*(p+n++)=*(a+j++);
    }
    for(i=start,n=0;i<=end;i++,n++)*(a+i)=*(p+n);
}
void StrMergeSort(char *p[],int length){
    char **temp;
    temp=(char**)malloc(sizeof(char*)*length);
    StrMergeSort_sub(p,0,length-1,temp);
    free(temp);
}
void StrHeapSort_sub(char *p[],int start,int length){
    char *temp;
    int i;
    temp=p[start];
    start++;
    for(i=start*2;i<length+1;i*=2){
        if(i<length && strcmp(p[i-1],p[i])<0)i++;
        if(strcmp(temp,p[i-1]) >= 0)break;
        p[start-1]=p[i-1];
        start=i;
    }
    p[start-1]=temp;
}
void StrHeapSort(char *p[],int length){
    int i;
    char *temp;
    for(i=length/2-1;i>=0;i--)
        HeapSort_sub(p,i,length);
    for(i=1;i<length;i++){
        temp=p[length-i];
        p[length-i]=p[0];
        p[0]=temp;
        HeapSort_sub(p,0,length-i);
    }
}
void StrSearch(char *p[],int length,char *target){        //字符串折半查找
    int but=length-1,top=0;
    int mid;
    void Bubble(char *p[],int n);
    StrBubbleSort(p,length);
    while(top<=but){
        mid=(top+but)/2;
        if(strcmp(target,*(p+mid))==0){
            printf("%d",mid);
            break;
        }else if(strcmp(target,*(p+mid))>0)top=mid+1;
        else but=mid-1;
    }
    if(top>but)printf("The string is not in the list.");
}
int StrSearch2_sub(char *p[],int start,int end,char *target){    //递归法折半查找
    int mid=(start+end)/2;
    if(strcmp(target,*(p+mid))==0)return mid;
    else if(start==end)return -1;
    else if(strcmp(target,*(p+mid))<0)return StrSearch2_sub(p,start,mid-1,target);
    else if(strcmp(target,*(p+mid))>0)return StrSearch2_sub(p,mid+1,end,target);
}
int StrSearch2(char *p[],int length,char *target){
    return StrSearch2_sub(p,0,length-1,target);
}
int main(){
    char *p[]={"super","hello","chinese","american","austrilia","banana","couple","digital","long","beautiful"};
    int i;
    display(p,10);
    HeapSort(p,10);
    display(p,10);
    i=StrSearch2_sub(p,0,9,"super");
    printf("%d\n",i);
	return 0;
}
