﻿// This code is part of Pcap_DNSProxy
// A local DNS server based on WinPcap and LibPcap
// Copyright (C) 2012-2016 Chengr28
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


#ifndef PCAP_DNSPROXY_PROCESS_H
#define PCAP_DNSPROXY_PROCESS_H

#include "Base.h"

//Global variables
extern CONFIGURATION_TABLE Parameter;
extern GLOBAL_STATUS GlobalRunningStatus;
extern BLOCKING_QUEUE<MONITOR_QUEUE_DATA> MonitorBlockingQueue;
#if defined(ENABLE_LIBSODIUM)
extern DNSCURVE_CONFIGURATION_TABLE DNSCurveParameter;
#endif
extern std::vector<DIFFERNET_FILE_SET_HOSTS> *HostsFileSetUsing, *HostsFileSetModificating;
extern std::deque<DNS_CACHE_DATA> DNSCacheList;
extern std::mutex LocalAddressLock[], HostsFileLock, DNSCacheListLock;

//Functions
bool LocalRequestProcess(
	const MONITOR_QUEUE_DATA &MonitorQueryData, 
	uint8_t * const OriginalRecv, 
	const size_t RecvSize);
bool SOCKS_RequestProcess(
	const MONITOR_QUEUE_DATA &MonitorQueryData);
bool HTTP_CONNECT_RequestProcess(
	const MONITOR_QUEUE_DATA &MonitorQueryData);
bool DirectRequestProcess(
	const MONITOR_QUEUE_DATA &MonitorQueryData, 
	uint8_t * const OriginalRecv, 
	const size_t RecvSize, 
	const bool IsDirectRequest);
#if defined(ENABLE_LIBSODIUM)
bool DNSCurveRequestProcess(
	const MONITOR_QUEUE_DATA &MonitorQueryData, 
	uint8_t * const OriginalRecv, 
	const size_t RecvSize);
#endif
bool TCP_RequestProcess(
	const MONITOR_QUEUE_DATA &MonitorQueryData, 
	uint8_t * const OriginalRecv, 
	const size_t RecvSize);
#if defined(ENABLE_PCAP)
void UDP_RequestProcess(
	const MONITOR_QUEUE_DATA &MonitorQueryData);
#endif
uint16_t SelectNetworkProtocol(
	void);
void AutoClear_DNS_Cache(
	void);
#endif
