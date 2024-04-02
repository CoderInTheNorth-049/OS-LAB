#include<bits/stdc++.h>
using namespace std;
int n,m;

struct table{
    int filesz;
    int blockno;
    int blocksz;
    int frag;
};

void update(int &i,int &idx,vector<int> &block,vector<int> &file,auto &ans){
    ans[idx].filesz=file[idx];
    ans[idx].blockno=i;
    ans[idx].blocksz=block[i];
    block[i]-=file[idx];
    ans[idx].frag=block[i];
}

void print(auto &ans){
    cout<<"file no\t file size\t block no\t block size\t fragment\n";
    for(int i=1;i<=m;i++){
        cout<<i<<"\t\t"<<ans[i].filesz<<"\t\t"<<ans[i].blockno<<"\t\t"<<ans[i].blocksz<<"\t\t"<<ans[i].frag<<endl;
    }
}

void FirstFit(vector<int> block,vector<int> file){
    vector<table> ans(m+1);
    function<void(int)> edit=[&](int idx){
        for(int i=1;i<=n;i++){
            if(block[i]>=file[idx]){
                update(i,idx,block,file,ans);
                return;
            }
        }
    };
    for(int i=1;i<=m;i++){
        edit(i);
    }
    cout<<"\nFirst Fit:\n";
    print(ans);

}

void BestFit(vector<int> block,vector<int> file){
    vector<table> ans(m+1);
    function<void(int)> edit=[&](int idx){
        int curridx=-1,currval=1e8;
        for(int i=1;i<=n;i++){
            if(block[i]>=file[idx] && (block[i]-file[idx])<currval){
                curridx=i;
                currval=block[i]-file[idx];
            }
        }
        update(curridx,idx,block,file,ans);
    };
    for(int i=1;i<=m;i++){
        edit(i);
    }
    cout<<"\nBest Fit:\n";
    print(ans);
}

void WorstFit(vector<int> block,vector<int> file){
    vector<table> ans(m+1);
    function<void(int)> edit=[&](int idx){
        int curridx=-1,currval=-1;
        for(int i=1;i<=n;i++){
            if(block[i]>=file[idx] && (block[i]-file[idx])>currval){
                curridx=i;
                currval=block[i]-file[idx];
            }
        }
        update(curridx,idx,block,file,ans);
    };
    for(int i=1;i<=m;i++){
        edit(i);
    }
    cout<<"\nWorst Fit:\n";
    print(ans);
}

void NextFit(vector<int> block,vector<int> file){
    vector<table> ans(m+1);
    function<void(int,int&)> edit=[&](int idx,int &last){
        for(int i=(last+1)%(n+1);i!=last%(n+1);i++){
            i%=(n+1);
            if(i==0) continue;
            if(block[i]>=file[idx]){
                update(i,idx,block,file,ans);
                last=i;
                return;
            }
        }
    };
    int last=0;
    for(int i=1;i<=m;i++){
        edit(i,last);
    }
    cout<<"\nNext Fit:\n";
    print(ans);
}

int main(){
    cout<<"enter no. of memory blocks: ";
    cin>>n;
    cout<<"enter no. of files: ";
    cin>>m;
    vector<int> block,file;
    block.resize(n+1);
    file.resize(m+1);

    cout<<"enter size of each memory block\n";
    for(int i=1;i<=n;i++) cin>>block[i];
    cout<<"enter size of each file\n";
    for(int i=1;i<=m;i++) cin>>file[i];

    FirstFit(block,file);
    BestFit(block,file);
    WorstFit(block,file);
    NextFit(block,file);

}