#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdio>ç

using namespace std;

// Estrutura para guardar os dados de cada combinação
struct Subcombination{
    int result;
    int division_index;
    int left_operand;
    int right_operand;
};

//Funçaõ para reconstruir a expressão
string reconstruct(int left, int right, int res, const vector<vector<vector<Subcombination>>>& details) {
    //Ve cada possível combinação no intervalo dado 
    for (const auto& sub : details[left][right]) { //n
        if (sub.result == res) {//Se é o resultado esperado
            if (sub.division_index == -1) {
                return to_string(res); // Caso base, número único
            }
            //Recursivamente, divide o problema em esquerda e direita, até chegar ao caso base
            string leftExpr = reconstruct(left, sub.division_index, sub.left_operand, details);//arvore binaria m
            string rightExpr = reconstruct(sub.division_index + 1, right, sub.right_operand, details);

            // Adiciona os parentesis 
            return "(" + leftExpr + " " + rightExpr + ")";
        }
    }
    return ""; // Caso inválido (não deve ocorrer, só para o compilador não reclamar)
}


bool algorithm(const vector<vector<int>>& table, const vector<int>& sequence, int result, string& full_answer){
    int s = sequence.size();
    int n = table.size();

    //Matriz com unordered_maps para resultados únicos
    vector<vector<unordered_map<int, int>>> resultsMap(s, vector<unordered_map<int, int>>(s));
    //será do tamanho mxm sendo m o tamanho da sequencia

    //Matriz com a estrutura detalhada
    vector<vector<vector<Subcombination>>> details(s, vector<vector<Subcombination>>(s));
    //esta matriz guarda só dados de cada combinação para depois reconstruir

    //Preencher a diagonal principal
    for (int i = 0; i < s; ++i){
        resultsMap[i][i][sequence[i]] = 1; //O numero 1 significa que  o resultado existe
        details[i][i].push_back({sequence[i], -1, -1, -1}); //O -1 significa que não há divisão
    }

    for (int len = 2; len <= s; ++len){ //m
        for (int left = 0; left <= s - len; ++left){ //m
            //O paramatro s - len determina o numero de diferentes sub-sequencias de tamanho len
            //que podemos criar a partir da sequencia original
            //Vai pelas diagonais
            int right = left + len - 1; //Indice da direita
            for (int i = right - 1; i >= left; --i){
                //i é o indice de divisão, e vai de direita a esquerda de forma a concentrar
                //os parentesis à esquerda

                // Já tenho n resultados, passa para a próxima entrada
                if (resultsMap[left][right].size() >= static_cast<size_t>(n)) {
                    break;
                }
                for (Subcombination& subleft : details[left][i]) { //n espaços, pior caso itera tudo
                    //Todas as combinações possíveis à esquerda
                    for (Subcombination& subright : details[i + 1][right]) {// n espaços, pior caso itera tudo
                        //Todas as combinações possíveis à direita
                        int temp_result = table[subleft.result - 1][subright.result - 1]; // Resultado da combinação

                        // Só guarda uma vez cada resultado
                        if (resultsMap[left][right].find(temp_result) == resultsMap[left][right].end()) {
                            //É a primeira vez, nesta sequencia de sub-problemas, que o valor combinado aparece
                            resultsMap[left][right][temp_result] = 1; // Marca o resultado como existente
                            details[left][right].push_back({temp_result, i, subleft.result, subright.result});
                        }
                    }
                }
            }
        }
        

    
    }
    // Final
        const auto& finalResults = resultsMap[0][s - 1]; // Canto superior direito
        if (finalResults.find(result) != finalResults.end() && finalResults.at(result) == 1) { // Existe
           full_answer = reconstruct(0, s - 1, result, details);
            return true;
        }
    return false;
}



int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, s;
    //L~e o tamanhop da tablea de operandos e o tamanho da seuqencia
    if (scanf("%d %d", &n, &s) != 2) {
        printf("Error reading input\n");
        return 1;
    }

    vector<vector<int>> table(n, vector<int>(n));
    //Aloca a tabela de operandos
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (scanf("%d", &table[i][j]) != 1) {
                printf("Error reading table input\n");
                return 1;//Inicializa a tabela
            }

    //A sequencia
    vector<int> sequence(s);
    for (int i = 0; i < s; ++i)
        if (scanf("%d", &sequence[i]) != 1) {
            printf("Error reading sequence input\n");
            return 1;//Inicializa a sequencia
        }

    int result; //Resultado esperado
    if (scanf("%d", &result) != 1) {
        printf("Error reading result input\n");
        return 1;
    }

    string full_answer;

    if (algorithm(table, sequence, result, full_answer)) {
        //Esta função irá retornar true caso encontre a solução, e false caso contrário
        //Tornará a string full_answer na resposta correta
        printf("%d\n", 1);
        printf("%s\n", full_answer.c_str());
    } else {
        printf("%d\n", 0);
    }

    return 0;
}