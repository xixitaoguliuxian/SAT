//
//  main.c
//  SAT2
//
//  Created by 嘻嘻桃谷六仙 on 2019/2/19.
//  Copyright © 2019年 嘻嘻桃谷六仙. All rights reserved.
//

#include <stdio.h>
#include "DPLL.h"
#include "Sudoku.h"
extern int n_clause;
extern int vars;

int main(int argc, const char * argv[])
{
    int k;
    char filename4[200];
    printf("------------------基于SAT的数独游戏求解程序--------------------\n");
    printf("------------------1 SAT   2 求解已知Sudoku   3 生成新的Sudoku错误  4 优化后的SAT   5 exit----------------\n");
    scanf("%d" ,&k);
    switch (k)
    {
        case 1:
            printf("请输入你想要验证的文件名\n");
            scanf("%s",filename4);
            CreatClause(filename4);
            if(dpll())
            {
                int n= 0;
                put_the_ans(vars);
                printf("是否需要检验答案？ 需要 1 不需要 0\n ");
                scanf("%d" , &n);
                if (n)
                {
                    check_the_ans();
                }
            }
            else
                printf("UNSAT\n");
            break;
        case 2:
            Sudoku();
            break;
        case 3:
            return 0;
            break;
        case 4:
            break;
        case 5:
            return 0;
        default:
            printf("输入错误，请重新输入\n");
            break;
    }
    
//    put_the_ans (vars);
//    else printf("UNSAT\n");
//    SetVar(-15);
//    check_the_ans();
//
    return 0;
}
