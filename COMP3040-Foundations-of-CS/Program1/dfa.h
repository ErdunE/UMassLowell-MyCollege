/****************************************************************************
 *
 * File:       	dfa.h
 * Author:     	
 * Revision:
 * Description:
 * Create:     	2019-06-01 14:21:45
 * Modified:   	2019-06-01 14:21:45
 *
 **************************************************************************/
#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

using std::vector;
using std::string;
using std::unordered_map;
using std::cout;
using std::endl;


using StateId =  int;
using StateStr  = string;
using InputT = char;
class CState
{
  public:
    CState();
    CState(unsigned int id,StateStr str);

    // input --> next state
    unordered_map<InputT,StateId> transitions;

    StateStr symbol;
    StateId state_id;  // 0 is invalid state
    void dump(){
      cout<<"{id:"<<state_id<<",str:"<<symbol<<"}"<<endl;}
};


struct TransitionDefine
{
  TransitionDefine(){}

  TransitionDefine(StateId from,InputT input,StateId to)
  :from_state(from)
  ,input(input)
  ,to_state(to)
  {
  }
  StateId from_state;
  InputT input;
  StateId to_state;
  void dump(){
    cout<<"transition:"<<from_state<<" "<<input<<" "<<to_state<<endl;
  }
};

using  TransitionDefines = vector<TransitionDefine>;
using StateMap = unordered_map<StateId,CState>;

class CDFA
{
  public:
    CDFA(const TransitionDefines &transition_defines,const StateMap &state_map,StateId begin_state,vector<StateId> end_state);
    ~CDFA(){}
    void Input(InputT inupt,bool v_flag=false);
    void Reset();
    bool EndState();
  private:
    StateMap m_states;
    StateId m_curr_state;
    vector<StateId> m_end_state;
    StateId m_begin_state;
};
