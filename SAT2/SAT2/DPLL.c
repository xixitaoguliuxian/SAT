//
//  DPLL.c
//  SAT2
//
//  Created by 嘻嘻桃谷六仙 on 2019/2/19.
//  Copyright © 2019年 嘻嘻桃谷六仙. All rights reserved.
//

#include "DPLL.h"
int *gucl_stack = NULL;//储存单子句
int n_gucl = 0;//上面的大小
extern int vars;
extern assign_info *assign;
extern literal linfo[MAX_VARS] [2]; //二维数组 第一个是文字的绝对值 第二个是文字的类型
extern clause *clauses;
extern int n_clause/*原来的子句数目*/, r_clauses/*现在的子句数目*/;
extern change_info changes[MAX_VARS];
extern unsigned int changes_index;
extern unsigned int n_changes[MAX_VARS][2];



//void Test(){
//    int flag=0;
//    for (int i = 1; i <= n_clause; i++) {
//        flag=0;
//        printf("第%2d行    " ,i);
//        printf("该句是否可满足 %d " ,clauses[i].is_satisfied);
//        printf("该句目前长度为 %d",clauses[i].current_length);
//        literals* p =  clauses[i].headp_literal;
//        for (int j = 0;j < 3;j++)
//        {
//            printf("%4d", p->data);
//            if (linfo[abs(p->data)][p->data > 0 ? 1 : 0].is_assigned>0) {
//                if((p->data >0 && assign[abs(p->data)].type)||(p->data <0 && assign[abs(p->data)].type== 0) ){
//                    printf("真值为1 ");
//                    flag=1;}
//                else  printf("真值为0 ");
//
//            } else {
//                printf("未赋值  ");
//            }
//            printf("%d",linfo[abs(p->data)][p->data > 0 ? 1 : 0].is_assigned);
//
//            literals* q = p->nextone;
//            p = q;
//
//
//        }
//        printf("该句真值为：%d ",flag);
//
//
//        printf("\n");
//    }
//}


int SetVar (int v)
{
    int p = abs(v) ,q = v >0 ? SATISFIED :SHRUNK; //p是将v转换成正数 q是v的类型 其为正的话 类型是SATISFID 为负的话类型是SHRUNK
    lit_in_clause * pivot1 = linfo[p][q].headp_clause; //pivot1指向包括该文字的句子
    lit_in_clause * pivot2 = NULL;//中间指针
    linfo[p][q].is_assigned = YES; //将该文字的赋值情况改成被赋值
    assign[p].decision = ASSIGN_IMPLIED; //将记录答案的数组的该文字的情况改成被赋值
    assign[p].type = q;//记录下该文字被赋值的类型
    for (int i = 0; i < linfo[p][q].n_occur; i++) //将包含该文字的子句状态改成可满足
    {
        int t = pivot1->data; //t是子句的序列号
        if (clauses[pivot1->data].is_satisfied == YES)//如果该子句原来就已经满足了 跳过
        {
            pivot2 = pivot1->nextone;//指针指向下一个包含该文字的子句的序列好
            pivot1 = pivot2;
            continue;
        }
        //记录下操作带来的影响
        changes[changes_index].literal_index = v; //记录下改变的文字
        changes[changes_index].type = 1; //记录下改变的类型 1 代表是将含该文字的子句状态改成了可满足
        changes[changes_index].clause_index = t; //记录下改变的子句的序列好
        changes_index++; //改变的计数加一
        clauses[pivot1->data].is_satisfied = YES; //将该子句状态改成可满足
        --r_clauses; //不可满足的子句的数目减一
        pivot2 = pivot1->nextone; //指针指向下一个子句序列号
        pivot1 = pivot2;
    }
    q = !q;
    linfo[p][q].is_assigned = YES; //将该文字的负文字的状态改成被赋值
    pivot1 = linfo[p][q].headp_clause; //指针指向包含该文字的子句的序列号
    pivot2 = NULL;//中间过渡指针
    //将含有该负文字的子句的长度减一
    for (int i = 0 ; i< linfo[p][q].n_occur; i++)
    {
        int index = pivot1->data;//含该文字的序列号
        pivot2 = pivot1->nextone;//指向下一个
        pivot1 =pivot2;
        if( clauses[index].is_satisfied == YES) continue; //如果该子句状态为可满足 不进行操作
        changes[changes_index].literal_index = v;//记录下改变的文字
        changes[changes_index].type = 0; // 记录下改变的类型 0 代表 将含该文字的负文字的子句长度减一
        changes[changes_index].clause_index = index; //记录下改变的子句的序列号
        changes_index++; //改变的计数加一
        --clauses[index].current_length;//减少该子句的长度
        if(clauses[index].current_length == 1 ) //如果该子句的长度变成了1 说明此时出现了单子句
        {
            literals * pivot3 = clauses[index].headp_literal; //该指针指向该子句包含的文字的链表
            literals * pivot4 = NULL;//中间过渡指针
            while (linfo[abs(pivot3->data)][pivot3->data > 0 ? SATISFIED : SHRUNK].is_assigned ==YES)//因为长度为1 则说明 一定出现了一个还没有被赋值的文字 找到该文字
            {  
                pivot4 = pivot3->nextone;
                pivot3 = pivot4;
            }
            int flag1 = 1;//标记该单子句是否在还没有没处理的单子句之中
            for (int j = 0; j < n_gucl; j++) {
                if( gucl_stack[j] == pivot3->data)
                {
                    flag1 = 0;
                    break;//如果出现了 则不需要将其重复放入储存单子句的数组中
                }
                if( gucl_stack[j] == -pivot3->data) return UNSAT; //如果此时出现的单子句和待处理的单子句所包含的文字相反 则说明出现了矛盾的单子句 此时 不可满足
            }
            if (flag1)//如果 这是新出现的单子句
            {
                clauses[index].current_ucl = pivot3->data; //将该唯一未被赋值的文字储存起来
                gucl_stack[n_gucl] = pivot3->data; //将该文字放入存放单子句的数组之中
                n_gucl++;//单子句的数目加一
            }
            
        }
        if(clauses[index].current_length == 0) return UNSAT; //如果出现了长度为0的不可满足的子句 则说明错误
    }
    return OK; //操作完毕
}
void UnVar(int m)
{
    int n = changes_index - m;
    for (int j = 0; j < n; j++)
    {
        assign[abs(changes[m+j].literal_index)].decision = ASSIGN_NONE;
        if(changes[m+j].type == 1)//说明该变化是由于将文字所在的句子变为真值的操作
        {
            linfo[abs(changes[m+j].literal_index)][changes[m+j].literal_index > 0 ? SATISFIED : SHRUNK].is_assigned = NO; //将该文字变成没有被赋值
            clauses[changes[m+j].clause_index].is_satisfied = NO; //将因其而变为可满足的句子变成不可满足
            r_clauses++;//不可满足的子句数目增加
        }
        else//说明该变化是由于将假文字所在的句子长度加回来
        {
            linfo[abs(changes[m+j].literal_index)][changes[m+j].literal_index < 0 ? SATISFIED : SHRUNK].is_assigned = NO; //将该负文字变成没有被赋值
            clauses[changes[m+j].clause_index].current_length++; //将因为该文字而是句子长度缩短的句子增长
        }
    }
    changes_index = m; //将改变的序号回到dpll之前
    n_gucl = 0; //此时单子句的数目为0
}
int GetLiteralDLCS(void)
{
    int i , j, C;
    unsigned int max = 0 , r , s, t;
    int u = 0;
    for (i=1; i<= vars; i++)
    {
        if (assign[i].decision == ASSIGN_NONE)
        {
            t = 0;
            s = 0;
            for (j=0; j<linfo[i][SATISFIED].n_occur; j++)
            {
                
                lit_in_clause * pivot = linfo[i][SATISFIED].headp_clause;
                for (int m = 0; m<j; m++) {
                    pivot = pivot->nextone;
                }
                C = pivot->data;
                s += 1 - clauses[C].is_satisfied;
                
            }
            for(j = 0; j< linfo[i][SHRUNK].n_occur; j++)
            {
                
                lit_in_clause * pivot = linfo[i][SHRUNK].headp_clause;
                for (int m = 0; m < j; m++)
                {
                    pivot = pivot->nextone;
                }
                C = pivot->data;
                t += 1 - clauses[C].is_satisfied;
                
            }
            r = s + t;
            if (r > max) {
                max = r;
                if (s>=t) u = i;
                else u = -i;
            }
        }
    }
    return u;
}

int dpll()
{
    while(n_gucl > 0)//n_gucl记录的是单子句的数目
    {
        n_gucl --;
        int k = SetVar(gucl_stack[n_gucl]);
        //如果按照单子句规则将 出现了为空的子句 则说明错误
        if(k == 0) {n_gucl=0; return UNSAT;}
    }
   // printf("\n");
    if (r_clauses == 0) return  SAT; //当未被赋值的句子等于0时 说明全部赋值完毕
    unsigned int choice = 1;
    //选择策略 从头开始找 直到找到未被赋值的 且在子句中出现的文字
//    while (1)
//    {
//        if(linfo[choice][1].is_assigned == NO && (linfo[choice][1].n_occur >0 ||linfo[choice][0].n_occur >0)) break;
//        choice ++;
//    }
//    if(linfo[choice][1].n_occur == 0) choice = -choice;
    choice = GetLiteralDLCS();
    int m = changes_index; //记下在下面开始之前的记录变化的序号
    //printf("给%d赋值了\n" ,choice);
   int k = SetVar(choice);//因为之前已经按照单子句规则化简了 所以不可能出现 空子句 但是可能出现矛盾的句子
   if(k==0)
   {
       UnVar(m);
       k = SetVar(-choice);
       if(k==0)
       {
           UnVar(m);
           return UNSAT;
       }
       if (dpll()) return SAT;
       else
       {
           UnVar(m);
           return UNSAT;
       }
    }
 //   Test();
   else {
       
    if(dpll())
        return SAT;
    else
        {
            UnVar(m);
            k = SetVar(-choice);
            if(k==0)
            {
                UnVar(m);
                return UNSAT;
            }
            if(dpll()) return SAT;
            else
            {
                UnVar(m);
                return  UNSAT;
           }
        }
   }
//    }
    return UNSAT;
}
