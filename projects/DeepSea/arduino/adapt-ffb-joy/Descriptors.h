/*
  Force Feedback Joystick
  USB HID descriptors for a force feedback joystick.  

  This code is for Microsoft Sidewinder Force Feedback Pro joystick
  with some room for additional extra controls.

  Copyright 2012  Tero Loimuneva (tloimu [at] gmail [dot] com)
  MIT License.

  Some code is based on LUFA Library, for which uses MIT license:

  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/


#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

#define ENABLE_JOYSTICK_SERIAL

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

		#include <avr/pgmspace.h>

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */

		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;

			// Joystick HID Interface
			USB_Descriptor_Interface_t            HID_Interface;

		// Joystick stuff

			USB_HID_Descriptor_HID_t              HID_JoystickHID;
			USB_Descriptor_Endpoint_t             HID_ReportOUTEndpoint;
	        USB_Descriptor_Endpoint_t             HID_ReportINEndpoint;

#ifdef ENABLE_JOYSTICK_SERIAL
		// Serial stuff

		// First CDC Control Interface
		USB_Descriptor_Interface_Association_t   CDC1_IAD;
		USB_Descriptor_Interface_t               CDC1_CCI_Interface;
		USB_CDC_Descriptor_FunctionalHeader_t    CDC1_Functional_Header;
		USB_CDC_Descriptor_FunctionalACM_t       CDC1_Functional_ACM;
		USB_CDC_Descriptor_FunctionalUnion_t     CDC1_Functional_Union;
		USB_Descriptor_Endpoint_t                CDC1_ManagementEndpoint;

		// First CDC Data Interface
		USB_Descriptor_Interface_t               CDC1_DCI_Interface;
		USB_Descriptor_Endpoint_t                CDC1_DataOutEndpoint;
		USB_Descriptor_Endpoint_t                CDC1_DataInEndpoint;
#endif // ENABLE_JOYSTICK_SERIAL

		} USB_Descriptor_Configuration_t;

		// Joystick stuff

		/** Endpoint number of the Joystick HID reporting IN endpoint. */
		#define JOYSTICK_EPNUM            1

		/** Size in bytes of the Joystick HID reporting IN endpoint. */
		#define JOYSTICK_EPSIZE           64

		/** Descriptor header type value, to indicate a HID class HID descriptor. */
		#define DTYPE_HID                 0x21

		/** Descriptor header type value, to indicate a HID class HID report descriptor. */
		#define DTYPE_Report              0x22

		/** Endpoint number of the Joystick HID reporting IN endpoint. */
		#define FFB_EPNUM            2

		/** Size in bytes of the Joystick FFB HID reporting OUT endpoint. */
		#define FFB_EPSIZE           64

		// Serial device stuff

		#define CDC1_TX_EPNUM	3
		#define CDC1_RX_EPNUM	4
		#define CDC1_NOTIFICATION_EPNUM        5

		/** Size in bytes of the CDC device-to-host notification IN endpoints. */
		#define CDC_NOTIFICATION_EPSIZE        8

		/** Size in bytes of the CDC data IN and OUT endpoints. */
		#define CDC_TXRX_EPSIZE                16

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint8_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif

