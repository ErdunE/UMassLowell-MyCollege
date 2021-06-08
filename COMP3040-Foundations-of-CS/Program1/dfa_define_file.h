/****************************************************************************
 *
 * File:       	dfa_define_file.h
 * Author:     	
 * Revision:
 * Description:
 * Create:     	2019-06-02 13:53:52
 * Modified:   	2019-06-02 13:53:52
 *
 **************************************************************************/
#pragma once

#include <fstream>
#include <string>
#include <set>
#include "dfa.h"
#include <vector>
#include <ostream>


using std::ifstream;
using std::string;
using std::set;
using std::vector;
using std::ostream;
class CDFADefineFile
{

  friend ostream & operator<<(ostream &out,CDFADefineFile &define);
  public:
    CDFADefineFile(const string file)
    :m_file(file)
    {
      m_lines_prefix={"states","alphabet","startstate","finalstate","transition"};
    }
    bool Init();
    TransitionDefines transitions;
    StateMap states;
    StateId begin_state;
    vector<StateId> end_state;
    set<InputT> inputs;
    bool ValidInput(InputT );
    static vector<string> Split_space(const string &,const string&);
    string Dump();
  private:
    void trim(string &str);
    bool read_file();
    void handle_line(string &line);
    void handle_states_line( const vector<string>& );
    void handle_alphabet_line( const  vector<string>& );
    void handle_startstate_line( const vector<string>& );
    void handle_finalstate_line( const vector<string>& );
    void handle_transition_line( const vector<string>& );
    StateId GetStateId(string str);
    vector<vector<string>> m_transitions;

  private:
    set<string> m_lines_prefix;
    string m_file;
    string m_s_begin_state;
    vector<string> m_s_end_state;
};
