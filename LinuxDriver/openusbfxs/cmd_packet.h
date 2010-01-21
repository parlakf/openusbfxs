#ifndef CMD_PACKET_H
#define CMD_PACKET_H
#ifndef __KERNEL__
typedef unsigned char __u8;
#endif

/* commands that the OpenUSBFXS board understands */
enum enum_openusbfxs_cmd {
    READ_VERSION	= 0x00,

    PROSLIC_SCURRENT	= 0x80,
    PROSLIC_RCURRENT	= 0x81,
    PROSLIC_RDIRECT	= 0x82,
    PROSLIC_WDIRECT	= 0x83,
    PROSLIC_RDINDIR	= 0x84,
    PROSLIC_WRINDIR	= 0x85,

    START_STOP_IO	= 0x7E,

    RESET		= 0xFF
};

union openusbfxs_packet {
#if 0
    struct {
    	__u8	cmd;
	__u8	len;
    }		rdvrsn_req;
#endif
    struct {
        __u8	cmd;
	__u8	len;
	__u8	mjr;
	__u8	mnr;
    }		rdvrsn_rep;
    struct {
	__u8	cmd;
	__u8	reg;
    }		rdirect_req, rdindir_req;
    struct {
	__u8	cmd;
	__u8	reg;
	__u8	val;
    }		rdirect_rpl, wdirect_req, wdirect_rpl;
    struct {
        __u8	cmd;
	__u8	reg;
	__u16	val;
    }		rdindir_rpl, wrindir_req, wrindir_rpl;
    struct {
        __u8	cmd;
	__u8	val;
    }		strtstp_req;
};

#define	PROSLIC_RDIRECT_REQ(r)		\
		{.rdirect_req={.cmd=PROSLIC_RDIRECT,.reg=(r)}}
#define PROSLIC_WDIRECT_REQ(r,v)	\
		{.wdirect_req={.cmd=PROSLIC_WDIRECT,.reg=(r),.val=(v)}}
#define PROSLIC_RDINDIR_REQ(r)		\
		{.rdindir_req={.cmd=PROSLIC_RDINDIR,.reg=(r)}}
#define	PROSLIC_WRINDIR_REQ(r,v)	\
	  {.wrindir_req={.cmd=PROSLIC_WRINDIR,.reg=(r),.val=cpu_to_le16(v)}}
#define START_STOP_IO_REQ(v)		\
		{.strtstp_req={.cmd=START_STOP_IO,.val=(v)}}


#define PROSLIC_RDIRECT_RPV(p)	p.rdirect_rpl.val
#define PROSLIC_WDIRECT_RPV(p)	p.wdirect_rpl.val
#define PROSLIC_RDINDIR_RPV(p)	le16_to_cpu(p.rdindir_rpl.val)
#define PROSLIC_WRINDIR_RPV(p)	le16_to_cpu(p.wrindir_rpl.val)


#define OPENUSBFXS_DTHDR_SIZE	8
union openusbfxs_data {
    struct {
	__u8	header[OPENUSBFXS_DTHDR_SIZE];
	__u8	sample[OPENUSBFXS_CHUNK_SIZE];
    }		oblique;
    struct {
	__u8	unusd1[3];
	__u8	serial;
	__u8	unusd2[4];
        __u8	sample[OPENUSBFXS_CHUNK_SIZE];
    }		outpack;
    struct {
	__u8	magic1;
	__u8	oddevn;		/* 0xdd for odd, 0xee for even packets */
	__u8	rsrved[6];
        __u8	sample[OPENUSBFXS_CHUNK_SIZE];
    }		in_pack;	/* yet unidentified in-packet */
    struct {
        __u8	magic1;
	__u8	magic2;		/* 0xdd for odd packets */
	__u8	hkdtmf;
	__u8	moutsm;
	__u16	tmr3lv;
	__u8	losses;
	__u8	serial;
        __u8	sample[OPENUSBFXS_CHUNK_SIZE];
    }		inopack;	/* odd in-packet */
    struct {
    	__u8	magic1;
	__u8	magic2;		/* 0xee for even packets */
	__u8	unusd1;
	__u8	moutsm;
	__u8	unusd3[3];
	__u8	serial;
        __u8	sample[OPENUSBFXS_CHUNK_SIZE];
    }		inepack;	/* even in-packet */
};
#define OPENUSBFXS_DPACK_SIZE	sizeof(union openusbfxs_data)


#if 0
#define	REQ_RESET()			\
    {.cmd=RESET,.len=2}
#endif /* 0 */

#endif /* CMD_PACKET_H */
