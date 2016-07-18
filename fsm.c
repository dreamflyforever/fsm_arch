#include <stdio.h>

/*state name*/
enum State {
	ST1, ST2, ST3, ST4, ST5
};

/*current state*/
struct fsm_cur_state
{
	unsigned char cur_state;
};

/*callback function also call action for state*/
typedef void (*fsm_func_ptr)(struct fsm_cur_state *);

/*action and next state*/
struct fsm_table
{
	fsm_func_ptr ptr;
	unsigned char nextState;        
};


/*state action*/
void donext(struct fsm_cur_state *cur_state)
{
	printf("\n---next---\n");       
}

void donothing(struct fsm_cur_state *cur_state)
{
	printf("\n---error---\n");      
}

void dohello(struct fsm_cur_state *cur_state)
{
	printf("\n---yes---\n");        
}


/*state table*/
struct fsm_table fsm_tab[5][2] = {
	{
		{donext, ST2}, 
		{donothing, ST1}
	},

	{
		{donext, ST3}, 
		{donothing, ST1}
	},

	{
		{donext, ST4}, 
		{donothing, ST1}
	},

	{
		{donext, ST5}, 
		{donothing, ST1}
	},

	{
		{dohello, ST1},        
		{donothing, ST1}
	},
}; 

/*state dispatch*/
void fsm_dispatch(struct fsm_cur_state *cur_state, unsigned char sig)
{
	(fsm_tab[cur_state->cur_state][sig].ptr)(cur_state);
	cur_state->cur_state =  fsm_tab[cur_state->cur_state][sig].nextState;
}

/*input h-e-l-l-o display OK*/
/*input right char table*/
char hello[] = {'h','e','l','l','o'};

int main()
{
	char i;
	unsigned int single;
	struct fsm_cur_state cs;

	/*init state*/
	cs.cur_state = ST1; 
	while (1) {
		i = getchar();
		if (i == hello[cs.cur_state]) {
			single = 0;     
		} else {
			single = 1;     
		}
		fsm_dispatch(&cs, single);
	}
	return 0;       
}
