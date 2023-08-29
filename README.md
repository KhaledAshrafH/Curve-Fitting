# Curve Fitting Genetic Algorithm

This program implements a genetic algorithm for curve fitting using a polynomial equation. The goal is to find the best coefficients for the polynomial equation that minimize the distance between the curve and a given set of data points. The genetic algorithm is used to search for the optimal solution by evolving a population of candidate solutions.

## Input Format

The input file should have the following format:

```
Number of datasets
Number of data points and polynomial degree for each dataset
x-coordinate and y-coordinate for each data point
```

For example:

```
1

4 2

1 5
2 8
3 13
4 20
```

This example represents one dataset with 4 data points and a polynomial degree of 2. The data points are (1, 5), (2, 8), (3, 13), and (4, 20).

## Chromosome Encoding and Objective Function

The solution is encoded as a chromosome using a floating-point representation of the polynomial coefficients. The genes represent the coefficients of the polynomial equation.

The objective function is the mean square error between the curve defined by the polynomial equation and the given data points. The fitness of a chromosome is calculated as the inverse of the total error, with higher fitness indicating a better solution.

## Genetic Algorithm Parameters

The following parameters are used in the genetic algorithm:

- Population size (`populationSize`): The number of chromosomes in each population.
- Number of iterations (`numOfIterations`): The maximum number of generations the algorithm will run.
- Crossover probability (`Pc`): The probability of performing crossover during reproduction.
- Mutation probability (`Pm`): The probability of performing mutation on a chromosome.

## Genetic Algorithm Steps

The genetic algorithm follows these steps:

1. **Initialization**: Initialize the population of chromosomes with random coefficients within the range \[-10, 10\].
1. **Individual Evaluation**: Calculate the fitness of each chromosome by evaluating the mean square error between the curve defined by the polynomial equation and the data points.
1. **Selection**: Select the best chromosomes from the population using tournament selection.
1. **Crossover**: Apply crossover between selected chromosomes with a probability of `Pc`.
1. **Mutation**: Perform mutation on the offspring chromosomes with a probability of `Pm`. The mutation is non-uniform, and the range of the mutation depends on the current iteration.
1. **Reproduction**: Replace the current population with the offspring chromosomes, preserving the best solutions using elitism.
1. Repeat steps 2 to 6 for the specified number of iterations.
1. Sort the final population based on fitness and output the best solution for each dataset.

## Output Format

The program outputs the results for each dataset, including the dataset index, the coefficients of the polynomial equation, and its mean square error. The output format is as follows:

```
Testcase <dataset index>:
The Coefficients: [ <coefficient1> , <coefficient2> , ... ]
Mean Square Error: <mean square error>
```

For example:

```
Testcase 1:
The Coefficients: [ 2.48 , 0.95 , 0.05 ]
Mean Square Error: 0.32456789012345678900
```

## Running the Program

To run the program, make sure you have the input file in the specified format. You can modify the input file directly or create a new file. Additionally, ensure that the necessary libraries are included, such as `<bits/stdc++.h>`.

Compile and run the program, and the results will be written to the output file specified in the code (`output.txt` in this case).

## Conclusion

The curve fitting genetic algorithm implemented in this program utilizes tournament selection, 2-point crossover, non-uniform mutation, and elitist replacement to find the best coefficients for a polynomial equation that minimizes the distance to given data points. By adjusting the parameters of the genetic algorithm, such as population size and number of iterations, you can explore different trade-offs between exploration and exploitation in the search for the optimal solution. The genetic algorithm provides an effective approach for solving curve fitting problems by iteratively evolving a population of candidate solutions to improve the fitness and convergence towards the optimal solution.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvement, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE.md).
