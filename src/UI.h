#pragma once

#include "FL/Fl_Window.H"
#include "FL/Fl_Box.H"
#include "FL/Fl_Input.H"
#include "FL/Fl_Button.H"
#include "FL/Fl_Output.H"
#include "FL/Fl_Choice.H"

#include "WeightedCode.h"

class MainWindow {

    public:
        MainWindow(int w, int h, const char* name);
        void show();

    private:
        static inline std::string infString;
        static inline WeightedCode obj;
    
    // Window
        Fl_Window* window;

    // Inputs
        Fl_Input* infInput;
        Fl_Input* codeInput;

    // Buttons
        Fl_Button* btnInput;
        Fl_Button* btnCode;
        Fl_Button* btnDeCode;
        Fl_Button* btnExit;


    // Outputs
        Fl_Output* codeOutput;
        
        Fl_Output* mOutput;
        Fl_Output* nOutput;
        Fl_Output* lOutput;
        Fl_Output* ROutput;

        Fl_Output* m2Output;
        Fl_Output* R2Output;
        Fl_Output* rOutput;
        Fl_Output* JOutput;
        
        Fl_Output* resultOutput;

    // Choises
        Fl_Choice* aChoice; 
        Fl_Choice* eChoice;

    // --- Button methods ---

    static void onInput(Fl_Widget*, void*);
    static void onCode(Fl_Widget*, void*);
    static void onDeCode(Fl_Widget*, void*);
    static void onExit(Fl_Widget*, void*);
    static void clearOnInput(Fl_Widget*, void*);
    static void clearOnCode(Fl_Widget*, void*);

    static bool validateString(const std::string& s, bool isInf);

};