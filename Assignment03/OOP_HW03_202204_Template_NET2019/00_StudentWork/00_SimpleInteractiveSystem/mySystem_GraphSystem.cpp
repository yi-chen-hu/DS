//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Prof. Sai-Keung Wong
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/04/25
//
#include <iostream>
#include "mySystem_GraphSystem.h"
#include <time.h>
#include <cmath>

using namespace std;

int Param::GRAPH_MAX_NUM_NODES = 1000;
int Param::GRAPH_MAX_NUM_EDGES = 1000;

GRAPH_SYSTEM::GRAPH_SYSTEM( )
{
    mFlgAutoNodeDeletion = false;
    initMemoryPool();
    createDefaultGraph();
    //
    // Implement your own stuff
    //
    mNumPoints_DoubleCircles = 24;
    
}

void GRAPH_SYSTEM::initMemoryPool()
{
    mNodeArr_Pool = new GRAPH_NODE[Param::GRAPH_MAX_NUM_NODES];
    mEdgeArr_Pool = new GRAPH_EDGE[Param::GRAPH_MAX_NUM_EDGES];

    mCurNumOfActiveNodes = 0;
    mCurNumOfActiveEdges = 0;
    mActiveNodeArr = new int[Param::GRAPH_MAX_NUM_NODES];
    mActiveEdgeArr = new int[Param::GRAPH_MAX_NUM_EDGES];

    mFreeNodeArr = new int[Param::GRAPH_MAX_NUM_NODES];
    mFreeEdgeArr = new int[Param::GRAPH_MAX_NUM_EDGES];
    //
    for (int i = 0; i < Param::GRAPH_MAX_NUM_NODES; ++i) {
        mNodeArr_Pool[i].id = i; // assign a unique id
    }
    for (int i = 0; i < Param::GRAPH_MAX_NUM_EDGES; ++i) {
        mEdgeArr_Pool[i].id = i; // assign a unique id
    }
    reset();
}

void GRAPH_SYSTEM::reset( )
{
    stopAutoNodeDeletion();
    mPassiveSelectedNode = 0;
    mSelectedNode = 0;
    //
    // Implement your own stuff
    //
    mCurNumOfActiveNodes = 0;
    mCurNumOfActiveEdges = 0;

    mCurNumOfFreeNodes = Param::GRAPH_MAX_NUM_NODES;
    mCurNumOfFreeEdges = Param::GRAPH_MAX_NUM_EDGES;

    for (int i = 0; i < mCurNumOfFreeNodes; ++i) {
        mFreeNodeArr[i] = i; // index is not used
    }
    for (int i = 0; i < mCurNumOfFreeEdges; ++i) {
        mFreeEdgeArr[i] = i; // index is not used
    }

}

void GRAPH_SYSTEM::createDefaultGraph( )
{
    reset( );
    //
    // Implement your own stuff
    //
    int n1 = addNode(0.0, 0.0, 0.0);
    int n2 = addNode(5.0, 0.0, 0.0);
    int n3 = addNode(0.0, 0.0, 5.0);
    int e1 = addEdge(n1, n2);
    int e2 = addEdge(n2, n3);
}

void GRAPH_SYSTEM::createRandomGraph_DoubleCircles(int n)
{
    reset( );
    srand(time(NULL));
    float dx = 5.0;
    float dz = 5.0;
    float r = 15; // radius
    float d = 10; // layer distance
    float offset_x = 15.;
    float offset_z = 15.;
    //
    // Implement your own stuff
    //
    int** layers;
    layers = new int* [2];
    for (int i = 0; i < 2; i++)
        layers[i] = new int[n];
    for (int j = 0; j < n; j++)
        layers[0][j] = addNode(r * cos(2.0 * 3.141592654 / n * j) + offset_x, 0.0, r * sin(2.0 * 3.141592654 / n * j) + offset_z);
    for (int j = 0; j < n; j++)
        layers[1][j] = addNode((r + d) * cos(2.0 * 3.141592654 / n * j) + offset_x, 0.0, (r + d) * sin(2.0 * 3.141592654 / n * j) + offset_z);
    for (int j = 0; j < n; j++)
    {
        int randNum;
        if (n < 8)
            randNum = j + (-1 + rand() % 3);
        else
           randNum = j + (-2 + rand() % 5);
        if (randNum < 0)
            randNum += n;
        else if (randNum > n - 1)
            randNum -= n;
        int e = addEdge(layers[0][j], layers[1][randNum]);
    }
}

void GRAPH_SYSTEM::createNet_Circular( int n, int num_layers )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 15.;
    float offset_z = 15.;
    //
    // Implement your own stuff
    //
    int** layers;
    layers = new int* [num_layers + 1];
    for (int i = 0; i < num_layers + 1; i++)
        layers[i] = new int[n];
    for(int i = 0; i < num_layers + 1; i++)
        for(int j = 0; j < n; j++)
            layers[i][j] = addNode(d * (1 + i) * cos(2.0 * 3.141592654 / n * j) + offset_x, 0.0, d * (1 + i) * sin(2.0 * 3.141592654 / n * j) + offset_z);
    for (int i = 0; i < num_layers; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int e;
            if (j == n - 1)
                e = addEdge(layers[i][j], layers[i][0]);
            else
                e = addEdge(layers[i][j], layers[i][j + 1]);
        }
    }
    for (int i = 0; i < num_layers; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int e;
            e = addEdge(layers[i][j], layers[i + 1][j]);
        }
    }
}
void GRAPH_SYSTEM::createNet_Square( int n, int num_layers )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = -5.;
    float offset_z = 5.;
    //
    // Implement your own stuff
    //
    int node[20][20];
    for (int i = 0; i < num_layers; i++)
    {
        for (int j = 0; j < num_layers; j++)
        {
            node[i][j] = addNode(dx * j + offset_x, 0.0, dz * i + offset_z);
        }
    }

    for (int i = 0; i < num_layers; i++)
    {
        for (int j = 0; j < num_layers - 1; j++)
        {
            int e = addEdge(node[i][j], node[i][j + 1]);
        }
    }

    for (int j = 0; j < num_layers; j++)
    {
        for (int i = 0; i < num_layers - 1; i++)
        {
            int e = addEdge(node[i][j], node[i + 1][j]);
        }
    }

    int start = (num_layers - n) / 2;
    int end = num_layers - start;

    GRAPH_NODE* nd;
    for (int i = start; i < end; i++)
    {
        for (int j = start; j < end; j++)
        {
            nd = &mNodeArr_Pool[node[i][j]];
            deleteNode(nd->dynamicID);
        }
    }

    /*
    int** layers;
    layers = new int* [num_layers];
    for (int i = 0; i < num_layers; i++)
        layers[i] = new int[n];
    
    for (int i = 0; i < num_layers; i++)
    {
        for (int j = 0; j < num_layers; j++)
        {
            layers[i][j] = addNode(dx * j + offset_x, 0.0, dz * i + offset_z);
        }
    }

    for (int i = 0; i < num_layers; i++)
    {
        for (int j = 0; j < num_layers - 1; j++)
        {
            int e = addEdge(layers[i][j], layers[i][j + 1]);
        }
    }

    for (int j = 0; j < num_layers; j++)
    {
        for (int i = 0; i < num_layers - 1; i++)
        {
            int e = addEdge(layers[i][j], layers[i + 1][j]);
        }
    }

    int start = (num_layers - n) / 2;
    int end = num_layers - start;

    GRAPH_NODE* node;
    for (int i = start; i < end; i++)
    {
        for (int j = start; j < end; j++)
        {
            node = &mNodeArr_Pool[layers[i][j]];
            deleteNode(node->dynamicID);
        }
    }
    */
}

void GRAPH_SYSTEM::createNet_RadialCircular( int n ) {

    reset( );

    float offset_x = 15.0;
    float offset_z = 15.0;

    float r = 15; // radius
    //
    // Implement your own stuff
    //  
    int n1 = addNode(0.0 + offset_x, 0.0, 0.0 + offset_z);

    for (int i = 0; i < n; i++)
    {
        int n = addNode(15 * cos(2.0 * 3.141592654 / 24 * i) + offset_x, 0.0, 15 * sin(2.0 * 3.141592654 / 24 * i) + offset_z);
        int e = addEdge(n1, n);
    }

}

GRAPH_NODE* GRAPH_SYSTEM::getFreeNode() {
    if (mCurNumOfFreeNodes == 0)    return 0;
    --mCurNumOfFreeNodes;
    int id = mFreeNodeArr[mCurNumOfFreeNodes];
    GRAPH_NODE* n = &mNodeArr_Pool[id];
    mActiveNodeArr[mCurNumOfActiveNodes] = id;
    n->dynamicID = mCurNumOfActiveNodes;
    ++mCurNumOfActiveNodes;
    return n;
}

// return node id
int GRAPH_SYSTEM::addNode( float x, float y, float z, float r )
{
    GRAPH_NODE* g;
    g = getFreeNode();
    if (g == 0) return -1; // invalid id.
    g->p = vector3(x, y, z);
    g->r = r;
    g->edgeID.clear();
    //cout << g->dynamicID << " " << g->id << endl;
    return g->id;
}

GRAPH_EDGE* GRAPH_SYSTEM::getFreeEdge() {
    if (mCurNumOfFreeEdges == 0) return 0;
    --mCurNumOfFreeEdges;
    int id = mFreeEdgeArr[mCurNumOfFreeEdges]; // get the last
    GRAPH_EDGE* e = &mEdgeArr_Pool[id];
    mActiveEdgeArr[mCurNumOfActiveEdges] = id; // put to last
    e->dynamicID = mCurNumOfActiveEdges;
    ++mCurNumOfActiveEdges;
    return e;
}

// return edge id
int GRAPH_SYSTEM::addEdge(int nodeID_0, int nodeID_1)
{
    GRAPH_EDGE* e;
    e = getFreeEdge();
    if (e == 0) return -1;
    e->nodeID[0] = nodeID_0;
    e->nodeID[1] = nodeID_1;
    mNodeArr_Pool[nodeID_0].edgeID.push_back(e->id);
    mNodeArr_Pool[nodeID_1].edgeID.push_back(e->id);
    //cout << e->dynamicID << " " << e->id << " " << e->nodeID[0] << " " << e->nodeID[1] << endl;
    return e->id;

}

void GRAPH_SYSTEM::askForInput( )
{
    //
    // Implement your own stuff
    // 
    cout << "GRAPH_SYSTEM" << endl;
    cout << "Key usage:" << endl;
    cout << "1: create a default graph" << endl;
    cout << "2: create nodes arranged in circles" << endl;
    cout << "3: create nodes arranged in squares. Some nodes at the center are removed." << endl;
    cout << "4: create nodes arranged in a circle and one node at center." << endl;
    cout << "5: create nodes arranged in two circles. The edges are randomly created for nodes in the inner and outer circle." << endl;
    cout << "Delete: delete a node and all the edges attached at it" << endl;
    cout << "Spacebar: unselect the selected node" << endl;
    cout << " " << endl;
    cout << "Use the mouse to select nodes and add edges" << endl;
    cout << "Click the left button to select/unselect or create an edge" << endl;
    cout << " " << endl;
    cout << "A selected node is highlighted as red." << endl;

}

GRAPH_NODE *GRAPH_SYSTEM::findNearestNode( double x, double z, double &cur_distance2 ) const
{
    GRAPH_NODE *n = 0;
    //
    // Implement your own stuff
    //
    for (int i = 0; i < mCurNumOfActiveNodes; i++)
    {
        int id = mActiveNodeArr[i];
        GRAPH_NODE* node = &mNodeArr_Pool[id];
        int nx = node->p.x;
        int nz = node->p.z;
        int distance = (nx - x) * (nx - x) + (nz - z) * (nz - z);
        if (i == 0)
        {
            cur_distance2 = distance;
            n = node;
        }
        if (distance <= cur_distance2)
        {
            cur_distance2 = distance;
            n = node;
        }
    }
    return n;
}

//
// compute mSelectedNode
//
void GRAPH_SYSTEM::clickAt(double x, double z)
{
    //
    // Implement your own stuff
    // 
    // mSelectedNode = n;
    double cur_d2;
    GRAPH_NODE* n = findNearestNode(x, z, cur_d2);
    if (n == 0) return;
    if (n == mSelectedNode)
    {
        mSelectedNode = 0;
        return;
    }
    if (cur_d2 > n->r * n->r) {
        mSelectedNode = 0;
        return;
    }
    if (n != mSelectedNode && mSelectedNode != 0)
    {
        int e = addEdge(n->id, mSelectedNode->id);
        mSelectedNode = 0;
        return;
    }
    mSelectedNode = n;
    //cout << n->dynamicID << endl;
}

void GRAPH_SYSTEM::deleteNode( int nodeID ) {
    //
    // Implement your own stuff
    // 
    int id = mActiveNodeArr[nodeID];
    GRAPH_NODE* node = &mNodeArr_Pool[id];

    //delete all edges which connect to deleted node
    int N = node->edgeID.size();

    for (int i = 0; i < N; i++)
    {
        GRAPH_EDGE* e = &mEdgeArr_Pool[node->edgeID[i]];
        mFreeEdgeArr[mCurNumOfFreeEdges++] = e->id; //free edgeÅÜ¤j
        mActiveEdgeArr[e->dynamicID] = mActiveEdgeArr[--mCurNumOfActiveEdges];    //move the last active edge to deleted edge
        GRAPH_EDGE* e_last = &mEdgeArr_Pool[mActiveEdgeArr[e->dynamicID]];
        e_last->dynamicID = e->dynamicID;   //update the dynamicID of the last edge

        //delete the edgeID in two nodes which connect to the deleted edge
        GRAPH_NODE* n1;
        if (e->nodeID[0] != node->id)
            n1 = &mNodeArr_Pool[e->nodeID[0]];
        else if (e->nodeID[1] != node->id)
            n1 = &mNodeArr_Pool[e->nodeID[1]];

        int N1 = n1->edgeID.size();
        for (int j = 0; j < N1; j++)
        {
            if (n1->edgeID[j] == e->id)
            {
                n1->edgeID.erase(n1->edgeID.begin() + j);
                break;
            }
        }
    }
    node->edgeID.clear();

    mFreeNodeArr[mCurNumOfFreeNodes++] = node->id;
    mActiveNodeArr[node->dynamicID] = mActiveNodeArr[mCurNumOfActiveNodes - 1];
    GRAPH_NODE* node_last = &mNodeArr_Pool[mActiveNodeArr[node->dynamicID]];
    node_last->dynamicID = node->dynamicID;
    --mCurNumOfActiveNodes;
    
    mSelectedNode = 0;
}

void GRAPH_SYSTEM::deleteSelectedNode(  ) {
    //
    // Implement your own stuff
    //
    if (isSelectedNode())
        deleteNode(mSelectedNode->dynamicID);

}

bool GRAPH_SYSTEM::isSelectedNode( ) const
{
    //
    // mSelectedNode != 0;
    //
    // Implement your own stuff
    // 
    
    return mSelectedNode != 0;
}

void GRAPH_SYSTEM::getInfoOfSelectedPoint( double &r, vector3 &p ) const
{
    r = mSelectedNode->r;
    p = mSelectedNode->p;
    //
    // Implement your own stuff
    // 
}



void GRAPH_SYSTEM::handleKeyPressedEvent( unsigned char key )
{
    
    switch( key ) {
    case 127: // delete
        mFlgAutoNodeDeletion = false;
        deleteSelectedNode( );
        mSelectedNode = 0;
        break;
    case '1':
        mFlgAutoNodeDeletion = false;
        createDefaultGraph( );
        mSelectedNode = 0;
        break;
    case '2':
        mFlgAutoNodeDeletion = false;
        createNet_Circular(12, 3);
        mSelectedNode = 0;

        break;
    case '3':
        mFlgAutoNodeDeletion = false;
        createNet_Square(3, 11); // you can modify this
        mSelectedNode = 0;

        break;
    case '4':
        mFlgAutoNodeDeletion = false;
        createNet_RadialCircular(24);
        mSelectedNode = 0;

        break;
    case '5':
        mFlgAutoNodeDeletion = false;
        createRandomGraph_DoubleCircles(24);
        mSelectedNode = 0;

        break;

    case ' ':
        mFlgAutoNodeDeletion = false;
        mSelectedNode = 0;
        break;
    case 'd':
        mFlgAutoNodeDeletion = !mFlgAutoNodeDeletion;
        break;

    case '<':
        mFlgAutoNodeDeletion = false;
        mNumPoints_DoubleCircles--;
        if (mNumPoints_DoubleCircles <= 3)
            mNumPoints_DoubleCircles = 3;
        createRandomGraph_DoubleCircles(mNumPoints_DoubleCircles);
        break;
    case '>':
        mFlgAutoNodeDeletion = false;
        mNumPoints_DoubleCircles++;
        if (mNumPoints_DoubleCircles >= 36)
            mNumPoints_DoubleCircles = 36;
        createRandomGraph_DoubleCircles(mNumPoints_DoubleCircles);
        break;
    }
}

void GRAPH_SYSTEM::handlePassiveMouseEvent( double x, double z )
{
    double cur_d2;
    GRAPH_NODE *n = findNearestNode( x, z, cur_d2 );
    if ( n == 0 ) return;
    if ( cur_d2 > n->r*n->r ) {
        mPassiveSelectedNode = 0;
        return;
    }
    mPassiveSelectedNode = n;
}

//
// get the number of nodes
//
int GRAPH_SYSTEM::getNumOfNodes( ) const
{
    //
    // Implement your own stuff
    // 
    return mCurNumOfActiveNodes;
}

void GRAPH_SYSTEM::getNodeInfo( int nodeIndex, double &r, vector3 &p ) const
{
    //
    // Implement your own stuff
    // 
    int i = mActiveNodeArr[nodeIndex];
    GRAPH_NODE* node = &mNodeArr_Pool[i];
    r = node->r;
    p = node->p;
}

//
// return the number of edges
//
int GRAPH_SYSTEM::getNumOfEdges( ) const
{
    //
    // Implement your own stuff
    // 
    return mCurNumOfActiveEdges;
}

//
// an edge should have two nodes: index 0 and index 1
// return the position of node with nodeIndex
//
vector3 GRAPH_SYSTEM::getNodePositionOfEdge( int edgeIndex, int nodeIndex ) const
{
    vector3 p;
    //
    // Implement your own stuff
    // 
    int index = mActiveEdgeArr[edgeIndex];
    GRAPH_EDGE* edge = &mEdgeArr_Pool[index];
    if (nodeIndex == 0)
    {
        int i = edge->nodeID[0];
        GRAPH_NODE* node = &mNodeArr_Pool[i];
        p = node->p;
    }
    else if (nodeIndex == 1)
    {
        int i = edge->nodeID[1];
        GRAPH_NODE* node = &mNodeArr_Pool[i];
        p = node->p;
    }
    return p;
}

void GRAPH_SYSTEM::stopAutoNodeDeletion()
{
    mFlgAutoNodeDeletion = false;
}

//
// For every frame, update( ) function is called.
// 
//
void GRAPH_SYSTEM::update( )
{
    if (!mFlgAutoNodeDeletion) {
     
        return;
    }
    mSelectedNode = 0;
    mPassiveSelectedNode = 0;
    if (getNumOfNodes() == 0)
        return;
    deleteNode(getNumOfNodes() - 1);
    Sleep(250);
    //
    //
    // Implement your own stuff
    // 

}