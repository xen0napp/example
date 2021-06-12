#pragma once

#include <Windows.h>
#include <iostream>
#include <thread>
#include <fstream>

#include <auth.hpp>
#include <sk_crypter.hpp>

/*
Your application's UUID found under Manage -> Applications
*/
#define PRODUCT_UUID "PUT_YOUR_APP_UUID_HERE"

std::uint8_t main()
{
	/*
	Initialize an connection with xen0n.app's API.
	*/
	xen0n::auth auth
		= xen0n::auth(PRODUCT_UUID)
		  .with_endpoint("https://xen0n.app/api/");

	/*
	Lambda function for fetching the license.
	*/
	auto get_license = ([]() {
		std::string license;
		printf(skCrypt("Enter license > "));
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
		printf(skCrypt("xen0n.app -> %s\n"), response->message().c_str());
		
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
		write_file.open(skCrypt("yourfile.bin"), std::ios::out | std::ios::binary);
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
