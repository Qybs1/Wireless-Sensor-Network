// SlistType.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


typedef int SlistData;//设置链表的数据模式
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 

//自定义链表
typedef struct SlistNode
{
    SlistData data;//节点的值
    struct SlistNode* next;//下一个节点的地址,为啥要在之前加struct，因为c语言认为typedef 还没结束，故不能在定义时使用
}SlistNode;


//初始化链表：申请一个新节点,需要输入节点值，返回这个新节点的指针
SlistNode* BuynewNode(SlistData x) {
  //步骤，先给这个节点分配内存（在堆区），在赋值并返回指针即可
    SlistNode* t = NULL;
    t = (SlistNode*)malloc(1*sizeof(SlistData));
    if (t == NULL) {
        exit(-1);
    }
    t->data = x;
    t->next = NULL;//记得下一个节点也要初始化为NULL！
    return t;
}


//功能函数

//遍历并打印链表的值
void PrintSlist(SlistNode* Slist) {
    if (Slist == NULL) { exit(-1); }//排除头结点为空的情况
    while (Slist->next) {//如果不是最后一个节点
        printf("%d", Slist->data);
        Slist = Slist->next;//转换到下一个节点
    }
    printf("%d", Slist->data);
    printf("\n");
}


//单链表尾插,即向尾部添加一个新的节点,并赋值,注意：链表的尾插只能找到链表尾部后再插入！，
//第二个注意点：因为函数传入的参数为形参，故传入的地址实际上是原来的地址的拷贝，如何验证：用查错来验证，调试中发现地址会改变，故要找到原来的地址的话，就应该使用二级指针，找到存放这个地址的地址
void SlistPushBack(SlistNode** Slist, SlistData x) {
    if (*Slist == NULL) { exit(-1); }//排除头结点为空的情况
    SlistNode* nows = *Slist;//这里需要把指针降级，否则结构体访问不兼容,此时Slist解引用得到的是存放地址的空间中存放的地址
    while (nows->next != NULL) {
        nows = nows->next;
    }
    //找到尾部后再创建新节点，并把值赋予新节点，而且节点的下一位为NULL！
    SlistNode* tem = BuynewNode(x);
    nows->next = tem;

}


//实现单链表尾删 ：参数为一个链表的头节点！, 用快慢指针，设置一个侦查节点，在头结点前面，当当前节点找到尾部后，这个节点就指向尾部的前一个节点！
void SlistPopBack(SlistNode** Slist) {
    if (Slist == NULL) { exit(-1); }//排除头结点为空的情况
    SlistNode* nowNode = *Slist;
    SlistNode* pre = BuynewNode(0);
    pre->next = nowNode;
    while (nowNode->next != NULL) {
        nowNode = nowNode->next;
        pre = pre->next;
    }
    //找到尾部后再删除节点!
    SlistNode* pre_nex = pre->next;
    pre->next = NULL;
    free(pre_nex);//释放内存 ； 为了防止野指针 ； 需要将原指针指向NULL
}

//实现单链表的头插和头删,中间插和中间删（这个重要）

//头插：在头部插入新节点，并返回新的头结点

SlistNode* SlistPushHead(SlistNode** Slist,SlistData x) {
    SlistNode* nowNode = *Slist;
    if (nowNode == NULL) { exit(-1); }
    //创建新节点
    SlistNode* tem = BuynewNode(x);
    tem->next = nowNode;
    return tem;
}

//头删：删除在头部的节点并返回新的头部
SlistNode* SlistPopHead(SlistNode** Slist) {
    SlistNode* nowNode = *Slist;
    SlistNode* nexthead = nowNode->next;

    nowNode->next = NULL;//直接断掉头部的指针指向即可
    free(nowNode);//释放内存 ； 为了防止野指针 ； 需要将原指针指向NULL
    return nexthead;
   
}






//实现单链表查找函数：作用：在指定链表头上查找整条链表中指定值的节点,找不到就返回NULL
SlistNode* SlistFind(SlistData x, SlistNode** start) {
    SlistNode* nowNode = *start;
    while (nowNode->next!=NULL) {
        if (nowNode->data == x) {
            return nowNode;
        }
        nowNode = nowNode->next;
    }
    if (nowNode->data == x) {
        return nowNode;
    }
    return NULL;
}


/*
    brief : 合并两个顺序（必要条件）链表的数学方程版
    返回值为合并后的头节点
*/

//自定义链表
typedef struct SlistNode_Math
{
    SlistData data;//节点的数字值
    SlistData pow;//节点的次方
    struct SlistNode_Math* next;//下一个节点的地址,为啥要在之前加struct，因为c语言认为typedef 还没结束，故不能在定义时使用
}SlistNode_Math;

//初始化链表：申请一个新节点,需要输入节点值，返回这个新节点的指针
SlistNode_Math* BuynewNode_Math(SlistData data , SlistData pow) {
    //步骤，先给这个节点分配内存（在堆区），在赋值并返回指针即可
    SlistNode_Math* t = NULL;
    t = (SlistNode_Math*)malloc( 128);
    if (t == NULL) {
        exit(-1);
    }
    t->data = data;
    t->pow = pow;
    t->next = NULL;//记得下一个节点也要初始化为NULL！
    return t; 
}


//单链表尾插,即向尾部添加一个新的节点,并赋值,注意：链表的尾插只能找到链表尾部后再插入！，
//第二个注意点：因为函数传入的参数为形参，故传入的地址实际上是原来的地址的拷贝，如何验证：用查错来验证，调试中发现地址会改变，故要找到原来的地址的话，就应该使用二级指针，找到存放这个地址的地址
void SlistPushBack_Math(SlistNode_Math** Slist, SlistData data , SlistData pow) {
    if (*Slist == NULL) { exit(-1); }//排除头结点为空的情况
    SlistNode_Math* nows = *Slist;//这里需要把指针降级，否则结构体访问不兼容,此时Slist解引用得到的是存放地址的空间中存放的地址
    while (nows->next != NULL) {
        nows = nows->next;
    }
    //找到尾部后再创建新节点，并把值赋予新节点，而且节点的下一位为NULL！
    SlistNode_Math* tem = BuynewNode_Math(data , pow);
    nows->next = tem;

}


//功能函数

//遍历并打印链表的值
void PrintSlist_Math(SlistNode_Math* Slist) {
    if (Slist == NULL) { exit(-1); }//排除头结点为空的情况
    while (Slist->next) {//如果不是最后一个节点
        printf("%d   %d", Slist->data , Slist->pow);
        printf("\n");
        Slist = Slist->next;//转换到下一个节点
    }
    printf("%d   %d", Slist->data , Slist->pow);
    printf("\n");
}

SlistNode_Math* cop1_Slist(SlistNode_Math* s1 , SlistNode_Math* s2) {
   //注意：s1和s2是头指针
    if (s1->next == NULL || s2->next == NULL) {
        exit(-1);
    }
    //新创建新链表的头结点
    SlistNode_Math* s3 = BuynewNode_Math(-1 , -1);
    while (s1 != NULL && s2 != NULL)
    {
        if (s1->pow == s2->pow) {
            SlistPushBack_Math(&s3, s1->data + s2->data, s1->pow);
            s3 = s3->next;
            s1 = s1->next;
            s2 = s2->next;
        }
        else
        {
            if (s1->pow < s2->pow) {
                SlistPushBack_Math(&s3, s2->data, s2->pow);
                s3 = s3->next;
                s2 = s2->next;
            }
            else
            {
                SlistPushBack_Math(&s3, s1->data, s1->pow);
                s3 = s3->next;
                s1 = s1->next;
            }
        }
        //当其中一个是空时
        if (s1 == NULL) {
            s3->next = s2;
        }
        else
        {
            s3->next = s1;
        }

        return s3;
    }
    
         
    
 
}






int main()
{
    //注意：要切实修改原来链表的东西，则需要地址传递，而因为原来Slist就是地址了，故应该用二级指针
   /* SlistNode* Slist1 = BuynewNode(3);
    PrintSlist(Slist1);
    SlistPushBack(&Slist1, 5);
    PrintSlist(Slist1);
    Slist1 = SlistPushHead(&Slist1, 2);
    PrintSlist(Slist1);
    SlistPopBack(&Slist1);
    PrintSlist(Slist1);
    Slist1 = SlistPopHead(&Slist1);

    PrintSlist(Slist1);*/

     SlistNode_Math* s1 = BuynewNode_Math(1,1);
    SlistNode_Math* s2 = BuynewNode_Math(2,1);
    SlistPushBack_Math(&s1 , 2 , 2);
    SlistPushBack_Math(&s1 , 3  ,1);
    SlistNode_Math* s3 = cop1_Slist(s1 , s2);
    
    PrintSlist_Math(s1);
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
