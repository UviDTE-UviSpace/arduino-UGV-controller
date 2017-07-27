======================
arduino-UGV-controller
======================


Project for controlling an unmanned guided vehicle (UGV) with an Arduino on-board. The Arduino is controller by a master connected through the serial port.

The project belongs to **UviSpace**, an Open-Source project developed at the *Electronic Technology Department in the University of Vigo*.

=====================
Project documentation
=====================

.. image:: https://readthedocs.org/projects/uvispace/badge/?version=latest
   :target: http://uvispace.readthedocs.io/en/latest/?badge=latest
   :alt: Documentation Status

The oficial documentation about the **UviSpace** project is hosted at `this website
<http://uvispace.readthedocs.io/en/latest/>`_.

==================================
Compiling and loading instructions
==================================

The project has been developed for being loaded on the `Romeo board, from DFRobot <https://www.dfrobot.com/product-844.html>`_. The project is compatible with the *open-source Arduino Software (IDE)*, that can be downloaded `here <https://www.arduino.cc/en/Main/Software>`_.

For loading the *arduino-UGV-controller* on a board, follow the next steps:

* Open the *UGV.ino* script from this repository with the *Arduino Software (IDE)*
* **(optional)** Compile the project with the verify button (top left *tick* button)
* Select **Tools > Board > Arduino/Genuino Uno**
* Connect the Romeo board to the PC through the USB cable. **Important:** If an XBee shield with and XBee transceiver is connected to the board:

  * put the RUN/PROG switch on the PROG position. If not, the PC will not be able to program the board
  * put the USB/XBEE switch at XBEE position. This step is critical, as some XBee modules were damaged in the past for setting the switch to the incorrect position. This is most probably due to a shortcircuit between the Romeo Tx port (5V signal) to the XBee Rx port (3V3 signal).
  
* Load the project to the board with the IDE Upload button (top left *arrow* button)
