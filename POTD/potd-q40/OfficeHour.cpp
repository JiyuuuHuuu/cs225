#include <iostream>
#include "OfficeHour.h"

/*
Given the current Office Hour queue and the currently on-duty staffers, return
how long the nth student will need to wait before a Staffer can reach them
Return -1 if there are no staff available to help the nth student

@param queue A queue containing the students currently waiting for help
@param onDutyStaff  A vector of Staffers currently on duty
@param nthStudent   The student for whom we are calculating a wait time
@return             How many minutes the nth student will have to wait before getting help
*/
int waitTime(queue<Student> queue, vector<Staffer> onDutyStaff, int nthStudent) {
    // Your code here!
    int waittime = 0;
    int nth = 0;
    while(1)
    {
      if ((nth == nthStudent && !onDutyStaff.empty()))
      {
        return waittime;
      }

      while(!onDutyStaff.empty())
      {
        
      }
    }

    return waittime;
}
