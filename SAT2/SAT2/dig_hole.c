//
//  dig_hole.c
//  SAT2
//
//  Created by 嘻嘻桃谷六仙 on 2019/2/25.
//  Copyright © 2019年 嘻嘻桃谷六仙. All rights reserved.
//

#include "dig_hole.h"
#include "DPLL.h"
extern int *gucl_stack ;//储存单子句
extern int n_gucl ;
int a[9];
void creat_the_ans(int n )
{
    int block[9][9];
    for (int i = 0 ; i < 9; i++)
    {

        int row = rand() % 10;
        int colum = rand() % 10;
        if (block[row][colum] != 0) {
            row = rand() % 10;
        }
        block[row][colum] = row*100+colum*10+i;
        a[i] = row*100+colum*10+i;
    }
    FILE *out = fopen("/Users/xixitaoguliuxian/Desktop/Sudoku.txt", "w");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j< 9 ; j++)
        {
            if(block[i][j]!=0)fprintf(out, "%d", block[i][j]%10);
            else fprintf(out, ".");

        }
        fprintf(out,"\n");
    }
    //每一个元素在每一列都至少出现一次
    fprintf(out, "p cnf 889");
    fprintf(out, " %d\n" , (9+5103));
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
    for (int i = 0; i < 9 ; i++) {
        fprintf(out, "%d ",a[i]);
        fprintf(out, "\n");
    }
    fclose(out);
    gucl_stack = NULL;//储存单子句
    n_gucl = 0;//上面的大小
    if(CreatClause("/Users/xixitaoguliuxian/Desktop/Sudoku.txt")&&dpll()){}
        
        }
    

