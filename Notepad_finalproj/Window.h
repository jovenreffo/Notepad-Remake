#ifndef WINDOW_H
#define WINDOW_H

#include <wx/wx.h>

#define WINDOW_SIZE (wxSize(640, 480))

class App : public wxApp
{
public:
	virtual bool OnInit();
};

enum
{
	ID_FULLSCREEN = wxID_HIGHEST + 1,
	ID_NEW_NOTE,
	ID_IMPORT
};

class Frame : public wxFrame
{
private:

	wxTextCtrl* m_pTextCtrl;
	wxToolBar* m_pToolBar;

	// Buttons
	wxBitmap m_undo;
	wxBitmap m_redo;
	wxBitmap m_cut;
	wxBitmap m_copy;
	wxBitmap m_paste;
	wxBitmap m_save;
	wxBitmap m_import;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;

public:
	Frame();
	~Frame();

	// Window setup
	void SetupFrame();
	void SetupTextBox();
	void SetupTools();
	void SetupSizer();

	// Events
	void OnCut(wxCommandEvent& event);
	void OnCopy(wxCommandEvent& event);
	void OnPaste(wxCommandEvent& event);
	void OnUndo(wxCommandEvent& event);
	void OnRedo(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnImport(wxCommandEvent& event);

};


#endif