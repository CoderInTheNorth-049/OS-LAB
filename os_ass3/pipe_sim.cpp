#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include<bits/stdc++.h>

using namespace std;

// Function to execute a command and redirect its output to a file
void exec_redirect_out(const string &cmd, const string &filename) {
    string full_cmd = cmd + " > " + filename;
    //cout<<full_cmd<<endl;
    system(full_cmd.c_str());
}

// Function to execute a command and provide a file as its input
void exec_redirect_in(const string &cmd, const string &filename) {
    string full_cmd = cmd + " < " + filename;
    //cout<<full_cmd<<endl;
    system(full_cmd.c_str());
}

int main() {
    // Temporary filename for storing intermediate output
    const string temp_filename = "./tmp/pipe_temp.txt";
    string cmd;
    int idx;
       cout<<"Enter 2 commands separated by pipe operator:\n";
       getline(cin,cmd);
       for(int i=0;i<cmd.size();i++){
        if (cmd[i]=='|'){
            idx=i;
            break;
        }
       }
       //cout<<cmd<<endl;   
       string cmd1=cmd.substr(0,idx);
       string cmd2=cmd.substr(idx+2,cmd.size()-idx-2);
        //cout<<cmd1<<" "<<cmd2<<endl;

    // Execute the first command and redirect its output to the temp file
    exec_redirect_out(cmd1, temp_filename);

    // Execute the second command and use the temp file as its input
    exec_redirect_in(cmd2, temp_filename);

    // Delete the temporary file
    //remove(temp_filename.c_str());
    return  0;
}

/* 
OUTPUT:
Enter 2 commands separated by pipe operator:
ls -l | grep -c 'pccoe'
3
 */
