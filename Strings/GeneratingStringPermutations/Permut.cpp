#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
using namespace std;
vector<string> generatePermutations(string str){
	vector<string> res;
	//BASE CASE
	if(str.length()==0)
		res.push_back("");
	else
	{
		for(int i=0;i<str.length();i++){
			char ch=str[i];
			string rest=str.substr(0,i)+str.substr(i+1);
			vector<string> s=generatePermutations(rest);
			for(int j=0;j<s.size();j++){
				string ss=ch+s.at(j);
				res.push_back(ss);
			}
		}
	}
	return res;
}
int main(){
	string str;
	printf("Enter the string: ");
	getline(cin,str);
	vector<string> res=generatePermutations(str);
	for(int i=0;i<res.size();i++){
		cout<<res.at(i)<<endl;
	}
	return 0;
}
			
