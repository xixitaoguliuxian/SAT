//
//  literal_clauses.h
//  SAT2
//
//  Created by 嘻嘻桃谷六仙 on 2019/2/19.
//  Copyright © 2019年 嘻嘻桃谷六仙. All rights reserved.
//

#ifndef literal_clauses_h
#define literal_clauses_h

#include <stdio.h>
#include "stack.h"
#define YES 1
#define NO  0
#define TRUE 1
#define FALSE 0
#define SATISFIED 1
#define SHRUNK 0

#define UNASSIGNED 0
#define ASSIGN_IMPLIED 1
#define ASSIGN_NONE 0
#define ERROR 0
#define OK 1
typedef struct lit_in_clause //储存与每个文字相关联的子句序列的链表结构
{
    struct lit_in_clause * nextone;
    int data;
}lit_in_clause;

typedef struct lit_in_clause_locs//储存与每个文字在其相关联的子句的位置链表结构
{
    struct lit_in_clause_locs * nextone;
    int data;
}lit_in_clause_locs;

typedef struct literal
{
    int is_assigned;
    int n_occur;
    lit_in_clause * headp_clause;//指向储存含该文字的子句序列号的链表的头指针
    lit_in_clause * included_clause; //中间过渡指针 可忽略
    lit_in_clause_locs *headp_locs;//指向储存与每个文字在其相关联的子句的位置链表结构的头指针
    lit_in_clause_locs * locs;////中间过渡指针 可忽略
}literal;
typedef struct literals//储存了子句中所包含的文字链表的结构
{
    int data;
    struct literals * nextone;
}literals;

typedef struct clause
{
    literals * all_literals;////中间过渡指针 可忽略
    literals * headp_literal;//指向储存该子句中所有的文字的头指针
    int current_length;//该子句现在的长度
    int original_length;//该子句原本的长度
    int is_satisfied;//该子句可满足时为1（YES）
    int current_ucl;//单子句时储存唯一的未被赋值的文字 否则为0
}clause;

typedef struct assign_info//储存了所有的元素的赋值情况
{
    int type;//文字为SATISFIED代表赋值为正 or SHRUNKK 代表赋值为负
    int decision;//是否被赋值
} assign_info;

int CreatClause (char *filename);
void put_the_ans (int number);
void check_the_ans(void);

#endif /* literal_clauses_h */
