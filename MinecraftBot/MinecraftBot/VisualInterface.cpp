#include "stdafx.h"
#include "VisualInterface.h"

namespace MinecraftBot
{

	//##################################
	//### User interaction functions ###
	//##################################

	//Validate the parameters to a server and connect, fired when someone presses on the "Connect" button
	void VisualInterface::Connect()
	{
		bool validated = true;

		//Grab data from the text boxes
		string username = ConvertString(this->UsernameTextBox->Text);
		string password = ConvertString(this->PasswordTextBox->Text);
		string ip = ConvertString(this->ServerIPTextBox->Text);
		String^ portString = this->PortTextBox->Text; //I leave it with the System string for easier parsing to int
		int port;

		//Validate it
		if(username.length() == 0)
		{
			WriteToConsole("The username field is empty!", true);
			validated = false;
		}
		if(password.length() == 0)
		{
			WriteToConsole("The password field is empty!", true);
			validated = false;
		}
		if(ip.length() == 0)
		{
			WriteToConsole("The IP address field is empty!", true);
			validated = false;
		}
		if(portString->Length == 0)
		{
			WriteToConsole("The server port field is empty!", true);
			validated = false;
		}
		else
		{
			if(!Int32::TryParse(portString, port))
			{
				WriteToConsole("The port must be a number!");
				validated = false;
			}
		}

		if(validated)
		{
			Client client = Client(username, password, ip, port);
		}
	}

	//######################################
	//### Interface management functions ###
	//######################################

	//Write in the console box
	void VisualInterface::WriteToConsole(string text)
	{
		this->NetworkConsole->Text += ConvertString(text);

		//Scroll down
		this->NetworkConsole->SelectionStart = this->NetworkConsole->TextLength;
		this->NetworkConsole->ScrollToCaret();
	}
	//Overload to skip line
	void VisualInterface::WriteToConsole(string text, bool skipLine)
	{
		if(skipLine)
		{
			this->NetworkConsole->Text += ConvertString(text + "\n");
		}
		else
		{
			this->NetworkConsole->Text += ConvertString(text);
		}

		//Scroll down
		this->NetworkConsole->SelectionStart = this->NetworkConsole->TextLength;
		this->NetworkConsole->ScrollToCaret();
	}

	//Write in the chat box
	void VisualInterface::WriteToChat(string text)
	{
		this->ChatConsole->Text += ConvertString(text);

		//Scroll down
		this->ChatConsole->SelectionStart = this->ChatConsole->TextLength;
		this->ChatConsole->ScrollToCaret();
	}
	//Overload to skip line
	void VisualInterface::WriteToChat(string text, bool skipLine)
	{
		if(skipLine)
		{
			this->ChatConsole->Text += ConvertString(text + "\n");
		}
		else
		{
			this->ChatConsole->Text += ConvertString(text);
		}

		//Scroll down
		this->ChatConsole->SelectionStart = this->ChatConsole->TextLength;
		this->ChatConsole->ScrollToCaret();
	}

	//#######################
	//### Other functions ###
	//#######################

	//Function used to convert C++/CLI System strings to std strings
	string VisualInterface::ConvertString(System::String^ text)
	{
		msclr::interop::marshal_context context;
		return context.marshal_as<std::string>(text);
	}
	//Do the opposite
	System::String^ VisualInterface::ConvertString(string text)
	{
		return gcnew String(text.c_str());
	}
}