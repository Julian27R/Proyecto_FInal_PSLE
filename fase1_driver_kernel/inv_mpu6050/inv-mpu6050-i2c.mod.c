#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const char ____versions[]
__used __section("__versions") =
	"\x1c\x00\x00\x00\xd0\x96\xff\xc8"
	"is_acpi_device_node\0"
	"\x18\x00\x00\x00\xbb\x43\x66\x5d"
	"regmap_write\0\0\0\0"
	"\x24\x00\x00\x00\xd6\x39\x88\x7f"
	"i2c_acpi_get_i2c_resource\0\0\0"
	"\x24\x00\x00\x00\x12\x26\x5a\x6d"
	"i2c_client_get_device_id\0\0\0\0"
	"\x1c\x00\x00\x00\x56\x7b\x26\xdc"
	"inv_mpu_core_probe\0\0"
	"\x20\x00\x00\x00\x94\x4f\xbd\xd1"
	"acpi_dev_get_resources\0\0"
	"\x20\x00\x00\x00\x2a\xfd\x76\xdc"
	"__devm_regmap_init_i2c\0\0"
	"\x1c\x00\x00\x00\xcb\xf6\xfd\xf0"
	"__stack_chk_fail\0\0\0\0"
	"\x1c\x00\x00\x00\xec\x36\x97\x7e"
	"i2c_register_driver\0"
	"\x14\x00\x00\x00\xc2\xa3\xf9\xeb"
	"_dev_err\0\0\0\0"
	"\x20\x00\x00\x00\xe9\xba\x58\xd4"
	"i2c_unregister_device\0\0\0"
	"\x20\x00\x00\x00\xa6\x31\x60\x9f"
	"i2c_new_client_device\0\0\0"
	"\x18\x00\x00\x00\xe6\x8c\x5f\x0f"
	"i2c_mux_alloc\0\0\0"
	"\x14\x00\x00\x00\xc5\x77\xfe\xc2"
	"_dev_warn\0\0\0"
	"\x20\x00\x00\x00\x27\x95\x3d\xad"
	"device_get_match_data\0\0\0"
	"\x10\x00\x00\x00\x63\xb6\xc0\xf9"
	"strlcat\0"
	"\x1c\x00\x00\x00\x75\x55\x01\x07"
	"acpi_match_device\0\0\0"
	"\x10\x00\x00\x00\x39\xe6\x64\xdd"
	"strscpy\0"
	"\x24\x00\x00\x00\x02\x31\x5d\xf4"
	"device_get_named_child_node\0"
	"\x18\x00\x00\x00\x96\x83\xb5\x98"
	"inv_mpu_pmops\0\0\0"
	"\x20\x00\x00\x00\x00\x26\x5a\x5e"
	"i2c_mux_del_adapters\0\0\0\0"
	"\x18\x00\x00\x00\x81\x04\x22\xc0"
	"i2c_del_driver\0\0"
	"\x1c\x00\x00\x00\x9b\xf5\xe8\xef"
	"fwnode_handle_put\0\0\0"
	"\x10\x00\x00\x00\x85\xba\x9c\x34"
	"strchr\0\0"
	"\x1c\x00\x00\x00\xc1\x5f\x81\x3d"
	"i2c_mux_add_adapter\0"
	"\x24\x00\x00\x00\xcb\x99\x66\xdc"
	"acpi_dev_free_resource_list\0"
	"\x18\x00\x00\x00\xc7\xdf\x30\xcd"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "inv-mpu6050,i2c-mux");

MODULE_ALIAS("acpi*:INVN6500:*");
MODULE_ALIAS("i2c:mpu6050");
MODULE_ALIAS("i2c:mpu6500");
MODULE_ALIAS("i2c:mpu6515");
MODULE_ALIAS("i2c:mpu6880");
MODULE_ALIAS("i2c:mpu9150");
MODULE_ALIAS("i2c:mpu9250");
MODULE_ALIAS("i2c:mpu9255");
MODULE_ALIAS("i2c:icm20608");
MODULE_ALIAS("i2c:icm20608d");
MODULE_ALIAS("i2c:icm20609");
MODULE_ALIAS("i2c:icm20689");
MODULE_ALIAS("i2c:icm20600");
MODULE_ALIAS("i2c:icm20602");
MODULE_ALIAS("i2c:icm20690");
MODULE_ALIAS("i2c:iam20680");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6050");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6050C*");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6500");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6500C*");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6515");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6515C*");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6880");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6880C*");
MODULE_ALIAS("of:N*T*Cinvensense,mpu9150");
MODULE_ALIAS("of:N*T*Cinvensense,mpu9150C*");
MODULE_ALIAS("of:N*T*Cinvensense,mpu9250");
MODULE_ALIAS("of:N*T*Cinvensense,mpu9250C*");
MODULE_ALIAS("of:N*T*Cinvensense,mpu9255");
MODULE_ALIAS("of:N*T*Cinvensense,mpu9255C*");
MODULE_ALIAS("of:N*T*Cinvensense,icm20608");
MODULE_ALIAS("of:N*T*Cinvensense,icm20608C*");
MODULE_ALIAS("of:N*T*Cinvensense,icm20608d");
MODULE_ALIAS("of:N*T*Cinvensense,icm20608dC*");
MODULE_ALIAS("of:N*T*Cinvensense,icm20609");
MODULE_ALIAS("of:N*T*Cinvensense,icm20609C*");
MODULE_ALIAS("of:N*T*Cinvensense,icm20689");
MODULE_ALIAS("of:N*T*Cinvensense,icm20689C*");
MODULE_ALIAS("of:N*T*Cinvensense,icm20600");
MODULE_ALIAS("of:N*T*Cinvensense,icm20600C*");
MODULE_ALIAS("of:N*T*Cinvensense,icm20602");
MODULE_ALIAS("of:N*T*Cinvensense,icm20602C*");
MODULE_ALIAS("of:N*T*Cinvensense,icm20690");
MODULE_ALIAS("of:N*T*Cinvensense,icm20690C*");
MODULE_ALIAS("of:N*T*Cinvensense,iam20680");
MODULE_ALIAS("of:N*T*Cinvensense,iam20680C*");

MODULE_INFO(srcversion, "E259E31AC9608CD16FF7D6E");
