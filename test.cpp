#include <bits/stdc++.h>

using namespace std;

int n, m, G[20][20], deg[20], p[8];

bool k5(int cur, int last, vector<vector<int>> &M, int v){
    if(cur == 5)
        return true;
    for(int i = last; i <= v; i++){
        bool ok = true;
        for(int j = 0; j < cur; j++){
            if(!M[i][p[j]]){
                ok = false;
                break;
            }
        }
        p[cur] = i;
        if(ok && k5(cur+1, i, M, v))
            return true;
    }
    return false;
}

bool k33(vector<vector<int>> &M, int v){
    for(int a1 = 1; a1 <= v; a1++)
    for(int b1 = 1; b1 <= v; b1++)if(M[a1][b1])
    for(int a2 = 1; a2 <= v; a2++)if(M[a2][b1]&&a2 != a1)
    for(int b2 = 1; b2 <= v; b2++)if(M[a1][b2]&&M[a2][b2]&&b2 != b1)
    for(int a3 = 1; a3 <= v; a3++)if(M[a3][b1]&&M[a3][b2]&&a3 != a1&&a3 != a2)
    for(int b3 = 1; b3 <= v; b3++)if(M[a1][b3]&&M[a2][b3]&&M[a3][b3]&&b3 != b1&&b3 != b2)
        return true;
    return false;
}

pair<int, int> red(vector<vector<int>> &M, int v, int e){
    vector<int> degr;
    for(int i = 0; i < v+1; i++){
        degr.push_back(0);
    }
    for(int i = 1; i <= v; i++){
            for(int j = 1; j <= v; j++){
                degr[i] += M[i][j];
            }
        }
    while(1){
        int j = 0;
        for(int i = 1; i <= v; i++){
            int k;
            if(degr[i] == 1){
                degr[i] = 0;
                for(j = 1; j <= v; j++){
                    if(M[i][j])
                        break;
                }
                M[i][j] = M[j][i] = 0;
                degr[j]--;
                e--;
            }
            else if(degr[i] == 2){
                degr[i] = 0;
                for(j = 1; j <= v; j++){
                    if(M[i][j])
                        break;
                }
                for(k = j + 1; k <= v; k++){
                    if(M[i][k])
                        break;
                }
                M[i][j] = M[j][i] = 0;
                M[i][k] = M[k][i] = 0;
                if(M[j][k]){
                	degr[j]--, degr[k]--;
				}
                M[j][k] = M[k][j] = 1;
                e--;
            }
        }
        if(j == 0)
            break;
    }
    for(int i = 1; i <= v; i++){
        if(degr[i] == 0)
            continue;
        for(int j = 1, k = 1; j <= v; j++){
            if(degr[j] != 0)
                M[i][k++] = M[i][j];
        }
    }
    int k = 0;
    for(int i = 1; i <= v; i++){
        if(degr[i] == 0)
            continue;
        if(i != ++k)
            M[k] = M[i];
    }
    v = k;
    for(int i = 1; i <= v; i++){
        M[i][i] = 0;
    }
    return make_pair(v, e);
}

bool kura(vector<vector<int>> &M, int v){
	for(int i = v; i >= 5; i--){
        vector<int> perm;
        for(int j = 0; j < v-i; j++){
            perm.push_back(0);
        }
        for(int j = 0; j < i; j++){
            perm.push_back(1);
        }
        do{
            vector<vector<int>> adj = M;
            for(int j = 0; j < v; j++){
                if(perm[j] == 0){
                    for(int k = 1; k <= v; k++){
                        adj[k][j+1] = adj[j+1][k] = 0;
                    }
                }
            }
            int e = 0;
            for(int j = 1; j <= v; j++){
                for(int k = j; k <= v; k++){
                    if(adj[j][k])
                        e++;
                }
            }
            if(e < 9)
                continue;
            pair<int, int> p = red(adj, v, e);
            if(p.first < 5||p.second < 9)
                continue;
            if(k5(0, 0, adj, p.first) || k33(adj, p.first))
                return false;
        }
        while(next_permutation(perm.begin(), perm.end()));
    }
    return true;
}

void redu1(){
    while(1){
        int j = 0;
        for(int i = 1; i <= n; i++){
            int k;
            if(deg[i] == 1){
                deg[i] = 0;
                for(j = 1; j <= n; j++){
                    if(G[i][j])
                        break;
                }
                G[i][j] = G[j][i] = 0;
                deg[j]--;
                m--;
            }
            else if(deg[i] == 2){
                deg[i] = 0;
                for(j = 1; j <= n; j++){
                    if(G[i][j])
                        break;
                }
                for(k = j + 1; k <= n; k++){
                    if(G[i][k])
                        break;
                }
                G[i][j] = G[j][i] = 0;
                G[i][k] = G[k][i] = 0;
                if(G[j][k]){
                	deg[j]--, deg[k]--;
				}
                G[j][k] = G[k][j] = 1;
                m--;
            }
        }
        if(j == 0)
            break;
    }
    for(int i = 1; i <= n; i++){
        if(deg[i] == 0)
            continue;
        for(int j = 1, k = 1; j <= n; j++){
            if(deg[j] != 0)
                G[i][k++] = G[i][j];
        }
    }
    int k = 0;
    for(int i = 1; i <= n; i++){
        if(deg[i] == 0)
            continue;
        if(i != ++k)
            memcpy(G[k], G[i], sizeof(G[0]));
    }
    n = k;
    for(int i = 1; i <= n; i++){
        G[i][i] = 0;
    }
}

int main(){
    int q;
    cin >> q;
    while(q--){
        cin >> n >> m;
        memset(G, 0, sizeof(G));
        memset(deg, 0, sizeof(deg));
        memset(p, 0, sizeof(p));
        for(int i = 0; i < m; i++){
            int x, y;
            cin >> x >> y;
            if(x != y)
                G[x][y] = G[y][x] = 1;
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                deg[i] += G[i][j];
            }
        }
        redu1();
        vector<vector<int>> reduced;
        
        for(int i = 0; i <= n; i++){
            vector<int> v;
            for(int j = 0; j <= n; j++){
                v.push_back(G[i][j]);
            }
            reduced.push_back(v);
        }
        
        kura(reduced, n);

        if(kura(reduced, n))
            cout << "Yes\n";
        else{
            cout << "No\n";
        }
    }
}
