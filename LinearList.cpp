#include<iostream>
#include<cstdlib>
#define MAX_SIZE 10
#define INIT_SIZE 10
#define ERR_NUM 99999

/*	“线性表”之“顺序表”
	Sequence List
	- Static
	- Dynamic

	打字人：SDDR
	完成日期：2021-03-22 20:25
	备注：	该代码是本人看过“王道”对应课程后的自主检测。
			如有雷同，那就雷同吧哈哈哈，反正在我脑子里了6.6
			王道yyds~	*/

typedef int ELEM_TYPE;

typedef struct {
	ELEM_TYPE data[MAX_SIZE];
	int length;
}SqListSta;

typedef struct {
	ELEM_TYPE* data;
	int length;
	int max_size;
}SqListDyn;

void InitListDyn(SqListDyn& L);
void IncreaseSizeDyn(SqListDyn& L, int len);
void DestroyListDyn(SqListDyn& L);
bool InsertListDyn(SqListDyn& L, int i, ELEM_TYPE e);
bool DeleteListDyn(SqListDyn& L, int i, ELEM_TYPE& e);
ELEM_TYPE GetElemDyn(SqListDyn L, int i);		//按位查找，返回数据元素
int LocateElemDyn(SqListDyn L, ELEM_TYPE e);	//按值查找，返回位序
int GetLengthDyn(SqListDyn L);
bool IsEmptyDyn(SqListDyn L);
bool IsFull(SqListDyn L);
void PrintListDyn(SqListDyn L);

/*static*/
void InitListSta(SqListSta& L) {
	L.length = 0;
	/*Being limited by L.length, codes followd could be hidden.*/
	for (int i = 0; i < MAX_SIZE; i++) {
		L.data[i] = 0;
	}
}

/*dynamic*/
void InitListDyn(SqListDyn& L) {
	L.length = 0;
	L.max_size = INIT_SIZE;
	L.data = (int*)malloc(sizeof(int) * L.max_size);

	/*another way
	L.data=new int[INIT_SIZE];
	*/
}

/// <summary>
/// 顺序表动态分配扩容
/// </summary>
/// <param name="L"></param>
/// <param name="len"></param>
void IncreaseSizeDyn(SqListDyn& L, int len) {
	int* p = L.data;
	L.data = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * (L.max_size + len));
	for (int i = 0; i < L.length; i++) {	//将数据复制到新的区域
		L.data[i] = p[i];
	}
	L.max_size += len;		//顺序表最大长度增加len
	free(p);
}
void DestroyListDyn(SqListDyn& L) {
	L.length = 0;
	L.max_size = 0;
	free(L.data);
	L.data = 0;
}

bool InsertListDyn(SqListDyn& L, int i, ELEM_TYPE e) {
	/*i在范围内*/
	if (i<1 || i>L.length + 1) {
		return false;
	}
	/*满*/
	if (L.length >= L.max_size) {
		return false;
	}
	for (int j = L.length; j > i - 1; j--) {
		L.data[j] = L.data[j - 1];
	}
	L.data[i - 1] = e;
	L.length += 1;
	return true;
}

bool DeleteListDyn(SqListDyn& L, int i, ELEM_TYPE& e) {
	if (i<1 || i>L.length) {
		return false;
	}
	e = L.data[i - 1];
	for (int j = i - 1; j < L.length - 1; j++) {
		L.data[j] = L.data[j + 1];
	}
	L.length -= 1;
	return true;
}

ELEM_TYPE GetElemDyn(SqListDyn L, int i) {
	if (i >= 1 && i <= L.length) {
		return L.data[i - 1];
	}
	return -ERR_NUM;
}

int LocateElemDyn(SqListDyn L, ELEM_TYPE e) {
	for (int i = 0; i < L.length; i++) {
		if (L.data[i] == e) {
			/*线性表位序从1开始，数组下标从0开始*/
			return i + 1;
		}
	}
	return 0;
}

int GetLengthDyn(SqListDyn L) {
	return L.length;
}

bool IsEmptyDyn(SqListDyn L) {
	if (L.length <= 0) return true;
	return false;
}

bool IsFull(SqListDyn L) {
	if (L.length >= L.max_size) return true;
	return false;
}

void PrintListDyn(SqListDyn L) {
	/* 注意<L.length，而非L.max_size */
	for (int i = 0; i < L.length; i++) {
		printf("%d ", L.data[i]);
	}
}

int main() {
	SqListDyn L;
	ELEM_TYPE e;
	InitListDyn(L);
	InsertListDyn(L, 1, 88);
	InsertListDyn(L, 1, 1);
	InsertListDyn(L, 3, 2);
	InsertListDyn(L, 4, 3);
	PrintListDyn(L);
	DeleteListDyn(L, 1, e);
	printf("\ne=%d\n", e);
	PrintListDyn(L);
	printf("\nlength=%d", GetLengthDyn(L));
	printf("\nGetElem=%d\n", GetElemDyn(L, 88));
	IncreaseSizeDyn(L, 5);
	DestroyListDyn(L);
	PrintListDyn(L);
	return 0;
}