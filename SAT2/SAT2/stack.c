//
//  stack.c
//  SAT2
//
//  Created by 嘻嘻桃谷六仙 on 2019/2/19.
//  Copyright © 2019年 嘻嘻桃谷六仙. All rights reserved.
//

#include "stack.h"
 
change_info changes[MAX_VARS];//用于储存每一步对结构所造成的影响
unsigned int changes_index = 0;

