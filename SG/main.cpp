#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<cstdio>
using namespace std;
struct node
{
    int x,y;
    char data;
    node *next,*prev;
}*p;
struct food
{
    int x;
    int y;
    char value;
}f;
struct poison
{
    int x,y;
    char value;
}pp;
struct wall
{
    int x,y;
    char value;
}w;
struct node *insert_save(struct node *p,int row,int col,char ch)
{
 struct node *ptr,*n=new node;
 ptr=p;
 if(p==NULL)
 {
     n->x=row;
     n->y=col;
     n->data=ch;
     n->next=NULL;
     n->prev=p;
     p=n;
 }
 else
 {
     while(ptr->next!=NULL)
     {
         ptr=ptr->next;
     }
     n->x=row;
     n->y=col;
     n->data=ch;
     ptr->next=n;
     n->next=NULL;
     n->prev=p;
 }
 return p;
}

struct node* resume_game(char board[20][50],struct node *p,struct food *f,struct poison *pp,struct wall *w,int *scores)
{
   FILE *fp,*fp1,*fp2,*fp3,*fp4;
   fp=fopen("snake.txt","r");
   fp1=fopen("food.txt","r");
   fp2=fopen("score.txt","r");
   fp3=fopen("poison.txt","r");
   fp4=fopen("wall.txt","r");
   char ch,s;
   int row,col,i;
   ch=getc(fp);
   while(ch!=EOF)
   {
       if(ch!='n')
       {   row=ch-'0'; // atoi
           ch=getc(fp);
          col=ch-'0';
           ch=getc(fp);
           s=ch;
           p=insert_save(p,row,col,s);
       }
       ch=getc(fp);
   }
   char ch1;
   ch1=getc(fp1);
   while(ch1!=EOF)
   {
       f->x=ch1-'0';
       ch1=getc(fp1);
       f->y=ch1-'0';
       ch1=getc(fp1);
       f->value=ch1;
       board[f->x][f->y]=f->value;
       ch1=getc(fp1);
   }
   *scores=getc(fp2)-'0';
   char ch2;
   ch2=getc(fp3);
   while(ch2!=EOF)
   {
       pp->x=ch2-'0';
       ch2=getc(fp3);
       pp->y=ch2-'0';
       ch2=getc(fp3);
       pp->value=ch2;
       board[pp->x][pp->y]=pp->value;
       ch2=getc(fp3);
   }
   char ch3;
     ch3=getc(fp4);
   while(ch3!=EOF)
   {
       w->x=ch3-'0';
       ch3=getc(fp4);
       w->y=ch3-'0';
       ch3=getc(fp4);
       w->value=ch3;
       board[w->x][w->y]=w->value;
       ch3=getc(fp4);
   }
   return p;
}

void save_game(struct node *p,struct food f,struct poison pp,struct wall w,int scores)
{
   FILE *fp,*fp1,*fp2,*fp3,*fp4;
   fp=fopen("snake.txt","w");
   fp1=fopen("food.txt","w");
   fp2=fopen("score.txt","w");
   fp3=fopen("poison.txt","w");
   fp4=fopen("wall.txt","w");
   struct node *p1=p;
   while(p1!=NULL)
   {
       putc(p1->x+'0',fp);
       putc(p1->y+'0',fp);
       putc(p1->data,fp);
       putc('n',fp);
       p1=p1->next;
   }
   putc(f.x+'0',fp1);
   putc(f.y+'0',fp1);
   putc(f.value,fp1);
   putc(scores+'0',fp2);
   putc(pp.x+'0',fp3);
   putc(pp.y+'0',fp3);
   putc(pp.value,fp3);
   putc(w.x+'0',fp4);
   putc(w.y+'0',fp4);
   putc(w.value,fp4);
   fclose(fp);
   fclose(fp1);
   fclose(fp2);
   fclose(fp3);
   fclose(fp4);
}

struct node *insertend(struct node *p,char v)
{

    char value=v;
    static int i=3,j=4;
    node *temp;
    temp=new node;

    if(p==NULL)
    {
        temp->x=i;
        temp->y=j;
        temp->data=value;
        temp->prev=NULL;
        temp->next=NULL;
        p=temp;
    }
    else
    {
        node *temp1;
        temp1=p;
        while(temp1->next!=NULL)
        {
            temp1=temp1->next;
        }
        node *temp;
        temp=new node;
        temp->x=i;
        temp->y=j;
        temp->data=value;
        temp->next=NULL;
        temp->prev=temp1;
        temp1->next=temp;

    }
    j++;
    return p;
}
void length(struct node *p,char x)//snake length inc.
{
        node *temp1;
        temp1=p;
        while(temp1->next!=NULL)
        {
            temp1=temp1->next;
        }
        node *temp;
        temp=new node;
        temp->x=temp1->x;
        temp->y=temp1->y-1;
        temp->data=x;
        temp->next=NULL;
        temp->prev=temp1;
        temp1->next=temp;
       // make_food(board);
}
/*void lengthh(struct node *p)
{
    node * temp1;
    temp1=p;
    while(temp1->next!=NULL)
    {
        temp1=temp1->next;
    }
    node *temp;
    temp=temp1;
    temp1->prev->next=NULL;
    delete temp;
}*/
/*int check(struct node *p)
{
int flag=0;
struct node *ptr=p;
//ptr=ptr->next;
while(ptr->next!=NULL)
{
if(ptr->x==f.x && ptr->y==f.y)
{
flag=1;
break;
}
ptr=ptr->next;
}
return flag;
}*/
int snakecheck(struct node *p)//gameover
{
    int flag1=0;
    struct node *ptr=p;
    ptr=ptr->next;
    while(ptr!=NULL)
    {
        if(p->x==ptr->x && p->y==ptr->y)
        {

            flag1=1;
            break;
        }
     ptr=ptr->next;
    }
    return flag1;
}
int check(struct node *p) //food on snake
{
   int flag=0;
  struct node *ptr=p;
    while(ptr->next!=NULL)
    {
        if(ptr->x==f.x && ptr->y==f.y)
        {
            flag=1;
            break;
        }
        ptr=ptr->next;
    }
    return flag;
}
int checkk(struct node *p)//mine on snake
{
     int flag=0;
  struct node *ptr=p;
    while(ptr->next!=NULL)
    {
        if(ptr->x==pp.x && ptr->y==pp.y)
        {
            flag=1;
            break;
        }
        ptr=ptr->next;
    }
    return flag;
}
int checkkk(struct node *p) // wall on snake
{
    int flag=0;
    struct node *ptr=p;
    while(ptr->next!=NULL)
    {
        if(ptr->x==w.x && ptr->y==w.y)
        {
            flag=1;
            break;
        }
        ptr=ptr->next;
    }
    return flag;

}
//row=a col=b
void make_food(char board[20][50],int a,int b)
{
    //cout<<"Enter food coordinates and value :"<<endl;
    //cin>>f.x>>f.y>>f.value;
    char c='F';
    f.x=a;
    f.y=b;
    f.value=c;
    board[f.x][f.y]=f.value;
    a+5;
    b+5;
}
void make_poison(char board[20][50],int k,int l)
{
    char ch='M';
    pp.x=k;
    pp.y=l;
    pp.value=ch;
    board[pp.x][pp.y]=pp.value;
    k+7;
    l+6;
}
void make_wall(char board[20][50],int t,int q)
 {
    char ch='W';
    w.x=t;
    w.y=q;
    w.value=ch;
    board[w.x][w.y]=w.value;
    t+7;
    q+6;
}

void display(char board[20][50],struct node *p,int h)
{
   int i,j;
   struct node *ptr=p;
   cout<<endl;
   cout<<" score : "<<h;
   if(h<20)
   {
     cout<<"                   Level:1 "<<endl;
   }
   else if(h>=20 && h<40)
   {
       cout<<"                 Level:2 "<<endl;
   }
   else if(h>=40 && h<60)
   {
       cout<<"                 Level:3 "<<endl;
   }
   else if(h>=60 && h<80)
   {
       cout<<"                 Level:4 "<<endl;
   }
   else if(h>=80 && h<100)
   {
       cout<<"                 Level:5 "<<endl;
   }
while(ptr!=NULL)
{
board[ptr->x][ptr->y]=ptr->data;
ptr=ptr->next;
}
   for(i=0;i<20;i++)
    {
        for(j=0;j<50;j++)
        {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}

// row=s,col=k

void swap(struct node *p,int s,int k)
{
    int x1,x2,y1,y2;
   struct node *ptr=p;
   x1=ptr->x;
   y1=ptr->y;
while(ptr->next!=NULL)
{
   ptr=ptr->next;
   x2=ptr->x;
   y2=ptr->y;
    ptr->x=x1;
 ptr->y=y1;
 x1=x2;
 y1=y2;
}
 p->x=s;
 p->y=k;
 //cout<<p->x<<p->y<<endl;
}
void clear_board(char board[20][50])
{
    int i,j;
      for(i=0;i<20;i++)
    {
        for(j=0;j<50;j++)
        {
            if(i==0 ||i==19 ||j==0 ||j==49){board[i][j]='+';}
             else if(board[i][j]!=f.value && board[i][j]!=pp.value && board[i][j]!=w.value) {board[i][j]=' ';}

        }
    }
}
void snake(char board[20][50],char choice)
{
    int g=2;
    static int flag=0,fg=0;
    static int a=2,b=2;
    static int k=12,l=20,t=15,q=25;
    static int h=0; //score
    char v;
    struct node *ptr;
    if(choice=='N')
    {
        v='#';
    ptr=insertend(p,v);
    p=ptr;
    while(g--)
    {
            v='*';
        ptr=insertend(ptr,v);
     }
make_food(board,a,b);
//make_poison(board,k,l);
if(check(p))
{
    a=a+2;
    b=b+2;
    if(a>18 || b>48)
    {
        a=2;

        b=2;
    }
   make_food(board,a,b);

}
if(checkk(p))
{
    t=t+3;
    q=q+4;
     if(t>18 || q>48)
    {
        t=16;
        q=16;
    }
    make_wall(board,t,q);
}
display(board,p,h);
    }
    else if(choice=='R')
    {

        p=resume_game(board,p,&f,&pp,&w,&h);
        display(board,p,h);

    }
    while(1)
    {
        //display(board,p);
        char ch;
        cout<<"Press up(W) down(S) left(A) right(D) save(s): ";
        cin>>ch;
        int n,m;//row=n col=m

if(ch=='D')
{
  ptr=p;
 if(h>=60)
  {
     if(ptr->y==49 )
     {

         cout<<"            GAMEOVER           "<<endl;
         break;
     }
  }

if(ptr->y==49)
  {
 n=ptr->x,m=1;
 }else
 {n=ptr->x;
 m=ptr->y+1;}
if(m!=ptr->next->y)
{
 swap(p,n,m);
}
if(snakecheck(p))
{
    FILE *fp,*fp1,*fp2,*fp3,*fp4;
   fp=fopen("snake.txt","r");
   fp1=fopen("food.txt","r");
   fp2=fopen("score.txt","r");
   fp3=fopen("poison.txt","r");
   fp4=fopen("wall.txt","r");
    cout<<"#GAMEOVER#"<<endl;
    break;
}
}
else if(ch=='S')
{
 ptr=p;
  if(h>=60)
  {
     if(ptr->x==19 )
     {

         cout<<"            GAMEOVER           "<<endl;
         break;
     }
  }
if(ptr->x==19)
 {n=1 ;
 m=ptr->y;}
 else
 {
 n=ptr->x+1;
 m=ptr->y;}
if(n!=ptr->next->x)
{
 swap(p,n,m);

}
if(snakecheck(p))
{
    FILE *fp,*fp1,*fp2,*fp3,*fp4;
   fp=fopen("snake.txt","r");
   fp1=fopen("food.txt","r");
   fp2=fopen("score.txt","r");
    fp3=fopen("poison.txt","r");
   fp4=fopen("wall.txt","r");
    cout<<"#GAMEOVER#"<<endl;
    break;
}
}
else if(ch=='A')
{
 ptr=p;
 if(h>=60)
  {
     if(ptr->y==1 )
     {

         cout<<"            GAMEOVER           "<<endl;
         break;
     }
  }
 if(ptr->y==1)
 {n=ptr->x;
 m=48;
 }else
 {n=ptr->x;
 m=ptr->y-1;}
if(m!=ptr->next->y)
{

 swap(p,n,m);

}
if(snakecheck(p))
{
    FILE *fp,*fp1,*fp2,*fp3,*fp4;
   fp=fopen("snake.txt","r");
   fp1=fopen("food.txt","r");
   fp2=fopen("score.txt","r");
    fp3=fopen("poison.txt","r");
   fp4=fopen("wall.txt","r");
    cout<<"#GAMEOVER#"<<endl;
    break;
}
}
else if(ch=='W')
{
 ptr=p;
 //cout<<ptr->x<<ptr->y<<endl;
 if(h>=60)
  {
     if(ptr->x==1 )
     {

         cout<<"            GAMEOVER           "<<endl;
         break;
     }
  }
 if(ptr->x==1)
 {n=18;
 m=ptr->y;
 }
 else
 {n=ptr->x-1;
 m=ptr->y;}
if(n!=ptr->next->x)
{

 swap(p,n,m);

}
if(snakecheck(p))
{
    FILE *fp,*fp1,*fp2,*fp3,*fp4;
   fp=fopen("snake.txt","r");
   fp1=fopen("food.txt","r");
   fp2=fopen("score.txt","r");
    fp3=fopen("poison.txt","r");
   fp4=fopen("wall.txt","r");
    cout<<"#GAMEOVER#"<<endl;
    break;
}
  //cout<<ptr->x<<ptr->y<<endl;
}
if(p->x==f.x && p->y==f.y)
{
    h+=5;
    a=a+2;
    b=b+2;
    if(a>18 || b>48)
    {
        a=2;
        b=2;
    }
    length(p,p->next->data);
    make_food(board,a,b);
    if(check(p))
{
    a=a+2;
    b=b+2;
    if(a>18 || b>48)
    {
        a=2;
        b=2;
    }
   make_food(board,a,b);

}
}
if(h==20 && flag==0)
{
    flag=1;
    make_poison(board,k,l);
    if(checkk(p))
{
    k=k+3;
    l=l+4;
     if(k>18 || l>48)
    {
        k=6;
        l=6;
    }
    make_poison(board,k,l);
}
}
if(p->x==pp.x && p->y==pp.y)
{
    cout<<endl;
   cout<<"        GAMEOVER        "<<endl;
   break;
}
if(h==80 && fg==0)
{
    fg=1;
    make_wall(board,t,q);
    if(checkkk(p))
{
    t=t+6;
    t=t+8;
     if(t>18 || q>48)
    {
        t=2;
        q=5;
    }
    make_wall(board,t,q);
}
}
if(p->x==w.x && p->y==w.y)
{
    cout<<endl;
   cout<<"        GAMEOVER        "<<endl;
   break;
}
if(ch=='s')
{
    save_game(p,f,pp,w,h);
    break;
}

clear_board(board);
system("cls");
if(h==100)
{
     cout<<"       YOU WIN        "<<endl;
    break;
}
display(board,p,h);

}

}

int main()
{
    cout<<"       #SNAKE GAME#        "<<endl;
    char board[20][50];

    for(int i=0;i<20;i++)
    {
        for(int j=0;j<50;j++)
        {
            if(i==0 || i==19 || j==0 || j==49)
            {
                board[i][j]='+';
            }
            else
            {
            board[i][j]=' ';
        }
        }
    }
    char c;
    cout<<endl;
    cout<<" N for NEW GAME \n R for RESUME GAME \n E for EXIT GAME "<<endl;
    cin>>c;
    if(c=='E')
    {
      cout<<" EXIT ";
    }
    else
    snake(board,c);

}
