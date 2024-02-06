#include<bits/stdc++.h>
using namespace std;

#define ff first
#define ss second

#define pii pair<int,int>

void priority(){

}

int main(){
    //priority + robin round. must work in either case.
    //given -> AT BT pri
    int n;
    cin>>n;
    cout << fixed << setprecision(5);
    // at pt bt jobno.
    vector<pair<pii,pii>> v(n);
    // at bt ct tat wt
    vector<vector<int>> table(n,vector<int>(6));
    for(int i=0;i<n;i++){
        cin>>v[i].ff.ff>>v[i].ff.ss>>v[i].ss.ff;
        v[i].ss.ss=i+1;
    }
}