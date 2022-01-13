#ifndef COMPUTERINFO_H
#define COMPUTERINFO_H
#include <stdint.h>
#include <QList>
#include <QStringList>
#include <windows.h>

typedef struct{
    char symbol;
    uint8_t diskUsage;
    uint16_t volume;
} DiskInfo;

class ComputerInfo
{
public:
    ComputerInfo();
    void getMemoryInfo(uint8_t *totalPhys, uint8_t *memUsage);
    QList<DiskInfo> getDiskInfo(void);
    QString getCPUInfo(void);
    void getCPUUsage(uint8_t *CPUUsage);
private:
        MEMORYSTATUSEX mem;
};



#endif // COMPUTERINFO_H
