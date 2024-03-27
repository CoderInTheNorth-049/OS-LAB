#include<bits/stdc++.h>
using namespace std;


void waiting(auto &alloc,auto &mx,auto &need,auto &avail){
    int n=alloc.size(),m=avail.size();
   
    queue<int> waitlist;
    vector<int> seq;
    vector<vector<int>> before(n,vector<int>(m)), after(n,vector<int>(m));
   
    auto check=[&](int idx)->bool{
        for(int i=0;i<m;i++){
            if(need[idx][i]>avail[i]) return false;
        }
        return true;
    };

    auto poss=[&](int idx, auto &req)->bool{
        for(int i=0;i<m;i++){
            if(req[i]>need[idx][i]) return false;
        }
        return true;
    };
   
    function<void(int,vector<int>&)> update_avail=[&](int idx,vector<int> &req){
        for(int i=0;i<m;i++){
            avail[i]-=req[i];
            avail[i]+=mx[idx][i];
        }
    };
   
    function<void()> print_seq=[&](){
        cout<<endl;
        cout<<"executing sequence with waiting:\n";
        for(auto &it:seq){
            cout<<"p"<<it<<" ";
        }
        cout<<endl;
    };
   
    function<void()> print_avail=[&](){
        for(int i=0;i<m;i++){
            cout<<avail[i]<<" ";
        }
        cout<<endl;
    };
   
    function<void(int)> print_need=[&](int idx){
        for(int i=0;i<m;i++){
            cout<<need[idx][i]<<" ";
        }
        cout<<endl;
    };


   
    for(int i=0;i<n;i++){
        cout<<"for p"<<i<<endl;
        bool ret = check(i);
       
        cout<<"current available\n";
        print_avail();
        cout<<"current need\n";
        print_need(i);
        cout<<endl;
       
        if(!ret){
            waitlist.push(i);
            cout<<"need > avail. skipped and added to waitlist\n";
            cout<<endl;
            continue;
        }
        cout<<"need <= avail. Now enter requested allocation\n";
        vector<int> req(m);
        for(int i=0;i<m;i++){
            cin>>req[i];
        }

        before[i]=avail;
        ret = poss(i,req);
        if(!ret){
            cout<<"Requested allocation is greater than max need. Therefore not possible to allocate and no sequence exists.\n";
            return;
        }
        update_avail(i,req);
        cout<<"resources available after allocation:\n";
        print_avail();
        cout<<endl;
        seq.push_back(i);
    }
   
    while(!waitlist.empty()){
        int curr=waitlist.front();
        cout<<"for p"<<curr<<endl;
        cout<<"current available\n";
        print_avail();
        cout<<"current need\n";
        print_need(curr);
        cout<<endl;
        waitlist.pop();
       
        bool ret = check(curr);
        if(!ret){
            waitlist.push(curr);
            cout<<"need > avail. skipped and added to waitlist\n";
            cout<<endl;
            continue;
        }
        cout<<"need <= avail. Now enter requested allocation\n";
        vector<int> req(m);
        for(int i=0;i<m;i++){
            cin>>req[i];
        }
        before[curr]=avail;
        if(!ret){
            cout<<"Requested allocation is greater than max need. Therefore not possible to allocate.\n";
            return;
        }
        update_avail(curr,req);
        cout<<"resources available after allocation:\n";
        print_avail();
        cout<<endl;
        seq.push_back(curr);
    }
    print_seq();
   
}

int main(){
   
    cout<<"enter no of processes and no of resources respectively\n";
    int n,m;cin>>n>>m;
    vector<vector<int>> alloc(n,vector<int>(m)), mx(n,vector<int>(m)), need(n,vector<int>(m));
    vector<int> avail(m);
   
    cout<<"enter allocation of resources for every process\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>alloc[i][j];
        }
    }
   
    cout<<"enter max allocation of resources for every process\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>mx[i][j];
        }
    }
   
    cout<<"enter available resources\n";
    for(int i=0;i<m;i++) cin>>avail[i];
   
    auto get_need=[&](){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                need[i][j]=mx[i][j]-alloc[i][j];
            }
        }
    };
    get_need();
   
    cout<<"\nNeed table:\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cout<<need[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
   
    waiting(alloc,mx,need,avail);
    
}