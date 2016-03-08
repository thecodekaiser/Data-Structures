#include<iostream>
#include<string>
using namespace std;

int find_DNA_Match(string str1,string str2,int start=0){
	char c1,c2;
	int result=-1;
	for(int i=0;i<str1.length()-str2.length()+1;i++){
		int lasti=i;
		for(int j=0;j<str2.length();j++){
			c1=str1.at(i);
			c2=str2.at(j);
			if(!((c1=='A'&&c2=='T')||(c2=='A'&&c1=='T')||(c1=='G'&&c2=='C')||(c1=='C'&&c2=='G')))
				break;
			else
				i+=1;
			if(j==str2.length()-1)
				result=lasti;
		}
		i=lasti;
	}
	return result+1;
}

int main(){
	string str1,str2;
	getline(cin,str1);
	getline(cin,str2);
	cout<<"WE CAN MATCH THE GIVEN STRAND AT THIS POSITION OF BASE: "<<find_DNA_Match(str1,str2)<<endl;
	return 0;
}
