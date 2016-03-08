#include<iostream>
#include<vector>
#include<cstdio>
#include<cstdlib>
using namespace std;

//Function to give the majority candidate
int findMaj_el(vector<int> V);
//Function to ascertain if a given candidate has a majority in a given vector
bool isMajority(vector<int> V,int el);
//Function to find the actual majority element
void maj_el(vector<int> v){
	int n = findMaj_el(v);
	//cout<<n<<endl;
	if(isMajority(v,n))
		printf("%d\n",n);
	else
		printf("-1\n");
}

int main(){
	int t;
	scanf("%d",&t);
	vector<int> v(t);
	for(int i=0;i<t;i++) cin>>v[i];
	maj_el(v);
	return 0;
}
//Function: findMaj_el(vector<int> v)
int findMaj_el(vector<int> V){
	int maj_Index=0,count=1;
	for(int i=1;i<V.size();i++){
		if(V.at(maj_Index)==V.at(i)){
			//cout<<"YES\n"<<endl;		
			count+=1;
		}
		else{
			//cout<<"NO\n"<<endl;
			count-=1;
		}
		if(count==0){
			maj_Index=i;
			count=1;
		}
	}
	//cout<<V.at(maj_Index)<<endl;
	return V.at(maj_Index);
}
//Function:isMajority(vector<int> v,int n)
bool isMajority(vector<int> v,int el){
	int count=0;
	for(int i=0;i<v.size();i++){
		if(el==v.at(i))
			count+=1;
		if(count>v.size()/2)
			return 1;
	}
	return 0;
}

