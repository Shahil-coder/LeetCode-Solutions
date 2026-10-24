
int convertToDays(char* date) {
    int daysInMonths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    int month = (date[0] - '0') * 10 + (date[1] - '0');
    int day = (date[3] - '0') * 10 + (date[4] - '0');
    
    int totalDays = day;
    for (int i = 0; i < month - 1; i++) {
        totalDays += daysInMonths[i];
    }
    
    return totalDays;
}

int countDaysTogether(char* arriveAlice, char* leaveAlice, char* arriveBob, char* leaveBob) {
    int aliceArrival = convertToDays(arriveAlice);
    int aliceLeave = convertToDays(leaveAlice);
    int bobArrival = convertToDays(arriveBob);
    int bobLeave = convertToDays(leaveBob);
    
    int latestArrival = (aliceArrival > bobArrival) ? aliceArrival : bobArrival;
    int earliestLeave = (aliceLeave < bobLeave) ? aliceLeave : bobLeave;
    
 
    if (latestArrival <= earliestLeave) {
        return earliestLeave - latestArrival + 1;
    }
    
    return 0;
}