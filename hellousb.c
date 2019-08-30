/* 
Code author: Ramana R (Rr42)
Code version: v1.0
Description:
    Sample code to demonstrate a linux USB driver.
Good USB device instructions: 
https://www.youtube.com/watch?v=5IDL070RtoQ&list=PLa2N8kjIXIWqYUmF2HvYrv35_R2JthYFo&index=2
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>


/* ID table */
/* Each entry holds a usb_device_id "object" returned by the macro 
'USB_DEVICE(<vendor id>, <device id>)'. The vendor and device ID of 
the USB device can be obtained using the 'lsusb' or 'lsusb -v' command 
in a terminal window. The last entry in the list entry in the array must 
be '{}' as an indication of the terminating entry.*/
static struct usb_device_id hellousb_table[] = 
{
    { USB_DEVICE(0x058f, 0x6387) },
    {}
};

/* Prober */
/* The probe function is called by the kernel when a device compatible with 
this driver is identified and no other compatible driver is found before hand. 
A return value of '0' indicates that this driver will manage the identified device.*/
static int hellousb_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    printk(KERN_INFO "--> Hellousb USB drive (%04X:%04X) identified\n", id->idVendor, id->idProduct);
    return 0;
}

/* Disconnector */
/* The disconnect function is called when the identified device id disconnected.*/
static void hellousb_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO "--> Hellousb USB drive disconnected\n");
}

/* USB driver */
/* Structure taht defines the driver and holds information of the key 
functionality of the driver.*/
static struct usb_driver hellousb_driver = 
{
    .name = "Hellow USB driver",
    .id_table = hellousb_table,
    .probe = hellousb_probe,
    .disconnect = hellousb_disconnect,
};

/* Initializer */
/* The Initializer is called when the kernel module is loaded.*/
static int __init hellousb_init(void)
{
    int rt = -1;
    printk(KERN_INFO "--> Hellousb kernel module loaded\n");
    printk(KERN_INFO "  > Registering Hellousb driver\n");
    rt = usb_register(&hellousb_driver);
    printk(KERN_INFO "  > Registeration return code: %i\n", rt);

    if (rt == -16)
    {
        printk(KERN_INFO "  > Driver already registered!\n");
        printk(KERN_INFO "  > Attempting to deregister existing driver...\n");
        usb_deregister(&hellousb_driver);
        printk(KERN_INFO "  > Driver successfully deregisted\n");

        printk(KERN_INFO "  > Registering Hellousb driver\n");
        rt = usb_register(&hellousb_driver);
    }

    printk(KERN_INFO "  > Hellousb driver registered successfully\n");

    return rt;
}

/* Exit function */
/* The exit function is called when the kernel module is unloaded.*/
static void __exit hellousb_exit(void)
{
    printk(KERN_INFO "--> Deregistering driver...\n");
    usb_deregister(&hellousb_driver);
    printk(KERN_INFO "  > Driver successfully deregistered\n");
    printk(KERN_INFO "--> Hellousb kernel module successfully unloaded\n");
}

module_init(hellousb_init);
module_exit(hellousb_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rr42");
MODULE_DESCRIPTION("Sample USB driver");
MODULE_VERSION("1.0");
