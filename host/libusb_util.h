#pragma once

#include <libusb.h>

struct dev_id {
	uint16_t vendor_id;
	uint16_t product_id;
};

/* Find any USB devices in the system matching the given Vendor and
 * Product ID */
libusb_device **find_matching_usb_devs(const struct dev_id *dev_ids);

/* structure describing a single matching interface found */
struct usb_interface_match {
	/* libusb device E*/
	libusb_device *usb_dev;
	/* Vendor ID of the device running matching interface */
	uint16_t vendor;
	/* Product ID of the device running matching interface */
	uint16_t product;
	/* USB Bus Address */
	uint8_t addr;
	/* configuration of matching interface */
	uint8_t configuration;
	/* interface number of matching interface */
	uint8_t interface;
	/* altsetting of matching interface */
	uint8_t altsetting;
	/* bInterfaceClass of matching interface */
	uint8_t class;
	/* bInterfaceSubClass of matching interface */
	uint8_t sub_class;
	/* bInterfaceProtocol of matching interface */
	uint8_t protocol;
	/* index of string descriptor of matching interface */
	uint8_t string_idx;
};

int dev_find_matching_interfaces(libusb_device *dev, int class, int sub_class, int protocol,
				 struct usb_interface_match *out, unsigned int out_len);

int usb_match_interfaces(libusb_context *ctx, const struct dev_id *dev_ids,
			 int class, int sub_class, int protocol,
			 struct usb_interface_match *out, unsigned int out_len);

libusb_device_handle *usb_open_claim_interface(libusb_context *ctx,
					       const struct usb_interface_match *ifm);
