#include <bits/stdc++.h>
using namespace std;
struct node{
    int x;
    int y;
    node(int x = 0, int y = 0):x(x), y(y){}
    int operator+(const node& a){
        return abs(a.x - x) + abs(a.y - y);
    }
}solution[20] = {
    node(3,3), node(0,0), node(0,1), node(0,2), 
    node(0,3), node(1,0), node(1,1), node(1,2), 
    node(1,3), node(2,0), node(2,1), node(2,2), 
    node(2,3), node(3,0), node(3,1), node(3,2)
};
struct Node{
    int mx, my, totalDist, pa;
    Node(int mx = 0, int my = 0, int totalDist = 0, int pa = 0):mx(mx), my(my), totalDist(totalDist), pa(pa){}
};
const int dr[] = {-1, 0, 1,  0};
const int dc[] = { 0, 1, 0, -1};
const string path = "URDL";
int board[4] [4];
inline int heuristics( ){
    int dist = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            dist += board[i][j] == 0 ? 0 : solution[board[i][j]] + node(i, j);
        }
    }
    return dist;
}
bool inversion(int arr[]){
    int invCount = 0;
    for(int i = 0; i < 16 - 1; i++){
        for(int j = i + 1; j < 16; j++){
            invCount += arr[i] && arr[j] && arr[i] > arr[j];
        }
    }
    int k = -1;
    for(int i = 3; i >= 0 && k == -1; i--){
        for(int j = 3; j >= 0 && k == -1; j--){
            if(board[i] [j] == 0)
                k = 3 - i;
        }
    }
    if(k & 1)
        return !(invCount & 1);
    else
        return invCount & 1;
}
inline bool valid(int x, int y){
    return x >= 0 && x <= 3 && y >= 0 && y <= 3;
}
int ans;
string ansSt, st;
int backtrack(int x, int y, int prex, int prey, int depth){
    if(depth > ans) return ans;
    int mk = heuristics( );
    if(mk + depth > ans) return ans;
    if(mk == 0){
        ans = depth;
        if(ansSt.size() > st.size() || ansSt > st)
            ansSt = st;
        return ans;
    }
    vector<Node> ve;
    for(int i = 0; i < 4; i++){
        if(valid(x + dr[i], y + dc[i])){
            if(x + dr[i] == prex && y + dc[i] == prey) continue;
            swap(board[x] [y], board[x + dr[i]] [y + dc[i]]);
            int km = heuristics();
            if(km == 0){
                st.push_back(path[i]);
                ans = depth;
                if(ansSt.size() > st.size() || ansSt > st)
                    ansSt = st;
                st.pop_back( );    
                swap(board[x] [y], board[x + dr[i]] [y + dc[i]]);
                return ans;    
            }
            if(km + depth <= ans && !inversion(*board)){
                ve.push_back(Node(x + dr[i], y + dc[i], km + depth, i));
            }
            swap(board[x] [y], board[x + dr[i]] [y + dc[i]]);
        }
    }
    sort(ve.begin(), ve.end(), [&](const Node& a, const Node& b){
        return a.totalDist < b.totalDist;
    });
    int k = ans;
    for(auto m: ve){
        if(m.totalDist > ans) continue;
        swap(board[x] [y], board[m.mx] [m.my]);
        st.push_back(path[m.pa]);
        k = min(k, backtrack(m.mx, m.my, x, y, depth + 1));
        st.pop_back();
        swap(board[x] [y], board[m.mx] [m.my]);
    }
    return k;
}
int main( ){
    int x, y;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            scanf("%d", &board[i][j]);
            if(board[i][j] == 0){
                x = i;
                y = j;
            }
        }
    }
    ans = 36;
    ansSt = "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
    backtrack(x, y, x, y, 0);
    printf("Case %d: ", ca++);
    if(ans == 36)
        printf("This puzzle is not solvable.\n");
    else
        cout << ansSt << '\n';
    return 0;
}