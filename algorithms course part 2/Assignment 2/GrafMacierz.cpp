#include <stdexcept>
#include <iostream>
#include <fstream>

#include "GrafMacierz.h"

GrafMacierz::GrafMacierz()
	:m_numberOfVertices(0)
{	
	m_matrix = new int* [MaxSize];
	for (size_t i = 0; i < MaxSize; i++) {
		m_matrix[i] = new int [MaxSize];
		for (size_t j = 0; j < MaxSize; j++) {
			m_matrix[i][j] = 0;
		}
	}
}

GrafMacierz::~GrafMacierz()
{
	for (size_t i = 0; i < MaxSize; i++) {
		delete[] m_matrix[i];
	}
	delete[] m_matrix;
}

void GrafMacierz::createVertices(size_t ile)
{
	if (m_numberOfVertices + ile > MaxSize)
		throw std::out_of_range("Przekroczono maksymalny rozmiar");
	m_numberOfVertices += ile;
}

void GrafMacierz::addEdge(size_t i_Vertex_Index_1, size_t i_Vertex_Index_2)
{
	if (i_Vertex_Index_1 >= MaxSize || i_Vertex_Index_2 >= MaxSize)
		throw std::out_of_range("Za duzy indeks");
	m_matrix[i_Vertex_Index_1][i_Vertex_Index_2] = 1;
}

void GrafMacierz::removeEdge(size_t i_Vertex_Index_1, size_t i_Vertex_Index_2)
{
	if (i_Vertex_Index_1 >= MaxSize || i_Vertex_Index_2 >= MaxSize)
		throw std::out_of_range("Za duzy indeks");
	m_matrix[i_Vertex_Index_1][i_Vertex_Index_2] = 0;
}

bool GrafMacierz::checkEdge(size_t i_Vertex_Index_1, size_t i_Vertex_Index_2)
{
	if (i_Vertex_Index_1 >= MaxSize || i_Vertex_Index_2 >= MaxSize)
		throw std::out_of_range("Za duzy indeks");
	return m_matrix[i_Vertex_Index_1][i_Vertex_Index_2];
}

int GrafMacierz::vertexDegree(size_t idx)
{
	if (idx >= MaxSize)
		throw std::out_of_range("Za duzy indeks");

	int degree = 0;

	for (size_t i = 0; i < (size_t)m_numberOfVertices; i++) {
		if (m_matrix[idx][i])
			degree++;
	}
	return degree;
}

std::vector<int> GrafMacierz::getNeighbourIndices(size_t idx)
{
	if (idx >= MaxSize)
		throw std::out_of_range("Za duzy indeks");

	std::vector<int> neighbours;
	for (size_t i = 0; i < (size_t)m_numberOfVertices; i++) {
		if (m_matrix[idx][i])
			neighbours.push_back(i);
	}

	return neighbours;
}

void GrafMacierz::printNeighbourIndices(size_t idx)
{
	for (auto it : getNeighbourIndices(idx)) {
		std::cout << it << " ";
	}
}

int GrafMacierz::getNumberOfEdges()
{
	int n = 0;
	for (size_t i = 0; i < (size_t)m_numberOfVertices; i++) {
		for (size_t j = 0; j < (size_t)m_numberOfVertices; j++) {
			if (m_matrix[i][j])
				n++;
		}
	}
	return n;
}

void GrafMacierz::readFromFile(std::string path)
{
	std::ifstream file(path);
	if (!file.good())
		throw std::runtime_error("Nie mozna otworzyc pliku");

	size_t numberOfVertecies;
	file >> numberOfVertecies;
	createVertices(numberOfVertecies);

	while(!file.eof()){
		size_t iIndex, jIndex;
		file >> iIndex;
		file >> jIndex;
		
		addEdge(iIndex, jIndex);
	}
}

void GrafMacierz::clear()
{
	for (size_t i = 0; i < (size_t)m_numberOfVertices; i++) {
		for (size_t j = 0; j < (size_t)m_numberOfVertices; j++) {
			m_matrix[i][j] = 0;
		}
	}
	m_numberOfVertices = 0;
}
