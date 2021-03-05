arm-none-eabi-gcc -mcpu=arm7tdmi -mthumb -mthumb-interwork -c src/*.c
rm -rf lib/libgbabackup.a
arm-none-eabi-ar cr lib/libgbabackup.a *.o
rm -rf *.o
