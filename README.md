# NTUA ECE Programing Languages
A set of 2 algorithmic problems coded in C++ and SML for the Programming Language course in NTUA.

## 1st Problem: Decrypt
In this problem we have to decrypt a message encrypted with the ROTN cipher (where each letter of the message is replaced with the N(nth) next letter) without knowing the N (offset) which is the key of the decryption.


<img width="159" alt="Screen Shot 2022-10-20 at 4 48 56 PM" src="https://user-images.githubusercontent.com/76242811/196966963-5349107d-ba83-429b-87f5-79962df7bef3.png">

To find the key we calculate the entropy of the given encrypted text for every possible offset (for the english alphabet 0<=N<=25) by the following function.


<img width="212" alt="Screen Shot 2022-10-20 at 4 52 14 PM" src="https://user-images.githubusercontent.com/76242811/196967683-cc3adbb7-451f-499f-a841-035600fd125d.png">

Where fn(c) is the frequency of letter c in the message and f(c) is the frequency of the letter c in the English vocabulary.

### The logic behind the solution
We calculate the entropy of the message for every possible offset and get an array with the length of the English alphabet [26]. After that we select the offset (N) that gives us the minimal entropy. Now we have found the offset (N)! Now all we have to do is shift all the letters in message N times left.

The solution was implemented both in C++ and SML.

## 1st Problem: Gas
In this problem we get as input a graph that represents the road grid of some country. Where nodes represent cities and edges represent motorways. Each edge has a weight that represent the liters of gas required to travel between the two cities that the motorway connects (we assume that the graph is connected). The output must be the minimum number of liters of gas required so that we can travel from every city to any other city (assuming that gas stations appear only in cities and not in the motorways).

### The logic behind the solution
The solution is based on a certain variation of the minimal spanning tree problem where we only have to find the maximum weight of the minimal spanning tree's edges.

The solution was implemented both in C++ and SML.
