#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>


void gotoxy(int x, int y){
    COORD pos;
    pos.X = x-1;
    pos.Y = y-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void clrscr(){
    system("cls");
}


void drawFrame(){
    clrscr();
    gotoxy(5,2);  printf("==========================================================");
    gotoxy(5,3);  printf("                MINI OS DASHBOARD MONITOR");
    gotoxy(5,4);  printf("==========================================================");

    gotoxy(5,6);  printf(" SYSTEM TIME     :");
    gotoxy(5,7);  printf(" SYSTEM DATE     :");
    gotoxy(5,8);  printf(" SYSTEM UPTIME   :");

    gotoxy(5,10); printf(" MEMORY USAGE    :");
    gotoxy(5,11); printf(" CPU USAGE       :");
    gotoxy(5,12); printf(" WIFI SPEED:");

    gotoxy(5,14); printf(" SYSTEM STATUS   :");

    gotoxy(5,17); printf("==========================================================");
    gotoxy(5,18); printf(" Press Ctrl + C to Exit");
    gotoxy(5,19); printf("==========================================================");
}


double getMemoryUsage(){
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&mem);
    double used = mem.ullTotalPhys - mem.ullAvailPhys;
    return (used*100.0)/mem.ullTotalPhys;
}


double getCPUUsage(){
    static clock_t lastClock = 0;
    clock_t now = clock();
    double cpu = 0;

    if(lastClock != 0){
        cpu = ((double)(now - lastClock) / CLOCKS_PER_SEC) * 50;
        if(cpu > 100) cpu = 100;
    }

    lastClock = now;
    return cpu;
}


double getWiFiSpeed(){
    return (rand() % 100) + 10;
}


void updateValues(time_t startTime){
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    int uptime = (int)difftime(now, startTime);
    int h = uptime/3600;
    int m = (uptime%3600)/60;
    int s = uptime%60;

    double memUsage = getMemoryUsage();
    double cpuUsage = getCPUUsage();
    double wifiSpeed = getWiFiSpeed();

    gotoxy(25,6);  printf("%02d:%02d:%02d     ", local->tm_hour, local->tm_min, local->tm_sec);
    gotoxy(25,7);  printf("%02d-%02d-%04d     ", local->tm_mday, local->tm_mon+1, local->tm_year+1900);
    gotoxy(25,8);  printf("%02d:%02d:%02d     ", h, m, s);

    gotoxy(25,10); printf("%.2f %%          ", memUsage);
    gotoxy(25,11); printf("%.2f %%          ", cpuUsage);
    gotoxy(25,12); printf("%.2f Mbps      ", wifiSpeed);

    gotoxy(25,14);
    if(cpuUsage < 80) printf("NORMAL            ");
    else printf("HIGH LOAD         ");

    fflush(stdout);
}

int main(){
    srand((unsigned int)time(NULL));
    drawFrame();
    time_t startTime = time(NULL);

    while(1){
        updateValues(startTime);
        Sleep(1000);
    }
    return 0;
}
