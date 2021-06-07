#include <iostream>
#include <string>
#include <fstream>
#include <boost/regex.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"


using std::cout;
using std::cin;
using std::endl;
using std::string;

using boost::regex;
using boost::smatch;
using boost::regex_error;

using boost::gregorian::date;
using boost::gregorian::from_simple_string;
using boost::gregorian::date_period;
using boost::gregorian::date_duration;

using boost::posix_time::ptime;
using boost::posix_time::time_duration;


int main(int argc, char **args)
{
    if (argc != 2)
    {
        cout << "usage: ./ps7 [logfile]" << endl;
        exit(1);
    }
    string s, rs;
    regex e1;
    regex e2;
    bool flag = false;
    ptime t1, t2;
    string filename(args[1]);
    std::ifstream infile(filename);
    std::ofstream outfile(filename + ".rpt");
    if (!infile || !outfile)
    {
        cout << "open file error" << endl;
        exit(1);
    }


    try
    
    {
        e1 = regex(R"((.*): (\(log.c.166\) server started.*))");
        e2 = regex("(.*)\\.\\d*:INFO:oejs.AbstractConnector:Started "
                   "SelectChannelConnector@0.0.0.0:9080.*");
    }
    catch (regex_error &exc)
    {
        cout << "Regex constructor failed with code " << exc.code() << endl;
        exit(1);
    }
    int line_number = 1;
    string str;
    while (getline(infile, s))
    {
        if (regex_match(s, e1))
        {
            smatch sm;
            regex_match(s, sm, e1);
            if (flag)
            {
                outfile << "failure" << endl;
            }
            flag = true;
            t1 = ptime(boost::posix_time::time_from_string(sm[1]));
            str = sm[2];
            outfile << line_number << " (log.c.166) server started "
                    << sm[1] << " ";
        }
        if (regex_match(s, e2))
        {
            smatch sm;
            regex_match(s, sm, e2);
            t2 = ptime(boost::posix_time::time_from_string(sm[1]));
            outfile << "success " << (t2 - t1).total_milliseconds()
                    << "ms" << endl;
            flag = false;
        }
        line_number++;
    }
    if (flag)
    {
        outfile << "failure" << endl;
    }
    infile.close();
    outfile.close();
    return 0;
}
