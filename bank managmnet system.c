#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
struct account
{
	int num;
	int pin;
	int balance;
	char name[100];
};

struct profile
{
	int id;
	int password;
};

struct account a;
struct profile admin;
int addon, deduct, remain;
int deposit(struct account);
int withdraw(struct account);
void details(struct account,int);
void customer();
void manager();
void list();
void search();
void add();
void modify();
int reclen=sizeof(a);
int bal;

int main()
{
	int choice; 
	printf("                                                  Welcome to Bank Management System \n");
	printf("\n--------------------------------------------------------------------------------------------------------------------------------");
	printf("\nLOGIN AS \n1. MANAGER \n2. CUSTOMER \n3. EXIT");
	printf("\nEnter your choice= ");
	scanf("%d",&choice);
	switch(choice){
		case 1:
			manager();
			break;
			
		case 2:
			customer();
			break;
			
		case 3:
			printf("\n*****Thank You For Using Our System*****");
			printf("\n----------------------------------------------------------------------------------------------------------------------------------");
			exit(1);

		default:
			printf("\nEnter the correct choice!!!");
	}
	
	return 0;
}

// Manager Service Main
void manager()
{
	FILE *fm;
	int id,flag=0;
	int pass,ch;
	fm = fopen("Manager.dat","rb+");
	if(fm==NULL)
	{
		fm = fopen("Manager.dat","wb+");
		if(fm==NULL)
		{
			printf("\nFile cannot be opened");
			exit(0);
		}
	}
	printf("\nEnter the manager id= ");
	scanf("%d",&id);
	rewind(fm);
	while(!feof(fm))
	{
		fscanf(fm,"%d %d",&admin.id, &admin.password);
		if(id==admin.id)
		{
			printf("Enter the password= ");
			scanf("%d",&pass);
			if(pass==admin.password)
			{
				printf("\n.....Access Granted.....\n");
				flag=1;
				break;
			}
		}
		else
		{
			continue;
		}
	}

	if(flag==1)
	{
		printf("\n1.List all accounts \n2.Search a record \n3.Add account \n4.Modify existing account \n5.Exit");
		while(1)
		{
			printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
			printf("\n\nEnter your choice of operation= ");
			scanf("%d",&ch);
			switch(ch)
			{
				case 1:
					list();
					break;
					
				case 2:
					search();
					break;
					
				case 3:
					add();
					break;
					
				case 4:
					modify();
					break;
								
				case 5: 
					printf("\n*****Thank You For Using Our System*****");
					exit(1);
					
				default:
					printf("\nEnter the correct choice!!!");
			}
		}
	}
	else 
	{
		printf(".....Acesses denied......");

	}
}


// Customer Service Main
void customer()
{
	FILE *fp;
	int n,i;
	int ch,z,k,pointer=0;
	int flag = 0,counter=0;
	int balance;
	char temp_name[50];

	
	fp = fopen("BankAcc.dat", "rb+");
	if(fp==NULL)
	{
		fp = fopen("BankAcc.dat", "wb+");
		{
			if(fp==NULL)
			{
				printf("\nFile cannot be created/opened...");
				exit(0);
			}
		}
	}
	
	// check the A/c num then copy the data to struct a
	printf("\nEnter the Account number= ");
	scanf("%d",&n);
	rewind(fp);
	while(fread(&a,reclen,1,fp)==1) //The counter is running one extra time
	{
	//	fscanf(fp,"%s %d %d %d",a.name, &a.num, &a.pin, &a.balance);
		if(a.num == n)
		{
			printf("Enter pin= ");
			scanf("%d",&k);
			if(a.pin==k)
			{
				flag = 1;
				printf("A/c Details Matched");
				break;
			}
		}
		else {
			continue;
		}
	}
	
	if(flag == 1)
	{
		strcpy(temp_name,a.name); // temp_name is used to store the name temporarily for future use.
		printf("\n\n1.Check info\n2.Deposit\n3.Withdraw\n4.Exit\n");	
		while(1)
		{
			printf("\n---------------------------------------------------------------------------------------------------------------------------------\n");
			printf("\nEnter your choice of operation= ");
			scanf("%d",&ch);
			switch(ch)
			{
				case 1:
					z = a.balance;
					pointer=1;
					details(a,pointer);
					break;
					
				case 2:
					a.balance = deposit(a);
					pointer=2;
					//a.balance = z;
					details(a,pointer);
					balance = a.balance;
					break;
					
				case 3:
					a.balance = withdraw(a);
					pointer=3;
					//a.balance = z;
					details(a,pointer);	
					balance = a.balance;
					break;
				
				case 4:
					rewind(fp);  //rewind makes the pointer point towards starting
					struct account b;
					while(fread(&a,reclen,1,fp)==1)
					{
						if(strcmp(a.name,temp_name)==0)
						{
							strcpy(b.name,a.name);
							b.num=a.num;
							b.balance=balance;
							b.pin=a.pin;
							fseek(fp,-reclen,SEEK_CUR); //fseek(fp,0,SEEK_END);
							fwrite(&b,reclen,1,fp);
							break;
						}
					}  				            
					fclose(fp);
					printf("\n*****Thank You For Using Our System*****");
					exit(1);
						
				default:
					printf("\nEnter correct choice!!!");
			}
		}
	}
	else 
	{
		printf("......User Credential not matched........");
	}
}


// Functions
void list()
{
	FILE *fp;
	fp = fopen("BankAcc.dat", "rb+");
	if(fp==NULL)
	{
		fp = fopen("BankAcc.dat", "wb+");
		if(fp==NULL)
		{
			printf("\nFile cannot be created/opened...");
			exit(0);
		}
	}
	rewind(fp);
	printf("\nAccount name       Account number       Account pin        Account balance\n");
	while(fread(&a,reclen,1,fp)==1)
	{
		printf("\n%-20s %-20d %-20d %-20d",a.name,a.num,a.pin,a.balance);
	}
}

void search()
{
	char sch[20];
	int num, found=0;
	FILE *fp;
    fp = fopen("BankAcc.dat", "rb+");
	if(fp==NULL)
	{
		fp = fopen("BankAcc.dat", "wb+");
		if(fp==NULL)
		{
			printf("\nFile cannot be created/opened...");
			exit(0);
		}
	}
	printf("\nEnter the Account Name or Account No. ");
	fflush(stdin);
	gets  (sch);
	num = atoi(sch);
	
	if (num != 0)
	{
		printf("\nAccount name       Account number       Account pin        Account balance\n");
		while(fread(&a,reclen,1,fp)==1)
		{
			if(a.num == num)
			{
				found = 1;
				printf("\n%-20s %-20d %-20d %-20d",a.name,a.num,a.pin,a.balance);
			}
		}	
	} 
	else
	{
		printf("\nAccount name       Account number       Account pin        Account balance\n");
		while(fread(&a,reclen,1,fp)==1)
		{
			if(strcmp(a.name,sch)==0)
			{
				found = 1;
				printf("\n%-20s %-20d %-20d %-20d",a.name,a.num,a.pin,a.balance);
			}
		}
	}
	if(found == 0)
	{
		printf("\nNo record found with the data: %s", sch);
	}
	fclose(fp);
}

void add()
{
	FILE *fp;
	char another;
	fp = fopen("BankAcc.dat", "rb+");
	if(fp==NULL)
	{
		fp = fopen("BankAcc.dat", "wb+");
		if(fp==NULL)
		{
			printf("\nFile cannot be created/opened...");
			exit(0);
		}
	}
	printf("\nThe list of accounts that are already present...\n");
	printf("Please don't repeat the same account number or you will face error!!!\n");
	printf("\nAccount name       Account number       Account pin        Account balance\n");
	rewind(fp);
	while(fread(&a,reclen,1,fp)==1)
	{
		printf("\n%-20s %-20d %-20d %-20d",a.name,a.num,a.pin,a.balance);
	}
	int recomNum = a.num + 1;
	printf("\n\nRecomended Account No.: %d\n", recomNum);
	fseek(fp,0,SEEK_END);
	another='y';
	while(another=='y')
	{
		printf("\nEnter Holder name , Account number , Account pin , Account opening balance: \n");
		scanf("\n%s %d %d %d",a.name,&a.num,&a.pin,&a.balance);
		fwrite(&a,reclen,1,fp);
		printf("\nWant to add more records? ");
		fflush(stdin);
		another=getchar();
	}
    fclose(fp);
}

void modify(){
    int mnum;
    FILE *fp;
    fp = fopen("BankAcc.dat", "rb+");
    int found = 0;
	if(fp==NULL)
	{
		fp = fopen("BankAcc.dat", "wb+");
		if(fp==NULL)
		{
			printf("\nFile cannot be created/opened...");
			exit(0);
		}
	}
	printf("\nEnter A/c num of the holder whose record needs to be changed....");
	scanf("%d", mnum);
	rewind(fp);  //rewind makes the pointer point towards starting
	struct account m;   // For modification			
	while(fread(&a,reclen,1,fp)==1)
	{
		if(mnum == a.num )
		{
			found = 1;
			printf("\nAccount name       Account number       Account pin        Account balance\n");
			printf("\n%-20s %-20d %-20d %-20d",a.name,a.num,a.pin,a.balance);
			printf("\n\nEnter Holder name   Account number   Account pin   Account opening balance: \n");
			scanf("\n%s %d %d %d",m.name,&m.num,&m.pin,&m.balance);
			fseek(fp,-reclen,SEEK_CUR); //fseek(fp,0,SEEK_END);
			fwrite(&m,reclen,1,fp);
			break;						
		}
	}
	if(found == 0)
	{
		printf("\nNo record found with data: %d You may check the list.", mnum);
	}
	fclose(fp);
}

int deposit(struct account a)
{
	bal= a.balance;
	printf("\nYour current balance = %d", bal);
	printf("\nEnter the amount you want to deposit= ");
	scanf("%d", &addon);
	remain=(bal+addon);
	return remain;
	
}

int withdraw(struct account a)
{
	bal = a.balance;
	printf("\nYour current balance = %d", bal);
	printf("\nEnter the amount you want to take out= ");
	scanf("%d",&deduct);
	if(deduct<=bal)
	{
		remain = (bal-deduct);
		printf("\nWithdrawl successful!!!");
		return remain;
	}
	else
	{
		printf("\nInsufficient balance!!!");
		return bal;
	}
}

void details(struct account a,int pointer)
{
	if(pointer==1){
		printf("\n\n....Account Details....");
		printf("\nName of the account holder = %s",a.name);
		printf("\nAccount number = %d",a.num);
		printf("\nBalance = %d",a.balance);
	}
	else if(pointer==2){
		printf("\n\n....The receipt....");
		printf("\nName of the account holder = %s",a.name);
		printf("\nAccount number = %d",a.num);
		printf("\nThe amount added = %d",addon);
		printf("\nBalance = %d",a.balance);
	}
	else if(pointer==3){
		printf("\n\n....The receipt....");
		printf("\nName of the account holder = %s",a.name);
		printf("\nAccount number = %d",a.num);
		printf("\nThe amount taken out = %d",deduct);
		printf("\nBalance = %d",a.balance);
	}	
}