#include <bits/stdc++.h>
using namespace std;

typedef long long lli;
const lli inf = 1e18;

class SegmentTree{
public:
  vector<lli> lazy,st;
  int n;
  SegmentTree(vector<lli> &a){
    n = a.size();
    st.assign(4*n,0);
    lazy.assign(4*n,0);
    construct_st(a,0,n-1,0);
  }

  SegmentTree(int n){
    this->n = n;
    st.assign(4*n,0);
    lazy.assign(4*n,0);
  }

  void update(int s,int e,lli val){
    update(s,e,val,0,n-1,0);
  }

  lli sum(int s,int e){
    return sum(s,e,0,n-1,0);
  }

private:
  void construct_st(vector<lli> &a,int l,int r,int i){
    if(l == r){
      st[i] = a[l];
      return;
    }
    int mid = (l+r)>>1;
    construct_st(a,l,mid,i*2+1);
    construct_st(a,mid+1,r,i*2+2);
    st[i] = st[i*2+1] + st[i*2+2];
  }

  void update(int s,int e, lli val,int l,int r,int i){
    if(lazy[i]){
      st[i] += (r-l+1) * lazy[i];
      if(l != r){
        lazy[i*2+1] += lazy[i];
        lazy[i*2+2] += lazy[i];
      }
      lazy[i] = 0;
    }
    if(e<l || r<s)
      return;
    if(s<=l && r<=e){
      st[i] += (r-l + 1) * val;
      if(l != r){
        lazy[i*2+1] += val;
        lazy[i*2+2] += val;
      }
      return;
    }
    int mid = (l + r) >> 1;
    update(s,e,val,l,mid,i*2+1);
    update(s,e,val,mid+1,r,i*2+2);
    st[i] = st[i*2+1] + st[i*2+2];
  }

  lli sum(int s,int e,int l,int r,int i){
    if(lazy[i]){
      st[i] += (r-l+1) * lazy[i];
      if(l != r){
        lazy[i*2+1] += lazy[i];
        lazy[i*2+2] += lazy[i];
      }
      lazy[i] = 0;
    }
    if(e<l || r<s)
      return 0;

    if(s<=l && r<=e)
      return st[i];

    int mid = (l + r) >> 1;
    lli L = sum(s,e,l,mid,i*2+1);
    lli R = sum(s,e,mid + 1,r,i*2+2);
    return L + R;
  }
};


int main(){
  cin.sync_with_stdio(0);
  cin.tie(0);
  return 0;
}
