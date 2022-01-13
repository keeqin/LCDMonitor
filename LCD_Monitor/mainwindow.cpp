#include "mainwindow.h"
#include "computerinfo.h"
#include "traymenu.h"
#include "libusb.h"
#include <QIcon>
#include <QTimer>
#include <QDebug>

#define USB_BUFFSIZE 24
#define USB_ACTIVED_ICON    ":/icon/monitor.jpg"
#define USB_INACTIVED_ICON  ":/icon/monitor2.jpg"
#define APP_QUIT_ICON  ":/icon/quit.jpg"

libusb_device_handle *handle;
bool isUSBDeviceActive;

ComputerInfo *info;

static void connectUSB(void)
{
    if(isUSBDeviceActive == true) return;
    if(handle != NULL)
    {
        libusb_release_interface(handle, 0);
    }
    handle = libusb_open_device_with_vid_pid(NULL, 0xee1e, 0x55f1);
    if(handle == NULL)
    {
        return;
    }
    libusb_set_auto_detach_kernel_driver(handle, 1);
    libusb_claim_interface(handle, 0);
    isUSBDeviceActive = true;
}

static void prepareCPUMemInfo(uint8_t *buffer)
{
    info->getCPUUsage(&buffer[1]);
    info->getMemoryInfo(&buffer[3], &buffer[2]);
    buffer[0] = 4;
}

static void prepareDiskInfo(uint8_t *buffer)
{
    QList<DiskInfo> diskInfos = info->getDiskInfo();
    int i = 1;
    foreach(DiskInfo diskInfo , diskInfos)
    {
        buffer[i++] = diskInfo.symbol;
        buffer[i++] = diskInfo.diskUsage;
        uint16_t *p = (uint16_t*)&buffer[i];
        *p = diskInfo.volume;
        i += 2;
    }
    buffer[0] = i;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    /************************************************/
    /**************initalize tray menu*****************/
    /************************************************/
    TrayMenu *trayMenu = new TrayMenu(this);



    /************************************************/
    /**************initalize tray icon*****************/
    /************************************************/
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(USB_INACTIVED_ICON));
    trayIcon->setToolTip("LCD Monitor");
    trayIcon->show();
    trayIcon->setContextMenu(trayMenu); //add trayMenu to trayicon
    trayIcon->showMessage("LCD Monitor","Launched", QSystemTrayIcon::Information, 100 );





    /************************************************/
    /****************initalize USB ********************/
    /************************************************/
    libusb_init(NULL);
    connectUSB();





    /************************************************/
    /************initalize CPU info *****************/
    /************************************************/
    info = new ComputerInfo;
    uint8_t data[USB_BUFFSIZE];
    prepareDiskInfo(data);


    /************************************************/
    /*******create a tiemr to send cpu info *********/
    /************************************************/
    QTimer *libusbTimer = new QTimer(this);
    libusbTimer->start(1000);


    connect(libusbTimer, &QTimer::timeout, this, [=]()mutable{
        if(isUSBDeviceActive == true)
        {
            static uint32_t count;
            count++;
            if(count == 60 * 10)
            {
                //update DiskInfo every 10 minutes
                count = 0;
                prepareDiskInfo(data);
            }else{
                prepareCPUMemInfo(data);
            }
            int size, rc;
            rc = libusb_interrupt_transfer(handle, 0x01, data, USB_BUFFSIZE, &size, 100);
            if(rc != 0)
            {
                isUSBDeviceActive = false;
            }/*else
            {
                qDebug() << "send success";
            }*/
        }else
        {
            connectUSB();
        }
    });


    QTimer *usbStateTimer = new QTimer(this);
    usbStateTimer->start(500);
    connect(usbStateTimer, &QTimer::timeout, this, [=]()mutable{
        static bool lastState = false;
        if(lastState != isUSBDeviceActive)
        {
            lastState = isUSBDeviceActive;
            trayIcon->setIcon(isUSBDeviceActive ? QIcon(USB_ACTIVED_ICON) : QIcon(USB_INACTIVED_ICON));
            if(isUSBDeviceActive)
            {
                prepareDiskInfo(data);
                int size;
                libusb_interrupt_transfer(handle, 0x01, data, USB_BUFFSIZE, &size, 100);
            }else
            {
                trayIcon->showMessage("LCD Monitor","USB Disconnected", QSystemTrayIcon::Warning, 100 );
            }

        }
    });
}

MainWindow::~MainWindow()
{
}

