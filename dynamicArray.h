#ifndef __DYNAMICARRAY_H__
#define __DYNAMICARRAY_H__
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//��̬����ṹ��
struct dynamicArray
{
	void** pAddr;		//ά����ʵ�ڶ�������������ָ��

	int m_capacity;		//��������

	int m_size;		//�����С
};


//��ʼ������
struct dynamicArray* init_DynamicArray(int capacity);

//��������
void insert_DynamicArray(struct dynamicArray* array, int pos, void* data);

//��������
void foreach_DynamicArray(struct dynamicArray* array, void(*myPrint)(void*));

//ɾ������ ��λ��ɾ��
void removeByPos_DynamicArray(struct dynamicArray* array, int pos);

//��ֵ��ɾ������
void removeByValue_DynamicArray(struct dynamicArray* array, void* data, int (*myCompare)(void*, void*));

//�ݻ�����
void destory_DynamicArray(struct dynamicArray* array);



#endif 


