# UBlox_Serial_GPS
The purpose of this repository is to be used with the Ublox 6m GPS. This GPS protocol is based on sending the messages directly as binary data rather than using NMEA strings and converting the messages to binary data. This makes communuciations with the UBlox through this method extremely fast. To understand how these messages are structed see the link to the UBlox manual below.
[UBlox 6m Manual with message protocols](https://www.u-blox.com/sites/default/files/products/documents/u-blox6_ReceiverDescrProtSpec_%28GPS.G6-SW-10018%29_Public.pdf)

To be able to select what messages you wish to have sent via the Ublox serial port you will need to download the following program made by Ublox. [u-center U-blox download](https://www.u-blox.com/en/product/u-center) 

Finally, to understand use this library correctly I suggest watching the video found below. In this video youtuber iforce2d does a tutorial on confiugring Ublox GPS modules to send data in binary form. Note that the files in this repository are also based heavily on his original files. I have made some changes of my own to accomodate additional messages but by and large the codes are very similar. [Tutorial on using U-center for U-blox configuration](https://www.u-blox.com/en/product/u-center)
