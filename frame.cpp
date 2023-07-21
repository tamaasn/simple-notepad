#include "frame.h"
Frame::Frame(): wxFrame(nullptr , wxID_ANY , "Simple Text Editor" , wxPoint(500,500) ,wxSize(550,450)){
    menufile = new wxMenu;
    menuother = new wxMenu;
    menuedit = new wxMenu;
    
    ios::sync_with_stdio(false);
    wcout.imbue(locale(""));

    menufile->Append(open_id , "Open file\tCtrl-O" , "Open file");
    menufile->AppendSeparator();
    menufile->Append(save_id , "Save file\tCtrl-S" , "Save file");
    menufile->Append(new_id , "New file\tCtrl-N" , "New file");
    menufile->Append(saveas_id , "Save as\tCtrl-Shift-S" , "Save as");
    
    wxPanel *panel = new wxPanel(this,-1);
    menuother->Append(about_id , "about","about this program");
    menuother->Append(wxID_EXIT , "exit","exit this program");
    
    text = new wxRichTextCtrl(this , text_id , _T(""), wxPoint(0,10) , wxSize(550,400));
    wxMenuBar *menubar= new wxMenuBar;
    menubar->SetSize(wxSize(30,100));
    
    menuedit->Append(redo_id , "Redo\tCtrl-Y" , "Redo");
    menuedit->Append(undo_id , "Undo\tCtrl-Z" , "Undo");
    menuedit->Append(copy_id , "Copy\tCtrl-C" , "Copy");
    menuedit->Append(paste_id , "Paste\tCtrl-V" , "Paste");
    menuedit->Append(cut_id , "Cut\tCtrl-X" , "Cut");

    menubar->Append(menufile , "&File");
    menubar->Append(menuedit , "&Edit");
    menubar->Append(menuother , "&Others");
    SetMenuBar(menubar);
    CreateStatusBar();
    this->SetStatusText("New file");

    Bind(wxEVT_MENU , &Frame::about , this , about_id);
    Bind(wxEVT_MENU, &Frame::open_file , this , open_id);
    Bind(wxEVT_MENU , &Frame::save_file , this , save_id);
    Bind(wxEVT_MENU , &Frame::new_file , this , new_id);
    Bind(wxEVT_MENU , &Frame::save_as , this , saveas_id);
    Bind(wxEVT_MENU , &Frame::exit_program , this , wxID_EXIT);
    Bind(wxEVT_MENU , &Frame::undo , this , undo_id);
    Bind(wxEVT_MENU , &Frame::redo , this ,redo_id);
    Bind(wxEVT_MENU , &Frame::copy , this , copy_id);
    Bind(wxEVT_MENU , &Frame::paste , this , paste_id);
    Bind(wxEVT_MENU , &Frame::cut , this , cut_id);
}

void Frame::cut(wxCommandEvent &event){
    text->Cut();
}

void Frame::undo(wxCommandEvent &event){
    text->Undo();
}

void Frame::redo(wxCommandEvent &event){
    text->Redo();
}

void Frame::copy(wxCommandEvent &event){
    text->Copy();
}

void Frame::paste(wxCommandEvent &event){
    text->Paste();
}


void Frame::exit_program(wxCommandEvent &event){
    exit(0);
}

void Frame::about(wxCommandEvent &event){
    wxLogMessage("This program made by tamaasn\nGithub page : https://github.com/tamaasn");
}

void Frame::open_file(wxCommandEvent &event){
    fileopened=true;
    wxFileDialog file_path(this , _T("Open file") , "","","",wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (file_path.ShowModal() == wxID_CANCEL){
        return;
    }
    text->ChangeValue("");
    cout << file_path.GetPath().utf8_str() << endl;
    filename = file_path.GetPath().utf8_str();
    wfstream read(filename);
    read.imbue(locale(""));
    wstring fileoutput;
    while (getline(read , fileoutput)){
        text->WriteText(fileoutput+"\n");
    }
    this->SetStatusText(filename);
    

}

void Frame::save_as(wxCommandEvent &event){
    wxFileDialog file_path(this , _T("Save file") , "" , "" ,"",wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (file_path.ShowModal() == wxID_CANCEL){
        return;
    }
    filename = file_path.GetPath().utf8_str();
    ofstream output(filename);
    output << text->GetValue().utf8_str();
    this->SetStatusText(filename);
}

void Frame::save_file(wxCommandEvent &event){
    if (!fileopened){
        wxFileDialog file_path(this , _T("Save file") , "" , "" , "" , wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
        if (file_path.ShowModal() == wxID_CANCEL){
            return;
        }
        filename = file_path.GetPath().utf8_str();
    }
    ofstream output(filename);
    output << text->GetValue().utf8_str();

}

void Frame::new_file(wxCommandEvent &event){
    fileopened=false;
    text->ChangeValue("");
    this->SetStatusText("New file");
}
