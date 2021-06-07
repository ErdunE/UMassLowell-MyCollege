'''
Author: your name
Date: 2020-10-23 09:06:48
LastEditTime: 2020-10-23 20:59:22
LastEditors: Please set LastEditors
Description: In User Settings Edit
FilePath: \assignments\ShallowNeuralNetworks\source\formulas.py
'''
import math
import numpy as np

def sig(x):
    #use logistic function as activation function
    # raise Exception('Implement this part.')
    # print(x)

    # I use standard sigmoid function as the logistic function
    return 1./(1.+np.exp(-x))

def inv_sig(x):
    #derivative of the output of neruon with respect to its input
    # raise Exception('Implement this part.')

    # the derivative is :
    return sig(x) * (1.-sig(x))

def err(o, t):
    #squared error function, o is the actual output value and t is the target output 
    # raise Exception('Implement this part.')

    # the square error is the square of the difference between the output and target.
    return (o-t)**2

def inv_err(o, t):
    #derivative of squared error function with respect to o
    # raise Exception('Implement this part.')

    # the derivative is very simple:
    return 2.*(o-t)*1.


