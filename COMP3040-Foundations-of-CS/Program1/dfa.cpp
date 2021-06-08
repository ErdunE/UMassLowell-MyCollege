/****************************************************************************
 *
 * File:       	dfa.cpp
 * Author:     	
 * Revision:
 * Description:
 * Create:     	2019-06-01 14:22:26
 * Modified:   	2019-06-01 14:22:26
 *
 **************************************************************************/
#include "dfa.h"
#include <algorithm>

CState::CState()
{
  symbol="";
  state_id = 0;
}

CState::CState(unsigned int id,StateStr str)
{
  symbol = str;
  state_id = id;
}

CDFA::CDFA(const TransitionDefines &transition_defines,const StateMap &state_map,StateId begin_state,vector<StateId> end_state)
{
  m_states = state_map;
  m_curr_state = m_begin_state= begin_state;
  m_end_state = end_state;

  for(auto &transition :transition_defines)
  {
    m_states[transition.from_state].transitions[transition.input] = transition.to_state;
  }
}

void CDFA::Input(InputT input,bool v_flag)
{
  if(true == v_flag)
  {
    cout<<"Current State: "<<m_states[m_curr_state].symbol+" Symbol: "<<input<<" -> New State: ";
  }
  m_curr_state = m_states[m_curr_state].transitions[input];
  if(true == v_flag)
  {
    cout<<m_states[m_curr_state].symbol<<endl;
  }
}

void CDFA::Reset()
{
  m_curr_state = m_begin_state;
}

bool CDFA::EndState()
{
  //return m_end_state.end() != m_end_state.find(m_curr_state);
  return m_end_state.end() != std::find(m_end_state.begin(),m_end_state.end(),m_curr_state);
  //return m_curr_state == m_end_state;
}
