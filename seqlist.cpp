#include<iostream>
using namespace std;
template <typename T,int size>class seqlist
{
	T slist[size];   //存放顺序表的数组
	int Maxsize;   //最大可容纳项数 
	int last;    //已存表项的最后位置
public:
	seqlist() { last=-1; Maxsize=size; }    //初始化为空表
	int Length() {return last+1;} //计算表长度
	int Find(T & x) ;        // 寻找x在表中位置（下标）
	bool IsIn(T & x);          //判断x是否在表中
	bool Insert(T & x,int i);         //x插入到列表中第i个位置处（下标）
	bool Remove(T & x);            //删除x
	int Next(T & x);                      //寻找x的后继位置
	int Prior(T & x);                     //寻找x的前驱位置
	bool IsEmpty(){return last==-1;}                    //判断表是否空
	bool IsFull()
	{return last==Maxsize -1;}          //判断表是否满
	T Get(int i) const;  //取第i个元素之值,此处需注意，若Box类的构造函数的参数未带默认参数值，则此函数需要改写
	T& operator[](int i);   //重载下标运算符[]
//	void BubbleSort();

};
class Box
{
private:
	int a;
	int b;
	int c;
public:
	Box(int =1,int =1,int=1);
	int volume(); 
    bool operator!=(Box &);
	bool operator>(Box &);
    friend ostream & operator << (ostream &sink, Box &m)
	{
		sink<<m.a <<'\t'<<m.b <<'\t'
			<<m.c<<'\t'<<"volume:\t"
			<<m.volume()<<endl;
		return sink;
	}
};

template <typename T,int size> 
int seqlist<T,size>::Find(T & x) 
{
	int i=0;
	while(i<=last && slist[i]!=x) i++;  //顺序查找是否有x 
	if (i>last) return -1; //未找到，返回-1
	else return i; //找到，返回下标
}
template <typename T,int size> 
bool seqlist<T,size>::IsIn(T & x)
{
	int i=0;
	bool found=0;
	while(i<=last && !found) //换了一种方法来查找
	if (slist[i]!=x) i++;
	else found=1; //找到
	return found;
}
template <typename T,int size> 
T& seqlist<T,size>::operator[](int i)
{
	if(i>last+1||i<0||i>=Maxsize)
	{
		cout<<"下标出界！"<<endl;
		exit(1);
	}
	if(i>last) last++; //下标运算符[]，只能增加表的元素，不能减少
	return slist[i];
}

template <typename T,int size> 
bool seqlist<T,size>::Insert(T & x, int i)
{
	int j;
	if (i<0||i>last+1||last==Maxsize -1) 
		return false;
	  //插入位置不合理，不能插入（稳健性）
	else
	{
		last++;
		for(j=last;j>i;j--) slist[j]=slist[j-1];
	   //从表最后位置向前依次后移，空出指定位置来
		slist[i]=x;
		return true;
	 }
}

template <typename T,int size>
bool seqlist<T,size>::Remove(T & x)
{
	int i=Find(x),j; //先去找x在哪个位置
    if(i>=0)
    {
		last--;
		for(j=i;j<=last;j++) 
			slist[j]=slist[j+1];
			 //依次前移，保证表连续
		return true;
    }
    return false; //表中不存在x
}

template <typename T,int size> 
int seqlist<T,size>::Next(T & x)
{
	int i=Find(x);
	if(i>=0 && i<last) return i+1; //x后继位置
	else return -1; //x不在表中，或在表末尾
}

template <typename T,int size> 
int seqlist<T,size>::Prior(T & x)
{
	int i=Find(x);
	if(i>0 && i<=last)  return i-1; //x前驱的位置
	else return -1; 
}
template <typename T,int size>
T seqlist<T,size>::Get(int i) const 
{
	if(i<0||i>last) exit(1);
	return slist[i];
} 
/*template <typename T,int size> 
void seqlist<T,size>::BubbleSort()
{
    bool noswap;
    int i,j;
    T temp;
    for (i=0;i<last;i++)
    {             //最多做n-1趟
 		noswap=true;	              //未交换标志为真
		for(j=last;j>i;j--)
        {          //从下往上冒泡
			if(slist[j]>slist[j-1])//降序
            {			
				temp=slist[j];
				slist[j]=slist[j-1];
				slist[j-1]=temp;
				noswap=false;
            }
        }
		if(noswap) break;  //本趟无交换，则终止算法。
	}
}
*/ 

Box::Box(int x, int y,int z):a(x),b(y),c(z){}
bool Box::operator!=(Box &m)
{	
   return a!=m.a||b!=m.b||c!=m.c;
}
bool Box:: operator>(Box & Boxobj)
{
	return a*b*c>Boxobj.a*Boxobj.b*Boxobj.c;
}
int Box::volume()
{	return a*b*c;	}

int main()
{
	seqlist <Box,20> boxseq;   //顺序表对象boxseq的元素为整型
	int i,j;
	const int n=4;
	Box k,a[n]={Box(1,8,2),Box(2,3,4),Box(6,2,4),Box(7,2,30)};
	for(j=0;j<n;j++) //把数组写入顺序表 
		if (!boxseq.Insert(a[j],j))
		{   
		  	cout<<"插入出错!"<<endl;
			break;
		}
  	//使用成员函数Get和Box重载过的<<打印顺序表中的有效元素
	for (i=0;i<boxseq.Length( );i++) 
	{
		k=boxseq.Get(i);
		cout<< k ;  	
	}
	cout<<endl;	  
		  
	//打使用下标访问运算符[] 和 Box中重载过的<<打印出顺序表中的有效元素 
	for(i=0;i<n;i++) 
	{
		boxseq[i]=Box(0,0,0); //采用下标运算符运算
		cout<<boxseq[i];
	}  
	cout<<endl;
	
	for(i=0;i<n;i++) 
		boxseq[i]=a[i];  
	boxseq[n]=Box(19,20,21);   //尝试能否使用重载过的[] 在顺序表中增加元素
	for(i=0;i<n+1;i++) 
		cout<<boxseq[i];
	cout<<endl; 
	k=Box(22,23,24);//此处为构造无名对象后，把无名对象的内容赋给k
	if (boxseq.IsIn(k)) cout<<"元素在顺序表中"<<endl;
	else cout <<"元素"<<k<<"不在顺序表中"<<endl;
 
	k=Box(2,3,4);
	if (boxseq.Remove (k)) cout<<"删除元素"<<k<<endl; //删除数组
	else cout<<"找不到元素，无法删除\n";


	for (i=0;i<boxseq.Length( );i++) 
	{
		k=boxseq.Get(i);
		cout<< k ; //打印元素删除后剩下的数组
	}		  
	cout<<endl;
	
	if (boxseq.Insert(k,j-1))// 把数组装回去,成功则打印
	{  
		for (i=0;i<boxseq.Length( );i++)  
		{
			k=boxseq.Get(i) ;
			cout<< k;
		}
		cout<<endl;  
	}
	k=boxseq.Get(boxseq.Next(k));
	cout<<"打印k元素的直接后继："<<k<<endl;
	   
	k=boxseq.Get(boxseq.Prior(k));
	cout<<"打印k元素的直接前驱："<<k<<endl;

	cout<<"该元素在表中的位置为："
		<<boxseq.Find(k)<<endl;
	if(boxseq.IsEmpty( ))  
		cout<<"表是空的"<<endl;
	else cout<<"表不空"<<endl;
	if (boxseq.IsFull())  
		cout<<"表是满的"<<endl;
	else cout<<"表未满"<<endl; 
	if (boxseq.IsIn(k))  
		cout<<"元素在表中"<<endl;

/*	boxseq.BubbleSort();
	cout<<"以volume为主关键词，降序排列后：\n";
	for (i=0;i<boxseq.Length( );i++)  
		cout<<boxseq[i]; //注意此处，boxseq只是模板类的对象，而非数组名称，之所以能直接在后面跟上[],是因为[]已经重载过。
*/ 
	cout<<"\n\n";	
	return 0; 
}

                       
