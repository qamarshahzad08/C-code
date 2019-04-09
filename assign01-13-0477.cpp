#include<iostream>
#include<cstring>
#include"Assign01-13-0477.h"
using namespace std;
int main()
{ Account *a1[100];
	 Transaction *t1[100];
	Customer *x[100];
	int a=2,ac=1;
	int b=112;
	int m=471;
	int choice,count=10,count1=10,count2=10;
	//saving customers
	x[0]=(Customer*)malloc(1*sizeof(Customer));
	x[0]->Add_New_Customer(1000,"qamar shahzad","qamarshehzad08@gmail.com",5550465,"house no 250 street no 100 I-8/4 islamabad","37405-3211485-1");
	x[1]=(Customer*)malloc(1*sizeof(Customer));
	x[1]->Add_New_Customer(1001,"ali nawaz","alinawaz786@gmail.com",2268790,"house no b1-686 street no 30 Muslim town Rwp","37405-4099123-4");
	x[2]=(Customer*)malloc(1*sizeof(Customer));
	x[2]->Add_New_Customer(1002,"Raja Mohsin","Mohsin.raja@yahoo.com",3314567,"house no 1158/AA street no 30 Rawal town Rwp","38113-3091234-8");
	x[3]=(Customer*)malloc(1*sizeof(Customer));
	x[3]->Add_New_Customer(1003,"haider ali","haidi.987@hotmail.com",4537861,"house no 121 street no 11 i-9/1 islamabad","37115-3241367-9");
	x[4]=(Customer*)malloc(1*sizeof(Customer));
	x[4]->Add_New_Customer(1004,"umeir shafi","shafi.u00@rocket.com",6578432,"house no 098 street no 31 islamabad","36304-3100374-8");
	x[5]=(Customer*)malloc(1*sizeof(Customer));
	x[5]->Add_New_Customer(1005,"mohsin anees","mohsin12@gmail.com",5123578,"house no 111 street no 100 I-8/4 islamabad","33435-2211475-0");
	x[6]=(Customer*)malloc(1*sizeof(Customer));
	x[6]->Add_New_Customer(1006,"ali Mughal","alimughal@gmail.com",4310980,"house no A1-987 street no 60 Muslim town Rwp","32110-4091232-9");
	x[7]=(Customer*)malloc(1*sizeof(Customer));
	x[7]->Add_New_Customer(1007,"Raja Haris","haris.raja@yahoo.com",3211567,"house no 112 street no 30 Rawal town Rwp","48110-2001234-6");
	x[8]=(Customer*)malloc(1*sizeof(Customer));
	x[8]->Add_New_Customer(1008,"zaib ali","zaibi.ali@hotmail.com",3761434,"house no 10 street no 7 i-7/1 islamabad","31254-3221317-1");
	x[9]=(Customer*)malloc(1*sizeof(Customer));
	x[9]->Add_New_Customer(1009,"umer shafiq","shafiq.umer@rocket.com",4544232,"house no 09 street no 3 islamabad","33204-3100263-3");
	//saving accounts
	a1[0]=(Account*)malloc(sizeof(Account));
	a1[0]->addnewaccount(100,1000,"saving",1000,"20/9/2014");
	a1[1]=(Account*)malloc(sizeof(Account));
	a1[1]->addnewaccount(101,1001,"saving",1000,"20/9/2014");
	a1[2]=(Account*)malloc(sizeof(Account));
	a1[2]->addnewaccount(102,1002,"saving",1000,"20/9/2014");
	a1[3]=(Account*)malloc(sizeof(Account));
	a1[3]->addnewaccount(103,1003,"saving",1000,"20/9/2014");
	a1[4]=(Account*)malloc(sizeof(Account));
	a1[4]->addnewaccount(104,1004,"saving",1000,"20/9/2014");
	a1[5]=(Account*)malloc(sizeof(Account));
	a1[5]->addnewaccount(105,1005,"Current",1000,"20/9/2014");
	a1[6]=(Account*)malloc(sizeof(Account));
	a1[6]->addnewaccount(106,1006,"Current",1000,"20/9/2014");
	a1[7]=(Account*)malloc(sizeof(Account));
	a1[7]->addnewaccount(107,1007,"Current",1000,"20/9/2014");
	a1[8]=(Account*)malloc(sizeof(Account));
	a1[8]->addnewaccount(108,1008,"Current",1000,"20/9/2014");
	a1[9]=(Account*)malloc(sizeof(Account));
	a1[9]->addnewaccount(109,1009,"Current",1000,"20/9/2014");
	//saving Transactions
	t1[0]=(Transaction*)malloc(sizeof(Transaction));
	t1[0]->Make_New_Transaction(230,100,"withdraw",10);
	t1[1]=(Transaction*)malloc(sizeof(Transaction));
	t1[1]->Make_New_Transaction(231,101,"withdraw",10);
	t1[2]=(Transaction*)malloc(sizeof(Transaction));
	t1[2]->Make_New_Transaction(232,102,"withdraw",10);
	t1[3]=(Transaction*)malloc(sizeof(Transaction));
    t1[3]->Make_New_Transaction(233,103,"withdraw",10);
	t1[4]=(Transaction*)malloc(sizeof(Transaction));
	t1[4]->Make_New_Transaction(234,104,"withdraw",10);
	t1[5]=(Transaction*)malloc(sizeof(Transaction));
	t1[5]->Make_New_Transaction(235,105,"deposit",10);
	t1[6]=(Transaction*)malloc(sizeof(Transaction));
	t1[6]->Make_New_Transaction(236,106,"deposit",10);
	t1[7]=(Transaction*)malloc(sizeof(Transaction));
	t1[7]->Make_New_Transaction(237,107,"deposit",10);
	t1[8]=(Transaction*)malloc(sizeof(Transaction));
	t1[8]->Make_New_Transaction(238,108,"deposit",10);
	t1[9]=(Transaction*)malloc(sizeof(Transaction));
	t1[9]->Make_New_Transaction(239,109,"deposit",10);
   for(;;)
{
	
  cout<<"1. Add New Customer"<<endl;
  cout<<"2. Open An Account"<<endl;
  cout<<"3. Make a Transaction (The Cusomter_ID & Account_ID should already exist) "<<endl;
  cout<<"4. Display/Search/Modify/Delete Customer"<<endl;
  cout<<"5. Display/Search/Modify/Delete Account"<<endl;
  cout<<"6. Display/Search transactions"<<endl;
  cout<<"7. exit from program"<<endl;

  cin>>choice;
  int checkspace1=0,checkspace2=0,checkspace3=0;

  if(choice==1)
  { for(int i=0;i<count;i++)
  { checkspace1=0;
	  if((x[i]->checkspace())==1)
     {b++;
		 x[i]->Add_New_Customer(b);
	  checkspace1=1;
	  break;
     }
  }
  if(checkspace1==0)
  {
	  for(int i=count;i<count+1;i++)
	  {
		  x[i]=(Customer*)malloc(1*sizeof(Customer));
		 x[i]->Add_New_Customer(b);
	  }
	  count++;}
	  b++;
 } 
  if(choice==2)
  {  checkspace3=0;
	  cout<<"Enter Customer ID"<<endl;
   int l;
   cin>>l;
    for(int i=0;i<count;i++)
	{ if(x[i]->Customer_id_exist(l)==1)
	  {checkspace3=1;
		  break;
	  }
	}
	if(checkspace3==1)
	{
	  for(int i=0;i<count1;i++)
   {  checkspace2=0;
	  if(a1[i]->checkspace()==1)
     { a1[i]->addnewaccount((220+count1),l);
	  
      checkspace2=1;
      break;
     }
    }
  if(checkspace2==0)
  {
	  for(int i=count1;i<count1+1;i++)
	  { 
		  a1[i]=(Account*)malloc(1*sizeof(Account));
		 a1[i]->addnewaccount((200+count1),l);
	  }
	  count1++;
  }
	}
	else 
		cout<<"Customer ID does not exist"<<endl;
	  
  }
  if(choice==3)
  { 
	  cout<<"please enter Account id to confirm your account"<<endl;
  int r;
  double c=0;
  cin>>r;
     for(int i=0;i<count1;i++)
	 {
		c=a1[i]->check(r);
		if(c!=0)
		{ cout<<"found"<<endl;
			break;
		}
	 }
 if(c!=0)
 { if(cin.peek()=='\n') cin.ignore();
	   char Transactiontype[20];
	   double amount;
	   cout<<"Transiction type (withdraw or deposit please enter in small letters)"<<endl;
	   cin.getline(Transactiontype,20);
	   cout<<"Amount_Transcated"<<endl;
	   cin>>amount;
	   if(strcmp(Transactiontype,"withdraw")==0)
		{ 
			cout<<"Transacted Amount"<<endl;
	
		if((c-amount)<0)
		{
		 cout<<"not possible you have only "<<c<<endl;
		 
		}
		}
	   if(strcmp(Transactiontype,"deposit")==0|| c-amount>0)
	   {
		  t1[count2]=(Transaction*)malloc(1*sizeof(Transaction));
		 t1[count2]->Make_New_Transaction(r,(60+count2),amount,Transactiontype);
	  
	  count2++;
	   }
	   if(strcmp(Transactiontype,"deposit")==0|| c-amount>0|| c-amount==0)
	   {
	    for(int i=0;i<count1;i++)
	 {
		if(a1[i]->check(r)!=0)
		{ if(strcmp(Transactiontype,"deposit")==0)
		   { a1[i]->balanceupdate((c+amount));
		   }
		else 
			a1[i]->balanceupdate((c-amount));
			break;
		}
	 }
	   }
	  
  }
  }
   
if(choice==4)
{if(count!=0)
{
  cout<<"1.Display All customers"<<endl;
  cout<<"2.search Customers"<<endl;
  cout<<"3.Modify customer"<<endl;
  cout<<"4.Delete Customer"<<endl;
  int choice1;
  cin>>choice1;
	
  if(choice1==1)
  {
	for(int i=0;i<count;i++)
	{x[i]->Display_Customer_Record();
	}
  }
  if(choice1==2)
  {
	  int search;
	  
	   cout<<"enter Customer ID to search"<<endl;
	  cin>>search;
	  for(int i=0;i<count;i++)
	  {
		  if(x[i]->search(search)==1)
		  { cout<<"found"<<endl;
		   x[i]->Display_Customer_Record();
			  break;
		  }
		  if((count-i)==1)
		  { cout<<"not found"<<endl;
		  }
	  }


  }
  
  if(choice1==3)
  {  
	  int search;
	  
	  cout<<"enter Customer ID to search"<<endl;
	  cin>>search;
	  for(int i=0;i<count;i++)
	  {
		  if(x[i]->search(search)==1)
			{  cout<<"enter Modified details"<<endl;

			  x[i]->Add_New_Customer(b++);
		  
		   //x[i]->Display_Customer_Record();
			  break;
		  }
		  if((count-i)==1)
		  { cout<<"not found"<<endl;
		  }
  }
}
  if(choice1==4)
  { 
   int search;
	  
	  cout<<"enter Customer ID to search for delete"<<endl;
	  cin>>search;
	  for(int i=0;i<count;i++)
	  {
		  if(x[i]->search(search)==1)
		  { 
		  x[i]->deletecustomer();
		  cout<<"Customer is deleted"<<endl;
			  break;
		  }
		  if(count-i==1)
		  { cout<<"not found"<<endl;
		  }
  }
}

  }

else
	cout<<"no Customer "<<endl;
}
if(choice==5)
{ if(count1!=0)
{
  cout<<"1.Display All Accounts"<<endl;
  cout<<"2.search Accounts"<<endl;
  cout<<"3.Modify Account"<<endl;
  cout<<"4.Delete Account"<<endl;
  int choice1;
  cin>>choice1;
  if(choice1==1)
  {
	for(int i=0;i<count1;i++)
	{a1[i]->Display_Account_Details();
	}
  }
  if(choice1==2)
  {
	  int id;
	  cout<<"enter account id"<<endl;
	  cin>>id;
	  for(int i=0;i<count1;i++)
	  { if(a1[i]->search(id)==1)
	   { cout<<"found"<<endl;
	  a1[i]->Display_Account_Details();
	   }
	  if(count1-i==1)
		  { cout<<"not found"<<endl;
		  }
	  }
  }
  if(choice1==3)
  {
	  int id;
	  cout<<"enter account id"<<endl;
	  cin>>id;
	  for(int i=0;i<count1;i++)
	  { if(a1[i]->search(id)==1)
	   { cout<<"found"<<endl;
	  m++;
	  cout<<"enter modified details"<<endl;
	  a1[i]->addnewaccount(id,m);
	   }
	  if(count-i==1)
		  { cout<<"not found"<<endl;
		  }
	  }
  }
  if(choice1==4)
  {   int id;
	  cout<<"enter account id to delete account"<<endl;
	  cin>>id;
	  for(int i=0;i<count1;i++)
	  { if(a1[i]->search(id)==1)
	   { cout<<"found"<<endl;
	  
	  cout<<"Account is deleted!"<<endl;
	  a1[i]->deleteaccount();
	  }
	  if(count1-i==1)
		  { cout<<"not found"<<endl;
		  }
  }
}
}
else
	cout<<"no Accounts "<<endl;
}
if(choice==6)
{ if(count2!=0)
{ cout<<"1.display all transactions"<<endl;
cout<<"2. search transaction"<<endl;
int choice1;
cin>>choice1;
 if(choice1==1)
 {
	for(int i=0;i<count2;i++)
	{t1[i]->Display_Transaction();
	}
 }
 if(choice1==2)
 {
	 int search_tran;
	 cout<<"enter transaction id to search"<<endl;
	 cin>>search_tran;
	 for(int i=0;i<count2;i++)
	 {
		 if(t1[i]->search_transaction(search_tran)==1)
		 {
			 cout<<"found"<<endl;
			 t1[i]->Display_Transaction();
		 }
		 if(count2-i==1)
		  { cout<<"not found"<<endl;
		  }
	 }
 }
}
else
	cout<<"no Transaction "<<endl;
}
if(choice==7)
{
	exit(0);
}
}for(int i=0;i<count;i++)
{free(x[i]);
}
for(int i=0;i<count1;i++)
{free(a1[i]);
}
for(int i=0;i<count2;i++)
{free(t1[i]);
}

return 0;
}