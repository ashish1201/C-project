#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include<conio.h>
#include<windows.h>
FILE *fp;
struct student
{
    char name[30],address[30],f_name[30],m_name[30],id[9];
    long int phn_n;
    int class_no;
}stu;

COORD coord = {0,0}; ///set the cordinate to 0, 0 (top-left corner of window);
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; /// X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawRectangle(){
    int i, j;
    gotoxy(0,0);
    printf("%c",201);
    for(i = 1; i < 78; i++){
        gotoxy(i, 0);
        printf("%c",205);
    }
    gotoxy(78,0);
    printf("%c",187);
    for(i = 1; i < 24; i++){
        gotoxy(78, i);
        printf("%c",186);
    }
    gotoxy(78, 24);
    printf("%c",188);
    for(i = 77; i > 0; i--){
        gotoxy(i,24);
        printf("%c",205);
    }
    gotoxy(0,24);
    printf("%c",200);
    for(i = 23; i > 0; i--){
        gotoxy(0,i);
        printf("%c",186);
    }


}

void add_data()
{
    system("cls");
    drawRectangle();

    gotoxy(2,2);printf(".......ADD RECORD.......");
    getchar();
    fp= fopen("record.txt","ab+");
    if(fp==NULL)
    {
        printf("unable to open file....");
        exit(1);
    }
    else
    {
       gotoxy(2,4); printf("NAME:\t"); gets(stu.name);
        gotoxy(2,5); printf("FATHERS NAME:\t"); gets(stu.f_name);
         gotoxy(2,6);printf("MOTHERS NAME:\t"); gets(stu.m_name);
         gotoxy(2,7);printf("ADDRESS:\t"); gets(stu.address);
         gotoxy(2,8);printf("ID:\t"); gets(stu.id);
        gotoxy(2,9); printf("PHONE NUMBER:\t"); scanf("%ld",&stu.phn_n);
         gotoxy(2,10);printf("CLASS:\t"); scanf("%d",&stu.class_no);
        fwrite(&stu, sizeof(stu), 1, fp);
         gotoxy(2,11);printf("Data has successfully been added.....");
         gotoxy(2,12);printf("Press enter key to continue to main menu..");
        getchar();
        getchar();
        fclose(fp);
        return;
    }
}
void search_data()
{

    system ("cls");
    drawRectangle();
    gotoxy(2,2);printf(".......SEARCH RECORD.......");
    getchar();
    char s_id[15];
    int isFound = 0;
    gotoxy(2,4);printf("Enter ID to Search:\t");
    gets(s_id);
    fp = fopen("record.txt","rb");
    if(fp==NULL)
    {
        printf("unable to open file....");
        exit(1);
    }
    while(fread(&stu,sizeof(stu),1,fp)==1)
        {
            if(strcmp(s_id,stu.id) == 0)
            {
                isFound = 1;
                break;
            }
        }
    if(isFound == 1)
    {
        gotoxy(2,6);printf("The record is Found");
        gotoxy(2,7);printf("ID:\t%s",stu.id);
        gotoxy(2,8);printf("NAME:\t%s",stu.name);
        gotoxy(2,9);printf("FATHERS NAME:\t%s",stu.f_name);
        gotoxy(2,10);printf("MOTHERS NAME:\t%s",stu.m_name);
        gotoxy(2,11);printf("ADDRESS:\t%s",stu.address);
        gotoxy(2,12);printf("PHONE NUMBER:\t%ld",stu.phn_n);
        gotoxy(2,13);printf("CLASS:\t%d",stu.class_no);
        gotoxy(2,15);printf("Press any key to continue to main menu..");
        getchar();
        fclose(fp);
        return;
    }
    else
    {
       gotoxy(2,4); printf("Sory, No record found in the database");
        gotoxy(2,6);printf("Press any key to continue to main menu..");
        getchar();
    }
    fclose(fp);
    return;
}
void modify_data()
{
    system ("cls");
    drawRectangle();
    gotoxy(2,2);printf(".........MODIFY RECORD.........");
    getchar();
    char s_id[15];
    int isFound = 0;
   gotoxy(2,4); printf("Enter ID to Modify:\t ");
    gets(s_id);
    fp = fopen("record.txt","rb+");
    if(fp==NULL)
    {
        printf("unable to open file....");
        exit(1);
    }
    while(fread(&stu,sizeof(stu),1,fp)==1)
    {
        if(strcmp(s_id, stu.id) == 0)
        {
            gotoxy(2,6);printf("NAME:\t"); gets(stu.name);
            gotoxy(2,7);printf("FATHERS NAME:\t"); gets(stu.f_name);
            gotoxy(2,8);printf("MOTHERS NAME:\t"); gets(stu.m_name);
            gotoxy(2,9);printf("ADDRESS:\t"); gets(stu.address);
            gotoxy(2,10);printf("ID:\t"); gets(stu.id);
            gotoxy(2,11);printf("PHONE NUMBER:\t"); scanf("%ld",&stu.phn_n);
            gotoxy(2,12);printf("CLASS:\t"); scanf("%d",&stu.class_no);
           fseek(fp,-sizeof(stu), SEEK_CUR);
            fwrite(&stu,sizeof(stu), 1, fp);
            getchar();
            gotoxy(2,14);printf("Press enter to continue to main menu..");
            getchar();
            isFound = 1;
            break;
        }
    }
    if(!isFound)
    {
       gotoxy(2,6); printf("No Record Found");
       gotoxy(2,8);printf("Press enter to continue to main menu..");
       getchar();
    }
    fclose(fp);
    return;
}
void delete_data()
{
    system("cls");
    drawRectangle();
    gotoxy(2,2);printf("........Delete Record.........");
    getchar();
    char s_id[15];
    gotoxy(2,4);printf("Enter ID to DELETE:\t");
    gets(s_id);
    FILE *temp;
    fp = fopen("record.txt","rb");
    temp = fopen("temp.txt", "wb");
    if(fp==NULL||temp==NULL)
    {
        printf("unable to open file....");
        exit(1);
    }
    else
    {
     while(fread(&stu, sizeof(stu),1,fp)==1)
    {
        if(strcmp(s_id, stu.id) == 0)
        {
            continue;
        }
        else
            fwrite(&stu,sizeof(stu),1,temp);
    }

    fclose(fp);
    fclose(temp);
    remove("record.txt");
    rename("temp.txt","record.txt");
   gotoxy(2,6); printf("The record is sucessfully deleted");
    gotoxy(2,8);printf("Press any key to continue to main menu..");
    getchar();
    }
    return;
}



void main_window()
{
    gotoxy(2,2); printf("......MAIN MENU......");
    gotoxy(2,4); printf("1. Add Student");
    gotoxy(2,5); printf("2. Search Student");
    gotoxy(2,6);  printf("3. Modify Student Record");
    gotoxy(2,7); printf("4. Delete Student Record");
    gotoxy(2,8); printf("5. Change password");
    gotoxy(2,9);printf("6. Exit");
    return;
}
void change_password()
{   system("cls");
    drawRectangle();

    char new_pass[8];
   gotoxy(2,2); printf("......CHANGE PASSWORD......");
    getchar();
     gotoxy(2,4);printf("Enter the new password(max 8 characters):\t");
    gets(new_pass);
    fp=fopen("password.txt","wb");
    fwrite(&new_pass,sizeof(new_pass),1,fp);
    fclose(fp);
     gotoxy(2,6);printf("The password has been successfully changed.");
     gotoxy(2,8);printf("Press enter to continue to main menu..");
    getchar();
    return;

}

int main()
{
	drawRectangle();
	gotoxy(2,2);
    int choice, check;
    char pass[9],password[9]="Wrong_value";
    fp=fopen("password.txt","rb");
    fgets(password,sizeof(password),fp);
    fclose(fp);
    printf("Enter the password:\t");
    scanf("%s",&pass);
    if (strcmp(pass,password)==0)
    {
    gotoxy(2,3) ;printf(".....Correct password.....\n");
    gotoxy(2,5);printf("Welcome to the program..press enter to contiue..");
    getchar();
    getchar();
    system("cls");
    program_loop:
    main_window();
    drawRectangle();
    gotoxy(2,11);printf("Enter your choice: ");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        add_data();
        system("cls");
        break;
    case 2:
        search_data();
        system("cls");
        break;
    case 3:
        modify_data();
        system("cls");
        break;
    case 4:
        delete_data();
        system("cls");
        break;
    case 5:
        change_password();
        system("cls");
        break;
    case 6:
    	system("cls");
    	drawRectangle();

       gotoxy(35,8);	printf("PROGRAMMED BY:");
    	gotoxy(35,10);printf("ANUJ CHALISE(076bce3022)");
       gotoxy(35,11);	printf("ASHISH SHARMA(076bce030)");
        gotoxy(35,12);printf("ASHISH UPADHAYA(076bce031)");
         gotoxy(35,13);printf("AMRIT BHETUWAL(076bce017)");
       gotoxy(2,19);
       exit (0);

        break;
    default:

        break;
    }

    goto program_loop;
    }
    else
    {
        getchar();
        gotoxy(2,3); printf(".........Invalid Password.........");
         gotoxy(2,5);printf("The database is password protected.");
         gotoxy(2,7);printf("Press enter to terminate the program.");
        getchar();
         gotoxy(3,9);
        exit(1);
    }
    return 0;
    system("pause");

}
