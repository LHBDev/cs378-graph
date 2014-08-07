// ----------------------
// projects/graph/Graph.h
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <deque>  // deque

// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef int vertex_descriptor;
        typedef std::pair<vertex_descriptor, vertex_descriptor> edge_descriptor;

        typedef std::deque<vertex_descriptor>::iterator vertex_iterator;
        typedef std::deque<edge_descriptor>::iterator edge_iterator;
        typedef std::set<vertex_descriptor>::iterator adjacency_iterator;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

       /**
         * @param u - vertex_descriptor
         * @param v - vertex_descriptor
         * @param g - reference to a graph
         * @return pair of edge_descriptor and boolean indicating whether creation of edge was successful
         * attempts to add an edge between vertex u and vertex v to Graph g
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor u, vertex_descriptor v, Graph& g) {
            int graph_size = (int)g._vertices.size();

            edge_descriptor ed = std::make_pair(u,v);
            if(graph_size > u){
                if(graph_size > v){
                    std::pair<adjacency_iterator, bool> uv = g._adjacents[u].insert(v);
                    if(uv.second){
                        g._edges.push_back(ed);
                    }
                    else
                        return std::make_pair(ed, false);
                }else{
                    for(vertex_descriptor i = graph_size; i <= v; ++i){
                        g._vertices.push_back(i);
                        g._adjacents.push_back(std::set<vertex_descriptor>());
                    }
                    return add_edge(u, v, g);
                }
            }

            return std::make_pair(ed, true);}

        // ----------
        // add_vertex
        // ----------

        /**
         * @param g reference to a Graph
         * @return vertex_descriptor
         * adds a vertex, v, to g and returns v
         */
        friend vertex_descriptor add_vertex (Graph& g) {
            vertex_descriptor v = g._vertices.size();
            g._vertices.push_back(v);
            g._adjacents.push_back(std::set<vertex_descriptor>());
            return v;}


        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * @param u - vertex descriptor
         * @param g - constant reference to a Graph
         * returns pair of adjacency iterators from beginning to end of all vertices adjacent to u
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor u, const Graph& g) {
            adjacency_iterator b = g._adjacents[u].begin();
            adjacency_iterator e = g._adjacents[u].end();
            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * @param u - vertex descriptor
         * @param v - vertex descriptor
         * @param g - constant reference to a Graph
         * @return pair of edge_descriptor and boolean indicating if edge between u, v exists
         * checks whether the graph contains an edge from u to v
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor u, vertex_descriptor v, const Graph& g) {
            edge_descriptor ed = std::make_pair(u, v);
            bool b = (g._adjacents[u].find(v) != g._adjacents[u].end());
            return std::make_pair(ed, b);}

        // -----
        // edges
        // -----

        /**
         * @param g - a constant reference to a Graph
         * @return a pair of edge_iterators to beginning and end of all edges in g
         * returns edge_iterators to beginning and end of all edges in a Graph
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) {
            edge_iterator b = g._edges.begin();
            edge_iterator e = g._edges.end();
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * @param g - a constant reference to a Graph
         * @return edges_size_type - number of edges in g
         * returns the number of edges in a Graph
         */
        friend edges_size_type num_edges (const Graph& g) {
            edges_size_type s = (edges_size_type) g._edges.size();
            return s;}
        // ------------
        // num_vertices
        // ------------

        /**
         * <your documentation>
         */
        friend vertices_size_type num_vertices (const Graph&) {
            // <your code>
            vertices_size_type s = 1; // fix
            return s;}

        // ------
        // source
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor source (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v = 0; // fix
            return v;}

        // ------
        // target
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor target (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v = 0; // fix
            return v;}

        // ------
        // vertex
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor vertex (vertices_size_type, const Graph&) {
            // <your code>
            vertex_descriptor vd = 0; // fix
            return vd;}

        // --------
        // vertices
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph&) {
            // <your code>
            static int a [] = {0, 0};     // dummy data
            vertex_iterator b = a;
            vertex_iterator e = a + 2;
            return std::make_pair(b, e);}

    private:
        // ----
        // data
        // ----

        std::deque< std::deque<vertex_descriptor> > g; // something like this

        // -----
        // valid
        // -----

        /**
         * <your documentation>
         */
        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Graph () {
            // <your code>
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h