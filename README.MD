# Genetic Algorithm to solve TSP

## Project requirements

1. Implement Specimen
   - Specimen genes should be a list of next city to visit
   - Specimen should be able to mutate
   - Specimen should be able to calculate fitness
2. Implement Population
   - Population should hold list of cities, possible connections and distances
   - Population should be able to generate random Specimens
   - Population should crossover based on single specimen fitness
   - Population should be able to mutate
   - Population should be able to calculate fitness
     - if connection is not possible, cost of that route should be greatly increased
     - Specimen can not be best if it has invalid connections
   - Population should be able to evolve
   - Population should be able to hold and return best specimen
3. Implement TSP
   - Read cities, connections and distances from file
   - Generate random cities, connections and distances
   - Pass data to Population