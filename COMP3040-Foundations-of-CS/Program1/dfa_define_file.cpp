/****************************************************************************
 *
 * File:       	dfa_define_file.cpp
 * Author:     	
 * Revision:
 * Description:
 * Create:     	2019-06-02 14:05:23
 * Modified:   	2019-06-02 14:05:23
 *
 **************************************************************************/
#include "dfa_define_file.h"
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::stringstream;



bool CDFADefineFile::Init()
{
  bool ret= read_file();
  if(false ==ret)
  {
    return ret;
  }
  if(states.empty())
  {
    cout<<" err dfa define,need states define"<<endl;
    return false;
  }
  if(inputs.empty())
  {
    cout<<" err dfa define,need input define"<<endl;
    return false;
  }
  if(m_s_begin_state.empty()||m_s_end_state.empty())
  {
    cout<<" err dfa define,need define startstate and finalstate"<<endl;
    return false;
  }
  if(m_transitions.empty())
  {
    cout<<" err dfa define,need define transition"<<endl;
    return false;
  }
  bool have_begin=false;
  bool have_end =false;
  for( auto &elem :states )
  {
    if(elem.second.symbol==m_s_begin_state)
    {
      begin_state = elem.first;
      have_begin = true;
    }
    //if(elem.second.symbol == m_s_end_state)
    //{
      //end_state = elem.first;
      //have_end = true;
    //}
  }
  have_end = true;
  for(auto s : m_s_end_state)
  {
    have_end = true;
    int id = GetStateId(s);
    if(-1==id)
    {
      have_end = false;
      break;
    }
    end_state.push_back(id);
  }
  if(have_begin==false||have_end==false)
  {
    cout<<"errr dfa define,startstate or finalstate define err"<<endl;
    return false;
  }

  for(auto &elem :m_transitions)
  {
    StateId b,e;
    InputT input = static_cast<InputT>(elem[1][0]);
    if(inputs.find(input)==inputs.end())
    {
      cout<<"errr dfa define,transition define err: input err"<<endl;
      return false;
    }
    b = GetStateId(elem[0]);
    e = GetStateId(elem[2]);
    if(b==-1||e==-1)
    {
      cout<<"errr dfa define,transition define err: state err"<<endl;
      return false;
    }
    transitions.push_back(TransitionDefine(b,input,e));
  }

  //for(auto &elem:states)
  //{
    //elem.second.dump();
  //}
  //cout<<"alphabet:";
  //for(auto &elem:inputs)
  //{
    //cout<<elem<<" ";
  //}
  //cout<<endl;
  //cout<<"startstate:"<<begin_state<<endl;
  //cout<<"finalstate:"<<end_state<<endl;
  //for(auto &elem:transitions)
  //{
    //elem.dump();
  //}

  return true;
}
StateId CDFADefineFile::GetStateId(string str)
{
  for(auto &elem:states)
  {
    if(elem.second.symbol==str)
    {
      return elem.first;
    }
  }
  return -1;
}

bool CDFADefineFile::read_file()
{
  if(true==m_file.empty())
  {
    cout<<" must have a dfa file"<<endl;
    return false;
  }
  ifstream fin;
  fin.open(m_file,std::ios::in);
  if(false == fin.is_open())
  {
    cout<<"  open file: "<<m_file<<" failed"<<endl;
    return false;
  }
  string line;
  while(std::getline(fin,line)){
    handle_line(line);
  }
  return true;
}

void CDFADefineFile::handle_line(string &line)
{
  if(true == line.empty())
  {
    return;
  }
  trim(line);
  if(line[0]=='#')
  {
    return;
  }

  size_t index = line.find_first_of(":");
  if(std::string::npos==index)
  {
    return ;
  }
  string line_left = line.substr(0,index);
  string line_right = line.substr(index+1);
  trim(line_left);
  trim(line_right);

  if (m_lines_prefix.find(line_left)==std::end(m_lines_prefix))
  {
    return ;
  }
  //cout<<"read: "<<line_left<<endl;
  //cout<<"read: "<<line_right<<endl;
  if("states"==line_left)
  {
    handle_states_line(Split_space(line_right," "));
  }

  if("alphabet"==line_left)
  {
    handle_alphabet_line(Split_space(line_right," "));
  }

  if("startstate"==line_left)
  {
    handle_startstate_line(Split_space(line_right," "));
  }
  if("finalstate"==line_left)
  {
    handle_finalstate_line(Split_space(line_right," "));
  }
  if("transition"==line_left)
  {
    handle_transition_line(Split_space(line_right," "));
  }
}

vector<string> CDFADefineFile::Split_space(const string &str,const string &pattern)
{
  vector<string>ret;
  if(pattern.empty()||str.empty())
  {
    return ret;
  }
  string ::size_type start=0,curr = str.find_first_of(pattern);
  for(;curr!=std::string::npos;)
  {
    if( curr != start )
    {
      ret.push_back(str.substr(start,curr-start));
    }
    start = curr+1;
    curr = str.find_first_of(pattern,start);
  }
  if(false == str.substr(start).empty())
  {
    ret.push_back(str.substr(start));
  }
  return ret;
}

void CDFADefineFile::handle_states_line(const vector<string>&splits)
{
  if(splits.empty())
  {
    return;
  }
  int id=0;
  set<string>set_splits;
  for(auto &elem:splits)
  {
    set_splits.insert(elem);
  }

  for(auto &elem:set_splits)
  {
    states[id]= CState(id,elem);
    id++;
  }
  return;
}
void CDFADefineFile::handle_alphabet_line(const vector<string>&splits)
{
  if(splits.empty())
  {
    return;
  }
  set<string>set_splits;
  for(auto &elem:splits)
  {
    set_splits.insert(elem);
  }

  for(auto &elem :set_splits)
  {
    inputs.insert(elem[0]);
  }
  return;
}
void CDFADefineFile::handle_startstate_line(const vector<string>&splits)
{
  if(splits.empty())
  {
    return;
  }
  m_s_begin_state=splits[0];
  return ;
}
void CDFADefineFile::handle_finalstate_line(const vector<string>&splits)
{
  if(splits.empty())
  {
    return;
  }
  m_s_end_state = splits;
  return ;
}
void CDFADefineFile::handle_transition_line(const vector<string>&splits)
{
  if(splits.empty())
  {
    return;
  }
  if(splits.size()!=3)
  {
    cout<<" err dfa define,transition define err,transition: curr_state input next_state"<<endl;
    exit(0);
  }
  m_transitions.push_back(splits);
  return ;
}

void CDFADefineFile::trim(string &str)
{
  str.erase(0,str.find_first_not_of(" "));
  str.erase(str.find_last_not_of(" ")+1);
}

bool CDFADefineFile::ValidInput(InputT input )
{
  return inputs.find(input)!=inputs.end();
}

string CDFADefineFile::Dump()
{
  stringstream ss;
  ss<<"---BEGIN DFA definition---"<<endl;
  ss<<"States:"<<endl;
  for(auto &elem:states)
  {
    ss<<"  "<<elem.second.symbol<<" ";
  }
  ss <<endl;
  ss <<"Alphabet:"<<endl;
  for(auto &elem:inputs)
  {
    ss <<"  "<<elem<<" ";
  }
  ss<<endl;
  ss<<"StartState: "<<m_s_begin_state<<endl;;
  ss<<"FinalState: ";
  for(auto s:m_s_end_state)
  {
    ss<<s;
  }
  ss<<endl;
  ss<<"Transitions:"<<endl;
  for(auto &elem:transitions)
  {
    ss<<"  "<<states[elem.from_state].symbol<<" "<<elem.input<<" "<<states[elem.to_state].symbol<<endl;
  }
  ss<<"---END DFA definition---";
  return ss.str();
    
}

ostream & operator<<(ostream &out,CDFADefineFile &define)
{
  out<<define.Dump();
  return out;
}
