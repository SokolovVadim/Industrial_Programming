/* C++ Program for Binry Search Algorithm */
#include <bits/stdc++.h> 
using namespace std; 
# define BYTES_TO_WRITE 256  
  
void badHeuristic( string str, int size,  
                        int badchar[BYTES_TO_WRITE])  
{  
    int i;  
  
    for (i = 0; i < BYTES_TO_WRITE; i++)  
        badchar[i] = -1;  
  
    for (i = 0; i < size; i++)  
        badchar[(int) str[i]] = i;  
}  

void search(int a, int b)  
{  
    stringstream ss;
    ss << a;
    string txt = ss.str();
    stringstream ss1;
    ss1 << b;
    string pat = ss1.str();



    int m = pat.size();  
    int n = txt.size();  
  
    int bad[BYTES_TO_WRITE];  
    badHeuristic(pat, m, bad);  
  
    int s = 0;
    while(s <= (n - m))  
    {  
        int j = m - 1;  
        while(j >= 0 && pat[j] == txt[s + j])  
            j--;  
        if (j < 0)  
        {  
            cout << "Binary search: position = " <<  s << endl;  
            s += (s + m < n)? m-bad[txt[s + m]] : 1;  
        }  
  
        else
            s += max(1, j - bad[txt[s + j]]);  
    }  
}  
int main()  
{  
    int* array = new int[100    ];
    for(int i(0); i < 100; ++i)
        array[i] = i;
    int a = 1123145;
    int b = 3;
    search(a, array[3]);  
    return 0;  
}  
