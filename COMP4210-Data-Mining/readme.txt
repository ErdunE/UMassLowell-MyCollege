Name: Erdun E
Course: COMP 5440, COMP 4210 Data Mining Fall 2020
instructor:Tingjian Ge
Assignment Name: Final Project

Project description:

## Implementation
The model consists two layers: the first one does not has an activation, as the sigmoid activation may hinder back-propagation. 
The second one has an additional output layer, which leverages sigmoid as activation.

## Performance
The error rate on training set is 0.03748
The error rate on testing set is  0.00246

## Dataset
I randomly split the dataset into three groups: Train:Test:Val = 7:2:1

## Run
python proj_test.py

## Dependencies
Python 2.7.3
Numpy