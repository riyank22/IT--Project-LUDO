#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int i,j;
void display(char*,char*,char*,char*); //for displaying (giving input the four char arrays)
int dice(void); //dice
void kingdom_finder(int,int *,int,char*,char*,char*, char*); //valur, initial kingdomn(kingdom number and postion)
void area_g(int,int*,int,char *, char *,char *, char *); //navigation function in green kingdom
void area_r(int,int *,int, char *, char *,char *, char *);
void area_b(int,int *,int, char *, char *,char *, char *);
void area_y(int,int *,int, char *, char *,char *, char *);

    char green_area[6][3],blue_area[6][3],red_area[3][6], yellow_area[3][6];
    char *gr_ptr, *bl_ptr, *re_ptr, *ye_ptr;
    gr_ptr=&green_area[0][0];bl_ptr=&blue_area[0][0];re_ptr=&red_area[0][0];ye_ptr=&yellow_area[0][0];

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

    *(ptr_pices)=1;

    *(ptr_pices+1)=1;

    printf("%d %d", pices[0][0], pices[0][1]);

    while(value!=6)
        {
        display(gr_ptr,bl_ptr,re_ptr,ye_ptr);
        printf("Enter value: ");
        scanf("%d", &value);
        }

        value=0;

    while(green_area[0][1]!='*')
    {
        display(gr_ptr,bl_ptr,re_ptr,ye_ptr);
        printf("\n%d %d\n", pices[0][0], pices[0][1]);
        printf("Enter value: ");
        scanf("%d", &value);

        kingdom_finder(value, ptr_pices,1,gr_ptr, re_ptr, bl_ptr, ye_ptr);
    }
}

void kingdom_finder(int value, int *initial_kingdom,int color,char *g, char *r, char *b, char *y)
{
    switch(*(initial_kingdom))
    {
        case 1:
        printf("kingdom identified\n");
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


}

void area_g(int value,int *initial,int color)
{
    int temp=*(initial+1);
    if(value+*(initial+1)>13)
    {
        *(initial)++; //to move to next kingdom
    }

    *(initial+1)+=value;

    if(*(initial+1)<=6) //moving pice to new location
    {   
        *(gr_ptr+2+3*(*(initial+1)-1))='*';
    }

    else if(*(initial+1)==7)
    {
        *(gr_ptr+1+3*5)='*';
    }

    else if(*(initial+1)>7&&color==1&&*(initial+1)<=12)
    {
        *(gr_ptr+1+(12-*(initial+1))*3)='*';
    }

    else
    {
        *(gr_ptr+(13-*(initial+1))*3)='*';
    }

    //clearing previous location    

    if(temp<=6) //moving pice to new location
    {   
        *(gr_ptr+2+3*(temp-1))='*';
    }

    else if(temp==7)
    {
        *(gr_ptr+1+3*5)='*';
    }

    else if(temp>7&&color==1&&temp<=12)
    {
        *(gr_ptr+1+(12-temp)*3)='*';
    }

    else
    {
        *(gr_ptr+(13-temp)*3)='*';
    }
}

void area_r(int value,int *initial, int color)
{
    int temp=*(initial+1);
    if(value+*(initial+1)>13)
    {
        *(initial)++; //to move to next kingdom
    }

    *(initial+1)+=value;

    if(*(initial+1)<=6) //moving pice to new location
    {   
        *(re_ptr+17-*(initial+1))='*';
    }

    else if(*(initial+1)==7)
    {
        *(re_ptr+6)='*';
    }

    else if(*(initial+1)>7&&color==2&&*(initial+1)<=12)
    {
        *(re_ptr+(initial+1)-1)='*';
    }

    else
    {
        *(re_ptr+(*(initial+1)-8))='*';
    }

    //clearing previous location    

    if(temp<=6)
    {   
        *(re_ptr+17-temp)='*';
    }

    else if(temp==7)
    {
        *(re_ptr+6)='*';
    }

    else if(temp>7&&color==2&&temp<=12) //for home pices (red pices for red kingdom)
    {
        *(re_ptr+temp-1)='*';
    }

    else
    {
        *(re_ptr+temp-8)='*';
    }
}

void area_b(int value,int *initial,int color)
{
    int temp=*(initial+1);

    if(value+*(initial+1)>13)
    {
        *(initial)++; //to move to next kingdom
    }

    *(initial+1)+=value;

    if(*(initial+1)<=6) //moving pice to new location
    {   
        *(bl_ptr+18-(3*(*(initial+1))))='*';
    }

    else if(*(initial+1)==7)
    {
        *(bl_ptr+1)='*';
    }

    else if(*(initial+1)>7&&color==3&&*(initial+1)<=12)
    {
        *(bl_ptr+1+(*(initial+1)-7)*3)='*';
    }

    else
    {
        *(bl_ptr+((*(initial+1)-7)*3)-1)='*';
    }

    //clearing previous location    

    if(temp <= 6) //moving pice to new location
    {   
        *(bl_ptr+18-(3*temp))='*';
    }

    else if(temp == 7)
    {
        *(bl_ptr+1)='*';
    }

    else if(temp > 7 && color==3 && temp<=12)
    {
        *(bl_ptr+1+(temp-7)*3)='*';
    }

    else
    {
        *(bl_ptr+((temp-7)*3)-1)='*';
    }
}

void area_y(int value,int *initial, int color)
{
    int temp=*(initial+1);
    if(value+*(initial+1)>13)
    {
        *(initial)++; //to move to next kingdom
    }

    *(initial+1)+=value;

    if(*(initial+1)<=6) //moving pice to new location
    {   
        *(ye_ptr+*(initial+1)-1)='*';
    }

    else if(*(initial+1)==7)
    {
        *(ye_ptr+11)='*';
    }

    else if(*(initial+1)>7&&color==4&&*(initial+1)<=12)
    {
        *(ye_ptr + 18 - *(initial+1))='*';
    }

    else
    {
        *(ye_ptr + 25 - *(initial+1))='*';
    }

    //clearing previous location    

    if(temp<=6) //moving pice to new location
    {   
        *(ye_ptr + temp - 1)='*';
    }

    else if(temp==7)
    {
        *(ye_ptr+6)='*';
    }

    else if(temp>7 && color==4 && temp<=12)
    {
        *(ye_ptr + 18 - temp)='*';
    }

    else
    {
        *(ye_ptr + 25 - temp)='*';
    }
}

int dice(void)
{
    float f;
    unsigned short int r;

    r = rand();
    //f = r / 65536.0;
    r = 1 + (r % 6);

    return (r);
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