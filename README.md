数据结构源码集
========

## 简介

以严蔚敏版《数据结构》为参考，实现书中抽象数据类型及其应用。涉及线性表、栈、队列、稀疏矩阵、广义表、串、二叉树、图等数据结构，包含KMP模式匹配
递归、括号匹配、数制转换、排序、搜索等常用的算法与应用。

## 目录

* [array_and_lists](/array_and_lists)
    * array.c
    * array.h
    * GeneralList.c
    * GeneralList.h
* [graph](/graph)
    * graph_base.h
    * list_graph.c
    * list_graph.h
    * matrix_graph.c
    * matrix_graph.h
    * [applement_of_graph](/graph/applement_of_graph)
        * articulatedAndBiconnected.h
        * articulatedAndBiconnected_List.c
        * articulatedAndBiconnected_Matrix.c
        * criticalPath.h
        * criticalPath_List.c
        * criticalPath_Matrix.c
        * depthFirstSpanningTree.h
        * depthFirstSpanningTree_List.c
        * depthFirstSpanningTree_Matrix.c
        * minimumSpanningTree.h
        * minimumSpanningTree_List.c
        * minimumSpanningTree_Matrix.c
        * shortestPath.h
        * shortestPath_List.c
        * shortestPath_Matrix.c
        * topologicalSort.h
        * topologicalSort_List.c
        * topologicalSort_Matrix.c
* [linear_list](/linear_list)
    * LinkList.c
    * LinkList.h
    * SequList.c
    * SequList.h
    * StaticLinkList.c
    * StaticLinkList.h
    * [applyment](/linear_list/applyment)
        * Polynomail.c
        * Polynomail.h
* [queue](/queue)
    * LinkQueue.c
    * LinkQueue.h
    * PriorityQueue.c
    * PriorityQueue.h
    * SequQueue.c
    * SequQueue.h
    * [applyment_of_queue](/queue/applyment_of_queue)
        * bankingSimulation.c
        * README.md

* [searching](/searching)
    * BalancedBinaryTree.c
    * BalancedBinaryTree.h
    * BinarySortTree.c
    * BinarySortTree.h
    * searching.c
    * searching.h
* [sorting](/sorting)
    * sorting.c
    * sorting.h
    * [applyment_of_sorting](/sorting/applyment_of_sorting)
        * README.md
        * wordcount_new.c
        * wordcount_old.c
* [sparse_matrix](/sparse_matrix)
    * SequMatrix.c
    * SequMatrix.h
* [stack](/stack)
    * LinkStack.c
    * LinkStack.h
    * SequStack.c
    * SequStack.h
    * [applyment_of_recursion](/stack/applyment_of_recursion)
        * corss_river.cpp
        * eightQueue.c
        * hanoi.c
        * sudoku.c
    * [applyment_of_stack](/stack/applyment_of_stack)
        * bracketMatch.c
        * caculate.c
        * conversion.c
        * editor.c
* [string](/string)
    * string.c
    * string.h
* [tree](/tree)
    * ChildBroLinkTree.c
    * ChildBroLinkTree.h
    * LinkBinaryTree.c
    * LinkBinaryTree.h
    * ThreadedLinkBinaryTree.c
    * ThreadedLinkBinaryTree.h
    * [applement_of_tree](/tree/applement_of_tree)
        * createTreeByTraverseSequence.c
        * huffmanTreeCoding.c
* DataStructureBase.h
* README.md

## 说明

`DataStructureBase.h`头文件包含了基本的类型说明与预定义值。约定一般函数均返回状态，状态类型为Status，可取以下四种值。同时包含了用于检测状态的宏，常用于测试和判断函数返回值

```c
#define OK 0
#define ERROR 1
#define OVERFLOW -2
#define INFEASIBLE -1
#define true 1
#define false 0

typedef int Status;
```

可使用下面三个配套的宏用于测试函数状态返回值，若函数操作不成功，则退出函数

```c
#define BEFORE_CHECK_RESULT()   \
    Status __status;

#define CHECK_RESULT(func)      \
    if((__status = func)!=OK){  \
        return __status;        \
    }                           \

#define AFTER_CHECK_RESULT()    \
    return OK
```

可使用以下宏用于判断变量内存是否分配成功，常用于动态分配之后

```c
#define CHECK_OVERFLOW(var)     \
    if(!var){                   \
        return OVERFLOW;        \
    }
```

可使用以下的宏用于类似断言的场景，若不符合断言，则返回ERROR

```c
#define CHECK_ERROR(exp)        \
    if(!(exp))                  \
        return ERROR
```

__[回到顶部](#数据结构源码集)__
--------
