## motion-led

Source code for the motion controlled led night light


### code

Firmware. This is a generic Makefile project. Building was tested using the GNU Arm Embedded toolchain.
Build with:

```bash
make BINPATH=<path/to/gnu/arm/embedded/toolchain/bin>     #(without trailing slash / !)
```

the BINPATH=... argument is not necessary if you have the binaries in your PATH

Also there are eclipse project files for use in eclipse with the Gnu Mcu Eclipse plugin. Use the "Import Existing Code" feature in eclipse

### pcb

PCB design data as well as gerber files

### cad

Contains everything related to the housing



