arm-none-eabi-gcc -mcpu=arm7tdmi -mthumb -mthumb-interwork -c -I include src/*.c
arm-none-eabi-ar cr lib/libgbabackup.a *.o
rm -rf *.o
