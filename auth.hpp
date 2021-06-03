/*
*
Copyright (c) 2021-2022 [xen0n.app]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

*/

#pragma once

#include <Windows.h>

#include <string>
#include <vector>


namespace xen0n
{
	typedef int package;

	class response
	{
	private:
		std::string message_str;
		bool status;
		std::string session;
		std::string uuid;
	public:
		/**
		* Initialize a response instance.
		* @param message The message returned by server
		* @param status The status provided by server (boolean)
		* @param session Encrypted session token provided by server.
		* @param uuid Application UUID provided by the authenticate function.
		*/
		response(std::string message, bool status, std::string session, std::string uuid);
	public:
		std::string expiry;
		std::string app;
		xen0n::package package;

		/**
		* Returns the message provided by server.
		* @return A string containing server-response.
		*/
		std::string message();

		/**
		* Check if the authentication suceeded.
		* @return A boolean containing status of request.
		*/
		bool succeeded();

		/**
		* Stream data from the server.
		* @return Container who contains bytes of streamed data.
		*/
		std::vector<std::uint8_t> stream();
	};

	class auth
	{
	private:
		std::string uuid;

		/**
		* Get's hardware identifier in xen0n.app's format.
		* @return Returns a base64 encoded string containing serials and other unique identifiers.
		*/
		std::string get_hardware();
	public:
		/**
		* Initialize an authentication instance.
		* @param uuid Universal identifier for the application you want to auth for.
		*/
		auth(std::string uuid);
	public:

		/**
		* Authenticate license key with xen0n.app.
		*
		* @param license License key provided by the user.
		* @param attempts Attempts if the authentication fails on server or client.
		* @return Returns an instance of xen0n::response* provided by the server.
		*/
		xen0n::response* authenticate(std::string license, int attempts = 1);
	};
}