import numpy as np

def sigmoid(z):
    return 1.0/(1.0+np.exp(-z))

def sigmoid_prime(z):
    return sigmoid(z)*(1-sigmoid(z))

print(sigmoid_prime(np.array([[1, 10, 20, 30, 32, 35, 38, 40]])))


