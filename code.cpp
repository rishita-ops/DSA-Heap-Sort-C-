#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter element " << i + 1 << ": ";
        cin >> arr[i];
    }

    for(int i=n/2-1;i>=0;i--)
    {
        int root=i;
        while(root*2+1<n)
        {
            int child=root*2+1;
            if(child+1<n && arr[child]<arr[child+1])
                child++;
            if(arr[root]<arr[child])
            {
                swap(arr[root],arr[child]);
                root=child;
            }
            else
                break;
        }
    }

    for(int i=n-1;i>=0;i--)
    {
        swap(arr[0],arr[i]);
        int root=0;
        while(root*2+1<i)
        {
            int child=root*2+1;
            if(child+1<i && arr[child]<arr[child+1])
                child++;
            if(arr[root]<arr[child])
            {
                swap(arr[root],arr[child]);
                root=child;
            }
            else
                break;
        }
    }

    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }

    return 0;
}