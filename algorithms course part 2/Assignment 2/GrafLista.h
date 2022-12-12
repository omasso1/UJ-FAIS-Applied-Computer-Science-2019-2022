#pragma once
#include <vector>
#include <set>
#include <string>



class GrafLista
{
private:
    struct Node {
        std::set<size_t> m_edges;
        void addEdge(size_t index);
        void removeEdge(size_t index);
        bool checkEdge(size_t index);
        size_t getNumberOfEdges();
        std::vector<size_t> getNeighbourIndicies();
        void printNeighbourIndices();
    };

    std::vector<Node> m_Nodes;

public:
    GrafLista();
    void addEdge(size_t i_Vertex_Index_1, size_t i_Vertex_Index_2);
    void removeEdge(size_t i_Vertex_Index_1, size_t i_Vertex_Index_2);
    bool checkEdge(size_t i_Vertex_Index_1, size_t i_Vertex_Index_2);
    int vertexDegree(size_t idx);
    void createVerticies(size_t size);
    std::vector<size_t> getNeighbourIndices(size_t idx);
    void printNeighbourIndices(size_t idx);
    int getNumberOfEdges();
    void readFromFile(std::string path);
    std::vector<size_t> DFS(size_t index, std::vector<size_t>&& alreadyVisited = std::vector<size_t>());
    std::vector<size_t> BFS(size_t index);
private:
    void clear();
};

