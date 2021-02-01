#include <bits/stdc++.h>

using namespace std;

typedef long long lli;
const lli inf = 1e18;


lli to_power(lli a, lli e){
  lli ans = 1LL;
  while(e){
    if(e&1){
      ans = ans * a;
    }
    a = a * a;
    e>=1LL;
  }
  return ans;
}

lli gcd(lli a, lli b){
  a = abs(a);
  b = abs(b);
  while(b){
    lli r = a%b;
    a = b;
    b = r;
  }
  return a;
}
lli lcm(lli a, lli b){
  return a * (b / gcd(a, b));
}

//  Find max k | a^k | n!
lli find_maxk(lli a,lli n){
  lli ans = 0, base = a;
  while(base<=n){
    ans += (n/base);
    base = (base*a);
  }
  return ans;
}


// <= 10^7
vector<int> compute_sieve(int n){
  vector<int> sieve(n + 1,0);
  for(int i=4;i<=n;i+=2)
    sieve[i] = 2;
  for(int i=3;i*i<=n;i+=2){
    if(!sieve[i]){
      for(int j = i*i;j<=n;j+=i*2){
        if(!sieve[j])
          sieve[j] = i;
      }
    }
  }
  return sieve;
}



// PI(m) = M/(ln(M)− 1)
vector<int> compute_primes(vector<int> &sieve){
  vector<int> primes;
  primes.push_back(2);
  for(int i=3;i<sieve.size();i+=2){
    if(!sieve[i])
      primes.push_back(i);
  }
  return primes;
}

// <= 10^14
vector<pair<lli,lli>> prime_factors(lli number,vector<int> &sieve, vector<int> &primes){
  lli N = 10000000;
  vector<pair<lli,lli>> F;
  for(int i=0;i<primes.size() && number > N ;i++){
    lli pi = primes[i];
    if(pi * pi > number)
      break;
    int f = 0;
    while(number%pi == 0){
      f++;
      number /= pi;
    }
    if(f){
      F.push_back({pi,f});
    }
  }

  if(number > N){
    F.push_back({number,1});
    return F;
  }

  while(sieve[number]){
    lli pi = sieve[number];
    int f = 0;
    while(number%pi == 0){
      f++;
      number /= pi;
    }
    F.push_back({pi,f});
  }

  if(number != 1)
    F.push_back({number,1});
  return F;
}


void compute_divisors(vector<pair<lli,lli>> &factors,int index,
  lli current_number,vector<lli> &divisors){
  if(index == factors.size()){
    divisors.push_back(current_number);
    return;
  }
  for(int i=0;i<=factors[index].second;i++){
    compute_divisors(factors,index+1,current_number,divisors);
    current_number *= factors[index].first;
  }
}


lli number_of_divisors( vector<pair<lli,int>> &prime_factors){
  lli ans = 1LL;
  for(auto &x: prime_factors){
    ans = (ans*(1LL + x.second));
  }
  return ans;
}


lli sum_of_divisors(vector<pair<lli,int>> &prime_factors){
  lli ans = 1LL;
  for(auto &x: prime_factors){
    lli temp = to_power(x.first,x.second+1) - 1LL;
    temp /= (x.first - 1LL);
    ans = (ans * temp);
  }
  return ans;
}



lli phi(vector<pair<lli,int>> &prime_factors){
  lli ans = 1LL;
  for(auto &x: prime_factors){
    ans = ans * to_power(x.first,x.second-1LL);
    ans = ans * (x.first-1LL);
  }
  return ans;
}

int main(){
  vector<int> sieve = compute_sieve(10000000);
  vector<int> primes = compute_primes(sieve);

  lli aux;
  while(cin >> aux){
    vector<pair<lli,lli>> F = prime_factors(aux,sieve,primes);
    vector<lli> divs;
    compute_divisors(F,0,1,divs);
    for(auto &di:divs)
      cout << di << " ";
    cout << "\n";
  }
  return 0;
}
