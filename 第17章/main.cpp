// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "CSmtp.h"
#include <conio.h>

int main(int argc, char* argv[])
{
	CSmtp mail;

	if (mail.GetLastError() != CSMTP_NO_ERROR)
	{
		printf("Unable to initialise winsock2.\n");
		return -1;
	}

	mail.SetSMTPServer("smtp.qq.com", 25);
	mail.SetLogin("account");
	mail.SetPassword("password");
	mail.SetSenderName("SenderName");
	mail.SetSenderMail("SenderEmail");
	mail.SetReplyTo("");
	mail.SetSubject("Subject");
	mail.AddRecipient("ReceiverEmail");
	mail.SetXPriority(XPRIORITY_NORMAL);
	mail.SetXMailer("The Bat! (v3.02) Professional");
	mail.SetMessageBody("EmailBody");
	mail.AddAttachment(argv[1]);

	printf("%s,%s\n", argv[0], argv[1]);

	if (mail.Send())
		printf("The mail was send successfully.\n");
	else
	{
		printf("%s\n", GetErrorText(mail.GetLastError()));
		printf("Unable to send the mail.\n");
	}

	return 0;
}
