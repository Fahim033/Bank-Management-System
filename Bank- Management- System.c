 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h> 


void menu();
void choice();
void createAcc();
void exitHome();
void cust_list();
void editAcc();
void delAcc();
void acc_detail();
void deposit();
void withdraw();
void transactionHistory();
void dep_his();
void with_his();
int check();
void gotoxy(int a, int b);

struct bank
{
    char name[20];
    char phone[20];
    char email[100];
    char address[100];
    long long acc_no;
    char nid[20];
    long long pin;
    long long user;
    double balance;

} p;


struct transaction
{
    char type[10];
    long long srcacc;
    double amount;
    char date[100];
    char accname[20];

} t;



int main()
{

    char usern[100];
    char pass[100];

    printf("Welcome To BANK AL-NASSR\n\n");

    printf("MANAGER LOGIN :-\n");

    printf("Enter Username : ");
    scanf(" %[^\n]", usern);

    printf("Enter Password : ");
    scanf(" %[^\n]", pass);

    if ((strcmp(usern, "admin") == 0 && strcmp(pass, "cse") == 0))
    {

        printf("\nYou Have Successfully Logged In As A Manager\n");

        printf("Press [Enter] To Continue -> \n");
        int key = getch();
        if (key == 13)
        {
            menu();
        }
        else
            main();
    }
    else
    {

        printf("\nIncorrect Login Credentials!\n");

        printf("[1] . Try Again\n");

        printf("[2] . Exit\n");

        printf("Please Enter Your Choice [1-2] : ");
        int key;
        scanf("%d", &key);
        if (key == 1)
        {
            main();
        }

        else if (key == 2)
        {
            exit(1);
        }
    }

    return 0;
}

void menu()
{


    printf("\nWELCOME TO MAIN MENU :\n");

    printf("[1] . Account Registration\n");

    printf("[2] . View Customers' List\n");

    printf("[3] . Deposit Money\n");

    printf("[4] . Withdraw Money\n");

    printf("[5] . Edit Account Info\n");

    printf("[6] . Account Details\n");

    printf("[7] . Transaction History\n");

    printf("[8] . Delete Account\n");

    printf("[9] . Exit\n");
    printf("Please Enter Your Choice [1-10] : ");
    choice();
}

void choice()
{
    int key;
    scanf("%d", &key);
    switch (key)
    {
    case 1:
        createAcc();
        break;
    case 2:
        cust_list();
        break;
    case 3:
        deposit();
        break;
    case 4:
        withdraw();
        break;
    case 5:
        editAcc();
    case 6:
        acc_detail();
        break;
    case 7:
        transactionHistory();
        break;
    case 8:
        delAcc();
        break;
    case 9:
        exitHome();
        break;
    default:
        menu();
    }
}

void cust_list()
{   
    system("cls");
    FILE *fp;
    fp = fopen("account.txt", "rb");
    gotoxy(52, 2);
    printf("\n\nCUSTOMERS LIST\n");

    gotoxy(2, 5);
    printf("|====================|========================|=========================|======================|====================|\n");
    gotoxy(2, 5);
    printf("|    Account No.     |          Name          |          Email          |         Phone        |        Balance     |\n");
    gotoxy(2, 6);
    printf("|====================|========================|=========================|======================|====================|\n");
    int y = 7;
    while (fread(&p, sizeof(p), 1, fp))
    {
        gotoxy(2, y);
        printf("|");
        gotoxy(23, y);
        printf("|");
        gotoxy(48, y);
        printf("|");
        gotoxy(74, y);
        printf("|");
        gotoxy(97, y);
        printf("|");
        gotoxy(118, y);
        printf("|");

        gotoxy(7, y);
        printf("%d", p.acc_no);
        gotoxy(25, y);
        printf("%s", p.name);
        gotoxy(51, y);
        printf("%s", p.email);
        gotoxy(77, y);
        printf("%s", p.phone);
        gotoxy(100, y);
        printf("%.2lf Tk", p.balance);
        gotoxy(2, y+1);
        printf("|--------------------|------------------------|-------------------------|----------------------|--------------------|\n");
        y+=2;
    }
    fclose(fp);

    gotoxy(40, y + 6);
    printf("Press [Enter] To Return Home. ");
    int key = getch();
    if (key == 13)
    {
        menu();
    }
    else
        cust_list();
}

void createAcc()
{
    FILE *fp;
    fp = fopen("account.txt", "ab+");
    printf("\nACCOUNT REGISTRATION :-\n\n");
    printf("[1] Enter Your Name           : ");
    scanf(" %[^\n]", p.name);
    printf("[2] Enter Your Account Number : ");
    scanf(" %lld", &p.acc_no);
    printf("[3] Enter Your Phone Number   : ");
    scanf(" %[^\n]", p.phone);
    printf("[4] Enter Your Address        : ");
    scanf(" %[^\n]", p.address);
    printf("[5] Enter Your E-mail         : ");
    scanf(" %[^\n]", p.email);
    printf("[6] Enter Your NID No.        : ");
    scanf(" %[^\n]", p.nid);
    printf("[7] Set A Pin                 : ");
    scanf(" %lld", &p.pin);

    p.balance=0.0;

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
    printf("\nACCOUNT HAS BEEN CREATED SUCCESSFULLY\n");
    printf("Press [ENTER] To Return Home");

    int key = getch();
    if (key == 13)
    {
        menu();
    }
}

void editAcc()
{
    FILE *fp, *temp;
    long long acc;
    printf("\nEDIT ACCOUNT:-\n");
    printf("Enter Account Number To Edit : \n");
    scanf("%lld", &acc);
    if (check(acc) == 1)
    {
        fp = fopen("account.txt", "rb");
        temp = fopen("new.txt", "wb");
        while (fread(&p, sizeof(p), 1, fp))
        {
            if (p.acc_no != acc)
                fwrite(&p, sizeof(p), 1, temp);
            else if (p.acc_no == acc)
            {
                printf("ACCOUNT FOUND!\n");
                printf("Enter Account Information\n");
                printf("[1] . Enter Your Name           : \n");
                scanf(" %[^\n]", p.name);
                printf("[2] . Enter Your Account Number : \n");
                scanf(" %d", &p.acc_no);
                printf("[3] . Enter Your Phone Number   : \n");
                scanf(" %[^\n]", p.phone);
                printf("[4] . Enter Your Address        : \n");
                scanf(" %[^\n]", p.address);
                printf("[5] . Enter Your E-mail         : \n");
                scanf(" %[^\n]", p.email);
                printf("[6] . Enter Your NID No.        : \n");
                scanf(" %[^\n]", p.nid);
                fwrite(&p, sizeof(p), 1, temp);
            }
        }
        fclose(fp);
        fclose(temp);
        printf("\nACCOUNT HAS BEEN UPDATED");
    }
    else if (check(acc) == 0)
    {
        printf("ACCOUNT NOT FOUND!!!\n");
        printf("[1] . Try Again\n");
        printf("[2] . Return To Menu\n");
        printf("[3] . Exit\n");
        printf("Please Enter Your Choice [1-3] : \n");
        int key;
        scanf("%d", &key);
        if (key == 1)
        {
            editAcc();
        }
        else if (key == 2)
        {
            menu();
        }

        else if (key == 3)
        {
            exit(1);
        }
    }
    remove("account.txt");
    rename("new.txt", "account.txt");
    printf("Press [ENTER] To Return Home");

    int key = getch();
    if (key == 13)
    {
        menu();
    }
}

void delAcc()
{

    FILE *fp, *temp;
    long long acc;

    printf("\nDELETE ACCOUNT :-\n");
    printf("Enter Account Number To Delete : ");
    scanf("%lld", &acc);
    if (check(acc) == 1)
    {
        fp = fopen("account.txt", "rb");
        temp = fopen("new.txt", "wb");
        while (fread(&p, sizeof(p), 1, fp))
        {
            if (p.acc_no != acc)
                fwrite(&p, sizeof(p), 1, temp);
        }
        fclose(fp);
        fclose(temp);
        remove("account.txt");
        rename("new.txt", "account.txt");
    
        printf("ACCOUNT HAS BEEN DELETED !\n");
   
        printf("Press [ENTER] To Return Home");

        int key = getch();
        if (key == 13)
        {
            menu();
        }
    }
    else if (check(acc) == 0)
    {
        printf("\nACCOUNT NOT FOUND!!!\n");
        printf("[1] . Try Again\n");
        printf("[2] . Return To Menu\n");
        printf("[3] . Exit\n");
        printf("Please Enter Your Choice [1-2] : ");
        int key;
        scanf("%d", &key);
        if (key == 1)
        {
         
            delAcc();
        }
        else if (key == 2)
        {
    
            menu();
        }

        else if (key == 3)
        {
            exit(1);
        }
    }
}

void acc_detail()
{
  
    FILE *fp;
    long long acc;
    printf("\nSEARCH ACCOUNT DETAILS :-\n");
    printf("\nEnter Account Number To Search : ");
    scanf("%lld", &acc);
    if (check(acc) == 1)
    {
        fp = fopen("account.txt", "rb");
        while (fread(&p, sizeof(p), 1, fp))

        {
            if (p.acc_no == acc)
            {
                printf("\nACCOUNT DETAILS\n\n");
                printf("[1] . Account Number : %d\n", p.acc_no);
                printf("[2] . Name           : %s\n", p.name);
                printf("[3] . Phone Number   : %s\n", p.phone);
                printf("[4] . Address        : %s\n", p.address);
                printf("[5] . E-mail         : %s\n", p.email);
                printf("[6] . National ID No.: %s\n", p.nid);
                printf("[7] . Current Balance: %.2lf Tk\n", p.balance);
            }
        }
        fclose(fp);
    }
    if (check(acc) == 0)
    {
        printf("\nNO ACCOUNT FOUND!!!\n");
        printf("[1] . Try Again\n");
        printf("[2] . Return To Menu\n");
        printf("[3] . Exit\n");
        printf("Please Enter Your Choice [1-3] : \n");
        int key;
        scanf("%d", &key);
        if (key == 1)
        {
            acc_detail();
        }
        else if (key == 2)
        {
            menu();
        }

        else if (key == 3)
        {
            exit(1);
        }
    }
    printf("Press [ENTER] To Return Home");

    int key = getch();
    if (key == 13)
    {
        menu();
    }
    else
        acc_detail();
}

void deposit()
{
    long long acc;
    double newBalance;

    printf("\nDEPOSIT AMMOUNT\n\n");
    printf("Enter Account Number To Deposit : \n");
    scanf("%lld", &acc);
    FILE *fp, *temp, *tp;

    if (check(acc) == 1)
    {
        fp = fopen("account.txt", "rb");
        temp = fopen("temp.txt", "wb");
        tp=fopen("record.txt", "ab+");
        while (fread(&p, sizeof(p), 1, fp))
        {
            if (p.acc_no != acc)
                fwrite(&p, sizeof(p), 1, temp);
            else if (p.acc_no == acc)
            {
                p.name;
                p.acc_no;
                p.phone;
                p.address;
                p.email;
                p.nid;
                p.pin;
                printf("Enter The Amount To Deposit : \n");
                scanf("%lf", &newBalance);
                p.balance += newBalance;
                t.srcacc = acc;
                t.amount = newBalance;
                strcpy(t.accname, p.name);
                strcpy(t.type, "deposit");
                time_t currentTime;
                time(&currentTime);
                strcpy(t.date, ctime(&currentTime));


                fwrite(&p, sizeof(p), 1, temp);
                fwrite(&t, sizeof(t), 1, tp);
            }
        }
        fclose(fp);
        fclose(temp);
        fclose(tp);
        remove("account.txt");
        rename("temp.txt", "account.txt");
    }

    if (check(acc) == 0)
    {
       printf("\nNO ACCOUNT FOUND!!!\n");
        printf("[1] . Try Again\n");
        printf("[2] . Return To Menu\n");
        printf("[3] . Exit\n");
        printf("Please Enter Your Choice [1-3] : \n");
        int key;
        scanf("%d", &key);
        if (key == 1)
        {
            deposit();
        }
        else if (key == 2)
        {
            menu();
        }

        else if (key == 3)
        {
            exit(1);
        }
    }

    printf("\nSUCESSFULLY DEPOSITED \n\n");
    printf("Press [ENTER] To Return Home");

    int key = getch();
    if (key == 13)
    {
        menu();
    }
    else
        deposit();
}

void withdraw()
{
    long long acc;
    printf("\nWITHDRAW AMOUNT :- \n\n");
    printf("Enter Account Number To Withdraw : \n");
    scanf("%lld", &acc);
    double money, temporary;
    FILE *fp, *temp, *tp;

    if (check(acc) == 1)
    {
        fp = fopen("account.txt", "rb");
        temp = fopen("temp.txt", "wb");
        tp=fopen("record.txt", "ab+");

        while (fread(&p, sizeof(p), 1, fp))
        {
            if (p.acc_no != acc)
                fwrite(&p, sizeof(p), 1, temp);
            else if (p.acc_no == acc)
            {
                p.name;
                p.acc_no;
                p.phone;
                p.address;
                p.email;
                p.nid;
                p.pin;
                temporary = p.balance;
                printf("Enter The Amount To Withdraw : \n");
                scanf("%lf", &money);
                if (money <= p.balance)
                {
                    p.balance = p.balance - money;
                    t.srcacc = acc;
                    t.amount = money;
                    strcpy(t.type, "withdraw");
                    strcpy(t.accname, p.name);
                    time_t currentTime;
                    time(&currentTime);
                    strcpy(t.date, ctime(&currentTime));
                    printf("\nSUCCESSFULLY WITHDRAWN");
                }
                fwrite(&p, sizeof(p), 1, temp);
                fwrite(&t, sizeof(t), 1, tp);

            }
        }
        fclose(fp);
        fclose(temp);
        fclose(tp);
        remove("account.txt");
        rename("temp.txt", "account.txt");
        if (temporary < money)
        {
            printf("\nINSUFFICIENT BALANCE!\n");
            printf("Current Balance is %.2lf Taka\n", temporary);
            printf("[1] . Try Again\n");
            printf("[2] . Return To Menu\n");
            printf("[3] . Exit\n");
            printf("Please Enter Your Choice [1-3] : \n");
            int key;
            scanf("%d", &key);
            if (key == 1)
            {
                withdraw();
            }
            else if (key == 2)
            {
                menu();
            }

            else if (key == 3)
            {
                exit(1);
            }
        }
    }
    if (check(acc) == 0)
    {

        printf("NO ACCOUNT FOUND!!!\n");
        printf("[1] . Try Again\n");
        printf("[2] . Return To Menu\n");
        printf("[3] . Exit\n");
        printf("Please Enter Your Choice [1-3] : \n");
        int key;
        scanf("%d", &key);
        if (key == 1)
        {
            withdraw();
        }
        else if (key == 2)
        {

            menu();
        }

        else if (key == 3)
        {
            exit(1);
        }
    }

    printf("\nPress [ENTER] To Return Home");

    int key = getch();
    if (key == 13)
    {
        menu();
    }
    else
        withdraw();
}


void transactionHistory()
{
    int choice;
    printf("[1] . Deposit History\n");
    printf("[2] . Withdraw History\n");
    printf("[3] . Return To Main Menu\n");
    printf("Enter your choice [1-3]: \n");
    scanf("%d", &choice);


    switch (choice)
    {
    case 1:
        dep_his();
        break;
    case 2:
        with_his();
        break;
    case 3:
        menu();
        break;
    default:
        menu();
    }

}




void dep_his()
{
    FILE *tp;
        tp=fopen("record.txt", "rb");
    if (tp == NULL)
    {
        printf("Error!!! Press [ENTER] to return to the main menu.");
        fclose(tp);
        int key = getch();
        if (key == 13)
        {
            menu();
        }
        return;
    }
    int op;
    printf("\n[1] . Full Deposit History\n");
    printf("[2] . Search By Account Number\n");
    printf("[3] . Return to Main Menu\n");
    printf("Enter your choice [1-3]: \n");
    scanf("%d", &op);

    if(op==1)
    {
        printf("\nDEOPOSIT HISTORY \n\n");

        int i=1;

        while (fread(&t, sizeof(t), 1, tp))
        {
            if(strcmp(t.type,"deposit") == 0)
            {
                printf("[%d]. Account Number: %d\n", i, t.srcacc);

                printf("Account holder's name: %s\n", t.accname);

                printf("Transaction Date: %s\n", t.date);

                printf("Deposited Amount: %.2lf\n", t.amount);
                i++;
            }
        }

    }


    else  if(op==2)
    {
        int m;
        printf("Enter account number:\n");
        scanf("%lld", &m);
        if(check(m)==1)
        {
            printf("\nDEPOSIT HISTORY\n\n");

            int i=1;
            while (fread(&t, sizeof(t), 1, tp))
            {
                if(m==t.srcacc && strcmp(t.type,"deposit") == 0)
                {
                        printf("[%d]. Account Number: %d\n", i, t.srcacc);
                        printf("Account holder's name: %s\n", t.accname);
                        printf("Deposited Amount: %.2lf\n", t.amount);
                        printf("Transaction Date: %s\n", t.date);

                        printf("\n");
                        i++;
                }


            }
        }
        else if(check(m)==0)
        {
            fclose(tp);
            printf("NO ACCOUNT FOUND!!!\n");
            printf("[1] . Try Again\n");
            printf("[2] . Return To Menu\n");
            printf("[3] . Exit\n");
            printf("Please Enter Your Choice [1-3] : \n");
            int key;
            scanf("%d", &key);
            if (key == 1)
            {

                dep_his;
            }
            else if (key == 2)
            {
               
                menu();
            }

            else if (key == 3)
            {
                exit(1);
            }
        }

    }
    else if(op==3)
    {
        fclose(tp);
        menu();
    }
    fclose(tp);
    printf("Press [Enter] To Return Home.\n ");
    int key = getch();
    if (key == 13)
    {
        menu();
    }
    else
        transactionHistory();
}

void with_his()
{
    FILE *tp;

    if (tp == NULL)
    {
        printf("Error!!! Press [ENTER] to return to the main menu\n");
        fclose(tp);
        int key = getch();
        if (key == 13)
        {
            menu();
        }
        return;
    }
    int op;
    printf("[1] . Full Withdraw History\n");
    printf("[2] . Search By Account Number\n");
    printf("[3] . Return to Main Menu\n");
    printf("Enter your choice[1-3]: \n");
    scanf("%d", &op);

    if(op==1)
    {
        tp=fopen("record.txt", "rb");
        printf(" WITHDRAW HISTORY ");

        int i=1;

        while (fread(&t, sizeof(t), 1, tp))
        {
            if(strcmp(t.type,"withdraw") == 0)
            {

                printf("[%d] . Account Number: %d\n", i, t.srcacc);

                printf("Account holder's name: %s\n", t.accname);

                printf("Transaction Date: %s\n", t.date);

                printf("Withdrawn Amount: %.2lf\n", t.amount);

                printf("\n");
                i++;
            }
        }

        fclose(tp);
    }


    else  if(op==2)
    {
        tp=fopen("record.txt", "rb");
        int m;
        printf("\nEnter Account Number:");
        scanf("%lld", &m);
        if(check(m)==1)
        {

            printf(" WITHDRAW HISTORY ");

            int i=1;
            while (fread(&t, sizeof(t), 1, tp))
            {
                if(m==t.srcacc)
                {
                    if(strcmp(t.type,"withdraw") == 0)
                    {

                        printf("[%d] . Account Number: %d\n", i, t.srcacc);
                        printf("Account holder's name: %s\n", t.accname);
                        printf("Withdrawn Amount: %.2lf\n", t.amount);
                        printf("Transaction Date: %s\n", t.date);
                        printf("\n");
                        i++;
                    }
                }


            }
            fclose(tp);
            printf("Press [Enter] To Return Home.\n ");
            int key = getch();
            if (key == 13)
            {
                menu();
            }
            else
                transactionHistory();
        }
        else if(check(m)==0)
        {
            printf("NO ACCOUNT FOUND!!!\n");
            printf("[1] . Try Again\n");
            printf("[2] . Return To Menu\n");
            printf("[3] . Exit\n");
            printf("Please Enter Your Choice [1-3] : \n");
            int key;
            scanf("%d", &key);
            if (key == 1)
            {
         
                with_his;
            }
            else if (key == 2)
            {

                menu();
            }

            else if (key == 3)
            {
                exit(1);
            }
        }

    }
    else if(op==3)
    {
        menu();
    }
    printf("Press [Enter] To Return Home.\n ");
    int key = getch();
    if (key == 13)
    {
        menu();
    }
    else
        transactionHistory();
}

int check(int acc)
{
    FILE *fp;
    fp = fopen("account.txt", "rb");

    while (!feof(fp))
    {
        fread(&p, sizeof(p), 1, fp);

        if (acc == p.acc_no)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void gotoxy(int a, int b)
{
    COORD coord = {0, 0};

    coord.X = a;
    coord.Y = b;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void exitHome()
{   
    printf("!!! THANK YOU FOR USING MY SOFTWARE !!!\n");
    printf("SEE YOU SOON\n");
  
    exit(0);
}
