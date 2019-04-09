#include<iostream>
#include<cstring>
using namespace std;
class Customer
{ private:
	char  Customer_Name[20], E_mail[30];
	 int Customer_ID;
long int Telephone_Number;
char  Address[50], NIC_NO[25];
public:
	
	
	void Add_New_Customer(int id);
	
	void Add_New_Customer( int id,char name[20],char email[30],long int telephone,char address[50],char nic[25]);
	
	int search(int s);
	void Display_Customer_Record();
	int Customer_id_exist(int j);
	void deletecustomer();
	
	int checkspace();
};
class Account
{    private:
	 int Account_ID,Customer_ID;
	char  Account_Type[20];
	double Balance;
	char Date_of_Creation[20];
     public:
		 double check(int a);
		 int search(int a);
	void addnewaccount(int a,int b);
		 void addnewaccount( int accountid, long int customerid,char accounttype[20],double bal,char date[20]);
		 	 void Display_Account_Details();
	 void deleteaccount();
		int checkspace();
		 void balanceupdate(double b);
		
};
class Transaction
{private:
	 int Transaction_ID,Account_ID;
	char  Transaction_Type[20];
double Amount_Transacted;
public:
	int search_transaction(int i);
	
	void Make_New_Transaction(int a,int b,double bal, char trans_type[20]);
	
	void Make_New_Transaction(int tans_id, int account_id,char transiction_type[20],double amount_transacted);
	
	void Display_Transaction();
	
};
int Customer::Customer_id_exist(int j)
{ if(j==Customer_ID)
   return 1;
else 
	return 0;
}
void Customer::Add_New_Customer(int id)
	{ 
		cout<<"Enter Customer name"<<endl;
		if(cin.peek()=='\n') cin.ignore();
	cin.getline(Customer_Name,20);
	
	cout<<"enter email"<<endl;
	cin.getline(E_mail,30);
	
	cout<<"enter Address"<<endl;
	cin.getline(Address,50);
	
	cout<<"enter cnic"<<endl;
	cin.getline(NIC_NO,25);
	
	cout<<"enter telephone number"<<endl;
	cin>>Telephone_Number;
	Customer_ID=id;
	
	}
void Customer::Add_New_Customer( int id,char name[20],char email[30],long int telephone,char address[50],char nic[25])
	{ Customer_ID=id;
	strcpy(Customer_Name,name);
	
	strcpy(E_mail,email);
	Telephone_Number=telephone;
	strcpy(Address,address);
	strcpy(NIC_NO,nic);


	}
	int Customer::search(int s)
	{ if(Customer_ID==s)
	      { 
			  return 1;
	      }
	else
		return 0;
	}
	void Customer::Display_Customer_Record()
	{if(Customer_ID!=0 || strcmp(Customer_Name,"\0")!=0)
	{
		cout<<"customer id is  "<<Customer_ID<<endl;
	cout<<"customer name is  "<<Customer_Name<<endl;
	
	cout<<"Email is  "<<E_mail<<endl;
	cout<<"Telephone number is  "<<Telephone_Number<<endl;
	cout<<"Address is  "<<Address<<endl;
	cout<<"Cnic number is "<<NIC_NO<<endl;
	cout<<"*******************************"<<endl<<endl;
	}
	}
	void Customer::deletecustomer()
	{ Customer_ID=0;
	strcpy(Customer_Name,"\0");
	strcpy(E_mail,"\0");
	strcpy(NIC_NO,"\0");
	Telephone_Number=0;



	}
	int Customer::checkspace()
	{
		if(Customer_ID==0 && strcmp(Customer_Name,"\0")==0)
		{
			return 1;
		}
		else
			return 0;
	}

	 double Account:: check(int a)
	{
		if(a==Account_ID)
		{
			return Balance;
		}
		else 
			return 0;
	}
		 int Account::search(int a)
	{
		if(a==Account_ID)
		{
			return 1;
		}
		else 
			return 0;
	}
		 void Account::addnewaccount(int a,int b)
		 {Account_ID=a;
		 Customer_ID=b;
			 if(cin.peek()=='\n') cin.ignore();
			 cout<<"Enter Account type"<<endl;
		 cin.getline(Account_Type,20);
		 cout<<"enter balance"<<endl;
		 cin>>Balance;
		 if(cin.peek()=='\n') cin.ignore();
		 cout<<"enter date"<<endl;
		 cin.getline(Date_of_Creation,20);
		 }
		 
		 void Account::addnewaccount( int accountid, long int customerid,char accounttype[20],double bal,char date[20])
		 {
			 Account_ID=accountid;
			 Customer_ID=customerid;
			 strcpy(Account_Type,accounttype);
			 Balance=bal;
			 strcpy(Date_of_Creation,date);
		 }
		 void Account::Display_Account_Details()
	{if(Account_ID!=0 || Customer_ID!=0)
		 {
		cout<<"customer id is  "<<Customer_ID<<endl;
	cout<<"Account id is  "<<Account_ID<<endl;
	cout<<"Account Type is  "<<Account_Type<<endl;
	cout<<"Date of creation is  "<<Date_of_Creation<<endl;
	cout<<"Total Balance  is  "<< Balance<<endl;
	cout<<"*******************************"<<endl<<endl;
		 }
	
	}
		 void Account::deleteaccount()
		 { Customer_ID=0;
		 Account_ID=0;
		  strcpy(Account_Type,"\0");
		  Balance=0;
			 strcpy(Date_of_Creation,"\0");

		 }
		int Account::checkspace()
		 {
			 if(Customer_ID==0 && Account_ID==0)
			 { return 1;
			 }
			 else
				 return 0;
		 }
		void Account:: balanceupdate(double b)
		{Balance=b;
		}
		int Transaction::search_transaction(int i)
	{
		if(i==Transaction_ID)
		{
			return 1;
		}
		else
			return 0;
	}
	void Transaction:: Make_New_Transaction(int a,int b,double bal, char trans_type[20])
	{ Transaction_ID=b;
	Account_ID=a;
	
		
	strcpy(Transaction_Type,trans_type);
		
		Amount_Transacted=bal;
		
		
	}
	void Transaction::Make_New_Transaction(int tans_id, int account_id,char transiction_type[20],double amount_transacted)
	{    Transaction_ID=tans_id;
	 Account_ID=account_id;
	strcpy(Transaction_Type,transiction_type);
	Amount_Transacted=amount_transacted;
	}
	void Transaction::Display_Transaction()
	{
		cout<<"Transaction id is "<<Transaction_ID<<endl;
		cout<<"Account id is"<<Account_ID<<endl;
		cout<<"Transaction Type is "<<Transaction_Type<<endl;
		cout<<"Amount Transacted is "<<Amount_Transacted<<endl;
		cout<<"*******************************"<<endl<<endl;
	}