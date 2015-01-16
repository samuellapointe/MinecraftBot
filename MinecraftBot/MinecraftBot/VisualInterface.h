#pragma once
#include "stdafx.h"

namespace MinecraftBot 
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Summary for VisualInterface
	/// </summary>
	public ref class VisualInterface : public System::Windows::Forms::Form
	{
	public:
		VisualInterface(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		//My functions
		void WriteToConsole(string text); //Write in the console
		void WriteToConsole(string text, bool skipLine); //Overload with option to skip line

		void WriteToChat(string text); //Write in the console
		void WriteToChat(string text, bool skipLine); //Overload with option to skip line

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~VisualInterface()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^  NetworkConsole;

	private: System::Windows::Forms::RichTextBox^  ChatConsole;
	private: System::Windows::Forms::Label^  NetworkConsoleLabel;
	private: System::Windows::Forms::Label^  PacketListLabel;
	private: System::Windows::Forms::Label^  ChatConsoleLabel;
	private: System::Windows::Forms::TextBox^  ChatTextBox;
	private: System::Windows::Forms::Button^  ChatSendButton;
	private: System::Windows::Forms::ListBox^  PacketList;
	private: System::Windows::Forms::TextBox^  UsernameTextBox;

	private: System::Windows::Forms::Label^  UsernameLabel;
	private: System::Windows::Forms::Label^  PasswordLabel;
	private: System::Windows::Forms::TextBox^  PasswordTextBox;
	private: System::Windows::Forms::TextBox^  PortTextBox;

	private: System::Windows::Forms::Label^  PortLabel;

	private: System::Windows::Forms::Label^  ServerIPLabel;
	private: System::Windows::Forms::TextBox^  ServerIPTextBox;
	private: System::Windows::Forms::CheckBox^  EnableAuthentificationCheckbox;
	private: System::Windows::Forms::Button^  ConnectButton;

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		//My functions
		void Connect();
		string ConvertString(System::String^ text);
		System::String^ ConvertString(string text);

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->NetworkConsole = (gcnew System::Windows::Forms::RichTextBox());
			this->ChatConsole = (gcnew System::Windows::Forms::RichTextBox());
			this->NetworkConsoleLabel = (gcnew System::Windows::Forms::Label());
			this->PacketListLabel = (gcnew System::Windows::Forms::Label());
			this->ChatConsoleLabel = (gcnew System::Windows::Forms::Label());
			this->ChatTextBox = (gcnew System::Windows::Forms::TextBox());
			this->ChatSendButton = (gcnew System::Windows::Forms::Button());
			this->PacketList = (gcnew System::Windows::Forms::ListBox());
			this->UsernameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->UsernameLabel = (gcnew System::Windows::Forms::Label());
			this->PasswordLabel = (gcnew System::Windows::Forms::Label());
			this->PasswordTextBox = (gcnew System::Windows::Forms::TextBox());
			this->PortTextBox = (gcnew System::Windows::Forms::TextBox());
			this->PortLabel = (gcnew System::Windows::Forms::Label());
			this->ServerIPLabel = (gcnew System::Windows::Forms::Label());
			this->ServerIPTextBox = (gcnew System::Windows::Forms::TextBox());
			this->EnableAuthentificationCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->ConnectButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// NetworkConsole
			// 
			this->NetworkConsole->BackColor = System::Drawing::SystemColors::WindowText;
			this->NetworkConsole->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->NetworkConsole->ForeColor = System::Drawing::SystemColors::Info;
			this->NetworkConsole->Location = System::Drawing::Point(14, 28);
			this->NetworkConsole->Name = L"NetworkConsole";
			this->NetworkConsole->ReadOnly = true;
			this->NetworkConsole->Size = System::Drawing::Size(298, 300);
			this->NetworkConsole->TabIndex = 0;
			this->NetworkConsole->TabStop = false;
			this->NetworkConsole->Text = L"";
			// 
			// ChatConsole
			// 
			this->ChatConsole->BackColor = System::Drawing::SystemColors::Window;
			this->ChatConsole->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ChatConsole->ForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->ChatConsole->Location = System::Drawing::Point(567, 28);
			this->ChatConsole->Name = L"ChatConsole";
			this->ChatConsole->ReadOnly = true;
			this->ChatConsole->Size = System::Drawing::Size(298, 276);
			this->ChatConsole->TabIndex = 2;
			this->ChatConsole->TabStop = false;
			this->ChatConsole->Text = L"";
			// 
			// NetworkConsoleLabel
			// 
			this->NetworkConsoleLabel->AutoSize = true;
			this->NetworkConsoleLabel->Font = (gcnew System::Drawing::Font(L"Lucida Console", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->NetworkConsoleLabel->Location = System::Drawing::Point(12, 9);
			this->NetworkConsoleLabel->Name = L"NetworkConsoleLabel";
			this->NetworkConsoleLabel->Size = System::Drawing::Size(158, 16);
			this->NetworkConsoleLabel->TabIndex = 3;
			this->NetworkConsoleLabel->Text = L"Network Console";
			// 
			// PacketListLabel
			// 
			this->PacketListLabel->AutoSize = true;
			this->PacketListLabel->Font = (gcnew System::Drawing::Font(L"Lucida Console", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->PacketListLabel->Location = System::Drawing::Point(315, 9);
			this->PacketListLabel->Name = L"PacketListLabel";
			this->PacketListLabel->Size = System::Drawing::Size(118, 16);
			this->PacketListLabel->TabIndex = 4;
			this->PacketListLabel->Text = L"Packet List";
			// 
			// ChatConsoleLabel
			// 
			this->ChatConsoleLabel->AutoSize = true;
			this->ChatConsoleLabel->Font = (gcnew System::Drawing::Font(L"Lucida Console", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ChatConsoleLabel->Location = System::Drawing::Point(564, 9);
			this->ChatConsoleLabel->Name = L"ChatConsoleLabel";
			this->ChatConsoleLabel->Size = System::Drawing::Size(128, 16);
			this->ChatConsoleLabel->TabIndex = 5;
			this->ChatConsoleLabel->Text = L"Chat Console";
			// 
			// ChatTextBox
			// 
			this->ChatTextBox->Location = System::Drawing::Point(567, 310);
			this->ChatTextBox->Name = L"ChatTextBox";
			this->ChatTextBox->Size = System::Drawing::Size(224, 18);
			this->ChatTextBox->TabIndex = 7;
			// 
			// ChatSendButton
			// 
			this->ChatSendButton->Location = System::Drawing::Point(797, 309);
			this->ChatSendButton->Name = L"ChatSendButton";
			this->ChatSendButton->Size = System::Drawing::Size(67, 19);
			this->ChatSendButton->TabIndex = 8;
			this->ChatSendButton->Text = L"Send";
			this->ChatSendButton->UseVisualStyleBackColor = true;
			this->ChatSendButton->Click += gcnew System::EventHandler(this, &VisualInterface::ChatSendButton_Click);
			// 
			// PacketList
			// 
			this->PacketList->BackColor = System::Drawing::SystemColors::Window;
			this->PacketList->FormattingEnabled = true;
			this->PacketList->ItemHeight = 11;
			this->PacketList->Location = System::Drawing::Point(318, 28);
			this->PacketList->Name = L"PacketList";
			this->PacketList->Size = System::Drawing::Size(243, 301);
			this->PacketList->TabIndex = 8;
			this->PacketList->TabStop = false;
			// 
			// UsernameTextBox
			// 
			this->UsernameTextBox->Location = System::Drawing::Point(89, 338);
			this->UsernameTextBox->Name = L"UsernameTextBox";
			this->UsernameTextBox->Size = System::Drawing::Size(158, 18);
			this->UsernameTextBox->TabIndex = 1;
			// 
			// UsernameLabel
			// 
			this->UsernameLabel->AutoSize = true;
			this->UsernameLabel->Location = System::Drawing::Point(15, 341);
			this->UsernameLabel->Name = L"UsernameLabel";
			this->UsernameLabel->Size = System::Drawing::Size(68, 11);
			this->UsernameLabel->TabIndex = 10;
			this->UsernameLabel->Text = L"Username:";
			// 
			// PasswordLabel
			// 
			this->PasswordLabel->AutoSize = true;
			this->PasswordLabel->Location = System::Drawing::Point(15, 364);
			this->PasswordLabel->Name = L"PasswordLabel";
			this->PasswordLabel->Size = System::Drawing::Size(68, 11);
			this->PasswordLabel->TabIndex = 11;
			this->PasswordLabel->Text = L"Password:";
			// 
			// PasswordTextBox
			// 
			this->PasswordTextBox->Location = System::Drawing::Point(89, 361);
			this->PasswordTextBox->Name = L"PasswordTextBox";
			this->PasswordTextBox->Size = System::Drawing::Size(158, 18);
			this->PasswordTextBox->TabIndex = 2;
			this->PasswordTextBox->UseSystemPasswordChar = true;
			// 
			// PortTextBox
			// 
			this->PortTextBox->Location = System::Drawing::Point(357, 361);
			this->PortTextBox->Name = L"PortTextBox";
			this->PortTextBox->Size = System::Drawing::Size(158, 18);
			this->PortTextBox->TabIndex = 4;
			// 
			// PortLabel
			// 
			this->PortLabel->AutoSize = true;
			this->PortLabel->Location = System::Drawing::Point(311, 364);
			this->PortLabel->Name = L"PortLabel";
			this->PortLabel->Size = System::Drawing::Size(40, 11);
			this->PortLabel->TabIndex = 15;
			this->PortLabel->Text = L"Port:";
			// 
			// ServerIPLabel
			// 
			this->ServerIPLabel->AutoSize = true;
			this->ServerIPLabel->Location = System::Drawing::Point(276, 341);
			this->ServerIPLabel->Name = L"ServerIPLabel";
			this->ServerIPLabel->Size = System::Drawing::Size(75, 11);
			this->ServerIPLabel->TabIndex = 14;
			this->ServerIPLabel->Text = L"Server IP:";
			// 
			// ServerIPTextBox
			// 
			this->ServerIPTextBox->Location = System::Drawing::Point(357, 338);
			this->ServerIPTextBox->Name = L"ServerIPTextBox";
			this->ServerIPTextBox->Size = System::Drawing::Size(158, 18);
			this->ServerIPTextBox->TabIndex = 3;
			// 
			// EnableAuthentificationCheckbox
			// 
			this->EnableAuthentificationCheckbox->AutoSize = true;
			this->EnableAuthentificationCheckbox->Checked = true;
			this->EnableAuthentificationCheckbox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->EnableAuthentificationCheckbox->Location = System::Drawing::Point(549, 340);
			this->EnableAuthentificationCheckbox->Name = L"EnableAuthentificationCheckbox";
			this->EnableAuthentificationCheckbox->Size = System::Drawing::Size(185, 15);
			this->EnableAuthentificationCheckbox->TabIndex = 5;
			this->EnableAuthentificationCheckbox->Text = L"Enable authentification";
			this->EnableAuthentificationCheckbox->UseVisualStyleBackColor = true;
			// 
			// ConnectButton
			// 
			this->ConnectButton->Location = System::Drawing::Point(549, 361);
			this->ConnectButton->Name = L"ConnectButton";
			this->ConnectButton->Size = System::Drawing::Size(94, 18);
			this->ConnectButton->TabIndex = 6;
			this->ConnectButton->Text = L"Connect";
			this->ConnectButton->UseVisualStyleBackColor = true;
			this->ConnectButton->Click += gcnew System::EventHandler(this, &VisualInterface::ConnectButton_Click);
			// 
			// VisualInterface
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 11);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(877, 388);
			this->Controls->Add(this->ConnectButton);
			this->Controls->Add(this->EnableAuthentificationCheckbox);
			this->Controls->Add(this->PortTextBox);
			this->Controls->Add(this->PortLabel);
			this->Controls->Add(this->ServerIPLabel);
			this->Controls->Add(this->ServerIPTextBox);
			this->Controls->Add(this->PasswordTextBox);
			this->Controls->Add(this->PasswordLabel);
			this->Controls->Add(this->UsernameLabel);
			this->Controls->Add(this->UsernameTextBox);
			this->Controls->Add(this->PacketList);
			this->Controls->Add(this->ChatSendButton);
			this->Controls->Add(this->ChatTextBox);
			this->Controls->Add(this->ChatConsoleLabel);
			this->Controls->Add(this->PacketListLabel);
			this->Controls->Add(this->NetworkConsoleLabel);
			this->Controls->Add(this->ChatConsole);
			this->Controls->Add(this->NetworkConsole);
			this->Font = (gcnew System::Drawing::Font(L"Lucida Console", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"VisualInterface";
			this->Text = L"Minecraft Bot";
			this->Load += gcnew System::EventHandler(this, &VisualInterface::VisualInterface_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: 
	System::Void VisualInterface_Load(System::Object^  sender, System::EventArgs^  e) 
	{
		 
	}
	System::Void ChatSendButton_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		
	}
private: System::Void ConnectButton_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Connect();
	}
};
}

