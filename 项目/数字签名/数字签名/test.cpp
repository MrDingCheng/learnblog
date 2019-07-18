#pragma once
#include<iostream>
#include"MD5.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << argv[0] << "\tfilename" << std::endl;
		return 0;
	}
	MD5 md5;
	switch ((int)(*argv[1]-'0'))
	{
	case 0:
		std::cout << md5.getStringMd5(argv[2]) << std::endl;
		break;
	case 1:
		std::cout << md5.getFileMd5(argv[2]) << std::endl;
		break;
	default:
		break;
	}
	return 0;
}