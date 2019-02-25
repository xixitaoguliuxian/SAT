//
//  literal_clauses.c
//  SAT2
//
//  Created by 嘻嘻桃谷六仙 on 2019/2/19.
//  Copyright © 2019年 嘻嘻桃谷六仙. All rights reserved.
//

#include "literal_clauses.h"
#include <stdlib.h>
assign_info *assign;
literal linfo[MAX_VARS] [2];
clause *clauses;
int n_clause/*原来的子句数目*/, r_clauses/*现在的子句数目*/;
int vars;
extern int *gucl_stack;//储存单子句
extern int n_gucl;//上面的大小
int CreatClause (char *filename)//用来建立储存子句和文字信息的数据结构
{
    int count1 = 1;
    int count2 = 1;
    int temp_literal;//读入的文字
    FILE *in = fopen(filename, "r");
    if (in == NULL){
        printf("输入错误\n");
        return ERROR;
    }
    char c;
    int ALL_VAR,ALL_CLAUSES;
    while(1){
        c = getc(in);
        if(c == 'p') break;
    }
    c = getc(in);
    c = getc(in);
    c = getc(in);
    c = getc(in);
    fscanf(in,"%d %d",&ALL_VAR,&ALL_CLAUSES);//ALL_VAR表示总共的文字的数目 ALL_CLAUSES代表总的子句数字
    n_clause = ALL_CLAUSES;
    r_clauses = ALL_CLAUSES;
    vars = ALL_VAR;
    assign = (assign_info *)malloc(sizeof(assign_info)*(ALL_VAR+1));//assign数组用于储存所有的文字的赋值状态
    gucl_stack = (int *)malloc(sizeof(int)*(ALL_VAR));// gucl_stack用于储存单子句所包含的唯一的文字
    //初始化所有文字的赋值状态
    for (int i = 1; i<=ALL_VAR; i++)
    {
        assign[i].decision = UNASSIGNED;
        assign[i].type = SATISFIED;
    }
    //初始化数组
    for(int i = 1; i <= ALL_VAR ; i++)
    {
        linfo[i][0].is_assigned = NO;
        linfo[i][0].n_occur = 0;
        linfo[i][0].included_clause = (lit_in_clause *)malloc(sizeof(lit_in_clause));
        linfo[i][0].headp_clause = linfo[i][0].included_clause;
        linfo[i][0].locs = (lit_in_clause_locs *)malloc(sizeof(lit_in_clause_locs));
        linfo[i][0].headp_locs =  linfo[i][0].locs;
        linfo[i][1].is_assigned = NO;
        linfo[i][1].n_occur = 0;
        linfo[i][1].included_clause = (lit_in_clause *)malloc(sizeof(lit_in_clause));
        linfo[i][1].headp_clause = linfo[i][1].included_clause;
        linfo[i][1].locs = (lit_in_clause_locs *)malloc(sizeof(lit_in_clause_locs));
        linfo[i][1].headp_locs =  linfo[i][1].locs;
        
    }
    //初始化子句
    clauses = (clause *)malloc(sizeof(clause)*(ALL_CLAUSES+1));
    for (int i=1; i<=ALL_CLAUSES; i++) {
        clauses[i].all_literals = (literals *)malloc(sizeof(literals));
        clauses[i].headp_literal = clauses[i].all_literals;
        clauses[i].is_satisfied = NO;
        clauses[i].original_length = 0;
        clauses[i].current_length = 0;
        clauses[i].current_ucl = NO;
     //  clauses[i].binary_code = 1;
    }
    while(count2 <= ALL_CLAUSES)//当读取的行数少于子句数时 继续读
    {
        fscanf(in, "%d",&temp_literal);
        while(temp_literal != 0)
        {
           //更新文字数组
            if(temp_literal > 0)
            {
                linfo[temp_literal][1].included_clause->data = count2;
                linfo[temp_literal][1].included_clause->nextone = (lit_in_clause *)malloc(sizeof(lit_in_clause));
                lit_in_clause * piovt1 = linfo[temp_literal][1].included_clause->nextone;
                linfo[temp_literal][1].included_clause = piovt1;
                linfo[temp_literal][1].locs->data = count1;
                linfo[temp_literal][1].locs->nextone = (lit_in_clause_locs *)malloc(sizeof(lit_in_clause_locs));
                lit_in_clause_locs * pivot2 = linfo[temp_literal][1].locs->nextone;
                linfo[temp_literal][1].locs = pivot2;
                linfo[temp_literal][1].n_occur ++;
                
            }
            else
            {
                linfo[(0-temp_literal)][0].included_clause->data = count2;
                linfo[(0-temp_literal)][0].included_clause->nextone = (lit_in_clause *)malloc(sizeof(lit_in_clause));
                lit_in_clause * piovt1 = linfo[(0-temp_literal)][0].included_clause->nextone;
                linfo[(0-temp_literal)][0].included_clause = piovt1;
                linfo[(0-temp_literal)][0].locs->data = count1;
                linfo[(0-temp_literal)][0].locs->nextone = (lit_in_clause_locs *)malloc(sizeof(lit_in_clause_locs));
                lit_in_clause_locs * pivot2 = linfo[(0-temp_literal)][0].locs->nextone;
                linfo[(0-temp_literal)][0].locs = pivot2;
                linfo[(0-temp_literal)][0].n_occur ++;
            }
            //更新子句链表
            clauses[count2].all_literals->data = temp_literal;
            clauses[count2].all_literals->nextone = (literals *)malloc(sizeof(literals));
            literals * pivot3 = clauses[count2].all_literals->nextone;
            clauses[count2].all_literals = pivot3;
            clauses[count2].current_length ++;
            clauses[count2].original_length ++;
            count1++; //子句的长度
            fscanf(in, "%d",&temp_literal);
         }
        //用于标记单子句并储存单子句所包含的唯一的文字 将单子句包含的文字加入gucl_stck中
        if(clauses[count2].original_length == 1) {
            clauses[count2].current_ucl = clauses[count2].headp_literal->data;
            gucl_stack[n_gucl] = clauses[count2].headp_literal->data;
            n_gucl++;
        }
        count1 = 1;
        count2++;//子句的序列数
    }

    printf("链表创建成功！\n");
    //用于输出结构的建立情况
    for (int i = 1; i <= ALL_CLAUSES; i++) {
        printf("第%d行    " ,i);
        literals* p =  clauses[i].headp_literal;
        for (int j = 0;j < clauses[i].current_length;j++)
        {
            printf("%d ", p->data);
            literals* q = p->nextone;
            p = q;


        }
        printf("\n");
    }
    for(int i = 1; i<= ALL_VAR;i++){
    printf("第%d个文字出现在了下列子句中： " ,i);
    lit_in_clause * p = linfo[i][1].headp_clause;
    lit_in_clause_locs * q =linfo[i][1].headp_locs;
    if(linfo[i][1].n_occur>0){
     for (int j = 0; j< linfo[i][1].n_occur; j++) {
        printf("第%d句的第%d个位置 " , p->data,q->data);
        lit_in_clause * m = p->nextone;
        p = m;
        lit_in_clause_locs * n =  q->nextone;
        q = n;
    }

    }
        printf("\n");
    }
    for(int i = 1; i<= ALL_VAR;i++){
        printf("第%d个负文字出现在了下列子句中： " ,i);
        lit_in_clause * p = linfo[i][0].headp_clause;
        lit_in_clause_locs * q =linfo[i][0].headp_locs;
        if(linfo[i][0].n_occur>0){
            for (int j = 0; j< linfo[i][0].n_occur; j++) {
                printf("第%d句的第%d个位置 " , p->data,q->data);
                lit_in_clause * m = p->nextone;
                p = m;
                lit_in_clause_locs * n =  q->nextone;
                q = n;
            }

        }
        printf("\n");
   }
        
    fclose(in);
    return OK;
}

void put_the_ans(int number)
{
    int i = 1;
    for (i=1; i<=number; i++)
    {
     if(assign[i].type == SATISFIED)
     {
         printf("第%d个文字的真值为      %d\n" ,i,i);
     }
     else if(assign[i].type == SHRUNK)
     {
         printf("第%d个文字的真值为      %d\n" ,i,(0-i));
    }
    
    }
    printf("---------------答案输出完毕---------------\n");
}
void check_the_ans ()
{
    int flag = 0;
    for (int i = 1 ; i <= n_clause; i ++) {
        flag = 0;
        printf("第%d句的真值为：" ,i);
        literals * pivot1 = clauses[i].headp_literal;
        for (int j= 0; j < clauses[i].original_length; j++)
        {
            if(assign[abs(pivot1->data)].type == 1)
            {
                if (pivot1->data >0)
                {
                    flag = 1;
                    printf("(%d)1  " ,pivot1->data );
                }
                else printf("(%d)0  " ,pivot1->data );
            }
            else
            {
                if (pivot1->data > 0)  printf("(%d)0  " ,pivot1->data );
                else
                {
                    printf("(%d)1  " ,pivot1->data );
                    flag = 1;
                }
            }
             pivot1 = pivot1->nextone;
        }
        if(flag) printf("   1");
        else  printf("   0");
        printf("\n");
    }
}

void put_the_ans_intofile(int number)
{
    char filename[200];
    printf("请输入你想要新建的文件名：\n");
    scanf("%s",filename);
    FILE *in = fopen(filename, "w");
    int i = 1;
    for(i=1;i<=number;i++)
    {
        
        if(assign[i].type == SATISFIED) fprintf(in, "%d  ",i);
        else fprintf(in, "%d",-i);
        if ((i % 5) == 0) fprintf(in, "\n");
    }
    printf("求解成功\n");
    fclose(in);
}

