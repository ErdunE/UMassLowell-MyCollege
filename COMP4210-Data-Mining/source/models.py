import numpy as np
import random
from config import LEARNING_RATE
from formulas import sig, inv_sig, inv_err

curr_node_id = 0

class Layer:
    def __init__(self, num_nodes, input_vals, layer_num):
        self.num_nodes = num_nodes
        self.input_vals = input_vals
        self.layer_num = layer_num
        self.weight = [[random.random() for col in range(len(input_vals))] for row in range(num_nodes)]
        self.weight_delta = [[0 for col in range(len(input_vals))] for row in range(num_nodes)]
        self.layer_net = [0 for col in range(num_nodes)]
        self.layer_out = [0 for col in range(num_nodes)]
        self.bias = (random.random() * 2) - 1

    def eval(self, x):
        #evaluation part
        #Get input, compute the output of layer nodes.
        # raise Exception('Implement this part.')

        # convert to numpy array for matrix operation.
        if type(self.weight)!=np.ndarray:
            self.weight = np.array(self.weight)
            self.layer_net = np.array(self.layer_net).reshape([-1, 1])
        

        x = np.array(x)
        # save the input for backprop
        self.layer_inputs = []
        self.layer_inputs.append(x) 


        # save the hidden for backprop
        hidden1 = self.weight.dot(x)

        # the first layer does not need a output layer, as well as sigmoid activation
        if self.layer_num == 1:
            return hidden1

        # for the second, it has an output layer

        # save the second hidden before matmul
        self.layer_inputs.append(hidden1) 
        hidden2 = self.layer_net.T.dot(hidden1)
        # save the hidden before sigmoid
        self.layer_inputs.append(hidden2) 
        out = sig(hidden2)
        # the final output
        
        # save the final output
        self.layer_out[0] = out
        self.layer_inputs.append(out) 

        return out
        
        
            

    def backprop(self, other):
        #use backpropagation method to update weights
                
        # raise Exception('Implement this part.')

        # for the second layer
        if self.layer_num == 2:
            other = np.array(other)
            
            # inv_err 
            grads = inv_err(self.layer_inputs.pop(-1), other)

            # inv_sig
            grads = grads * inv_sig(self.layer_inputs.pop(-1))


            # for w, the derivative is x,
            # for x, is w
            grads = grads.reshape(-1, 1)
            grads_w = self.layer_inputs.pop(-1).reshape(-1, 1).dot(grads)
            grads_x = self.layer_net.reshape(-1, 1).dot(grads)


            # update the output layer weight, the learning rate is 1e-2
            self.layer_net = self.layer_net - 1e-2 * grads_w.reshape([-1, 1])

            grads = grads_x
        else:
            # get the output grads from last layer
            grads = other.output_grads
            
        
        # get the input
        x = self.layer_inputs.pop(-1).reshape(-1, 1)


        # for w, the derivative is x,
        # for x, is w
        # print(grads.shape, x.shape)
        grads_w = x.dot(grads.T).T
        grads_x = self.weight.T.dot(grads)


        # update w, I set learning rate as 1e-2
        self.weight = self.weight - 1e-2 * grads_w

        # return the gradient for the following layer
        self.output_grads = grads_x
        return grads_x


class cfile(file):
    def __init__(self, name, mode = 'r'):
        self = file.__init__(self, name, mode)

    def w(self, string):
        self.writelines(str(string) + '\n')
        return None
