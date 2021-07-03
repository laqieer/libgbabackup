# GBA Cart Backup Media Access Library

*Part from the code of this project comes from decompiled binaries, use it at your own risk.*

*[libsavgba](https://github.com/laqieer/libsavgba) is an safe alternative to this, you are encouraged to use it instead.*
* 256kbit SRAM High Speed Access Library ver. 1.0.3 (SRAM_F_V103) from [fireemblem8u](https://github.com/FireEmblemUniverse/fireemblem8u)
* 1Mbit FLASH Library ver. 1.0.3 (FLASH1M_V103) from [pokeruby](https://github.com/pret/pokeruby)
* 256kbit SRAM Library ver. 1.1.3 (SRAM_V113) from [katam](https://github.com/jiangzhengwenjz/katam)
* 512kbit FLASH Library ver. 1.3.1 (FLASH512_V131)
* 4kbit/64kbit EEPROM Library ver. 1.2.4 (EEPROM_V124) from [tmc](https://github.com/zeldaret/tmc)

## Test

||EZ-FLASH OMEGA|EverDrive-GBA X5|SuperCard MINI SD|mGBA|visualboyadvance-m|NO$GBA|VisualBoyAdvance|NanoBoyAdvance|
|---|---|---|---|---|---|---|---|---|
|sram|passed|passed|passed|passed|passed|passed|passed|passed|
|sram_fast|passed|passed|passed|passed|passed|passed|passed|passed|
|flash_512k|passed|passed|unsupported device|passed|passed|passed|passed|passed|
|flash_1m|passed|passed|unsupported device|passed|passed|passed|passed|passed|
|eeprom_4k|passed|passed|verify error|passed|passed|passed|passed|passed|
|eeprom_64k|passed|verify error*|verify error|passed|[verify error](https://github.com/visualboyadvance-m/visualboyadvance-m/issues/810)|passed|passed|passed|
|sram_512k(not used in official games)|passed|mirrored|passed|mirrored|passed|mirrored|passed|mirrored|

* EverDrive-GBA X5 doesn't have a specific save type to choose for 64k eeprom.

## Links

* [GBATEK](http://problemkaputt.de/gbatek.htm#gbacartridges)
* [reinerziegler](https://reinerziegler.de.mirrors.gg8.se/GBA/gba.htm)
* [dillonbeliveau](https://dillonbeliveau.com/2020/06/05/GBA-FLASH.html)
