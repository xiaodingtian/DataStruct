#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//节点结构体
struct LinkNode
{
	//维护一个指针域
	struct LinkNode* next;
};
//链表结构体
struct LList
{
	struct LinkNode pHeader;
	int m_Size;
};
typedef void* LinkList;

LinkList init_LinkList()
{
	struct LList *myList= malloc(sizeof(struct LList));

	if (myList == NULL)
	{
		return NULL;
	}

	myList->pHeader.next = NULL;
	myList->m_Size = 0;

	return myList;
}

//插入
void insert_LinkList(LinkList list,int pos ,void * data)
{
	if (list == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}
	struct LList* mylist = list;
	if (pos<0 || pos>mylist->m_Size - 1)
	{
		//无效位置进行尾插
		pos = mylist->m_Size;
	}
	//用户数据前四个字节 由我们来使用
	struct LinkNode* myNode = data;

	//找插入节点的前驱节点
	struct LinkNode* pCurrent = &mylist->pHeader;
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}
	//pCurrent是前驱节点位置

	//更改指针指向
	myNode->next = pCurrent->next;
	pCurrent->next = myNode;
	//更新链表长度
	mylist->m_Size++;
}

//遍历
void foreach_LinkList(LinkList list,void(*myForeach)(void *))
{
	if (list == NULL)
	{
		return;
	}
	struct LList* myList = list;
	struct LinkNode* myNode = myList->pHeader.next;
	for (int i = 0; i < myList->m_Size; i++)
	{
		myForeach(myNode);
		myNode = myNode->next;
	}

}
//删除节点 按位置删除
void removeByPos_ListList(LinkList list, int pos)
{
	if (list == NULL)
	{
		return;
	}
	struct LList* myList = list;
	if (pos<0 || pos>myList->m_Size - 1)
	{ 
		return;
	}
	//找待删除节点的前驱位置
	struct LinkNode* pCurrent = &myList->pHeader;
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}
	//记录待删除的节点
	struct LinkNode* pDel = pCurrent->next;
	//更改指针指向
	pCurrent->next = pDel->next;
	//free(pDel)数据是用户开辟管理的，用户管理释放
	myList->m_Size--;
}
//删除节点 按值删除
void removeByValue_LinkList(LinkList list, void* data, int(*myCompare)(void*, void*))
{
	if (list == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}
	struct LList* myList = list;
	//创建两个辅助指针
	struct LinkNode* pPrev = &myList->pHeader;
	struct LinkNode* pCurrent = pPrev->next;
	for (int i = 0; i < myList->m_Size;i++)
	{
		//pCurrent.data data 将两个指针比较利用回调交给用户
		if (myCompare(pCurrent, data))
		{
			pPrev->next = pCurrent->next;
			myList->m_Size--;
			break;
		}
		//辅助指针后移
		pPrev = pCurrent;
		pCurrent = pCurrent->next;
	}
}

//销毁数组
void destory_LinkList(LinkList list)
{
	if (list == NULL)
	{
		return;
	}
	free(list);
	list = NULL;
}

//测试

struct Person
{
	void* node;
	char name[64];
	int age;
};

void myPrintPerson(void * data)
{
	struct Person* p = data;
	printf("姓名：%s    年龄：%d\n", p->name, p->age);
}

void myComparePerson(void* data1, void* data2)
{
	struct Person* p1 = data1;
	struct Person* p2 = data2;
	return strcmp(p1->name, p2->name) == 0 && p1->age == p2->age;
}

void test01()
{
	//初始化链表
	LinkList mylist = init_LinkList();
	//创建数据
	struct Person p1 = { NULL,"aaa",10 };
	struct Person p2 = { NULL,"bbb",20 };
	struct Person p3 = { NULL,"ccc",30 };
	struct Person p4 = { NULL,"ddd",40 };
	struct Person p5 = { NULL,"eee",50 };
	//插入节点
	insert_LinkList(mylist, 0, &p1);
	insert_LinkList(mylist, 0, &p2);
	insert_LinkList(mylist, 1, &p3);
	insert_LinkList(mylist, -1, &p4);
	insert_LinkList(mylist, 0, &p5);
	//遍历
	foreach_LinkList(mylist, myPrintPerson);
	//删除aaa
	removeByPos_ListList(mylist, 3);
	printf("------------------------\n");
	foreach_LinkList(mylist, myPrintPerson);
	struct Person p = { NULL,"ddd",40 };
	removeByValue_LinkList(mylist, &p, myComparePerson);
	printf("------------------------\n");
	foreach_LinkList(mylist, myPrintPerson);
	//销毁数组
	destory_LinkList(mylist);
	mylist = NULL;
}
int main()
{
	test01();
	return 0 ;
}