#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 单链表节点
typedef struct LNode
{
    int Sno, score;
    char name[20];
    struct LNode *next;
} LNode;

void printTitle()
{
    printf("\n----------------- Student Score Query System -----------------\n\n");
    printf("1.Show the scores of all students.\n");
    printf("2.Insert the record of a student's score.\n");
    printf("3.Delete the record of a student's score.\n");
    printf("4.Modify the record of a student's score.\n");
    printf("5.Show the score of a given student.\n");
    printf("6.Show student who has achieved a given score.\n");
    printf("0.Quit.\n");
    printf("\nPlease input the number of the operation you want to perform: ");
}

// 链表排序

// 获取总行数
int countLines(FILE *file)
{   
    int line_num = 0;
    char strLine[50];
    rewind(file);
    while (fgets(strLine, 50, file))
    {
        line_num++;
    }
    rewind(file);
    return line_num;
}

// 导入学生成绩
LNode *importData(LNode *LinkList)
{
    LinkList = (LNode*)malloc(sizeof(LNode));
    LNode *p = LinkList, *q = LinkList;
    FILE *fp = fopen("test.txt", "r");
    int i, Sno, score, N = countLines(fp);
    char name[20] = {};
    for (i = 0; i < N; i++)
    {
        q = (LNode*)malloc(sizeof(LNode));
        fscanf(fp, "%d\t%s\t%d\n", &Sno, name, &score);
        q->Sno = Sno;
        strcpy(q->name, name);
        q->score = score;
        p->next = q;
        p = q;
    }
    p->next = NULL;
    fclose(fp);
    return LinkList;
}

// 保存学生成绩
LNode *saveData(LNode *LinkList)
{
    FILE *fp = fopen("test.txt", "w");
    LNode *p = LinkList->next;
    while (p != NULL)
    {
        fprintf(fp, "%d\t%s\t%d\n", p->Sno, p->name, p->score);
        p = p->next;
    }
    fclose(fp);
    return LinkList;
}

// 1.显示学生成绩表
void printTable(LNode *LinkList)
{
    LNode *p = LinkList;
    FILE *fp = fopen("test.txt", "r");
    int i, N = countLines(fp);
    p = LinkList->next;
    while (p != NULL)
    {
        printf("%d\t%s\t%d\n", p->Sno, p->name, p->score);
        p = p->next;
    }
    fclose(fp);
}

// 2.插入一条记录
void insert(LNode *LinkList)
{
    int Sno, score, flag, temp;
    char name[20] = {};
    LNode *q, *p = (LNode*)malloc(sizeof(LNode));
    p->next = LinkList->next;
    LinkList->next = p;
    do       // 保证该学生不存在
    {
        printf("Please input Student Number: ");
        scanf("%d", &temp);
        q = LinkList->next;
        flag = 0;
        while (q != NULL)
        {
            if (q->Sno == temp)
            {
                flag = 1;
                printf("Wrong Student Number!\n");
                break;
            }
            q = q->next;
        }
    } while (flag);
    p->Sno = temp;
    printf("Please input Name: ");
    scanf("%s", p->name);
    printf("Please input Score: ");
    scanf("%d", &p->score);
    saveData(LinkList);
    printf("Insert Complete!");
}

// 3.删除一条记录
void delete(LNode *LinkList)
{
    int temp, flag;
    LNode *q;
    do       // 保证该学生存在
    {
        printf("Please input Student Number: ");
        scanf("%d", &temp);
        q = LinkList;
        flag = 1;
        while (q->next != NULL)
        {
            if (q->next->Sno == temp)
            {
                flag = 0;
                break;
            }
            q = q->next;
        }
        if (!flag)
        {
            break;
        }
        printf("Student not exist!\n");
    } while (flag);
    q->next = q->next->next;
    saveData(LinkList);
    printf("Delete Complete!");
}

// 4.修改一条记录
void modify(LNode *LinkList)
{
    int temp, flag;
    LNode *q;
    do       // 保证该学生存在
    {
        printf("Please input Student Number: ");
        scanf("%d", &temp);
        q = LinkList->next;
        flag = 1;
        while (q != NULL)
        {
            if (q->Sno == temp)
            {
                flag = 0;
                break;
            }
            q = q->next;
        }
        if (!flag)
        {
            break;
        }
        printf("Student not exist!\n");
    } while (flag);
    printf("Please input score: ");
    scanf("%d", &q->score);
    saveData(LinkList);
    printf("Modify Complete!");
}

// 5.查看指定学生的成绩
void showScoreOfStu(LNode *LinkList)
{
    int operation, temp, flag;
    char NAME[20] = {};
    LNode *q;
    while (1)
    {
        printf("1.Student Number\t\t2.Name\n");
        printf("(Input 1 or 2) Search by:");
        scanf("%d", &operation);
        if (operation == 1)       // 通过学号
        {
            do       // 保证该学生存在
            {
                printf("Please input Student Number: ");
                scanf("%d", &temp);
                q = LinkList->next;
                flag = 1;
                while (q != NULL)
                {
                    if (q->Sno == temp)
                    {
                        flag = 0;
                        break;
                    }
                    q = q->next;
                }
                if (!flag)
                {
                    printf("%d\t%s\t%d\n", q->Sno, q->name, q->score);
                    break;
                }
                printf("Student not exist!\n");
            } while (flag);
            break;
        }
        else if (operation == 2)       // 通过姓名
        {
            do       // 保证该学生存在
            {
                printf("Please input name: ");
                scanf("%s", NAME);
                q = LinkList->next;
                flag = 1;
                while (q != NULL)
                {
                    if (strcmp(q->name, NAME) == 0)
                    {
                        flag = 0;
                        break;
                    }
                    q = q->next;
                }
                if (!flag)
                {
                    printf("%d\t%s\t%d\n", q->Sno, q->name, q->score);
                    break;
                }
                printf("Student not exist!\n");
            } while (flag);
            break;
        }
        else
        {
            printf("Wrong operation!");
        }
        
    }
}

// 6.查看分数为指定成绩的学生（规定满分为100分）
void showStuGetScore(LNode *LinkList)
{
    int s, flag = 1;
    LNode *p = LinkList->next;
    while (1)
    {
        printf("Please input score: ");
        scanf("%d", &s);
        if (s >= 0 && s <= 100)
        {
            break;
        }
        else
        {
            printf("Score should in the range from 0 to 100!\n");
        }
    };
    while (p != NULL)
    {
        if (p->score == s)
        {
            printf("%d\t%s\t%d\n", p->Sno, p->name, p->score);
            flag = 0;
        }
        p = p->next;
    };
    if (flag)
    {
        printf("No student's score is %d.\n", s);
    }
}

int main()
{
    LNode *LinkList;
    int operation = 0;
    LinkList = importData(LinkList);
    while(1)
    {
        printTitle();
        scanf("%d", &operation);
        switch(operation)
        {
            case 0: return 0;
            case 1: printTable(LinkList); break;
            case 2: insert(LinkList); break;
            case 3: delete(LinkList); break;
            case 4: modify(LinkList); break;
            case 5: showScoreOfStu(LinkList); break;
            case 6: showStuGetScore(LinkList); break;
            default: printf("Wrong operation!\n"); break;
        }
        system("pause");
    }
}