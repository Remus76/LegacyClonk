/*
 * LegacyClonk
 *
 * Copyright (c) RedWolf Design
 * Copyright (c) 2007, Sven2
 * Copyright (c) 2017-2019, The LegacyClonk Team and contributors
 *
 * Distributed under the terms of the ISC license; see accompanying file
 * "COPYING" for details.
 *
 * "Clonk" is a registered trademark of Matthes Bender, used with permission.
 * See accompanying file "TRADEMARK" for details.
 *
 * To redistribute this file separately, substitute the full license texts
 * for the above references.
 */

// HTTP download dialog; downloads a file
// (like, e.g., a .c4u update group)

#ifndef INC_C4DownloadDlg
#define INC_C4DownloadDlg

#include "C4Gui.h"
#include "C4Network2Reference.h" // includes HTTP client

// dialog to download a file
class C4DownloadDlg : public C4GUI::Dialog
  {
	private:
#ifdef NETWORK
		C4Network2HTTPClient HTTPClient;
#endif

		C4GUI::Icon *pIcon;
		C4GUI::Label *pStatusLabel;
		C4GUI::ProgressBar *pProgressBar;
		C4GUI::CancelButton *pCancelBtn;
		const char *szError;
#ifdef HAVE_WINSOCK
		bool fWinSock;
#endif

	protected:
		C4DownloadDlg(const char *szDLType);
		virtual ~C4DownloadDlg();

	private:
		// updates the displayed status text and progress bar - repositions elements if necessary
		void SetStatus(const char *szNewText, int32_t iProgressPercent);

	protected:
		// idle proc: Continue download; close when finished
		virtual void OnIdle();

		// user presses cancel button: Abort download
		virtual void UserClose(bool fOK);

		// downloads the specified file to the specified location. Returns whether successful
		bool ShowModal(C4GUI::Screen *pScreen, const char *szURL, const char *szSaveAsFilename);

		const char *GetError();

	public:
		// download file showing download dialog; display error if download failed
		static bool DownloadFile(const char *szDLType, C4GUI::Screen *pScreen, const char *szURL, const char *szSaveAsFilename, const char *szNotFoundMessage = NULL);
	};


#endif // INC_C4DownloadDlg