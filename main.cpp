#pragma once

#include <Windows.h>
#include <iostream>
#include <thread>
#include <fstream>
#include "auth.hpp"
#include "skCrypt.h"

#define PRODUCT_UUID "PUT_YOUR_APP_UUID_HERE" //your UUID

void killThem() { //optional
	system(skCrypt("taskkill /f /im x64dbg"));
	system(skCrypt("taskkill /f /im HTTPDebuggerSvc.exe"));
	//add any other by your self
}

std::uint8_t main()
{
	SetConsoleTitleA(skCrypt("xen0n auth example"));
	std::thread protection(killThem);
	/*
	Initialize an connection with xen0n.app's API.
	*/
	xen0n::auth auth(PRODUCT_UUID);

	/*
	Lambda function for fetching the license.
	*/
	auto get_license = ([]() {
		std::string license;
		printf(skCrypt("Enter license: "));
		std::getline(std::cin, license);
		return license;
		});

	/*
	Authenticate with xen0n.app's API and returns an response object.
	*/
	xen0n::response* response = auth.authenticate(get_license(), 2);

	/*
	Check if the response was successful.
	*/
	if (response->succeeded())
	{
		printf(skCrypt("xen0n.app -> succesfully authenticated!\n"));
		
		/*
		Initialize stream and fetch the array of bytes.
		*/
		std::vector<std::uint8_t> stream = response->stream();

		/*
		Write to bytes to file. Keep in mind writing your secret or special files to disk is a vector and can result in cracking.
		If you're streaming an executable file (.exe) use portable executable and if it's a dll embed the injector into the project
		And if it's a driver embed your mapper preferably kdmapper into the actual project as well.
		And we say this with the most severity! Security is a must for any paid application.
		*/
		std::ofstream write_file;
		write_file.open(skCrypt("disk.png"), std::ios::out | std::ios::binary);
		write_file.write((char*)stream.data(), stream.size());
	}
	else
	{ 
		/*
		Authentication fails and print the error message returned by server.
		*/
		printf(skCrypt("xen0n.app> %s\n"), response->message().c_str());
	}
}
