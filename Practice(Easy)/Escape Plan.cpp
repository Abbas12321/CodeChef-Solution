#include <bits/stdc++.h>
using namespace std ;

#define  int        long long
#define  mod        1000000007
#define  modd       998244353
#define  inf        INT32_MAX
#define  INF        9e18
#define  ff         first 
#define  ss         second
#define  pb         push_back
#define  nl         '\n' 
#define  sz(s)      (int)((s).size())
#define  all(x)     (x).begin(),(x).end()

template <class T1, class T2> static inline void umin ( T1 &x , T2 y ) { if ( y < x ) x = y ; }
template <class T1, class T2> static inline void umax ( T1 &x , T2 y ) { if ( x < y ) x = y ; }

typedef pair   <int,int>       pii ;
typedef vector <int>           vi ;
typedef vector <vector<int>>   vvi ;
typedef vector <pair<int,int>> vpi ;
typedef map    <int,int>       mii ;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define  pd(ar,n) cerr << #ar << " = [ " ; for ( int i = 0 ; i < n ; i++ ) { cerr << ar[i] << " " ; } cerr << "] " << endl ;
#define  pdd(ar,n,m) cerr << #ar << endl ; for ( int i = 0 ; i < n ; i++ ) { { cerr << " [ " ; for ( int j = 0 ; j < m ; j++ ) { cerr << ar[i][j] << " " ; } ; cerr << "]" << endl ; } } ;

#ifndef ONLINE_JUDGE
    #define deb(x) cerr << #x << " = " ; print(x) ; cerr << endl ;
#else
    #define  deb(x...)
#endif

template <class T> void print ( T t ) { cerr << t ; }
template <class T1, class T2> void print ( pair <T1,T2> p ) { cerr << "{ " ; print(p.first) ; cerr <<", " ; print(p.second) ; cerr << " }" ; } ;
template <class T> void print ( vector <T> v ) { cerr <<  "[ " ; for ( T i : v ) { print(i) ; cerr << " " ;} cerr << "]" ; } ;
template <class T> void print ( set <T> s ) { cerr << "[ " ; for ( T i : s ) { print(i) ; cerr << " " ; } cerr  << "]" ; } ;
template <class T> void print ( multiset <T> ms ) { cerr << "[ " ; for ( T i : ms ) { print(i) ; cerr << " " ; } cerr  << "]" ; } ;
template <class T1, class T2> void print ( map <T1,T2> m ) { cerr << "[ " ; for ( auto i : m ) { print(i) ; cerr << " " ; } cerr << "]" ; }

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

const int N = 1e6+10 ;
int dp[N];
vi graph[N] ;
vi value(N,0) , leaves(N,0) ;

void dfs ( int node , int par ) {
    int others = 0 ;
    bool leaf = 1 ; 
    for ( auto i : graph[node] ) {
        if ( i != par ) {
            leaf = 0 ;
            dfs(i,node) ;
            leaves[node] += leaves[i] ;
            others += dp[i] ;
        }
    }
    if ( leaf ) {
        if ( value[node] != 0 ) dp[node] = value[node] ;
        else dp[node] = 1e14 ;
        leaves[node] = 1 ;
    } else {
        if ( value[node] == 0 ) dp[node] = others ;
        else dp[node] = min ( value[node] * leaves[node] , others ) ;
    }
}

void Solve () {
    int n = 0 ;
    cin >> n ;

    for ( int i = 1 ; i <= n ; i++ ) {
        dp[i] = value[i] = leaves[i] = 0 ;
        graph[i].clear() ;
    }

    for ( int i = 0 ; i < n-1 ; i++ ) {
        int u = 0 , v = 0 ;
        cin >> u >> v ;
        graph[u].pb(v) ;
        graph[v].pb(u) ;
    }

    for ( int i = 1 ; i <= n ; i++ ) cin >> value[i] ;
    

    dfs(1,1) ;
    cout << dp[1] << nl ;
}

signed main () {
    ios_base :: sync_with_stdio (0) ;
    cin.tie(0) ;
    cout.tie(0) ;
    int TestCases = 1 ;
    cin >> TestCases ;
    for ( int test = 1 ; test <= TestCases ; test++ ) {
        // cout << "Case #" << test << ": " ;
        Solve() ;
    }
    return 0 ;
}
