/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <unordered_map>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template<class T>
class Vertex;

template <class T>
class Vertex {
private:
	T info;
	vector<Edge<T>> adj; //arestas que saem desse vertice
	bool visited;
	bool processing;
	int indegree;
	int dist;
public:

	Vertex(T in);
	friend class Graph<T>;

	void addEdge(unsigned int id, Vertex<T> *dest, double w, unsigned int road_id, unsigned int capacity);
	Edge<T>* removeEdgeTo(Vertex<T> *d);

	T getInfo() const;
	void setInfo(T info);

	bool IsVisited();
	int getDist() const;
	int getIndegree() const;
	void GetAdjacentEdges(vector<Edge<T>> &adj);
	vector<Edge<T>>& GetAdjacentEdgesReference();
	void IncrementIndegree();
	bool operator==(const Vertex<T> &v2);
	Vertex* path;
};

template<class T>
inline bool Vertex<T>::operator==(const Vertex<T>& vertex2)
{
	return this->getInfo().GetId() == vertex2.getInfo().GetId();
}

template <class T>
struct vertex_greater_than {
    bool operator()(Vertex<T> * a, Vertex<T> * b) const {
        return a->getDist() > b->getDist();
    }
};


template <class T>
Edge<T>* Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	d->indegree--; //adicionado do exercicio 5
	typename vector<Edge<T>>::iterator it= adj.begin();
	typename vector<Edge<T>>::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) 
		{
			Edge<T> *edge_removed = new Edge<T>;
			*edge_removed = *it;
			adj.erase(it);
			return edge_removed;
		}
		else it++;
	}
	return NULL;
}

//atualizado pelo exerc�cio 5
template <class T>
Vertex<T>::Vertex(T in): info(in), visited(false), processing(false), indegree(0), dist(0) {
	path = NULL;
}


template <class T>
void Vertex<T>::addEdge(unsigned int id, Vertex<T> *dest, double w, unsigned int road_id, unsigned int capacity) {
	Edge<T> edgeD(id, dest, w, road_id, capacity);
	adj.push_back(edgeD);
}


template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template<class T>
inline bool Vertex<T>::IsVisited()
{
	return visited;
}

template <class T>
int Vertex<T>::getDist() const {
	return this->dist;
}


template <class T>
void Vertex<T>::setInfo(T info) {
	this->info = info;
}

template <class T>
int Vertex<T>::getIndegree() const {
	return this->indegree;
}

template<class T>
inline void Vertex<T>::GetAdjacentEdges(vector<Edge<T>> &adj)
{
	adj = this->adj;
}

template<class T>
inline vector<Edge<T>>& Vertex<T>::GetAdjacentEdgesReference()
{
	return adj;
}

template<class T>
inline void Vertex<T>::IncrementIndegree()
{
	indegree++;
}




/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template <class T>
class Edge {
	unsigned int id;
	Vertex<T> *dest;
	int road_id;
	double weight;
	unsigned int capacity;
	unsigned int fill;
public:
	Edge();
	Edge(unsigned int id, Vertex<T> *d, double w, int r_id, unsigned int capacity);
	unsigned int GetID() const;
	Vertex<T> GetDest();
	Vertex<T>* GetDestPointer();
	unsigned long long int GetRoadId() const;
	double GetWeight() const;
	unsigned int GetCapacity() const;
	unsigned int GetFill() const;
	void IncrementFill();
	void IncrementWeight(double weight);
	bool IsFull() const;

	friend class Graph<T>;
	friend class Vertex<T>;
};

template<class T>
inline Edge<T>::Edge()
{
}

template <class T>
Edge<T>::Edge(unsigned int id, Vertex<T> *d, double w, int r_id, unsigned int capacity): dest(d), road_id(r_id), weight(w), capacity(capacity), id(id){}

template<class T>
inline unsigned int Edge<T>::GetID() const
{
	return id;
}

template<class T>
inline Vertex<T> Edge<T>::GetDest()
{
	return *dest;
}

template<class T>
inline Vertex<T>* Edge<T>::GetDestPointer()
{
	return dest;
}

template<class T>
inline unsigned long long int Edge<T>::GetRoadId() const
{
	return road_id;
}

template<class T>
inline double Edge<T>::GetWeight() const
{
	return weight;
}

template<class T>
inline unsigned int Edge<T>::GetCapacity() const
{
	return capacity;
}

template<class T>
inline unsigned int Edge<T>::GetFill() const
{
	return fill;
}

template<class T>
inline void Edge<T>::IncrementFill()
{
	fill++;
}

template<class T>
inline void Edge<T>::IncrementWeight(double weight)
{
	this->weight += weight;
}

template<class T>
inline bool Edge<T>::IsFull() const
{
	return fill >= capacity;
}





/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<Vertex<T>*> &res) const;

	//exercicio 5
	int numCycles;
	
	void dfsVisit();
	void getPathTo(Vertex<T> *origin, list<T> &res);

public:
	void dfsVisit(Vertex<T> *v);
	void dfsUtil(Vertex<T> *v, vector<Vertex<T>*> &tree, unordered_map<Vertex<T>*, Vertex<T>*> &correspondent_not_reversed);
	Vertex<T>* Graph<T>::addVertex(const T &in);
	bool addEdge(unsigned int id, const T &sourc, const T &dest, double w, unsigned int road_id, unsigned int capacity);
	bool removeVertex(const T &in);
	Edge<T>* removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;

	//exercicio 5
	Vertex<T>* getVertex(const T &v) const;
	void resetIndegrees();
	vector<Vertex<T>*> getSources() const;
	int getNumCycles();
	vector<T> topologicalOrder();
	vector<T> getPath(const T &origin, const T &dest);
	void unweightedShortestPath(const T &v);
	bool isDAG();

	//tp6
	void bellmanFordShortestPath(const T &s);
	void dijkstraShortestPath(const T &src, const T &dest);
	vector<vector<Vertex<T>*>> StronglyConnectedComponents(Graph<T>& reversed_graph);

	void dfs_r(Vertex<T> *v, vector<Vertex<T>*> &res) const;
};


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
int Graph<T>::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}

template <class T>
bool Graph<T>::isDAG() {
	return (getNumCycles() == 0);
}

template<class T>
inline void Graph<T>::bellmanFordShortestPath(const T & s)
{
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T>* > q;
	q.push(v);

	while (!q.empty()) {
		v = q.front(); q.pop();
		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			if (w->dist > v->dist + v->adj[i].weight) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				q.push(w);
			}
		}
	}
}

template<class T>
inline void Graph<T>::dijkstraShortestPath(const T &src, const T &dest)
{
	bool heap_altered = false;

	for (unsigned int i = 0; i < vertexSet.size(); i++) 
	{
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->processing = false;
	}

	Vertex<T>* v = getVertex(src);
	v->dist = 0;

	vector< Vertex<T>* > pq;
	pq.push_back(v);

	make_heap(pq.begin(), pq.end());

	while (!pq.empty()) 
	{
		if(heap_altered)
			make_heap(pq.begin(), pq.end(), vertex_greater_than<T>());

		v = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();

		//otimiza��o
		if (*v == dest)
			return;

		for (unsigned int i = 0; i < v->adj.size(); i++) 
		{
			Vertex<T>* w = v->adj[i].dest;

			if (v->dist + v->adj[i].weight < w->dist) 
			{

				w->dist = v->dist + v->adj[i].weight;
				w->path = v;

				//se j� estiver na lista, apenas a actualiza
				if (!w->processing)
				{
					w->processing = true;
					pq.push_back(w);
				}

				heap_altered = true;
			}
		}
	}
}

template<class T>
inline void Graph<T>::dfsUtil(Vertex<T> *v, vector<Vertex<T>*> &tree, unordered_map<Vertex<T>*, Vertex<T>*> &correspondent_not_reversed)
{
	// Mark the current node as visited and save it to the tree
	v->visited = true;
	tree.push_back(v);

	// Recur for all the vertices adjacent to this vertex
	vector<Edge<T>> adjacent_edges;
	for (unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if (vertexSet[i]->getInfo() == v->getInfo())
		{
			adjacent_edges = vertexSet[i]->adj;
			break;
		}
	}
	unsigned int adjacent_edges_size = adjacent_edges.size();
	for (unsigned int i = 0; i < adjacent_edges_size; i++)
	{
		Vertex<T> *destination = adjacent_edges[i].GetDestPointer();
		if (correspondent_not_reversed[destination]->visited == false)
				dfsUtil(correspondent_not_reversed[destination], tree, correspondent_not_reversed);
	}
}

template<class T>
inline vector<vector<Vertex<T>*>> Graph<T>::StronglyConnectedComponents(Graph<T> &reversed_graph)
{
	vector<vector<Vertex<T>*>> forest;
	vector<Vertex<T>*> first_dfs_result;
	unsigned int num_vertex = getNumVertex();
	// Mark all the vertices as not visited (For first DFS)
	for (unsigned int i = 0; i < num_vertex; i++)
		vertexSet[i]->visited = false;

	// Fill vertices in vector according to their finishing times
	for (unsigned int i = 0; i < num_vertex; i++)
		if (vertexSet[i]->visited == false)
			dfs_r(vertexSet[i], first_dfs_result);

	// Mark all the vertices as not visited (For second DFS)
	for (unsigned int i = 0; i < num_vertex; i++)
		vertexSet[i]->visited = false;

	unordered_map<Vertex<T>*, Vertex<T>*> correspondent_not_reversed;
	for (unsigned int i = 0; i < num_vertex; i++)
		for (unsigned int j = 0; j < num_vertex; j++)
		{
			if(reversed_graph.vertexSet[j]->getInfo() == vertexSet[i]->getInfo())
				correspondent_not_reversed[reversed_graph.vertexSet[j]] = vertexSet[i];
		}

	// Now process all vertices in reversed order 
	for (int i = first_dfs_result.size() - 1; i >= 0; i--)
	{
		// Save Strongly connected component of the popped vertex
		if (first_dfs_result[i]->visited == false)
		{
			vector<Vertex<T>*> tree;
			reversed_graph.dfsUtil(first_dfs_result[i], tree, correspondent_not_reversed);
			forest.push_back(tree);
		}
	}
	return forest;
}

template <class T>
Vertex<T>* Graph<T>::addVertex(const T &in) {
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return v1;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v= *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}

			typename vector<Edge<T> >::iterator itAdj= v->adj.begin();
			typename vector<Edge<T> >::iterator itAdje= v->adj.end();
			for (; itAdj!=itAdje; itAdj++) {
				itAdj->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}

template <class T>
bool Graph<T>::addEdge(unsigned int id, const T &sourc, const T &dest, double w, unsigned int road_id, unsigned int capacity) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS = nullptr, *vD = nullptr;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ vS=*it; found++;}
		if ( (*it)->info == dest )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vD->indegree++;
	vS->addEdge(id, vD, w, road_id, capacity);

	return true;
}

template <class T>
Edge<T>* Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS = NULL, *vD = NULL;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ vS=*it; found++;}
		if ( (*it)->info == dest )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2)
		return NULL;

	vD->indegree--;

	return vS->removeEdgeTo(vD);
}




template <class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<T> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
	    if ( (*it)->visited==false )
	    	dfs(*it,res);
	return res;
}

template <class T>
void Graph<T>::dfs_r(Vertex<T> *v,vector<Vertex<T>*> &res) const {
	v->visited = true;

	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
	    if ( it->dest->visited == false)
		{
	    	dfs_r(it->dest, res);
	    }

	res.push_back(v);
}

template <class T>
void Graph<T>::dfs(Vertex<T> *v, vector<Vertex<T>*> &res) const {
	v->visited = true;
	res.push_back(v);
	typename vector<Edge<T> >::iterator it = (v->adj).begin();
	typename vector<Edge<T> >::iterator ite = (v->adj).end();
	for (; it != ite; it++)
		if (it->dest->visited == false) {
			dfs(it->dest, res);
		}
}

template <class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren=0;
	inf =v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l=level.front();
		level.pop(); l++;
		int nChildren=0;
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren=nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}


template <class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v) return vertexSet[i];
	return NULL;
}

template<class T>
void Graph<T>::resetIndegrees() {
	//colocar todos os indegree em 0;
	for(unsigned int i = 0; i < vertexSet.size(); i++) vertexSet[i]->indegree = 0;

	//actualizar os indegree
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		//percorrer o vector de Edges, e actualizar indegree
		for(unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
			vertexSet[i]->adj[j].dest->indegree++;
		}
	}
}


template<class T>
vector<Vertex<T>*> Graph<T>::getSources() const {
	vector< Vertex<T>* > buffer;
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		if( vertexSet[i]->indegree == 0 ) buffer.push_back( vertexSet[i] );
	}
	return buffer;
}


template <class T>
void Graph<T>::dfsVisit() {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	it=vertexSet.begin();
	for (; it !=ite; it++)
	    if ( (*it)->visited==false )
	    	dfsVisit(*it);
}

template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v) {
	v->processing = true;
	v->visited = true;
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++) {
		if ( it->dest->processing == true) numCycles++;
	    if ( it->dest->visited == false ){
	    	dfsVisit(it->dest);
	    }
	}
	v->processing = false;
}

template<class T>
vector<T> Graph<T>::topologicalOrder() {
	//vector com o resultado da ordenacao
	vector<T> res;

	//verificar se � um DAG
	if( getNumCycles() > 0 ) {
		cout << "Ordenacao Impossivel!" << endl;
		return res;
	}

	//garantir que os "indegree" estao inicializados corretamente
	this->resetIndegrees();

	queue<Vertex<T>*> q;

	vector<Vertex<T>*> sources = getSources();
	while( !sources.empty() ) {
		q.push( sources.back() );
		sources.pop_back();
	}

	//processar fontes
	while( !q.empty() ) {
		Vertex<T>* v = q.front();
		q.pop();

		res.push_back(v->info);

		for(unsigned int i = 0; i < v->adj.size(); i++) {
			v->adj[i].dest->indegree--;
			if( v->adj[i].dest->indegree == 0) q.push( v->adj[i].dest );
		}
	}

	//testar se o procedimento foi bem sucedido
	if ( res.size() != vertexSet.size() ) {
		while( !res.empty() ) res.pop_back();
	}

	//garantir que os "indegree" ficam atualizados ao final
	this->resetIndegrees();

	return res;
}



template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest){

	list<T> buffer;
	Vertex<T>* v = getVertex(dest);

	buffer.push_front(v->info);
	while ( v->path != NULL &&  v->path->info != origin) {
		v = v->path;
		buffer.push_front(v->info);
	}
	if( v->path != NULL )
		buffer.push_front(v->path->info);


	vector<T> res;
	while( !buffer.empty() ) {
		res.push_back( buffer.front() );
		buffer.pop_front();
	}
	return res;
}


template<class T>
void Graph<T>::unweightedShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T>* > q;
	q.push(v);

	while( !q.empty() ) {
		v = q.front(); q.pop();
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			if( w->dist == INT_INFINITY ) {
				w->dist = v->dist + 1;
				w->path = v;
				q.push(w);
			}
		}
	}
}


#endif /* GRAPH_H_ */
