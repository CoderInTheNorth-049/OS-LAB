#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include<bits/stdc++.h>
using namespace std;

multimap<int,string> mp;

// Function to calculate total seek time
int calculateSeekTime(const vector<int>& requests, int headPosition) {
    int seekTime = 0;
    int currentHead = headPosition;
    for (int i = 0; i < requests.size(); ++i) {
        seekTime += abs(currentHead - requests[i]);
        currentHead = requests[i];
    }
    return seekTime;
}

// FIFO Disk Scheduling Algorithm
int fifo(const vector<int>& requests, int headPosition, vector<int>& sequence) {
    int seekTime = 0;
    int currentHead = headPosition;
    for (int i = 0; i < requests.size(); ++i) {
        sequence.push_back(requests[i]);
        seekTime += abs(currentHead - requests[i]);
        currentHead = requests[i];
    }
    mp.insert({seekTime,"FIFO"});
    return seekTime;
}

// SSTF Disk Scheduling Algorithm
int sstf(const vector<int>& requests, int headPosition, vector<int>& sequence) {
    vector<int> sortedRequests = requests;
    sort(sortedRequests.begin(), sortedRequests.end());
    int seekTime = 0;
    int currentHead = headPosition;
    while (!sortedRequests.empty()) {
        int closestRequest = sortedRequests.front();
        int minDistance = abs(currentHead - closestRequest);
        int closestIndex = 0;

        for (int i = 1; i < sortedRequests.size(); ++i) {
            int distance = abs(currentHead - sortedRequests[i]);
            if (distance < minDistance) {
                minDistance = distance;
                closestRequest = sortedRequests[i];
                closestIndex = i;
            }
        }
        sequence.push_back(closestRequest);
        seekTime += minDistance;
        currentHead = closestRequest;
        sortedRequests.erase(sortedRequests.begin() + closestIndex);
    }
    mp.insert({seekTime,"SSTF"});
    return seekTime;  
}

// SCAN Disk Scheduling Algorithm
int scan(const vector<int>& requests, int headPosition, int maxCylinder, vector<int>& sequence) {
    vector<int> lowerRequests, upperRequests;
    for (int request : requests) {
        if (request < headPosition) {
            lowerRequests.push_back(request);
        } else {
            upperRequests.push_back(request);
        }
    }
    sort(lowerRequests.begin(), lowerRequests.end(), greater<int>());
    sort(upperRequests.begin(), upperRequests.end());
    int seekTime = 0;
    int currentHead = headPosition;
    int direction = 1; // 1 for moving upwards, -1 for moving downwards
    while (true) {
        if (direction == 1) {
            for (int i = 0; i < upperRequests.size(); ++i) {
                if (upperRequests[i] >= currentHead) {
                    sequence.push_back(upperRequests[i]);
                    seekTime += abs(currentHead - upperRequests[i]);
                    currentHead = upperRequests[i];
                    upperRequests.erase(upperRequests.begin() + i);
                    break;
                }
            }
            if (upperRequests.empty()) {
                if (currentHead != maxCylinder) {
                    sequence.push_back(maxCylinder);
                    seekTime += abs(currentHead - maxCylinder);
                    currentHead = maxCylinder;
                }
                direction = -1;
                continue;
            }
        } else {
            for (int i = 0; i < lowerRequests.size(); ++i) {
                if (lowerRequests[i] <= currentHead) {
                    sequence.push_back(lowerRequests[i]);
                    seekTime += abs(currentHead - lowerRequests[i]);
                    currentHead = lowerRequests[i];
                    lowerRequests.erase(lowerRequests.begin() + i);
                    break;
                }
            }
            if (lowerRequests.empty()) {
                if (currentHead != 0) {
                    sequence.push_back(0);
                    seekTime += abs(currentHead);
                    currentHead = 0;
                }
                break;
            }
        }
    }
    mp.insert({seekTime,"SCAN"});
    return seekTime;
}

// C-SCAN Disk Scheduling Algorithm
void cscan(int arr[], int head, int maxCylinder, int size, vector<int>& sequence) {
    int seek_count = 0;
    int distance, cur_track;
    vector<int> left, right;
    left.push_back(0);
    right.push_back(maxCylinder); // Changed here
    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            left.push_back(arr[i]);
        if (arr[i] > head)
            right.push_back(arr[i]);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    for (int i = 0; i < right.size(); i++) {
        cur_track = right[i];
        sequence.push_back(cur_track);
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }
    head = 0;
    seek_count += maxCylinder; // Changed here
    for (int i = 0; i < left.size(); i++) {
        cur_track = left[i];
        sequence.push_back(cur_track);
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }
    mp.insert({seek_count,"C-SCAN"});
    cout << "Seek Time = " << seek_count << endl;
    cout << "Order of requests serviced by C-SCAN: ";
    for (int i = 0; i < sequence.size(); i++) {
        cout << sequence[i] << "->";
    }
    cout << endl;
}

int main() {
    int size;
    cout << "Enter the number of requests: ";
    cin >> size;
    int arr[size];
    cout << "Enter the requests: ";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    int head, maxCylinder;
    cout << "Enter the initial head position: ";
    cin >> head;
    cout << "Enter the maximum cylinder size: ";
    cin >> maxCylinder;
    vector<int> requests(arr, arr + size);
    vector<int> sequence;
    cout << "Initial position of head: " << head << endl;
    cout << "FIFO Seek Time: " << fifo(requests, head, sequence) << endl;
    cout << "Sequence: ";
    for (int i = 0; i < sequence.size(); i++) {
        cout << sequence[i] << "->";
    }
    cout << endl;
    sequence.clear();
    cout << "SSTF Seek Time: " << sstf(requests, head, sequence) << endl;
    cout << "Sequence: ";
    for (int i = 0; i < sequence.size(); i++) {
        cout << sequence[i] << "->";
    }
    cout << endl;
    sequence.clear();
    cout << "SCAN Seek Time: " << scan(requests, head, maxCylinder, sequence) << endl;
    cout << "Sequence: ";
    for (int i = 0; i < sequence.size(); i++) {
        cout << sequence[i] << "->";
    }
    cout << endl;
    sequence.clear();
    cout << "C-SCAN" << endl;
    cscan(arr, head, maxCylinder, size, sequence);
    cout<<endl;

    for(auto &it:mp){
        cout<<it.second<<" < ";
    }
    cout<<endl;
    return 0;
}