# include <iostream>
# include <vector>
# include <float.h>
# include <queue>
# include <stack>
# include <cmath>
# include <fstream>
# include <string>
# include <sstream>

using namespace::std;
struct Edge
{
    int start;
    int destination;
    double weight;
}; // 代表边的类

class EdgeWeightedDigraph{
    private:
        vector<vector<Edge*>> adj; 
    public:
        int V; // number of vertices
        int E; // number of edges
        EdgeWeightedDigraph(int V);
        void addEdge(Edge* e);
        vector<Edge*> getadj(int v);
}; // 带权有向图的类

EdgeWeightedDigraph::EdgeWeightedDigraph(int V){
    this->V = V;
    this->E = 0;
    this->adj.resize(V);
    // cout << "build EdgeWeightedDigraph success" << endl;
}

void EdgeWeightedDigraph::addEdge(Edge* e){
    int start = e->start;
    int destination = e->destination;
    adj[start].push_back(e);
    E++;
} // 把边加入到图中

vector<Edge*> EdgeWeightedDigraph::getadj(int v){
    return adj[v];
}


class EdgeWeightedDirectedCycle{
    private:
        vector<bool> marked;
        vector<Edge*> edgeTo;
        vector<bool> onStack;
        stack<Edge*> cycle;
        void dfs(EdgeWeightedDigraph* G, int v);
    public:
        EdgeWeightedDirectedCycle(EdgeWeightedDigraph* G);
        stack<Edge*> getCycle();
}; // 在有向图中寻找环



EdgeWeightedDirectedCycle::EdgeWeightedDirectedCycle(EdgeWeightedDigraph* G){
    marked.resize(G->V);
    onStack.resize(G->V);
    edgeTo.resize(G->V);
    for(int i = 0;i<G->V;i++){
        if(!marked[i])dfs(G, i);
    }
}
void EdgeWeightedDirectedCycle::dfs(EdgeWeightedDigraph* G, int v){
    // cout << "now dfs is in " << v;
    onStack[v] = true;
    marked[v] = true;
    for(Edge* e:G->getadj(v)){
        int w = e->destination;
        // cout << endl;
        // cout << v << " has neighbor " << w;
        if(!cycle.empty())return;
        else if(!marked[w]){
            edgeTo[w] = e;
            dfs(G,w);
        }
        else if(onStack[w]){
            Edge* f = e;
            while(f->start!=w){
                cycle.push(f);
                f = edgeTo[f->start];
            }
            cycle.push(f);
            return;
        }
    }
    onStack[v] = false;
}


stack<Edge*> EdgeWeightedDirectedCycle::getCycle(){
    return cycle;
}


class BellmanFordSp{
    private:
        vector<double> distTo;
        vector<Edge*> edgeTo;
        vector<bool> onQueue;
        queue<int> q;
        int cost;
        stack<Edge*> cycle;
        void relax(EdgeWeightedDigraph* G, int v);
    public:
        BellmanFordSp(EdgeWeightedDigraph* G, int s);
        void findNegativeCycle();
        bool hasNegativeCycle();
        stack<Edge*> getNegativeCycle(); 

};


BellmanFordSp::BellmanFordSp(EdgeWeightedDigraph* G, int s){
    distTo.resize(G->V,DBL_MAX);
    edgeTo.resize(G->V);
    onQueue.resize(G->V);
    distTo[s] = 0;

    // BellmanFord algorithm
    q.push(s);
    onQueue[s] = true;
    while(!q.empty()&&cycle.empty()){
        int v = q.front();
        q.pop();
        onQueue[v] = false;
        relax(G,v);
    }
}


void BellmanFordSp::relax(EdgeWeightedDigraph* G, int v){
    // cout << endl; 
    // cout << "now relaxing " << v << endl;

    for(Edge* e:G->getadj(v)){
        int w = e->destination;
        // cout << v << "has neighbor " << w << " with edge weight " << e->weight << ". ";
        if(distTo[w] > distTo[v] + e->weight){
            distTo[w] = distTo[v] + e->weight;
            edgeTo[w] = e;
            // cout << "updated " << v << " -> " << w << " to " << distTo[w] << endl;
            if(!onQueue[w]){q.push(w);onQueue[w]=true;}
        }
        if(++cost%(G->V)==0){
            findNegativeCycle();
            if(!cycle.empty()) return;
        }
    }
}

void BellmanFordSp::findNegativeCycle(){
    int V = edgeTo.size();
    EdgeWeightedDigraph* spt = new EdgeWeightedDigraph(V);
    for(int i = 0;i < V;i++){
        Edge* e = edgeTo[i];
        if(e==nullptr)continue;
        // cout << " edgeTo " << i << " is " << e->start << " -> " << e->destination;
        spt->addEdge(e);
    }
    EdgeWeightedDirectedCycle* finder = new EdgeWeightedDirectedCycle(spt);
    cycle = finder->getCycle();
}

bool BellmanFordSp::hasNegativeCycle(){
    return !cycle.empty();
}

stack<Edge*> BellmanFordSp::getNegativeCycle(){
    return cycle;
}


int main(){
    vector<string> currency;
    string filename;
    cin >> filename;
    ifstream infile(filename);
    string line;
    string rate;
    getline(infile,line);
    int V = stoi(line);
    vector<vector<double>> rates(V); // 输入的汇率数组
    EdgeWeightedDigraph* G = new EdgeWeightedDigraph(V);
    for(int i = 0; i < V; i++){
        getline(infile,line);
        istringstream iss(line);
        for(int j = 0;j<=V;j++){
            iss >> rate;
            if(j==0){currency.push_back(rate);continue;} // pass USD etc.
            rates[i].push_back(atof(rate.c_str()));
        }
    }

    // test rates 
    for(int i = 0; i < V; i++){
        for(int j = 0;j<V;j++){
            cout << rates[i][j] << " ";
            Edge* e = new Edge();
            e->start = i;
            e->destination = j;
            e->weight = -log(rates[i][j]);
            G->addEdge(e);
        }
        // cout << endl;
    }
    cout << "rates build success";
    
    BellmanFordSp* spt = new BellmanFordSp(G,0);
    if(spt->hasNegativeCycle()){
        stack<Edge*> cycle = spt->getNegativeCycle();
        while(!cycle.empty()){
            Edge* e = cycle.top();
            cycle.pop();
            cout << currency[e->start] << "  ->  " << currency[e->destination] << "  ";
        }
    }
}


