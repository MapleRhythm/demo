#include<iostream>
using namespace std;
template <typename T,int size>class seqlist
{
	T slist[size];   //���˳���������
	int Maxsize;   //������������ 
	int last;    //�Ѵ��������λ��
public:
	seqlist() { last=-1; Maxsize=size; }    //��ʼ��Ϊ�ձ�
	int Length() {return last+1;} //���������
	int Find(T & x) ;        // Ѱ��x�ڱ���λ�ã��±꣩
	bool IsIn(T & x);          //�ж�x�Ƿ��ڱ���
	bool Insert(T & x,int i);         //x���뵽�б��е�i��λ�ô����±꣩
	bool Remove(T & x);            //ɾ��x
	int Next(T & x);                      //Ѱ��x�ĺ��λ��
	int Prior(T & x);                     //Ѱ��x��ǰ��λ��
	bool IsEmpty(){return last==-1;}                    //�жϱ��Ƿ��
	bool IsFull()
	{return last==Maxsize -1;}          //�жϱ��Ƿ���
	T Get(int i) const;  //ȡ��i��Ԫ��ֵ֮,�˴���ע�⣬��Box��Ĺ��캯���Ĳ���δ��Ĭ�ϲ���ֵ����˺�����Ҫ��д
	T& operator[](int i);   //�����±������[]
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
	while(i<=last && slist[i]!=x) i++;  //˳������Ƿ���x 
	if (i>last) return -1; //δ�ҵ�������-1
	else return i; //�ҵ��������±�
}
template <typename T,int size> 
bool seqlist<T,size>::IsIn(T & x)
{
	int i=0;
	bool found=0;
	while(i<=last && !found) //����һ�ַ���������
	if (slist[i]!=x) i++;
	else found=1; //�ҵ�
	return found;
}
template <typename T,int size> 
T& seqlist<T,size>::operator[](int i)
{
	if(i>last+1||i<0||i>=Maxsize)
	{
		cout<<"�±���磡"<<endl;
		exit(1);
	}
	if(i>last) last++; //�±������[]��ֻ�����ӱ���Ԫ�أ����ܼ���
	return slist[i];
}

template <typename T,int size> 
bool seqlist<T,size>::Insert(T & x, int i)
{
	int j;
	if (i<0||i>last+1||last==Maxsize -1) 
		return false;
	  //����λ�ò����������ܲ��루�Ƚ��ԣ�
	else
	{
		last++;
		for(j=last;j>i;j--) slist[j]=slist[j-1];
	   //�ӱ����λ����ǰ���κ��ƣ��ճ�ָ��λ����
		slist[i]=x;
		return true;
	 }
}

template <typename T,int size>
bool seqlist<T,size>::Remove(T & x)
{
	int i=Find(x),j; //��ȥ��x���ĸ�λ��
    if(i>=0)
    {
		last--;
		for(j=i;j<=last;j++) 
			slist[j]=slist[j+1];
			 //����ǰ�ƣ���֤������
		return true;
    }
    return false; //���в�����x
}

template <typename T,int size> 
int seqlist<T,size>::Next(T & x)
{
	int i=Find(x);
	if(i>=0 && i<last) return i+1; //x���λ��
	else return -1; //x���ڱ��У����ڱ�ĩβ
}

template <typename T,int size> 
int seqlist<T,size>::Prior(T & x)
{
	int i=Find(x);
	if(i>0 && i<=last)  return i-1; //xǰ����λ��
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
    {             //�����n-1��
 		noswap=true;	              //δ������־Ϊ��
		for(j=last;j>i;j--)
        {          //��������ð��
			if(slist[j]>slist[j-1])//����
            {			
				temp=slist[j];
				slist[j]=slist[j-1];
				slist[j-1]=temp;
				noswap=false;
            }
        }
		if(noswap) break;  //�����޽���������ֹ�㷨��
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
	seqlist <Box,20> boxseq;   //˳�������boxseq��Ԫ��Ϊ����
	int i,j;
	const int n=4;
	Box k,a[n]={Box(1,8,2),Box(2,3,4),Box(6,2,4),Box(7,2,30)};
	for(j=0;j<n;j++) //������д��˳��� 
		if (!boxseq.Insert(a[j],j))
		{   
		  	cout<<"�������!"<<endl;
			break;
		}
  	//ʹ�ó�Ա����Get��Box���ع���<<��ӡ˳����е���ЧԪ��
	for (i=0;i<boxseq.Length( );i++) 
	{
		k=boxseq.Get(i);
		cout<< k ;  	
	}
	cout<<endl;	  
		  
	//��ʹ���±���������[] �� Box�����ع���<<��ӡ��˳����е���ЧԪ�� 
	for(i=0;i<n;i++) 
	{
		boxseq[i]=Box(0,0,0); //�����±����������
		cout<<boxseq[i];
	}  
	cout<<endl;
	
	for(i=0;i<n;i++) 
		boxseq[i]=a[i];  
	boxseq[n]=Box(19,20,21);   //�����ܷ�ʹ�����ع���[] ��˳���������Ԫ��
	for(i=0;i<n+1;i++) 
		cout<<boxseq[i];
	cout<<endl; 
	k=Box(22,23,24);//�˴�Ϊ������������󣬰�������������ݸ���k
	if (boxseq.IsIn(k)) cout<<"Ԫ����˳�����"<<endl;
	else cout <<"Ԫ��"<<k<<"����˳�����"<<endl;
 
	k=Box(2,3,4);
	if (boxseq.Remove (k)) cout<<"ɾ��Ԫ��"<<k<<endl; //ɾ������
	else cout<<"�Ҳ���Ԫ�أ��޷�ɾ��\n";


	for (i=0;i<boxseq.Length( );i++) 
	{
		k=boxseq.Get(i);
		cout<< k ; //��ӡԪ��ɾ����ʣ�µ�����
	}		  
	cout<<endl;
	
	if (boxseq.Insert(k,j-1))// ������װ��ȥ,�ɹ����ӡ
	{  
		for (i=0;i<boxseq.Length( );i++)  
		{
			k=boxseq.Get(i) ;
			cout<< k;
		}
		cout<<endl;  
	}
	k=boxseq.Get(boxseq.Next(k));
	cout<<"��ӡkԪ�ص�ֱ�Ӻ�̣�"<<k<<endl;
	   
	k=boxseq.Get(boxseq.Prior(k));
	cout<<"��ӡkԪ�ص�ֱ��ǰ����"<<k<<endl;

	cout<<"��Ԫ���ڱ��е�λ��Ϊ��"
		<<boxseq.Find(k)<<endl;
	if(boxseq.IsEmpty( ))  
		cout<<"���ǿյ�"<<endl;
	else cout<<"������"<<endl;
	if (boxseq.IsFull())  
		cout<<"��������"<<endl;
	else cout<<"��δ��"<<endl; 
	if (boxseq.IsIn(k))  
		cout<<"Ԫ���ڱ���"<<endl;

/*	boxseq.BubbleSort();
	cout<<"��volumeΪ���ؼ��ʣ��������к�\n";
	for (i=0;i<boxseq.Length( );i++)  
		cout<<boxseq[i]; //ע��˴���boxseqֻ��ģ����Ķ��󣬶����������ƣ�֮������ֱ���ں������[],����Ϊ[]�Ѿ����ع���
*/ 
	cout<<"\n\n";	
	return 0; 
}

                       
