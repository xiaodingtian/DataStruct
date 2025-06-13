#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//�ڵ�ṹ��
struct LinkNode
{
	//ά��һ��ָ����
	struct LinkNode* next;
};
//����ṹ��
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

//����
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
		//��Чλ�ý���β��
		pos = mylist->m_Size;
	}
	//�û�����ǰ�ĸ��ֽ� ��������ʹ��
	struct LinkNode* myNode = data;

	//�Ҳ���ڵ��ǰ���ڵ�
	struct LinkNode* pCurrent = &mylist->pHeader;
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}
	//pCurrent��ǰ���ڵ�λ��

	//����ָ��ָ��
	myNode->next = pCurrent->next;
	pCurrent->next = myNode;
	//����������
	mylist->m_Size++;
}

//����
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
//ɾ���ڵ� ��λ��ɾ��
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
	//�Ҵ�ɾ���ڵ��ǰ��λ��
	struct LinkNode* pCurrent = &myList->pHeader;
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}
	//��¼��ɾ���Ľڵ�
	struct LinkNode* pDel = pCurrent->next;
	//����ָ��ָ��
	pCurrent->next = pDel->next;
	//free(pDel)�������û����ٹ���ģ��û������ͷ�
	myList->m_Size--;
}
//ɾ���ڵ� ��ֵɾ��
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
	//������������ָ��
	struct LinkNode* pPrev = &myList->pHeader;
	struct LinkNode* pCurrent = pPrev->next;
	for (int i = 0; i < myList->m_Size;i++)
	{
		//pCurrent.data data ������ָ��Ƚ����ûص������û�
		if (myCompare(pCurrent, data))
		{
			pPrev->next = pCurrent->next;
			myList->m_Size--;
			break;
		}
		//����ָ�����
		pPrev = pCurrent;
		pCurrent = pCurrent->next;
	}
}

//��������
void destory_LinkList(LinkList list)
{
	if (list == NULL)
	{
		return;
	}
	free(list);
	list = NULL;
}

//����

struct Person
{
	void* node;
	char name[64];
	int age;
};

void myPrintPerson(void * data)
{
	struct Person* p = data;
	printf("������%s    ���䣺%d\n", p->name, p->age);
}

void myComparePerson(void* data1, void* data2)
{
	struct Person* p1 = data1;
	struct Person* p2 = data2;
	return strcmp(p1->name, p2->name) == 0 && p1->age == p2->age;
}

void test01()
{
	//��ʼ������
	LinkList mylist = init_LinkList();
	//��������
	struct Person p1 = { NULL,"aaa",10 };
	struct Person p2 = { NULL,"bbb",20 };
	struct Person p3 = { NULL,"ccc",30 };
	struct Person p4 = { NULL,"ddd",40 };
	struct Person p5 = { NULL,"eee",50 };
	//����ڵ�
	insert_LinkList(mylist, 0, &p1);
	insert_LinkList(mylist, 0, &p2);
	insert_LinkList(mylist, 1, &p3);
	insert_LinkList(mylist, -1, &p4);
	insert_LinkList(mylist, 0, &p5);
	//����
	foreach_LinkList(mylist, myPrintPerson);
	//ɾ��aaa
	removeByPos_ListList(mylist, 3);
	printf("------------------------\n");
	foreach_LinkList(mylist, myPrintPerson);
	struct Person p = { NULL,"ddd",40 };
	removeByValue_LinkList(mylist, &p, myComparePerson);
	printf("------------------------\n");
	foreach_LinkList(mylist, myPrintPerson);
	//��������
	destory_LinkList(mylist);
	mylist = NULL;
}
int main()
{
	test01();
	return 0 ;
}