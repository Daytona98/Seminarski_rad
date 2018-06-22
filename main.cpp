

//Test of cheap 13.56 Mhz RFID-RC522 module from eBay
//This code is based on Martin Olejar's MFRC522 library. Minimal changes
//Adapted for Nucleo STM32 F401RE. Should work on other Nucleos too

//Connect as follows:
//RFID pins        ->  Nucleo header CN5 (Arduino-compatible header)
//----------------------------------------
//RFID IRQ=pin5    ->   Not used. Leave open
//RFID MISO=pin4   ->   Nucleo SPI_MISO=PA_6=D12
//RFID MOSI=pin3   ->   Nucleo SPI_MOSI=PA_7=D11
//RFID SCK=pin2    ->   Nucleo SPI_SCK =PA_5=D13
//RFID SDA=pin1    ->   Nucleo SPI_CS  =PB_6=D10
//RFID RST=pin7    ->   Nucleo         =PA_9=D8
//3.3V and Gnd to the respective pins

#include "mbed.h"
#include "MFRC522.h"

DigitalOut LedGreen(LED1);

//Serial connection to PC for output
Serial pc(USBTX, USBRX);


//MFRC522    RfChip   (SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS, MF_RESET);
MFRC522    RfChip   (PTD2, PTD3, PTD1, PTD0, PTC4);
//MFRC522    RfChip2   (PTD2, PTD3, PTD1, PTC3, PTC2); //Adding extra sensors if needed
//MFRC522    RfChip3   (PTD2, PTD3, PTD1, PTA2, PTB23);

int main(void)
{
    pc.printf("starting...\n");

    // Init. RC522 Chip
    RfChip.PCD_Init();
//    RfChip2.PCD_Init();
//    RfChip3.PCD_Init();

    while (true) {
        LedGreen = 1;

        if ( RfChip.PICC_IsNewCardPresent()) {
            if (RfChip.PICC_ReadCardSerial()) {

                LedGreen = 0;

                pc.printf("Card Reader 1: ");
                for (uint8_t i = 0; i < RfChip.uid.size; i++) {
                    pc.printf(" %X02", RfChip.uid.uidByte[i]);
                }
                pc.printf("\n\r");
            }
        }

/*      if ( RfChip2.PICC_IsNewCardPresent()) {
            if (RfChip2.PICC_ReadCardSerial()) {

                        LedGreen = 0;

                        pc.printf("Card Reader 2: ");
                        for (uint8_t i = 0; i < RfChip2.uid.size; i++) {
                            pc.printf(" %X02", RfChip2.uid.uidByte[i]);
                        }
                        pc.printf("\n\r");
                    }
                }

                if ( RfChip3.PICC_IsNewCardPresent()) {
                    if (RfChip3.PICC_ReadCardSerial()) {

                        LedGreen = 0;

                        pc.printf("Card Reader 3: ");
                        for (uint8_t i = 0; i < RfChip3.uid.size; i++) {
                            pc.printf(" %X02", RfChip3.uid.uidByte[i]);
                        }
                        pc.printf("\n\r");
                    }
                }*/

    }
}
