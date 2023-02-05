#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int i,j;
void display(char*,char*,char*,char*); //for displaying (giving input the four char arrays)

void kingdom_finder(int,int *,int,char*,char*,char*, char*); //valur, initial kingdomn(kingdom number and postion)
void area_g(int,int*,int,char *, char *,char *, char *); //navigation function in green kingdom
void area_r(int,int *,int, char *, char *,char *, char *);
void area_b(int,int *,int, char *, char *,char *, char *);
void area_y(int,int *,int, char *, char *,char *, char *);

int main(void)
{
    char green_area[6][3],blue_area[6][3],red_area[3][6], yellow_area[3][6];
    char *gr_ptr, *bl_ptr, *re_ptr, *ye_ptr;
    gr_ptr=&green_area[0][0];bl_ptr=&blue_area[0][0];re_ptr=&red_area[0][0];ye_ptr=&yellow_area[0][0];

    for(i=0;i<18;i++)
    {
        *(gr_ptr+i)=*(bl_ptr+i)=*(re_ptr+i)=*(ye_ptr+i)='_';
    }
    int pices[1][2]; //coords of pices (kingdom/coord)

    //1-green
    //2-red
    //3-blue
    //4-yellow
    int *ptr_pices; //for storing posititon of pices (kingdom,location)
    ptr_pices=&pices[0][0];
    int value=0;

    *(ptr_pices)=3;

    *(ptr_pices+1)=1;

    printf("%d %d", pices[0][0], pices[0][1]);

    while(value!=6)
        {
        printf("\n%d %d\n", pices[0][0], pices[0][1]);
        display(gr_ptr,bl_ptr,re_ptr,ye_ptr);
        printf("Enter value: ");
        scanf("%d", &value);
        }
    
        value=0;
        display(gr_ptr,bl_ptr,re_ptr,ye_ptr);

    while(*(gr_ptr+1)!='*')
    {
        display(gr_ptr,bl_ptr,re_ptr,ye_ptr);
        printf("\n%d %d\n", pices[0][0], pices[0][1]);
        printf("Enter value: ");
        scanf("%d", &value);

        kingdom_finder(value, ptr_pices,3,gr_ptr, re_ptr, bl_ptr, ye_ptr);
    }

    display(gr_ptr,bl_ptr,re_ptr,ye_ptr);
}

void kingdom_finder(int value, int *initial_kingdom,int color,char *g, char *r, char *b, char *y)
{
    switch(*(initial_kingdom))
    {
        case 1:
        area_g(value, initial_kingdom,color, g,r,b,y);
        
        break;

        case 2:
        area_r(value, initial_kingdom,color,r,b,y,g);
        break;

        case 3:
        area_b(value, initial_kingdom,color,b,y,g,r);
        break;

        case 4:
        area_y(value, initial_kingdom,color,y,g,r,b);
        break;
    }

}

void area_g(int value,int *initial, int color,char *g, char *r, char *b, char *y)
{
    int temp=*(initial+1);
    *(initial+1)+=value;

    if(*(initial+1)>18)
    {
        *(g+(18-temp)*3)='_';//clearing past record

        value=*(initial+1)-18; //finding the coordinates to move in next kingdom
        *(initial+1)=value; //assigning the coords of the next kingdom
        value=0; //as coordinates are already assigned, putting value = 0
        *(initial)+=1;
        area_r(value, initial, color,r,b,y,g);
        //to move to next kingdom
    }

    if(*(initial+1)<=6 && *(initial)==1) //moving pice to new location
    {   
        *(g+2+3*(*(initial+1)-1))='*';
    }

    else if(*(initial+1)==7)
    {
        *(g+1+3*5)='*';
    }

    else if(color==1 && *(initial+1)<13)
    {
        *(g+(12-*(initial+1))*3+1)='*';
    }

    else
    {
        if(*(initial+1)>7 && *(initial+1)<13)
        {
        *(initial+1)+=5;
        }

        *(g+(18-*(initial+1))*3)='*';
    }

    if(value!=0)
    {
    //clearing previous location
    if(temp<=6) //moving pice to new location
    {   
        *(g+2+3*(temp-1))='_';
    }

    else if(temp==7)
    {
        *(g+1+3*5)='_';
    }

    else if(color==1 && temp<13)
    {
        *(g+(12-temp)*3+1)='_';
    }

    else
    {
        if(temp>7 && temp<13)
        {
        temp+=5;
        }
        
        *(g+(18-temp)*3)='_';
    }
    }
}

void area_r(int value,int *initial, int color, char*r, char *b, char *y, char *g)
{
    int temp=*(initial+1);
    *(initial+1)+=value;

    if(*(initial+1)>18)
    {
        *(r+(temp-13))='_';//clearing past record

        value=*(initial+1)-18;
        *(initial+1)=value;
        value=0;
        *(initial)+=1;
        area_b(value, initial, color, b,y,g,r);
        return(0);
        //to move to next kingdom
    }

    //moving pice to new location
    if(*(initial+1)<=6 && *(initial)==2)  //if it is in the same kingdom
    {   
        *(r+18-*(initial+1))='*';
    }

    else if(*(initial+1)==7)
    {
        *(r+6)='*';
    }

    else if(color==2 && *(initial+1)<13)
    {
        *(r+*(initial+1)-1)='*';
    }

    else
    {
        if(*(initial+1)>7 && *(initial+1)<13)
        {
            *(initial+1)+=5;
        }
        *(r+(*(initial+1)-13))='*';
    }

    //clearing previous location

    if(value!=0)
    {
    if(temp<=6)
    {   
        *(r+18-temp)='_';
    }

    else if(temp==7)
    {
        *(r+6)='_';
    }

    else if(color==2 && temp<13)
    {
        *(r+temp-1)='_';
    }

    else
    {
        if(temp>7 && temp<13)
        {
            temp+=5;
        }
        *(r+temp-13)='_';
    }
    }
}

void area_b(int value,int *initial, int color, char *b, char *y, char *g, char *r)
{
    int temp=*(initial+1);
    *(initial+1)+=value;

    if(*(initial+1)>18)
    {
        *(b+3*temp-37)='_';//clearing past record

        value=*(initial+1)-18;
        *(initial+1)=value;
        value=0;
        *(initial)+=1;
        area_y(value, initial, color, y, g, r, b);
        //to move to next kingdom
    }

    if(*(initial+1)<=6 && *(initial)==3) //moving pice to new location
    {   
        *(b+18-(3*(*(initial+1))))='*';
    }

    else if(*(initial+1)==7)
    {
        *(b+1)='*';
    }

    else if(color==3 && *(initial+1)<13)
    {
        *(b+1+(*(initial+1)-7)*3)='*';
    }

    else
    {
        if(*(initial+1)>7 && *(initial+1)<13)
        {
        *(initial+1)+=5;
        }
        *(b+3*(*(initial+1))-37)='*';
    }

    //clearing previous location    

    if(value!=0)
    {

    if(temp <= 6) //moving pice to new location
    {   
        *(b+18-(3*temp))='_';
    }

    else if(temp == 7)
    {
        *(b+1)='_';
    }

    else if(color==3 && temp<13)
    {
        *(b+1+(temp-7)*3)='_';
    }

    else
    {
        if(temp>7 && temp<13)
        {
        temp+=5;
        }
        *(b+3*temp-37)='_';
    }
    }
}

void area_y(int value,int *initial, int color, char *y, char *g, char *r, char *b)
{
    int temp=*(initial+1);
    *(initial+1)+=value;

    if(*(initial+1)>18)
    {
        *(y+30-temp)='_';

        value=*(initial+1)-18;
        *(initial+1)=value;
        value=0;
        *(initial)=1;
        area_g(value, initial, color,g,r,b,y);
        //to move to next kingdom
    }

    if(*(initial+1)<=6 && *(initial)==4) //moving pice to new location
    {   
        *(y+*(initial+1)-1)='*';
    }

    else if(*(initial+1)==7)
    {
        *(y+11)='*';
    }

    else if(color==4 && *(initial+1)<13)
    {
        *(y + 18 - *(initial+1))='*';
    }

    else
    {
        if(*(initial+1)>7 && *(initial+1)<13)
        {
        *(initial+1)+=5;
        }
        *(y+30-*(initial+1))='*';
    }

    //clearing previous location    

    if(value!=0)
    {
        if(temp<=6 && *(initial)==4) //moving pice to new location
        {   
            *(y+temp-1)='_';
        }

        else if(temp==7)
        {
            *(y+11)='_';
        }

        else if(color==4 && temp<13)
        {
            *(y + 18 - temp)='_';
        }

        else
        {
            if(temp>7 && temp<13)
            {
            temp+=5;
            }
            *(y+30-temp)='_';
        }
    }
}

void display(char *g,char *b, char *r, char *y)
{
    for(i=0;i<6;i++) //blue
    {
        for(j=0;j<12;j++)
        {
            printf(" ");
        }

        for(j=0;j<3;j++)
        {
            printf("%c ", *(b+j+i*3));
        }

        for(j=0;j<12;j++)
        {
            printf(" ");
        }
        printf("\n");
    }

    for(i=0;i<3;i++) //blue
    {

        for(j=0;j<6;j++)
        {
            printf("%c ", *(r+j+i*6));
        }

        for(j=0;j<6;j++)
        {
            printf(" ");
        }

        for(j=0;j<6;j++)
        {
            printf("%c ", *(y+j+i*6));
        }
        printf("\n");
    }

    for(i=0;i<6;i++) //green
    {
        for(j=0;j<12;j++)
        {
            printf(" ");
        }

        for(j=0;j<3;j++)
        {
            printf("%c ", *(g+j+i*3));
        }

        for(j=0;j<12;j++)
        {
            printf(" ");
        }
        printf("\n");
    }
}