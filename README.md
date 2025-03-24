# Projeto-ASA-Public
Desenvolvimento, em diferentes linguagens, de algoritmos de forma a resolução de diferentes problemas computacionais, implementando técnicas de tratamento, síntese e análise de algoritmos e estruturas de dados

# P1 - Projeto Arqueológico e Otimização de Transporte e Distribuição

Tabelas de Operadores Binários e Parênteses

Utilização de tabelas que descrevem operações binárias. O problema consiste em automatizar a colocação de parênteses nas sequências de operações para obter o resultado desejado.

# Objetivo:

Desenvolver um algoritmo que insira parênteses de forma correta nas sequências de operações binárias, como exemplificado abaixo:

### Operador ⊕:

| ⊕   | **1**   | **2**   | **3**   |
| --- | --- | --- | --- |
| **1**   | 2   | 2   | 1   |
| **2**   | 3   | 2   | 1   |
| **3**   | 1   | 3   | 3   |


Exemplo de Sequência:

2 ⊕ 2 ⊕ 2 ⊕ 2 ⊕ 1 ⊕ 3 = 1

Uma das possíveis maneiras de colocar os parênteses seria:

((((2 ⊕ 2) ⊕ 2) ⊕ (2 ⊕ 1)) ⊕ 3) = 1

# Tecnologias:

    Python

# P2 - Análise de Conectividade da Rede de Transporte Urbano

# Objetivo:

Calcular o índice de conectividade da rede de metro, onde:

mc = max{ML(e1, e2) | e1, e2 ∈ Metro}

Aqui, ML(e1, e2) denota o número mínimo de mudanças de linha necessárias para viajar entre as estações e1 e e2.
# Tecnologias:

    Python

    Algoritmos de grafos

# P3 - Distribuição de Brinquedos de Natal

# Objetivo:

Desenvolver uma solução de programação linear para otimizar a distribuição de brinquedos de forma a atender as demandas das crianças, respeitar os limites de estoque das fábricas, e atender aos requisitos de distribuição por país.
Restrições:

    Cada fábrica fi tem um estoque máximo de brinquedos fmaxi.

    Cada país pj tem um número mínimo de brinquedos a serem entregues pminj e um número máximo de brinquedos exportados pmaxj.

    Cada criança pode receber no máximo um brinquedo de um conjunto solicitado.

Tecnologias:

    Python

    PuLP (Biblioteca para Programação Linear)
