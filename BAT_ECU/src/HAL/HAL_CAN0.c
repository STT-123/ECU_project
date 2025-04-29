#define _GNU_SOURCE
#include "HAL_CAN0.h"

#include "./DRV/LOG/Drv_ZLog.h"
#include "./GLB/G_GloabalVariable.h"

#define GET_STATE 1
#define GET_RESTART_MS 2
#define GET_BITTIMING 3
#define GET_CTRLMODE 4
#define GET_CLOCK 5
#define GET_BITTIMING_CONST 6
#define GET_BERR_COUNTER 7
#define GET_XSTATS 8

struct get_req {
	struct nlmsghdr n;
	struct rtgenmsg g;
};


#define parse_rtattr_nested(tb, max, rta) \
	(parse_rtattr((tb), (max), RTA_DATA(rta), RTA_PAYLOAD(rta)))
static void parse_rtattr(struct rtattr **tb, int max, struct rtattr *rta, int len);
/*
 * 函数名称：HAL_can0_init_all
 * 功能描述：初始化 CAN0 设备，包括网络配置、套接字绑定
 * 输出参数：
 *      fd：返回 CAN socket 文件描述符
 * 返回值：
 *      0 表示成功
 *      非 0 表示失败
 */
bool HAL_can0_init(int *fd)
{
    zlog_info(debug_out, "开始初始化 CAN0...\n");

    if (!HAL_can0_ifconfig_init())
    {
        zlog_error(debug_out, "HAL_can1_ifconfig_init 失败\n");
        return false;
    }
    zlog_info(debug_out, "CAN0 网络配置成功\n");

    if (!HAL_can0_band_init(fd))
    {
        zlog_error(debug_out, "HAL_can0_band_init 失败\n");
        return false;
    }
    zlog_info(debug_out, "CAN0 绑定成功，fd = %d\n", *fd);

    return true;
}


/*
 * 函数名称：can_ifconfig_up
 * 功能描述：创建CAN网络
 * 输入参数：device：物理设备名称，如"CAN1"
 *         bitrate:速率，如250000（250Kbps)
 * 输出参数：0有效，其他失效
 */
bool HAL_can0_ifconfig_init(void)
{
	FILE* fp = NULL;
	bool state = false;
	char buf[128]={0};

	snprintf(buf,127,"ifconfig %s down",PORT_CAN0_DEVICE_NAME);
	system(buf);
	snprintf(buf,127,"ip link set %s type can bitrate %d", PORT_CAN0_DEVICE_NAME, PORT_CAN0_CAN_BITRATE);
	system(buf);
	snprintf(buf,127,"ifconfig %s up",PORT_CAN0_DEVICE_NAME);
	system(buf);

	//检查网络是否存在
	snprintf(buf,127,"ifconfig | grep %s",PORT_CAN0_DEVICE_NAME);
	fp = popen(buf, "r");
	memset(buf,0,128);
	if(fgets(buf, 128, fp) != NULL)
	{
		state = true;
	}
	pclose(fp);

	return state;
}

/*
 * 函数名称：can_band
 * 功能描述：创绑定CAN设备
 * 输入参数：device：物理设备名称，如"CAN1"
 *         fd:SOCKET句柄
 * 输出参数：0有效，其他失效
 */

bool HAL_can0_band_init(int *fd)
{
    struct ifreq m_ifr;
    struct sockaddr_can m_addr;
    // 创建 CAN 的套接字
    *fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (*fd < 0) {
        return false; // 创建套接字失败
    }

    // 指定 CAN0 设备
    strcpy(m_ifr.ifr_name, PORT_CAN0_DEVICE_NAME);
    if (ioctl(*fd, SIOCGIFINDEX, &m_ifr) < 0) {
        close(*fd); // 关闭套接字
        return false; // 获取接口索引失败
    }

    // 将套接字与 CAN0 绑定
    m_addr.can_family = AF_CAN;
    m_addr.can_ifindex = m_ifr.ifr_ifindex;

    if (bind(*fd, (struct sockaddr *)&m_addr, sizeof(m_addr)) < 0) {
        close(*fd); // 关闭套接字
        return false; // 绑定失败
    }
    return true; // 成功
}

/*
 * 函数名称：can_write
 * 功能描述：CAN设备写数据
 * 输入参数：fd:SOCKET句柄
 *          pFrame：CAN帧数据指针
 * 输出参数：0有效，其他失效
 */
bool HAL_can0_write(int fd,struct canfd_frame *pFrame)
{
	int canState;
	int retval=0, len = 0;
	fd_set fs_write;
	static struct timeval tv_timeout;
	FD_ZERO (&fs_write);
	FD_SET (fd, &fs_write);
	tv_timeout.tv_sec = 0;
	tv_timeout.tv_usec = 1000;
	while(1)
	{
		retval = select (fd + 1, NULL, &fs_write, NULL, &tv_timeout);
		if (retval>0)
		{
			len=write(fd, pFrame, sizeof(struct canfd_frame));
			HAL_can0_get_state((const char *)"can0", &canState);

			if(len == sizeof(struct canfd_frame))
				return true;
			else
				return false;
	    }
		else
		{
			return false;
		}

	}
	return false;
}

/*
 * 函数名称：can_read
 * 功能描述：CAN设备读数据
 * 输入参数：fd:SOCKET句柄
 *          pFrame：CAN帧数据指针
 *          msTimeout：超时时间MS
 * 输出参数：0有效，其他失效
 */
bool HAL_can0_read(int fd, struct canfd_frame *pFrame,unsigned int msTimeout)
{
    int retval = 0, len = 0;
    fd_set   fs_read;
    struct timeval tv_timeout;

    FD_ZERO(&fs_read);
	FD_SET (fd, &fs_read);
	tv_timeout.tv_sec = msTimeout/1000;
	tv_timeout.tv_usec = (msTimeout%1000)*1000;
	retval = select (fd + 1, &fs_read, NULL, NULL, &tv_timeout);
	if (retval > 0)
	{
		if (len == sizeof(struct canfd_frame))
        {
            return true; // 成功读取完整的一帧数据
        }
        else
        {
            return false; // 读取失败或数据不完整
        }
	}
	else if (retval == 0)
	{
		return true;
    }

    return false;
}

/*
 * 函数名称：can_close
 * 功能描述：CAN关闭
 * 输入参数：fd:SOCKET句柄
 * 输出参数：无
 */
void HAL_can0_closeEx(int *fd)
{
	if(*fd>=0)
	{
		close(*fd);
		*fd=-1;
	}
}

bool HAL_can0_set_filter(int fd, struct can_filter *__can_filter , int  num)
{
 struct can_filter rfilter[num];
 int i;
 if(num<=0)
  return true;

 for(i=0;i<num;i++)
 {
  rfilter[i].can_id = __can_filter[i].can_id;
  rfilter[i].can_mask = __can_filter[i].can_mask ; // can_id &mask== can_id & mask
 }
 setsockopt( fd, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));//设置规则
 return true;
}


static void parse_rtattr(struct rtattr **tb, int max, struct rtattr *rta, int len)
{
	memset(tb, 0, sizeof(*tb) * max);
	while (RTA_OK(rta, len)) {
		if (rta->rta_type <= max) {
			tb[rta->rta_type] = rta;
		}

		rta = RTA_NEXT(rta, len);
	}
}


static int send_dump_request(int fd, int family, int type)
{
	struct get_req req;

	memset(&req, 0, sizeof(req));

	req.n.nlmsg_len = sizeof(req);
	req.n.nlmsg_type = type;
	req.n.nlmsg_flags = NLM_F_REQUEST | NLM_F_ROOT | NLM_F_MATCH;
	req.n.nlmsg_pid = 0;
	req.n.nlmsg_seq = 0;

	req.g.rtgen_family = family;

	return send(fd, (void *)&req, sizeof(req), 0);
}



static int do_get_nl_link(int fd, __u8 acquire, const char *name, void *res)
{
	struct sockaddr_nl peer;

	char cbuf[64];
	char nlbuf[1024 * 8];

	int ret = -1;
	int done = 0;

	struct iovec iov = {
		.iov_base = (void *)nlbuf,
		.iov_len = sizeof(nlbuf),
	};

	struct msghdr msg = {
		.msg_name = (void *)&peer,
		.msg_namelen = sizeof(peer),
		.msg_iov = &iov,
		.msg_iovlen = 1,
		.msg_control = &cbuf,
		.msg_controllen = sizeof(cbuf),
		.msg_flags = 0,
	};
	struct nlmsghdr *nl_msg;
	ssize_t msglen;

	struct rtattr *linkinfo[IFLA_INFO_MAX + 1];
	struct rtattr *can_attr[IFLA_CAN_MAX + 1];

	if (send_dump_request(fd, AF_PACKET, RTM_GETLINK) < 0) {
		perror("Cannot send dump request");
		return ret;
	}

	while (!done && (msglen = recvmsg(fd, &msg, 0)) > 0) {
		size_t u_msglen = (size_t) msglen;
		/* Check to see if the buffers in msg get truncated */
		if (msg.msg_namelen != sizeof(peer) ||
		    (msg.msg_flags & (MSG_TRUNC | MSG_CTRUNC))) {
			fprintf(stderr, "Uhoh... truncated message.\n");
			return -1;
		}

		for (nl_msg = (struct nlmsghdr *)nlbuf;
		     NLMSG_OK(nl_msg, u_msglen);
		     nl_msg = NLMSG_NEXT(nl_msg, u_msglen)) {
			int type = nl_msg->nlmsg_type;
			int len;

			if (type == NLMSG_DONE) {
				done++;
				continue;
			}
			if (type != RTM_NEWLINK)
				continue;

			struct ifinfomsg *ifi = NLMSG_DATA(nl_msg);
			struct rtattr *tb[IFLA_MAX + 1];

			len =
				nl_msg->nlmsg_len - NLMSG_LENGTH(sizeof(struct ifaddrmsg));
			parse_rtattr(tb, IFLA_MAX, IFLA_RTA(ifi), len);

			if (strcmp
			    ((char *)RTA_DATA(tb[IFLA_IFNAME]), name) != 0)
				continue;

			if (tb[IFLA_LINKINFO])
				parse_rtattr_nested(linkinfo,
						    IFLA_INFO_MAX, tb[IFLA_LINKINFO]);
			else
				continue;

			if (acquire == GET_XSTATS) {
				if (!linkinfo[IFLA_INFO_XSTATS])
					fprintf(stderr, "no can statistics found\n");
				else {
					memcpy(res, RTA_DATA(linkinfo[IFLA_INFO_XSTATS]),
					       sizeof(struct can_device_stats));
					ret = 0;
				}
				continue;
			}

			if (!linkinfo[IFLA_INFO_DATA]) {
				fprintf(stderr, "no link data found\n");
				return ret;
			}

			parse_rtattr_nested(can_attr, IFLA_CAN_MAX,
					    linkinfo[IFLA_INFO_DATA]);

			switch (acquire) {
			case GET_STATE:
				if (can_attr[IFLA_CAN_STATE]) {
					*((int *)res) = *((__u32 *)
							  RTA_DATA(can_attr
								   [IFLA_CAN_STATE]));
					ret = 0;
				} else {
					fprintf(stderr, "no state data found\n");
				}

				break;
			case GET_RESTART_MS:
				if (can_attr[IFLA_CAN_RESTART_MS]) {
					*((__u32 *) res) = *((__u32 *)
							     RTA_DATA(can_attr
								      [IFLA_CAN_RESTART_MS]));
					ret = 0;
				} else
					fprintf(stderr, "no restart_ms data found\n");

				break;
			case GET_BITTIMING:
				if (can_attr[IFLA_CAN_BITTIMING]) {
					memcpy(res,
					       RTA_DATA(can_attr[IFLA_CAN_BITTIMING]),
					       sizeof(struct can_bittiming));
					ret = 0;
				} else
					fprintf(stderr, "no bittiming data found\n");

				break;
			case GET_CTRLMODE:
				if (can_attr[IFLA_CAN_CTRLMODE]) {
					memcpy(res,
					       RTA_DATA(can_attr[IFLA_CAN_CTRLMODE]),
					       sizeof(struct can_ctrlmode));
					ret = 0;
				} else
					fprintf(stderr, "no ctrlmode data found\n");

				break;
			case GET_CLOCK:
				if (can_attr[IFLA_CAN_CLOCK]) {
					memcpy(res,
					       RTA_DATA(can_attr[IFLA_CAN_CLOCK]),
					       sizeof(struct can_clock));
					ret = 0;
				} else
					fprintf(stderr,
						"no clock parameter data found\n");

				break;
			case GET_BITTIMING_CONST:
				if (can_attr[IFLA_CAN_BITTIMING_CONST]) {
					memcpy(res,
					       RTA_DATA(can_attr[IFLA_CAN_BITTIMING_CONST]),
					       sizeof(struct can_bittiming_const));
					ret = 0;
				} else
					fprintf(stderr, "no bittiming_const data found\n");

				break;
			case GET_BERR_COUNTER:
				if (can_attr[IFLA_CAN_BERR_COUNTER]) {
					memcpy(res,
					       RTA_DATA(can_attr[IFLA_CAN_BERR_COUNTER]),
					       sizeof(struct can_berr_counter));
					ret = 0;
				} else
					fprintf(stderr, "no berr_counter data found\n");

				break;

			default:
				fprintf(stderr, "unknown acquire mode\n");
			}
		}
	}

	return ret;
}


static int open_nl_sock()
{
	int fd;
	int sndbuf = 32768;
	int rcvbuf = 32768;
	unsigned int addr_len;
	struct sockaddr_nl local;

	fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	if (fd < 0) {
		printf("Cannot open netlink socket");
		return -1;
	}

	setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (void *)&sndbuf, sizeof(sndbuf));

	setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (void *)&rcvbuf, sizeof(rcvbuf));

	memset(&local, 0, sizeof(local));
	local.nl_family = AF_NETLINK;
	local.nl_groups = 0;

	if (bind(fd, (struct sockaddr *)&local, sizeof(local)) < 0) {
		printf("Cannot bind netlink socket");
		return -1;
	}

	addr_len = sizeof(local);
	if (getsockname(fd, (struct sockaddr *)&local, &addr_len) < 0) {
		printf("Cannot getsockname");
		return -1;
	}
	if (addr_len != sizeof(local)) {
		printf("Wrong address length %u\n", addr_len);
		return -1;
	}
	if (local.nl_family != AF_NETLINK) {
		printf("Wrong address family %d\n", local.nl_family);
		return -1;
	}
	return fd;
}

static int get_link(const char *name, __u8 acquire, void *res)
{
	int err, fd;

	fd = open_nl_sock();
	if (fd < 0)
		return -1;

	err = do_get_nl_link(fd, acquire, name, res);
	close(fd);

	return err;

}

int HAL_can0_get_state(const char *name, int *state)
{
	return get_link(name, GET_STATE, state);
}
