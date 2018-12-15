#pragma once

#include <time.h>
#include <windows.h>			// Sleep

#include "CurrentSource.h"
#define RET ("\r")

namespace VorlageWindowsForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private: bool dataReceived;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  eingabe;
	private: System::Windows::Forms::TextBox^  ausgabe;
	private: System::IO::Ports::SerialPort^  serialPort1;


	
			 static int dataping;

	public:
		Form1(void)
		{
			dataReceived = false;
			dataping = 0;
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//

			_COM_Abfragen();
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	

	protected:


	private: System::Windows::Forms::Label^  label1;

	
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->eingabe = (gcnew System::Windows::Forms::TextBox());
			this->ausgabe = (gcnew System::Windows::Forms::TextBox());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(36, 80);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Senden";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// eingabe
			// 
			this->eingabe->Location = System::Drawing::Point(36, 43);
			this->eingabe->Name = L"eingabe";
			this->eingabe->Size = System::Drawing::Size(100, 20);
			this->eingabe->TabIndex = 1;
			this->eingabe->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::eingabe_KeyDown);
			// 
			// ausgabe
			// 
			this->ausgabe->Location = System::Drawing::Point(142, 43);
			this->ausgabe->Name = L"ausgabe";
			this->ausgabe->Size = System::Drawing::Size(100, 20);
			this->ausgabe->TabIndex = 2;
			// 
			// serialPort1
			// 
			this->serialPort1->BaudRate = 115200;
			// 
			// Form1
			// 
			this->ClientSize = System::Drawing::Size(546, 377);
			this->Controls->Add(this->ausgabe);
			this->Controls->Add(this->eingabe);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"f";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void eingabe_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}

private: System::Void serialPort1_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) {

	ausgabe->Text = serialPort1->ReadLine();
	
	dataReceived = true;	// Muss als erstes ausgeführt werden, wenn Daten Empfangen werden !!
	//dataping++;

	//serialPort1->Close();
}
private: System::Void serialPort1_ErrorReceived(System::Object^  sender, System::IO::Ports::SerialErrorReceivedEventArgs^  e) {

	int x = 1;
	_COM_Abfragen();
}


/// <summary> 
/// COM Ports abfragen und nach HF Gerät suchen </summary>
private: void _COM_Abfragen()
{
	array <System::String^>^ ports;
	array <System::String^>^ goodPorts = gcnew array <String^> (100);

	String^ goodPort;
	String^ _SN;
	String^ IDN = gcnew String("*idn?\r");
	/*if (!serialPort1->IsOpen)
	{
		serialPort1->Open();
	}*/

	//ports = serialPort1->GetPortNames();

	ports = System::IO::Ports::SerialPort::GetPortNames();

	/*System::IO::Ports::SerialPort:
		int x;
		x = ports->Count;*/
	
	
	try		// Klären, ob gehen tut!! (HERMANN)		.exe ohne VisualStudio, anderer PC
	{
		int j = 0;
		for (int i = 0 ; ports[i] != nullptr; i++)	/// ????
		{
			serialPort1->PortName = ports[i];
			if (!serialPort1->IsOpen)
			{
				serialPort1->Open();
			}
			
			serialPort1->Write("*idn?\r");


			///	Data.Receive vielleicht nicht unbedingt notwendig => Fehler mit Exeption abfangen??
			Sleep(100);
			//if (1)	// if (dataReceived)
			try
			{
				//serialPort1->ReadTo(" ");
				
				//_SN = serialPort1->ReadTo("\r");

				_SN = serialPort1->ReadExisting();

				CurrentSource^ cur1 = gcnew CurrentSource(_SN);

				if (serialPort1->ReadTo(" ") == "HighFinesse")	// Schneidet 'HighFinesse' aus !!
				//if (Convert::to(_SN[12]) == Convert::ToChar("HighFinesse"))	// Schneidet 'HighFinesse' aus !!

				{
					
					//ports[i]->CopyTo(i,goodPorts,0,4);
					goodPort = serialPort1->PortName;

					//goodPorts->Add();
					goodPorts[j] = goodPort;
					j++;

					_SN = serialPort1->ReadExisting();
					_SN = "HighFinesse " + _SN;
					
				}
				dataReceived = true;
			}

			catch(const System::IndexOutOfRangeException^fehler2) {}
			//dataReceived = false;
			//
			catch (...) {
				j++;
			};
			

			serialPort1->Close();

			///} while (dataReceived == false);
		}
	}

	catch( const System::IndexOutOfRangeException^fehler1)
	{
		// Array Ende erreicht 
	}

	serialPort1->PortName = goodPort;	/// EXEPETION ==> System.ArgumentNullException: "Der Wert darf nicht NULL sein. Parametername: PortName"
										// wenn keine Ports gefunden => FEHLER!! => muss abgefangen werden!


	//serialPort1->po
	ausgabe->Text = serialPort1->PortName;

	//serialPort1->Close();
}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

	//String^ _return = gcnew String("\r");

	String^ txt;// = gcnew String("");
	char sendtxt;
	if (!serialPort1->IsOpen)
	{
		serialPort1->Open();
	}

	//_COM_Abfragen();

	txt = eingabe->Text;
	txt += RET;
	//sendtxt = Convert::ToChar(txt);
	//eingabe->Text = text;
	//serialPort1->WriteLine(txt);	// sendet 0x0A (LF) mit

	serialPort1->Write(txt);		// nur 'RET' (CR) '\r'
	//serialPort1->Close();
	
}
private: System::Void eingabe_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Return)
		button1_Click(0, e);
}
};
}

