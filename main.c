#include <stdio.h>
#define LISTSIZE 13
#define HASHSIZE 13
#define DELFLAG -1

typedef int dataType;
//顺序表
typedef struct{
    dataType items[LISTSIZE];
    int length;
} Sqlist;
//哈希表
typedef struct{
    int key;
} DataType;

typedef struct{
    DataType data;
    int times;
} HashTable[HASHSIZE];

//顺序表
void InitList(Sqlist *L);
int ListLength(Sqlist L);
int ListEmpty(Sqlist L);
int ListInsert(Sqlist *l, int pos, dataType item);
int TraverseList(Sqlist L);
//哈希表
void CreatHash(HashTable ht, DataType items[], int n);
int HashInsert(HashTable, DataType x);
int HashDelete(HashTable ht, DataType x);
void DisplayHash(HashTable ht);
int HashSearch(HashTable ht, DataType);
int HashFind(HashTable ht, int searchValue);

int HashFunc(int key) {
    return key % HASHSIZE;
}
//主函数
void main()
{
    int i, searchValue, aa;
    Sqlist Lq;
    InitList(&Lq);
    printf("-------哈希查找--------\n");
    printf("请输入要建立哈希表的关键字序列，以空格分开，以-1结束 \n");
    int input;
    for (i = 0; i < LISTSIZE; i++) {
        scanf("%d", &input);
        if(input == -1) {
             break;
        }
        ListInsert(&Lq, i, input);
    }
    printf("--------哈希查找--------\n");
    printf("1:哈希表操作\n");
    printf("0:退出\n");
    scanf("%d", &aa);
    //switch(aa)
    //{
      //  case 1:

        //case 0:
        //break;
         //return 0;
    //}

    
    
    TraverseList(Lq);
    HashTable ht;
    CreatHash(ht, Lq.items, Lq.length);
    DisplayHash(ht);
    // int searchValue;
    // scanf("%d", &searchValue);
    // findValueInHashTable(ht, searchValue);
    printf("请输入查找元素 :\n");
    scanf("%d", &searchValue);
    HashFind(ht, searchValue);



    return ;
}


void InitList(Sqlist *L)
{
    L->length=0;
    // L->items = [LISTSIZE]{};
}
int ListLength(Sqlist L)
{
    return L.length;
}
int ListEmpty(Sqlist L)
{
    if (L.length <= 0)
    return 1;
    else
    return 0;
}
int ListInsert(Sqlist *L, int pos, dataType item)
{
    int i;
    if (L->length>= LISTSIZE)
    {
        printf("顺序表已满，无法进行插入操作。");
        return 0;
    }

    if (pos < 0 || pos > L->length+1)
    {
        printf("插入位置不合法。");
        return 0;
    }
    L->items[L->length] = item;
    L->length++;
}
int TraverseList (Sqlist L)
{
    int i;
    for (i = 0; i<L.length;i++)
    printf("%d \t", L.items[i]);
    printf("\n");
    return 0;
}

int HashCollison(int current) {
    return (current + 1) % HASHSIZE;
}

//哈希表
int HashSearch(HashTable ht, DataType x)
{//找到则返回哈希地址， 没找到就返回负的哈希地址
    int addr;
    addr = HashFunc(x.key);
    while(ht[addr].data.key != NULL && ht[addr].data.key != x.key){
        /* code */
        printf("[%d]冲突地址为: %d \n", x.key, addr);
        addr = HashCollison(addr);
    }
    if (ht[addr].data.key == x.key) {
        return addr;
    } else {
        return -addr;
    }   
}

int HashFind(HashTable ht, int searchValue) {
    DataType t = { key: searchValue };
    int addr = HashSearch(ht, t);
    if (addr >= 0) {
        printf("查找到的地址为 :%d\n", addr);
    }
    else
    {
        printf("未找到\n"); 
    }
    
    return -1;
}

void CreatHash(HashTable ht, DataType items[], int n) {
    int i;
    for (i = 0; i < HASHSIZE; i++)
    {
        ht[i].data.key = NULL;
        ht[i].times=0;
    }
    for (i = 0; i <n; i++)
    {
        HashInsert(ht, items[i]);
    }
}
int HashInsert(HashTable ht, DataType x)
{
    int addr;
    addr = HashSearch(ht, x);
    if (addr > 0) {
        return 0;
    }
    ht[-addr].data = x;
    ht[-addr].times = 1;
    return 1;
}
void DisplayHash(HashTable ht)
{
    int i;
    printf("\n哈希表\n哈希地址:\t");
    for (i = 0; i < HASHSIZE; i++)
    {
        if (ht[i].data.key != NULL)
        {
            printf("%d\t", ht[i].data.key);
        }
        else
        {
            printf("\t");
        }
        printf("\n");
        
    }
    printf("关键字:\t");
    for (i = 0 ; i <= HASHSIZE; i++)
    printf("%d \t", i);//关键字的打印
    if (i = HASHSIZE)
    {
        printf("\n");
    }


}
int HashDelete(HashTable ht, DataType x)
{
    int addr;
    addr = HashSearch(ht, x);
    if (addr>0)
    {
        ht[addr].data.key = DELFLAG;
        return 1;
    }
    return 0;
}

