#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include <fstream>
#include <locale>
#include <iostream>

using namespace std;

class Frame: public wxFrame{
    public:
        Frame();
        ~Frame();
    private:
        int open_id=1;
        int save_id=2;
        int text_id=3;
        int saveas_id=4;
        int new_id=5;
        int about_id=6;
        int redo_id=7;
        int undo_id=8;
        int copy_id=9;
        int paste_id=10;
        int cut_id=11;
        int window_id=12;

        void about(wxCommandEvent &event);
        void open_file(wxCommandEvent &event);
        void save_file(wxCommandEvent &event);
        void new_file(wxCommandEvent &event);
        void save_as(wxCommandEvent &event);
        void exit_program(wxCommandEvent &event);
        void redo(wxCommandEvent &event);
        void undo(wxCommandEvent &event);
        void copy(wxCommandEvent &event);
        void paste(wxCommandEvent &event);
        void cut(wxCommandEvent &event);
        void resize(wxSizeEvent &event);


        bool fileopened=false;

        string filename;
        string get_save_filepath();
        
        wxMenuBar *menubar;
        wxMenu *menufile;
        wxMenu *menuedit;
        wxMenu *menuother;
        wxRichTextCtrl *text;
};
