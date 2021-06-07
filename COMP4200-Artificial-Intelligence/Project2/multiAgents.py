# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        
        minFoodist = float("inf")
        ghost_position = successorGameState.getGhostPositions()
        food_list = successorGameState.getFood().asList()
        
        for food in food_list:
            minFoodist = min(minFoodist, manhattanDistance(newPos, food))

        for ghost in ghost_position:
            if (manhattanDistance(newPos, ghost) < 2):
                return -float('inf')
                
        score = successorGameState.getScore() + 1.0/minFoodist
        return score


def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        self_max_value = self.max_value(gameState, 0, 0)[0]
        return self_max_value

    def minimax(self, gameState, agentIndex, depth):
        if depth is self.depth * gameState.getNumAgents() \
                    or gameState.isLose() or gameState.isWin():
            self_evaluation = self.evaluationFunction(gameState)
            return self_evaluation
        if agentIndex is 0:
            return self.max_value(gameState, agentIndex, depth)[1]
        else:
            return self.min_value(gameState, agentIndex, depth)[1]

    def max_value(self, gameState, agentIndex, depth):
        value = ("max",-float("inf"))
        for action in gameState.getLegalActions(agentIndex):
            successor_state = (action,self.minimax(gameState.generateSuccessor(agentIndex,action),
                                        (depth + 1)%gameState.getNumAgents(),depth+1))
            value = max(value,successor_state,key=lambda x:x[1])
        return value

    def min_value(self, gameState, agentIndex, depth):
        value = ("min",float("inf"))
        for action in gameState.getLegalActions(agentIndex):
            successor_state = (action,self.minimax(gameState.generateSuccessor(agentIndex,action),
                                        (depth + 1)%gameState.getNumAgents(),depth+1))
            value = min(value,successor_state,key=lambda x:x[1])
        return value

       
class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        self_max_value = self.max_value(gameState, 0, 0, -float("inf"), float("inf"))[0]
        return self_max_value

    def alphabeta(self, gameState, agentIndex, depth, alpha, beta):
        if depth is self.depth * gameState.getNumAgents() \
                or gameState.isLose() or gameState.isWin():
            self_evaluation = self.evaluationFunction(gameState)
            return self_evaluation
        if agentIndex is 0:
            return self.max_value(gameState, agentIndex, depth, alpha, beta)[1]
        else:
            return self.min_value(gameState, agentIndex, depth, alpha, beta)[1]

    def max_value(self, gameState, agentIndex, depth, alpha, beta):
        value = ("max",-float("inf"))
        for action in gameState.getLegalActions(agentIndex):
            successor_state = (action,self.alphabeta(gameState.generateSuccessor(agentIndex,action),
                                      (depth + 1)%gameState.getNumAgents(),depth+1, alpha, beta))
            value = max(value,successor_state,key=lambda x:x[1])
            if value[1] > beta: return value
            else: alpha = max(alpha,value[1])

        return value

    def min_value(self, gameState, agentIndex, depth, alpha, beta):
        value = ("min",float("inf"))
        
        for action in gameState.getLegalActions(agentIndex):
            successor_state = (action,self.alphabeta(gameState.generateSuccessor(agentIndex,action),
                                      (depth + 1)%gameState.getNumAgents(),depth+1, alpha, beta))
            value = min(value,successor_state,key=lambda x:x[1])

            if value[1] < alpha:
                return value
            else:
                beta = min(beta, value[1])

        return value
        util.raiseNotDefined()

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        max_depth = self.depth * gameState.getNumAgents()
        self_expectimax = self.expectimax(gameState, "expect",max_depth, 0)[0]
        return self_expectimax

    def expectimax(self, gameState, action, depth, agentIndex):
        if depth is 0 or gameState.isLose() or gameState.isWin():
            return (action, self.evaluationFunction(gameState))
        if agentIndex is 0:
            return self.max_value(gameState,action,depth,agentIndex)
        else:
            return self.exp_value(gameState,action,depth,agentIndex)

    def max_value(self,gameState,action,depth,agentIndex):
        value = ("max", -(float('inf')))
        for legalAction in gameState.getLegalActions(agentIndex):
            nextAgent = (agentIndex + 1) % gameState.getNumAgents()
            successor_action = None
            if depth != self.depth * gameState.getNumAgents():
                successor_action = action
            else:
                successor_action = legalAction
            successor_value = self.expectimax(gameState.generateSuccessor(agentIndex, legalAction),
                                        successor_action,depth - 1,nextAgent)
            value = max(value,successor_value,key = lambda x:x[1])
        return value

    def exp_value(self,gameState,action,depth,agentIndex):
        legalActions = gameState.getLegalActions(agentIndex)
        score = 0
        propability = 1.0/len(legalActions)
        for legalAction in legalActions:
            nextAgent = (agentIndex + 1) % gameState.getNumAgents()
            value = self.expectimax(gameState.generateSuccessor(agentIndex, legalAction),
                                            action, depth - 1, nextAgent)
            score += value[1] * propability
        return (action, score)

import math
        

def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    
    
    new_pos = currentGameState.getPacmanPosition()
    new_food = currentGameState.getFood().asList()
    mininum_foodist = float('inf')
    
    for food in new_food:
        mininum_foodist = min(mininum_foodist, manhattanDistance(new_pos, food))
    ghost_distance = 0
    
    for ghost in currentGameState.getGhostPositions():
        ghost_distance = manhattanDistance(new_pos, ghost)
        if (ghost_distance < 2):
            return -float('inf')

    food_left = currentGameState.getNumFood()
    caps_left = len(currentGameState.getCapsules())
    food_leftMultiplier = 950050
    caps_leftMultiplier = 10000
    food_distMultiplier = 950
    additional_factors = 0
    
    if currentGameState.isLose():
        additional_factors -= 50000
    elif currentGameState.isWin():
        additional_factors += 50000
    return 1.0/(food_left + 1) * food_leftMultiplier + ghost_distance + \
           1.0/(mininum_foodist + 1) * food_distMultiplier + \
           1.0/(caps_left + 1) * caps_leftMultiplier + additional_factors

better = betterEvaluationFunction
