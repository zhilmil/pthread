#include <stdio.h>

typedef struct{
	int state;
} yo;

void changer(yo* p)
{
	p->state = 5;
}
void printer(yo p)
{
	printf("%d\n", p.state);
}
void main()
{
	yo p;
	changer(&p);
	printer(p);
}