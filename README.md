PSEUDOKO 
    
    A device driver for a pseudo stack device.
 
The Linux character device type supports the following operations

– Open: only one is allowed.

– Write: writes an char string to top of the device stack. Error if stack is full.

– Read: reads an item from top of the device stack. Error if stack is empty.

– Release: release the device 
