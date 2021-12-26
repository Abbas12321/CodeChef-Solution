#include "bits/stdc++.h"

using namespace std;

typedef long double ld;
typedef long long ll;

#define sz(x) (int)(x).size()
#define f first
#define s second

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
template<typename T, typename U> bool ckmin(T &a, const U &b){ return b < a ? a = b, true : false; }
template<typename T, typename U> bool ckmax(T &a, const U &b){ return b > a ? a = b, true : false; }

int tt, n, q;
vector<int> par, ord, col;
vector<vector<int>> adj;
map<pair<int, int>, bool> opp; // is u, v opposite or not after all queries

void dfs(int v, int p){
    par[v] = p;
    for(auto i : adj[v]){
        if(i == p) continue;
        dfs(i, v);
    }
    ord.push_back(v);
}

void dfs2(int v, int c){
    col[v] = c;
    for(auto i : adj[v]){
        if(i == par[v]) continue;
        int u = min(v, i), x = max(v, i);
        if(opp[{u, x}]) dfs2(i, c ^ 1);
        else dfs2(i, c);
    }
}

inline int qry(int v){
    cout << v + 1 << endl;
    int ret; cin >> ret;
    return ret;
}

int main(){
    cin >> tt;
    while(tt--){
        par.clear(); ord.clear(); adj.clear(); opp.clear();
        col.clear();
        cin >> n >> q; adj.assign(n, vector<int>());
        for(int i = 0; i < n - 1; ++i){
            int u, v; cin >> u >> v; --u, --v;
            adj[v].push_back(u);
            adj[u].push_back(v);
        }
        int cur = qry(0); // number of different edges
        par.assign(n, -1);
        col.assign(n, -1);
        dfs(0, -1);
        vector<int> different(n, 0);
        // go in ord order and query
        for(auto i : ord){
            if(!i) break;
            int different_cnt = qry(i);// gives num different after swap
            // cout << different_cnt << ' ' << cur << ' ' << different[i] << '\n';
            if(different_cnt == cur + 1 + different[i]){ // introduced extra swap
                opp[{min(i, par[i]), max(i, par[i])}] = false; // different after all swaps
                different[par[i]] -= 1;
            }
            else{
                opp[{min(i, par[i]), max(i, par[i])}] = true; //same after all swaps
                different[par[i]] += 1;
            }
            cur = different_cnt;
            // for(auto x : different) cout << x << ' ';
            // cout << '\n';
        }
        for(auto i : adj[0]){
            int u = min(i, 0), v = max(i, 0);
            opp[{u, v}] = !opp[{u, v}];
        }
        // for(auto i: opp) cout << i.f.f << ' ' << i.f.s << ' ' << i.s << '\n';  
        dfs2(0, 0);
        int tot = 0;
        for(int i = 0; i < n; ++i){
            tot += col[i];
            // cout << col[i] << ' ';
        }
        // cout << '\n';
        if(tot <= n/2){
            for(int i = 0; i < n; ++i){
                if(col[i]) qry(i);
            }
        }
        else{
            for(int i = 0; i < n; ++i){
                if(!col[i]) qry(i);
            }            
        }
        cout << 0 << endl;
        int ver; cin >> ver;
        if(ver == -1) assert(false);
    }
    return 0;
}
