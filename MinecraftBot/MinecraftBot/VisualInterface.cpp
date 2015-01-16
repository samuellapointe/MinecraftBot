#include "stdafx.h"
#include "VisualInterface.h"

using namespace MinecraftBot;

//##################################
//### User interaction functions ###
//##################################

//Validate the parameters to a server and connect, fired when someone presses on the "Connect" button
void VisualInterface::Connect()
{
	WriteToConsole("Hello World", true);
	WriteToChat("Hello World 2", true);
}

//######################################
//### Interface management functions ###
//######################################

//Write in the console box
void VisualInterface::WriteToConsole(string text)
{
	this->NetworkConsole->Text += ConvertString(text);
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
}

//Write in the chat box
void VisualInterface::WriteToChat(string text)
{
	this->ChatConsole->Text += ConvertString(text);
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