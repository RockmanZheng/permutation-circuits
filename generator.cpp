#include <stack>
#include <queue>
#include <map>
#include <vector>
#include <array>
#include <list>
#include <iostream>
#include <algorithm>
#include <string>

using Perm = std::string;

using Path = std::vector<std::string>;

struct Gate {
	Perm perm;
	Path actions;
	Gate(const Perm& p, const Path& as) {
		perm = p;
		actions = as;
	}
};

struct Compare {
	bool operator()(const Gate& a, const Gate& b)const {
		return a.perm < b.perm;
	}
};

using Graph = std::map<Gate, std::list<Gate>, Compare>;
using VisitTag = std::map<Gate, bool, Compare>;

Perm cn12(const Perm& perm) {
	Perm new_perm(perm);
	int pos5 = new_perm.find('5');
	int pos7 = new_perm.find('7');
	int pos6 = new_perm.find('6');
	int pos8 = new_perm.find('8');
	std::swap(new_perm[pos5], new_perm[pos7]);
	std::swap(new_perm[pos6], new_perm[pos8]);
	return new_perm;
}

Perm cn13(const Perm& perm) {
	Perm new_perm(perm);
	int pos5 = new_perm.find('5');
	int pos7 = new_perm.find('7');
	int pos6 = new_perm.find('6');
	int pos8 = new_perm.find('8');
	std::swap(new_perm[pos5], new_perm[pos6]);
	std::swap(new_perm[pos7], new_perm[pos8]);
	return new_perm;
}

Perm cn23(const Perm& perm) {
	Perm new_perm(perm);
	int pos3 = new_perm.find('3');
	int pos7 = new_perm.find('7');
	int pos4 = new_perm.find('4');
	int pos8 = new_perm.find('8');
	std::swap(new_perm[pos3], new_perm[pos4]);
	std::swap(new_perm[pos7], new_perm[pos8]);
	return new_perm;
}

Perm cn21(const Perm& perm) {
	Perm new_perm(perm);
	int pos3 = new_perm.find('3');
	int pos7 = new_perm.find('7');
	int pos4 = new_perm.find('4');
	int pos8 = new_perm.find('8');
	std::swap(new_perm[pos3], new_perm[pos7]);
	std::swap(new_perm[pos4], new_perm[pos8]);
	return new_perm;
}

Perm cn31(const Perm& perm) {
	Perm new_perm(perm);
	int pos2 = new_perm.find('2');
	int pos6 = new_perm.find('6');
	int pos4 = new_perm.find('4');
	int pos8 = new_perm.find('8');
	std::swap(new_perm[pos2], new_perm[pos6]);
	std::swap(new_perm[pos4], new_perm[pos8]);
	return new_perm;
}

Perm cn32(const Perm& perm) {
	Perm new_perm(perm);
	int pos2 = new_perm.find('2');
	int pos6 = new_perm.find('6');
	int pos4 = new_perm.find('4');
	int pos8 = new_perm.find('8');
	std::swap(new_perm[pos2], new_perm[pos4]);
	std::swap(new_perm[pos6], new_perm[pos8]);
	return new_perm;
}

Perm tof1(const Perm& perm) {
	Perm new_perm(perm);
	int pos4 = new_perm.find('4');
	int pos8 = new_perm.find('8');
	std::swap(new_perm[pos8], new_perm[pos4]);
	return new_perm;
}

Perm tof2(const Perm& perm) {
	Perm new_perm(perm);
	int pos6 = new_perm.find('6');
	int pos8 = new_perm.find('8');
	std::swap(new_perm[pos8], new_perm[pos6]);
	return new_perm;
}

Perm tof3(const Perm &perm) {
	Perm new_perm(perm);
	int pos7 = new_perm.find('7');
	int pos8 = new_perm.find('8');
	std::swap(new_perm[pos8], new_perm[pos7]);
	return new_perm;
}

typedef Perm(*Action)(const Perm &);
std::vector<Action> actions = { cn12, cn13, cn23, cn21, cn31, cn32, tof1, tof2, tof3 };
std::vector<std::string> action_names = { "cn12","cn13","cn23","cn21","cn31","cn32","tof1","tof2","tof3" };

Gate init(Perm("12345678"), Path());

VisitTag initVisitTag(const Graph& graph) {
	VisitTag visited;
	for (auto p = graph.begin(); p != graph.end(); p++)
	{
		visited[p->first] = false;
	}
	return visited;
}

Graph getGraph(const Gate &init) {
	Graph graph;
	VisitTag visited;
	std::queue<Gate> Q;
	Q.push(init);
	visited[init] = true;

	while (!Q.empty()) {
		Gate gate = Q.front();
		graph[gate] = std::list<Gate>();
		Q.pop();
		for (int i = 0; i < actions.size(); i++) {
			Gate next(actions[i](gate.perm), gate.actions);
			next.actions.push_back(action_names[i]);
			if (visited.find(next) == visited.end()) {
				graph[gate].push_back(next);
				Q.push(next);
				visited[next] = true;
			}
		}
	}
	return graph;
}

void printActions(const Path& actions) {
	for (int i = 0; i < actions.size(); i++) {
		std::cout << actions[i] << " ";
	}
}

void printGate(const Gate& gate) {
	std::cout << gate.perm << " ";
	printActions(gate.actions);
}

void printGraph(const Graph& graph,const Gate& start) {
	std::queue<Gate> Q;
	Q.push(start);
	while (!Q.empty()) {
		Gate gate = Q.front();
		Q.pop();
		printGate(gate);
		std::cout << std::endl;
		std::list<Gate> list = graph.at(gate);
		auto next = list.begin();
		while (next != list.end()) {
			Q.push(*next);
			next++;
		}
	}
}

int main() {
	Graph graph = getGraph(init);
	printGraph(graph, init);
	return 0;
}


