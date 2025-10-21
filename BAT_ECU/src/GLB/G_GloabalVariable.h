#ifndef __G_GLOABALVARIABLE_H__
#define __G_GLOABALVARIABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/can.h>
#include <time.h>
#include <string.h>

#include <linux/types.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/fs.h>

#include <net/if.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#define PCS_STOP 0x03		// 外部急停，充电桩急停输入
#define DOOR_OPEN 0x04		// 门禁故障检测。+
#define EMERGENCY_STOP 0x05 // 急停故障，emcu0故障的第5bit
#define BMS_COM_FAULT 0x06	// 和bms通讯故障 ecmu 0 的第六bit
// #define BMS_CURR_FAULT   0x07    // bms电流异常 ecmu 0 的第7bit
// #define DCMETER_COM_FAULT 0x12      //电表通讯故障  emcu1 的第2字节
#define SMOKE_FAULT 0x09	// 烟雾故障  emcu0 的第9字节
#define PHY_LINK_FAULT 0x28 // PHY连接故障   emcu2 的第8字节
#define ANGLE_FAULT 0x29	// 倾角故障   emcu2 的第9字节
#define SD_FAULT 0x31		// sd卡故障   emcu3 的第1字节
// #define INSIDE_NTC_FAULT 0x32      //内部温度故障  emcu3 的第2字节
// #define OUTSIDE_COM_FAULT 0x33      //外部温度传感器故障  emcu3 的第3字节

#define SET_ERROR 0
#define SET_RECOVER 1

#define ALL_FAULT 0xFF // 获取总故障的时候使用。

// #define USB_MOUNT_POINT "/media/usb0"
#define USB_MOUNT_POINT "/mnt/sda"
// #########################################################################################//

// #########################################################################################//
typedef struct
{
	uint8_t flag;
	uint32_t ip;

} Setting_t;
extern Setting_t setting;
// #########################################################################################//

// #########################################################################################//

#define RESULT_OK 0
#define RESULT_FAIL -1

// #########################################################################################//

// #########################################################################################//

#define OTAIDLE 0x0000
#define XMODEMISTTRANFERINGFILE 0x0001
#define XMODEMNORMALTERMINATION 0x0002
#define XMODEMOUTTIMETERMINATION 0x0004
#define XMODEMABORTTERMINATION 0x0006
#define FILEISDECRYPTIIONING 0x0008
#define FILEDECRYPTIONNORMALTERMINATION 0x0010
#define OTASTARTRUNNING 0x0080

#define OTASUCCESS 0x0100
#define OTAFAILED 0x0200

// #########################################################################################//

// #########################################################################################//

typedef enum
{
	ECU = 1,
	BCU,
	BMU,
	AC,
	ACP,
	DCDC
} OTADEVICETYPE;

// #########################################################################################//

// #########################################################################################//
#define OTAFILENAMEMAXLENGTH 128
#define MAX_FILE_COUNT 20

typedef struct
{
	unsigned char OTAFileType;
	char OTAFilename[OTAFILENAMEMAXLENGTH];
	char OTAUdsSblFilename[MAX_FILE_COUNT][OTAFILENAMEMAXLENGTH];
	char OTAUdsFilename[MAX_FILE_COUNT][OTAFILENAMEMAXLENGTH];
	unsigned int deviceID;
	unsigned char deviceType;
	unsigned char OTAStart;
	unsigned char multDeviceOTA;
	unsigned char multDeviceOTANum;

	unsigned char UpDating;

} OTAObject;

// #########################################################################################//

// #########################################################################################//

typedef struct
{
	/* Is this CAN (0) or CAN FD (1) */
	uint8_t ProtocolMode;

	/* Is Extended frame */
	uint8_t Extended;

	/* Length */
	uint8_t Length;

	/* RTR */
	uint8_t Remote;

	/* Error */
	uint8_t Error;

	/* Bit Rate Switch. Possible values 0 or 1. Valid only if ProtocolMode indicates CAN FD */
	uint8_t BRS;

	/* Error State Indicator.  Possible values 0 or 1. Valid only if ProtocolMode indicates CAN FD */
	uint8_t ESI;

	/* Data Length Code. Possible values 0-15. Valid only if ProtocolMode indicates CAN FD */
	uint8_t DLC;

	/* CAN ID */
	uint32_t ID;

	/* Reserved */
	uint32_t Reserved;

	/*
	  TIMESTAMP_NOT_REQUIRED is a macro that will be defined by Target teams
	  PIL, C166, FM5, xPC if they do not require the timestamp field during code
	  generation. By default, timestamp is defined. If the targets do not require
	  the timestamp field, they should define the macro TIMESTAMP_NOT_REQUIRED before
	  including this header file for code generation.
	*/
#ifndef TIMESTAMP_NOT_REQUIRED
	/* Timestamp */
	double Timestamp;
#endif

	/* Data field */
	uint8_t Data[64];

} CANFD_MESSAGE;

typedef struct
{

	/* Is Extended frame */
	uint8_t Extended;

	/* Length */
	uint8_t Length;

	/* RTR */
	uint8_t Remote;

	/* Error */
	uint8_t Error;

	/* CAN ID */
	uint32_t ID;

	/*
	  TIMESTAMP_NOT_REQUIRED is a macro that will be defined by Target teams
	  PIL, C166, FM5, xPC if they do not require the timestamp field during code
	  generation. By default, timestamp is defined. If the targets do not require
	  the timestamp field, they should define the macro TIMESTAMP_NOT_REQUIRED before
	  including this header file for code generation.
	*/
#ifndef TIMESTAMP_NOT_REQUIRED
	/* Timestamp */
	double Timestamp;
#endif

	/* Data field */
	uint8_t Data[8];

} CAN_MESSAGE;

// #########################################################################################//

// #########################################################################################//

/*
 * CAN bit-timing parameters
 */
struct can_bittiming
{
	__u32 bitrate;		/* Bit-rate in bits/second */
	__u32 sample_point; /* Sample point in one-tenth of a percent */
	__u32 tq;			/* Time quanta (TQ) in nanoseconds */
	__u32 prop_seg;		/* Propagation segment in TQs */
	__u32 phase_seg1;	/* Phase buffer segment 1 in TQs */
	__u32 phase_seg2;	/* Phase buffer segment 2 in TQs */
	__u32 sjw;			/* Synchronisation jump width in TQs */
	__u32 brp;			/* Bit-rate prescaler */
};

/*
 * CAN harware-dependent bit-timing constant
 */
struct can_bittiming_const
{
	char name[16];	 /* Name of the CAN controller hardware */
	__u32 tseg1_min; /* Time segement 1 = prop_seg + phase_seg1 */
	__u32 tseg1_max;
	__u32 tseg2_min; /* Time segement 2 = phase_seg2 */
	__u32 tseg2_max;
	__u32 sjw_max; /* Synchronisation jump width */
	__u32 brp_min; /* Bit-rate prescaler */
	__u32 brp_max;
	__u32 brp_inc;
};

/*
 * CAN clock parameters
 */
struct can_clock
{
	__u32 freq; /* CAN system clock frequency in Hz */
};

/*
 * CAN operational and error states
 */
enum can_state
{
	CAN_STATE_ERROR_ACTIVE = 0, /* RX/TX error count < 96 */
	CAN_STATE_ERROR_WARNING,	/* RX/TX error count < 128 */
	CAN_STATE_ERROR_PASSIVE,	/* RX/TX error count < 256 */
	CAN_STATE_BUS_OFF,			/* RX/TX error count >= 256 */
	CAN_STATE_STOPPED,			/* Device is stopped */
	CAN_STATE_SLEEPING,			/* Device is sleeping */
	CAN_STATE_MAX
};

/*
 * CAN bus error counters
 */
struct can_berr_counter
{
	__u16 txerr;
	__u16 rxerr;
};

/*
 * CAN controller mode
 */
struct can_ctrlmode
{
	__u32 mask;
	__u32 flags;
};

/*
 * CAN device statistics
 */
struct can_device_stats
{
	__u32 bus_error;		/* Bus errors */
	__u32 error_warning;	/* Changes to error warning state */
	__u32 error_passive;	/* Changes to error passive state */
	__u32 bus_off;			/* Changes to bus off state */
	__u32 arbitration_lost; /* Arbitration lost errors */
	__u32 restarts;			/* CAN controller re-starts */
};

/*
 * CAN netlink interface
 */
enum
{
	IFLA_CAN_UNSPEC,
	IFLA_CAN_BITTIMING,
	IFLA_CAN_BITTIMING_CONST,
	IFLA_CAN_CLOCK,
	IFLA_CAN_STATE,
	IFLA_CAN_CTRLMODE,
	IFLA_CAN_RESTART_MS,
	IFLA_CAN_RESTART,
	IFLA_CAN_BERR_COUNTER,
	__IFLA_CAN_MAX
};

#define IFLA_CAN_MAX (__IFLA_CAN_MAX - 1)

// #########################################################################################//

// #########################################################################################//

typedef struct
{
	uint16_t year;	  /**< @brief Year       */
	uint16_t month;	  /**< @brief Month      */
	uint16_t day;	  /**< @brief Day        */
	uint16_t hour;	  /**< @brief Hour       */
	uint16_t minutes; /**< @brief Minutes    */
	uint8_t seconds;  /**< @brief Seconds    */
} Rtc_Ip_TimedateType;
#endif