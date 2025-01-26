#include <bits/stdc++.h>
using namespace std;
int a[100005],tree[400005];
vector<int> v[100005];
int cnt(int l,int r,int c)
{
    return upper_bound(v[c].begin(),v[c].end(),r)-lower_bound(v[c].begin(),v[c].end(),l);
}
void build(int node,int st,int en)
{
    if (st==en)
    tree[node]=a[st];
    else
    {
        int mid=(st+en)/2;
        build(2*node,st,mid);
        build(2*node+1,mid+1,en);
        tree[node]=(cnt(st,en,tree[2*node])>cnt(st,en,tree[2*node+1])? tree[2*node]:tree[2*node+1]);
    }
}
int query(int node,int st,int en,int l,int r)
{
    if (en<l || st>r || r<l)
    return 0;
    if (l<=st && en<=r)
    return cnt(l,r,tree[node]);
    int mid=(st+en)/2;
    return max(query(2*node,st,mid,l,r),query(2*node+1,mid+1,en,l,r));
}

int query_number(int node,int st,int en,int l,int r)
{
    if (en<l || st>r || r<l)
    return 0;
    if (l<=st && en<=r)
    return tree[node];
    int mid=(st+en)/2;
    return query(2*node,st,mid,l,r) > query(2*node+1,mid+1,en,l,r) ? tree[2*node] : tree[2*node+1];
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        v[a[i]].push_back(i);
    }
    build(1,1,n);
    while (q--)
    {
        int l,r;
        scanf("%d %d",&l,&r);
        int result = (query(1,1,n,l,r)*2 > (r-l+1))?query_number(1,1,n,l,r):0;
        printf("%d\n",result);
    }
}