// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall TestGraph.c++ -o TestGraph -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestGraph

To obtain coverage of the test:
    % gcov-4.7 -b Graph.c++ TestGraph.c++
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h"

#include "Graph.h"

// ---------
// TestGraph
// ---------

template <typename G>
struct TestGraph : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          G                     graph_type;
    typedef typename G::vertex_descriptor  vertex_descriptor;
    typedef typename G::edge_descriptor    edge_descriptor;
    typedef typename G::vertex_iterator    vertex_iterator;
    typedef typename G::edge_iterator      edge_iterator;
    typedef typename G::adjacency_iterator adjacency_iterator;
    typedef typename G::vertices_size_type vertices_size_type;
    typedef typename G::edges_size_type    edges_size_type;};

// directed, sparse, unweighted
// possibly connected
// possibly cyclic
typedef testing::Types<
            boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>,
            Graph>
        my_types;

TYPED_TEST_CASE(TestGraph, my_types);

//add edge
TYPED_TEST(TestGraph, add_edge){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    ASSERT_EQ(1, num_edges(g));
    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p1.first);
    ASSERT_EQ(false, p1.second);
    vertex_descriptor a = source(edAB, g);
    vertex_descriptor b = target(edAB, g);
    ASSERT_EQ(a, vdA);
    ASSERT_EQ(b, vdB);
}

TYPED_TEST(TestGraph, add_edge2){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, 2, g).first;

    ASSERT_EQ(2, num_edges(g));
    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    std::pair<edge_descriptor, bool> p2 = add_edge(vdA, 2, g);
    ASSERT_EQ(edAB, p1.first);
    ASSERT_EQ(false, p1.second);
    vertex_descriptor a = source(edAB, g);
    vertex_descriptor b = target(edAB, g);
    ASSERT_EQ(a, vdA);
    ASSERT_EQ(b, vdB);

    ASSERT_EQ(edAC, p2.first);
    ASSERT_EQ(false, p2.second);
    vertex_descriptor c = source(edAC, g);
    vertex_descriptor d = target(edAC, g);
    ASSERT_EQ(a, vdA);
    ASSERT_EQ(d, 2);
}

TYPED_TEST(TestGraph, add_edge3){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edA5 = add_edge(vdA, 5, g).first;

    ASSERT_EQ(2, num_edges(g));
    ASSERT_EQ(6, num_vertices(g));
    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    std::pair<edge_descriptor, bool> p2 = add_edge(vdA, 5, g);
    ASSERT_EQ(edAB, p1.first);
    ASSERT_EQ(false, p1.second);
    vertex_descriptor a = source(edAB, g);
    vertex_descriptor b = target(edAB, g);
    ASSERT_EQ(a, vdA);
    ASSERT_EQ(b, vdB);

    ASSERT_EQ(edA5, p2.first);
    ASSERT_EQ(false, p2.second);
    vertex_descriptor c = source(edA5, g);
    vertex_descriptor d = target(edA5, g);
    ASSERT_EQ(a, vdA);
    ASSERT_EQ(d, 5);
}

//add_vertex
TYPED_TEST(TestGraph, add_vertex){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    for(int i = 0; i < 100; ++i)
        add_vertex(g);
    ASSERT_EQ(100, num_vertices(g));
}

TYPED_TEST(TestGraph, add_vertex2){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor v = add_vertex(g);
    vertex_descriptor w = add_vertex(g);

    ASSERT_EQ(2, num_vertices(g));
    ASSERT_EQ(0, v);
    ASSERT_EQ(1, w);
}

TYPED_TEST(TestGraph, add_vertex3){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor v = add_vertex(g);
    add_edge(v, 99, g);
    ASSERT_EQ(100, num_vertices(g));
}

//adjacent_vertices

TYPED_TEST(TestGraph, adjacent_vertices){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    add_edge(vdA, vdB, g);

    std::pair<adjacency_iterator,adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_EQ(*b, vdB);
    ++b;
    ASSERT_EQ(b,e);
}

TYPED_TEST(TestGraph, adjacent_vertices2){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    add_edge(vdA, vdB, g);
    add_edge(vdC, vdB, g);

    std::pair<adjacency_iterator,adjacency_iterator> p = adjacent_vertices(vdA, g);
    std::pair<adjacency_iterator,adjacency_iterator> q = adjacent_vertices(vdC, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    adjacency_iterator b2 = q.first;
    adjacency_iterator e2 = q.second;
    ASSERT_EQ(*b, vdB);
    ASSERT_EQ(*b2, vdB);
    ASSERT_EQ(*b2, *b);
    ++b; ++b2;
    ASSERT_EQ(b,e);
    ASSERT_EQ(b2, e2);
}

TYPED_TEST(TestGraph, adjacent_vertices3){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    for(int i = 0; i < 10; ++i)
        add_edge(vdA, i, g);

    std::pair<adjacency_iterator,adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    for(int i = 0; i < 10; ++i)
        ASSERT_EQ(*b++, i);
    ASSERT_EQ(b,e);
}

TYPED_TEST(TestGraph, edge){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor v = add_vertex(g);
    vertex_descriptor u = add_vertex(g);

    std::pair<edge_descriptor,bool> p = edge(v, u, g);
    ASSERT_EQ(false, p.second);

}

TYPED_TEST(TestGraph, edge2){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor v = add_vertex(g);
    vertex_descriptor u = add_vertex(g);
    edge_descriptor e = add_edge(v, u, g).first;

    std::pair<edge_descriptor,bool> p = edge(v, u, g);
    ASSERT_EQ(true, p.second);
    ASSERT_EQ(e, p.first);

}

TYPED_TEST(TestGraph, edge3){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor v = add_vertex(g);
    vertex_descriptor u = add_vertex(g);
    edge_descriptor e = add_edge(v, u, g).first;

    std::pair<edge_descriptor,bool> p = edge(u, v, g);
    ASSERT_EQ(false, p.second);
    ASSERT_FALSE(p.first == e);

}

TYPED_TEST(TestGraph, edges){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor v = add_vertex(g);
    for(int i = 0; i < 10; ++i)
        add_edge(v, i, g);
    ASSERT_EQ(10, num_edges(g));

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator b = p.first;
    edge_iterator e = p.second;

    for(int i = 0; i < 10; ++i)
    {
        edge_descriptor ed = *b;
        ASSERT_EQ(i, target(ed, g));
        ++b;
    }
    ASSERT_EQ(b, e);
}

TYPED_TEST(TestGraph, edges2){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor v = add_vertex(g);

    ASSERT_EQ(0, num_edges(g));

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator b = p.first;
    edge_iterator e = p.second;

    ASSERT_EQ(b, e);
}

TYPED_TEST(TestGraph, edges3){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor v = add_vertex(g);
    for(int i = 0; i < 100; ++i)
        add_edge(v, i, g);
    ASSERT_EQ(100, num_edges(g));

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator b = p.first;
    edge_iterator e = p.second;

    for(int i = 0; i < 100; ++i)
    {
        edge_descriptor ed = *b;
        ASSERT_EQ(i, target(ed, g));
        ++b;
    }
    ASSERT_EQ(b, e);
}

TYPED_TEST(TestGraph, num_edges){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    ASSERT_EQ(0, num_edges(g));
}

TYPED_TEST(TestGraph, num_edges2){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor u = add_vertex(g);
    edge_descriptor e = add_edge(u, 100, g).first;
    ASSERT_EQ(source(e, g), u);
    ASSERT_EQ(target(e, g), 100);
    ASSERT_EQ(1, num_edges(g));
}

TYPED_TEST(TestGraph, num_edges3){
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor u = add_vertex(g);
    vertex_descriptor v = add_vertex(g);
    add_edge(u,v,g);
    add_edge(v,u,g);
    for(int i = 0; i < 100; ++i)
    {
        add_edge(u, i, g);
        add_edge(v, i, g);
    }

    ASSERT_EQ(200, num_edges(g));
}

TYPED_TEST(TestGraph, Vertex) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(1, vs);}

TYPED_TEST(TestGraph, Edge) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edA5 = add_edge(vdA, 5, g).first;

    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    std::pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(2, es);
    ASSERT_EQ(6, num_vertices(g));

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);}

TYPED_TEST(TestGraph, Vertices) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, Edges) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAC, ed);}
    ++b;
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, Adjacent_Vertices) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    ASSERT_EQ(e, b);}