#include <stdio.h>
#include <stdlib.h>
#define N 100

typedef struct meminfo
{
	void *addr; //所分配的地址
	int  size;//实际分配内存的大小
	int  flag;//是否分配：分配 ：1 未分配： 0
	
}meminfo;

meminfo mems[N]; //全局变量存储所分配的变量
int	item = 0;//计数器
void* my_malloc(size_t size)
{
	void * p = malloc(size);
	if(p != NULL)
	{
		meminfo m1;
		m1.addr = p;
		m1.size = size;
		m1.flag = 1; //分配成功置一
		mems[item] = m1;
		item++;
	}
	return p;
}

void my_free(void *addr)
{
	if(addr != NULL)
	{
		int i;
		for(i = 0;i < item;i++)
		{
			if(mems[i].addr == addr)
			{
				free(addr);
				addr = NULL;
				mems[i].flag = 0; //释放成功置零
			}
		}
	}
}

void checkmem()
{
	int i;
	for(i = 0;i < item;i++)
	{
		if(mems[i].flag == 1) //未释放的
		{
			printf("%X\t%d\n",mems[i].addr,mems[i].size);
			my_free(mems[i].addr);//释放掉
		}
	}
}

int main(int argc, char const *argv[])
{
	int *p = (int*)my_malloc(40);
	int *q = (int*)my_malloc(20);
	char *ch = (char*)my_malloc(30);

	my_free(p);
	checkmem();
	return 0;
}
