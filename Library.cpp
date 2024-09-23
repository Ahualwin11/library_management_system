//
// Created by Ahua'l on 2024-09-03.
//
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>  //包含exit函数
#include <conio.h>//密码输入
#include <windows.h>//背景
using namespace std;
#define OK 1
#define ERROR 0
#define OVERFLOW -2

int bj1 = 0;  //标记是否完成账号注册
int bj2 = 0;  //标记是否完成密码设置
int bj3 = 0;  //标记是否完成账号输入
int bj4 = 0;  //标记是否完成密码正确

string z1, z2; //账号12
int ch, m1, m2; //密码12
int zcbj = 0, drbj = 0; //标记注册是否完成，标记登入是否完成

//定义图书信息
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`


struct Book {
    string id;//ISBN
    string name;//书名
    double price;//定价
};

//定义单链表
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`


typedef int Status; //Status 是函数返回值类型，其值是函数结果状态代码。

typedef struct LNode {
    Book data; //结点的数据域
    struct LNode *next; //结点的指针域
} LNode, *LinkList; //LinkList为指向结构体LNode的指针类型

string head_1, head_2, head_3;
int length;

Status InitList_L(LinkList &L) { //算法2.6 单链表的初始化
    //构造一个空的单链表L
    L = new LNode; //生成新结点作为头结点，用头指针L指向头结点
    L->next = NULL; //头结点的指针域置空
    return OK;
}

Status GetElem_L(LinkList L, int i, Book &e) { //算法2.7 单链表的取值
    //在带头结点的单链表L中查找第i个元素
    //用e返回L中第i个数据元素的值
    int j;
    LinkList p;
    p = L->next;
    j = 1; //初始化，p指向第一个结点，j为计数器
    while (j < i && p) { //顺链域向后扫描，直到p指向第i个元素或p为空
        p = p->next; //p指向下一个结点
        ++j; //计数器j相应加1
    }
    if (!p || j > i)
        return ERROR; //i值不合法i＞n或i<=0
    e = p->data; //取第i个结点的数据域
    return OK;
} //GetElem_L

LNode *LocateElem_L(LinkList L, int e) { //算法2.8 按值查找
    //在带头结点的单链表L中查找值为e的元素
    LinkList p;
    p = L->next;
    while (p && p->data.price != e)//顺链域向后扫描，直到p为空或p所指结点的数据域等于e
        p = p->next; //p指向下一个结点
    return p; //查找成功返回值为e的结点地址p，查找失败p为NULL
} //LocateElem_L

Status ListInsert_L(LinkList &L, int i, Book &e) { //算法2.9 单链表的插入
    //在带头结点的单链表L中第i个位置插入值为e的新结点
    int j;
    LinkList p, s;
    p = L;
    j = 0;
    while (p && j < i - 1) {
        p = p->next;
        ++j;
    }//查找第i?1个结点，p指向该结点
    if (!p || j > i - 1)
        return ERROR; //i＞n+1或者i＜1
    s = new LNode; //生成新结点*s
    s->data = e; //将结点*s的数据域置为e
    s->next = p->next; //将结点*s的指针域指向结点ai
    p->next = s; //将结点*p的指针域指向结点*s
    ++length;
    return OK;
} //ListInsert_L

Status ListDelete_L(LinkList &L, int i) { //算法2.9 单链表的删除
    //在带头结点的单链表L中，删除第i个位置
    LinkList p, q;
    int j;
    p = L;
    j = 0;
    while ((p->next) && (j < i - 1)) //查找第i?1个结点，p指向该结点
    {
        p = p->next;
        ++j;
    }
    if (!(p->next) || (j > i - 1))
        return ERROR; //当i>n或i<1时，删除位置不合理
    q = p->next; //临时保存被删结点的地址以备释放
    p->next = q->next; //改变删除结点前驱结点的指针域
    delete q; //释放删除结点的空间
    --length;
    return OK;
} //ListDelete_L

void CreateList_H(LinkList &L, int n) { //算法2.11 前插法创建单链表
    //逆位序输入n个元素的值，建立到头结点的单链表L
    LinkList p;
    L = new LNode;
    L->next = NULL; //先建立一个带头结点的空链表
    length = 0;
    fstream file;
    file.open("book.txt");
    if (!file) {
        cout << "未找到相关文件，无法打开！" << endl;
        exit(ERROR);
    }
    file >> head_1 >> head_2 >> head_3;
    while (!file.eof()) {
        p = new LNode; //生成新结点*p
        file >> p->data.id >> p->data.name >> p->data.price; //输入元素值赋给新结点*p的数据域
        p->next = L->next;
        L->next = p; //将新结点*p插入到头结点之后
        length++;//同时对链表长度进行统计
    }
    file.close();
} //CreateList_F

void CreateList_R(LinkList &L, int n) { //算法2.12 后插法创建单链表
    //正位序输入n个元素的值，建立带表头结点的单链表L
    LinkList p, r;
    L = new LNode;
    L->next = NULL; //先建立一个带头结点的空链表
    r = L; //尾指针r指向头结点
    length = 0;
    fstream file; //打开文件进行读写操作
    file.open("book.txt");
    if (!file) {
        cout << "未找到相关文件，无法打开！" << endl;
        system("pause");
        exit(ERROR);
    }
    file >> head_1 >> head_2 >> head_3;
    while (!file.eof()) { //将文件中的信息运用后插法插入到链表中
        p = new LNode;//生成新结点
        file >> p->data.id >> p->data.name >> p->data.price;//输入元素值赋给新结点*p的数据域
        p->next = NULL;
        r->next = p;//将新结点*p插入尾结点*r之后
        r = p;//r指向新的尾结点*p
        length++; //同时对链表长度进行统计
    }
    file.close();
} //CreateList_L


//函数声明
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
void lmain();//主菜单选择函数
void main1();//信息注册系统
void main2();//用户登入系统
void main3();//访问图书系统
int weishu62();//位数限制
int weishu61();//位数限制
int weishu1();//位数限制
//函数定义
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
int weishu61() {
    int s[7], i = 0, mm = 0;
    while (1) {
        while ((ch = getch()) != '\r') {
            if (ch < 48 || ch > 57) {
                if (ch != '\b')
                    continue;
            }
            if (ch == ' ')continue;
            if (ch != '\b') {
                if (i == 6)continue;
                s[i] = ch;
                putchar(ch);
                i++;
            } else {
                if (i == 0)continue;
                putchar('\b');
                putchar(' ');
                putchar('\b');
                i--;
            }
        }
        if (i == 0)
            continue;
        if (i == 1) {
            mm = s[0] - 48;
            break;
        }
        if (i == 2) {
            mm = (s[0] - 48) * 10 + (s[1] - 48);
            break;
        }
        if (i == 3) {
            mm = (s[0] - 48) * 100 + (s[1] - 48) * 10 + (s[2] - 48);
            break;
        }
        if (i == 4) {
            mm = (s[0] - 48) * 1000 + (s[1] - 48) * 100 + (s[2] - 48) * 10 + (s[3] - 48);
            break;
        }
        if (i == 5) {
            mm = (s[0] - 48) * 10000 + (s[1] - 48) * 1000 + (s[2] - 48) * 100 + (s[3] - 48) * 10 + (s[4] - 48);
            break;
        }
        if (i == 6) {
            mm = (s[0] - 48) * 100000 + (s[1] - 48) * 10000 + (s[2] - 48) * 1000 + (s[3] - 48) * 100 +
                 (s[4] - 48) * 10 + (s[5] - 48);
            break;
        }
    }
    return mm;
}

int weishu62() {
    int s[7], i = 0, mm = 0;
    while (1) {
        while ((ch = getch()) != '\r') {
            if (ch < 48 || ch > 57) {
                if (ch != '\b')
                    continue;
            }
            if (ch == ' ')continue;
            if (ch != '\b') {
                if (i == 6)continue;
                s[i] = ch;
                putchar('*');
                i++;
            } else {
                if (i == 0)continue;
                putchar('\b');
                putchar(' ');
                putchar('\b');
                i--;
            }
        }
        if (i == 0)
            continue;
        if (i == 1) {
            mm = s[0] - 48;
            break;
        }
        if (i == 2) {
            mm = (s[0] - 48) * 10 + (s[1] - 48);
            break;
        }
        if (i == 3) {
            mm = (s[0] - 48) * 100 + (s[1] - 48) * 10 + (s[2] - 48);
            break;
        }
        if (i == 4) {
            mm = (s[0] - 48) * 1000 + (s[1] - 48) * 100 + (s[2] - 48) * 10 + (s[3] - 48);
            break;
        }
        if (i == 5) {
            mm = (s[0] - 48) * 10000 + (s[1] - 48) * 1000 + (s[2] - 48) * 100 + (s[3] - 48) * 10 + (s[4] - 48);
            break;
        }
        if (i == 6) {
            mm = (s[0] - 48) * 100000 + (s[1] - 48) * 10000 + (s[2] - 48) * 1000 + (s[3] - 48) * 100 +
                 (s[4] - 48) * 10 + (s[5] - 48);
            break;
        }
    }
    return mm;
}

int weishu1() {
    int ch, s[2], i = 0, sum1;
    while (1) {
        while ((ch = getch()) != '\r') {
            if (ch < 48 || ch > 57) {
                if (ch != '\b')
                    continue;
            }
            if (ch == ' ')continue;
            if (ch != '\b') {
                if (i == 1)continue;
                s[i] = ch;
                putchar(ch);
                i++;
            } else {
                if (i == 0)continue;
                putchar('\b');
                putchar(' ');
                putchar('\b');
                i--;
            }
        }
        if (i == 0)
            continue;
        if (i == 1) {
            sum1 = s[0] - 48;
            break;
        }
    }

    return sum1;
}

void lmain()//登录功能函数
{

    system("cls");
    system("color 1F");
    printf("\n\n\t    欢迎使用Ahual图书管理系统\n\n");
    cout << "╔*☆***◎***◇***☆*** 菜单 ***☆***◇***◎***☆* ╗\n";
    cout << "|★|\t                              \t|★|\n";
    cout << "|☆|\t        一、信息注册系统      \t|☆|\n";
    cout << "|★|\t                              \t|★|\n";
    cout << "|☆|\t        二、用户登入系统      \t|☆|\n";
    cout << "|★|\t                              \t|★|\n";
    cout << "|☆|\t        三、访问图书系统      \t|☆|\n";
    cout << "|★|\t                              \t|★|\n";
    cout << "|☆|\t        四、退出管理系统      \t|☆|\n";
    cout << "|☆|\t                              \t|☆|\n";
    cout << "╚*☆***◎***◇****☆****★****☆****◇***◎***☆***╝";
    int choose;
    printf("\n\n\t    请按数字选择(仅数字，限1位，其他字符无法输入)\n\n");
    printf("\t    按回车键确定：");
    choose = weishu1();
    switch (choose)//功能函数
    {
        case 1:
            main1();
            break;
        case 2:
            main2();
            break;
        case 3:
            main3();
            break;
        case 4:
            system("cls");
            exit(0);
            break;
        default:
            system("cls");
            cout << "\n\t\t操作结果提示↓\n\n";
            printf("**********************************************");
            printf("\n\n\t\t输入有误 请重新输入!\n\n");
            printf("**********************************************");
            printf("\n\n\t\t");
            system("pause");
            lmain();
    }

}

//信息注册系统系统
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
void main1() {
    int tt1 = 0;//标记是否完成账号设置
    int choose;
    choose = -1;
    while (choose != 0) {
        system("cls");
        system("color 2F");
        printf("\n\n\t    您已进入账号注册系统系统\n\n");
        cout << "╔*☆***◎***◇***☆*** 菜单1 ***☆***◇***◎***☆* ╗\n";
        cout << "|★|\t                                 \t|★|\n";
        cout << "|☆|\t       一、请设置用户账号        \t|☆|\n";
        cout << "|★|\t                                 \t|★|\n";
        cout << "|☆|\t       二、设置数字登入密码     \t|☆|\n";
        cout << "|★|\t                                 \t|★|\n";
        cout << "|☆|\t       三、退出返回上一级        \t|☆|\n";
        cout << "|☆|\t                                 \t|☆|\n";
        cout << "╚*☆***◎***◇****☆**** ★****☆****◇***◎***☆* ╝";
        printf("\n\n\t    请按数字选择(无法输入其他字符或多个数字)\n\n");
        printf("\t    按回车键确定：");
        choose = weishu1();

        switch (choose)//功能函数
        {
            case 1:
                system("cls");
                cout << "\n\t\t用户操作提示↓\n\n";
                cout << "请设置用户账号(任意字符、任意长度的)：";
                cin >> z1;
                system("cls");
                cout << "\n\t\t操作结果提示↓\n\n";
                printf("# # # # # # # # # # # # # # # # # # # # # # # #");
                printf("\n\n\t\t 账号注册成功!\n\n");
                tt1 = 1;//标记完成账号设置
                bj1 = 1;
                printf("# # # # # # # # # # # # # # # # # # # # # # # #");
                printf("\n\n\t\t");
                system("pause");
                break;
            case 2:
                if (tt1 != 1)//标记是否完成账号设置
                {
                    system("cls");
                    cout << "\n\t\t注册系统检查提醒↓\n\n";
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t  您未注册入账户 请先注册一个账号\n\n");
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ \n\n");
                    system("pause");
                    main1();
                }
                system("cls");
                cout << "\n\t\t用户操作提示↓\n\n";
                cout << "请设置登入密码(已受限数字，受限1-6位，不信试试)：";
                m1 = weishu61();
                system("cls");
                cout << "\n\t\t操作结果提示↓\n\n";
                printf("# # # # # # # # # # # # # # # # # # # # # # # #");
                printf("\n\n\t\t 密码设置成功!\n\n");
                bj2 = 1;
                printf("# # # # # # # # # # # # # # # # # # # # # # # #");
                printf("\n\n\t\t");
                system("pause");
                break;
            case 3:
                zcbj = bj1 + bj2;
                lmain();
                break;
            default:
                system("cls");
                cout << "\n\t\t操作结果提示↓\n\n";
                printf("# # # # # # # # # # # # # # # # # # # # # # # #");
                printf("\n\n\t\t输入有误 请重新输入!\n\n");
                printf("# # # # # # # # # # # # # # # # # # # # # # # #");
                printf("\n\n\t\t");
                system("pause");
        }

    }
    return;

}

//用户登入系统
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
void main2() {
    int tt2 = 0;//标记是否完成账号输入
    system("color 0A");
    if (zcbj != 2) //检查是否已经注册
    {
        system("cls");
        cout << "\n\t\t登入系统检查提示↓\n\n";
        printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
        printf("\n\n\t  用户尚未注册 请先返回注册!\n\n");
        printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ \n\n");
        system("pause");
        lmain();
    }

    int choose;
    choose = -1;
    while (choose != 0) {
        system("cls");
        system("color 0A");
        printf("\n\n\t    您已进入用户登入系统\n\n");
        cout << "╔*☆***◎***◇***☆*** 菜单2 ***☆***◇***◎***☆* ╗\n";
        cout << "|★|\t                                 \t|★|\n";
        cout << "|☆|\t       一、请输入用户账号        \t|☆|\n";
        cout << "|★|\t                                 \t|★|\n";
        cout << "|☆|\t       二、请输入登入密码        \t|☆|\n";
        cout << "|★|\t                                 \t|★|\n";
        cout << "|☆|\t       三、退出返回上一级        \t|☆|\n";
        cout << "|☆|\t                                 \t|☆|\n";
        cout << "╚*☆***◎***◇****☆**** ★****☆****◇***◎***☆* ╝";
        printf("\n\n\t    请按数字选择(无法输入其他字符)\n\n");
        printf("\t    按回车键确定：");
        choose = weishu1();

        switch (choose)//功能函数
        {
            case 1:
                system("cls");
                cout << "\n\t\t用户操作提示↓\n\n";
                cout << "请输入用户账号：";
                cin >> z2;
                if (z1 == z2) {
                    system("cls");
                    cout << "\n\t\t操作结果提示↓\n\n";
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t\t 账号匹配成功!\n\n");
                    tt2 = 1;//标记已经完成账号输入
                    bj3 = 1;
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t\t");
                    system("pause");
                } else {
                    system("cls");
                    cout << "\n\t\t操作结果提示↓\n\n";
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t\t 账号不存在匹配失败!\n\n");
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t\t");
                    system("pause");
                }
                break;
            case 2:
                if (tt2 != 1)//标记没有完成账号输入
                {
                    system("cls");
                    cout << "\n\t\t系统检查提示↓\n\n";
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t  未输入账户 请先输入账号!\n\n");
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ \n\n");
                    system("pause");
                    main2();
                }
                system("cls");
                cout << "\n\t\t用户操作提示↓\n\n";
                cout << "请输入设置的密码(已加密*)：";
                m2 = weishu62();//加密输入
                if (m1 == m2) {
                    system("cls");
                    cout << "\n\t\t操作结果提示↓\n\n";
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t\t 密码正确，登入成功!\n\n");
                    bj4 = 1;
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t\t");
                    system("pause");
                    main2();
                } else {
                    for (int k = 0; k < 3; k++) {
                        system("cls");
                        cout << "\n\t\t操作结果提示↓\n\n";
                        printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                        printf("\n\n\t  密码错误,还剩%d次\n\n", 3 - k);
                        printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                        printf("\n\n\t\t");
                        system("pause");
                        system("cls");
                        cout << "\n\t\t用户操作提示↓\n\n";
                        cout << "请重新输入正确的密码：";
                        m2 = weishu62();
                        if (m1 == m2) {
                            system("cls");
                            cout << "\n\t\t操作结果提示↓\n\n";
                            printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                            printf("\n\n\t\t 密码正确，登入成功!\n\n");
                            bj4 = 1;
                            printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                            printf("\n\n\t\t");
                            system("pause");
                            main2();
                        }
                        if (k == 2) {
                            system("cls");
                            cout << "\n\t\t操作结果提示↓\n\n";
                            printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                            printf("\n\n\t   密码错误3次，请重新注册账号\n\n");
                            printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                            printf("\n\n\t\t");
                            system("pause");
                            zcbj = 0;
                            lmain();
                        }
                    }
                }
                break;
            case 3:
                drbj = bj3 + bj4;
                lmain();
                break;
            default:
                system("cls");
                cout << "\n\t\t操作结果提示↓\n\n";
                printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                printf("\n\n\t\t输入有误 请重新输入!\n\n");
                printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                printf("\n\n\t\t");
                system("pause");
        }
    }
    return;

}

//访问图书系统
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
void main3() {
    system("color 5F");
    if (drbj != 2)  //检查是否已经登入
    {
        system("cls");
        cout << "\n\t\t访问系统检查提醒↓\n\n";
        printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
        printf("\n\n\t  用户尚未登入 请先返回登入!\n\n");
        printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ \n\n");
        system("pause");
        lmain();
    }
    int a, y = 0;
    double price;
    Book e; //结构体实例
    int choose;
    LinkList L, p;
    choose = -1;
    while (choose != 0) {
        system("cls");
        system("color 5F");
        printf("\n\n\t    您已进入访问图书系统\n\n");
        cout << "╔*☆***◎***◇***☆*** 菜单2 ***☆***◇***◎***☆* ╗\n";
        cout << "|★|\t                                 \t|★|\n";
        cout << "|☆|\t          1. 建立书架            \t|☆|\n";
        cout << "|★|\t                                 \t|★|\n";
        cout << "|☆|\t          2. 查询图书            \t|☆|\n";
        cout << "|★|\t                                 \t|★|\n";
        cout << "|☆|\t          3. 查询价格            \t|☆|\n";
        cout << "|☆|\t                                 \t|☆|\n";
        cout << "|☆|\t          4. 增加图书            \t|☆|\n";
        cout << "|★|\t                                 \t|★|\n";
        cout << "|☆|\t          5. 删除图书            \t|☆|\n";
        cout << "|★|\t                                 \t|★|\n";
        cout << "|☆|\t          6. 库存浏览            \t|☆|\n";
        cout << "|☆|\t                                 \t|☆|\n";
        cout << "|☆|\t          7.返回上一层           \t|☆|\n";
        cout << "|☆|\t                                 \t|☆|\n";
        cout << "╚*☆***◎***◇****☆**** ★****☆****◇***◎***☆* ╝";
        printf("\n\n\t    请按数字选择(无法输入其他字符)\n\n");
        printf("\t    按回车键确定：");
        choose = weishu1();
        switch (choose) {
            case 1://使用后插法创建单链表
                InitList_L(L);
                CreateList_R(L, length);
                system("cls");
                cout << "\n\t\t操作结果提示↓\n\n";
                printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                cout << "\n\n\t  输入 book.txt 信息完毕\n\n";
                printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                system("pause");
                break;
            case 2: //单链表的按序号取值
                system("cls");
                cout << "\n\t\t用户操作提示↓\n\n";
                cout << "请输入您想查询书架上第(_)本书的信息:";
                cin >> a;
                if (GetElem_L(L, a, e)) {
                    system("cls");
                    cout << "\n\t\t操作结果提示↓\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    cout << "第" << a << "本图书的信息是：";
                    cout << left << setw(15) << e.id << "  " << left << setw(50)
                         << e.name << " \t" << e.price << endl
                         << endl;
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                } else {
                    system("cls");
                    cout << "\n\t\t操作结果提示↓\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                    cout << "\n\n\t  超出范围 查找失败\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                }
                break;
            case 3: //单链表的按值查找
                system("cls");
                p = L->next;
                while (p) {
                    y++;
                    cout << left << setw(5) << p->data.price << "  ";
                    if (y % 5 == 0)
                        cout << endl;
                    p = p->next;
                }
                cout << "\n\t\t用户操作提示↓\n\n";
                cout << "\n请输入所要查找价格:";
                cin >> price;
                if (LocateElem_L(L, price) != NULL) {
                    system("cls");
                    cout << "\n\t\t操作结果提示↓\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                    cout << "\n\n\t  查找成功\n\n";
                    cout << "该价格对应的书名为：" << LocateElem_L(L, price)->data.name << endl << endl;
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                } else {
                    system("cls");
                    cout << "\n\t\t操作结果提示↓\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                    cout << "\n\n\t  查找失败! 定价" << price << " 没有找到\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                }
                break;
            case 4: //单链表的插入
                system("cls");
                cout << "\n\t\t用户操作提示↓\n\n";
                cout << "请输入增加的书籍信息 插入位置  编号   书名       价格(空格隔开)\n\n";
                cout << "样例 (四个信息)      1         97871  C语言基础  55\n";
                cout << "样例 (四个信息)      2         97872  C++基础    66\n";
                cout << "样例 (四个信息)      3         97873  数据结构   77\n";
                cout << "依次输入：           ";
                cin >> a;
                cin >> e.id >> e.name >> e.price;
                if (ListInsert_L(L, a, e)) {
                    system("cls");
                    cout << "\n\t\t操作结果提示↓\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                    cout << "\n\n\t  书本信息插入成功\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                } else {
                    system("cls");
                    cout << "\n\t\t操作结果提示↓\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                    cout << "\n\n\t  格式错误 插入失败\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                }
                break;
            case 5: //单链表的删除
                system("cls");
                cout << "请输入所要删除的书籍的位置:";
                cin >> a;
                if (ListDelete_L(L, a)) {
                    system("cls");
                    cout << "\n\t\t操作结果提示↓\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                    cout << "\n\n\t  删除成功!\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                } else {
                    system("cls");
                    cout << "\n\t\t操作结果提示↓\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                    cout << "\n\n\t 位置错误 删除失败!\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                }
                break;
            case 6: //单链表的输出
                system("cls");
                cout << "\n\t\t操作结果提示↓\n\n";
                printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                p = L->next;
                while (p) {
                    cout << left << setw(15) << p->data.id << "\t" << left << setw(
                            50) << p->data.name << "\t" << left << setw(5)
                         << p->data.price << endl;
                    p = p->next;
                }
                cout << endl;
                printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                system("pause");
                break;
            case 7:
                lmain();
                break;
            default:
                system("cls");
                cout << "\n\t\t操作结果提示↓\n\n";
                printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                printf("\n\n\t\t输入有误 请重新输入!\n\n");
                printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                system("pause");
        }
    }
    system("cls");
    printf("\n\n\t\t访问结束按任意键返回\n\n");
    getch();
    lmain();
    return;
}

//主函数
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
int main() {
    lmain();//主菜单
    return 0;
}

