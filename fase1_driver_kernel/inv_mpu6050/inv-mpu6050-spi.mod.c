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
	"\x18\x00\x00\x00\xbb\x43\x66\x5d"
	"regmap_write\0\0\0\0"
	"\x1c\x00\x00\x00\x0a\xbe\xc7\x3b"
	"spi_get_device_id\0\0\0"
	"\x1c\x00\x00\x00\x56\x7b\x26\xdc"
	"inv_mpu_core_probe\0\0"
	"\x14\x00\x00\x00\xc2\xa3\xf9\xeb"
	"_dev_err\0\0\0\0"
	"\x1c\x00\x00\x00\xfd\x60\xf3\x1b"
	"driver_unregister\0\0\0"
	"\x20\x00\x00\x00\x27\x95\x3d\xad"
	"device_get_match_data\0\0\0"
	"\x20\x00\x00\x00\xc7\x34\x94\x0a"
	"__spi_register_driver\0\0\0"
	"\x18\x00\x00\x00\x96\x83\xb5\x98"
	"inv_mpu_pmops\0\0\0"
	"\x20\x00\x00\x00\xcd\x4b\x8d\x8f"
	"__devm_regmap_init_spi\0\0"
	"\x18\x00\x00\x00\xc7\xdf\x30\xcd"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "inv-mpu6050");

MODULE_ALIAS("spi:mpu6000");
MODULE_ALIAS("spi:mpu6500");
MODULE_ALIAS("spi:mpu6515");
MODULE_ALIAS("spi:mpu6880");
MODULE_ALIAS("spi:mpu9250");
MODULE_ALIAS("spi:mpu9255");
MODULE_ALIAS("spi:icm20608");
MODULE_ALIAS("spi:icm20608d");
MODULE_ALIAS("spi:icm20609");
MODULE_ALIAS("spi:icm20689");
MODULE_ALIAS("spi:icm20600");
MODULE_ALIAS("spi:icm20602");
MODULE_ALIAS("spi:icm20690");
MODULE_ALIAS("spi:iam20680");
MODULE_ALIAS("acpi*:INVN6000:*");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6000");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6000C*");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6500");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6500C*");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6515");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6515C*");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6880");
MODULE_ALIAS("of:N*T*Cinvensense,mpu6880C*");
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

MODULE_INFO(srcversion, "E7828449F92F6170AC341D5");
