#include <iostream>
#include <fstream>
#include <queue>

#include "GrafLista.h"

void GrafLista::Node::addEdge(size_t index)
{
	m_edges.insert(index);
}

void GrafLista::Node::removeEdge(size_t index)
{
	m_edges.erase(index);
}

bool GrafLista::Node::checkEdge(size_t index)
{
	return m_edges.find(index) != m_edges.end();
}

size_t GrafLista::Node::getNumberOfEdges()
{
	return m_edges.size();
}

std::vector<size_t> GrafLista::Node::getNeighbourIndicies()
{
	return std::vector<size_t>(m_edges.begin(), m_edges.end());
}

void GrafLista::Node::printNeighbourIndices()
{
	for (auto it : m_edges) {
		std::cout << it << " ";
	}
}

GrafLista::GrafLista()
{
}

void GrafLista::addEdge(size_t i_Vertex_Index_1, size_t i_Vertex_Index_2)
{
	m_Nodes.at(i_Vertex_Index_1).addEdge(i_Vertex_Index_2);
}

void GrafLista::removeEdge(size_t i_Vertex_Index_1, size_t i_Vertex_Index_2)
{
	m_Nodes.at(i_Vertex_Index_1).removeEdge(i_Vertex_Index_2);
}

bool GrafLista::checkEdge(size_t i_Vertex_Index_1, size_t i_Vertex_Index_2)
{
	return m_Nodes.at(i_Vertex_Index_1).checkEdge(i_Vertex_Index_2);
}

int GrafLista::vertexDegree(size_t idx)
{
	return m_Nodes.at(idx).getNumberOfEdges();
}

void GrafLista::createVerticies(size_t size)
{
	m_Nodes.resize(m_Nodes.size() + size);
}

std::vector<size_t> GrafLista::getNeighbourIndices(size_t idx)
{
	return m_Nodes.at(idx).getNeighbourIndicies();
}

void GrafLista::printNeighbourIndices(size_t idx)
{
	m_Nodes.at(idx).printNeighbourIndices();
}

int GrafLista::getNumberOfEdges()
{
	int sum = 0;
	for (auto it : m_Nodes) {
		sum += it.getNumberOfEdges();
	}
	return sum;
}

void GrafLista::readFromFile(std::string path)
{
	std::ifstream file(path);
	if (!file.good())
		throw std::runtime_error("Nie mozna otworzyc pliku");

	size_t numberOfVertecies;
	file >> numberOfVertecies;
	createVerticies(numberOfVertecies);
	while (!file.eof()) {
		size_t iIndex, jIndex;
		file >> iIndex;
		file >> jIndex;
		addEdge(iIndex, jIndex);
	}
}

std::vector<size_t> GrafLista::DFS(size_t index, std::vector<size_t>&& alreadyVisited)
{
	std::vector<size_t> returnVector{index };
	alreadyVisited.push_back(index);
	for (auto it : getNeighbourIndices(index)) {
		if (std::find(alreadyVisited.begin(), alreadyVisited.end(), it) == alreadyVisited.end()) {
			alreadyVisited.push_back(it);
			std::vector<size_t> temp = std::move(DFS(it, std::move(alreadyVisited)));
			returnVector.insert(returnVector.end(), temp.begin(), temp.end());
		}
		
	}
	return returnVector;
}

std::vector<size_t> GrafLista::BFS(size_t index)
{
	std::vector<size_t> alreadyVisited{ index };
	std::vector<size_t> returnVector;
	std::queue<size_t> queue;
	queue.push(index);
	while (!queue.empty()) {
		size_t v = queue.front();
		returnVector.push_back(v);
		queue.pop();
		for (auto it : getNeighbourIndices(v)) {
			if (std::find(alreadyVisited.begin(), alreadyVisited.end(), it) == alreadyVisited.end()) {
				alreadyVisited.push_back(it);
				queue.push(it);
			}
			
		}
	}
	return returnVector;
}

void GrafLista::clear()
{
	for (auto it : m_Nodes) {
		m_Nodes.clear();
	}
	m_Nodes.clear();
}
