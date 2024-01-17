#include "Window.h"
#include "StandardPath.h"

Frame::Frame()
	: wxFrame(nullptr, wxID_ANY, _T("Notepad"), wxDefaultPosition, wxSize(640, 480))
{
	// Call the primary function that will set up other frame components.
	this->SetupFrame();

	// Set the minimum size of the window.
	this->SetMinSize(wxSize(640, 480));

	// Add event listeners to the text control
	// The Bind() function takes an event type which is a tool event in this case,
	// the function to bind to which is contained within the Frame class, a parent window,
	// and an ID
	m_pToolBar->Bind(wxEVT_TOOL, &Frame::OnCut, this, wxID_CUT);
	m_pToolBar->Bind(wxEVT_TOOL, &Frame::OnCopy, this, wxID_COPY);
	m_pToolBar->Bind(wxEVT_TOOL, &Frame::OnPaste, this, wxID_PASTE);
	m_pToolBar->Bind(wxEVT_TOOL, &Frame::OnUndo, this, wxID_UNDO);
	m_pToolBar->Bind(wxEVT_TOOL, &Frame::OnRedo, this, wxID_REDO);
	m_pToolBar->Bind(wxEVT_TOOL, &Frame::OnSave, this, wxID_SAVE);
	m_pToolBar->Bind(wxEVT_TOOL, &Frame::OnImport, this, ID_IMPORT);
}

Frame::~Frame()
{
	// Unbind the events to preserve resources
	m_pToolBar->Unbind(wxEVT_TOOL, &Frame::OnCut, this, wxID_CUT);
	m_pToolBar->Unbind(wxEVT_TOOL, &Frame::OnCopy, this, wxID_COPY);
	m_pToolBar->Unbind(wxEVT_TOOL, &Frame::OnPaste, this, wxID_PASTE);
	m_pToolBar->Unbind(wxEVT_TOOL, &Frame::OnUndo, this, wxID_UNDO);
	m_pToolBar->Unbind(wxEVT_TOOL, &Frame::OnRedo, this, wxID_REDO);
	m_pToolBar->Unbind(wxEVT_TOOL, &Frame::OnSave, this, wxID_SAVE);
	m_pToolBar->Unbind(wxEVT_TOOL, &Frame::OnImport, this, ID_IMPORT);
}

void Frame::SetupFrame()
{
	this->SetupTextBox();
	this->SetupTools();
	this->SetupSizer();
}

void Frame::SetupTextBox()
{
	// Initialize the text box that will act as the main control for the user
	m_pTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
}

void Frame::SetupTools()
{
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
#ifdef __WXMSW__ // Only add the wxTB_FLAT style if the user has windows
	m_pToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TEXT | wxTB_FLAT);
#else
	m_pToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TEXT);
#endif
	
	// Initialize bitmaps by navigating to the program path, and specifying it as a PNG, otherwise an error is thrown
	m_copy = wxBitmap(path_data::dataDir + "\\copy_small.png", wxBITMAP_TYPE_PNG);
	m_cut = wxBitmap(path_data::dataDir + "\\cut_small.png", wxBITMAP_TYPE_PNG);
	m_paste = wxBitmap(path_data::dataDir + "\\paste_small.png", wxBITMAP_TYPE_PNG);
	m_undo = wxBitmap(path_data::dataDir + "\\undo_small.png", wxBITMAP_TYPE_PNG);
	m_redo = wxBitmap(path_data::dataDir + "\\redo_small.png", wxBITMAP_TYPE_PNG);
	m_save = wxBitmap(path_data::dataDir + "\\save.png", wxBITMAP_TYPE_PNG);
	m_import = wxBitmap(path_data::dataDir + "\\import.png", wxBITMAP_TYPE_PNG);

	// Add items to the tool bar.
	// The function takes an ID to identify the action, the bitmap, and a tooltip that displays when the 
	// action is hovered over.
	m_pToolBar->AddTool(wxID_CUT, _T("Cut"), m_cut, _T("Cut selected text."));
	m_pToolBar->AddTool(wxID_COPY, _T("Copy"), m_copy, _T("Copy selected text."));
	m_pToolBar->AddTool(wxID_PASTE, _T("Paste"), m_paste, _T("Paste selected text."));
	m_pToolBar->AddSeparator();
	m_pToolBar->AddTool(wxID_UNDO, _T("Undo"), m_undo, _T("Undo last action."));
	m_pToolBar->AddTool(wxID_REDO, _T("Redo"), m_redo, _T("Redo last action."));
	m_pToolBar->AddSeparator();
	m_pToolBar->AddTool(wxID_SAVE, _T("Save"), m_save, _T("Save file."));
	m_pToolBar->AddTool(ID_IMPORT, _T("Import"), m_import, _T("Import a text file."));


	m_pToolBar->Realize();
	this->SetToolBar(m_pToolBar);
}

void Frame::SetupSizer()
{
	// Set up a box sizer
	// A sizer is a componenet that is going to allow the textbox to resize dynamically when the window does
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pTopSizer);

	// Add the button sizer to the top sizer so it is at the top
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().Border(wxALL, 5));
	
	// The following function call will add the text box to the sizer with different flags.
	// .Proportion(1) allows for the window to stretch vertically, and .Exapnd() allows for horizontal stretch
	m_pTopSizer->Add(m_pTextCtrl, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
}

void Frame::OnCut(wxCommandEvent& event)
{
	if (m_pTextCtrl->CanCut())
		m_pTextCtrl->Cut();
}

void Frame::OnCopy(wxCommandEvent& event)
{
	if (m_pTextCtrl->CanCopy())
		m_pTextCtrl->Copy();
}

void Frame::OnPaste(wxCommandEvent& event)
{
	if (m_pTextCtrl->CanPaste())
		m_pTextCtrl->Paste();
}

void Frame::OnUndo(wxCommandEvent& event)
{
	if (m_pTextCtrl->CanUndo())
		m_pTextCtrl->Undo();
}

void Frame::OnRedo(wxCommandEvent& event)
{
	if (m_pTextCtrl->CanRedo())
		m_pTextCtrl->Redo();
}

void Frame::OnSave(wxCommandEvent& event)
{
	// Ensure data transfer completes successfully
	wxFileDialog* pSaveDialog = new wxFileDialog(this, _T("Save Note"), wxEmptyString, wxEmptyString, _T("Text files (*.txt)|*.txt"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (pSaveDialog->ShowModal() == wxID_OK)
	{
		wxString filePath = pSaveDialog->GetPath();
		m_pTextCtrl->SaveFile(filePath);
	}
}

void Frame::OnImport(wxCommandEvent& event)
{
	wxFileDialog* pOpenDialog = new wxFileDialog(this, _T("Open Text File"), wxEmptyString, wxEmptyString, _T("Text files (*.txt)|*.txt"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (pOpenDialog->ShowModal() == wxID_OK)
	{
		wxString filePath = pOpenDialog->GetPath();
		wxString fileName = pOpenDialog->GetFilename();

		m_pTextCtrl->LoadFile(filePath);
	}
}
