//program for ludo (terminal based)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int i,j;
void display(); //for displaying (giving input the four char arrays)

void area_finder(int,int *, int,char); //value, initial kingdomn(kingdom number and postion)
void area_g(int,int *, char, int); //navigation function in green kingdom
void area_r(int,int *, char, int); //navigation function in red kingdom
void area_b(int,int *, char, int); //navigation function in blue kingdom
void area_y(int,int *, char, int); //navigation function in yellow kingdom
void homelock_manipulator(int);
int difference(int);
void gr_player();
/*void re_player();
void bl_player();
void ye_player();*/

int dice(void); //dice

//declaring count of homecount tokens (won tokens)
int tokens[16][4]; //coords of tokens (kingdom/coord/colour/sequence)
int homecount[4]={0,0,0,0};
int choices[4]={0,0,0,0}; //showing no. of choices (g,r,b,y)
int *ptr_tokens; //for storing posititon of tokens (kingdom,location)

char *gr_ptr, *bl_ptr, *re_ptr, *ye_ptr;//pointers pointing to the area arrays
char *homelock_ptr; //pointer pointing to the arrays storing data for homelock ptr.
    
int main(void)
{
    char green_area[6][3],blue_area[6][3],red_area[3][6], yellow_area[3][6];
    gr_ptr=&green_area[0][0];bl_ptr=&blue_area[0][0];re_ptr=&red_area[0][0];ye_ptr=&yellow_area[0][0];

    for(i=0;i<18;i++)
    {
        *(gr_ptr+i)=*(bl_ptr+i)=*(re_ptr+i)=*(ye_ptr+i)='_';//assigning the blank spaces.
    }

    for(i=0;i<16;i++)
    {
        tokens[i][3]=i+1;
    }

    for(i=0,j=1;i<16;i++)
    {
        tokens[i][2]=j;
        if(i%4==3)
        {
            j++;
        }
    }

    ptr_tokens=&tokens[0][0]; //liking pointer
    char homelock [4][4]={
                            {"****"},
                            {"++++"},
                            {"////"},
                            {"????"}
                         };
    homelock_ptr=&homelock[0][0];

    //assiging count 0.

    //1-green
    //2-red
    //3-blue
    //4-yellow

    system("clear");
    printf("welcome\n");

    while(homecount[*(ptr_tokens+2)-1]!=1) //colour code
    {
        gr_player();
    }
    system("clear");
    display();
}

void area_finder(int value, int *token, int user_choice,char c)
{
    switch(*(token+user_choice))
    {
        case 1:
        area_g(value, token,c, user_choice);
        break;

        case 2:
        area_r(value, token,c, user_choice);
        break;

        case 3:
        area_b(value, token,c, user_choice);
        break;

        case 4:
        area_y(value, token,c, user_choice);
        break;
    }

}

void area_g(int value,int *token,char c, int user_choice)
{
    int temp=*(token+1+user_choice);
    *(token+1+user_choice)+=value;

    if(*(token+1+user_choice)>18)
    {
        *(gr_ptr+(18-temp)*3)='_';//clearing past record

        value=*(token+1+user_choice)-18; //finding the coordinates to move in next kingdom
        *(token+1+user_choice)=value; //assigning the coords of the next kingdom
        value=0; //as coordinates are already assigned, putting value = 0
        *(token+user_choice)+=1;

        area_r(value, token, c,user_choice);
        goto end;
        //to move to next kingdom
    }

    if(*(token+1+user_choice)<=6) //moving pice to new location
    {   
        *(gr_ptr+2+3*(*(token+1+user_choice)-1))=c;
    }

    else if(*(token+1+user_choice)==7)
    {
        *(gr_ptr+1+3*5)=c;
    }

    else if(*(token+2+user_choice)==1 && (*(token+1+user_choice)<13 || temp<13))
    {
        if(*(token+1+user_choice)==13)  //condition for reaching homecount
        {
            homecount[0]++; //increasing count by 1
        }

        else if(*(token+1+user_choice)>13) //if value is larger then dumping the increament
        {
            *(token+1+user_choice)=temp;
            value=0;
        }

        else
        {
        *(gr_ptr+(12-*(token+1+user_choice))*3+1)=c;
        }
    }

    else
    {
        if(*(token+1+user_choice)>7 && *(token+1+user_choice)<13)
        {
        *(token+1+user_choice)+=5;
        }

        else if(*(token+1+user_choice)==13 && temp==7)
        {
            *(token+1+user_choice)=18;
        }
        printf("Alpha\n");
        *(gr_ptr+(18-*(token+1+user_choice))*3)=c;
    }

    if(value!=0)
    {
    //clearing previous location
    if(temp<=6) //moving pice to new location
    {   
        *(gr_ptr+2+3*(temp-1))='_';
    }

    else if(temp==7)
    {
        *(gr_ptr+1+3*5)='_';
    }

    else if(*(token+2)==1 && temp<13)
    {
        *(gr_ptr+(12-temp)*3+1)='_';
    }

    else
    {
        if(temp>7 && temp<13)
        {
        temp+=5;
        }
        
        *(gr_ptr+(18-temp)*3)='_';
    }
    }

    end:
}

void area_r(int value,int *token, char c, int user_choice)
{
    int temp=*(token+user_choice+1);
    *(token+user_choice+1)+=value;

    if(*(token+user_choice+1)>18)
    {
        *(re_ptr+(temp-13))='_';//clearing past record

        value=*(token+user_choice+1)-18;
        *(token+user_choice+1)=value;
        value=0;
        *(token)+=1;
        area_b(value, token,c,user_choice);
        goto end;
        //to move to next kingdom
    }

    //moving pice to new location
    if(*(token+user_choice+1)<=6)  //if it is in the same kingdom
    {   
        *(re_ptr+18-*(token+user_choice+1))=c;
    }

    else if(*(token+user_choice+1)==7)
    {
        *(re_ptr+6)=c;
    }

    else if(*(token+user_choice+2)==2 && (*(token+user_choice+1)<13 || temp<13))
    {
        if(*(token+user_choice+1)==13)  //condition for reaching homecount
        {
            homecount[1]++;; //increasing count by 1
        }

        else if(*(token+user_choice+1)>13) //if value is larger then dumping the increament
        {
            *(token+user_choice+1)=temp;
            value=0;
        }

        else
        {
        *(re_ptr+*(token+user_choice+1)-1)=c;
        }
    }

    else
    {
        if(*(token+user_choice+1)>7 && *(token+user_choice+1)<13)
        {
            *(token+user_choice+1)+=5;
        }

        else if(*(token+user_choice+1)==13 && temp==7)
        {
            *(token+user_choice+1)=18;
        }

        *(re_ptr+(*(token+user_choice+1)-13))=c;
    }

    //clearing previous location

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

    else if(*(token+user_choice+2)==2 && temp<13)
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

    end:
}

void area_b(int value,int *token, char c, int user_choice)
{
    int temp=*(token+user_choice+1);
    *(token+user_choice+1)+=value;

    if(*(token+user_choice+1)>18)
    {
        *(bl_ptr+3*temp-37)='_';//clearing past record

        value=*(token+user_choice+1)-18;
        *(token+user_choice+1)=value;
        value=0;
        *(token)+=1;
        area_y(value, token, c, user_choice);
        goto end;
        //to move to next kingdom
    }

    if(*(token+user_choice+1)<=6) //moving pice to new location
    {   
        *(bl_ptr+18-(3*(*(token+user_choice+1))))=c;
    }

    else if(*(token+user_choice+1)==7)
    {
        *(bl_ptr+1)=c;
    }

    else if(*(token+user_choice+2)==3 && (*(token+user_choice+1)<13 || temp<13))
    {
        if(*(token+user_choice+1)==13)  //condition for reaching homecount
        {
            homecount[2]++;; //increasing count by 1
        }

        else if(*(token+user_choice+1)>13) //if value is larger then dumping the increament
        {
            *(token+user_choice+1)=temp;
            value=0;
        }

        else
        {
        *(bl_ptr+1+(*(token+user_choice+1)-7)*3)=c;
        }
    }

    else
    {
        if(*(token+user_choice+1)>7 && *(token+user_choice+1)<13)
        {
        *(token+user_choice+1)+=5;
        }

        else if(*(token+user_choice+1)==13 && temp==7)
        {
            *(token+user_choice+1)=18;
        }

        *(bl_ptr+3*(*(token+user_choice+1))-37)=c;
    }

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

    else if(*(token+user_choice+2)==3 && temp<13)
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

    end:
}

void area_y(int value,int *token, char c, int user_choice)
{
    int temp=*(token+user_choice+1);
    *(token+user_choice+1)+=value;

    if(*(token+user_choice+1)>18)
    {
        *(ye_ptr+30-temp)='_';

        value=*(token+user_choice+1)-18;
        *(token+user_choice+1)=value;
        value=0;
        *(token)=1;
        area_g(value, token,c,user_choice);
        goto end;
        //to move to next kingdom
    }

    if(*(token+user_choice+1)<=6) //moving pice to new location
    {   
        *(ye_ptr+*(token+user_choice+1)-1)=c;
    }

    else if(*(token+user_choice+1)==7)
    {
        *(ye_ptr+11)=c;
    }

    else if(*(token+user_choice+2)==4 && (*(token+user_choice+1)<13 || temp<13))
    {
        if(*(token+user_choice+1)==13)  //condition for reaching homecount
        {
            homecount[3]++;; //increasing count by 1
        }

        else if(*(token+user_choice+1)>13) //if value is larger then dumping the increament
        {
            *(token+user_choice+1)=temp;
            value=0;
        }

        else
        {
        *(ye_ptr + 18 - *(token+user_choice+1))=c;
        }
    }

    else
    {
        if(*(token+user_choice+1)>7 && *(token+user_choice+1)<13)
        {
        *(token+user_choice+1)+=5;
        }

       else if(*(token+user_choice+1)==13 && temp==7)
        {
            *(token+user_choice+1)=18;
        } 

        *(ye_ptr+30-*(token+user_choice+1))=c;
    }

    //clearing previous location    

    if(value!=0)
    {
        if(temp<=6 && *(token)==4) //moving pice to new location
        {   
            *(ye_ptr+temp-1)='_';
        }

        else if(temp==7)
        {
            *(ye_ptr+11)='_';
        }

        else if(*(token+user_choice+2)==4 && temp<13)
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

    end:
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

void gr_player()
{
    char dummy;
    int user_choice=1,value;
    int diff[3]={7,7,7}; //stating distance between tokens

    /* diff[1]=difference (1,2) */

    if (homecount[0]==4)
    {
        goto end;
    }

    value=dice();

    switch (choices[0])
    {
    case 1:
        break;

    case 4:
        diff[2]=difference(3);

        if(diff[2]>6)
        {
        break;
        }

    case 3:
        diff[1]=difference(2);

        if(diff[1]>6)
        {
        break;
        }

    case 2:
        diff[0]=difference(1);
        printf("\nDiff 0 is %d", diff[0]);
        break;
    
    default:
        break;
    }

    if(choices[0]>1)
    {
        while(value==diff[0] || value==diff[1] || value == diff[2])
        {
        value=dice();
        }
    }

    display();

    if(value==6 && choices[0]+homecount[0]<4)
    {
        choices[0]++;
    }

    printf("%d", choices[0]);

    for(int i=0;i<4;i++)
    {
        printf("\nThe Coords for %d are %d %d", tokens[i][3], tokens[i][0], tokens[i][1]);
    }

    printf("\nThe Dice Value is %d\n\n", value);

    if(choices[0]>0)
    {
        if(choices[0]>1)
        {
            printf("Enter the choice: ");
            scanf("%d", &user_choice);
        }

        if(value==6 && user_choice!=homecount[0]+choices[0])
        {
            choices[0]--;
        }

    else if(value==6)
    {
        *(ptr_tokens+(user_choice-1)*4)=1;
        *(ptr_tokens+(user_choice-1)*4 + 1)=14;
        homelock_manipulator(0);
        value=0;
    }

        area_finder(value, ptr_tokens, 4*(user_choice-1),'*');
    }   
        printf("PRESS ENTER TO CONTINUE.\n");
        dummy=getchar();
        system("clear");

    end:
}

void homelock_manipulator(int colourcode)
{
    bool kill=0;

    if(kill!=1)
    {
        switch (4-homecount[colourcode]-choices[colourcode])
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

    else
    {   
        char c;
        switch (colourcode+1)
        {
        case 1:
            c='*';
            break;
        
        case 2:
            c='+';
            break;
        
        case 3:
            c='/';
            break;
        
        case 4:
            c='?';
            break;
        }

        switch (4-homecount[colourcode]-choices[colourcode])
        {
        case 1:
            *(homelock_ptr+4*colourcode+2)=c;
            break;

        case 2:
            *(homelock_ptr+4*colourcode+1)=c;
            break;

        case 3:
            *(homelock_ptr+4*colourcode+0)=c;
            break;
        
        case 0:
            *(homelock_ptr+4*colourcode+3)=c;
            break;
        
        default:
            break;
        }
    }
}

int difference(int i)
{
    if(tokens[0][i]-tokens[0][i-1]>1)
    {
        return(7);
    }

    else if(tokens[0][i]!=tokens[0][i-1])
    {
        return(13+tokens[1][i]-tokens[1][i-1]);
    }

    else
    {
        return(tokens[1][i]-tokens[1][i-1]);
    }
}