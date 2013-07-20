#include<stdio.h>
#include<stdlib.h>
#define MAX 40
int direc[8];
int sx,sy;
int boundary=0;
int clock1=2;  			// clock =1 means clockwise ,0 means anticlockwise
int count=0;
int a[2];
struct point
{
	int x_coord;
	int y_coord;
	int timestamp;
	int reach;
	int flag;
	int in;
	int out;
};
typedef struct point node;
node p[MAX][MAX];
void initialise()				//returns the start vertex
{
	srand(time(NULL));			
	sx=rand()%MAX;
	sy=rand()%MAX;
}
int dir()
{
	int t;
	t=rand()%8;
	return t;
}
int gendir()
{
	int t;
	t=dir();
	if(direc[t]==1)
		return t;
	else
		gendir();
}
void setdir()
{
	int i,j;
	for(i=0,j=1;i<8,j<8;i+=2,j+=2)
	{
		direc[i]=1;
		direc[j]=0;	
	}
}
boundary_set(node *temp)	//sets the flags when the boundary is reached 
{     	
	int dir;
	dir=temp->out;
	if((a[0]!=2)||(a[1]!=2))
	{
		if(boundary==0)
		{
			if(a[0]==0)
			{
				if(dir==2)
				clock1=1;
				if(dir==6)
				clock1=0;
				
			}
			if(a[0]==1)
			{
				if(dir==6)
				clock1=1;
				if(dir==2)
				clock1=0;
			}
			if(a[1]==0)
			{
				if(dir==0)
				clock1=0;
				if(dir==4)
				clock1=1;
			}
			if(a[1]==1)
			{
				if(dir==4)
				clock1=0;
				if(dir==0)
				clock1=1;
			}
		}
		
		if(boundary>=1)
		{
			if(a[0]==0)
			{
				if(clock1==1)
					direc[6]=0;
				if(clock1==0)
					direc[2]=0;
			}	
			if(a[0]==1)
			{
				if(clock1==1)
					direc[2]=0;
				if(clock1==0)
					direc[6]=0;
			}
			if(a[1]==0)
			{
				if(clock1==1)
					direc[0]=0;
				if(clock1==0)
					direc[4]=0;
			}
			if(a[1]==1)
			{
				if(clock1==1)
					direc[4]=0;
				if(clock1==0)
					direc[0]=0;
			}
		}
	}
	boundary++;
	if(clock1==2)
	boundary--;
}

int returnIfStart(node *temp)
{
	int x=temp->x_coord;
	int y=temp->y_coord;
	int t=0;
	int x1,x2,y1,y2;
	x1=x+1;
	x2=x-1;
	y1=y+1;
	y2=y-1;
	if(y!=(MAX-1))
	if((x==sx)&&((y+1)==sy))
	t=1;
	if(x!=0)
	if(((x-1)==sx)&&(y==sy))
	t=1;
	if(y!=0)
	if((x==sx)&&((y-1)==sy))
	t=1;
	if(x!=(MAX-1))
	if(((x+1)==sx)&&(y==sy))
	t=1;
	return t;
	
}
void check_bound(node *temp)   //checks whether the point lies in a boundary and on which boundary does it lie
{
	int x=temp->x_coord;
	int y=temp->y_coord;
	if(x==0)
		a[0]=0;
	else if(x==(MAX-1))
		a[0]=1;
	else
		a[0]=2;
	if(y==0)
		a[1]=0;
	else if(y==(MAX-1))
		a[1]=1;
	else
		a[1]=2;
}
void visitedFlagSet(node *temp)
{
	int x=temp->x_coord;	
	int y=temp->y_coord;
	int d=temp->in;
	if(x!=(MAX-1))
	if(p[x+1][y].reach==1)
	direc[0]=0;
	if(y!=(MAX-1))
	if(p[x][y+1].reach==1)
	direc[2]=0;
	if(x!=0)
	if(p[x-1][y].reach==1)
	direc[4]=0;
	if(y!=0)
	if(p[x][y-1].reach==1)
	direc[6]=0;
}	

void set_flags(node *temp)		//sets the desired directions in which the move can be taken
{
	setdir();	
	visitedFlagSet(temp);
	check_bound(temp);	//checks the boundary and sets the flags accordingly
	if(a[0]==0)
		direc[4]=0;
	if(a[0]==1)
		direc[0]=0;
	if(a[1]==0)
		direc[6]=0;
	if(a[1]==1)
		direc[2]=0;
}
 

node *next_ver(node *temp,int d)	//finds the direction and returns the next random point in the matrix
{
	node *t;
	t=(node *)malloc(sizeof(node));
	count++;
		if(d==0)
		{
			t->x_coord=temp->x_coord+1;
			t->y_coord=temp->y_coord;
			t->timestamp=count;
			t->reach=1;
			t->in=d;
			temp->out=d;
			return t;
		}
		else if(d==2)
		{
			t->x_coord=temp->x_coord;
			t->y_coord=temp->y_coord+1;
			t->timestamp=count;
			t->reach=1;
			t->in=d;
			temp->out=d;
			return t;
		}
		else if(d==4)
		{
			t->x_coord=temp->x_coord-1;
			t->y_coord=temp->y_coord;
			t->timestamp=count;
			t->reach=1;
			t->in=d;
			temp->out=d;
			return t;
		}
		else if(d==6)
		{
			t->x_coord=temp->x_coord;
			t->y_coord=temp->y_coord-1;
			t->timestamp=count;
			t->reach=1;
			t->in=d;
			temp->out=d;
			return t;
		}
}

void create_neighbour(node *temp,node *vl,node *vr,node *vin)	//creates the neighbourhood of a particular point
{
	int x,y;
	x=temp->x_coord;
	y=temp->y_coord;
	int dir=temp->in;
	if(dir==0)
	{
		if(x!=(MAX-1))
		{
			if(y!=(MAX-1))
			vl->reach=p[x+1][y+1].reach;
			if((vl->reach)==1)
			{
				vl->x_coord=x+1;
				vl->y_coord=y+1;
				vl->in=p[x+1][y+1].in;
				vl->out=p[x+1][y+1].out;
				vl->timestamp=p[x+1][y+1].timestamp;
			}
			if(y!=0)
			vr->reach=p[x+1][y-1].reach;
			if((vr->reach)==1)
			{
				vr->x_coord=x+1;
				vr->y_coord=y-1;
				vr->in=p[x+1][y-1].in;
				vr->out=p[x+1][y-1].out;
				vr->timestamp=p[x+1][y-1].timestamp;
			}
		}
			vl->flag=1;
			vr->flag=7;
			vin->flag=4;					
	}
	if((dir==2)||(dir==10))
	{
		if(y!=(MAX-1))
		{
			if(x!=0)
			vl->reach=p[x-1][y+1].reach;
			if((vl->reach)==1)
			{
				vl->x_coord=x-1;
				vl->y_coord=y+1;
				vl->flag=3;
				vl->in=p[x-1][y+1].in;
				vl->out=p[x-1][y+1].out;	
				vl->timestamp=p[x-1][y+1].timestamp;
			}
			if(x!=(MAX-1))
			vr->reach=p[x+1][y+1].reach;
			if((vr->reach)==1)
			{
				vr->x_coord=x+1;
				vr->y_coord=y+1;
				vr->flag=1;
				vr->in=p[x+1][y+1].in;
				vr->out=p[x+1][y+1].out;
				vr->timestamp=p[x+1][y+1].timestamp;
			}
		}
		vin->flag=6;
		vl->flag=3;
		vr->flag=1;
	}
	if(dir==4)
	{
		if(x!=0)
		{
			if(y!=0)
			vl->reach=p[x-1][y-1].reach;
			if((vl->reach)==1)
			{
				vl->x_coord=x-1;
				vl->y_coord=y-1;
				vl->flag=5;
				vl->in=p[x-1][y-1].in;
				vl->out=p[x-1][y-1].out;
				vl->timestamp=p[x-1][y-1].timestamp;
			}
			if(y!=(MAX-1))
			vr->reach=p[x-1][y+1].reach;
			if((vr->reach)==1)
			{
				vr->x_coord=x-1;
				vr->y_coord=y+1;
				vr->flag=3;
				vr->in=p[x-1][y+1].in;
				vr->out=p[x-1][y+1].out;
				vr->timestamp=p[x-1][y+1].timestamp;
			}
		}
		vin->flag=0;
		vl->flag=5;
		vr->flag=3;
	}
	if(dir==6)
	{
		if(y!=0)
		{
			if(x!=(MAX-1))
			vl->reach=p[x+1][y-1].reach;
			if((vl->reach)==1)
			{
				vl->x_coord=x+1;
				vl->y_coord=y-1;
				vl->flag=7;
				vl->in=p[x+1][y-1].in;
				vl->out=p[x+1][y-1].out;
				vl->timestamp=p[x+1][y-1].timestamp;
			}			
			if(x!=0)
			vr->reach=p[x-1][y-1].reach;
			if((vr->reach)==1)
			{
				vr->x_coord=x-1;
				vr->y_coord=y-1;
				vr->flag=5;
				vr->in=p[x-1][y-1].in;
				vr->out=p[x-1][y-1].out;
				vr->timestamp=p[x-1][y-1].timestamp;
			}
		}
		vin->flag=2;
		vl->flag=7;
		vr->flag=5;
	}
}	
void forward(int x,int y)
{
	while(x!=((y+1)%8))
	{
		direc[x]=0;
		x=(++x)%8;
	}
}
void move(int x,int y,int z)
{
	if(z==4)
		if(x<y)
		forward(z,x);
		else
		forward(x,z);
	else
		if(x<y)
			forward(x,z);
		else
			forward(z,x);
}
void move_in(int x,int y,int z)
{
	if(y==4)
		if(x<z)
			forward(x,z);
		else
			forward(z,x);
	else
		if(x<z)
			forward(z,x);
		else
			forward(x,z);
}

int direction(node *n)
{
	int d=0;
	if((n->flag)==3)
	{
		if((n->in)==0)
		{
			if((n->out)==6)
			d=1;
			else
			d=2;
		}
		if((n->in)==6)
		{
			if((n->out)==0)
			d=2;
			else
			d=1;
		}
		if((n->in)==4)
		d=1;
		if((n->in)==2)
		d=2;
	}
	if((n->flag)==1)
	{
		if((n->in)==4)
		{
			if((n->out)==6)
			d=2;
			else
			d=1;
		}
		if((n->in)==6)
		{	
			if((n->out)==4)
			d=1;
			else
			d=2;
		}
		if((n->in)==2)
		d=1;
		if((n->in)==0)
		d=2;
	}
	if((n->flag)==5)
	{
		if((n->in)==0)
		{
			if((n->out)==2)
			d=2;
			else
			d=1;
		}
		if((n->in)==2)
		{
			if((n->out)==0)
			d=1;
			else
			d=2;
		}
		if((n->in)==4)
		d=2;
		if((n->in)==6)
		d=1;
	}
	if((n->flag)==7)
	{
		if((n->in)==4)
		{
			if((n->out)==2)
			d=1;
			else 
			d=2;
		}
		if((n->in)==2)
		{
			if((n->out)==4)
			d=2;
			else
			d=1;
		}
		if((n->in)==6)
		d=2;
		if((n->in)==0)
		d=1;
	}
	return d;
}
void setDirection(node *n)			
{
	int dirn=0;
	node *vr,*vl,*vin;
	vr=(node *)malloc(sizeof(node));
	vl=(node *)malloc(sizeof(node));
	vin=(node *)malloc(sizeof(node));
	create_neighbour(n,vl,vr,vin);
	int fl,fr,fin;
	fl=vl->flag;
	fr=vr->flag;
	fin=vin->flag;
	if((vl->reach==1)&&(vr->reach==1))
	{
		if(vl->timestamp<vr->timestamp)
		{
			dirn=direction(vl);
			if(dirn==1)
			move_in(fl,fin,fr);	
			if(dirn==2)
			move(fl,fr,fin);
		}
		else
		{
			dirn=direction(vr);
			if(dirn==1)
			move(fr,fl,fin);
			if(dirn==2)
			move_in(fr,fin,fl);
		}
	}	
	if((vl->reach==1)&&(vr->reach!=1))
	{
		dirn=direction(vl);
		if(dirn==1)
		forward(fl,fin);
		if(dirn==2)
		move(fl,fr,fin);
	}	
	if((vr->reach==1)&&(vl->reach!=1))
	{
		dirn=direction(vr);
		if(dirn==1)
		move(fr,fl,fin);
		if(dirn==2)
		forward(fin,fr);
	}
}
void array(node *temp)
{
	int i=temp->x_coord;
	int j=temp->y_coord;
	p[i][j].x_coord=i;
	p[i][j].y_coord=j;
	p[i][j].in=temp->in;
	p[i][j].out=temp->out;	
	p[i][j].timestamp=temp->timestamp;
	p[i][j].reach=temp->reach;
}
int GoToStart(node *temp)
{
	int z=-1;
	int x,y;
	x=temp->x_coord;
	y=temp->y_coord;
	if((x!=(MAX-1))&&(y!=(MAX-1)))
	if(p[x+1][y+1].in==10)
	{
		if((p[x+1][y+1].out==2)||(p[x+1][y+1].out==0))
		if(direc[2]==1)
		z=2;
		else
		z=0;
		if(p[x+1][y+1].out==4)
		z=0;
		if(p[x+1][y+1].out==6)
		z=2;
	}
	if((x!=0)&&(y!=(MAX-1)))
	if(p[x-1][y+1].in==10)
	{
		if((p[x-1][y+1].out==4)||(p[x-1][y+1].out==2))
		if(direc[2]==1)
		z=2;
		else
		z=4;
		if(p[x-1][y+1].out==0)
		z=4;
		if(p[x-1][y+1].out==6)
		z=2;
	}
	if((x!=0)&&(y!=0))
	if(p[x-1][y-1].in==10)
	{
		if((p[x-1][y-1].out==4)||(p[x-1][y-1].out==6))
		if(direc[4]==1)
		z=4;
		else
		z=6;
		if(p[x-1][y-1].out==0)
		z=4;
		if(p[x-1][y-1].out==2)
		z=6;
	}
	if((x!=(MAX-1))&&(y!=0))
	if(p[x+1][y-1].in==10)	
	{
		if((p[x+1][y-1].out==6)||(p[x+1][y-1].out==0))
		if(direc[6]==1)
		z=6;
		else
		z=0;
		if(p[x+1][y-1].out==2)
		z=6;
		if(p[x+1][y-1].out==4)
		z=0;
	}
	return z;
}	
int main()
{
	FILE *fp;
	fp=fopen("output.txt","w");
	int t,val,value,reverse;
	int h=0;
	int c=1;
	int k,j;
	node *start,*nxt,*n;
	initialise();
	start=(node *)malloc(sizeof(node));
	start->x_coord=sx;
	start->y_coord=sy;
//	printf("%d\t%d\n",start->x_coord,start->y_coord);
	fprintf(fp,"%d\t%d\n",start->x_coord,start->y_coord);
	start->in=10;
	set_flags(start);
	t=gendir();
	nxt=next_ver(start,t);
	start->reach=1;
	array(start);
	boundary_set(start);
	n=nxt;
//	printf("%d\t%d\n",nxt->x_coord,nxt->y_coord);
	fprintf(fp,"%d\t%d\n",nxt->x_coord,nxt->y_coord);
	while(c)
	{	int x=0;
		set_flags(n);
		setDirection(n);
		if(boundary>=1)
		boundary_set(n);
		int i;
		for(i=0;i<8;i++)
		{
			if(direc[i]==0)
			x++;
		}
		if(x==8)
		{
			printf("No direction is valid now...have to start all over....\n");
			break;
		}	
		else
		{
			t=gendir();
			int v;
			v=GoToStart(n);
			if((v>=0)&&(h>3))
			nxt=next_ver(n,v);
			else
			nxt=next_ver(n,t);
			array(n);
			if(boundary==0)
			boundary_set(n);
			n=nxt;
			//printf("%d\t%d\n",nxt->x_coord,nxt->y_coord);
			fprintf(fp,"%d\t%d\n",nxt->x_coord,nxt->y_coord);
			val=returnIfStart(nxt);
			if((val==1)&&(h>2))
			{
				//printf("%d\t%d\n",start->x_coord,start->y_coord);
				fprintf(fp,"%d\t%d\n",start->x_coord,start->y_coord);
				printf("DONE!!!!!\n");
				printf("total points=%d\n",h+3);
				break;
			}
			if((val==2)&&(h>2))
			{
			
			}
		}
		h++;
	}
}
