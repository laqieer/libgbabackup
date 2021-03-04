arm-none-eabi-gcc -mcpu=arm7tdmi -mthumb -mthumb-interwork -c src/*.c
arm-none-eabi-ar cr lib/libgbabackup.a *.o
rm -rf *.o
