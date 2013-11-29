#include <stdio.h>

//状态的enum定义 
enum State{ST1, ST2, ST3, ST4, ST5};

//定义一个存储当前状态的结构体
struct FsmCurState
{
    unsigned char curState;
};

//回调函数的指针
typedef void (*FsmFuncPtr)(struct FsmCurState *);
//状态表里面的表项的结构定义，回调函数和下一状态 
struct FsmTabEle
{
    FsmFuncPtr ptr;
    unsigned char nextState;        
};


//具体的函数 
void doNext(struct FsmCurState *curState)
{
    printf("\n---next---\n");       
}

void doNothing(struct FsmCurState *curState)
{
    printf("\n---error---\n");      
}

void doHello(struct FsmCurState *curState)
{
    printf("\n---yes---\n");        
}


//状态表
struct FsmTabEle FsmTab[5][2] = {
    {{doNext, ST2}, 
        {doNothing, ST1}},

    {{doNext, ST3}, 
        {doNothing, ST1}},

    {{doNext, ST4}, 
        {doNothing, ST1}},

    {{doNext, ST5}, 
        {doNothing, ST1}},

    {{doHello, ST1},        
        {doNothing, ST1}},
}; 

//状态调度函数
void FsmDispatch(struct FsmCurState *curState, unsigned char sig)
{
    (FsmTab[curState->curState][sig].ptr)(curState);
    curState->curState =  FsmTab[curState->curState][sig].nextState;
}




//输入h-e-l-l-o就显示OK  
//表格实现
char hello[] = {'h','e','l','l','o'};

int main()
{
    char i;
    unsigned int single;
    struct FsmCurState cs;

    //初始化
    cs.curState = ST1; 
    while (1)
    {
        i = getchar();
        if (i == hello[cs.curState])
        {
            single = 0;     
        }
        else
        {
            single = 1;     
        }
        FsmDispatch(&cs, single);
    }
    return 0;       
}
