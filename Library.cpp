//
// Created by Ahua'l on 2024-09-03.
//
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>  //����exit����
#include <conio.h>//��������
#include <windows.h>//����
using namespace std;
#define OK 1
#define ERROR 0
#define OVERFLOW -2

int bj1 = 0;  //����Ƿ�����˺�ע��
int bj2 = 0;  //����Ƿ������������
int bj3 = 0;  //����Ƿ�����˺�����
int bj4 = 0;  //����Ƿ����������ȷ

string z1, z2; //�˺�12
int ch, m1, m2; //����12
int zcbj = 0, drbj = 0; //���ע���Ƿ���ɣ���ǵ����Ƿ����

//����ͼ����Ϣ
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`


struct Book {
    string id;//ISBN
    string name;//����
    double price;//����
};

//���嵥����
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`


typedef int Status; //Status �Ǻ�������ֵ���ͣ���ֵ�Ǻ������״̬���롣

typedef struct LNode {
    Book data; //����������
    struct LNode *next; //����ָ����
} LNode, *LinkList; //LinkListΪָ��ṹ��LNode��ָ������

string head_1, head_2, head_3;
int length;

Status InitList_L(LinkList &L) { //�㷨2.6 ������ĳ�ʼ��
    //����һ���յĵ�����L
    L = new LNode; //�����½����Ϊͷ��㣬��ͷָ��Lָ��ͷ���
    L->next = NULL; //ͷ����ָ�����ÿ�
    return OK;
}

Status GetElem_L(LinkList L, int i, Book &e) { //�㷨2.7 �������ȡֵ
    //�ڴ�ͷ���ĵ�����L�в��ҵ�i��Ԫ��
    //��e����L�е�i������Ԫ�ص�ֵ
    int j;
    LinkList p;
    p = L->next;
    j = 1; //��ʼ����pָ���һ����㣬jΪ������
    while (j < i && p) { //˳�������ɨ�裬ֱ��pָ���i��Ԫ�ػ�pΪ��
        p = p->next; //pָ����һ�����
        ++j; //������j��Ӧ��1
    }
    if (!p || j > i)
        return ERROR; //iֵ���Ϸ�i��n��i<=0
    e = p->data; //ȡ��i������������
    return OK;
} //GetElem_L

LNode *LocateElem_L(LinkList L, int e) { //�㷨2.8 ��ֵ����
    //�ڴ�ͷ���ĵ�����L�в���ֵΪe��Ԫ��
    LinkList p;
    p = L->next;
    while (p && p->data.price != e)//˳�������ɨ�裬ֱ��pΪ�ջ�p��ָ�������������e
        p = p->next; //pָ����һ�����
    return p; //���ҳɹ�����ֵΪe�Ľ���ַp������ʧ��pΪNULL
} //LocateElem_L

Status ListInsert_L(LinkList &L, int i, Book &e) { //�㷨2.9 ������Ĳ���
    //�ڴ�ͷ���ĵ�����L�е�i��λ�ò���ֵΪe���½��
    int j;
    LinkList p, s;
    p = L;
    j = 0;
    while (p && j < i - 1) {
        p = p->next;
        ++j;
    }//���ҵ�i?1����㣬pָ��ý��
    if (!p || j > i - 1)
        return ERROR; //i��n+1����i��1
    s = new LNode; //�����½��*s
    s->data = e; //�����*s����������Ϊe
    s->next = p->next; //�����*s��ָ����ָ����ai
    p->next = s; //�����*p��ָ����ָ����*s
    ++length;
    return OK;
} //ListInsert_L

Status ListDelete_L(LinkList &L, int i) { //�㷨2.9 �������ɾ��
    //�ڴ�ͷ���ĵ�����L�У�ɾ����i��λ��
    LinkList p, q;
    int j;
    p = L;
    j = 0;
    while ((p->next) && (j < i - 1)) //���ҵ�i?1����㣬pָ��ý��
    {
        p = p->next;
        ++j;
    }
    if (!(p->next) || (j > i - 1))
        return ERROR; //��i>n��i<1ʱ��ɾ��λ�ò�����
    q = p->next; //��ʱ���汻ɾ���ĵ�ַ�Ա��ͷ�
    p->next = q->next; //�ı�ɾ�����ǰ������ָ����
    delete q; //�ͷ�ɾ�����Ŀռ�
    --length;
    return OK;
} //ListDelete_L

void CreateList_H(LinkList &L, int n) { //�㷨2.11 ǰ�巨����������
    //��λ������n��Ԫ�ص�ֵ��������ͷ���ĵ�����L
    LinkList p;
    L = new LNode;
    L->next = NULL; //�Ƚ���һ����ͷ���Ŀ�����
    length = 0;
    fstream file;
    file.open("book.txt");
    if (!file) {
        cout << "δ�ҵ�����ļ����޷��򿪣�" << endl;
        exit(ERROR);
    }
    file >> head_1 >> head_2 >> head_3;
    while (!file.eof()) {
        p = new LNode; //�����½��*p
        file >> p->data.id >> p->data.name >> p->data.price; //����Ԫ��ֵ�����½��*p��������
        p->next = L->next;
        L->next = p; //���½��*p���뵽ͷ���֮��
        length++;//ͬʱ�������Ƚ���ͳ��
    }
    file.close();
} //CreateList_F

void CreateList_R(LinkList &L, int n) { //�㷨2.12 ��巨����������
    //��λ������n��Ԫ�ص�ֵ����������ͷ���ĵ�����L
    LinkList p, r;
    L = new LNode;
    L->next = NULL; //�Ƚ���һ����ͷ���Ŀ�����
    r = L; //βָ��rָ��ͷ���
    length = 0;
    fstream file; //���ļ����ж�д����
    file.open("book.txt");
    if (!file) {
        cout << "δ�ҵ�����ļ����޷��򿪣�" << endl;
        system("pause");
        exit(ERROR);
    }
    file >> head_1 >> head_2 >> head_3;
    while (!file.eof()) { //���ļ��е���Ϣ���ú�巨���뵽������
        p = new LNode;//�����½��
        file >> p->data.id >> p->data.name >> p->data.price;//����Ԫ��ֵ�����½��*p��������
        p->next = NULL;
        r->next = p;//���½��*p����β���*r֮��
        r = p;//rָ���µ�β���*p
        length++; //ͬʱ�������Ƚ���ͳ��
    }
    file.close();
} //CreateList_L


//��������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
void lmain();//���˵�ѡ����
void main1();//��Ϣע��ϵͳ
void main2();//�û�����ϵͳ
void main3();//����ͼ��ϵͳ
int weishu62();//λ������
int weishu61();//λ������
int weishu1();//λ������
//��������
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

void lmain()//��¼���ܺ���
{

    system("cls");
    system("color 1F");
    printf("\n\n\t    ��ӭʹ��Ahualͼ�����ϵͳ\n\n");
    cout << "�X*��***��***��***��*** �˵� ***��***��***��***��* �[\n";
    cout << "|��|\t                              \t|��|\n";
    cout << "|��|\t        һ����Ϣע��ϵͳ      \t|��|\n";
    cout << "|��|\t                              \t|��|\n";
    cout << "|��|\t        �����û�����ϵͳ      \t|��|\n";
    cout << "|��|\t                              \t|��|\n";
    cout << "|��|\t        ��������ͼ��ϵͳ      \t|��|\n";
    cout << "|��|\t                              \t|��|\n";
    cout << "|��|\t        �ġ��˳�����ϵͳ      \t|��|\n";
    cout << "|��|\t                              \t|��|\n";
    cout << "�^*��***��***��****��****��****��****��***��***��***�a";
    int choose;
    printf("\n\n\t    �밴����ѡ��(�����֣���1λ�������ַ��޷�����)\n\n");
    printf("\t    ���س���ȷ����");
    choose = weishu1();
    switch (choose)//���ܺ���
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
            cout << "\n\t\t���������ʾ��\n\n";
            printf("**********************************************");
            printf("\n\n\t\t�������� ����������!\n\n");
            printf("**********************************************");
            printf("\n\n\t\t");
            system("pause");
            lmain();
    }

}

//��Ϣע��ϵͳϵͳ
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
void main1() {
    int tt1 = 0;//����Ƿ�����˺�����
    int choose;
    choose = -1;
    while (choose != 0) {
        system("cls");
        system("color 2F");
        printf("\n\n\t    ���ѽ����˺�ע��ϵͳϵͳ\n\n");
        cout << "�X*��***��***��***��*** �˵�1 ***��***��***��***��* �[\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "|��|\t       һ���������û��˺�        \t|��|\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "|��|\t       �����������ֵ�������     \t|��|\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "|��|\t       �����˳�������һ��        \t|��|\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "�^*��***��***��****��**** ��****��****��***��***��* �a";
        printf("\n\n\t    �밴����ѡ��(�޷����������ַ���������)\n\n");
        printf("\t    ���س���ȷ����");
        choose = weishu1();

        switch (choose)//���ܺ���
        {
            case 1:
                system("cls");
                cout << "\n\t\t�û�������ʾ��\n\n";
                cout << "�������û��˺�(�����ַ������ⳤ�ȵ�)��";
                cin >> z1;
                system("cls");
                cout << "\n\t\t���������ʾ��\n\n";
                printf("# # # # # # # # # # # # # # # # # # # # # # # #");
                printf("\n\n\t\t �˺�ע��ɹ�!\n\n");
                tt1 = 1;//�������˺�����
                bj1 = 1;
                printf("# # # # # # # # # # # # # # # # # # # # # # # #");
                printf("\n\n\t\t");
                system("pause");
                break;
            case 2:
                if (tt1 != 1)//����Ƿ�����˺�����
                {
                    system("cls");
                    cout << "\n\t\tע��ϵͳ������ѡ�\n\n";
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t  ��δע�����˻� ����ע��һ���˺�\n\n");
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ \n\n");
                    system("pause");
                    main1();
                }
                system("cls");
                cout << "\n\t\t�û�������ʾ��\n\n";
                cout << "�����õ�������(���������֣�����1-6λ����������)��";
                m1 = weishu61();
                system("cls");
                cout << "\n\t\t���������ʾ��\n\n";
                printf("# # # # # # # # # # # # # # # # # # # # # # # #");
                printf("\n\n\t\t �������óɹ�!\n\n");
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
                cout << "\n\t\t���������ʾ��\n\n";
                printf("# # # # # # # # # # # # # # # # # # # # # # # #");
                printf("\n\n\t\t�������� ����������!\n\n");
                printf("# # # # # # # # # # # # # # # # # # # # # # # #");
                printf("\n\n\t\t");
                system("pause");
        }

    }
    return;

}

//�û�����ϵͳ
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
void main2() {
    int tt2 = 0;//����Ƿ�����˺�����
    system("color 0A");
    if (zcbj != 2) //����Ƿ��Ѿ�ע��
    {
        system("cls");
        cout << "\n\t\t����ϵͳ�����ʾ��\n\n";
        printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
        printf("\n\n\t  �û���δע�� ���ȷ���ע��!\n\n");
        printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ \n\n");
        system("pause");
        lmain();
    }

    int choose;
    choose = -1;
    while (choose != 0) {
        system("cls");
        system("color 0A");
        printf("\n\n\t    ���ѽ����û�����ϵͳ\n\n");
        cout << "�X*��***��***��***��*** �˵�2 ***��***��***��***��* �[\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "|��|\t       һ���������û��˺�        \t|��|\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "|��|\t       �����������������        \t|��|\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "|��|\t       �����˳�������һ��        \t|��|\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "�^*��***��***��****��**** ��****��****��***��***��* �a";
        printf("\n\n\t    �밴����ѡ��(�޷����������ַ�)\n\n");
        printf("\t    ���س���ȷ����");
        choose = weishu1();

        switch (choose)//���ܺ���
        {
            case 1:
                system("cls");
                cout << "\n\t\t�û�������ʾ��\n\n";
                cout << "�������û��˺ţ�";
                cin >> z2;
                if (z1 == z2) {
                    system("cls");
                    cout << "\n\t\t���������ʾ��\n\n";
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t\t �˺�ƥ��ɹ�!\n\n");
                    tt2 = 1;//����Ѿ�����˺�����
                    bj3 = 1;
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t\t");
                    system("pause");
                } else {
                    system("cls");
                    cout << "\n\t\t���������ʾ��\n\n";
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t\t �˺Ų�����ƥ��ʧ��!\n\n");
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t\t");
                    system("pause");
                }
                break;
            case 2:
                if (tt2 != 1)//���û������˺�����
                {
                    system("cls");
                    cout << "\n\t\tϵͳ�����ʾ��\n\n";
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t  δ�����˻� ���������˺�!\n\n");
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ \n\n");
                    system("pause");
                    main2();
                }
                system("cls");
                cout << "\n\t\t�û�������ʾ��\n\n";
                cout << "���������õ�����(�Ѽ���*)��";
                m2 = weishu62();//��������
                if (m1 == m2) {
                    system("cls");
                    cout << "\n\t\t���������ʾ��\n\n";
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t\t ������ȷ������ɹ�!\n\n");
                    bj4 = 1;
                    printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                    printf("\n\n\t\t");
                    system("pause");
                    main2();
                } else {
                    for (int k = 0; k < 3; k++) {
                        system("cls");
                        cout << "\n\t\t���������ʾ��\n\n";
                        printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                        printf("\n\n\t  �������,��ʣ%d��\n\n", 3 - k);
                        printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                        printf("\n\n\t\t");
                        system("pause");
                        system("cls");
                        cout << "\n\t\t�û�������ʾ��\n\n";
                        cout << "������������ȷ�����룺";
                        m2 = weishu62();
                        if (m1 == m2) {
                            system("cls");
                            cout << "\n\t\t���������ʾ��\n\n";
                            printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                            printf("\n\n\t\t ������ȷ������ɹ�!\n\n");
                            bj4 = 1;
                            printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                            printf("\n\n\t\t");
                            system("pause");
                            main2();
                        }
                        if (k == 2) {
                            system("cls");
                            cout << "\n\t\t���������ʾ��\n\n";
                            printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                            printf("\n\n\t   �������3�Σ�������ע���˺�\n\n");
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
                cout << "\n\t\t���������ʾ��\n\n";
                printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                printf("\n\n\t\t�������� ����������!\n\n");
                printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
                printf("\n\n\t\t");
                system("pause");
        }
    }
    return;

}

//����ͼ��ϵͳ
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
void main3() {
    system("color 5F");
    if (drbj != 2)  //����Ƿ��Ѿ�����
    {
        system("cls");
        cout << "\n\t\t����ϵͳ������ѡ�\n\n";
        printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ ");
        printf("\n\n\t  �û���δ���� ���ȷ��ص���!\n\n");
        printf("@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ \n\n");
        system("pause");
        lmain();
    }
    int a, y = 0;
    double price;
    Book e; //�ṹ��ʵ��
    int choose;
    LinkList L, p;
    choose = -1;
    while (choose != 0) {
        system("cls");
        system("color 5F");
        printf("\n\n\t    ���ѽ������ͼ��ϵͳ\n\n");
        cout << "�X*��***��***��***��*** �˵�2 ***��***��***��***��* �[\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "|��|\t          1. �������            \t|��|\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "|��|\t          2. ��ѯͼ��            \t|��|\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "|��|\t          3. ��ѯ�۸�            \t|��|\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "|��|\t          4. ����ͼ��            \t|��|\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "|��|\t          5. ɾ��ͼ��            \t|��|\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "|��|\t          6. ������            \t|��|\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "|��|\t          7.������һ��           \t|��|\n";
        cout << "|��|\t                                 \t|��|\n";
        cout << "�^*��***��***��****��**** ��****��****��***��***��* �a";
        printf("\n\n\t    �밴����ѡ��(�޷����������ַ�)\n\n");
        printf("\t    ���س���ȷ����");
        choose = weishu1();
        switch (choose) {
            case 1://ʹ�ú�巨����������
                InitList_L(L);
                CreateList_R(L, length);
                system("cls");
                cout << "\n\t\t���������ʾ��\n\n";
                printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                cout << "\n\n\t  ���� book.txt ��Ϣ���\n\n";
                printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                system("pause");
                break;
            case 2: //������İ����ȡֵ
                system("cls");
                cout << "\n\t\t�û�������ʾ��\n\n";
                cout << "�����������ѯ����ϵ�(_)�������Ϣ:";
                cin >> a;
                if (GetElem_L(L, a, e)) {
                    system("cls");
                    cout << "\n\t\t���������ʾ��\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    cout << "��" << a << "��ͼ�����Ϣ�ǣ�";
                    cout << left << setw(15) << e.id << "  " << left << setw(50)
                         << e.name << " \t" << e.price << endl
                         << endl;
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                } else {
                    system("cls");
                    cout << "\n\t\t���������ʾ��\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                    cout << "\n\n\t  ������Χ ����ʧ��\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                }
                break;
            case 3: //������İ�ֵ����
                system("cls");
                p = L->next;
                while (p) {
                    y++;
                    cout << left << setw(5) << p->data.price << "  ";
                    if (y % 5 == 0)
                        cout << endl;
                    p = p->next;
                }
                cout << "\n\t\t�û�������ʾ��\n\n";
                cout << "\n��������Ҫ���Ҽ۸�:";
                cin >> price;
                if (LocateElem_L(L, price) != NULL) {
                    system("cls");
                    cout << "\n\t\t���������ʾ��\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                    cout << "\n\n\t  ���ҳɹ�\n\n";
                    cout << "�ü۸��Ӧ������Ϊ��" << LocateElem_L(L, price)->data.name << endl << endl;
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                } else {
                    system("cls");
                    cout << "\n\t\t���������ʾ��\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                    cout << "\n\n\t  ����ʧ��! ����" << price << " û���ҵ�\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                }
                break;
            case 4: //������Ĳ���
                system("cls");
                cout << "\n\t\t�û�������ʾ��\n\n";
                cout << "���������ӵ��鼮��Ϣ ����λ��  ���   ����       �۸�(�ո����)\n\n";
                cout << "���� (�ĸ���Ϣ)      1         97871  C���Ի���  55\n";
                cout << "���� (�ĸ���Ϣ)      2         97872  C++����    66\n";
                cout << "���� (�ĸ���Ϣ)      3         97873  ���ݽṹ   77\n";
                cout << "�������룺           ";
                cin >> a;
                cin >> e.id >> e.name >> e.price;
                if (ListInsert_L(L, a, e)) {
                    system("cls");
                    cout << "\n\t\t���������ʾ��\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                    cout << "\n\n\t  �鱾��Ϣ����ɹ�\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                } else {
                    system("cls");
                    cout << "\n\t\t���������ʾ��\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                    cout << "\n\n\t  ��ʽ���� ����ʧ��\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                }
                break;
            case 5: //�������ɾ��
                system("cls");
                cout << "��������Ҫɾ�����鼮��λ��:";
                cin >> a;
                if (ListDelete_L(L, a)) {
                    system("cls");
                    cout << "\n\t\t���������ʾ��\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                    cout << "\n\n\t  ɾ���ɹ�!\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                } else {
                    system("cls");
                    cout << "\n\t\t���������ʾ��\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                    cout << "\n\n\t λ�ô��� ɾ��ʧ��!\n\n";
                    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    system("pause");
                }
                break;
            case 6: //����������
                system("cls");
                cout << "\n\t\t���������ʾ��\n\n";
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
                cout << "\n\t\t���������ʾ��\n\n";
                printf("* * * * * * * * * * * * * * * * * * * * * * * *");
                printf("\n\n\t\t�������� ����������!\n\n");
                printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                system("pause");
        }
    }
    system("cls");
    printf("\n\n\t\t���ʽ��������������\n\n");
    getch();
    lmain();
    return;
}

//������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
int main() {
    lmain();//���˵�
    return 0;
}

