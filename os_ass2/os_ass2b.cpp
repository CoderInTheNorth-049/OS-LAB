#include<bits/stdc++.h>
using namespace std;

#define ff first
#define ss second

#define pii pair<int,int>

void updateTable(int i, int &strt, vector<pair<pii,pii>> &v, vector<vector<int>> &table, int &tat, int &wt, int ct){
    table[i][0]=v[i].ss.ss; //jobNo
    table[i][1]=v[i].ff.ff; //AT
    table[i][2]=v[i].ss.ff; //BT
    if(ct==1e9) ct=max(v[i].ff.ff,strt)+v[i].ss.ff;
    table[i][3]=ct;// CT
    strt=table[i][3];
    table[i][4]=strt-table[i][1];tat+=table[i][4];
    table[i][5]=table[i][4]-table[i][2];wt+=table[i][5];
    table[i][6]=v[i].ff.ss; //prio
}

void printTable(int n,vector<vector<int>> &table,int tat,int wt){
    cout<<"job AT BT CT TAT WT PRIO\n";
    for(auto &it:table){
        for(int x:it) cout<<x<<" ";
        cout<<endl;
    }
    cout<<"avg tat: "<<1.0*tat/n<<endl;
    cout<<"avg wt: "<<1.0*wt/n<<endl;
}


void priority(int n, vector<pair<pii,pii>> v, vector<vector<int>> table){
    sort(v.begin(),v.end());
    // v-> at pt bt jobno
    int it=1;
    priority_queue<pair<int,pii>, vector<pair<int,pii>>, greater<pair<int,pii>>> pq;
    pq.push({v[0].ff.ss,{v[0].ss.ff,0}});
   
    // jobNo at bt ct tat wt prio
    int strt=0,tat=0,wt=0;
    while(!pq.empty()){
        pair<int,pii> curr=pq.top();
        pq.pop();
        updateTable(curr.ss.ss, strt, v, table, tat, wt, 1e9);
        while(it<n){
            if(v[it].ff.ff<=strt){
                pq.push({v[it].ff.ss, {v[it].ss.ff, it}});
                it+=1;
            }
            else break;
        }
    }
    printTable(n,table,tat,wt);

}

int main(){
    //given -> AT BT pri
    int n;
    cout<<"Enter no. of jobs: ";
    cin>>n;
    cout << fixed << setprecision(5);
    // at pt bt jobno.
    vector<pair<pii,pii>> v(n);
    // jbNO at pt bt ct tat wt
    vector<vector<int>> table(n,vector<int>(7));
   cout<<"Enter AT, BT and PRIO for jobs:\n";
    for(int i=0;i<n;i++){
        cin>>v[i].ff.ff>>v[i].ss.ff>>v[i].ff.ss;
        v[i].ss.ss=i+1;
    }
    cout<<"Priority:"<<endl;
    priority(n,v,table);
    cout<<endl<<endl;
}

/*OUTPUT:

Enter no. of jobs: 4
Enter AT, BT and PRIO for jobs:
0 8 3
1 4 1
2 9 4
3 5 2
Priority:
job AT BT CT TAT WT PRIO
1 0 8 8 8 0 3 
2 1 4 12 11 7 1 
3 2 9 26 24 15 4 
4 3 5 17 14 9 2 
avg tat: 14.25000
avg wt: 7.75000

*/
