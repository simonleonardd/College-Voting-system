#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
fstream file;
class Student
{
	protected:
		char name[30];
		int Id;
		bool vote;
	public:
		Student()
		{
			vote=0;
			Id=0;
		}
		Student(char Name[30],int id)
		{
			strcpy(name,Name);
			Id=id;
		}
		void getData();
		void setData();
		void setfile();
		void getfile();
		void getStud(int id);
		friend void castVote();
};
class Candidate:protected Student
{
	protected:
		int vote_count;
	public:
		Candidate()
		{
			vote_count=0;
		}
		void setCandidate();
		void viewCandidate();
		void CandidateList();
		void getCandidate();
		void addCandidate();
		friend void findWinner();
		friend void castVote();
		friend bool addvote(int cid);
};
void Candidate::addCandidate()
{
	file.open("candidate.dat",ios::app|ios::binary);
	file.write((char *)&*this,sizeof(class Candidate));
	file.close();
}
void Candidate::viewCandidate()
{
	file.open("candidate.dat",ios::in|ios::binary);
	while(file.read((char *)&*this,sizeof(class Candidate)))
	{
		this->getCandidate();
	}
	file.close();
}
void Candidate::CandidateList()
{
	file.open("candidate.dat",ios::in|ios::binary);
	while(file.read((char *)&*this,sizeof(class Candidate)))
	{
		cout<<this->name<<"\t\t\t\t"<<"|"<<"\t\t\t\t"<<this->Id<<"\n";
	}
	file.close();
}
void Candidate::getCandidate()
{
	this->getData();
	cout<<"The total number of vote's got by the candidate ::"<<vote_count<<endl;
}
void Candidate::setCandidate()
{
	this->setData();
}
void Student::setData()
{
	cout<<"Enter the name of the student ::";
	cin>>name;
	cout<<"Enter the Roll number of student ::";
	cin>>Id;
}
void Student::getData()
{
	cout<<"Name of the student is ::"<<name<<endl;
	cout<<"Roll number of the Student is ::"<<Id<<endl;
	if(vote)
	cout<<"Vote has been casted "<<endl;
	else
	cout<<"Vote has not yet been cast "<<endl;
}
void Student::setfile()
{
	file.open("student.dat",ios::app|ios::binary);
	file.write((char *)&*this,sizeof(class Student));
	file.close();
}
void Student::getfile()
{
	file.open("student.dat",ios::in|ios::binary);
	while(file.read((char *)&*this,sizeof(class Student)))
	this->getData();
	file.close();
}
bool addvote(int cid)
{
	int k;
	k=0;
	Candidate a;
	file.open("candidate.dat",ios::in|ios::binary);
	while(file.read((char *)&a,sizeof(class Candidate)))
	{
		if(a.Id==cid)
		{
		 fstream c;
		 c.open("candidate.dat",ios::out|ios::in|ios::binary);
		 c.seekp(sizeof(class Candidate)*k,ios::beg);
		 a.vote_count+=1;
		 c.write((char *)&a,sizeof(class Candidate));
		 c.close();
		 file.close();
		 return 1;
		}
		k++;
	}
	file.close();
	return 0;
}
void castVote()
{
	Student x;
	Candidate y;
	char sname[30];
	int sid;
	int cid;
	cout<<"Enter Your name ::";
	cin>>sname;
	cout<<"Enter Your student Id ::";
	cin>>sid;
	int flag;
	flag=0;
	int k=0;
	file.open("student.dat",ios::in|ios::binary);
	while(file.read((char *)&x,sizeof(class Student)))
	{
		if(x.Id==sid&&strcmp(x.name,sname)==0&&x.vote==0)
		{
			y.viewCandidate();
			while(1)
			{
			//y.viewCandidate();
			cout<<"Enter the candidate Id you want to vote for ::";
			cin>>cid;
			fstream c;
		 	c.open("student.dat",ios::out|ios::in|ios::binary);
		 	c.seekp(sizeof(class Student)*k,ios::beg);
		 	x.vote+=1;
		 	c.write((char *)&x,sizeof(class Student));
		 	c.close();
		 	file.close();
			if(addvote(cid))
			{
			cout<<"The vote is casted successfully "<<endl;
			return;
			}
			else
			cout<<"Invalid Candidate Id "<<endl;
			}
		}
		k++;
	}
	cout<<"Invaid cridentials or you have already castted your vote"<<endl;
	file.close();
}
void findWinner()
{
	Candidate can;
	int vt;
	vt=0;
	file.open("candidate.dat",ios::in|ios::binary);
	while(file.read((char *)&can,sizeof(class Candidate)))
	{
		if(vt<can.vote_count)
		vt=can.vote_count;
	}
	cout<<vt;
	file.close();
	int cnt;
	file.open("candidate.dat",ios::in|ios::binary);
	while(file.read((char *)&can,sizeof(class Candidate)))
	{
		if(vt==can.vote_count)
		{
			cout<<"The winner of this election is"<<endl;
			can.getData();
		}
	}
	file.close();
}
int main()
{
	Student S;
	Candidate C,C1;
	int oo,op,op1;
	int x,pas,x1;
	while(oo=1)
	{
		cout<<"\n\t\t1.ADMINISTRATOR\n\t\t2.VOTER";
		cout<<"\n\t\tEnter Your Choice :";
		cin>>op1;
	if(op1==1)
 {
		cout<<"\n\t\tEnter The Password To Login:";
		cin>>pas;
	if(pas==101)
  {	
	while(1)
	{

		cout<<"\n\t\t1.ADD VOTER\n\t\t2.ADD CANDIDATE\n\t\t3.\n\t\tVIEW VOTERS\n\t\t4.VIEW CANDIDATES\n\t\t5.CHECK RESULT\n\t\tEnter the Choice :";
		cin>>op;
		if(op==1)
		{
			S.setData();
			S.setfile();
			cout<<"\n\n\n";
		}
		if(op==2)
		{
			C.setCandidate();
			C.addCandidate();
			cout<<"\n\n\n";
		}
		if(op==3)
		{
			S.getfile();
			cout<<"\n\n\n";
		}
		if(op==4)
		{
			C.viewCandidate();
			cout<<"\n\n\n";
		}
		
		if(op==5)
		{
			findWinner();
			cout<<"\n\n\n";
		}
	}
  }
  else
  {
 	cout<<"Your Password is wrong";
 	
  } 
 }
 if(op1==2)
 {			
 			C1.CandidateList();
			castVote();
			cout<<"\n\n\n";		
 }
}
}
