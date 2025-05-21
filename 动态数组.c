#include"dynamicArray.h"

//����
struct Person
{
	char name[64];
	int age;
};

void myPrintPreson(void *data)
{
	struct Person* p = data;
	printf("����:%s  ����:%d\n",p->name,p->age);
}

int myComparePerson(void* data1, void* data2)
{
	struct Person* p1 = data1;
	struct Person* p2 = data2;
	return strcmp(p1->name, p2->name) == 0 && p1->age == p2->age;
}
int main()
{
	//��ʼ��
	struct dynamicArray * array = init_DynamicArray(5);
	//׼������
	struct Person p1 = { "��ɪ",18 };
	struct Person p2 = { "������",19 };
	struct Person p3 = { "��ɲ���",23 };
	struct Person p4 = { "��",12 };
	struct Person p5 = { "���о�",52 };
	struct Person p6 = { "���",23 };
	printf("��������ǰ������:%d   ��С:%d\n",array->m_capacity,array->m_size);
	//��������
	insert_DynamicArray(array, 0, &p1);
	insert_DynamicArray(array, 0, &p2);
	insert_DynamicArray(array, 1, &p3);
	insert_DynamicArray(array, 0, &p4);
	insert_DynamicArray(array, -1, &p5);
	insert_DynamicArray(array, 2, &p6);
	//��������
	foreach_DynamicArray(array, myPrintPreson);
	printf("�������ݺ�����:%d   ��С:%d\n", array->m_capacity, array->m_size);
	//����ɾ��(����λ��)
	removeByPos_DynamicArray(array, 2);
	printf("-------------------\n");
	foreach_DynamicArray(array, myPrintPreson);
	printf("ɾ�����ݺ�����:%d   ��С:%d\n", array->m_capacity, array->m_size);
	printf("-------------------\n");
	struct Person p = { "��ɪ",18 };
	removeByValue_DynamicArray(array, &p, myComparePerson);
	foreach_DynamicArray(array, myPrintPreson);
	printf("ɾ�����ݺ�����:%d   ��С:%d\n", array->m_capacity, array->m_size);
	destory_DynamicArray(array);
	array = NULL;
	return 0;
}