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
    table[i][4]=table[i][3]-table[i][1];tat+=table[i][4];
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
    int quant=4;
    // for v => {at, {bt, jobNo}}
    int time=v[0].ff,tat=0,wt=0;
    queue<pair<int,pii>> q;
    // q-> {AT,{BT, jobNo}}
    q.push(v[0]);
    int it=1,temp=0;
    while(!q.empty()){
        pair<int,pii> curr=q.front();
        //cout<<curr.ff<<" "<<curr.ss.ff<<" "<<curr.ss.ss<<endl;
        q.pop();
        time+=min(quant,curr.ss.ff);
        while(it<n && v[it].ff<=time){
            
            q.push(v[it]);
            it+=1;
        }
        curr.ss.ff-=quant;
        if(curr.ss.ff<=0){
            updateTable(curr.ss.ss-1,temp,v,table,tat,wt,time);
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
    cout<<"Enter no. of jobs: ";
    cin>>n;
    cout << fixed << setprecision(5);
    // at bt job no.
    vector<pair<int,pii>> v(n);
    // at bt ct tat wt
    vector<vector<int>> table(n,vector<int>(6));
    cout<<"Enter AT and BT for jobs:\n";
    for(int i=0;i<n;i++){
        cin>>v[i].ff>>v[i].ss.ff;
        v[i].ss.ss=i+1;
    }
    cout<<"First come first serve:"<<endl;
    fcfs(n,v,table);
    cout<<endl<<endl;
    cout<<"Non pre-emptive SJF:"<<endl;
    nsjf(n,v,table);
    cout<<endl<<endl;
    cout<<"Pre-emptive SJF:"<<endl;
    sjf(n,v,table);
    cout<<endl<<endl;
    cout<<"Round Robin:"<<endl;
    robin(n,v,table);
    cout<<endl<<endl;

}
/*OUTPUT:

Enter no. of jobs: 4
Enter AT and BT for jobs:
0 8
1 4
2 9
3 5
First come first serve:
job AT BT CT TAT WT
1 0 8 8 8 0 
2 1 4 12 11 7 
3 2 9 21 19 10 
4 3 5 26 23 18 
avg tat: 15.25000
avg wt: 8.75000


Non pre-emptive SJF:
job AT BT CT TAT WT
1 0 8 8 8 0 
2 1 4 12 11 7 
3 2 9 26 24 15 
4 3 5 17 14 9 
avg tat: 14.25000
avg wt: 7.75000


Pre-emptive SJF:
job AT BT CT TAT WT
1 0 8 17 17 9 
2 1 4 5 4 0 
3 2 9 26 24 15 
4 3 5 10 7 2 
avg tat: 13.00000
avg wt: 6.50000


Round Robin:
job AT BT CT TAT WT
1 0 8 20 20 12
2 1 4 8 7 3
3 2 9 26 24 15
4 3 5 25 22 17 
avg tat: 18.25000
avg wt: 11.75000

*/