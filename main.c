#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>



struct payment
{
    char mode[20],Tid[15];
    time_t time;
};

struct student
{
    int fee,paid,due;
    struct payment p;
    char n[50];
    int r,c;//roll and class
} stud,s;

struct teacher
{
    char n[50];
    struct payment p;
    int sal,paid,due;
    int id,no;
} tech,t;




int clscanf();//check class (1-12)
struct payment pay(int);//For Payment Transaction
void recipt(struct student,int);//Display recipt of student
void recipt_t(struct teacher,int);//Display recipt of teacher
void intro();//About Team
void dist();//display all record of Staff
void displayall();//Display all records of students
void head();
void headt();
void display(struct student);//For displaying records
int getfee(int);//for the calculation of fee
//int chkdat(int,int);// for checking date
void start();
void addrec(int);//for adding records
void modrec(int);//for modifying records
void searchrec(int);//for searching records
void delrec(int);//for deleting records
void ext();//for exiting
//void salary(int);//for the calculation of salary of teacher and staff

int w;
void center(char *s)
{
    int y,width;
    COORD c;
    CONSOLE_SCREEN_BUFFER_INFO cs;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cs);
    y = cs.dwCursorPosition.Y;

    width=cs.srWindow.Right - cs.srWindow.Left + 1;
    w=width;

    c.X=width/2 - strlen(s)/2;
    c.Y=y+1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
    printf("%s\n",s);
}



FILE *fs,*ft;//file declaration

time_t tim;



void main(void)
{
    center("");
    int i,j,k;

    system("color 9a");
    for(i=0; i<w; i++)
    {
        printf("\xdb");
    }

    printf("\n");
    center("---     WELCOME TO SCHOOL BILLING SYSTEM    ---");
    printf("\n\n");
    center("--  DEVELOPED BY GROUP 1    --");
    printf("\n");

    for(i=0; i<w; i++)
    {
        printf("\xdb");
    }
    printf("\n");
    printf("\nEnter any key to continue");
    for(i=0; i<5; i++)
    {
        printf(".");
        Sleep(500);//after printing one . another comes after 0.5 seconds
    }

    getch();


    system("cls");//clears the screen
    system("color 6b");
    printf("\n");
    for(i=0; i<w; i++)
    {
        printf("\xdb");
    }

    printf("\n\n");
    center("--  WELCOME TO  --");
    printf("\n");
    center("--   School Billing System Project   --");
    printf("\n\n");

    for(i=0; i<w; i++)
    {
        printf("\xdb");
    }

    time(&tim);
    printf("\n\nCurrent Date and Time : %s",ctime(&tim));


    printf("\n\nEnter any key to start\n");
    for(i=0; i<5; i++)
    {
        printf(".");
        Sleep(500);
    }
    fflush(stdin);
    getch();

    system("color 0f");//1st is for back ground color and second is for text color
    start();
}

void start()
{
    int i,j,ch,c,cl,rnum,q,amount,a=1;//j is for selection of account type
    char name[30];
    system("cls");

    center("---    SCHOOL BILLING SYSTEM    ---");
    printf("\n\n\t1. Database \n\t2. Payments \n\t3. Developers \n\t4. Exit \n\tEnter Your Choice : ");
    scanf("%d",&ch);
    switch(ch)
    {
    case 1:
        system("cls");
        center("--  DATABASE    --");
        printf("\n\t1. Student");
        printf("\n\t2. Teachers and Staffs");
        printf("\n\t3. Back to main Menu");
        printf("\n\tAccount type : ");
        fflush(stdin);
        scanf("%d",&j);

        switch (j)
        {
        case 3:
            start();
        case 1:
            system("cls");
            center("--   STUDENT    --");
            printf("\n\n\t1. Add record");
            printf("\n\t2. Display all records");
            printf("\n\t3. Search record");
            printf("\n\t4. Modify record");
            printf("\n\t5. Delete record");
            printf("\n\t6. Exit");
            printf("\n\n\t Enter choice : ");
            fflush(stdin);
            scanf("%d",&i);

            switch (i)
            {
            case 1:
                addrec(j);//function call
                start();//function call
            case 2:
                displayall();
                start();
            case 3:
                searchrec(j);
                start();
            case 4:
                modrec(j);
                start();
            case 5:
                delrec(j);
                start();
            case 6:
                ext();
            default :
                printf("\n\n\tInvalid entry!!");
                system("pause");
                start();
            }

        case 2:
            system("cls");
            center("---     TEACHER AND STAFF   ---");
            printf("\n\t1. Add record");
            printf("\n\t2. Display all");
            printf("\n\t3. Search record");
            printf("\n\t4. Modify record");
            printf("\n\t5. Delete record");
            printf("\n\t6. Exit");
            printf("\n\n\tEnter Choice : ");
            fflush(stdin);
            scanf("%d",&i);
            switch (i)
            {
            case 1:
                addrec(j);
                start();
            case 2:
                dist();
                start();
            case 3:
                searchrec(j);
                start();
            case 4:
                modrec(j);
                start();
            case 5:
                delrec(j);
                start();
            case 6:
                ext();
            default :
                printf("\n\n\tInvalid entry!!");
                system("pause");
                start();
            }
        default :
            printf("\n\n\tInvalid entry!!");
            system("pause");
            start();
        }

    case 2:
        //payment
        system("cls");
        center("---     Payment     ---");
        printf("\n\n\t1. Student Fee Submit");
        printf("\n\n\t2. Teacher and staff Salary Payment");
        printf("\n\n\tEnter your choice : ");
        scanf("%d",&c);
        switch(c)
        {
        case 1:
            system("cls");
            center("Enter Student Details");
            printf("\n\nEnter Name : ");
            scanf("%s",&name);
            printf("\nEnter Class : ");
            scanf("%d",&cl);
            printf("\nEnter Roll Number : ");
            scanf("%d",&rnum);

            fs=fopen("student","rb+");
                while(fread(&stud,sizeof(stud),1,fs)==1)
                {
                    if (strcmpi(name,stud.n)==0 && cl==stud.c && rnum==stud.r)
                    {
                        system("cls");
                        a=0;
                        center("Student Details");
                        printf("\n\n");
                        display(stud);
                        if(stud.due==0)
                        {
                            printf("\nFee is Full Paid!!");
                            getch();
                            break;
                        }

                        //calcfee
                        printf("\n\nNumber of Quarter to be paid for(out of 4) : ");
                        scanf("%d",&q);
                        amount=q*(stud.fee/4);

                        printf("\n\nEnter any key to continue...");
                        getch();

                        stud.p=pay(amount);
                        stud.paid+=amount;
                        stud.due=stud.fee-stud.paid;

                        recipt(stud,amount);

                        fseek(fs,-sizeof(stud),SEEK_CUR);
                        fwrite(&stud,sizeof(stud),1,fs);
                        break;

                    }
                }
                if (a==1)
                    printf("\n\nRECORD NOT FOUND");
                printf("\n\n");
                system("pause");
                fflush(stdin);
                fclose(fs);
            start();

        case 2:
            system("cls");
            center("Enter Teacher/Staff Details");
            printf("\nEnter Name : ");
            scanf("%s",&name);
            printf("\nEnter ID Number : ");
            scanf("%d",&rnum);

            ft=fopen("teacher","rb+");
            while(fread(&tech,sizeof(tech),1,ft)==1)
            {
                if (strcmp(name,tech.n)==0 && tech.id==rnum)
                {
                    a=0;
                    system("cls");
                    center("Teacher Details");
                    printf("\n");

                    disp(tech);
                    if(tech.due==0)
                    {
                        printf("\nFee is Full Paid!!");
                        getch();
                        break;
                    }

                    printf("\nEnter Number of months to be paid for : ");
                    scanf("%d",&q);

                    amount = q * (tech.sal/12);
                    tech.p=pay(amount);
                    tech.paid+=amount;
                    tech.due=tech.sal-tech.paid;

                    recipt_t(tech,amount);

                    fseek(ft,-sizeof(tech),SEEK_CUR);
                    fwrite(&tech,sizeof(tech),1,ft);
                    break;

                }
            }
            if (a==1)
                printf("\n\nRECORD NOT FOUND");
            printf("\n\n");
            system("pause");
            fflush(stdin);
            fclose(ft);
            start();
        }

    case 3:
        intro();
        start();

    case 4:
        ext();

    default:
        //invalid choice
        printf("\nInvalid Input! Please Enter Correct Input...");
        start();
    }
}

void addrec(int j)
{
    char c='y';
    system("cls");

    center("ADD RECORD");
    if (j==1)
    {
        while(c=='y'||c=='Y')
        {
            int a=1;
            printf("\n\nEnter the name of student : ");
            fflush(stdin);
            scanf("%s",stud.n);
            printf("\nEnter the class : ");
            fflush(stdin);
            stud.c=clscanf();
            printf("\nEnter the Roll No. : ");
            fflush(stdin);
            scanf("%d",&stud.r);

            stud.fee = getfee(stud.c);
            stud.paid=0;
            stud.due=stud.fee;
            strcpy(stud.p.mode,"Nil");
            strcpy(stud.p.Tid,"Nil");

            fs=fopen("student","ab+");//opening a binary file in apend mode
            fwrite(&stud,sizeof(stud),1,fs);
            fclose(fs);
            printf("\n\nRecord added Successfully...");
            printf("\n\nDo you want to add more record (press y or Y) : ");
            fflush(stdin);
            c=getch();
        }
        //getch();
    }
    if (j==2)
    {
        while(c=='y'||c=='Y')
        {
            int a=1;
            printf("\n\nEnter name of Teacher/Staff : " );
            fflush(stdin);
            scanf("%s",tech.n);
            printf("\nEnter Teacher/Staff Id : ");
            fflush(stdin);
            scanf("%d",&tech.id);
            printf("\nEnter number of Class/Shift per month : ");
            scanf("%d",&tech.no);
            fflush(stdin);
            tech.sal = 1000 * tech.no * 12;
            tech.paid=0;
            tech.due=tech.sal;
            strcpy(tech.p.mode,"Nil");
            strcpy(tech.p.Tid,"Nil");

            ft=fopen("teacher","ab+");
            fwrite(&tech,sizeof(tech),1,ft);
            fclose(ft);
            printf("\n\nRecord added Successfully...");
            printf("\n\nDo you want to add more record(press y or Y) : ");
            fflush(stdin);
            c=getch();
        }
        fflush(stdin);
        printf("\n\n");
        system("pause");
    }
}

void searchrec(int j)
{
    char name[50],namet[50];
    int a=1,choice,cl,rll;
    char c='y';
    if (j==1)
    {
        while(c=='y'||c=='Y')
        {
            //int a=1;
            system("cls");

            center("--  SEARCH RECORD   --");
            printf("\n\n\tEnter Search Type : ");
            printf("\n\n\t1. Search by Name");
            printf("\n\n\t2. Search by Class");
            printf("\n\n\t3. Search by Roll Num");
            printf("\n\n\t4. Exit");
            printf("\n\n\tEnter your choice : ");
            fflush(stdin);
            scanf("%d",&choice);
            system("cls");
            printf("\n\n");
            center("SEARCH RECORD");
            if (choice==1)
            {
                a=1;
                printf("\n\nEnter Name of Student to Search : ");
                fflush(stdin);
                scanf("%s",name);
                fs=fopen("student","rb");

                system("cls");
                center("--   SEARCH RESULT   --");

                while(fread(&stud,sizeof(stud),1,fs)==1)
                {
                    if (strcmpi(name,stud.n)==0)
                    {
                        a=0;
                        display(stud);
                    }
                }
                if (a==1)
                    printf("\n\nRECORD NOT FOUND");
                printf("\n\n");
                system("pause");
                fflush(stdin);
                fclose(fs);
            }
            else if (choice==2)
            {
                a=1;
                printf("\n\nEnter Class of Student to Search : ");
                fflush(stdin);
                cl=clscanf();
                fs=fopen("student","rb");

                system("cls");
                center("--   SEARCH RESULT   --");

                while(fread(&stud,sizeof(stud),1,fs)==1)
                {
                    if (stud.c==cl)
                    {
                        a=0;
                        display(stud);
                    }
                }
                if (a==1)
                    printf("\n\nRECORD NOT FOUND");
                printf("\n\n");
                system("pause");
                fflush(stdin);
                fclose(fs);
            }
            else if (choice==3)
            {
                a=1;
                printf("\n\nEnter Roll Num of Student to Search : ");
                fflush(stdin);
                rll=clscanf();
                fs=fopen("student","rb");

                system("cls");
                center("--   SEARCH RESULT   --");

                while(fread(&stud,sizeof(stud),1,fs)==1)
                {
                    if (rll==stud.r)
                    {
                        a=0;
                        display(stud);
                    }
                }
                if (a==1)
                    printf("\n\nRECORD NOT FOUND");
                printf("\n\n");
                system("pause");
                fflush(stdin);
                fclose(fs);
            }
            else if(choice==4)
            {
                ext();
            }
            else
            {
                printf("\n\n\n\t\tINVALID ENTRY!!!!\n\n\t\t");
                system("pause");
                searchrec(1);
            }
            printf("\n\nDo you want to continue with the process(press y or Y) : ");
            fflush(stdin);
            c=getch();
        }
        getch();
    }
    if (j==2)
    {
        while(c=='y'||c=='Y')
        {
            int a=1;
            system("cls");
            center("SEARCH RECORD");
            printf("\n\nEnter Name of Teacher/Staff to Search : ");
            fflush(stdin);
            scanf("%s",&namet);
            ft=fopen("teacher","rb");

            system("cls");
            center("--   SEARCH RESULT   --");

            while(fread(&tech,sizeof(tech),1,ft)==1)
            {
                if (strcmp(namet,tech.n)==0)
                {
                    a=0;
                    printf("\nName = %s",tech.n);
                    printf("\nTeacher/Staff Id = %d",tech.id);
                    printf("\nYearly Salary = %d",tech.sal);

                    printf("\nPaid : %d",tech.paid);
                    printf("\nOutstanding : %d",tech.due);
                    if(strcmpi("Nil",tech.p.Tid)==0)
                        printf("\nLast fee paid on : No Payment Yet\n");
                    else
                        printf("\nLast fee paid on : %s",ctime(&tech.p.time));
                    printf("Mode of payment : %s",tech.p.mode);
                    printf("\nTransaction ID : %s\n\n",tech.p.Tid);
                }
            }
            if (a==1)
                printf("\n\nRECORD NOT FOUND");
            printf("\n\n");
            system("pause");
            fflush(stdin);
            fclose(ft);
            printf("\n\nDo you want to continue with the process(press y or Y) : ");
            fflush(stdin);
            c=getch();
        }
        getch();
    }

}

void modrec(int j)
{

    char name[50];
    int a=1,choice,cl,rolno;
    char c='y';
    if (j==1)
    {
        while(c=='y'||c=='Y')
        {
            system("cls");

            center("--   MODIFY RECORD   --");
            printf("\n\n\tEnter Modify Type ");
            printf("\n\n\t1. Modify by Name ");
            printf("\n\n\t2. Modify by Name & Class");
            printf("\n\n\t3. Modify by Name,Class & Roll Num");
            printf("\n\n\t4. Exit");
            printf("\n\n\tEnter your choice : ");
            fflush(stdin);
            scanf("%d",&choice);
            system("cls");
            center("Enter Details");
            if (choice==1)
            {
                int a=0;
                printf("\n\nEnter Name of Student to Modify : ");
                fflush(stdin);
                scanf("%s",name);
                fs=fopen("student","rb+");
                while(fread(&stud,sizeof(stud),1,fs)==1)
                {
                    a=1;
                    if (strcmpi(name,stud.n)==0)
                    {
                        a=0;
                        printf("\n\n");
                        center("Enter New Details");
                        printf("\n\nEnter New Name of Student : ");
                        fflush(stdin);
                        scanf("%s",stud.n);
                        printf("\nEnter New Class of Student : ");
                        fflush(stdin);
                        stud.c=clscanf();
                        printf("\nEnter New Roll Number of Student : ");
                        fflush(stdin);
                        scanf("%d",&stud.r);
                        fseek(fs,-sizeof(stud),SEEK_CUR);
                        fwrite(&stud,sizeof(stud),1,fs);
                        fclose(fs);
                    }
                }
                if (a==1)
                    printf("\n\nRECORDS NOT FOUND");
                else
                    printf("\n\nRECORDS SUCCESSFULLY  MODIFIED");
                printf("\n\n");
                system("pause");
            }

            else if (choice==2)
            {
                int a=0;
                printf("\n\nEnter Name of Student to Modify: ");
                fflush(stdin);
                scanf("%s",&name);
                printf("\n\nEnter Class of Student to Modify: ");
                fflush(stdin);
                cl=clscanf();
                fs=fopen("student","rb+");
                while(fread(&stud,sizeof(stud),1,fs)==1)
                {
                    a=1;
                    if (strcmpi(name,stud.n)==0 && cl==stud.c)
                    {
                        a=0;
                        center("Enter New Details");
                        printf("\n\nEnter New Name of Student : ");
                        fflush(stdin);
                        scanf("%s",stud.n);
                        printf("\nEnter New Class of Student : ");
                        fflush(stdin);
                        stud.c=clscanf();
                        printf("\nEnter New Roll Number of Student : ");
                        fflush(stdin);
                        scanf("%d",&stud.r);
                        fseek(fs,-sizeof(stud),SEEK_CUR);
                        fwrite(&stud,sizeof(stud),1,fs);
                        fclose(fs);
                    }
                }
                if (a==1)
                    printf("\n\nRECORDS NOT FOUND");
                else
                    printf("\n\nRECORDS SUCCESSFULLY  MODIFIED");
                printf("\n\n");
                system("pause");
            }
            else if (choice==3)
            {
                int a=0;
                printf("\n\nEnter Name of Student to Modify : ");
                fflush(stdin);
                scanf("%s",&name);
                printf("\n\nEnter Class of Student to Modify : ");
                fflush(stdin);
                cl=clscanf();
                printf("\n\nEnter Roll Number of Student to Modify : ");
                fflush(stdin);
                scanf("%d",&rolno);
                fs=fopen("student","rb+");
                while(fread(&stud,sizeof(stud),1,fs)==1)
                {
                    a=1;
                    if (strcmpi(name,stud.n)==0 && cl==stud.c &&rolno==stud.r)
                    {
                        a=0;
                        printf("\nEnter New Name of Student : ");
                        fflush(stdin);
                        scanf("%s",stud.n);
                        printf("\nEnter New Class of Student : ");
                        fflush(stdin);
                        stud.c=clscanf();
                        printf("\nEnter New Roll Number of Student : ");
                        fflush(stdin);
                        scanf("%d",&stud.r);
                        fseek(fs,-sizeof(stud),SEEK_CUR);
                        fwrite(&stud,sizeof(stud),1,fs);
                        fclose(fs);
                    }
                }
                if (a==1)
                    printf("\n\nRECORDS NOT FOUND");
                else
                    printf("\n\nRECORDS SUCCESSFULLY  MODIFIED");
                printf("\n\n");
                system("pause");
            }
            else if (choice==4) ext();
            else
            {
                printf("\n\n\n\t\tINVALID ENTRY!!!!\n\n\t\t");
                system("pause");
                modrec(1);
            }

            printf("\n\nDo you want to continue with the process(press y or Y) : ");
            fflush(stdin);
            c=getch();
        }
        getch();
    }

    if (j==2)
    {
        while(c=='y'||c=='Y')
        {
            int a=1;
            system("cls");
            center("MODIFY RECORD");
            printf("Enter Name of Teacher to Modify : ");
            fflush(stdin);
            scanf("%s",&name);
            ft=fopen("teacher","rb+");
            while(fread(&tech,sizeof(tech),1,ft)==1)
            {
                if (strcmpi(name,tech.n)==0)
                {
                    a=0;
                    center("Enter New Details");
                    printf("\nEnter New Name of Teacher : ");
                    fflush(stdin);
                    scanf("%s",tech.n);
                    printf("\nEnter New Id of Teacher : ");
                    fflush(stdin);
                    scanf("%d",&tech.id);
                    fseek(ft,-sizeof(tech),SEEK_CUR);
                    fwrite(&tech,sizeof(tech),1,ft);
                    fclose(ft);
                }
            }

            if (a==1)
                printf("\n\nRECORD NOT FOUND");
            else
                printf("\n\nRECORD SUCCESSFULLY  MODIFIED");
            printf("\n\n");
            system("pause");
            fflush(stdin);

            printf("\n\nDo you want to continue with the process(press y or Y) : ");
            fflush(stdin);
            c=getch();
        }
        getch();
    }
}

void delrec(int j)
{
    system("cls");
    center("--   DELETE RECORD   --");

    FILE *temp,*t1;
    int a=1,cl,roll;
    char name[50],c='y';
    if (j==1)
    {
        while(c=='y'||c=='Y')
        {
            int a=1;
            printf("\n\nEnter Name of Student to Delete : ");
            fflush(stdin);
            scanf("%s",name);
            printf("\n\nEnter Class of Student to Delete : ");
            scanf("%d",&cl);
            printf("\n\nEnter Roll Number of Student to Delete : ");
            scanf("%d",&roll);
            fs=fopen("student","rb");
            temp=fopen("tempfile","wb");//opening of temporary file for deleting process
            while (fread(&stud,sizeof(stud),1,fs)==1)
            {
                if (strcmpi(stud.n,name)==0 && stud.c==cl && stud.r==roll)
                {
                    a=0;
                    continue;
                }
                else
                {
                    fwrite(&stud,sizeof(stud),1,temp);
                }
            }

            if (a==1)
                printf("\n\nRECORD NOT FOUND");
            else
                printf("\n\nRECORD SUCCESSFULLY  DELETED");
            printf("\n\n");
            system("pause");
            fflush(stdin);

            fclose(fs);
            fclose(temp);
            system("del student");/*all data except the data to be
            deleted in student were 1st moved to temp and data in student
            was deleted*/
            system("ren tempfile, student");//renaming temp to student
            printf("\n\nDo you want to continue with the process(press y or Y) : ");
            fflush(stdin);
            c=getch();
        }
        getch();
    }

    if (j==2)
    {
        a=1;
        char namet[50];
        while(c=='y'||c=='Y')
        {
            printf("\n\nEnter Name of Teacher to Delete Record : ");
            fflush(stdin);
            scanf("%s",&namet);
            ft=fopen("teacher","rb");
            t1=fopen("tempfile1","wb");
            while (fread(&tech,sizeof(tech),1,ft)==1)
            {
                if (strcmp(tech.n,namet)==0)
                {
                    a=0;
                    continue;
                }
                else
                {
                    fwrite(&tech,sizeof(tech),1,t1);
                }
            }

            if (a==1)
                printf("\n\nRECORD NOT FOUND");
            else
                printf("\n\nRECORD SUCCESSFULLY  DELETED");
            printf("\n\n");
            system("pause");
            fflush(stdin);

            fclose(ft);
            fclose(t1);
            system("del teacher");
            system("ren tempfile1, teacher");
            printf("\n\nDo you want to continue with the process(press y or Y) : ");
            fflush(stdin);
            c=getch();
        }
        getch();
    }
}

void ext()
{
    int i;
    system("color 0c");
    printf("\n");
    center("Thank you for using School Billing System Project");
    system("pause");
    system("cls");
    printf("\n");
    center("Exiting");
    printf("\n");
    for(i=0; i<w; i++)
    {
        Sleep(50);
        printf("\xdb");
    }
    getch();
    intro();
    exit(0);
}

int getfee(int x)
{
    int f = 50000;
    f = f + x*10000;
    return f;
}

void display(struct student s)
{
    printf("\nName : %s",s.n);
    printf("\nClass : %d",s.c);
    printf("\nRoll No : %d",s.r);
    printf("\nYearly Fee : %d",s.fee);
    printf("\nPaid : %d",s.paid);
    printf("\nOutstanding : %d",s.due);
    if(strcmpi("Nil",s.p.Tid)==0)
        printf("\nLast fee paid on : No Payment Yet\n");
    else
        printf("\nLast fee paid on : %s",ctime(&s.p.time));
    printf("Mode of payment : %s",s.p.mode);
    printf("\nTransaction ID : %s\n\n",s.p.Tid);
}

void displayall()
{
    int a=1;
    struct student stu;
    system("cls");
    printf("\n");
    center("All Students Record");
    printf("\n");
    head();
    printf("\n");
    fs=fopen("student","rb");
    while(fread(&stu,sizeof(stu),1,fs)==1)
    {
        a=0;
        if(strcmpi("Nil",stu.p.Tid)==0)
            printf("%-8d %-15s %-5d %-10d %-10d %-10d %-12s %-14s %s\n",stu.r,stu.n,stu.c,stu.fee,stu.paid,stu.due,stu.p.mode,stu.p.Tid,"No Payment Yet");
        else
            printf("%-8d %-15s %-5d %-10d %-10d %-10d %-12s %-14s %s",stu.r,stu.n,stu.c,stu.fee,stu.paid,stu.due,stu.p.mode,stu.p.Tid,ctime(&stu.p.time));
    }
    if (a==1)
        printf("\n\nRECORD NOT FOUND");
    printf("\n\n");
    system("pause");
    fflush(stdin);
    fclose(fs);
}

void dist()
{
    int a=1;
    struct teacher stu;
    system("cls");
    printf("\n");
    center("All Staffs Record");
    printf("\n");
    headt();
    printf("\n");
    fs=fopen("teacher","rb");
    while(fread(&stu,sizeof(stu),1,fs)==1)
    {
        a=0;
        if(strcmpi("Nil",stu.p.Tid)==0)
            printf("%-8d %-15s %-7d %-10d %-10d %-10d %-12s %-14s %s\n",stu.id,stu.n,stu.no,stu.sal,stu.paid,stu.due,stu.p.mode,stu.p.Tid,"No Payment Yet");
        else
            printf("%-8d %-15s %-7d %-10d %-10d %-10d %-12s %-14s %s",stu.id,stu.n,stu.no,stu.sal,stu.paid,stu.due,stu.p.mode,stu.p.Tid,ctime(&stu.p.time));
    }
    if (a==1)
        printf("\n\nRECORD NOT FOUND");
    printf("\n\n");
    system("pause");
    fflush(stdin);
    fclose(fs);
}

void headt()
{
    printf("\n%-8s %-15s %-7s %-10s %-10s %-10s %-12s %-14s %s\n","ID Num","Name","Shifts","Salary","Paid","Due","Mode","Transcation Id","Last Payment on");
}

void head()
{
    printf("\n%-8s %-15s %-5s %-10s %-10s %-10s %-12s %-14s %s\n","Roll Num","Name","Class","Fee","Paid","Due","Mode","Transcation Id","Last Payment on");
}

int clscanf()
{
    int mnt,mon;
    fflush(stdin);
    scanf("%d",&mnt);
    if (mnt>12 ||mnt<1)
    {

        MessageBox(0,"Invalid Class!\nEnter Class","Error!!",0);
        fflush(stdin);
        mon=clscanf();
    }
    else
        return mnt;
}

struct payment pay(int a)
{
    struct payment p;
    int ch;
    system("cls");

    printf("\nAmount to be paid : %d",a);
    time(&tim);
    p.time=tim;

    printf("\n\n\nPayment Mode");
    printf("\n\n\t1. Net Banking");
    printf("\n\t2. Card");
    printf("\n\t3. Demand Draft");
    printf("\n\t4. UPI");
    printf("\n\n\tEnter payment mode : ");
    scanf("%d",&ch);

    switch(ch)
    {
    case 1:
        strcpy(p.mode,"Net Banking");
        break;
    case 2:
        strcpy(p.mode,"Card");
        break;
    case 3:
        strcpy(p.mode,"Demand Draft");
        printf("\nEnter Draft Number : ");
        scanf("%s",&p.Tid);
        return p;
    case 4:
        strcpy(p.mode,"UPI");
        break;
    default:
        printf("\n\nInvalid Input!! Enter correct option");
        getch();
        pay(a);
    }
    printf("\nEnter Transaction Number : ");
    scanf("%s",&p.Tid);
    return p;
}

void recipt(struct student s,int a)
{
    system("cls");
    center("---    RECIPT    ---");
    printf("\n");

    printf("\nName : %s",s.n);
    printf("\nClass : %d",s.c);
    printf("\nRoll No : %d",s.r);
    printf("\nYearly Fee : %d",s.fee);
    printf("\nPaid : %d",a);
    printf("\nOutstanding : %d",s.due);
    if(strcmpi("Nil",s.p.Tid)==0)
        printf("\nLast fee paid on : No Payment Yet\n");
    else
        printf("\nLast fee paid on : %s",ctime(&s.p.time));
    printf("Mode of payment : %s",s.p.mode);
    printf("\nTransaction ID : %s\n\n",s.p.Tid);

    getch();
}

void disp(struct teacher t)
{
    printf("\nName = %s",tech.n);
    printf("\nTeacher/Staff Id = %d",tech.id);
    printf("\nYearly Salary = %d",tech.sal);

    printf("\nPaid : %d",tech.paid);
    printf("\nOutstanding : %d",tech.due);
    if(strcmpi("Nil",tech.p.Tid)==0)
        printf("\nFee Submission Date : No Payment Yet\n");
    else
        printf("\nFee Submission Date : %s",ctime(&tech.p.time));
    printf("Mode of payment : %s",tech.p.mode);
    printf("\nTransaction ID : %s\n\n",tech.p.Tid);
}

void recipt_t(struct teacher t,int a)
{
    system("cls");
    center("---    RECIPT    ---");
    printf("\n");
    printf("\nName = %s",t.n);
    printf("\nTeacher/Staff Id = %d",t.id);
    printf("\nYearly Salary = %d",t.sal);

    printf("\nPaid : %d",a);
    printf("\nOutstanding : %d",t.due);
    if(strcmpi("Nil",t.p.Tid)==0)
        printf("\nPayment Date : No Payment Yet\n");
    else
        printf("\nPayment Date : %s",ctime(&t.p.time));
    printf("Mode of payment : %s",t.p.mode);
    printf("\nTransaction ID : %s\n\n",t.p.Tid);
    getch();
}

void intro()
{
    int i;
    system("cls");
    system("color E9");
    for(i=0; i<w; i++)
    {
        printf("\xdb");
    }
    printf("\n");
    center("Developers : Group 1");
    printf("\n");
    for(i=0; i<w; i++)
    {
        printf("\xdb");
    }
    printf("\n\n\n\tMembers:");
    printf("\n\n\tShivam Jha\n\t1900290120108\n\tComputer Science");
    printf("\n\n\tRitu Yadav\n\t1900290120092\n\tComputer Science");
    printf("\n\n\tRupal Garg\n\t1900290120093\n\tComputer Science");
    printf("\n\n\n\tPlease Enter any key to continue");
    for(i=0;i<5;i++)
    {
        printf(".");
        Sleep(500);
    }
    getch();
    system("color 0F");
    system("cls");
}
