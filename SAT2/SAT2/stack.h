//
//  stack.h
//  SAT2
//
//  Created by 嘻嘻桃谷六仙 on 2019/2/19.
//  Copyright © 2019年 嘻嘻桃谷六仙. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include <stdio.h>
#define MAX_CLAUSES 5000
#define MAX_VARS 20000

typedef struct  change_info{
    int type;//1代表赋值使其所在的句子为真 0 代表将该文字的负文字在句子中标记
    int clause_index;//改变的句子的编号
    int literal_index;
}change_info;




#endif /* stack_h */
