#pragma once
#include <vector>
#include <string>



class GrafMacierz
{

public:
    static constexpr size_t MaxSize = 100;
private:
    //od razu musimy zadeklarowaæ maksymaln¹ iloœæ wierzcho³ków - tutaj 100;
    int** m_matrix;
    int m_numberOfVertices;

public:
    GrafMacierz();
    ~GrafMacierz();
    void createVertices(size_t ile);
    void addEdge(size_t i_Vertex_Index_1, size_t i_Vertex_Index_2);
    void removeEdge(size_t i_Vertex_Index_1, size_t i_Vertex_Index_2);
    bool checkEdge(size_t i_Vertex_Index_1, size_t i_Vertex_Index_2);
    int vertexDegree(size_t idx);
    std::vector<int> getNeighbourIndices(size_t idx);
    void printNeighbourIndices(size_t idx);
    int getNumberOfEdges();
    void readFromFile(std::string path);

private:
    void clear();
};

