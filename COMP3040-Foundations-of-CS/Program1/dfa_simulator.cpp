/****************************************************************************
 * Copyright(c) 2019, all rights reserved
 *
 * File:       	dfa_simulator.cpp
 * Author:     	T1035
 * Revision:
 * Description:
 * Create:     	2019-06-21 16:40:27
 * Modified:   	2019-06-21 16:40:27
 *
 **************************************************************************/
#include "dfa.h"
#include "dfa_define_file.h"
#include <iostream>
#include <sstream>
#include <set>
#include <fstream>
#include <string.h>

using std::cout;
using std::endl;
using std::cin;
using std::set;
using std::stringstream;
using std::ifstream;

void Usage(const char* funcname)
{
  stringstream ss;
  ss<<"Usage:\n";
  ss<<"     "<<funcname<<" -d <dfafile> -v\n";
  ss<<"     This is a simple DFA Implementation. The DFA definition\n";
  ss<<"     is specified via .dfa file; input string is read from stdin.\n";
  ss<<"     In non-verbose mode, print ACCEPT or NOT ACCPET as the case may be.\n";
  ss<<"     -h\n";
  ss<<"       print usage\n";
  ss<<"     -d<dfafile>\n";
  ss<<"       DFA definition file\n";
  ss<<"     -v\n";
  ss<<"       verbose mode; display machine definition, transitions etc.\n";
  ss<<"\n";
  ss<<"     Example run in interactive mode:\n";
  ss<<"     $ ./dfa m1.dfa\n";
  ss<<"\n";
  ss<<"     # DFA M1 from Page 36 of ITC Text;\n";
  ss<<"     states: q1 q2 q3\n";
  ss<<"     alphabet: 0 1\n";
  ss<<"     startstate:q1\n";
  ss<<"     finalstate:q2\n";
  ss<<"     transition:q1 0 q1\n";
  ss<<"     transition:q1 1 q2\n";
  ss<<"     transition:q2 0 q3\n";
  ss<<"     transition:q2 1 q2\n";
  ss<<"     transition:q3 0 q2\n";
  ss<<"     transition:q3 1 q2\n";
  ss<<"\n";
  ss<<"     Example run in interactive mode:\n";
  ss<<"     $ ./dfa m1.dfa\n";
  ss<<"     00011\n";
  ss<<"     00011 --> ACCEPT\n";
  ss<<"     00100\n";
  ss<<"     00100 --> ACCEPT\n";
  ss<<"     00000\n";
  ss<<"     00000 --> NOT ACCEPT\n";
  cout<<ss.str();
  exit(0);
}

void err_param(const char *funcname)
{
  stringstream ss;
  ss<<"Param err:\n";
  ss<<"         "<<funcname<<" -h \n";
  ss<<"         "<<"show help\n";
  cout<<ss.str();
  exit(0);
}


void exe_transition(string define_file,bool v_flag)
{
  CDFADefineFile dfa_define(define_file);
  if(false==dfa_define.Init())
  {
    cout<<"PARSE DFA DEFINE FILE FAILED!!!"<<endl;
    exit(0);
  }

  if(true == v_flag)
  {
    cout<<dfa_define<<endl;
  }

  CDFA dfa(dfa_define.transitions,dfa_define.states,dfa_define.begin_state,dfa_define.end_state);
  auto result = [&](string &line,bool v_flag)->string{
    string ret ="";
    dfa.Reset();
    for(auto &c:line)
    {
      if(false == dfa_define.ValidInput(c))
      {
        dfa.Reset();
        ret+="Invalid alphabet:"+std::to_string(c)+"; IGNORING reset of input\n";
        return ret;
        //continue;
      }
      dfa.Input(c,v_flag);
    }
    if(true==dfa.EndState())
    {
      ret+=line+" --> ACCEPT";
    }
    else
    {
      ret+=line+" --> NOT ACCEPT";

    }
    return ret;
  };
  string line;
  while(std::getline(cin,line))
  {
    if(true==line.empty())
    {
      continue;
    }
    cout<<result(line,v_flag)<<endl;
  }
}
int main(int args,const char **argc)
{
  if (args<2)
  {
    Usage(argc[0]);
    return 0;
  }

  int num = args;
  set<char> options={'d','v','h'};
  unordered_map<char,string> options_val;
  for(int i=1;i<num;)
  {
    string prg = string(argc[i]);
    if(prg.size()>2){err_param(argc[0]);}
    if(prg[0]!='-'||prg.size()<2)
    {
      err_param(argc[0]);
    }
    if(options.end()==options.find(prg[1]))
    {
      err_param(argc[0]);
    }
    if('h'==prg[1] && options_val.empty())
    {
      Usage(argc[0]);
    }
    options_val[prg[1]] = (i+1>=args)?"":argc[i+1];
    i +=2;
  }
  exe_transition(options_val['d'],options_val.count('v'));
  return 0;
}
