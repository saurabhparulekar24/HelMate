/**
 * @file      BootMain.c
 * @brief     Main file for the ESE5160 bootloader. Handles updating the main application
 * @details   Main file for the ESE5160 bootloader. Handles updating the main application
 * @author    Eduardo Garcia
 * @author    Nick M-G
 * @date      2024-03-03
 * @version   2.0
 * @copyright Copyright University of Pennsylvania
 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "conf_example.h"
#include "sd_mmc_spi.h"
#include <asf.h>
#include <string.h>

#include "ASF/sam0/drivers/dsu/crc32/crc32.h"
#include "SD Card/SdCard.h"
#include "SerialConsole/SerialConsole.h"
#include "Systick/Systick.h"
#include "ASF/sam0/drivers/dsu/crc32/crc32.h"

/******************************************************************************
 * Defines
 ******************************************************************************/
#define APP_START_ADDRESS           ((uint32_t) 0x12000)                    ///< Start of main application. Must be address of start of main application
#define APP_START_RESET_VEC_ADDRESS (APP_START_ADDRESS + (uint32_t) 0x04)   ///< Main application reset vector address
#define NVM_BYTES_PER_ROW 256                                               /// Bytes in one ROW of NVM
#define __DEBUG__ 1                                                         /// Debugging Enable Bit

/******************************************************************************
 * Structures and Enumerations
 ******************************************************************************/

struct usart_module cdc_uart_module;   ///< Structure for UART module connected to EDBG (used for unit test output)

/******************************************************************************
 * Local Function Declaration
 ******************************************************************************/
static void jumpToApplication(void);
static bool StartFilesystemAndTest(void);
static void configure_nvm(void);
static enum status_code flash_bin(char *bin_to_flash);
static enum status_code perform_nvm_crc(uint8_t *dataBuffer, int row_number);
static enum status_code write_nvm(int row_number, uint8_t *buffer);
static enum status_code erase_nvm(int row_number);

/******************************************************************************
 * Global Variables
 ******************************************************************************/
// INITIALIZE VARIABLES
char test_file_name[] = "0:sd_mmc_test.txt";   ///< Test TEXT File name
char test_bin_file[] = "0:sd_binary.bin";      ///< Test BINARY File name
char test_bin_TestA[] = "0:Application_New.bin";	       /// Test Binary A
char test_bin_TestB[] = "0:TestB.bin";	       /// Test Binary B
char test_txt_flagA[] = "0:Application_New.txt";         /// Text Flag A
char test_txt_flagB[] = "0:FlagB.txt";         /// Text Flag B
Ctrl_status status;                            ///< Holds the status of a system initialization
FRESULT res, flagA_status, flagB_status;       // Holds the result of the FATFS functions done on the SD CARD TEST
FATFS fs;                                      // Holds the File System of the SD CARD
FIL file_object;                               // FILE OBJECT used on main for the SD Card Test
uint8_t readBuffer[NVM_BYTES_PER_ROW];         // Readbuffer to store data read from sdcard
enum status_code flash_status;                 // Flag to check if the updating was successful

/******************************************************************************
 * Global Functions
 ******************************************************************************/

/**
* @fn		int main(void)
* @brief	Main function for ESE5160 Bootloader Application

* @return	Unused (ANSI-C compatibility).
* @note		Bootloader code initiates here.
*****************************************************************************/

int main(void) {

    /*1.) INIT SYSTEM PERIPHERALS INITIALIZATION*/
    system_init();
    delay_init();
    InitializeSerialConsole();
    system_interrupt_enable_global();

    /* Initialize SD MMC stack */
    sd_mmc_init();

    // Initialize the NVM driver
    configure_nvm();

    irq_initialize_vectors();
    cpu_irq_enable();

    // Configure CRC32
    dsu_crc32_init();

    SerialConsoleWriteString("ESE5160 - ENTER BOOTLOADER");   // Order to add string to TX Buffer

    /*END SYSTEM PERIPHERALS INITIALIZATION*/

    /*2.) STARTS SIMPLE SD CARD MOUNTING AND TEST!*/

    // EXAMPLE CODE ON MOUNTING THE SD CARD AND WRITING TO A FILE
    // See function inside to see how to open a file
    SerialConsoleWriteString("\x0C\n\r-- SD/MMC Card Example on FatFs --\n\r");

    if (StartFilesystemAndTest() == false) {
        SerialConsoleWriteString("SD CARD failed! Check your connections. System will restart in 5 seconds...");
        delay_cycles_ms(5000);
        system_reset();
    } else {
        SerialConsoleWriteString("SD CARD mount success! Filesystem also mounted. \r\n");
    }

    /*END SIMPLE SD CARD MOUNTING AND TEST!*/

    /*3.) STARTS BOOTLOADER HERE!*/
    // Open flag file and check for flags
    static bool is_flashing = false;
    test_txt_flagA[0] = LUN_ID_SD_MMC_0_MEM + '0';
	flagA_status = f_open(&file_object, (char const *)test_txt_flagA, FA_READ|FA_OPEN_EXISTING);
    // Check if FlagA is present
    if(flagA_status == FR_OK){
        is_flashing = true;
        // remove Flag file it exists to prevent update next reset
        f_unlink((char const *)test_txt_flagA);
        test_bin_TestA[0] = LUN_ID_SD_MMC_0_MEM + '0';
        // Flash TestA
        flash_status = flash_bin(test_bin_TestA);
    }
    else{
        test_txt_flagB[0] = LUN_ID_SD_MMC_0_MEM + '0';
        flagB_status = f_open(&file_object, (char const *)test_txt_flagB, FA_READ|FA_OPEN_EXISTING);
        // Check if FlagB is present
        if(flagB_status == FR_OK){
            is_flashing = true;
            // remove Flag file it exists to prevent update next reset
            f_unlink((char const *)test_txt_flagB);
            test_bin_TestB[0] = LUN_ID_SD_MMC_0_MEM + '0';
            // Flash TestB
            flash_status = flash_bin(test_bin_TestB);
        }
    }
    // #if(__DEBUG__)
    //     if(flagA_status != FR_OK && flagB_status != FR_OK){
    //         test_bin_TestA[0] = LUN_ID_SD_MMC_0_MEM + '0';
    //         flash_bin(test_bin_TestA);
    //     }
    // #endif
    if(is_flashing){
    if(flash_status==STATUS_OK){
        SerialConsoleWriteString("Updated Firmware Successfully");
    }
    else{
        SerialConsoleWriteString("Unsuccessful in updating Firmware");
    }
    }

    
    

    // Students - this is your mission!

    /* END BOOTLOADER HERE!*/

    // 4.) DEINITIALIZE HW AND JUMP TO MAIN APPLICATION!
    SerialConsoleWriteString("ESE5160 - EXIT BOOTLOADER");   // Order to add string to TX Buffer
    delay_cycles_ms(100);                                    // Delay to allow print

    // Deinitialize HW - deinitialize started HW here!
    DeinitializeSerialConsole();   // Deinitializes UART
    sd_mmc_deinit();               // Deinitialize SD CARD

    // Jump to application
    jumpToApplication();

    // Should not reach here! The device should have jumped to the main FW.
}

/******************************************************************************
 * Static Functions
 ******************************************************************************/

/**
 * function      static void StartFilesystemAndTest()
 * @brief        Starts the filesystem and tests it. Sets the filesystem to the global variable fs
 * @details      Jumps to the main application. Please turn off ALL PERIPHERALS that were turned on by the bootloader
 *				before performing the jump!
 * @return       Returns true is SD card and file system test passed. False otherwise.
 ******************************************************************************/
static bool StartFilesystemAndTest(void) {
    bool sdCardPass = true;
    uint8_t binbuff[256];

    // Before we begin - fill buffer for binary write test
    // Fill binbuff with values 0x00 - 0xFF
    for (int i = 0; i < 256; i++) {
        binbuff[i] = i;
    }

    // MOUNT SD CARD
    Ctrl_status sdStatus = SdCard_Initiate();
    if (sdStatus == CTRL_GOOD)   // If the SD card is good we continue mounting the system!
    {
        SerialConsoleWriteString("SD Card initiated correctly!\n\r");

        // Attempt to mount a FAT file system on the SD Card using FATFS
        SerialConsoleWriteString("Mount disk (f_mount)...\r\n");
        memset(&fs, 0, sizeof(FATFS));
        res = f_mount(LUN_ID_SD_MMC_0_MEM, &fs);   // Order FATFS Mount
        if (FR_INVALID_DRIVE == res) {
            LogMessage(LOG_INFO_LVL, "[FAIL] res %d\r\n", res);
            sdCardPass = false;
            goto main_end_of_test;
        }
        SerialConsoleWriteString("[OK]\r\n");

        // Create and open a file
        SerialConsoleWriteString("Create a file (f_open)...\r\n");

        test_file_name[0] = LUN_ID_SD_MMC_0_MEM + '0';
        res = f_open(&file_object, (char const *) test_file_name, FA_CREATE_ALWAYS | FA_WRITE);

        if (res != FR_OK) {
            LogMessage(LOG_INFO_LVL, "[FAIL] res %d\r\n", res);
            sdCardPass = false;
            goto main_end_of_test;
        }

        SerialConsoleWriteString("[OK]\r\n");

        // Write to a file
        SerialConsoleWriteString("Write to test file (f_puts)...\r\n");

        if (0 == f_puts("Test SD/MMC stack\n", &file_object)) {
            f_close(&file_object);
            LogMessage(LOG_INFO_LVL, "[FAIL]\r\n");
            sdCardPass = false;
            goto main_end_of_test;
        }

        SerialConsoleWriteString("[OK]\r\n");
        f_close(&file_object);   // Close file
        SerialConsoleWriteString("Test is successful.\n\r");

        // Write binary file
        // Read SD Card File
        test_bin_file[0] = LUN_ID_SD_MMC_0_MEM + '0';
        res = f_open(&file_object, (char const *) test_bin_file, FA_WRITE | FA_CREATE_ALWAYS);

        if (res != FR_OK) {
            SerialConsoleWriteString("Could not open binary file!\r\n");
            LogMessage(LOG_INFO_LVL, "[FAIL] res %d\r\n", res);
            sdCardPass = false;
            goto main_end_of_test;
        }

        // Write to a binaryfile
        SerialConsoleWriteString("Write to test file (f_write)...\r\n");
        uint32_t varWrite = 0;
        if (0 != f_write(&file_object, binbuff, 256, &varWrite)) {
            f_close(&file_object);
            LogMessage(LOG_INFO_LVL, "[FAIL]\r\n");
            sdCardPass = false;
            goto main_end_of_test;
        }

        SerialConsoleWriteString("[OK]\r\n");
        f_close(&file_object);   // Close file
        SerialConsoleWriteString("Test is successful.\n\r");

    main_end_of_test:
        SerialConsoleWriteString("End of Test.\n\r");

    } else {
        SerialConsoleWriteString("SD Card failed initiation! Check connections!\n\r");
        sdCardPass = false;
    }

    return sdCardPass;
}

/**
 * function      static void jumpToApplication(void)
 * @brief        Jumps to main application
 * @details      Jumps to the main application. Please turn off ALL PERIPHERALS that were turned on by the bootloader
 *				before performing the jump!
 * @return
 ******************************************************************************/
static void jumpToApplication(void) {
    // Function pointer to application section
    void (*applicationCodeEntry)(void);

    // Rebase stack pointer
    __set_MSP(*(uint32_t *) APP_START_ADDRESS);

    // Rebase vector table
    SCB->VTOR = ((uint32_t) APP_START_ADDRESS & SCB_VTOR_TBLOFF_Msk);

    // Set pointer to application section
    applicationCodeEntry = (void (*)(void))(unsigned *) (*(unsigned *) (APP_START_RESET_VEC_ADDRESS));

    // Jump to application. By calling applicationCodeEntry() as a function we move the PC to the point in memory pointed by applicationCodeEntry,
    // which should be the start of the main FW.
    applicationCodeEntry();
}

/**
 * function      static void configure_nvm(void)
 * @brief        Configures the NVM driver
 * @details
 * @return
 ******************************************************************************/
static void configure_nvm(void) {
    struct nvm_config config_nvm;
    nvm_get_config_defaults(&config_nvm);
    config_nvm.manual_page_write = false;
    nvm_set_config(&config_nvm);
}

/**
 * @brief Calculates CRC on the data in NVM 
 * Caculates CRC on the data copied from the SDCARD on a block of 256 bytes
 * @param[in] dataBuffer Data Buffer in which data from the SDCARD was stored
 * @param[in] row_number row number
 * @return enum status_code 
 * \retval STATUS_OK Data is not corrupted
 * \retval STATUS_ABORTED could not calculate CRC
 */
static enum status_code perform_nvm_crc(uint8_t *dataBuffer, int row_number){
    enum status_code crcResult = STATUS_ABORTED;
    uint32_t firstresultCRC = 0;
    uint8_t nvmBuffer[NVM_BYTES_PER_ROW];
    // Calculate CRC on the data read from SDCard
    //Before using the CRC32 on RAM, execute the following code:
    *((volatile unsigned int*) 0x41007058) &= ~0x30000UL;
    enum status_code rtr_code = dsu_crc32_cal(dataBuffer, NVM_BYTES_PER_ROW, &firstresultCRC);
    //After using the CRC32, execute the following code:
    *((volatile unsigned int*) 0x41007058) |= 0x20000UL;

    if(rtr_code != STATUS_OK){
        SerialConsoleWriteString("Could not calculate CRC on Buffer Data\r\n");
    }
    // Read data from the NVM and perform CRC and check against the resultCRC
    // we need to read page by page, one page is 64 bytes, to read 256 bytes we need to read 4 times
    // Reading from the NVM memory can be performed using direct addressing into the NVM memory space, or by calling the nvm_read_buffer() function
    uint32_t secondresultCRC = 0;
    if(rtr_code == STATUS_OK){
        rtr_code = dsu_crc32_cal(APP_START_ADDRESS + row_number*NVM_BYTES_PER_ROW, NVM_BYTES_PER_ROW, &secondresultCRC);
        if(rtr_code != STATUS_OK){
            SerialConsoleWriteString("Could not calculate CRC on NVM Data\r\n");
        }
    }
    if(firstresultCRC == secondresultCRC){
        crcResult = STATUS_OK;
    }
    else{
        SerialConsoleWriteString("CRC did not match\r\n");
    }
    
    return crcResult;
}

/**
 * @brief Writes to NVM
 * Writes to 256 bytes starting from nvm_addr
 * @param[in] row_number row number
 * @param[in] buffer data to write
 * @return enum status_code 
 * \retval STATUS_ABORTED 
 * \retval STATUS_OK
 */
static enum status_code write_nvm(int row_number, uint8_t *buffer){
    enum status_code rtr_code = STATUS_ABORTED;
    for(int i=0;i<4;i++){
        rtr_code = nvm_write_buffer(APP_START_ADDRESS + row_number*NVM_BYTES_PER_ROW + NVMCTRL_PAGE_SIZE*i, buffer + i*NVMCTRL_PAGE_SIZE, NVMCTRL_PAGE_SIZE);
        if(rtr_code != STATUS_OK){
            SerialConsoleWriteString("Failed To write NVM\r\n");
            break;
        }
    }
    return rtr_code;
}

/**
 * @brief Erases NVM
 * Erases one row in NVM from nvm_addr
 * @param[in] row_number Row number to erase
 * @return enum status_code 
 */
static enum status_code erase_nvm(int row_number){
    enum status_code rtr_code = nvm_erase_row(APP_START_ADDRESS + row_number*NVM_BYTES_PER_ROW);
    char erased_byte_NVM = 0xFF;
    if(rtr_code!=STATUS_OK){
            SerialConsoleWriteString("Error While erasing data\r\n");
    }
    // Reading from the NVM memory can be performed using direct addressing into the NVM memory space
    // reading each bytes in the row
    if(rtr_code!=STATUS_OK){
        for(int i=0;i<NVM_BYTES_PER_ROW;i++){
            char *a = (char *)(APP_START_ADDRESS + i + (row_number*NVM_BYTES_PER_ROW));
            if(*a != erased_byte_NVM){
                SerialConsoleWriteString("Page not erased\r\n");
                rtr_code = STATUS_ABORTED;
                break;
            }
        }
    }
    return rtr_code;
}

/**
 * @brief Flashes the bin file
 * 
 * @param[in] bin_to_flash Bin File name to flash
 * @return enum status_code 
 */
static enum status_code flash_bin(char *bin_to_flash){
    const uint32_t len = NVM_BYTES_PER_ROW;
    char h[64];
    enum status_code rtr_code = STATUS_ABORTED;
    res = f_open(&file_object, (char const *)bin_to_flash, FA_READ);		
	if (res != FR_OK)
	{
		SerialConsoleWriteString("Could not open bin file!\r\n");
	}
    else{
        uint32_t size_of_bin = (uint32_t)f_size(&file_object);
        for(uint32_t i=0; i<360;i++){

            uint32_t readBytes = 0, bytesLeft = len, BufferOffset = 0;

            res = f_read(&file_object, readBuffer, bytesLeft, &readBytes);

            if(res != FR_OK){
                SerialConsoleWriteString("Bin Read Failed!\r\n");
            }
            // Erase NVM
            rtr_code = erase_nvm(i);
            #if __DEBUG__
            if(rtr_code==STATUS_OK){
                SerialConsoleWriteString("Memory Erased \r\n");
            }
            #endif
            // Write BIN to NVM
            rtr_code = write_nvm(i, readBuffer);
            #if __DEBUG__
            if(rtr_code==STATUS_OK){
                SerialConsoleWriteString("Bin Written to NVM\r\n");
                
            }
            #endif
            // Perform CRC on the NVM
            rtr_code = perform_nvm_crc(readBuffer, i);
            #if __DEBUG__
            if(rtr_code==STATUS_OK){
                SerialConsoleWriteString("CRC Passed\r\n");
            }
            snprintf(h,63,"Number of Rows %d\r\n", i);
            SerialConsoleWriteString(h);
            #endif
        }
    }
    f_close(&file_object);
    return rtr_code;
}
