//
//  preprocess.h
//  SAT2
//
//  Created by 嘻嘻桃谷六仙 on 2019/2/19.
//  Copyright © 2019年 嘻嘻桃谷六仙. All rights reserved.
//

#ifndef preprocess_h
#define preprocess_h

#include <stdio.h>
//int SetVar(int v)//computes F|v
//{
//    int i;
//    int p = abs(v), q = (v>0) ? SATISFIED : SHRUNK ;
//    lit_in_clause *pivot;
//    linfo[p][q].is_assigned = YES;
//    pivot = linfo[p][q].headp_clause;
//    if(linfo[p][q].n_occur>0)
//    {
//    for(i=0;i < linfo[p][q].n_occur;i++)
//    {
//        int j = pivot->data;
//        lit_in_clause * a = pivot->nextone;
//        pivot = a;
//        if(clauses[j].is_satisfied)continue;
//        clauses[j].is_satisfied = YES;
//        --r_clauses;
//        changes[changes_index++].clause_index = j;
//        n_changes[depth][SATISFIED]++;
//    }
//    }
//    assign[p].type = q;
//    assign[p].depth = depth;
//    assign[p].decision = ASSIGN_IMPLIED;
//    q = (v< 0) ? SATISFIED : SHRUNK ;
//    //去掉包含该文字但是为非的
//    lit_in_clause *pivot1 = linfo[p][q].headp_clause;
//    lit_in_clause_locs *pivot2 = linfo[p][q].headp_locs;
//    linfo[p][q].is_assigned = YES;
//    int k = 0;
//    for (i=0;i < linfo[p][q].n_occur; i++)
//   {
//
//        int j = pivot1->data;
//        lit_in_clause * a = pivot1->nextone;
//        pivot1 = a;
//        k = pivot2->data;
//        lit_in_clause_locs * b = pivot2->nextone;
//        pivot2 = b;
//        if(clauses[j].is_satisfied)continue;
//        --clauses[j].current_length;
////        clauses[j].binary_code -= ((1<<k));
//        changes[changes_index].clause_index = j;
//        changes[changes_index++].literal_index = k;
//        n_changes[depth][SHRUNK]++;
//        if(clauses[j].current_length == 1)
//       {
//           literals * pivot3 = clauses[j].headp_literal;
//           while (linfo[abs(pivot3->data)][pivot3->data >0 ? SATISFIED : SHRUNK].is_assigned)
//           {
//               literals *pivot4 = pivot3->nextone;
//               pivot3 = pivot4;
//           }
//           int w = pivot3->data;
//           int t = w > 0  ? SATISFIED : SHRUNK;
//           if(linfo[abs(w)][!t].is_unit == YES)
//           {
//               contradictoy_unit_clauses = TRUE;
//               linfo[abs(w)][t].antecedent_clause = j;
//               conflicting_literal = w ;
//           }
//           else
//           {
//               clauses[j].current_ucl = w;
//               linfo[abs(w)][t].is_unit = YES;
//               linfo[abs(w)][t].antecedent_clause = j;
//               gucl_stack[n_gucl] = j; //储存的是为单子句的序列号
//               n_gucl++;
//           }
//
////            int loc = (int)log2(clauses[j].binary_code);
////            clauses[j].all_literals = clauses[j].headp_literal;
////            for(int i = 1;i<loc;i++)
////            {
////                clauses[j].all_literals = clauses[j].all_literals->nextone;
////            }
////            int w = clauses[j].all_literals->data;
////            int s = abs(w), t = (w>0) ? SATISFIED : SHRUNK;
////            linfo[s][t].antecedent_clause = j;
////            if(linfo[s][(!t)].is_unit == YES)
////            {
////                contradictoy_unit_clauses = TRUE;
////                conflicting_literal = w;
////            }
////            else if (linfo[s][(!t)].is_unit == NO)
////            {
////                gucl_stack[n_gucl] = clauses[j].current_ucl = w;
////                linfo[s][t].is_unit = YES;
////                ++n_gucl;
////
////            }
//       }
//       if (clauses[j].current_length == 0) {
//           return 0;
//       }
//
//    }
//    if(depth && backtrack_level == depth-1)
//        ++backtrack_level;
//    ++depth;
//    return 1;
//}
//
//void UnSetVar (int v)//恢复F
//{
//    //register int i;
//    register int p = abs(v);// q = (v>0) ? SATISFIED : SHRUNK;
//    -- depth;
//    if(depth && backtrack_level == depth)
//        --backtrack_level;
//    while (n_changes[depth][SHRUNK])
//    {
//        --n_changes[depth][SHRUNK];
//        register int j = changes[--changes_index].clause_index;
//   //   register int k = changes[changes_index].literal_index;
//        ++clauses[j].current_length;
//        if(clauses[j].current_length == 2)
//        {
//            int s = abs(clauses[j].current_ucl);
//            int t = (clauses[j].current_ucl > 0) ? SATISFIED : SHRUNK;
//            linfo[s][t].is_unit = NO;
//            clauses[j].current_ucl = 0;
//        }
//       // clauses[j].binary_code += ((1<<k));
//    }
//    while (n_changes[depth][SATISFIED])
//    {
//        --n_changes[depth][SATISFIED];
//        register int j = changes[--changes_index].clause_index;
//        clauses[j].is_satisfied = NO;
//        ++r_clauses;
//    }
//    linfo[p][SATISFIED].is_assigned = NO;
//    linfo[p][SHRUNK].is_assigned = NO;
//    assign[p].type = v > 0 ? SATISFIED : SHRUNK;
//    assign[p].decision = UNASSIGNED;
//}
//
//int dpll()
//{
//    //单子句传播规则
//     //int * ml_stack = NULL;
//     //int n_ml = 0;
//    while(n_gucl > 0)
//    {
////        if(contradictoy_unit_clauses)//解决有冲突的部分
////        {
////            ic_cnt = 0;
////            int cl = abs(conflicting_literal);
////            impl_clauses[ic_cnt++] = linfo[cl][SATISFIED].antecedent_clause;//存下以该文字为单子句的子句
////            impl_clauses[ic_cnt++] = linfo[cl][SHRUNK].antecedent_clause;//同上
////            assign[cl].decision = UNASSIGNED;
////            while(n_lucl)//当还存在已经赋值的文字时
////            {
////                UnSetVar(lucl_stack[--n_lucl]);
////                register int s = abs(lucl_stack[n_lucl]);
////                register int t = lucl_stack[n_lucl] >0 ? TRUE :FALSE;
////                impl_clauses[ic_cnt++] = linfo[s][t].antecedent_clause;
////                assign[s].type = t;
////                assign[s].decision = UNASSIGNED;
////            }
////            contradictoy_unit_clauses = FALSE;
////            free(lucl_stack);
////            n_gucl= 0;
////            return UNSAT;
////        }
////        else if(n_gucl)//存在单子句
////        {
////            lucl_stack = (int *) realloc(lucl_stack,(n_lucl+1)*sizeof(int));
////            register int implied_lit = gucl_stack[--n_gucl];
////            lucl_stack[n_lucl++] = implied_lit;
////            assign[abs(implied_lit)].type = implied_lit > 0 ? TRUE :FALSE;
////            assign[abs(implied_lit)].decision = ASSIGN_IMPLIED;
////            SetVar(implied_lit);
////           // n_units++//？
////        }
////        else break;
//        if(!SetVar(gucl_stack[n_gucl])) return UNSAT;
//        n_gucl --;
//
//    }
//    if(r_clauses==0) return SAT;
//
////    for(int i = 1; i < n_vars; ++i)
////    {
////        int x, y, u, C;
////        x = y = 0;
////        if(assign[i].decision == ASSIGN_NONE)
////        {
////            u = 0;
////        }
////    }改善的另一个方面*/
//    int index_VAR = 1;
//    while(1) {
//        if ((assign[index_VAR].decision == UNASSIGNED)&&(linfo[index_VAR][1].n_occur>0)) {
//            break;
//        }
//        index_VAR++;
//      }//采用某种选择策略
//    assign[index_VAR].type = index_VAR ? TRUE :FALSE;
//    assign[index_VAR].depth = depth;
//    assign[index_VAR].decision = ASSIGN_IMPLIED;
//    SetVar(index_VAR);
//    if(dpll()) return SAT;
//    UnSetVar(index_VAR);
//    SetVar(-index_VAR);
//    if(dpll()) return SAT;
//    return UNSAT;
////    assign[abs(index_VAR)].decision =ASSIGN_NONE;
////    int max_depth = 0 ,i, j, k, m, left = FALSE;
////    if(ic_cnt)
////    {
////        while (ic_cnt)
////        {
////            i = impl_clauses[--ic_cnt];
////            k = clauses[i].original_length;
////            literals * pivot = clauses[i].headp_literal;
////            for(j=0;j<k;++j)
////            {
////                m = abs(pivot->data);
////                pivot = pivot->nextone;
////                if(assign[m].decision == ASSIGN_BRANCHED && assign[m].depth > max_depth)
////                max_depth = assign[m].depth;
////            }
////        }
////        left = TRUE;
////    }
////    //++n_backtracks;
////    if(backtrack_level >= depth-1)
////    {
////        assign[abs(index_VAR)].type = !assign[abs(index_VAR)].type;
////        assign[abs(index_VAR)].decision = ASSIGN_IMPLIED;
////        SetVar(-index_VAR);
////        if(dpll())return SAT;
////        UnSetVar(-index_VAR);
////        assign[abs(index_VAR)].type = UNASSIGNED;
////        assign[abs(index_VAR)].decision = ASSIGN_NONE;
////        if(left && ic_cnt)
////        {
////            while (ic_cnt) {
////                i = impl_clauses[--ic_cnt];
////                k = clauses[i].original_length;
////                literals * pivot = clauses[i].headp_literal;
////                for (j=0; j < k; ++j)
////                {
////                    m = abs(pivot->data);
////                    pivot = pivot->nextone;
////                    if(assign[m].decision == ASSIGN_BRANCHED && assign[m].depth > max_depth)
////                        max_depth = assign[m].depth;
////                }
////            }
////            if(max_depth < backtrack_level)
////                backtrack_level = max_depth;
////        }
////    }
////    ic_cnt = 0;
////    while (n_lucl)
////    {
////        int z = lucl_stack[--n_lucl];
////        UnSetVar(z);
////        assign[abs(z)].type = UNASSIGNED;
////        assign[abs(index_VAR)].decision = ASSIGN_NONE;
////
////    }
////    free(lucl_stack);
////    contradictoy_unit_clauses = FALSE;
////    return UNSAT;
//
//
//
//
//
//}
//
//
//
#endif /* preprocess_h */
