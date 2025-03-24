import pulp
from pulp import GLPK_CMD

def parse_input():
    n, m, t = map(int, input().split())

    factories = {}
    for i in range(n):
        index, country, maxf = map(int, input().split())
        if maxf > 0:
            factories[index] = [country, maxf]
        else:
            continue

    countries = {}
    for i in range(m):
        index, pmax, pmin = map(int, input().split())
        countries[index] = [pmax, pmin]

    kids = {}
    for i in range(t):
        data = list(map(int, input().split()))
        index = data[0]
        country = data[1]
        toys = data[2:]
        kids[index] = [country, toys]

    return factories, countries, kids

def problem_solver(factories, countries, kids):
    # Define Problem
    prob = pulp.LpProblem("Toy_Distribution", pulp.LpMaximize)

    # Decision Variables
    x = pulp.LpVariable.dicts("x", ((k, i) for k in kids for i in kids[k][1]), cat=pulp.LpBinary)

    # Objective: Maximize the number of kids satisfied
    prob += pulp.lpSum(x[k, i] for k in kids for i in kids[k][1]), "Maximize_Distribution"

    # Constraints
    #CERTA
    for factory in factories:
        fmax = factories[factory][1]
        prob += pulp.lpSum(x[k, i] for k in kids for i in kids[k][1] if factory == i) <= fmax, f"Max_Factory_Production_{factory}"

    #CERTA
    for kid in kids:
        prob += pulp.lpSum(x[kid, i] for i in kids[kid][1]) <= 1, f"One_Toy_Per_Kid_{kid}"

    for country in countries:
        pmin = countries[country][1]
        kids_in_country = [k for k in kids if kids[k][0] == country]
        if not kids_in_country:
            continue
        prob += pulp.lpSum(x[k, i] for k in kids_in_country for i in kids[k][1]) >= pmin, f"Min_Toy_Per_Country_{country}"
        # prob += pulp.lpSum(x[k, i] for f in factories_in_country for k in kids for i in kids[k][1] if i == f) <= countries[country][0], f"Max_Toy_Per_Country_{country}"

    #REGALOS EXPORTADOSSSSSS SI EL CARAJITO ES DEL PAIS NO CUENTAAAAAAAA
    for country in countries:
        pmax = countries[country][0]
        factories_in_country = [f for f in factories if factories[f][0] == country]
        if not factories_in_country:
            continue
        prob += pulp.lpSum(x[k, i] for k in kids for i in kids[k][1] if i in factories_in_country and kids[k][0] != country) <= pmax, f"Max_Toy_Per_Country_{country}"

    solver = GLPK_CMD(msg=False)
    status = prob.solve(solver)

    if status != 1:
        return -1
    else:
        return int(prob.objective.value())

# Main
def main():
    factories, countries, children = parse_input()
    print(problem_solver(factories, countries, children))

main()
