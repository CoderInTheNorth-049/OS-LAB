#include<bits/stdc++.h>
using namespace std;

#define ff first
#define ss second

#define pii pair<int,int>

void updateTable(int i, int &strt, vector<pair<int,pii>> &v, vector<vector<int>> &table, int &tat, int &wt, int ct){
    table[i][0]=v[i].ss.ss; //jobNo
    table[i][1]=v[i].ff; //AT
    table[i][2]=v[i].ss.ff; //BT
    if(ct==1e9) ct=max(v[i].ff,strt)+v[i].ss.ff;
    table[i][3]=ct;// CT
    strt=table[i][3];
    table[i][4]=strt-table[i][1];tat+=table[i][4];
    table[i][5]=table[i][4]-table[i][2];wt+=table[i][5];
}

void printTable(int n,vector<vector<int>> &table,int tat,int wt){
    cout<<"job AT BT CT TAT WT\n";
    for(auto &it:table){
        for(int x:it) cout<<x<<" ";
        cout<<endl;
    }
    cout<<"avg tat: "<<1.0*tat/n<<endl;
    cout<<"avg wt: "<<1.0*wt/n<<endl;
}

void robin(int n, vector<pair<int,pii>> v, vector<vector<int>> table){
    sort(v.begin(),v.end());
    // for v => {at, {bt, jobNo}}
    int time=v[0].ff,tat=0,wt=0;
    queue<pair<int,pii>> q;
    // q-> {AT,{BT, jobNo}}
    q.push(v[0]);
    int it=1,temp=0;
    while(1){
        pair<int,pii> curr=q.front();
        q.pop();
        time+=min(2,curr.ss.ff);
        while(v[it].ff<=time){
            q.push(v[it]);
            it+=1;
        }
        curr.ss.ff-=2;
        if(curr.ss.ff<=0){
            updateTable(curr.ss.ss,temp,v,table,tat,wt,time);
        }
        else q.push(curr);
        if(q.empty()){
            if(it<n){
                time=v[it].ff;
                q.push(v[it]);
            }else break;
        }
    }
     printTable(n,table,tat,wt);
}

void sjf(int n, vector<pair<int,pii>> v, vector<vector<int>> table){
    sort(v.begin(),v.end());
    // for v => {at, {bt, jobNo}}
    int time=v[0].ff,tat=0,wt=0;
    priority_queue<pair<pii,int>, vector<pair<pii,int>>, greater<pair<pii,int>>> pq;
    // pq -> {{remained BT, jobNo}, idx}
    pq.push({v[0].ss,0});
    int it=1,temp=0;
    while(1){
        pair<pii,int> curr=pq.top();
        //cout<<"idx "<<curr.ss<<"   remained"<<curr.ff.ff<<endl;
        pq.pop();
        time+=1;
        if(v[it].ff==time){
            pq.push({v[it].ss,it});
            it+=1;
        }
        curr.ff.ff-=1;
        if(curr.ff.ff!=0) pq.push(curr);
        else{
            updateTable(curr.ss,temp,v,table,tat,wt,time);
        }
        if(pq.empty()){
            if(it<n){
                time=v[it].ff;
                pq.push({v[it].ss,it});
            }else break;
        }
    }
    printTable(n,table,tat,wt);
}

void fcfs(int n,vector<pair<int,pii>> v,vector<vector<int>> table){
    sort(v.begin(),v.end());
    int strt=0,tat=0,wt=0;
    for(int i=0;i<n;i++){
        // jobNo at bt ct tat wt
        updateTable(i,strt,v,table,tat,wt,1e9);        
    }
    printTable(n,table,tat,wt);
}

void  nsjf(int n, vector<pair<int,pii>> v, vector<vector<int>> table){
    sort(v.begin(),v.end());
    // for v => at bt jobNo
    int it=1;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({v[0].ss.ff,0});
   
// jobNo at bt ct tat wt
    int strt=0,tat=0,wt=0;
    while(!pq.empty()){
        pii curr=pq.top();
        pq.pop();
        updateTable(curr.ss, strt, v, table, tat, wt, 1e9);
        while(it<n){
            if(v[it].ff<=strt){
                pq.push({v[it].ss.ff,it});
                it+=1;
            }
            else break;
        }
    }
    printTable(n,table,tat,wt);
}

int main(){
    int n;
    cin>>n;
    cout << fixed << setprecision(5);
    // at bt job no.
    vector<pair<int,pii>> v(n);
    // at bt ct tat wt
    vector<vector<int>> table(n,vector<int>(6));
    for(int i=0;i<n;i++){
        cin>>v[i].ff>>v[i].ss.ff;
        v[i].ss.ss=i+1;
    }
    //fcfs(n,v,table);
    //sjf(n,v,table);
    robin(n,v,table);
   
}