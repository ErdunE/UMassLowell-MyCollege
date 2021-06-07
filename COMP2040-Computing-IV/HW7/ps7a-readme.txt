/**********************************************************************
 *  readme.txt template                                                   
 *  Kronos PS7a startup
 **********************************************************************/

Name:Erdun E

Hours to complete assignment: 7 Hours


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
 yes.
 yes.
 I think everything is working properly. I have compared the logs of 
 device5 with the sample output. Although there are some differences in 
 format, the contents are consistent.


/**********************************************************************
 *  Copy here all regex's you created for parsing the file, 
 *  and explain individually what each ones does.
 **********************************************************************/
 (.*): (\(log.c.166\) server started.*)
 Use this expression to determine the device startup and extract the 
 startup time from the first group.

 (.*)\\.\\d*:INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080.*

 Use this expression to match a device startup completion and extract 
 the completion time in the first group.


/**********************************************************************
 *  Describe your overall approach for solving the problem.
 *  100-200 words.
 **********************************************************************/

 I use these two expressions to figure out what the current line is, 
 if it's started, I record the time to t1, if it's finished, I record 
 the time to t2, And calculate the value of t2 minus t1, which is the 
 time it takes to start. Use a flag to determine if the startup failed, 
 and if the current flag is true, expect the next one to be "completion row", 
 and if the next row is still "start line", the last start failed.

/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/
Yunhao Mei
Chuming Zhen
Chenghai Cao
Fangwen Wang
Hong Zhao


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
 None


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
 None

