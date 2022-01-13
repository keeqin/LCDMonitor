#include "computerinfo.h"
#include <QFileInfoList>
#include <QDir>
#include <QDebug>
#include <QProcess>
#include "jqcpumonitor.h"


#define MB (1024*1014)
#define GB (1024*1024*1014)


ComputerInfo::ComputerInfo()
{
    JQCPUMonitor::initialize();
    mem.dwLength = sizeof(mem);
}


void ComputerInfo::getMemoryInfo(uint8_t *totalPhys, uint8_t *memUsage)
{
    GlobalMemoryStatusEx(&mem);
    *totalPhys = mem.ullTotalPhys/GB;
    *memUsage = static_cast<uint8_t>((mem.ullTotalPhys - mem.ullAvailPhys) * 100 / static_cast<double>(mem.ullTotalPhys));
}


void ComputerInfo::getCPUUsage(uint8_t *CPUUsage)
{
    *CPUUsage =  static_cast<uint8_t>(JQCPUMonitor::cpuUsagePercentage()*100);
}


QList<DiskInfo> ComputerInfo::getDiskInfo(void)
{
    QList<DiskInfo> diskList;
    QFileInfoList dirs = QDir::drives();
    foreach (QFileInfo dir, dirs)
    {
        DiskInfo diskinfo;
        QString dirName = dir.absolutePath();
        LPCWSTR lcpwstrDriver = (LPCWSTR)dirName.utf16();
        ULARGE_INTEGER liFreeBytesAvailble, liTotalBytes, liTotalFreeBytes;
        if(GetDiskFreeSpaceEx(lcpwstrDriver, &liFreeBytesAvailble, &liTotalBytes, &liTotalFreeBytes))
        {
            diskinfo.symbol = qPrintable(dirName)[0];
            diskinfo.volume = static_cast<uint16_t>(liTotalBytes.QuadPart / GB);
            diskinfo.diskUsage = static_cast<uint8_t>((liTotalBytes.QuadPart - liTotalFreeBytes.QuadPart)*100/ static_cast<double>(liTotalBytes.QuadPart));
            diskList.append(diskinfo);
        }

    }
    return diskList;
}

