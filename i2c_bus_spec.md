

#I2C Protocol
##Joe Brown
##Rev 1


##Command Format
The I2C protocol will consists of three (3) parts:

1.   Device Address (including a read/write bit)
2.   Register Address
3.   Data byte

In this document it will be assumed that the Read() and Write() Commands automatically adjust the read/write bit in the address byte.

###Calculating Command Read/Write time
Every I2C transaction has the same flow:

    Start(1)->(Address(7)+R/W(1))->Ack(1)->Register(8)->Ack(1)->Data(8)->Ack(1)->Stop(1)

>Note: The Data byte may be read or written depending on the polarity of the R/W bit

Using this we can calculate the transaction time for every transaction using the clock speed of the bus:

    Transaction time = 29 * (1 / Clock Rate)

For a standard 400 kHz I2C bus the time will be 73 microseconds.

##Register Map Summary

<center>
<table border="1" cellspacing="1" >
<tr><td>Description                     </td><td>Location</td><td>Size</td><td>R/W-></td></tr>
<tr><td>Address                         </td><td>  0x00  </td><td> 1  </td><td>R/W  </td></tr>
<tr><td>Type                            </td><td>  0x01  </td><td> 1  </td><td> R   </td></tr>
<tr><td>Number of Read Endpoints        </td><td>  0x02  </td><td> 1  </td><td> R   </td></tr>
<tr><td>Start Address of Read Endpoints </td><td>  0x03  </td><td> 1  </td><td> R   </td></tr>
<tr><td>Number of Write Endpoints       </td><td>  0x04  </td><td> 1  </td><td> R   </td></tr>
<tr><td>Start Address of Write Endpoints</td><td>  0x05  </td><td> 1  </td><td> R   </td></tr>
<tr><td>Individual Peripheral Registers </td><td>  0x06  </td><td> 250</td><td> -   </td></tr>
</table>
</center>

##Peripheral Register Definitions
###Address (1) - 0x00                              R/W
Address of the selected peripheral.
Register Description:

*   [7:1] Address of selected device
*   [0]   Reserved

Example:

    Read(0x90,0x00) -> 0x90 // I certainly hope it returns its own address
    Write(0x90,0x00,0x80)   // change address to 0x80
    Read(0x80,0x00) -> 0x80 // Address is now changed

###Type (1) -  0x01                                R
Type identifier for the selected peripheral.
Register Description:

* [7:0] Type Identifier

Example:

    Read(0x90,0x01) -> 0x10 // Peripheral type at address 0x90 is 0x10

###Number of Read Endpoints (1) - 0x02             R
Number of readable endpoints for the selected peripheral.
Register Description:

* [7:0] Number of readable endpoints

Example:

    Read(0x90,0x02) -> 0x01 // Number of readable endpoints at address 0x90 is 1

###Start Address of Read Endpoints (1) - 0x03      R
Starting address of readable endpoints for the selected peripheral. Note: Readable endpoints can only be read from.
Register Description:

* [7:0] Start address of readable endpoints

Example:

    Read(0x90,0x03) -> 0x20 // Readable endpoints start at address 0x20
    Read(0x90,0x20) -> 0x01 // Current value of address 0x20 is 1

###Number of Write Endpoints (1) - 0x04            R
Number of writable endpoints for the selected peripheral.
Register Description:

* [7:0] Number of writable endpoints

Example:

    Read(0x90,0x04) -> 0x01 // Number of writable endpoints at address 0x90 is 1

###Start Address of Write Endpoints (1) - 0x05     R
Starting address of writable endpoints for the selected peripheral. Writable endpoints can be read from and written to.
Register Description:

* [7:0] Start address of writable endpoints

Example:

    Read(0x90,0x04) -> 0x01 // Number of writable endpoints at address 0x90 is 1
    Read(0x90,0x05) -> 0x21 // The address of that endpoint is 0x21
    Write(0x90,0x21,1)      // Write 1 to that endpoint
    
###Individual Peripheral Registers (250) -   0x06  R/W*
Peripheral registers defined by the specific peripheral for which they reside.
