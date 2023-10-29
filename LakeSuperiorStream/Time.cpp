#include "Time.h"

Time::Time(const std::string& date, const std::string& time) {
    std::stringstream ss(date);
    std::getline(ss,month,'/');
    std::getline(ss,day,'/');
    std::getline(ss,year,'/');

    if(year.length() <= 2){
        year = "20" + year;
    }
    // from start to :
    hours = time.substr(0, time.find(':'));
    // from : to end
    minutes = time.substr(time.find(':') + 1);
}

//Sensor time stamp
Time::Time(const std::string& timestamp) {
    // first pos to first /
    month = timestamp.substr(0, timestamp.find('/'));
    // between 1st / and 2nd /
    day = timestamp.substr(timestamp.find('/') + 1, timestamp.find('/'));
    // from last / to end
    year = timestamp.substr(timestamp.find_last_of('/') + 1, 4);
    //skipping over space gap from data set to :
    hours = timestamp.substr(timestamp.find(' ') + 1, timestamp.find(':') - timestamp.find(' ') - 1);
    // from first : to second :
    minutes = timestamp.substr(timestamp.find(':') + 1, 2);
    // from second : to end
    seconds = timestamp.substr(timestamp.find_last_of(':') + 1, 2);
}

int Time::getYear() const {
    try{
        return std::stoi(year);
    }catch(std::invalid_argument &e){
        return 0;
    }
}

int Time::getMonth() const {
    try{
        return std::stoi(month);
    }catch(std::invalid_argument &e){
        return 0;
    }
}

int Time::getDay() const {
    try{
        return std::stoi(day);
    }catch(std::invalid_argument &e){
        return 0;
    }
}

int Time::getHours() const {
    try{
        return std::stoi(hours);
    }catch(std::invalid_argument &e){
        return 0;
    }
}

int Time::getMinutes() const {
    try{
        return std::stoi(minutes);
    }catch(std::invalid_argument &e){
        return 0;
    }
}

int Time::getSeconds() const {
    try{
        return std::stoi(seconds);
    }catch(std::invalid_argument &e){
        return 0;
    }
}

double Time::getTotalSeconds() const {
    time_t epoch = 0,finish,rawtime;
    struct tm *timeInfo;
    time ( &rawtime );
    timeInfo = localtime ( &rawtime );
    timeInfo->tm_year = getYear()-1900;
    timeInfo->tm_mon = getMonth()-1;
    timeInfo->tm_mday = getDay();
    timeInfo->tm_hour = getHours();
    timeInfo->tm_min = getMinutes();
    timeInfo->tm_sec = getSeconds();

    finish = mktime(timeInfo);
    double total = difftime(finish,epoch);
    return total;
}

std::string Time::toString() const {
    return month + "/" + day + "/" + year + " " + hours + ":"+ minutes + ":"+ seconds;
}
