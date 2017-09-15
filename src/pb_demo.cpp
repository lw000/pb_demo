//============================================================================
// Name        : pb_demo.cpp
// Author      : lw
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "platform.pb.h"

using namespace platform;

#include <log4z/log4z.h>
using namespace zsummer::log4z;

int main(int argc, char** argv) {

	ILog4zManager::getInstance()->start();

	clock_t t = clock();

	{
		for (int i = 0; i < 10000; i++) {
			platform::msg_login_request login;
			login.set_device(1);
			login.set_username("liwei");
			login.set_userpsd("1234567890");

			unsigned char buff[512];
			bool r = login.SerializeToArray(buff, sizeof(buff));
			int len = login.ByteSize();
			if (r) {
				platform::msg_login_request login1;
				bool r1 = login1.ParseFromArray(buff, len);
				if (r1) {
					std::cout << "[" << login.device() << ","
							<< login.username() << "," << login.userpsd() << "]"
							<< std::endl;
				}
			}
		}

	}

	clock_t t1 = clock();
	LOGFMTA("exec times: %f", ((double) t1 - t) / CLOCKS_PER_SEC);
	return 0;
}
