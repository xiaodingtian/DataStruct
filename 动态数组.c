#include"dynamicArray.h"

//测试
struct Person
{
	char name[64];
	int age;
};

void myPrintPreson(void *data)
{
	struct Person* p = data;
	printf("姓名:%s  年龄:%d\n",p->name,p->age);
}

int myComparePerson(void* data1, void* data2)
{
	struct Person* p1 = data1;
	struct Person* p2 = data2;
	return strcmp(p1->name, p2->name) == 0 && p1->age == p2->age;
}
int main()
{
	//初始化
	struct dynamicArray * array = init_DynamicArray(5);
	//准备数据
	struct Person p1 = { "亚瑟",18 };
	struct Person p2 = { "安琪拉",19 };
	struct Person p3 = { "马可波罗",23 };
	struct Person p4 = { "瑶",12 };
	struct Person p5 = { "云中君",52 };
	struct Person p6 = { "孙策",23 };
	printf("插入数据前：容量:%d   大小:%d\n",array->m_capacity,array->m_size);
	//插入数据
	insert_DynamicArray(array, 0, &p1);
	insert_DynamicArray(array, 0, &p2);
	insert_DynamicArray(array, 1, &p3);
	insert_DynamicArray(array, 0, &p4);
	insert_DynamicArray(array, -1, &p5);
	insert_DynamicArray(array, 2, &p6);
	//遍历数组
	foreach_DynamicArray(array, myPrintPreson);
	printf("插入数据后：容量:%d   大小:%d\n", array->m_capacity, array->m_size);
	//测试删除(按照位置)
	removeByPos_DynamicArray(array, 2);
	printf("-------------------\n");
	foreach_DynamicArray(array, myPrintPreson);
	printf("删除数据后：容量:%d   大小:%d\n", array->m_capacity, array->m_size);
	printf("-------------------\n");
	struct Person p = { "亚瑟",18 };
	removeByValue_DynamicArray(array, &p, myComparePerson);
	foreach_DynamicArray(array, myPrintPreson);
	printf("删除数据后：容量:%d   大小:%d\n", array->m_capacity, array->m_size);
	destory_DynamicArray(array);
	array = NULL;
	return 0;
}