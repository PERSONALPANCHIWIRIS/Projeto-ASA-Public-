#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

struct Edge{
    int line_id;
    unordered_set<int> stations;
    unordered_set<int> adjacencies;
};

class Grid{
    private:
    //Um mapa onde a chave é o id de cada vetor e contem um vetor das adjacencias desse vetor
        unordered_map<int, Edge> grid;
    public:
    void addStation(int station, int dest, int line_id){
        grid[line_id].stations.insert(station);
        grid[line_id].stations.insert(dest);
    }

    unordered_map<int, Edge> getGrid(){
        return grid;
    }

    void addAdjacencies(int line_1, int line_2){
        grid[line_1].adjacencies.insert(line_2);
        grid[line_2].adjacencies.insert(line_1);
    }

    int countStations(){
        unordered_set<int> all_stations;
        for (auto entry : grid){
            for (int station : entry.second.stations){
                all_stations.insert(station);
            }
        }
        return all_stations.size();
    }
};

//Ve se duas linhas têm estações em comum
bool commonStations(unordered_set<int>& stations1, unordered_set<int>& stations2){
    for (int station : stations1){
        if (stations2.find(station) != stations2.end()){
            return true;
        }
    }
    return false;
}

int BFS(Grid lines_grid){
    if (lines_grid.getGrid().empty()) return 0; //para um grid vazio, não executa a BFS

        
        int max_steps = 0;                           //esta variave será o max(MC)
        auto grid = lines_grid.getGrid();           //obtem o grid
        unordered_map<int, bool> visited;

        //Realiza a BFS para cada vertice do grafo, mantendo o numero maximo de passos
        for (const auto& startNode : grid) {
            queue<pair<int, int>> q; // Pair: <vertice, distancia>
            visited.clear(); // Inicializa o vetor de visitados
            q.push({startNode.first, 0});
            visited[startNode.first] = true;

            while (!q.empty()) {
                int current = q.front().first;
                int distance = q.front().second;
                q.pop();

                //Atualiza o maximo de passos
                max_steps = max(max_steps, distance);

                //Ve todos os vizinhos e, dependedo da distancia, adiciona-os à fila
                unordered_set<int> adjacencies = grid.at(current).adjacencies;
                for (int neighbor : adjacencies) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push({neighbor, distance + 1});
                    }
                }
            }
        }
        return max_steps;
}

int solve_MC(Grid lines_grid){
    for (auto entry : lines_grid.getGrid()){
        for (auto entry2 : lines_grid.getGrid()){        
            if (entry.first == entry2.first){
                continue;
            }

            if (commonStations(entry.second.stations, entry2.second.stations)){
                lines_grid.addAdjacencies(entry.first, entry2.first);
            }
        }
    }
    int line_changes = BFS(lines_grid);
    return line_changes;
}


int main(){
    Grid lines_grid;
    int station_num, connections_num, lines_num;
    unordered_map<int, int> stations_for_line;
    //Leitura da primeira linha do input
    if (scanf("%d %d %d", &station_num, &connections_num, &lines_num) != 3){
        printf("Error reading input\n");
        return 1;
    }

    //leitura das linhas de metro
    for (int i = 0; i < connections_num; i++){
        int station, dest, line_id;
        if (scanf("%d %d %d", &station, &dest, &line_id) != 3){
            printf("Error reading first line of input\n");
            return 1;
        }
        //Ainda esta linha não foi registada
        if (stations_for_line.find(line_id) == stations_for_line.end()){
            stations_for_line[line_id] = 1;
        }
        stations_for_line[line_id]++;
        lines_grid.addStation(station, dest, line_id);
    }

    for (auto entry : stations_for_line){
        //Uma linha de metro com uma unica estação
        if (entry.second == 1){
            printf("%d\n", -1);
            return 0;
        }

        //Uma linha de metro com todas as estações
        if (entry.second == station_num){
            printf("%d\n", 0);
            return 0;
        }
    }

    //Ver se o grafo é conexo
    if (connections_num < (station_num - 1)){
        printf("%d\n", -1);
        return 0;
    }

    //verificação de uma estação estar fora das linhas de metro
    if (lines_grid.countStations() < station_num){
        printf("%d\n", -1);
        return 0;
    }

    //output do MC
    int MC = solve_MC(lines_grid);
    printf("%d\n", MC);

    return 0;
}