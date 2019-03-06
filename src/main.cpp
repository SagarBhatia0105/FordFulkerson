#include<iostream>
#include<fstream>
#include<queue>
#define V 6
#define inf 1000
#define Max 10000
using namespace std;

//0 for white color
//1 for grey color
//2 for black color
class Vertex{

  private:
    int parent;
    int dis;
    int color;
  public:
    void setColor(int c){
      color = c;
    }

    void setDistance(int d){
      dis = d;
    }

    void setParent(int p){
      parent = p;
    }

    int getColor(){
      return color;
    }

    int getDistance(){
      return dis;
    }

    int getParent(){
      return parent;
    }

};

Vertex *v1[V];

void printBFS(int **adj, int s, int l) {

  if (s == l)
    cout<<s<<" ";
  else if (v1[l]->getParent() == -1) {
    cout<<"No path exists from "<<s<<" to "<<l<<endl;
  }
  else {
    printBFS(adj, s, v1[l]->getParent());
    cout<<l<<" ";
  }
}

/*BFS traversal of the graph*/
bool BFS(int **adj, int s, int t){

  //cout<<"In BFS";
  Vertex* v[V];

  for(int i=0; i<V; i++){
    v[i] = new Vertex();
  }

  for(int i=0; i<V; i++){
    v1[i] = new Vertex();
  }

  queue <int> Q;
  int u;

  //initializing the vertex properties
  for(int i = 1; i<V; i++){

    //initializing the first vertex
    if(i == 0){
      v[0]->setColor(1);
      v[0]->setDistance(0);
      v[0]->setParent(-1);
    }
    else{
    v[i]->setColor(0);
    v[i]->setDistance(inf);
    v[i]->setParent(-1);
    }
  }

  //Doing the traversal
  Q.push(s);
  while(!(Q.empty())){
    u = Q.front();
    Q.pop();
    for(int i = 0; i<V; i++){

      if(adj[u][i] != 0 && v[i]->getColor() == 0){
        v[i]->setColor(1);
        v[i]->setDistance(v[u]->getDistance() + 1);
        v[i]->setParent(u);
        Q.push(i);
      }
    }
    v[u]->setColor(2);
  }

  for(int i=0; i<V; i++){
    v1[i] = v[i];
  }

  //cout<<"The Flow is "<<endl;
  //printBFS(adj, s, t);

  //if the last node is visited in each augmenting path
  if(v1[t]->getColor() == 2)
    return true;
  else
    return false;
}

int FordFul(int **adj, int s, int t){
  int **radj; //residual graph matrix
  int maxFlow = 0;
  int pathFlow;
  int u;
  int count = 0;

  radj = new int*[V];

  for (int j=0; j<V; j++){
    radj[j] = new int[V];
  }

  for(int i=0; i<V; i++){
    for(int j=0; j<V; j++)
      radj[i][j] = adj[i][j];
  }

  while(BFS(radj, s, t)){
    pathFlow = Max;

    for(int v = t; v!=s; v = v1[v]->getParent()){
      u = v1[v]->getParent();
      pathFlow = min(pathFlow, radj[u][v]);
    }

    for(int v = t; v!=s; v = v1[v]->getParent()){
      u = v1[v]->getParent();

      radj[u][v] -=pathFlow;
      radj[v][u] += pathFlow;
    }

    /*count = count + 1;
    if(count == 2)
      break;*/
    maxFlow +=pathFlow;
  }

  return maxFlow;
}

int main(int argc, char const *argv[]) {
  /* code */
  fstream input(argv[1]);

  int **adj;
  int s = 0,e,v,w;
  int edges;
  adj = new int*[V];
  input>> edges;

  if(!input)
	{
		cout<<"Error in reading from input file"<<endl;
		return -1;
	}

  for (int j=0; j<V; j++){
    adj[j] = new int[V];
  }

  //set the value for all the edges to be zero initially
  for(int k = 0; k<V; k++){
    for(int l = 0; l<V; l++){
      adj[k][l] = 0;
    }
  }

  //enter the values in the adjacency matrix
  for(int m=0; m<edges; m++){
    input>>e;
    input>>v;
    input>>w;

    adj[e][v] = w;
    //adj[v][e] = w;
  }

  cout<<"The max flow is "<<FordFul(adj, s, V-1)<<endl;

  input.close();
  return 0;
}
