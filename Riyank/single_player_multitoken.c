//program for ludo (terminal based)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int i,j;
void display(); //for displaying (giving input the four char arrays)

void area_finder(int, int,char); //value, initial kingdomn(kingdom number and postion)
void area_g(int, char, int); //navigation function in green kingdom
void area_r(int, char, int); //navigation function in red kingdom
void area_b(int, char, int); //navigation function in blue kingdom
void area_y(int, char, int); //navigation function in yellow kingdom
void homelock_manipulator(int);
int difference(int);
void player(); //game console

int dice(void); //dice

//declaring count of homecount tokens (won tokens)
int tokens[4][5]; //coords of tokens (sequence/area/location/colourcode/coor symbol/coords x/ coord y)

int homecount[4]={0,0,0,0};
int choices[4]={0,0,0,0}; //showing no. of choices (g,r,b,y)
int *ptr_tokens; //for storing posititon of tokens (kingdom,location)

char *gr_ptr, *bl_ptr, *re_ptr, *ye_ptr;//pointers pointing to the area arrays
char *homelock_ptr; //pointer pointing to the arrays storing data for homelock ptr.
    
int main(void)
{
    //defining areas
    char green_area[6][3],blue_area[6][3],red_area[3][6], yellow_area[3][6];
    gr_ptr=&green_area[0][0];bl_ptr=&blue_area[0][0];re_ptr=&red_area[0][0];ye_ptr=&yellow_area[0][0];

    for(i=0;i<18;i++)
    {
        *(gr_ptr+i)=*(bl_ptr+i)=*(re_ptr+i)=*(ye_ptr+i)='_';//assigning the blank spaces.
    }

    for(i=0;i<4;i++) //feeding sequence data
    {
        tokens[i][0]=i+1;
    }

    for(i=0;i<4;i++) //feeding colourcode
    {
        tokens[i][3]=1;
    }

    for(i=0;i<4;i++) //feeding coloursymbol
    {
        tokens[i][4]=(int)'*';
    }

    ptr_tokens=&tokens[0][0]; //assigning pointer
    char homelock [4][4]={
                            {"****"},
                            {"++++"},
                            {"////"},
                            {"????"}
                         };
    homelock_ptr=&homelock[0][0];

    //assiging count 0.
    
    //colour code
    //1-green
    //2-red
    //3-blue
    //4-yellow

    system("clear");

    while(homecount[tokens[0][3]-1]!=4) //terminating condition
    {
        player();
    }
    system("clear");
    display();
}

void player()
{
    char dummy;
    int user_choice=1,value;

    if (homecount[0]==4)
    {
        goto end;
    }

    value=dice();

    printf("\n\nLUDO GAME (TERMINAL BASED)\n\n");

    display();

    if(value==6 && choices[0]+homecount[0]<5)
    {
        choices[0]++;
    }

    for(int i=0;i<4;i++)
    {
        printf("\nThe Coords for %d are %d %d", tokens[i][0], tokens[i][1], tokens[i][2]);
    }

    printf("\nThe Dice Value is %d\n\n", value);

    if(choices[0]>0)
    {
        if(choices[0]>1||homecount[0]>1)
        {
            printf("Enter the choice: ");
            scanf("%d", &user_choice);
        }

        if(value==6 && user_choice!=homecount[0]+choices[0])
        {
            choices[0]--;
        }

        else if(value==6 && choices[0]!=5)
        {
            tokens[user_choice-1][1]=1;
            tokens[user_choice-1][2]=14;
            homelock_manipulator(tokens[user_choice-1][3]-1);
            value=0;
        }

        area_finder(value, (user_choice-1), tokens[user_choice-1][4]); //value, sequence, colour symbol
    }   

        if(choices[0]==1)
        {
        printf("PRESS ENTER TO CONTINUE.");
        dummy=getchar();
        }
        
        system("clear");

    end:
}

void homelock_manipulator(int colourcode)
{
    switch (4-homecount[0]-choices[0])
    {
    case 0:
        *(homelock_ptr+4*colourcode)='_';
        break;

    case 1:
        *(homelock_ptr+4*colourcode+1)='_';
        break;

    case 2:
        *(homelock_ptr+4*colourcode+2)='_';
        break;
    
    case 3:
        *(homelock_ptr+4*colourcode+3)='_';
        break;
    
    default:
        break;
    }
}

void area_finder(int value, int user_choice,char c)
{
    switch(tokens[user_choice][1]) //identifying location(area) of token from itsarea
    {
        case 1:
        area_g(value,c,user_choice);
        break;

        case 2:
        area_r(value,c,user_choice);
        break;

        case 3:
        area_b(value,c,user_choice);
        break;

        case 4:
        area_y(value,c,user_choice);
        break;
    }

}

void area_g(int value, char c, int user_choice)
{
    int temp=tokens[user_choice][2];
    tokens[user_choice][2]+=value;
    int x=tokens[user_choice][2];

    if(x>18)
    {
        *(gr_ptr+(18-temp)*3)='_';//clearing past record

        value=x-18; //finding the coordinates to move in next kingdom

        tokens[user_choice][2]=value; //assigning the coords of the next kingdom

        value=0; //as coordinates are already assigned, putting value = 0
        
        tokens[user_choice][1]++;

        area_r(value, c, user_choice);
        goto end;
        //to move to next kingdom
    }

    if(x<=6) //moving pice to new location
    {   
        *(gr_ptr+2+3*(x-1))=c;
    }

    else if(x==7)
    {
        *(gr_ptr+1+3*5)=c;
    }

    else if(tokens[user_choice][3]==1 && (x<13 || temp<13))
    {
        if(x==13)  //condition for reaching homecount
        {
            homecount[0]++; //increasing count by 1
            tokens[user_choice][1]=0;
            tokens[user_choice][2]=0;
        }

        else if(x>13) //if value is larger then dumping the increament
        {
            x=temp;
            value=0;
        }

        else
        {
        *(gr_ptr+(12-x)*3+1)=c;
        }
    }

    else
    {
        if(x>7 && x<13)
        {
            x+=5;
        }

        else if(x==13 && temp==7)
        {
            x=18;
        }
        *(gr_ptr+(18-x)*3)=c;
    }

    tokens[user_choice][2]=x;

    end:
    //clearing previous location

    if(value!=0)
    {
    if(temp<=6) //for values 0 to 6
    {   
        *(gr_ptr+2+3*(temp-1))='_';
    }

    else if(temp==7) //for value is equal to 7
    {
        *(gr_ptr+1+3*5)='_';
    }

    else if(tokens[user_choice][3]==1 && temp<13) //for home lane
    {
        *(gr_ptr+(12-temp)*3+1)='_';
    }

    else //for values between 13 to 18
    {
        if(temp>7 && temp<13)
        {
        temp+=5;
        }
        
        *(gr_ptr+(18-temp)*3)='_';
    }
    }
}

void area_r(int value, char c, int user_choice)
{
    int temp=tokens[user_choice][2];
    tokens[user_choice][2]+=value;
    int x=tokens[user_choice][2];

    if(x>18)
    {
        *(re_ptr+(temp-13))='_';//clearing past record

        value=x-18;

        tokens[user_choice][2]=value; //assigning the coords of the next kingdom;

        value=0;
        tokens[user_choice][1]+=1;
        area_b(value,c,user_choice);
        goto end;
        //to move to next kingdom
    }

    //moving pice to new location
    if(x<=6)  //if it is in the same kingdom
    {   
        *(re_ptr+18-x)=c;
    }

    else if(x==7)
    {
        *(re_ptr+6)=c;
    }

    else if(tokens[user_choice][3]==2 && (x<13 || temp<13))
    {
        if(x==13)  //condition for reaching homecount
        {
            homecount[1]++;; //increasing count by 1
        }

        else if(tokens[user_choice][2]>13) //if value is larger then dumping the increament
        {
            x=temp;
            value=0;
        }

        else
        {
            *(re_ptr+x-1)=c;
        }
    }

    else
    {
        if(x>7 && x<13)
        {
            x+=5;
        }

        else if(x==13 && temp==7)
        {
            x=18;
        }

        *(re_ptr+(x-13))=c;
    }

    tokens[user_choice][2]=x;

    //clearing previous location

    end:

    if(value!=0)
    {
    if(temp<=6)
    {   
        *(re_ptr+18-temp)='_';
    }

    else if(temp==7)
    {
        *(re_ptr+6)='_';
    }

    else if(tokens[user_choice][3]==2 && temp<13)
    {
        *(re_ptr+temp-1)='_';
    }

    else
    {
        if(temp>7 && temp<13)
        {
            temp+=5;
        }
        *(re_ptr+temp-13)='_';
    }
    }
}

void area_b(int value, char c, int user_choice)
{
    int temp=tokens[user_choice][2];
    tokens[user_choice][2]+=value;
    int x=tokens[user_choice][2];

    if(x>18)
    {
        *(bl_ptr+3*temp-37)='_';//clearing past record

        value=x-18;
        tokens[user_choice][2]=value;
        value=0;
        tokens[user_choice][1]++;
        area_y(value, c, user_choice);
        goto end;
        //to move to next kingdom
    }

    if(x<=6) //moving pice to new location
    {   
        *(bl_ptr+18-(3*(x)))=c;
    }

    else if(x==7)
    {
        *(bl_ptr+1)=c;
    }

    else if(tokens[user_choice][3]==3 && (x<13 || temp<13))
    {
        if(x==13)  //condition for reaching homecount
        {
            homecount[2]++;; //increasing count by 1
        }

        else if(x>13) //if value is larger then dumping the increament
        {
            x=temp;
            value=0;
        }

        else
        {
        *(bl_ptr+1+(x-7)*3)=c;
        }
    }

    else
    {
        if(x>7 && x<13)
        {
        x+=5;
        }

        else if(x==13 && temp==7)
        {
            x=18;
        }

        *(bl_ptr+3*(x)-37)=c;
    }

    tokens[user_choice][2]=x;

    end: //for moving to next kingdom

    //clearing previous location    

    if(value!=0)
    {

    if(temp <= 6) //moving pice to new location
    {   
        *(bl_ptr+18-(3*temp))='_';
    }

    else if(temp == 7)
    {
        *(bl_ptr+1)='_';
    }

    else if(tokens[user_choice][3]==3 && temp<13)
    {
        *(bl_ptr+1+(temp-7)*3)='_';
    }

    else
    {
        if(temp>7 && temp<13)
        {
        temp+=5;
        }
        *(bl_ptr+3*temp-37)='_';
    }
    }
}

void area_y(int value, char c, int user_choice)
{
    int temp=tokens[user_choice][2];
    tokens[user_choice][2]+=value;
    int x=tokens[user_choice][2];

    if(x>18)
    {
        *(ye_ptr+30-temp)='_';

        value=x-18;
        tokens[user_choice][2]=value;
        value=0;
        tokens[user_choice][1]=1;
        area_g(value,c,user_choice);
        goto end;
        //to move to next kingdom
    }

    if(x<=6) //moving pice to new location
    {   
        *(ye_ptr+x-1)=c;
    }

    else if(x==7)
    {
        *(ye_ptr+11)=c;
    }

    else if(tokens[user_choice][3]==4 && (x<13 || temp<13))
    {
        if(x==13)  //condition for reaching homecount
        {
            homecount[3]++;; //increasing count by 1
        }

        else if(x>13) //if value is larger then dumping the increament
        {
            x=temp;
            value=0;
        }

        else
        {
        *(ye_ptr + 18 - x)=c;
        }
    }

    else
    {
        if(x>7 && x<13)
        {
        x+=5;
        }

       else if(x==13 && temp==7)
        {
            x=18;
        } 

        *(ye_ptr+30-x)=c;
    }

    tokens[user_choice][2]=x;

    end:

    //clearing previous location    

    if(value!=0)
    {
        if(temp<=6) //moving pice to new location
        {   
            *(ye_ptr+temp-1)='_';
        }

        else if(temp==7)
        {
            *(ye_ptr+11)='_';
        }

        else if(tokens[user_choice][3]==4 && temp<13)
        {
            *(ye_ptr + 18 - temp)='_';
        }

        else
        {
            if(temp>=7 && temp<13)
            {
            temp+=5;
            }
            *(ye_ptr+30-temp)='_';
        }
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

void display()
{
    for(i=0;i<6;i++) //blue
    {
        for(j=0;j<12 && i!=2 && i!=4;j++)
        {
            printf(" ");
        }

        if(i==2)
        {
            printf("  %c   %c     ", *(homelock_ptr+4),*(homelock_ptr+4+1));
        }
        else if(i==4)
        {
            printf("  %c   %c     ", *(homelock_ptr+4+2),*(homelock_ptr+4+3));
        }

        for(j=0;j<3;j++)
        {
            printf("%c ", *(bl_ptr+j+i*3));
        }

        for(j=0;j<12 && i!=2 && i!=4;j++)
        {
            printf(" ");
        }

        if(i==2)
        {
            printf("  %c   %c     ", *(homelock_ptr+8),*(homelock_ptr+8+1));
        }
        else if(i==4)
        {
            printf("  %c   %c     ", *(homelock_ptr+8+2),*(homelock_ptr+8+3));
        }

        printf("\n");
    }

    for(i=0;i<3;i++) //red and blue
    {

        for(j=0;j<6;j++)
        {
            printf("%c ", *(re_ptr+j+i*6));
        }

        if(i==0)
        {
            printf("  %d   ", homecount[2]);
        }
        
        else if(i==1)
        {
            printf("%d   %d ", homecount[1], homecount[3]);
        }

        else
        {
            printf("  %d   ", homecount[0]);
        }

        for(j=0;j<6;j++)
        {
            printf("%c ", *(ye_ptr+j+i*6));
        }
        printf("\n");
    }

    for(i=0;i<6;i++) //green
    {
        for(j=0;j<12 && i!=2 && i!=4;j++)
        {
            printf(" ");
        }

        if(i==2)
        {
            printf("  %c   %c     ", *(homelock_ptr),*(homelock_ptr+1)); //green home
        }
        else if(i==4)
        {
            printf("  %c   %c     ", *(homelock_ptr+2),*(homelock_ptr+3));
        }

        for(j=0;j<3;j++)
        {
            printf("%c ", *(gr_ptr+j+i*3));
        }

        for(j=0;j<12 && i!=2 && i!=4;j++)
        {
            printf(" ");
        }

        if(i==2)
        {
            printf("  %c   %c     ", *(homelock_ptr+12),*(homelock_ptr+12+1));
        }
        else if(i==4)
        {
            printf("  %c   %c     ", *(homelock_ptr+12+2),*(homelock_ptr+12+3));
        }
        printf("\n");
    }
}