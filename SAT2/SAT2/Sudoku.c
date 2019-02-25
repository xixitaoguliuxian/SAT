//
//  Sudoku.c
//  SAT2
//
//  Created by 嘻嘻桃谷六仙 on 2019/2/24.
//  Copyright © 2019年 嘻嘻桃谷六仙. All rights reserved.
//

#include "Sudoku.h"

extern int *gucl_stack;//储存单子句
extern int n_gucl;//上面的大小
extern int vars;
extern assign_info *assign;
extern literal linfo[MAX_VARS] [2]; //二维数组 第一个是文字的绝对值 第二个是文字的类型
extern clause *clauses;
extern int n_clause/*原来的子句数目*/, r_clauses/*现在的子句数目*/;
extern change_info changes[MAX_VARS];
extern unsigned int changes_index;
extern unsigned int n_changes[MAX_VARS][2];
void create_cnf(char* filename)
{
    int i;
    printf("请输入你想要进行数独的形式：\n");
    printf("自行输入数独表 1（用.代表未填入数字） 从文件中读取 2\n");
    scanf("%d", &i);
    int a[50];
    int row[9][9];
    int count1 = 0;
    char c;
    char filename3[200];
    switch (i)
    {
        case 1:
            for (int x = 0; x < 9; x++)
            {
            for(int y = 0;y < 9; y++ )
            {
                c = getchar();
                if(c == '.')continue;
                else
                {
                    a[count1] = x*100+y*10+(int)c-(int)'0';
                    count1++;
                    row[x][y] = x*100+y*10+(int)c-(int)'0';
                    
                }
            }
                getchar();
            }
            break;
        case 2:
            printf("请输入文件名：\n");
            scanf("%s",filename3);
            FILE *in = fopen(filename3, "r");
            for (int x = 0; x < 9; x++)
            {
                for(int y = 0;y < 9; y++ )
                {
                    c = getc(in);
                    if(c == '.')continue;
                    else
                    {
                        a[count1] = x*100+y*10+(int)c-(int)'0';
                        count1++;
                        row[x][y] = x*100+y*10+(int)c-(int)'0';
                        
                    }
                }
                getc(in);
            }
            fclose(in);
            break;
        default:
            printf("输入错误！");
            break;
    }
    
   
    FILE *out = fopen(filename, "w");
    //每一个元素在每一列都至少出现一次
    fprintf(out, "p cnf 889");
    fprintf(out, " %d\n" , (count1+5103));
    for (int y = 0; y < 9; y++)
    {
        
        for (int n = 1; n<=9; n++)
        {
//            int flag = 0;
//            for (int i = 1; i <=9; i++)
//            {
//                if(row[i][y]==n)
//                {
//                    flag = 1;
//                    break;
//                }
//            }
//            if (flag) continue;
            for (int x = 0; x < 9; x++)
            {
                fprintf(out,"%d ", x*100+y*10+n);
            }
        }
        fprintf(out, "\n");
    }
    //每一个元素在每一行都至少出现一次
    for (int x = 0; x < 9; x++)
    {
        for (int n = 1; n<=9; n++)
        {
//            int flag = 0;
//            for (int i = 1; i <=9; i++)
//            {
//                if(row[x][i]==n)
//                {
//                    flag = 1;
//                    break;
//                }
//            }
//            if (flag) continue;
            for (int y = 0; y < 9; y++)
            {
                fprintf(out,"%d ", x*100+y*10+n);
            }
        }
        fprintf(out, "\n");
    }
    //每个元素在每一个3*3格子中都要出现一次
    for (int r= 0; r <3; r++)
    {
        for (int s = 0; s<3; s++) {
            for (int n = 1; n<=9; n++) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j< 3; j++) {
                        fprintf(out, "%d " ,(3*r+i)*100+(3*s+j)*10+n);
                    }
                }
                fprintf(out, "\n");
            }
        }
    }
    //每个格子只含有一个数字
    for (int i = 0; i< 9; i++) {
        for (int j = 0; j< 9; j++) {
            for (int n = 1; n <9; n++) {
                for (int m = n+1; m<=9; m++) {
                    fprintf(out, "%d ",-(i*100+j*10+n));
                    fprintf(out, "%d" , -(i*100+j*10+m));
                    fprintf(out, "\n");
                }
            }
        }
    }
    for (int i = 0; i < count1 ; i++) {
        fprintf(out, "%d ",a[i]);
        fprintf(out, "\n");
    }
    fclose(out);
}

void ans_Sudoku()
{
    for (int x = 0; x< 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            for(int n = 1; n <=9; n++)
            {
                if(assign[x*100+y*10+n].decision == YES) printf("%d " ,n);
            }
            
        }
        printf("\n");
    }
}

void Sudoku()
{
    char filename2[200];
    printf("请输入你想写入cnf文件的文件名：  \n");
    scanf("%s" ,filename2);
    create_cnf(filename2);
    if(CreatClause(filename2)) printf("成功将Sudoku转换成SAT问题!\n");
    gucl_stack = NULL;//储存单子句
    n_gucl = 0;//上面的大小
    if(dpll()) printf("计算成功!\n");
    printf("答案为：\n");
    ans_Sudoku();
    printf("输出完毕\n");
}
