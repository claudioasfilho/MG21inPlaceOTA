/***********************************************************************************************//**
 * \file   app.c
 * \brief  This example shows how to do Bluetooth OTA update under application control.
 *
 *  For more details about the Bluetooth OTA, refer to application note AN1086.
 *
 ***************************************************************************************************
 * <b> (C) Copyright 2018 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/

/* Bluetooth stack headers */
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"

#include "app.h"

#if DEBUG_LEVEL
/* printf debugging is enabled */
#include "retargetserial.h"
#include <stdio.h>
#define uart_flush RETARGET_SerialFlush

#else
/* debug prints are DISABLED - replace printf etc. with empty implementation */
#define printf(fmt, ...) (0)
#define uart_flush() (0)

#endif

#include "btl_interface.h"
#include "btl_interface_storage.h"

static void bootMessage(struct gecko_msg_system_boot_evt_t *bootevt);

static BootloaderInformation_t bldInfo;
static BootloaderStorageSlot_t slotInfo;

/* OTA variables */
static uint32 ota_image_position = 0;
static uint8 ota_in_progress = 0;
static uint8 ota_image_finished = 0;
static uint16 ota_time_elapsed = 0;

static int32_t get_slot_info()
{
	int32_t err;

	bootloader_getInfo(&bldInfo);
	printf("Gecko bootloader version: %u.%u\r\n", (bldInfo.version & 0xFF000000) >> 24, (bldInfo.version & 0x00FF0000) >> 16);

	err = bootloader_getStorageSlotInfo(1, &slotInfo);

	if(err == BOOTLOADER_OK)
	{
		printf("Slot 0 starts @ 0x%8.8x, size %u bytes\r\n", slotInfo.address, slotInfo.length);
	}
	else
	{
		printf("Unable to get storage slot info, error %x\r\n", err);
	}

	return(err);
}

static void erase_slot_if_needed()
{
	uint32_t offset = 0;
	uint8_t buffer[256];
	int i;
	int dirty = 0;
	int32_t err = BOOTLOADER_OK;
	int num_blocks = 0;

	/* check the download area content by reading it in 256-byte blocks */

	num_blocks = slotInfo.length / 256;

	while((dirty == 0) && (offset < 256*num_blocks) && (err == BOOTLOADER_OK))
	{
		err = bootloader_readStorage(0, offset, buffer, 256);
		if(err == BOOTLOADER_OK)
		{
			i=0;
			while(i<256)
			{
				if(buffer[i++] != 0xFF)
				{
					dirty = 1;
					break;
				}
			}
			offset += 256;
		}
		printf(".");
	}

	if(err != BOOTLOADER_OK)
	{
		printf("error reading flash! %x\r\n", err);
	}
	else if(dirty)
	{
		printf("download area is not empty, erasing...\r\n");
		bootloader_eraseStorageSlot(0);
		printf("done\r\n");
	}
	else
	{
		printf("download area is empty\r\n");
	}

	return;
}

static void print_progress()
{
	// estimate transfer speed in kbps
	int kbps = ota_image_position*8/(1024*ota_time_elapsed);

	printf("pos: %u, time: %u, kbps: %u\r\n", ota_image_position, ota_time_elapsed, kbps);
}

void appMain(gecko_configuration_t *pconfig)
{

#if DISABLE_SLEEP > 0
	pconfig->sleep.flags = 0;
#endif

#if DEBUG_LEVEL
	RETARGET_SerialInit();
#endif

	  // Initialize stack
	  gecko_init(pconfig);

	  while (1) {
	    /* Event pointer for handling events */
	    struct gecko_cmd_packet* evt;

#if DEBUG_LEVEL
	    /* if there are no events pending then the next call to gecko_wait_event() may cause
	     * device go to deep sleep. Make sure that debug prints are flushed before going to sleep */
	    if (!gecko_event_pending()) {
	        uart_flush();
	    }
#endif

	    /* Check for stack event. */
	    evt = gecko_wait_event();

	    /* Handle events */
	    switch (BGLIB_MSG_ID(evt->header)) {
	      /* This boot event is generated when the system boots up after reset.
	       * Do not call any stack commands before receiving the boot event.
	       * Here the system is set to start advertising immediately after boot procedure. */
	      case gecko_evt_system_boot_id:
#if DEBUG_LEVEL
	    	  bootMessage(&(evt->data.evt_system_boot));

#endif
	    	  /* 1 second soft timer, used for performance statistics during OTA file upload */
	    	  gecko_cmd_hardware_set_soft_timer(32768, 0, 0);

	        /* set advertising interval to 100 ms */
	        gecko_cmd_le_gap_set_advertise_timing(0, 160, 160, 0, 0);

	        /* Start general advertising and enable connections. */
	        printf("boot event - starting advertising\r\n");
	        gecko_cmd_le_gap_start_advertising(0, le_gap_general_discoverable, le_gap_connectable_scannable);

	        /* bootloader init must be called before calling other bootloader_xxx API calls */
	        bootloader_init();

	        /* read slot information from bootloader */
	        if(get_slot_info() == BOOTLOADER_OK)
	        {
	        	/* the download area is erased here (if needed), prior to any connections are opened */
	        	erase_slot_if_needed();
	        }
	        else
	        {
	        	printf("Check that you have installed correct type of Gecko bootloader!\r\n");
	        }
	        break;

	      case gecko_evt_le_connection_opened_id:
	    	  printf("connection opened\r\n");
	    	  break;

	      case gecko_evt_le_connection_closed_id:
	    	  printf("connection closed, reason: 0x%2.2x\r\n", evt->data.evt_le_connection_closed.reason);

	    	  if (ota_image_finished) {
	    		  printf("Installing new image\r\n");
#if DEBUG_LEVEL
	    		  uart_flush();
#endif
	    		  bootloader_setImageToBootload(0);
	    		  bootloader_rebootAndInstall();
	    	  } else {
	    		  /* Restart advertising after client has disconnected */
	    		  gecko_cmd_le_gap_start_advertising(0, le_gap_general_discoverable, le_gap_connectable_scannable);
	    	  }
	    	  break;

	      case gecko_evt_hardware_soft_timer_id:
	    	  if(ota_in_progress)
	    	  {
	    		  ota_time_elapsed++;
	    		  print_progress();
	    	  }
	    	  break;

	    	  /* write operations to ota_data, ot_control characteristics are handled here :*/
	      case gecko_evt_gatt_server_user_write_request_id:
	      {
	    	  uint32_t connection = evt->data.evt_gatt_server_user_write_request.connection;
	    	  uint32_t characteristic = evt->data.evt_gatt_server_user_write_request.characteristic;
	    	  if(characteristic == gattdb_ota_control)
	    	  {
	    		  switch(evt->data.evt_gatt_server_user_write_request.value.data[0])
	    		  {
	    		  case 0://Erase and use slot 0
	    			  // NOTE: download are is NOT erased here, because the long blocking delay would result in supervision timeout
	    			  //bootloader_eraseStorageSlot(0);
	    			  ota_image_position=0;
	    			  ota_in_progress=1;
	    			  break;
	    		  case 3://END OTA process
	    			  //wait for connection close and then reboot
	    			  ota_in_progress=0;
	    			  ota_image_finished=1;
	    			  printf("upload finished. received file size %u bytes\r\n", ota_image_position);
	    			  uart_flush();
	    			  break;
	    		  default:
	    			  break;
	    		  }
	    	  } else if(characteristic == gattdb_ota_data)
	    	  {
	    		  if(ota_in_progress)
	    		  {
	    			  bootloader_writeStorage(0,//use slot 0
	    					  ota_image_position,
							  evt->data.evt_gatt_server_user_write_request.value.data,
							  evt->data.evt_gatt_server_user_write_request.value.len);
	    			  ota_image_position+=evt->data.evt_gatt_server_user_write_request.value.len;
	    		  }
	    	  }
	    	  gecko_cmd_gatt_server_send_user_write_response(connection,characteristic,0);
	      }
	    	  break;

	      default:
	        break;
	    }
	  }

}

static void bootMessage(struct gecko_msg_system_boot_evt_t *bootevt)
{
	bd_addr local_addr;
	int i;

	printf("stack version: %u.%u.%u\r\n", bootevt->major, bootevt->minor, bootevt->patch);
	local_addr = gecko_cmd_system_get_bt_address()->address;

	printf("local BT device address: ");
	for(i=0;i<5;i++)
	{
		printf("%2.2x:", local_addr.addr[5-i]);
	}
	printf("%2.2x\r\n", local_addr.addr[0]);

}
