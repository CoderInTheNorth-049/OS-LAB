#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <sstream>
#include <algorithm>
using namespace std;
void printFrames(const unordered_set<int> &frames)
{
    cout << "Frames: ";
    for (auto frame : frames)
    {
        cout << frame << " ";
    }
    cout << endl;
}
int fcfs(const vector<int> &pages, int numFrames)
{
    unordered_set<int> frames;
    queue<int> q; // To store the current frame content in FCFS order
    int pageFaults = 0;
    for (int i = 0; i < pages.size(); i++)
    {
        // If page is not in frames, it's a page fault
        if (frames.find(pages[i]) == frames.end())
        {
            pageFaults++;
            cout << "Page " << pages[i] << " caused a page fault." << endl;
            if (frames.size() < numFrames)
            {
                frames.insert(pages[i]);
                q.push(pages[i]);
            }
            else
            {
                // Remove the first added page from frames
                int front = q.front();
                q.pop();
                frames.erase(front);
                // Add the new page to frames
                frames.insert(pages[i]);
                q.push(pages[i]);
            }
        }
        printFrames(frames);
    }
    return pageFaults;
}
int lru(const vector<int> &pages, int numFrames)
{
    unordered_set<int> frames;
    vector<int> recentAccess;
    int pageFaults = 0;
    for (int i = 0; i < pages.size(); i++)
    {
        if (frames.find(pages[i]) == frames.end())
        {
            pageFaults++;
            cout << "Page " << pages[i] << " caused a page fault." << endl;
            if (frames.size() < numFrames)
            {
                frames.insert(pages[i]);
                recentAccess.push_back(pages[i]);
            }
            else
            {
                int lruPage = recentAccess[0];
                frames.erase(lruPage);
                recentAccess.erase(recentAccess.begin());
                // Add the new page to frames and recentAccess
                frames.insert(pages[i]);
                recentAccess.push_back(pages[i]);
            }
        }
        else
        {
            // Update recent access list
            recentAccess.erase(remove(recentAccess.begin(),

                                      recentAccess.end(), pages[i]),
                               recentAccess.end());
            recentAccess.push_back(pages[i]);
        }
        printFrames(frames);
    }

    return pageFaults;
}
int optimal(const vector<int> &pages, int numFrames)
{
    unordered_set<int> frames;
    int pageFaults = 0;
    for (int i = 0; i < pages.size(); i++)
    {
        // If page is not in frames, it's a page fault
        if (frames.find(pages[i]) == frames.end())
        {
            pageFaults++;
            cout << "Page " << pages[i] << " caused a page fault." << endl;
            // If number of frames is not full, add the page
            if (frames.size() < numFrames)
            {
                frames.insert(pages[i]);
            }
            else
            {
                int farthest = i;
                int pageToReplace = -1;
                for (const auto &frame : frames)
                {
                    int j;
                    for (j = i + 1; j < pages.size(); j++)
                    {
                        if (frame == pages[j])
                        {
                            break;
                        }
                    }
                    if (j > farthest)
                    {
                        farthest = j;
                        pageToReplace = frame;
                    }
                }
                frames.erase(pageToReplace);
            }
            frames.insert(pages[i]);
        }

        printFrames(frames);
    }
    return pageFaults;
}
int main()
{
    int numFrames;
    string pageString;
    cout << "Enter the number of frames: ";
    cin >> numFrames;
    cin.ignore();
    cout << "Enter the page reference string separated by spaces: ";
    getline(cin, pageString);
    stringstream ss(pageString);
    int pageNumber;
    vector<int> pages;
    while (ss >> pageNumber)
    {
        pages.push_back(pageNumber);
    }
    int fcfsFaults = fcfs(pages, numFrames);
    int lruFaults = lru(pages, numFrames);
    int optimalFaults = optimal(pages, numFrames);
    cout << "Total page faults using FCFS: " << fcfsFaults << endl;
    cout << "Total page faults using LRU: " << lruFaults << endl;
    cout << "Total page faults using Optimal: " << optimalFaults << endl;
    return 0;
}