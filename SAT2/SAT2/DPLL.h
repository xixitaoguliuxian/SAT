//
//  DPLL.h
//  SAT2
//
//  Created by 嘻嘻桃谷六仙 on 2019/2/19.
//  Copyright © 2019年 嘻嘻桃谷六仙. All rights reserved.
//

#ifndef DPLL_h
#define DPLL_h

#include <stdio.h>
#include <stdlib.h>
#include "literal_clauses.h"
#include "Branching rules.h"
#define UNSAT 0
#define SAT 1

int SetVar(int v);
void UnSetVar (int v);
int dpll(void);
int GetLiteralDLCS(void);
#endif /* DPLL_h */
