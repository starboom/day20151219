#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAXSIZE 30
#define HashVar 11
#define PhoneLen 11
#define NumofPhone 13
typedef enum{False,True} BOOL;
typedef enum{NULLKEY,HAVEKEY,DELKEY} HAVEORNOT;

typedef struct HashTable
{
	int elem[MAXSIZE];
	HAVEORNOT elemflag[MAXSIZE];
	int count;
}HashTable;

typedef struct 
{
	int keynum;
}Record;
int PickPhonenum1(char const * _phone);
int PickPhonenum2(char const * _phone);
int PickPhonenum3(char const * _phone);
void InitialHash(HashTable *H)
{
	int i;
	(*H).count = 0;
	for(i = 0;i < MAXSIZE;i++)
	{
		(*H).elemflag[i] = NULLKEY;
	}
}
BOOL SearchHash(HashTable H,int k,int *p)
{
	int p1;
	(*p) = Hash(k);
	p1 = (*p);
	while(H.elemflag[(*p)] == HAVEKEY && k != H.elem[(*p)])
	{
		(*p)++;
		if((*p) >= MAXSIZE)
			(*p) = (*p) % MAXSIZE;
		if((*p) == p1)
			return False;
	}
	if(k == H.elem[(*p)] && H.elemflag[(*p)] == HAVEKEY)
		return True;
	else
		return False;
	
}
BOOL InsertHash(HashTable *H,Record e)
{
	int p;//存放hash地址
	if(SearchHash((*H),e.keynum,&p))
		return False;
	else
	{
		(*H).elemflag[p] = HAVEKEY;
		(*H).elem[p] = e.keynum;
		(*H).count++;
		return True;
	}
}
void CreatHash(HashTable * H,long int _phone) //18390934608
{
	Record e;
	e.keynum = _phone; 
	InsertHash(H,e);
}

void PrintHash(HashTable H)
{
	int i;
	printf("元素标号\t哈希值\n");
	for(i=0;i < MAXSIZE;i++)	
		if(H.elemflag[i] == HAVEKEY)
		{
			printf("%-4d\t\t",i );
			printf("%-4d\n",H.elem[i]);
		}
	// printf("\ncount: %d\n",H.count);
}

BOOL DeleteHash(HashTable *H,Record e)
{
	int p;
	if(!(SearchHash((*H),e.keynum,&p)))
		return False;
	else
	{
		(*H).elemflag[p] = DELKEY;
		(*H).count--;
		return True;
	}
}

int Hash(int kn)
{
	return (kn % HashVar);
}

int main(int argc, char const *argv[])
{


/********取手机号码前三个字段*****************/
/*
	int fd;
	int i;
	int PhoneNum[NumofPhone];
	fd = open("phone.txt", O_CREAT | O_EXCL | O_RDWR,0777);
	if(fd == -1)
	{
		fd = open("phone.txt",O_RDWR,0777);
		// perror("open file :");
	}

	char buf[PhoneLen];
	int TxtLen;
	read(fd,buf,PhoneLen - 8);
	PhoneNum[0] = atoll(buf);
	// printf("%d\n",PhoneNum );
	for(i = 1;i < NumofPhone ;i++)
	{
		TxtLen = lseek(fd,PhoneLen - 3,SEEK_CUR);
		// printf("TxtLen = %d\n",TxtLen);
		read(fd,buf,PhoneLen - 6);
		PhoneNum[i] = atoll(buf);
		// printf("%d\n",PhoneNum );
		memset(buf,sizeof(buf),0);
		// TxtLen = lseek(fd,PhoneLen - 3,SEEK_CUR);
	}	
	for(i = 0;i < NumofPhone;i++)
	{
		printf("%d\n",PhoneNum[i] );
	}*/
/***********************************************/
	char *PhoneNum = "18390934608";
	HashTable _H1;
	HashTable _H2;
	HashTable _H3;
	HashTable _H4;
	int PhoneFlag1;
	int PhoneFlag2;
	int PhoneFlag3;
	int PhoneFlag;
	
	int SerachPos;
	int PhoneNum1 =  PickPhonenum1(PhoneNum);
	int PhoneNum2 =  PickPhonenum2(PhoneNum);
	int PhoneNum3 =  PickPhonenum3(PhoneNum);

	InitialHash(&_H1);
	CreatHash(&_H1,PhoneNum1);
	PhoneFlag1 = Hash(PhoneNum1);

	InitialHash(&_H2);
	CreatHash(&_H2,PhoneNum2);

	PhoneFlag2 = Hash(PhoneNum2);

	InitialHash(&_H3);
	CreatHash(&_H3,PhoneNum3);

	PhoneFlag3 = Hash(PhoneNum3);

	PhoneFlag = PhoneFlag1 * 100 + PhoneFlag2 * 10 + PhoneFlag3;


	InitialHash(&_H4);
	CreatHash(&_H4,PhoneFlag);
	PrintHash(_H4);

// BOOL SearchHash(HashTable H,int k,int *)

	if(SearchHash(_H4,PhoneFlag,&SerachPos))
		printf("This phonenum is exist!\n");
	else
		printf("This phonenum is not exist!\n");
	return 0;
}

int PickPhonenum1(char const * _phone)
{

	int i;
	char phone_1[3] = {'0'};
	for(i = 0;i < 3;i++)
	{
		phone_1[i] = *_phone;
		_phone++;
	}
	return atoi(phone_1);
}
int PickPhonenum2(char const * _phone)
{

	int i;
	char phone_1[4] = {'0'};
	for(i = 0;i < 4;i++)
	{
		phone_1[i] = *(_phone + i + 3);
		// printf("*_phone + 3 = %c\n",*(_phone + i + 3));
		// _phone++;
	}
	return atoi(phone_1);
}

int PickPhonenum3(char const * _phone)
{

	int i;
	char phone_1[4] = {'0'};
	for(i = 0;i < 4;i++)
	{
		phone_1[i] = *(_phone + i + 7);
		// printf("*_phone + 3 = %c\n",*(_phone + i + 7));
	
	}
	return atoi(phone_1);
}