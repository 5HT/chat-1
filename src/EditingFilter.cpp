//////////////////////////////////////////////////
// Blabber [EditingFilter.cpp]
//////////////////////////////////////////////////

#include <interface/InterfaceDefs.h>
#include <app/Message.h>
#include "EditingFilter.h"
#include "Messages.h"
#include "ChatWindow.h"

EditingFilter::EditingFilter(BTextView *v, ChatWindow *w)
	:
	BMessageFilter(B_ANY_DELIVERY, B_ANY_SOURCE, B_KEY_DOWN, NULL)
{
	view   = v;
	window = w;
}

filter_result
EditingFilter::Filter(BMessage *message, BHandler **target)
{
	int32 modifiers;
	
	bool sendWithEnter = false;
	
	int8 byte;
	message->FindInt8("byte", &byte);

	if (message->FindInt32("modifiers", &modifiers))
	{
		return B_DISPATCH_MESSAGE;
	}

	if ((modifiers & B_COMMAND_KEY) != 0 && byte == B_UP_ARROW)
	{
		//window->RevealPreviousHistory();
	}
	else if ((modifiers & B_COMMAND_KEY) != 0 && byte == B_DOWN_ARROW)
	{
		//window->RevealNextHistory();
	}
	else if (byte == B_ENTER)
	{
		if (((modifiers & B_COMMAND_KEY) == 0) ^ (int)sendWithEnter)
		{
			view->Insert("\n");
			return B_SKIP_MESSAGE;
		}
		else 
		{
			window->PostMessage(JAB_CHAT_SENT);
			return B_SKIP_MESSAGE;
		}
	}
	else if (byte == B_ESCAPE)
	{
		window->Minimize(true);
	}
	
	return B_DISPATCH_MESSAGE;
}

